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
// Created by Wangyunlai on 2022/6/6.
//

#include "sql/stmt/select_stmt.h"
#include "common/log/log.h"
#include "event/sql_debug.h"
#include "sql/expr/expression.h"
#include "sql/parser/parse_defs.h"
#include "sql/stmt/filter_stmt.h"
#include "sql/stmt/order_by_stmt.h"
#include "storage/db/db.h"
#include "storage/field/field.h"
#include "storage/table/table.h"
#include <algorithm>
#include <cstddef>
#include <vector>

SelectStmt::~SelectStmt()
{
  if (nullptr != filter_stmt_) {
    delete filter_stmt_;
    filter_stmt_ = nullptr;
  }
  if (nullptr != order_stmt_) {
    delete order_stmt_;
    order_stmt_ = nullptr;
  }
}

/**
 * @description: 解析要查询到字段, 转换到Field中去
 * @return {RC} 查询的状况
 */
static RC get_expressions(
    const SelectSqlNode &sql_node, std::vector<Expression *> &res_expressions,
    const std::unordered_map<std::string, Table *> &table_map, const std::vector<Table *> &tables, Db *db
)
{
  RC                               rc = RC::SUCCESS;
  std::vector<ExprNode>            expr_nodes;
  std::vector<SelectorNode> const &selector_nodes = sql_node.selectors;

  // 因为*的原因，直接处理所有的RelAttr
  std::vector<RelAttrSqlNode> explicit_attrs;
  for (auto const &node : sql_node.selectors) {
    if (node.nodetype == RELATTR) {
      explicit_attrs.emplace_back(node.rel_attr);
    }
  }
  if (!explicit_attrs.empty()) {
    rc = FieldExpr::create(explicit_attrs, table_map, tables, res_expressions, db);
    if (rc != RC::SUCCESS){
      sql_debug("Err at attrs->exprs");
      return rc;
    }
  }

  // 处理除了RelAttr的其他Selectors
  for (auto &node : selector_nodes) {
    switch (node.nodetype) {
      case RELATTR: {
        // 已经提前处理，此处什么也不做
      } break;
      case AGGRE: {
        expr_nodes.emplace_back(ExprNode(node.aggretion));
      } break;
      case FUNCTION: {
        if (node.function.left == nullptr && node.function.rel_attr.attribute_name.empty()) {
          LOG_WARN("Error at function node");
          return RC::FAILURE;
        }
        expr_nodes.emplace_back(ExprNode(node.function));
      } break;
      case EXPRESSION: {
        return RC::UNIMPLENMENT;
      } break;
    }
  }

  for (auto &expr_node : expr_nodes) {
    Expression *tmp_expression;
    rc = Expression::create(expr_node, table_map, tables, tmp_expression, db);
    if (rc != RC::SUCCESS) {
      LOG_WARN("create expression err");
      return rc;
    }
    res_expressions.push_back(tmp_expression);
  }
  return rc;
}

RC SelectStmt::create(Db *db, const SelectSqlNode &select_sql, Stmt *&stmt)
{
  if (nullptr == db) {
    LOG_WARN("invalid argument. db is null");
    return RC::INVALID_ARGUMENT;
  }

  // parse the tables;
  std::vector<Table *>                     tables;
  std::unordered_map<std::string, Table *> table_map;
  std::vector<SelectorNode>                selectors  = select_sql.selectors;
  std::vector<ConditionSqlNode>            conditions = select_sql.conditions;
  std::vector<OrderSqlNode>                orderbys   = select_sql.orders;
  // 处理显式给出的表
  for (size_t i = 0; i < select_sql.relations.size(); i++) {
    const char *table_name = select_sql.relations[i].c_str();
    if (nullptr == table_name) {
      LOG_WARN("invalid argument. relation name is null. index=%d", i);
      return RC::INVALID_ARGUMENT;
    }

    Table *table = db->find_table(table_name);
    if (nullptr == table) {
      LOG_WARN("no such table. db=%s, table_name=%s", db->name(), table_name);
      return RC::SCHEMA_TABLE_NOT_EXIST;
    }

    tables.push_back(table);
    table_map.insert(std::pair<std::string, Table *>(table_name, table));
  }

  // 处理联结需要的表
  for (size_t i = 0; i < select_sql.joinctions.size(); i++) {
    const char *table_name = select_sql.joinctions[i].join_relation.c_str();
    if (nullptr == table_name) {
      LOG_WARN("invalid argument. join relation name is null. index=%d", i);
      return RC::INVALID_ARGUMENT;
    }

    Table *table = db->find_table(table_name);
    if (nullptr == table) {
      LOG_WARN("no such table. db=%s, table_name=%s", db->name(), table_name);
      return RC::SCHEMA_TABLE_NOT_EXIST;
    }

    tables.push_back(table);
    table_map.insert(std::pair<std::string, Table *>(table_name, table));
  }

  // get the expression 聚合函数, 三个函数、和查询的列在这里转化
  // 处理Selectors：聚合、列、函数、（表达式）
  std::vector<Expression *> expressions;
  auto                      rc = get_expressions(select_sql, expressions, table_map, tables, db);
  if (rc != RC::SUCCESS) {
    LOG_WARN("cannot parse express");
    return rc;
  }

  // ---------
  Table *default_table = nullptr;
  if (tables.size() == 1) {
    default_table = tables[0];
  }

  // 处理联结需要的条件
  for (size_t i = 0; i < select_sql.joinctions.size(); i++) {
    std::vector<ConditionSqlNode> const &tmp_vec_condi = select_sql.joinctions[i].join_conditions;
    for (auto j : tmp_vec_condi)
      conditions.emplace_back(j);
  }

  // 创建where条件的STMT
  // 有关 where 条件的处理, 过滤出需要的数据
  FilterStmt *filter_stmt = nullptr;
  rc                      = FilterStmt::create(
      db, default_table, &table_map, conditions.data(), static_cast<int>(conditions.size()), filter_stmt
  );
  if (rc != RC::SUCCESS) {
    LOG_WARN("cannot construct filter stmt");
    return rc;
  }

  // 创建ORDER_BY的STMT
  OrderByStmt *orderby_stmt = nullptr;
  rc                        = OrderByStmt::create(
      db, default_table, &table_map, orderbys.data(), static_cast<int>(orderbys.size()), orderby_stmt
  );
  if (rc != RC::SUCCESS) {
    LOG_WARN("cannot construct orderby stmt");
    return rc;
  }

  // everything alright
  SelectStmt *select_stmt = new SelectStmt();
  // TODO add expression copy
  select_stmt->tables_.swap(tables);
  select_stmt->expressions_.swap(expressions);
  select_stmt->filter_stmt_ = filter_stmt;
  select_stmt->order_stmt_  = orderby_stmt;
  stmt                      = select_stmt;
  return RC::SUCCESS;
}
