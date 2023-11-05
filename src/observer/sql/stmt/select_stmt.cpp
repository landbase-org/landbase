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
#include "event/sql_debug.h"
#include "sql/expr/expression.h"
#include "sql/parser/parse_defs.h"
#include "sql/stmt/filter_stmt.h"
#include "sql/stmt/order_by_stmt.h"
#include "storage/db/db.h"
#include "storage/table/table.h"
#include <algorithm>
#include <cstddef>
#include <vector>

RC handle_where_alias(std::vector<ConditionSqlNode> &conditions, std::vector<AttrSqlNode> &table_names);

RC handle_sub_query_alias(ParseSubQueryExpr *expr, std::vector<AttrSqlNode> &parent_table_names)
{
  auto &sub_query   = expr->sub_query();
  auto  table_names = sub_query->relations;
  auto &fields      = sub_query->attributes;
  auto &aggres      = sub_query->aggregations;

  // select * from csq_1 t, csq_2 t;
  auto iter = std::unique(table_names.begin(), table_names.end(), [](const AttrSqlNode &a, const AttrSqlNode &b) {
    if (a.table_alias != "" && b.table_alias != "") {
      return a.table_alias == b.table_alias;
    }
    return false;
  });

  if (iter != table_names.end()) {
    sql_debug("invalid argument. table alias cannot be repeated");
    return RC::INVALID_ARGUMENT;
  }

  // 检查非法情况：select * as alias from table_name_1 t1;
  for (auto &field : fields) {
    if (field.attribute_name == "*" && field.field_alias != "") {
      sql_debug("invalid argument. field alias cannot be used with *");
      return RC::INVALID_ARGUMENT;
    }
  }

  // 处理字段
  for (auto &node : table_names) {
    if (node.table_alias != "") {
      for (auto &field : fields) {
        if (field.relation_name == node.table_alias) {
          field.relation_name = node.relation_name;
          field.table_alias   = node.table_alias;
        }
      }
      for (auto &aggre : aggres) {
        if (aggre.attribute_name.table_alias == node.table_alias) {
          aggre.attribute_name.relation_name = node.relation_name;
          aggre.attribute_name.table_alias   = node.table_alias;
        }
      }
    }
  }
  // 合并上级表名
  parent_table_names.insert(parent_table_names.end(), table_names.begin(), table_names.end());
  // 只处理where中的子查询
  return handle_where_alias(sub_query->conditions, parent_table_names);
}

RC handle_where_alias(std::vector<ConditionSqlNode> &conditions, std::vector<AttrSqlNode> &table_names)
{
  RC rc = RC::SUCCESS;
  for (auto &cond : conditions) {
    switch (cond.left->expr_type()) {
      case ParseExprType::FIELD: {
        auto left_expr = static_cast<ParseFieldExpr *>(cond.left);
        if (left_expr->table_name() != "") {
          for (auto &node : table_names) {
            if (node.table_alias != "") {
              if (left_expr->table_name() == node.table_alias) {
                left_expr->set_table_name(node.relation_name);
                break;
              }
            }
          }
        }
      } break;
      case ParseExprType::SUBQUERY: {
        auto left_expr = static_cast<ParseSubQueryExpr *>(cond.left);
        auto tmp       = table_names;
        rc             = handle_sub_query_alias(left_expr, tmp);
        if (rc != RC::SUCCESS) {
          sql_debug("handle sub query alias err");
          return rc;
        }
      } break;
    }
    switch (cond.right->expr_type()) {
      case ParseExprType::FIELD: {
        auto right_expr = static_cast<ParseFieldExpr *>(cond.right);
        if (right_expr->table_name() != "") {
          for (auto &node : table_names) {
            if (node.table_alias != "") {
              if (right_expr->table_name() == node.table_alias) {
                right_expr->set_table_name(node.relation_name);
                break;
              }
            }
          }
        }
      } break;
      case ParseExprType::SUBQUERY: {
        auto right_expr = static_cast<ParseSubQueryExpr *>(cond.right);
        auto tmp        = table_names;
        rc              = handle_sub_query_alias(right_expr, tmp);
        if (rc != RC::SUCCESS) {
          sql_debug("handle sub query alias err");
          return rc;
        }
      } break;
    }
  }
  return rc;
}

RC handle_alias(SelectSqlNode &select_sql)
{
  auto  table_names = select_sql.relations;
  auto &fields      = select_sql.attributes;
  auto &aggres      = select_sql.aggregations;

  // select * from csq_1 t, csq_2 t;
  auto iter = std::unique(table_names.begin(), table_names.end(), [](const AttrSqlNode &a, const AttrSqlNode &b) {
    if (a.table_alias != "" && b.table_alias != "") {
      return a.table_alias == b.table_alias;
    }
    return false;
  });

  if (iter != table_names.end()) {
    sql_debug("invalid argument. table alias cannot be repeated");
    return RC::INVALID_ARGUMENT;
  }

  // 检查非法情况：select * as alias from table_name_1 t1;
  for (auto &field : fields) {
    if (field.attribute_name == "*" && field.field_alias != "") {
      sql_debug("invalid argument. field alias cannot be used with *");
      return RC::INVALID_ARGUMENT;
    }
  }

  // 处理字段
  for (auto &node : table_names) {
    if (node.table_alias != "") {
      for (auto &field : fields) {
        if (field.relation_name == node.table_alias) {
          field.relation_name = node.relation_name;
          field.table_alias   = node.table_alias;
        }
      }
      for (auto &aggre : aggres) {
        if (aggre.attribute_name.table_alias == node.table_alias) {
          aggre.attribute_name.relation_name = node.relation_name;
          aggre.attribute_name.table_alias   = node.table_alias;
        }
      }
    }
  }
  // 只处理where中的子查询
  return handle_where_alias(select_sql.conditions, table_names);
}

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
  // 如果只是普通的查询列表数据
  RC rc = RC::SUCCESS;
  if (!sql_node.attributes.empty()) {
    return FieldExpr::create(sql_node, table_map, tables, res_expressions, db);
  }

  // aggregation的情况

  for (auto &expr_node : sql_node.aggregations) {
    Expression *tmp_expression;
    rc = AggreExpression::create(expr_node, table_map, tables, tmp_expression, db);
    if (rc != RC::SUCCESS) {
      sql_debug("create expression err");
      return rc;
    }
    res_expressions.push_back(tmp_expression);
  }
  return rc;
}

RC SelectStmt::create(Db *db, SelectSqlNode &select_sql, Stmt *&stmt)
{
  if (nullptr == db) {
    sql_debug("invalid argument. db is null");
    return RC::INVALID_ARGUMENT;
  }
  RC rc = RC::SUCCESS;

  // parse the tables;
  std::vector<Table *>                     tables;
  std::unordered_map<std::string, Table *> table_map;
  std::vector<OrderSqlNode>                orderbys = select_sql.orders;
  for (size_t i = 0; i < select_sql.relations.size(); i++) {
    const char *table_name = select_sql.relations[i].relation_name.c_str();
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

  // 处理别名
  rc = handle_alias(select_sql);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  // get the expression 聚合函数, 和查询的列在这里转化
  std::vector<Expression *> expressions;
  rc = get_expressions(select_sql, expressions, table_map, tables, db);
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

  // 复杂子查询，将condition中的父表加入到table_map中
  for (auto &cond : conditions) {
    if (cond.left->expr_type() == ParseExprType::FIELD) {
      auto left_expr = static_cast<ParseFieldExpr *>(cond.left);
      if (left_expr->table_name() != "") {
        auto table_name = left_expr->table_name();
        auto table      = db->find_table(table_name.c_str());
        if (table == nullptr) {
          sql_debug("no such table. db=%s, table_name=%s", db->name(), table_name.c_str());
          return RC::SCHEMA_TABLE_NOT_EXIST;
        }
        table_map.insert(std::pair<std::string, Table *>(table_name, table));
      }
    }
    if (cond.right->expr_type() == ParseExprType::FIELD) {
      auto right_expr = static_cast<ParseFieldExpr *>(cond.right);
      if (right_expr->table_name() != "") {
        auto table_name = right_expr->table_name();
        auto table      = db->find_table(table_name.c_str());
        if (table == nullptr) {
          sql_debug("no such table. db=%s, table_name=%s", db->name(), table_name.c_str());
          return RC::SCHEMA_TABLE_NOT_EXIST;
        }
        table_map.insert(std::pair<std::string, Table *>(table_name, table));
      }
    }
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
