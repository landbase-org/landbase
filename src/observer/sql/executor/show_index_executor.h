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
// Created by Wangyunlai on 2023/6/14.
//

#pragma once

#include "common/log/log.h"
#include "common/rc.h"
#include "event/session_event.h"
#include "event/sql_debug.h"
#include "event/sql_event.h"
#include "session/session.h"
#include "sql/executor/sql_result.h"
#include "sql/operator/index_list_physical_operator.h"
#include "sql/stmt/show_index_stmt.h"
#include "storage/db/db.h"

/**
 * @brief 显示所有表的执行器
 * @ingroup Executor
 * @note 与CreateIndex类似，不处理并发
 */
class ShowIndexExecutor
{
public:
  ShowIndexExecutor()          = default;
  virtual ~ShowIndexExecutor() = default;

  RC execute(SQLStageEvent *sql_event)
  {
    SqlResult    *sql_result    = sql_event->session_event()->sql_result();
    SessionEvent *session_event = sql_event->session_event();
    Stmt         *stmt          = sql_event->stmt();

    Db *db = session_event->session()->get_current_db();

    // get the table name of query index
    ShowIndexStmt *show_index_stmt = static_cast<ShowIndexStmt *>(stmt);
    const auto    &table_name      = show_index_stmt->getTableName();
    Table         *table           = db->find_table(table_name.c_str());
    if (table == nullptr) {  // table not exist;
      sql_debug("it is not exits with the table=%s of the query index", table_name.c_str());
      return RC::FAILURE;
    }
    auto &indexes = table->get_indexes();

    // index header
    // Table  | Non_unique  | Key_name  | Seq_in_index |   Column_name
    // 表名     是否唯一索引    索引名称  序号(针对多列索引) 列名和列在索引中的
    TupleSchema tuple_schema;
    tuple_schema.append_cell(TupleCellSpec("Table"));
    tuple_schema.append_cell(TupleCellSpec("Non_unique"));
    tuple_schema.append_cell(TupleCellSpec("Key_name"));
    tuple_schema.append_cell(TupleCellSpec("Seq_in_index"));
    tuple_schema.append_cell(TupleCellSpec("Column_name"));
    sql_result->set_tuple_schema(tuple_schema);

    auto oper = new IndexListPhysicalOperator(table_name, indexes);
    sql_result->set_operator(std::unique_ptr<PhysicalOperator>(oper));

    return RC::SUCCESS;
  }
};