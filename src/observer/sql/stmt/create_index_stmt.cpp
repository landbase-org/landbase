/* Copyright (c) 2021 OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL
v2. You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by Wangyunlai on 2023/4/25.
//

#include "sql/stmt/create_index_stmt.h"
#include "common/lang/string.h"
#include "common/log/log.h"
#include "event/sql_debug.h"
#include "storage/db/db.h"
#include "storage/field/field_meta.h"
#include "storage/table/table.h"

using namespace std;
using namespace common;

RC CreateIndexStmt::create(Db *db, const CreateIndexSqlNode &create_index, Stmt *&stmt)
{
  stmt                   = nullptr;
  const auto  atr_names  = create_index.attribute_names;
  const char *table_name = create_index.relation_name.c_str();
  Table      *table      = db->find_table(table_name);

  // check the table_name empty;
  if (is_blank(table_name) || is_blank(create_index.index_name.c_str())) {
    sql_debug("invalid argument. db=%p, table_name=%p, index name=%s", db, table_name, create_index.index_name.c_str());
    return RC::INVALID_ARGUMENT;
  }

  // check whether the table exists
  if (nullptr == table) {
    sql_debug("no such table. db=%s, table_name=%s", db->name(), table_name);
    return RC::SCHEMA_TABLE_NOT_EXIST;
  }

  Index *index = table->find_index(create_index.index_name.c_str());
  if (nullptr != index) {
    sql_debug("index with name(%s) already exists. table name=%s", create_index.index_name.c_str(), table_name);
    return RC::SCHEMA_INDEX_NAME_REPEAT;
  }

  auto                   filed_metas = table->table_meta().field_metas();
  std::vector<FieldMeta> idx_field_meta;
  for (std::string atr_name : atr_names) {
    // check
    auto target = std::find_if(filed_metas->begin(), filed_metas->end(), [&atr_name](const auto &meta) {
      return atr_name == meta.name();
    });

    if (filed_metas->end() == target) {
      sql_debug("no such field in table. db=%s, table=%s, field name=%s", db->name(), table_name, atr_name.c_str());
      return RC::SCHEMA_FIELD_NOT_EXIST;
    }

    idx_field_meta.emplace_back(*target);
  }

  stmt = new CreateIndexStmt(table, std::move(idx_field_meta), create_index.unique, create_index.index_name);
  return RC::SUCCESS;
}