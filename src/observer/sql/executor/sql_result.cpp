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
// Created by WangYunlai on 2022/11/18.
//

#include "sql/executor/sql_result.h"
#include "common/log/log.h"
#include "common/rc.h"
#include "session/session.h"
#include "sql/expr/tuple.h"
#include "sql/parser/parse_defs.h"
#include "storage/trx/trx.h"

SqlResult::SqlResult(Session *session) : session_(session) {}

void SqlResult::set_tuple_schema(const TupleSchema &schema) { tuple_schema_ = schema; }

RC SqlResult::open()
{
  if (nullptr == operator_) {
    return RC::INVALID_ARGUMENT;
  }

  Trx *trx = session_->current_trx();
  trx->start_if_need();
  return operator_->open(trx);
}

RC SqlResult::close()
{
  if (nullptr == operator_) {
    return RC::INVALID_ARGUMENT;
  }
  RC rc = operator_->close();
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to close operator. rc=%s", strrc(rc));
  }

  operator_.reset();

  if (session_ && !session_->is_trx_multi_operation_mode()) {
    if (rc == RC::SUCCESS) {
      rc = session_->current_trx()->commit();
    } else {
      RC rc2 = session_->current_trx()->rollback();
      if (rc2 != RC::SUCCESS) {
        LOG_PANIC("rollback failed. rc=%s", strrc(rc2));
      }
    }
  }
  return rc;
}

RC SqlResult::next_tuple(Tuple *&tuple)
{
  RC rc = operator_->next();

  // TODO TODOH 这里之后写 COUNT(*) 为0 的情况
  // if (auto x = dynamic_cast<ProjectTuple *>(tuple)) {                       // 判断COUNT(*)等于0的情况
  //   if (x->is_aggregation() && aggre_calcs.empty() && rc != RC::SUCCESS) {  // 当前为聚合查询的第一次,
  //   且表中的数据为空
  //   }
  // }

  if (rc != RC::SUCCESS) {
    return rc;
  }

  // TODOH 这里返回具体的数据内容, 先在这里直接处理aggregation的数据, 之后看懂他算子的操作之后再优化

  tuple = operator_->current_tuple();
  if (auto x = dynamic_cast<ProjectTuple *>(tuple)) {
    if (!x->is_aggregation()) {
      return RC::SUCCESS;
    }

    int  cell_num        = tuple->cell_num();
    auto tuple_cell_spec = x->get_tuple_cell_spec();
    do {
      // UPDATE
      tuple = operator_->current_tuple();
      if (aggre_calcs.size() == 0) {  // 初始化当前aggre_calcs
        for (size_t i = 0; i < cell_num; i++) {
          Value value;
          rc = tuple->cell_at(i, value);
          aggre_calcs.push_back(AggreCalc{tuple_cell_spec[i]->aggre_type(), value});
        }
      } else {
        for (size_t i = 0; i < cell_num; i++) {
          Value value;
          rc = tuple->cell_at(i, value);
          aggre_calcs[i].update(value);
        }
      }
    } while (RC::SUCCESS == operator_->next());

    std::vector<Value> values;
    for (size_t i = 0; i < cell_num; i++) {
      values.push_back(aggre_calcs[i].get_value());
    }
    auto list_tuple = new ValueListTuple;
    list_tuple->set_cells(values);
    tuple = list_tuple;
  }
  return rc;
}

void SqlResult::set_operator(std::unique_ptr<PhysicalOperator> oper)
{
  ASSERT(operator_ == nullptr, "current operator is not null. Result is not closed?");
  operator_ = std::move(oper);
}
