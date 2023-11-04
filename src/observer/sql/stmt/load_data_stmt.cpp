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
// Created by Wangyunlai on 2023/7/12.
//

#include "sql/stmt/load_data_stmt.h"
#include "common/lang/string.h"
#include "common/log/log.h"
#include "event/sql_debug.h"
#include "storage/db/db.h"
#include "storage/table/table.h"
#include <unistd.h>
using namespace common;

RC LoadDataStmt::create(Db *db, const LoadDataSqlNode &load_data, Stmt *&stmt)
{
  RC          rc         = RC::SUCCESS;
  const char *table_name = load_data.relation_name.c_str();
  if (is_blank(table_name) || is_blank(load_data.file_name.c_str())) {
    sql_debug("invalid argument. db=%p, table_name=%p, file name=%s", db, table_name, load_data.file_name.c_str());
    return RC::INVALID_ARGUMENT;
  }

  // check whether the table exists
  Table *table = db->find_table(table_name);
  if (nullptr == table) {
    sql_debug("no such table. db=%s, table_name=%s", db->name(), table_name);
    return RC::SCHEMA_TABLE_NOT_EXIST;
  }

  if (0 != access(load_data.file_name.c_str(), R_OK)) {
    sql_debug("no such file to load. file name=%s, error=%s", load_data.file_name.c_str(), strerror(errno));
    return RC::FILE_NOT_EXIST;
  }

  stmt = new LoadDataStmt(table, load_data.file_name.c_str());
  return rc;
}
