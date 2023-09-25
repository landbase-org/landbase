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

#pragma once

#include "sql/operator/physical_operator.h"
#include "storage/index/index.h"
#include <vector>

/**
 * @brief 索引列表物理算子
 * @ingroup PhysicalOperator
 * @details 用于将索引列表转换为物理算子,为了方便实现的接口，比如help命令
 */
class IndexListPhysicalOperator : public PhysicalOperator
{
public:
  IndexListPhysicalOperator() {}
  IndexListPhysicalOperator(std::string table_name, const std::vector<Index *> &indexes)
      : indexes_(indexes),
        table_name_(table_name)
  {
    iterator_ = indexes_.begin();
  }

  virtual ~IndexListPhysicalOperator() = default;

  PhysicalOperatorType type() const override { return PhysicalOperatorType::INDEX_LIST; }

  RC open(Trx *) override { return RC::SUCCESS; }

  RC next() override
  {
    if (!started_) {
      started_  = true;
      iterator_ = indexes_.begin();
    } else if (iterator_ != indexes_.end()) {
      ++iterator_;
    }
    return iterator_ == indexes_.end() ? RC::RECORD_EOF : RC::SUCCESS;
  }

  virtual RC close() override { return RC::SUCCESS; }

  virtual Tuple *current_tuple() override  // 获取当前迭代器中的结果
  {
    if (iterator_ == indexes_.end()) {
      return nullptr;
    }

    vector<Value> cells;
    const auto    index = *iterator_;
    const auto   &meta  = index->index_meta();
    cells.push_back(Value(table_name_.c_str()));  // 表名
    cells.push_back(Value(1));                    // 是否为唯一索引, 默认是
    cells.push_back(Value(meta.name()));          // 索引名称
    cells.push_back(Value(1));                    // 索引序号, 当前是单索引, 默认为1
    cells.push_back(Value(meta.field()));         // 索引的列表名称
    tuple_.set_cells(cells);

    return &tuple_;
  }

private:
  std::string                    table_name_;
  std::vector<Index *>           indexes_;
  std::vector<Index *>::iterator iterator_;
  bool                           started_ = false;
  ValueListTuple                 tuple_;  // 返回结果的tuple
};
