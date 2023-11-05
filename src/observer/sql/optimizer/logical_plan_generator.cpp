/* Copyright (c) 2023 OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by Wangyunlai on 2023/08/16.
//

#include "sql/optimizer/logical_plan_generator.h"

#include "sql/expr/expression.h"
#include "sql/expr/sub_query_expr.h"
#include "sql/operator/aggre_logical_operator.h"
#include "sql/operator/calc_logical_operator.h"
#include "sql/operator/delete_logical_operator.h"
#include "sql/operator/explain_logical_operator.h"
#include "sql/operator/insert_logical_operator.h"
#include "sql/operator/join_logical_operator.h"
#include "sql/operator/logical_operator.h"
#include "sql/operator/order_logical_operator.h"
#include "sql/operator/predicate_logical_operator.h"
#include "sql/operator/project_logical_operator.h"
#include "sql/operator/table_get_logical_operator.h"
#include "sql/operator/update_logical_operator.h"

#include "event/sql_debug.h"
#include "sql/stmt/calc_stmt.h"
#include "sql/stmt/delete_stmt.h"
#include "sql/stmt/explain_stmt.h"
#include "sql/stmt/filter_stmt.h"
#include "sql/stmt/insert_stmt.h"
#include "sql/stmt/select_stmt.h"
#include "sql/stmt/stmt.h"
#include "sql/stmt/update_stmt.h"
#include "storage/field/field.h"
#include <memory>
#include <utility>
using std::unique_ptr;

RC LogicalPlanGenerator::create(Stmt *stmt, unique_ptr<LogicalOperator> &logical_operator)
{
  RC rc = RC::SUCCESS;
  switch (stmt->type()) {
    case StmtType::CALC: {
      CalcStmt *calc_stmt = static_cast<CalcStmt *>(stmt);
      rc                  = create_plan(calc_stmt, logical_operator);
    } break;

    case StmtType::SELECT: {
      SelectStmt *select_stmt = static_cast<SelectStmt *>(stmt);
      rc                      = create_plan(select_stmt, logical_operator);
    } break;

    case StmtType::INSERT: {
      InsertStmt *insert_stmt = static_cast<InsertStmt *>(stmt);
      rc                      = create_plan(insert_stmt, logical_operator);
    } break;

    case StmtType::UPDATE: {
      UpdateStmt *update_stmt = static_cast<UpdateStmt *>(stmt);
      rc                      = create_plan(update_stmt, logical_operator);
    } break;

    case StmtType::DELETE: {
      DeleteStmt *delete_stmt = static_cast<DeleteStmt *>(stmt);
      rc                      = create_plan(delete_stmt, logical_operator);
    } break;

    case StmtType::EXPLAIN: {
      ExplainStmt *explain_stmt = static_cast<ExplainStmt *>(stmt);
      rc                        = create_plan(explain_stmt, logical_operator);
    } break;
    default: {
      rc = RC::UNIMPLENMENT;
    }
  }
  return rc;
}

RC LogicalPlanGenerator::create_plan(CalcStmt *calc_stmt, std::unique_ptr<LogicalOperator> &logical_operator)
{
  logical_operator.reset(new CalcLogicalOperator(std::move(calc_stmt->expressions())));
  return RC::SUCCESS;
}

// select stmt的逻辑计划生成器
RC LogicalPlanGenerator::create_plan(SelectStmt *select_stmt, unique_ptr<LogicalOperator> &logical_operator)
{
  // Project -> aggre -> (Orderby) -> (predicate) -> table_scan
  // 因为是从根节点开始执行， 所以执行的顺序是从table_scan开始
  unique_ptr<LogicalOperator> root_oper(nullptr);  // 根

  // 创建table_scan算子
  unique_ptr<LogicalOperator> table_oper(nullptr);
  const std::vector<Table *> &tables = select_stmt->tables();
  for (Table *table : tables) {
    // 从表中获取数据的算子
    unique_ptr<LogicalOperator> table_get_oper(new TableGetLogicalOperator(table, true /*readonly*/));
    if (table_oper == nullptr) {
      table_oper = std::move(table_get_oper);
    } else {
      JoinLogicalOperator *join_oper = new JoinLogicalOperator;
      join_oper->add_child(std::move(table_oper));
      join_oper->add_child(std::move(table_get_oper));
      table_oper = unique_ptr<LogicalOperator>(join_oper);
    }
  }
  root_oper = std::move(table_oper);

  // 创建filter算子
  unique_ptr<LogicalOperator> predicate_oper;
  RC                          rc = create_plan(select_stmt->filter_stmt(), predicate_oper);
  if (rc != RC::SUCCESS) {
    sql_debug("failed to create predicate logical plan. rc=%s", strrc(rc));
    return rc;
  }
  if (predicate_oper) {  // 将(root_oper)table_oper插入作为predicate_oper的子结点然后再更新root_oper
    predicate_oper->add_child(std::move(root_oper));
    root_oper = std::move(predicate_oper);
  }

  // 创建aggre算子
  std::vector<std::unique_ptr<AggreExpression>> aggre_exprs;
  for (auto expr : select_stmt->expressions()) {
    AggreExpression::get_aggre_expression(expr, aggre_exprs);
  }
  if (!aggre_exprs.empty()) {
    unique_ptr<LogicalOperator> aggre_oper(new AggreLogicalOperator(std::move(aggre_exprs)));
    aggre_oper->add_child(std::move(root_oper));
    root_oper = std::move(aggre_oper);
  }

  // 创建order算子
  unique_ptr<LogicalOperator> orderby_oper;
  rc = create_plan(select_stmt->order_by_stmt(), orderby_oper);
  if (rc != RC::SUCCESS) {
    sql_debug("failed to create order logical plan. rc=%s", strrc(rc));
    return rc;
  }
  if (orderby_oper) {
    orderby_oper->add_child(std::move(root_oper));
    root_oper = std::move(orderby_oper);
  }

  // 生成project算子
  unique_ptr<LogicalOperator> project_oper(new ProjectLogicalOperator(select_stmt->expressions()));
  project_oper->add_child(std::move(root_oper));

  logical_operator.swap(project_oper);
  return RC::SUCCESS;
}

RC LogicalPlanGenerator::create_plan(FilterStmt *filter_stmt, unique_ptr<LogicalOperator> &logical_operator)
{
  std::vector<unique_ptr<Expression>> expr_list;
  const std::vector<FilterUnit *>    &filter_units = filter_stmt->filter_units();
  for (const FilterUnit *filter_unit : filter_units) {
    auto &filter_unit_left  = filter_unit->left();
    auto &filter_unit_right = filter_unit->right();

    unique_ptr<Expression> left = nullptr;
    switch (filter_unit_left->type()) {
      case ExprType::FIELD: {
        auto tmp_expr = static_cast<const FieldExpr *>(filter_unit_left);
        left          = unique_ptr<Expression>(new FieldExpr(tmp_expr->field()));
      } break;
      case ExprType::VALUE: {
        auto tmp_expr = static_cast<const ValueExpr *>(filter_unit_left);
        left          = unique_ptr<Expression>(new ValueExpr(tmp_expr->get_value()));
      } break;
      case ExprType::VALUELIST: {
        auto tmp_expr = static_cast<const ValueListExpr *>(filter_unit_left);
        left          = unique_ptr<Expression>(new ValueListExpr(tmp_expr->value_list()));
      } break;
      case ExprType::SUBQUERY: {
        left = std::unique_ptr<Expression>(filter_unit_left);
      } break;
      default: {
        sql_debug("unimplement expr: %d", filter_unit_left->type());
      } break;
    }

    unique_ptr<Expression> right = nullptr;
    switch (filter_unit_right->type()) {
      case ExprType::FIELD: {
        auto tmp_expr = static_cast<const FieldExpr *>(filter_unit_right);
        right         = unique_ptr<Expression>(new FieldExpr(tmp_expr->field()));
      } break;
      case ExprType::VALUE: {
        auto tmp_expr = static_cast<const ValueExpr *>(filter_unit_right);
        right         = unique_ptr<Expression>(new ValueExpr(tmp_expr->get_value()));
      } break;
      case ExprType::VALUELIST: {
        auto tmp_expr = static_cast<const ValueListExpr *>(filter_unit_right);
        right         = unique_ptr<Expression>(new ValueListExpr(tmp_expr->value_list()));
      } break;
      case ExprType::SUBQUERY: {
        right = unique_ptr<Expression>(filter_unit_right);
      } break;
      default: {
        sql_debug("unimplement expr: %d", filter_unit_left->type());
      } break;
    }

    Expression *expr = nullptr;
    switch (filter_unit->comp()) {
      case EQUAL_TO:
      case LESS_EQUAL:
      case NOT_EQUAL:
      case LESS_THAN:
      case GREAT_EQUAL:
      case GREAT_THAN:
      case LIKE:
      case NOT_LIKE:
      case IS:
      case IS_NOT: {
        expr = new ComparisonExpr(filter_unit->comp(), std::move(left), std::move(right));
      } break;
      case IN:
      case NOT_IN: {
        expr = new InExpr(std::move(left), filter_unit->comp(), std::move(right));
      } break;
      case EXISTS:
      case NOT_EXISTS: {
        expr = new ExistsExpr(filter_unit->comp(), std::move(right));
      } break;
      case NO_OP: {
        sql_debug("no comp op where create plan");
      } break;
      default: {
        sql_debug("unimplement comp: %d", filter_unit->comp());
      } break;
    }
    expr_list.emplace_back(expr);
  }

  unique_ptr<PredicateLogicalOperator> predicate_oper;
  if (!expr_list.empty()) {
    ConjunctionExpr::Type       type = filter_stmt->has_or() ? ConjunctionExpr::Type::OR : ConjunctionExpr::Type::AND;
    unique_ptr<ConjunctionExpr> conjunction_expr(new ConjunctionExpr(type, expr_list));
    predicate_oper = unique_ptr<PredicateLogicalOperator>(new PredicateLogicalOperator(std::move(conjunction_expr)));
  }

  logical_operator = std::move(predicate_oper);
  return RC::SUCCESS;
}

RC LogicalPlanGenerator::create_plan(OrderByStmt *order_by_stmt, std::unique_ptr<LogicalOperator> &logical_operator)
{
  const std::vector<OrderByUnit *> order_units = order_by_stmt->order_units();
  if (order_units.empty()) {
    LOG_INFO("No OrderByUnits");
    logical_operator = nullptr;
    return RC::SUCCESS;
  }

  unique_ptr<OrderLogicalOperator> order_oper = std::make_unique<OrderLogicalOperator>(order_units);

  logical_operator = std::move(order_oper);
  return RC::SUCCESS;
}

RC LogicalPlanGenerator::create_plan(InsertStmt *insert_stmt, unique_ptr<LogicalOperator> &logical_operator)
{
  Table      *table       = insert_stmt->table();
  const auto &values_list = insert_stmt->values_list();

  InsertLogicalOperator *insert_operator = new InsertLogicalOperator(table, values_list);
  logical_operator.reset(insert_operator);
  return RC::SUCCESS;
}

RC LogicalPlanGenerator::create_plan(UpdateStmt *update_stmt, unique_ptr<LogicalOperator> &logical_operator)
{
  // 初始化
  Table      *table       = update_stmt->table();
  FilterStmt *filter_stmt = update_stmt->filter_stmt();
  RC          rc          = RC::SUCCESS;

  // 获取所有的字段
  std::vector<Field> fields;
  for (int i = table->table_meta().sys_field_num(); i < table->table_meta().field_num(); i++) {
    const FieldMeta *field_meta = table->table_meta().field(i);
    fields.push_back(Field(table, field_meta));
  }

  // 获取扫表的逻辑算子
  unique_ptr<LogicalOperator> table_get_oper(new TableGetLogicalOperator(table, false /*readonly*/));

  // 获取谓词的逻辑算子
  unique_ptr<LogicalOperator> predicate_oper;
  rc = create_plan(filter_stmt, predicate_oper);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  // 设置update的逻辑算子
  unique_ptr<LogicalOperator> update_oper(
      new UpdateLogicalOperator(table, update_stmt->field_metas(), update_stmt->expr_list())
  );

  // 设置子算子
  if (predicate_oper) {
    predicate_oper->add_child(std::move(table_get_oper));
    update_oper->add_child(std::move(predicate_oper));
  } else {
    update_oper->add_child(std::move(table_get_oper));
  }

  logical_operator = std::move(update_oper);
  return rc;
}

RC LogicalPlanGenerator::create_plan(DeleteStmt *delete_stmt, unique_ptr<LogicalOperator> &logical_operator)
{
  Table             *table       = delete_stmt->table();
  FilterStmt        *filter_stmt = delete_stmt->filter_stmt();
  std::vector<Field> fields;
  for (int i = table->table_meta().sys_field_num(); i < table->table_meta().field_num(); i++) {
    const FieldMeta *field_meta = table->table_meta().field(i);
    fields.push_back(Field(table, field_meta));
  }
  unique_ptr<LogicalOperator> table_get_oper(new TableGetLogicalOperator(table, false /*readonly*/));

  unique_ptr<LogicalOperator> predicate_oper;
  RC                          rc = create_plan(filter_stmt, predicate_oper);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  unique_ptr<LogicalOperator> delete_oper(new DeleteLogicalOperator(table));

  if (predicate_oper) {
    predicate_oper->add_child(std::move(table_get_oper));
    delete_oper->add_child(std::move(predicate_oper));
  } else {
    delete_oper->add_child(std::move(table_get_oper));
  }

  logical_operator = std::move(delete_oper);
  return rc;
}

RC LogicalPlanGenerator::create_plan(ExplainStmt *explain_stmt, unique_ptr<LogicalOperator> &logical_operator)
{
  Stmt                       *child_stmt = explain_stmt->child();
  unique_ptr<LogicalOperator> child_oper;
  RC                          rc = create(child_stmt, child_oper);
  if (rc != RC::SUCCESS) {
    sql_debug("failed to create explain's child operator. rc=%s", strrc(rc));
    return rc;
  }

  logical_operator = unique_ptr<LogicalOperator>(new ExplainLogicalOperator);
  logical_operator->add_child(std::move(child_oper));
  return rc;
}
