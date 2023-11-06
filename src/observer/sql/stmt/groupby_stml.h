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
// Created by Wangyunlai on 2022/5/22.
//

#pragma once

#include "stmt.h"
#include "storage/db/db.h"
#include <memory>
#include <unordered_map>
#include <vector>

class Db;
class Table;
class FieldMeta;

class GroupByUnit
{
public:
  GroupByUnit() = default;
  GroupByUnit(std::unique_ptr<Expression> expr) : expr_(std::move(expr)) {}
  ~GroupByUnit() = default;

  void                         set_expr(std::unique_ptr<Expression> expr) { expr_ = std::move(expr); }
  std::unique_ptr<Expression> *expr() { return &expr_; }
  static RC                    create(
                         Db *db, const std::unordered_map<std::string, Table *> &table_map, const std::vector<Table *> &tables,
                         const GroupBySqlNode &groupby, std::unique_ptr<GroupByUnit> *groupby_unit
                     );

private:
  std::unique_ptr<Expression> expr_;
};

class GroupByStmt : public Stmt
{
public:
  GroupByStmt()          = default;
  virtual ~GroupByStmt() = default;

  StmtType    type() const override { return StmtType::GROUP_BY; }
  void        add_unit(std::unique_ptr<GroupByUnit> unit) { groupby_units_.push_back(std::move(unit)); }
  const auto *groupby_units() const { return &groupby_units_; }
  static RC   create(
        Db *db, const std::unordered_map<std::string, Table *> &table_map, const std::vector<Table *> &tables,
        const std::vector<GroupBySqlNode> &groupby_nodes, GroupByStmt *&stmt
    );

private:
  std::vector<std::unique_ptr<GroupByUnit>> groupby_units_;
};