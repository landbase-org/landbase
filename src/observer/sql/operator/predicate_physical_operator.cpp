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
// Created by WangYunlai on 2022/6/27.
//

#include "sql/operator/predicate_physical_operator.h"
#include "common/log/log.h"
#include "sql/expr/sub_query_expr.h"
#include "sql/stmt/filter_stmt.h"
#include "storage/field/field.h"
#include "storage/record/record.h"

PredicatePhysicalOperator::PredicatePhysicalOperator(std::unique_ptr<Expression> expr) : expression_(std::move(expr))
{
  ASSERT(expression_->value_type() == BOOLEANS, "predicate's expression should be BOOLEAN type");
}

RC PredicatePhysicalOperator::open(Trx *trx)
{
  if (children_.size() != 1) {
    LOG_WARN("predicate operator must has one child");
    return RC::INTERNAL;
  }

  RC rc = children_[0]->open(trx);

  switch (expression_->type()) {
    case ExprType::CONJUNCTION: {
      // TODO: 假设CONJUNCTION的children内没有CONJUNCTION
      auto  conjunction_expr = static_cast<ConjunctionExpr *>(expression_.get());
      auto &children         = conjunction_expr->children();
      for (auto &child : children) {
        if (child->type() == ExprType::SUBQUERY) {
          auto subquery_expr = static_cast<SubQueryExpr *>(child.get());
          rc                 = subquery_expr->executor(trx);
          if (rc != RC::SUCCESS) {
            sql_debug("failed to execute subquery expression");
            return rc;
          }
        }
      }
    } break;
    case ExprType::COMPARISON: {
      auto  comp_expr  = static_cast<ComparisonExpr *>(expression_.get());
      auto &left_expr  = comp_expr->left();
      auto &right_expr = comp_expr->right();
      if (left_expr->type() == ExprType::SUBQUERY) {
        auto subquery_expr = static_cast<SubQueryExpr *>(left_expr.get());
        rc                 = subquery_expr->executor(trx);
        if (rc != RC::SUCCESS) {
          sql_debug("failed to execute subquery expression");
          return rc;
        }
      }
      if (right_expr->type() == ExprType::SUBQUERY) {
        auto subquery_expr = static_cast<SubQueryExpr *>(right_expr.get());
        rc                 = subquery_expr->executor(trx);
        if (rc != RC::SUCCESS) {
          sql_debug("failed to execute subquery expression");
          return rc;
        }
      }
    } break;
    case ExprType::IN: {
      auto  in_expr    = static_cast<InExpr *>(expression_.get());
      auto &left_expr  = in_expr->left();
      auto &right_expr = in_expr->right();
      if (left_expr->type() == ExprType::SUBQUERY) {
        auto subquery_expr = static_cast<SubQueryExpr *>(left_expr.get());
        rc                 = subquery_expr->executor(trx);
        if (rc != RC::SUCCESS) {
          sql_debug("failed to execute subquery expression");
          return rc;
        }
      }
      if (right_expr->type() == ExprType::SUBQUERY) {
        auto subquery_expr = static_cast<SubQueryExpr *>(right_expr.get());
        rc                 = subquery_expr->executor(trx);
        if (rc != RC::SUCCESS) {
          sql_debug("failed to execute subquery expression");
          return rc;
        }
      }
    } break;
    case ExprType::EXISTS: {
      auto  exists_expr    = static_cast<ExistsExpr *>(expression_.get());
      auto &sub_query_expr = exists_expr->right();
      if (sub_query_expr->type() == ExprType::SUBQUERY) {
        auto subquery_expr = static_cast<SubQueryExpr *>(sub_query_expr.get());
        rc                 = subquery_expr->executor(trx);
        if (rc != RC::SUCCESS) {
          sql_debug("failed to execute subquery expression");
          return rc;
        }
      }
    } break;
    default: {
      sql_debug("uninplemented ExprType");
    } break;
  }
  return rc;
}

RC PredicatePhysicalOperator::next()
{
  RC                rc   = RC::SUCCESS;
  PhysicalOperator *oper = children_.front().get();

  while (RC::SUCCESS == (rc = oper->next())) {
    Tuple *tuple = oper->current_tuple();

    if (nullptr == tuple) {
      rc = RC::INTERNAL;
      LOG_WARN("failed to get tuple from operator");
      break;
    }

    Value value;
    rc = expression_->get_value(*tuple, value);  // 根据expression判断 当前值是否符合where后面的条件, 如果不满足, 则继续
    if (rc != RC::SUCCESS) {
      return rc;
    }

    if (value.get_boolean()) {
      return rc;
    }
  }
  return rc;
}

RC PredicatePhysicalOperator::close()
{
  children_[0]->close();
  return RC::SUCCESS;
}

Tuple *PredicatePhysicalOperator::current_tuple() { return children_[0]->current_tuple(); }
