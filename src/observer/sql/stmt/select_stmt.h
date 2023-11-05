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
// Created by Wangyunlai on 2022/6/5.
//

#pragma once

#include <memory>
#include <vector>

#include "common/rc.h"
#include "order_by_stmt.h"
#include "sql/parser/parse_defs.h"
#include "sql/stmt/filter_stmt.h"
#include "sql/stmt/groupby_stml.h"
#include "sql/stmt/stmt.h"
#include "storage/field/field.h"

class FieldMeta;
class FilterStmt;
class Db;
class Table;
class OrderByStmt;

/**
 * @brief 表示select语句
 * @ingroup Statement
 */
class SelectStmt : public Stmt
{
public:
  SelectStmt() = default;
  ~SelectStmt() override;

  StmtType type() const override { return StmtType::SELECT; }

public:
  static RC create(Db *db, const SelectSqlNode &select_sql, Stmt *&stmt);

public:
  const std::vector<Table *>      &tables() const { return tables_; }
  const std::vector<Expression *> &expressions() const { return expressions_; }
  FilterStmt                      *filter_stmt() const { return filter_stmt_; }
  OrderByStmt                     *order_by_stmt() const { return order_stmt_; }
  GroupByStmt                     *groupby_stmt() const { return groupby_stmt_; }
  HavingStmt                      *having_stmt() const { return having_stmt_; }

private:
  std::vector<Expression *> expressions_;
  std::vector<Table *>      tables_;
  FilterStmt               *filter_stmt_  = nullptr;
  OrderByStmt              *order_stmt_   = nullptr;
  GroupByStmt              *groupby_stmt_ = nullptr;
  HavingStmt               *having_stmt_  = nullptr;
};
