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
#include "sql/parser/parse_defs.h"
#include "stmt.h"
#include "storage/db/db.h"
#include "storage/field/field.h"
#include <unordered_map>
#include <vector>

class Db;
class Table;
class FieldMeta;

class OrderByUnit
{
public:
  Field order_field;
  bool  is_asc = true;
};

/**
 * @brief 表示OrderBy的stmt
 */
class OrderByStmt : public Stmt
{
  OrderByStmt()  = default;
  virtual ~OrderByStmt();
  StmtType type() const override { return StmtType::ORDER_BY; }

public:
  static RC create(
      Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables, const OrderSqlNode *orderbys,
      int order_num, OrderByStmt *&stmt
  );
  static RC create_orderby_unit(
      Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables, const OrderSqlNode &orderby,
      OrderByUnit *&order_unit
  );

private:
  std::vector<OrderByUnit *> order_units_;
};