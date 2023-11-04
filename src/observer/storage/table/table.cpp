/* Copyright (c) 2021 Xie Meiyi(xiemeiyi@hust.edu.cn) and OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by Meiyi & Wangyunlai on 2021/5/13.
//

#include <algorithm>
#include <cstddef>
#include <cstdio>
#include <limits.h>
#include <memory>
#include <numeric>
#include <string.h>
#include <string>
#include <unordered_set>
#include <vector>

#include "common/defs.h"
#include "common/lang/string.h"
#include "common/log/log.h"
#include "event/sql_debug.h"
#include "sql/parser/parse_defs.h"
#include "storage/buffer/disk_buffer_pool.h"
#include "storage/common/condition_filter.h"
#include "storage/common/meta_util.h"
#include "storage/field/field.h"
#include "storage/field/field_meta.h"
#include "storage/index/bplus_tree_index.h"
#include "storage/index/index.h"
#include "storage/record/record_manager.h"
#include "storage/table/table.h"
#include "storage/table/table_meta.h"
#include "storage/trx/trx.h"

Table::~Table()
{
  if (record_handler_ != nullptr) {
    delete record_handler_;
    record_handler_ = nullptr;
  }

  if (data_buffer_pool_ != nullptr) {
    data_buffer_pool_->close_file();
    data_buffer_pool_ = nullptr;
  }

  for (std::vector<Index *>::iterator it = indexes_.begin(); it != indexes_.end(); ++it) {
    Index *index = *it;
    delete index;
  }
  indexes_.clear();

  LOG_INFO("Table has been closed: %s", name());
}

RC Table::create(
    int32_t table_id, const char *path, const char *name, const char *base_dir, int attribute_count,
    const AttrInfoSqlNode attributes[]
)
{
  if (table_id < 0) {
    LOG_WARN("invalid table id. table_id=%d, table_name=%s", table_id, name);
    return RC::INVALID_ARGUMENT;
  }

  if (common::is_blank(name)) {
    LOG_WARN("Name cannot be empty");
    return RC::INVALID_ARGUMENT;
  }
  LOG_INFO("Begin to create table %s:%s", base_dir, name);

  if (attribute_count <= 0 || nullptr == attributes) {
    LOG_WARN("Invalid arguments. table_name=%s, attribute_count=%d, attributes=%p", name, attribute_count, attributes);
    return RC::INVALID_ARGUMENT;
  }

  RC rc = RC::SUCCESS;

  // 使用 table_name.table 记录一个表的元数据
  // 判断表文件是否已经存在
  int fd = ::open(path, O_WRONLY | O_CREAT | O_EXCL | O_CLOEXEC, 0600);
  if (fd < 0) {
    if (EEXIST == errno) {
      LOG_ERROR("Failed to create table file, it has been created. %s, EEXIST, %s", path, strerror(errno));
      return RC::SCHEMA_TABLE_EXIST;
    }
    LOG_ERROR("Create table file failed. filename=%s, errmsg=%d:%s", path, errno, strerror(errno));
    return RC::IOERR_OPEN;
  }

  close(fd);

  // 创建表元信息
  if ((rc = table_meta_.init(table_id, name, attribute_count, attributes)) != RC::SUCCESS) {
    LOG_ERROR("Failed to init table meta. name:%s, ret:%d", name, rc);
    return rc;  // delete table file
  }

  std::fstream fs;
  fs.open(path, std::ios_base::out | std::ios_base::binary);
  if (!fs.is_open()) {
    LOG_ERROR("Failed to open file for write. file name=%s, errmsg=%s", path, strerror(errno));
    return RC::IOERR_OPEN;
  }

  // 记录元数据到文件中
  table_meta_.serialize(fs);
  fs.close();

  std::string        data_file = table_data_file(base_dir, name);
  BufferPoolManager &bpm       = BufferPoolManager::instance();
  rc                           = bpm.create_file(data_file.c_str());
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to create disk buffer pool of data file. file name=%s", data_file.c_str());
    return rc;
  }

  rc = init_record_handler(base_dir);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to create table %s due to init record handler failed.", data_file.c_str());
    // don't need to remove the data_file
    return rc;
  }

  base_dir_ = base_dir;
  LOG_INFO("Successfully create table %s:%s", base_dir, name);
  return rc;
}

RC Table::drop(const char *base_dir)
{
  // 初始化
  RC                 rc  = RC::SUCCESS;
  BufferPoolManager &bpm = BufferPoolManager::instance();

  // close data buffer pool and delete data file
  auto path = table_data_file(base_dir, name());
  rc        = bpm.close_file(path.c_str());
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to close BufferPool: %s", name());
    return RC::FAILURE;
  }
  int fail = remove(path.c_str());
  if (fail) {
    LOG_ERROR("Failed to drop table data file: %s", name());
    return RC::FAIL_TO_DELETE_FILE;
  }

  // meta has no buffer pool only need to delete the meta file
  path = table_meta_file(base_dir, name());
  fail = remove(path.c_str());
  if (fail) {
    LOG_ERROR("Failed to drop table meta file: %s", name());
    return RC::FAIL_TO_DELETE_FILE;
  }

  // delete the index buffer pool and delete index file
  for (auto index : indexes_) {
    path = table_index_file(base_dir, name(), index->index_meta().name());
    bpm.close_file(path.c_str());
    if (rc != RC::SUCCESS) {
      LOG_ERROR("Failed to close BufferPool: %s", name());
      return RC::FAILURE;
    }
    fail = remove(path.c_str());
    if (fail) {
      LOG_ERROR("Failed to drop index %s on table %s", index->index_meta().name(), name());
      return RC::FAIL_TO_DELETE_FILE;
    }
  }

  return rc;
}

RC Table::open(const char *meta_file, const char *base_dir)
{
  // 加载元数据文件
  std::fstream fs;
  std::string  meta_file_path = std::string(base_dir) + common::FILE_PATH_SPLIT_STR + meta_file;
  fs.open(meta_file_path, std::ios_base::in | std::ios_base::binary);
  if (!fs.is_open()) {
    LOG_ERROR("Failed to open meta file for read. file name=%s, errmsg=%s", meta_file_path.c_str(), strerror(errno));
    return RC::IOERR_OPEN;
  }
  if (table_meta_.deserialize(fs) < 0) {
    LOG_ERROR("Failed to deserialize table meta. file name=%s", meta_file_path.c_str());
    fs.close();
    return RC::INTERNAL;
  }
  fs.close();

  // 加载数据文件
  RC rc = init_record_handler(base_dir);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to open table %s due to init record handler failed.", base_dir);
    // don't need to remove the data_file
    return rc;
  }

  base_dir_ = base_dir;

  const int index_num = table_meta_.index_num();
  for (int i = 0; i < index_num; i++) {
    const IndexMeta                *index_meta  = table_meta_.index(i);
    const std::vector<std::string> *field_names = index_meta->fields();
    std::vector<FieldMeta>          field_metas;

    for (auto field_name : *field_names) {
      auto field_meta = table_meta_.field(field_name.c_str());
      if (nullptr == field_meta) {
        LOG_ERROR(
            "Found invalid index meta info which has a non-exists field. table=%s, index=%s, field=%s",
            name(),
            index_meta->name(),
            index_meta->field()
        );
        // skip cleanup
        //  do all cleanup action in destructive Table function
        return RC::INTERNAL;
      }
      field_metas.push_back(*field_meta);
    }

    BplusTreeIndex *index      = new BplusTreeIndex();
    std::string     index_file = table_index_file(base_dir, name(), index_meta->name());
    rc                         = index->open(index_file.c_str(), *index_meta, field_metas);
    if (rc != RC::SUCCESS) {
      delete index;
      LOG_ERROR(
          "Failed to open index. table=%s, index=%s, file=%s, rc=%s",
          name(),
          index_meta->name(),
          index_file.c_str(),
          strrc(rc)
      );
      // skip cleanup
      //  do all cleanup action in destructive Table function.
      return rc;
    }
    indexes_.push_back(index);
  }

  return rc;
}

RC Table::insert_record(Record &record)
{
  RC rc = RC::SUCCESS;
  rc    = record_handler_->insert_record(record.data(), table_meta_.record_size(), &record.rid());
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Insert record failed. table name=%s, rc=%s", table_meta_.name(), strrc(rc));
    return rc;
  }

  rc = insert_entry_of_indexes(record);
  if (rc != RC::SUCCESS) {  // 可能出现了键值重复
    RC rc2 = delete_entry_of_indexes(record, false /*error_on_not_exists*/);
    if (rc2 != RC::SUCCESS) {
      LOG_ERROR(
          "Failed to rollback index data when insert index entries failed. table name=%s, rc=%d:%s",
          name(),
          rc2,
          strrc(rc2)
      );
    }
    rc2 = record_handler_->delete_record(&record.rid());
    if (rc2 != RC::SUCCESS) {
      LOG_PANIC(
          "Failed to rollback record data when insert index entries failed. table name=%s, rc=%d:%s",
          name(),
          rc2,
          strrc(rc2)
      );
    }
  }
  return rc;
}

RC Table::visit_record(const RID &rid, bool readonly, std::function<void(Record &)> visitor)
{
  return record_handler_->visit_record(rid, readonly, visitor);
}

RC Table::update_record(const Record &record, const Record &new_record)
{
  RC rc = RC::SUCCESS;
  rc    = delete_entry_of_indexes(record, false);
  if (rc != RC::SUCCESS) {
    sql_debug("Failed to delete index entries. table=%s, rc=%d:%s", name(), rc, strrc(rc));
    return rc;
  }

  rc = insert_entry_of_indexes(new_record);
  if (rc != RC::SUCCESS) {
    sql_debug("Failed to insert index entries. table=%s, rc=%d:%s", name(), rc, strrc(rc));
    // 回滚
    insert_entry_of_indexes(record);
    return rc;
  }

  // 之前的没毛病之后就可以更新索引数据了
  rc = record_handler_->update_record(new_record.data(), &record.rid());
  if (rc != RC::SUCCESS) {
    sql_debug("Update record failed. table name=%s, rc=%s", table_meta_.name(), strrc(rc));
    return rc;
  }
  return rc;
}

RC Table::get_record(const RID &rid, Record &record)
{
  const int record_size = table_meta_.record_size();
  char     *record_data = (char *)malloc(record_size);
  ASSERT(nullptr != record_data, "failed to malloc memory. record data size=%d", record_size);

  auto copier = [&record, record_data, record_size](Record &record_src) {
    memcpy(record_data, record_src.data(), record_size);
    record.set_rid(record_src.rid());
  };
  RC rc = record_handler_->visit_record(rid, true /*readonly*/, copier);
  if (rc != RC::SUCCESS) {
    free(record_data);
    LOG_WARN("failed to visit record. rid=%s, table=%s, rc=%s", rid.to_string().c_str(), name(), strrc(rc));
    return rc;
  }

  record.set_data_owner(record_data, record_size);
  return rc;
}

RC Table::recover_insert_record(Record &record)
{
  RC rc = RC::SUCCESS;
  rc    = record_handler_->recover_insert_record(record.data(), table_meta_.record_size(), record.rid());
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Insert record failed. table name=%s, rc=%s", table_meta_.name(), strrc(rc));
    return rc;
  }

  rc = insert_entry_of_indexes(record);
  if (rc != RC::SUCCESS) {  // 可能出现了键值重复
    RC rc2 = delete_entry_of_indexes(record, false /*error_on_not_exists*/);
    if (rc2 != RC::SUCCESS) {
      LOG_ERROR(
          "Failed to rollback index data when insert index entries failed. table name=%s, rc=%d:%s",
          name(),
          rc2,
          strrc(rc2)
      );
    }
    rc2 = record_handler_->delete_record(&record.rid());
    if (rc2 != RC::SUCCESS) {
      LOG_PANIC(
          "Failed to rollback record data when insert index entries failed. table name=%s, rc=%d:%s",
          name(),
          rc2,
          strrc(rc2)
      );
    }
  }
  return rc;
}

const char *Table::name() const { return table_meta_.name(); }

const TableMeta &Table::table_meta() const { return table_meta_; }

// Record: __null | 其他字段...
RC Table::make_record(int value_num, const Value *values, Record &record)
{
  const int normal_field_start_index = table_meta_.sys_field_num();

  // 检查 value 数量是否和字段数目相同
  if (value_num + normal_field_start_index != table_meta_.field_num()) {
    LOG_WARN("Input values don't match the table's schema, table name:%s", table_meta_.name());
    return RC::SCHEMA_FIELD_MISSING;
  }

  // 检查 value 和字段是否匹配
  for (int i = 0; i < value_num; i++) {
    const FieldMeta *field = table_meta_.field(i + normal_field_start_index);
    const Value     &value = values[i];

    if (value.is_null()) {
      if (!field->nullable()) {
        return RC::SCHEMA_FIELD_NOT_NULLABLE;
      } else {
        continue;
      }
    }

    if (field->type() != value.attr_type()) {
      Value *change = const_cast<Value *>(&value);
      if (change->type_cast(field->type())) {
        continue;
      }
      LOG_ERROR(
          "Invalid value type. table name =%s, field name=%s, type=%d, but given=%d",
          table_meta_.name(),
          field->name(),
          field->type(),
          value.attr_type()
      );
      return RC::SCHEMA_FIELD_TYPE_MISMATCH;
    }
  }

  // 复制所有字段的值，注意处理 null 值
  int   record_size = table_meta_.record_size();
  char *record_data = (char *)malloc(record_size);

  // 将整个record的数据传入，会返回 __null 字段的 bitmap
  auto null_field = table_meta_.bitmap_of_null_field(record_data);

  for (int i = 0; i < value_num; i++) {
    const FieldMeta *field    = table_meta_.field(i + normal_field_start_index);
    const Value     &value    = values[i];
    size_t           copy_len = field->len();

    if (value.is_null()) {
      null_field.set_bit(normal_field_start_index + i);
      // memcpy(record_data + field->offset(), "\0", copy_len);
      continue;
    }

    null_field.clear_bit(normal_field_start_index + i);
    if (field->type() == CHARS || field->type() == TEXTS) {
      const size_t data_len = value.length();
      if (copy_len > data_len) {
        copy_len = data_len + 1;
      }
    }
    memcpy(record_data + field->offset(), value.data(), copy_len);
  }

  record.set_data_owner(record_data, record_size);
  return RC::SUCCESS;
}

RC Table::init_record_handler(const char *base_dir)
{
  std::string data_file = table_data_file(base_dir, table_meta_.name());

  RC rc = BufferPoolManager::instance().open_file(data_file.c_str(), data_buffer_pool_);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to open disk buffer pool for file:%s. rc=%d:%s", data_file.c_str(), rc, strrc(rc));
    return rc;
  }

  record_handler_ = new RecordFileHandler();
  rc              = record_handler_->init(data_buffer_pool_);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to init record handler. rc=%s", strrc(rc));
    data_buffer_pool_->close_file();
    data_buffer_pool_ = nullptr;
    delete record_handler_;
    record_handler_ = nullptr;
    return rc;
  }

  return rc;
}

RC Table::get_record_scanner(RecordFileScanner &scanner, Trx *trx, bool readonly, ConditionFilter *filter_ptr)
{
  RC rc = scanner.open_scan(this, *data_buffer_pool_, trx, readonly, nullptr);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("failed to open scanner. rc=%s", strrc(rc));
  }
  return rc;
}

RC Table::create_index(Trx *trx, bool unique, const std::vector<FieldMeta> *field_metas, const char *index_name)
{
  if (common::is_blank(index_name) || 0 == field_metas->size()) {
    LOG_INFO("Invalid input arguments, table name is %s, index_name is blank or attribute_name is blank", name());
    return RC::INVALID_ARGUMENT;
  }

  IndexMeta                new_index_meta;
  std::vector<std::string> field_names;
  std::for_each(field_metas->begin(), field_metas->end(), [&field_names](const auto &meta) {
    field_names.push_back(meta.name());
  });

  std::string field_names_str = "";
  for (size_t i = 0; i < field_names.size(); i++) {
    field_names_str += i == 0 ? ' ' : ',';
    field_names_str += field_names[i];
  }

  if (table_meta_.find_index_by_fields(field_names)) {  // 如果找到了， 则说明当前索引已经存在
    LOG_INFO("Invalid input arguments, table name is %s, attribute %s exist index", name(), field_names_str.c_str());
    return RC::INVALID_ARGUMENT;
  }

  RC rc = new_index_meta.init(index_name, *field_metas, unique);
  if (rc != RC::SUCCESS) {
    LOG_INFO(
        "Failed to init IndexMeta in table:%s, index_name:%s, field_name:%s",
        name(),
        index_name,
        field_names_str.c_str()
    );
    return rc;
  }

  // 创建索引相关数据
  BplusTreeIndex *index      = new BplusTreeIndex();
  std::string     index_file = table_index_file(base_dir_.c_str(), name(), index_name);
  rc                         = index->create(index_file.c_str(), new_index_meta, *field_metas);
  if (rc != RC::SUCCESS) {
    delete index;
    LOG_ERROR("Failed to create bplus tree index. file name=%s, rc=%d:%s", index_file.c_str(), rc, strrc(rc));
    return rc;
  }

  // 遍历当前的所有数据，插入这个索引
  RecordFileScanner scanner;
  rc = get_record_scanner(scanner, trx, true /*readonly*/);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to create scanner while creating index. table=%s, index=%s, rc=%s", name(), index_name, strrc(rc));
    return rc;
  }

  Record record;
  while (scanner.has_next()) {
    rc = scanner.next(record);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to scan records while creating index. table=%s, index=%s, rc=%s", name(), index_name, strrc(rc));
      return rc;
    }
    rc = index->insert_entry(record.data(), &record.rid());
    if (rc != RC::SUCCESS) {
      LOG_WARN(
          "failed to insert record into index while creating index. table=%s, index=%s, rc=%s",
          name(),
          index_name,
          strrc(rc)
      );
      return rc;
    }
  }
  scanner.close_scan();
  LOG_INFO("inserted all records into new index. table=%s, index=%s", name(), index_name);

  indexes_.push_back(index);

  /// 接下来将这个索引放到表的元数据中
  TableMeta new_table_meta(table_meta_);
  rc = new_table_meta.add_index(new_index_meta);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to add index (%s) on table (%s). error=%d:%s", index_name, name(), rc, strrc(rc));
    return rc;
  }

  /// 内存中有一份元数据，磁盘文件也有一份元数据。修改磁盘文件时，先创建一个临时文件，写入完成后再rename为正式文件
  /// 这样可以防止文件内容不完整
  // 创建元数据临时文件
  std::string  tmp_file = table_meta_file(base_dir_.c_str(), name()) + ".tmp";
  std::fstream fs;
  fs.open(tmp_file, std::ios_base::out | std::ios_base::binary | std::ios_base::trunc);
  if (!fs.is_open()) {
    LOG_ERROR("Failed to open file for write. file name=%s, errmsg=%s", tmp_file.c_str(), strerror(errno));
    return RC::IOERR_OPEN;  // 创建索引中途出错，要做还原操作
  }
  if (new_table_meta.serialize(fs) < 0) {
    LOG_ERROR("Failed to dump new table meta to file: %s. sys err=%d:%s", tmp_file.c_str(), errno, strerror(errno));
    return RC::IOERR_WRITE;
  }
  fs.close();

  // 覆盖原始元数据文件
  std::string meta_file = table_meta_file(base_dir_.c_str(), name());
  int         ret       = rename(tmp_file.c_str(), meta_file.c_str());
  if (ret != 0) {
    LOG_ERROR(
        "Failed to rename tmp meta file (%s) to normal meta file (%s) while creating index (%s) on table (%s). "
        "system error=%d:%s",
        tmp_file.c_str(),
        meta_file.c_str(),
        index_name,
        name(),
        errno,
        strerror(errno)
    );
    return RC::IOERR_WRITE;
  }

  table_meta_.swap(new_table_meta);

  LOG_INFO("Successfully added a new index (%s) on the table (%s)", index_name, name());
  return rc;
}

RC Table::delete_record(const Record &record)
{
  RC rc = delete_entry_of_indexes(record, true);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to delete index entries. table=%s, rc=%d:%s", name(), rc, strrc(rc));
    return rc;
  }
  rc = record_handler_->delete_record(&record.rid());
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to delete record. table=%s, rc=%d:%s", name(), rc, strrc(rc));
    return rc;
  }
  return rc;
}

RC Table::insert_entry_of_indexes(const Record &record)
{
  Record tmp_record(record);
  auto   bitmap = table_meta_.bitmap_of_null_field(tmp_record.data());

  RC rc = RC::SUCCESS;
  for (Index *index : indexes_) {
    // 含有 null 值的字段不插入索引
    bool has_null = false;

    auto &field_metas = index->field_metas();
    for (auto &field_meta : field_metas) {
      int field_index = table_meta_.field_index(&field_meta);
      if (field_index == -1) {
        LOG_ERROR("Failed to find field index. table=%s, field=%s", name(), field_meta.name());
        return RC::INTERNAL;
      }
      if (bitmap.get_bit(field_index)) {
        has_null = true;
        break;
      }
    }

    if (has_null) {
      continue;
    }

    rc = index->insert_entry(record.data(), &record.rid());
    if (rc != RC::SUCCESS) {
      break;
    }
  }
  return rc;
}

RC Table::delete_entry_of_indexes(const Record &record, bool error_on_not_exists)
{
  Record tmp_record(record);
  auto   bitmap = table_meta_.bitmap_of_null_field(tmp_record.data());

  RC rc = RC::SUCCESS;
  for (Index *index : indexes_) {
    // 含有 null 值的字段不需要从索引里删除
    bool has_null = false;

    auto &field_metas = index->field_metas();
    for (auto &field_meta : field_metas) {
      int field_index = table_meta_.field_index(&field_meta);
      if (field_index == -1) {
        LOG_ERROR("Failed to find field index. table=%s, field=%s", name(), field_meta.name());
        return RC::INTERNAL;
      }
      if (bitmap.get_bit(field_index)) {
        has_null = true;
        break;
      }
    }

    if (has_null) {
      continue;
    }

    rc = index->delete_entry(record.data(), &record.rid());
    if (rc != RC::SUCCESS) {
      if (rc != RC::RECORD_INVALID_KEY || !error_on_not_exists) {
        break;
      }
    }
  }
  return rc;
}

Index *Table::find_index(const char *index_name) const
{
  for (Index *index : indexes_) {
    if (0 == strcmp(index->index_meta().name(), index_name)) {
      return index;
    }
  }
  return nullptr;
}
Index *Table::find_index_by_field(const char *field_name) const
{
  const TableMeta &table_meta = this->table_meta();
  const IndexMeta *index_meta = table_meta.find_index_by_field(field_name);
  if (index_meta != nullptr) {
    return this->find_index(index_meta->name());
  }
  return nullptr;
}

std::vector<Index *> Table::find_indexes_by_field(const char *field_name) const
{
  std::vector<Index *> res;
  for (auto index : indexes_) {
    if (0 == strcmp(index->index_meta().field(), field_name)) {
      res.emplace_back(index);
    }
  }
  return res;
}

Index *Table::find_index_by_fields(std::vector<std::string> &field_names) const
{
  // 因为给出的fields可能为乱顺序， 所以需要用set
  std::unordered_set<std::string> set(field_names.begin(), field_names.end());
  for (auto index : indexes_) {
    if (index->field_metas().size() != set.size()) {
      continue;
    }

    bool equa = true;
    for (const auto &field_meta : index->field_metas()) {
      if (!set.contains(field_meta.name())) {
        equa = false;
        break;
      }
    }

    if (equa) {
      return index;
    }
  }

  return nullptr;
}

RC Table::sync()
{
  RC rc = RC::SUCCESS;
  for (Index *index : indexes_) {
    rc = index->sync();
    if (rc != RC::SUCCESS) {
      LOG_ERROR(
          "Failed to flush index's pages. table=%s, index=%s, rc=%d:%s",
          name(),
          index->index_meta().name(),
          rc,
          strrc(rc)
      );
      return rc;
    }
  }
  LOG_INFO("Sync table over. table=%s", name());
  return rc;
}

bool Table::is_null(const FieldMeta *field_meta, char *data) const
{
  auto null_field  = table_meta_.bitmap_of_null_field(data);
  int  field_index = table_meta_.field_index(field_meta);
  if (field_index == -1) {
    LOG_ERROR("Failed to find field index. table=%s, field=%s", name(), field_meta->name());
    return false;
  }
  return null_field.get_bit(field_index);
}
