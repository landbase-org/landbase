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
// Created by WangYunlai on 2021/6/9.
//

#include "sql/operator/table_scan_physical_operator.h"
#include "event/sql_debug.h"
#include "sql/expr/sub_query_expr.h"
#include "sql/expr/tuple.h"
#include "storage/table/table.h"

using namespace std;

RC TableScanPhysicalOperator::open(Trx *trx)
{
  RC rc = table_->get_record_scanner(record_scanner_, trx, readonly_);
  if (rc == RC::SUCCESS) {
    oper_meta = make_pair(table_, table_->table_meta().field_metas());
  }
  trx_ = trx;

  // 理论上此时只有 COMPARISON expr
  for (auto &expr : predicates_) {
    switch (expr->type()) {
      case ExprType::COMPARISON: {
        auto  comp_expr  = static_cast<ComparisonExpr *>(expr.get());
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
        auto  in_expr    = static_cast<InExpr *>(expr.get());
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
        auto  exists_expr    = static_cast<ExistsExpr *>(expr.get());
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
        sql_debug("unsupported expression type: %d", expr->type());
      } break;
    }
  }

  return rc;
}

RC TableScanPhysicalOperator::next()
{
  if (!record_scanner_.has_next()) {
    return RC::RECORD_EOF;
  }

  RC   rc            = RC::SUCCESS;
  bool filter_result = false;
  while (record_scanner_.has_next()) {
    rc = record_scanner_.next(current_record_);
    if (rc != RC::SUCCESS) {
      return rc;
    }

    inspector_.set_record(&current_record_);
    inspector_.set_schema(oper_meta.first, oper_meta.second);
    rc = filter(inspector_, filter_result);
    if (rc != RC::SUCCESS) {
      return rc;
    }

    if (filter_result) {
      // sql_debug("get a tuple: %s", tuple_->to_string().c_str());
      // 必须new出来，因为Tuple共享了 TupleSpecCell
      RowTuple *tuple_ = new RowTuple();
      tuple_->set_record(&current_record_);
      tuple_->set_schema(oper_meta.first, oper_meta.second);
      tuples_.emplace_back(tuple_);
      break;
    } else {
      // sql_debug("a tuple is filtered: %s", tuple_->to_string().c_str());
      rc = RC::RECORD_EOF;
    }
  }
  return rc;
}

RC TableScanPhysicalOperator::close() { return record_scanner_.close_scan(); }

Tuple *TableScanPhysicalOperator::current_tuple()
{
  // tuples_.back()->set_record(&current_record_);
  return tuples_.back();
}

string TableScanPhysicalOperator::param() const { return table_->name(); }

void TableScanPhysicalOperator::set_predicates(vector<unique_ptr<Expression>> &&exprs)
{
  predicates_ = std::move(exprs);
}

RC TableScanPhysicalOperator::filter(RowTuple &tuple, bool &result)
{
  RC    rc = RC::SUCCESS;
  Value value;
  for (unique_ptr<Expression> &expr : predicates_) {
    rc = expr->get_value(tuple, value);
    if (rc != RC::SUCCESS) {
      return rc;
    }

    bool tmp_result = value.get_boolean();
    if (!tmp_result) {
      result = false;
      return rc;
    }
  }

  result = true;
  return rc;
}
