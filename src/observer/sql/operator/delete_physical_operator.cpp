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

#include "sql/operator/delete_physical_operator.h"
#include "common/log/log.h"
#include "event/sql_debug.h"
#include "sql/operator/index_scan_physical_operator.h"
#include "sql/stmt/delete_stmt.h"
#include "storage/record/record.h"
#include "storage/table/table.h"
#include "storage/trx/trx.h"
RC DeletePhysicalOperator::open(Trx *trx)
{
  if (children_.empty()) {
    return RC::SUCCESS;
  }

  std::unique_ptr<PhysicalOperator> &child = children_[0];
  RC                                 rc    = child->open(trx);
  if (rc != RC::SUCCESS) {
    sql_debug("failed to open child operator: %s", strrc(rc));
    return rc;
  }

  trx_ = trx;

  return RC::SUCCESS;
}

RC DeletePhysicalOperator::next()
{
  RC rc = RC::SUCCESS;
  if (children_.empty()) {
    return RC::RECORD_EOF;
  }

  PhysicalOperator *child = children_[0].get();
  while (RC::SUCCESS == (rc = child->next())) {
    Tuple *tuple = child->current_tuple();
    if (nullptr == tuple) {
      sql_debug("failed to get current record: %s", strrc(rc));
      return rc;
    }

    RowTuple *row_tuple = static_cast<RowTuple *>(tuple);
    Record   &record    = row_tuple->record();
    rc                  = trx_->delete_record(table_, record);
    if (rc != RC::SUCCESS) {
      sql_debug("failed to delete record: %s", strrc(rc));
      return rc;
    }

    // TODOH 之后如果更改了事务执行方法， 基地更改这里
    if (auto x = dynamic_cast<IndexScanPhysicalOperator *>(child)) {
      x->set_idx_increase(false);  // 当前事物已经删除了一个数据， index的指针以及在下一个数据上， 不需要更新迭代器
    } else if (child->children().size()) {
      if (auto x = dynamic_cast<IndexScanPhysicalOperator *>(child->children().front().get())) {
        x->set_idx_increase(false);  // 当前事物已经删除了一个数据， index的指针以及在下一个数据上， 不需要更新迭代器
      }
    }
  }

  return RC::RECORD_EOF;
}

RC DeletePhysicalOperator::close()
{
  if (!children_.empty()) {
    children_[0]->close();
  }
  return RC::SUCCESS;
}
