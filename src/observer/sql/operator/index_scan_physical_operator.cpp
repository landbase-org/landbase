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
// Created by Wangyunlai on 2022/07/08.
//

#include "sql/operator/index_scan_physical_operator.h"
#include "event/sql_debug.h"
#include "sql/expr/do_expr.h"
#include "sql/expr/sub_query_expr.h"
#include "storage/index/index.h"
#include "storage/trx/trx.h"
#include <cstddef>
#include <cstring>
IndexScanPhysicalOperator::IndexScanPhysicalOperator(
    Table *table, Index *index, bool readonly, const char *left_value, size_t left_value_len, bool left_inclusive,
    const char *right_value, size_t right_value_len, bool right_inclusive
)
    : table_(table),
      index_(index),
      readonly_(readonly),
      left_inclusive_(left_inclusive),
      right_inclusive_(right_inclusive)
{
  if (left_value) {
    left_value_     = left_value;
    left_value_len_ = left_value_len;
  }
  if (right_value) {
    right_value_     = right_value;
    right_value_len_ = right_value_len;
  }
}

RC IndexScanPhysicalOperator::open(Trx *trx)
{
  RC rc = RC::SUCCESS;

  if (nullptr == table_ || nullptr == index_) {
    return RC::INTERNAL;
  }
  IndexScanner *index_scanner = index_->create_scanner(
      left_value_, left_value_len_, left_inclusive_, right_value_, right_value_len_, right_inclusive_
  );
  if (nullptr == index_scanner) {
    sql_debug("failed to create index scanner");
    return RC::INTERNAL;
  }

  record_handler_ = table_->record_handler();
  if (nullptr == record_handler_) {
    sql_debug("invalid record handler");
    index_scanner->destroy();
    return RC::INTERNAL;
  }
  index_scanner_ = index_scanner;

  inspector_.set_schema(table_, table_->table_meta().field_metas());

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

RC IndexScanPhysicalOperator::next()
{
  RID rid;
  RC  rc = RC::SUCCESS;

  record_page_handler_.cleanup();

  bool filter_result = false;
  while (RC::SUCCESS == (rc = index_scanner_->next_entry(&rid, (get_idx_increase())))) {
    set_idx_increase(true);

    rc = record_handler_->get_record(record_page_handler_, &rid, readonly_, &current_record_);
    if (rc != RC::SUCCESS) {
      return rc;
    }

    inspector_.set_record(&current_record_);

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

    if (!filter_result) {
      continue;
    }

    rc = trx_->visit_record(table_, current_record_, readonly_);
    if (rc == RC::RECORD_INVISIBLE) {
      continue;
    } else {
      RowTuple *new_tuple = new RowTuple();
      new_tuple->set_record(&current_record_);
      new_tuple->set_schema(table_, table_->table_meta().field_metas());
      tuples_.emplace_back(new_tuple);
      return rc;
    }
  }

  return rc;
}

RC IndexScanPhysicalOperator::close()
{
  index_scanner_->destroy();
  index_scanner_ = nullptr;
  return RC::SUCCESS;
}

Tuple *IndexScanPhysicalOperator::current_tuple() { return tuples_.back(); }

void IndexScanPhysicalOperator::set_predicates(std::vector<std::unique_ptr<Expression>> &&exprs)
{
  predicates_ = std::move(exprs);
}

RC IndexScanPhysicalOperator::filter(Tuple *tuple, bool &result)
{
  RC    rc = RC::SUCCESS;
  Value value;
  for (std::unique_ptr<Expression> &expr : predicates_) {
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

std::string IndexScanPhysicalOperator::param() const
{
  return std::string(index_->index_meta().name()) + " ON " + table_->name();
}
