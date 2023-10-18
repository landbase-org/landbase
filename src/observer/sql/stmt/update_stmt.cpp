/* Copyright (c) 2021 OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by Wangyunlai on 2022/5/22.
//

#include "sql/stmt/update_stmt.h"
#include "storage/db/db.h"

UpdateStmt::UpdateStmt(
    Table *table, FilterStmt *filter_stmt, std::vector<const FieldMeta *> &field_meta,
    std::vector<const Value *> &values
)
    : table_(table),
      filter_stmt_(filter_stmt),
      field_metas_(std::move(field_meta)),
      values_(std::move(values))
{}

UpdateStmt::~UpdateStmt()
{
  if (filter_stmt_ != nullptr) {
    delete filter_stmt_;
    filter_stmt_ = nullptr;
  }
  for (auto &value : values_) {
    delete value;
  }
}

// TODO: 支持多个属性的更新
RC UpdateStmt::create(Db *db, const UpdateSqlNode &update, Stmt *&stmt)
{
  // 检查参数
  const char *table_name = update.relation_name.c_str();
  if (nullptr == db || nullptr == table_name) {
    LOG_WARN("invalid argument. db=%p, table_name=%p", db, table_name);
    return RC::INVALID_ARGUMENT;
  }

  // 查找表
  Table *table = db->find_table(table_name);
  if (nullptr == table) {
    LOG_WARN("no such table. db=%s, table_name=%s", db->name(), table_name);
    return RC::SCHEMA_TABLE_NOT_EXIST;
  }

  // 查找字段元信息
  std::vector<const FieldMeta *> field_metas;
  for (auto &field_name : update.attr_list) {
    auto field_meta = table->table_meta().field(field_name.c_str());
    if (field_meta == nullptr) {
      LOG_ERROR("Fail to find field %s in table %s", field_name.c_str(), table->name());
      return RC::SCHEMA_FIELD_NOT_EXIST;
    }
    field_metas.push_back(field_meta);
  }

  // 检查字段和值的类型是否匹配
  for (int i = 0; i < field_metas.size(); i++) {
    if (field_metas[i]->type() != update.value_list[i].attr_type()) {
      LOG_ERROR(
          "Fail to update %s, field type(%d) and value type(%d) mismatch",
          table->name(),
          field_metas[i]->type(),
          update.value_list[i].attr_type()
      );
      return RC::INVALID_ARGUMENT;
    }
  }

  // 新建 Value
  std::vector<const Value *> values;
  for (auto &attr : update.value_list) {
    values.emplace_back(new Value(attr));
  }

  // 设置过滤条件
  std::unordered_map<std::string, Table *> table_map;
  table_map.insert(std::pair<std::string, Table *>(std::string(table_name), table));

  FilterStmt *filter_stmt = nullptr;
  RC          rc          = FilterStmt::create(
      db, table, &table_map, update.conditions.data(), static_cast<int>(update.conditions.size()), filter_stmt
  );
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to create filter statement. rc=%d:%s", rc, strrc(rc));
    return rc;
  }

  // 新建 Stmt
  stmt = new UpdateStmt(table, filter_stmt, field_metas, values);
  return RC::SUCCESS;
}
