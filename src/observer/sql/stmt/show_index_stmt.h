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
// Created by Wangyunlai on 2023/6/14.
//

#pragma once

#include <string>
#include <vector>

#include "event/sql_debug.h"
#include "sql/stmt/stmt.h"

class Db;

/**
 * @brief 描述表的语句
 * @ingroup Statement
 * @details 虽然解析成了stmt，但是与原始的SQL解析后的数据也差不多
 */
class ShowIndexStmt : public Stmt
{
public:
  ShowIndexStmt(const std::string &table_name) : table_name_(table_name) {}
  virtual ~ShowIndexStmt() = default;

  std::string getTableName() { return table_name_; }
  StmtType    type() const override { return StmtType::SHOW_INDEX; }

  static RC create(Db *db, const ShowIndexSqlNode &show_index, Stmt *&stmt)
  {
    stmt = new ShowIndexStmt(show_index.relation_name);
    LOG_INFO("show index statement: table name %s", show_index.relation_name.c_str());
    return RC::SUCCESS;
  }

private:
  std::string table_name_;
};