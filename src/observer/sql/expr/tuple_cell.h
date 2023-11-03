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

#include "sql/expr/expression.h"
#include "sql/parser/parse_defs.h"
#include "storage/field/field_meta.h"
#include "storage/table/table.h"
#include <iostream>

class TupleCellSpec
{
public:
  TupleCellSpec(const char *table_name, const char *field_name, const char *alias = nullptr);
  TupleCellSpec(const char *table_name, const char *field_name, AggreType aggre_type, const char *alias = nullptr);
  TupleCellSpec(const char *alias);

  const char     *table_name() const { return table_name_.c_str(); }
  const char     *field_name() const { return field_name_.c_str(); }
  const char     *alias() const { return alias_.c_str(); }
  const AggreType aggre_type() const { return aggre_type_; }
  const void      set_aggre_type(AggreType aggre_type) { aggre_type_ = aggre_type; }

public:
  bool const operator==(const AggreExpression &expr) const;
  bool const operator==(const Field &field) const;

private:
  std::string table_name_;
  std::string field_name_;
  AggreType   aggre_type_;
  std::string alias_;
};
