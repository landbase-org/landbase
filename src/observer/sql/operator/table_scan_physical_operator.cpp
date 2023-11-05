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
#include "sql/expr/do_expr.h"
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

  for (auto &expr : predicates_) {
    // 尝试执行子查询，如果不需要父tuple就能执行成功
    rc = do_expr(trx_, expr.get(), nullptr);

    if (rc != RC::SUCCESS) {
      sql_debug("[open] failed to do expression");
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

    // 有可能是复杂子查询，所以要将parent_tuple_也包含在里面
    Tuple *tuple = &inspector_;
    if (nullptr != parent_tuple_) {
      CompoundTuple *tmp = new CompoundTuple(parent_tuple_, tuple);
      tuple              = tmp;
    }

    rc = filter(tuple, filter_result);
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

RC TableScanPhysicalOperator::filter(Tuple *tuple, bool &result)
{
  RC    rc = RC::SUCCESS;
  Value value;
  for (unique_ptr<Expression> &expr : predicates_) {
    rc = expr->get_value(*tuple, value);
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
