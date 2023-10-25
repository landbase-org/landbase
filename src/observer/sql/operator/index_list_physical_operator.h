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
#include "storage/field/field_meta.h"
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
  IndexListPhysicalOperator() = default;
  IndexListPhysicalOperator(std::string table_name, const std::vector<Index *> &indexes);
  virtual ~IndexListPhysicalOperator() = default;

  PhysicalOperatorType type() const override;
  RC                   open(Trx *) override;
  RC                   next() override;
  virtual RC           close() override;
  virtual Tuple       *current_tuple() override;  // 获取当前迭代器中的结果

private:
  std::string          table_name_;
  std::vector<Index *> indexes_;
  size_t               cur_index_idx_;    // 当前位于index
  size_t               cur_fields_idx_;   // 当前field的下标
  bool                 started_ = false;  // 是否已经开始
  ValueListTuple       tuple_;            // 返回结果的tuple
};
