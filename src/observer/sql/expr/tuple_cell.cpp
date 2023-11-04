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
// Created by WangYunlai on 2022/07/05.
//

#include "sql/expr/tuple_cell.h"
#include "common/lang/comparator.h"
#include "common/lang/string.h"
#include "common/log/log.h"
#include "storage/field/field.h"
#include <sstream>

TupleCellSpec::TupleCellSpec(const char *table_name, const char *field_name, const char *alias)
{
  if (table_name) {
    table_name_ = table_name;
  }
  if (field_name) {
    field_name_ = field_name;
  }
  if (alias) {
    alias_ = alias;
  } else {
    if (table_name_.empty()) {
      alias_ = field_name_;
    } else {
      alias_ = table_name_ + "." + field_name_;
    }
  }
}

TupleCellSpec::TupleCellSpec(const char *table_name, const char *field_name, AggreType aggre_type, const char *alias)
    : TupleCellSpec(table_name, field_name, alias)
{
  aggre_type_ = aggre_type;
}

TupleCellSpec::TupleCellSpec(const char *alias)
{
  if (alias) {
    alias_ = alias;
  }
}

bool const TupleCellSpec::operator==(const AggreExpression &expr) const
{
  auto table_name = expr.table_name();
  auto field_name = expr.field_name();
  auto aggre_type = expr.get_aggre_type();
  // 这里如果使用 return expr.table_name() == table_name_
  // && expr.field_name == field_name_ && expr.get_aggre_type == aggre_type_
  // 会有错误， 很奇怪，可能是字符串和字符数组之间转化的问题
  if (table_name != table_name_) {
    return false;
  }
  if (field_name != field_name_) {
    return false;
  }
  if (aggre_type != aggre_type_) {
    return false;
  }
  return true;
}

bool const TupleCellSpec::operator==(const Field &field) const
{
  return field.table_name() == table_name_ && field.field_name() == field_name_;
}
