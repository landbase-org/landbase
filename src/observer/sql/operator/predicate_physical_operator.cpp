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
#include "event/sql_debug.h"
#include "sql/expr/do_expr.h"
#include "sql/expr/sub_query_expr.h"

PredicatePhysicalOperator::PredicatePhysicalOperator(std::unique_ptr<Expression> expr) : expression_(std::move(expr))
{
  ASSERT(expression_->value_type() == BOOLEANS, "predicate's expression should be BOOLEAN type");
}

RC PredicatePhysicalOperator::open(Trx *trx)
{
  if (children_.size() != 1) {
    sql_debug("predicate operator must has one child");
    return RC::INTERNAL;
  }
  trx_  = trx;
  RC rc = children_[0]->open(trx);
  if (rc != RC::SUCCESS) {
    sql_debug("[open] failed to open child operator");
  }

  // 尝试执行子查询，如果不需要父tuple就能执行成功
  rc = do_expr(trx_, expression_.get(), nullptr);

  if (rc != RC::SUCCESS) {
    sql_debug("[open] failed to do expression");
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
      sql_debug("failed to get tuple from operator");
      break;
    }

    if (nullptr != parent_tuple_) {
      CompoundTuple *tmp = new CompoundTuple(parent_tuple_, tuple);
      tuple              = tmp;
    }

    // 执行子查询
    rc = do_expr(trx_, expression_.get(), tuple);
    if (rc != RC::SUCCESS) {
      sql_debug("[open] failed to do expression");
      return rc;
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
