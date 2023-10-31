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
// Created by Wangyunlai on 2023/6/13.
//

#include "sql/executor/create_table_executor.h"

#include "common/log/log.h"
#include "event/session_event.h"
#include "event/sql_event.h"
#include "session/session.h"
#include "sql/operator/physical_operator.h"
#include "sql/operator/project_physical_operator.h"
#include "sql/optimizer/logical_plan_generator.h"
#include "sql/optimizer/physical_plan_generator.h"
#include "sql/parser/parse_defs.h"
#include "sql/stmt/create_table_stmt.h"
#include "sql/stmt/select_stmt.h"
#include "sql/stmt/stmt.h"
#include "storage/db/db.h"
#include "storage/table/table.h"
#include "storage/trx/trx.h"

/**
 * @brief 处理Create-Select的函数
 * @ingroup executor
 * @param stmt 
 * @param session 
 * @return RC 
 * @details 目前处理了两种模式，接下来需要等待expression的完成之后，支持expression
 */

RC CreateTableExecutor::execute_sub_select(Stmt *stmt, Session *session)
{
  CreateTableStmt             *ct_stmt    = dynamic_cast<CreateTableStmt *>(stmt);
  Db                          *cur_db     = session->get_current_db();
  Trx                         *cur_trx    = session->current_trx();
  Table                       *new_table  = nullptr;
  std::vector<AttrInfoSqlNode> from_attrs = ct_stmt->attr_infos();

  ASSERT(
      stmt->type() == StmtType::CREATE_TABLE,
      "create table executor can not run this command: %d",
      static_cast<int>(stmt->type())
  );

  // TODOX: 处理Create-Select
  // 默认只有一个子查寻
  Expression   *sub_select_expr = ct_stmt->sub_select().front();
  SelectSqlNode sub_select_sql  = dynamic_cast<SubQueryExpression *>(sub_select_expr)->get_sub_select();
  Stmt         *sub_select_stmt = nullptr;
  RC            rc              = SelectStmt::create(cur_db, sub_select_sql, sub_select_stmt);
  if (rc != RC::SUCCESS) {
    LOG_WARN("Failed to create sub-select stmt");
    return rc;
  }
  // 如果Attr为空，则根据Select构造所有的Attr
  if (from_attrs.empty()) {
    for (auto field : dynamic_cast<SelectStmt *>(sub_select_stmt)->query_fields()) {
      FieldMeta       fm          = *field.meta();
      AttrInfoSqlNode select_attr = AttrInfoSqlNode{fm.type(), fm.name(), unsigned(fm.len()), fm.nullable()};
      from_attrs.emplace_back(std::move(select_attr));
    }
  }
  // 尝试创建一个新的表
  const int   attr_num = static_cast<int>(from_attrs.size());
  const char *t_name   = ct_stmt->table_name().c_str();
  RC          inner_rc = cur_db->create_table(t_name, attr_num, from_attrs.data());
  if (inner_rc != RC::SUCCESS) {
    LOG_WARN("Failed to create table from sub-select");
    return inner_rc;
  }
  // 处理Select算子，将它转为Project算子并Open
  std::unique_ptr<LogicalOperator> logical_oper;
  LogicalPlanGenerator             logical_generator;
  logical_generator.create(sub_select_stmt, logical_oper);
  std::unique_ptr<PhysicalOperator> physical_oper;
  PhysicalPlanGenerator             physical_generator;
  physical_generator.create(*logical_oper, physical_oper);
  auto subselect_oper = dynamic_cast<ProjectPhysicalOperator *>(physical_oper.get());
  subselect_oper->open(cur_trx);

  // X: 拿到新表，把值加入进新的表
  new_table = cur_db->find_table(t_name);
  while (subselect_oper->next() == RC::SUCCESS) {
    Tuple             *temp_tup = subselect_oper->current_tuple();
    std::vector<Value> row_data;
    for (size_t idx{0}; idx < temp_tup->cell_num(); idx++) {
      Value temp_value;
      temp_tup->cell_at(idx, temp_value);
      row_data.emplace_back(temp_value);
    }
    Record temp_record;
    inner_rc = new_table->make_record(row_data.size(), row_data.data(), temp_record);
    if (inner_rc != RC::SUCCESS) {
      LOG_WARN("Failed to make record from select");
      return inner_rc;
    }
    inner_rc = cur_trx->insert_record(new_table, temp_record);
    if (inner_rc != RC::SUCCESS) {
      LOG_WARN("Failed to insert record from select");
      return inner_rc;
    }
  }
  return RC::SUCCESS;

}

RC CreateTableExecutor::execute(SQLStageEvent *sql_event)
{
  Stmt    *stmt    = sql_event->stmt();
  Session *session = sql_event->session_event()->session();
  ASSERT(
      stmt->type() == StmtType::CREATE_TABLE,
      "create table executor can not run this command: %d",
      static_cast<int>(stmt->type())
  );

  CreateTableStmt *create_table_stmt = static_cast<CreateTableStmt *>(stmt);
  if (!create_table_stmt->sub_select().empty()) {
    RC rc = execute_sub_select(stmt, session);
    if (rc != RC::SUCCESS) {
      LOG_WARN("Fail deal create-select");
    }
    return rc;
  }
  const int attribute_count = static_cast<int>(create_table_stmt->attr_infos().size());

  const char *table_name = create_table_stmt->table_name().c_str();
  RC rc = session->get_current_db()->create_table(table_name, attribute_count, create_table_stmt->attr_infos().data());

  return rc;
}