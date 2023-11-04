/* Copyright (c) 2021OceanBase and/or its affiliates. All rights reserved.
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

#include "sql/stmt/insert_stmt.h"
#include "common/log/log.h"
#include "event/sql_debug.h"
#include "sql/parser/value.h"
#include "storage/db/db.h"
#include "storage/table/table.h"
InsertStmt::InsertStmt(Table *table, const std::vector<std::vector<Value>> &values_list, int value_list_amount)
    : table_(table),
      values_list_(values_list),
      value_list_amount_(value_list_amount)
{}

RC InsertStmt::create(Db *db, const InsertSqlNode &inserts, Stmt *&stmt)
{
  // 检查参数
  const char *table_name = inserts.relation_name.c_str();
  if (nullptr == db || nullptr == table_name || inserts.values_list.empty()) {
    sql_debug(
        "invalid argument. db=%p, table_name=%p, value_list_num=%d",
        db,
        table_name,
        static_cast<int>(inserts.values_list.size())
    );
    return RC::INVALID_ARGUMENT;
  }

  // check whether the table exists
  Table *table = db->find_table(table_name);
  if (nullptr == table) {
    sql_debug("no such table. db=%s, table_name=%s", db->name(), table_name);
    return RC::SCHEMA_TABLE_NOT_EXIST;
  }

  // 检查变量是否满足字段的约束
  const auto      &value_list = inserts.values_list;
  const TableMeta &table_meta = table->table_meta();
  const int        field_num  = table_meta.field_num() - table_meta.sys_field_num();
  for (const auto &values : value_list) {
    const int value_num = values.size();
    if (field_num != value_num) {
      sql_debug("schema mismatch. value num=%d, field num in schema=%d", value_num, field_num);
      return RC::SCHEMA_FIELD_MISSING;
    }

    // 检查字段和变量类型是否匹配，字段不可为空时变量是否为空
    const int sys_field_num = table_meta.sys_field_num();
    for (int i = 0; i < value_num; i++) {
      const FieldMeta *field_meta = table_meta.field(i + sys_field_num);
      const AttrType   field_type = field_meta->type();
      const AttrType   value_type = values[i].attr_type();

      if (values[i].is_null()) {
        if (!field_meta->nullable()) {
          sql_debug("table %s field %s is not nullable", table_meta.name(), field_meta->name());
          return RC::SCHEMA_FIELD_NOT_NULLABLE;
        } else {
          continue;
        }
      }

      if (field_type != value_type) {
        // 转换日期 value
        if (field_type == DATES && value_type == CHARS) {
          Value *change = const_cast<Value *>(&values[i]);
          // PS: must convert the string to int_32 here!
          int32_t mid = 0;
          mid         = convert_string_to_date(change->data());
          if (mid == -1) {
            sql_debug(
                "field type mismatch. table=%s, field=%s, field type=%d, value_type=%d",
                table_name,
                field_meta->name(),
                field_type,
                value_type
            );
            return RC::SCHEMA_FIELD_TYPE_MISMATCH;
          }
          change->set_date(mid);
          continue;
        }
        // 如果可以转换，就转换一下
        auto &change = const_cast<Value &>(values[i]);
        if (change.type_cast(field_type)) {
          if (values[i].attr_type() == TEXTS && values[i].length() > field_meta->len()) {
            sql_debug(
                "field length mismatch. table=%s, field=%s, field length=%d, value length=%d",
                table_name,
                field_meta->name(),
                field_meta->len(),
                values[i].length()
            );
            return RC::SCHEMA_FIELD_TYPE_MISMATCH;
          }
          continue;
        }
        sql_debug(
            "field type mismatch. table=%s, field=%s, field type=%d, value_type=%d",
            table_name,
            field_meta->name(),
            field_type,
            value_type
        );
        return RC::SCHEMA_FIELD_TYPE_MISMATCH;
      }
    }
  }

  // everything alright
  stmt = new InsertStmt(table, inserts.values_list, value_list.size());
  return RC::SUCCESS;
}