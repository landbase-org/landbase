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
#include "sql/stmt/groupby_stml.h"
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
 * @description: 解析要查询到字段, 如果Express中全是FieldExpr那么就是普通的查询
 * @description:                如果Express中全是AggreExpr那么就是普通的聚合查询
 * @description:                否则就是聚合查询
 * @return {RC} 查询的状况
 */
static RC get_expressions(
    const SelectSqlNode &sql_node, std::vector<Expression *> &res_expressions,
    const std::unordered_map<std::string, Table *> &table_map, const std::vector<Table *> &tables, Db *db
)
{
  RC rc = RC::SUCCESS;
  // 没有聚合函数， 直接返回普通的类型
  int aggre_size = 0;
  for (auto node : sql_node.rel_attr_aggres) {
    if (node.is_aggre()) {
      aggre_size++;
    }
  }
  if (aggre_size != 0 && aggre_size != sql_node.rel_attr_aggres.size() && sql_node.groupbys.size() == 0) {
    return RC::FAILURE;
  }
  if (aggre_size == 0) {
    std::vector<RelAttrSqlNode> rel_attrs;
    for (auto node : sql_node.rel_attr_aggres) {
      rel_attrs.push_back(node);
    }
    return FieldExpr::create(rel_attrs, table_map, tables, res_expressions, db);
  }

  /**************************
   *    聚合函数， GROUP BY   *
   **************************/
  // 解析聚合函数
  for (auto &expr_node : sql_node.rel_attr_aggres) {
    Expression *tmp_expression;
    if (expr_node.is_aggre()) {
      rc = AggreExpression::create(expr_node, table_map, tables, tmp_expression, db);
    } else {
      rc = FieldExpr::create(expr_node, table_map, tables, tmp_expression);
    }

    if (rc != RC::SUCCESS) {
      sql_debug("create aggregation expression err");
      return rc;
    }
    res_expressions.push_back(tmp_expression);
  }
  return rc;
}

RC SelectStmt::create(Db *db, const SelectSqlNode &select_sql, Stmt *&stmt)
{
  if (nullptr == db) {
    sql_debug("invalid argument. db is null");
    return RC::INVALID_ARGUMENT;
  }

  // parse the tables;
  std::vector<Table *>                     tables;
  std::unordered_map<std::string, Table *> table_map;
  const std::vector<OrderSqlNode>         &orderbys = select_sql.orders;
  const std::vector<GroupBySqlNode>       &groupbys = select_sql.groupbys;
  std::vector<OrderSqlNode>                groupbys_order;  // 转化为OrderSqlNode节点的
  std::for_each(groupbys.begin(), groupbys.end(), [&groupbys_order](const GroupBySqlNode &node) {
    groupbys_order.push_back({static_cast<RelAttrSqlNode>(node)});
  });

  for (size_t i = 0; i < select_sql.relations.size(); i++) {
    const char *table_name = select_sql.relations[i].c_str();
    if (nullptr == table_name) {
      sql_debug("invalid argument. relation name is null. index=%d", i);
      return RC::INVALID_ARGUMENT;
    }

    Table *table = db->find_table(table_name);
    if (nullptr == table) {
      sql_debug("no such table. db=%s, table_name=%s", db->name(), table_name);
      return RC::SCHEMA_TABLE_NOT_EXIST;
    }

    tables.push_back(table);
    table_map.insert(std::pair<std::string, Table *>(table_name, table));
  }

  // add the join's table to the tables
  for (size_t i = 0; i < select_sql.joinctions.size(); i++) {
    const char *table_name = select_sql.joinctions[i].join_relation.c_str();
    if (nullptr == table_name) {
      sql_debug("invalid argument. join relation name is null. index=%d", i);
      return RC::INVALID_ARGUMENT;
    }

    Table *table = db->find_table(table_name);
    if (nullptr == table) {
      sql_debug("no such table. db=%s, table_name=%s", db->name(), table_name);
      return RC::SCHEMA_TABLE_NOT_EXIST;
    }

    tables.push_back(table);
    table_map.insert(std::pair<std::string, Table *>(table_name, table));
  }

  // get the expression 聚合函数, 和查询的列在这里转化
  std::vector<Expression *> expressions;
  auto                      rc = get_expressions(select_sql, expressions, table_map, tables, db);
  if (rc != RC::SUCCESS) {
    sql_debug("cannot parse express");
    return rc;
  }

  // ---------
  Table *default_table = nullptr;
  if (tables.size() == 1) {
    default_table = tables[0];
  }

  // add up the join's conditions
  std::vector<ConditionSqlNode> conditions = select_sql.conditions;
  for (size_t i = 0; i < select_sql.joinctions.size(); i++) {
    std::vector<ConditionSqlNode> const &tmp_vec_condi = select_sql.joinctions[i].join_conditions;
    for (auto j : tmp_vec_condi)
      conditions.emplace_back(j);
  }

  // create filter statement in `where` statement
  // 有关 where 条件的处理, 过滤出需要的数据
  FilterStmt *filter_stmt = nullptr;
  rc                      = FilterStmt::create(
      db, default_table, &table_map, conditions.data(), static_cast<int>(conditions.size()), filter_stmt
  );
  if (rc != RC::SUCCESS) {
    sql_debug("cannot construct filter stmt");
    return rc;
  }

  // create orderby stmt for ORDER BY
  // 创建ORDER_BY的STMT
  OrderByStmt *orderby_stmt = nullptr;
  rc                        = OrderByStmt::create(
      db, default_table, &table_map, orderbys.data(), static_cast<int>(orderbys.size()), orderby_stmt
  );
  if (rc != RC::SUCCESS) {
    sql_debug("cannot construct orderby stmt");
    return rc;
  }

  // 创建GROUP BY, 因为需要分组， 所以在他之前加一个order算子， 这样获取结果的时候就是连续的
  OrderByStmt *orderby_stmt_before_group = nullptr;
  GroupByStmt *groupby_stmt              = nullptr;
  if (!groupbys.empty()) {
    rc = OrderByStmt::create(
        db,
        default_table,
        &table_map,
        groupbys_order.data(),
        static_cast<int>(groupbys_order.size()),
        orderby_stmt_before_group
    );
    rc = GroupByStmt::create(db, table_map, tables, groupbys, groupby_stmt);
    if (RC::SUCCESS == rc) {
      LOG_INFO("create group by success");
      LOG_INFO("create group by success");
    }
  }

  // 创建Having
  HavingStmt *having_stmt = nullptr;
  if (!select_sql.havings.empty()) {
    rc = HavingStmt::create(
        db, default_table, &table_map, select_sql.havings.data(), select_sql.havings.size(), having_stmt
    );
    LOG_INFO("create having success");
  }

  // everything alright
  SelectStmt *select_stmt = new SelectStmt();
  // TODO add expression copy
  select_stmt->tables_.swap(tables);
  select_stmt->expressions_.swap(expressions);
  select_stmt->filter_stmt_               = filter_stmt;
  select_stmt->order_stmt_                = orderby_stmt;
  select_stmt->orderby_stmt_before_group_ = orderby_stmt_before_group;
  select_stmt->groupby_stmt_              = groupby_stmt;
  select_stmt->having_stmt_               = having_stmt;
  stmt                                    = select_stmt;
  return RC::SUCCESS;
}
