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

#include "common/rc.h"
#include "sql/stmt/filter_stmt.h"
#include "sql/stmt/stmt.h"

class Table;

/**
 * @brief 更新语句
 * @ingroup Statement
 */
class UpdateStmt : public Stmt
{
public:
  UpdateStmt() = default;
  UpdateStmt(
      Table *table, FilterStmt *filter_stmt, std::vector<const FieldMeta *> &field_meta,
      std::vector<std::unique_ptr<Expression>> &expr_list
  );
  ~UpdateStmt() override;

public:
  static RC create(Db *db, UpdateSqlNode &update_sql, Stmt *&stmt);

public:
  Table      *table() const { return table_; }
  FilterStmt *filter_stmt() { return filter_stmt_; }
  const auto &field_metas() const { return field_metas_; }
  const auto &expr_list() const { return expr_list_; }
  auto       &expr_list() { return expr_list_; }
  StmtType    type() const override { return StmtType::UPDATE; }

private:
  Table                                   *table_ = nullptr;
  std::vector<const FieldMeta *>           field_metas_;
  std::vector<std::unique_ptr<Expression>> expr_list_;
  FilterStmt                              *filter_stmt_ = nullptr;
};
