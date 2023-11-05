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
// Created by WangYunlai on 2022/6/7.
//

#pragma once

#include "common/rc.h"
#include "sql/expr/tuple.h"
#include "sql/operator/physical_operator.h"
#include "storage/record/record_manager.h"

class Table;

/**
 * @brief 表扫描物理算子
 * @ingroup PhysicalOperator
 */
class TableScanPhysicalOperator : public PhysicalOperator
{
public:
  TableScanPhysicalOperator(Table *table, bool readonly) : table_(table), readonly_(readonly) {}

  ~TableScanPhysicalOperator() override
  {
    for (auto i : tuples_)
      delete i;
    tuples_.clear();
  }

  std::string param() const override;

  PhysicalOperatorType type() const override { return PhysicalOperatorType::TABLE_SCAN; }

  RC open(Trx *trx) override;
  RC next() override;
  RC close() override;

  Tuple *current_tuple() override;

  void set_predicates(std::vector<std::unique_ptr<Expression>> &&exprs);
  void set_parent_tuple(Tuple *parent_tuple) override { parent_tuple_ = parent_tuple; }

private:
  RC filter(Tuple *tuple, bool &result);

private:
  Table                                                   *table_    = nullptr;
  Trx                                                     *trx_      = nullptr;
  bool                                                     readonly_ = false;
  RecordFileScanner                                        record_scanner_;
  Record                                                   current_record_;
  RowTuple                                                 inspector_;
  std::pair<const Table *, const std::vector<FieldMeta> *> oper_meta;
  std::vector<RowTuple *>                                  tuples_;
  std::vector<std::unique_ptr<Expression>>                 predicates_;  // TODO chang predicate to table tuple filter
  Tuple                                                   *parent_tuple_ = nullptr;
};
