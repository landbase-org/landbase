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

#include "sql/stmt/filter_stmt.h"
#include "common/lang/string.h"
#include "common/log/log.h"
#include "common/rc.h"
#include "sql/expr/expression.h"
#include "sql/parser/parse_defs.h"
#include "sql/parser/value.h"
#include "storage/db/db.h"
#include "storage/table/table.h"

FilterStmt::~FilterStmt()
{
  for (FilterUnit *unit : filter_units_) {
    delete unit;
  }
  filter_units_.clear();
}

RC FilterStmt::create(
    Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables, const ConditionSqlNode *conditions,
    int condition_num, FilterStmt *&stmt
)
{
  RC rc = RC::SUCCESS;
  stmt  = nullptr;

  FilterStmt *tmp_stmt = new FilterStmt();
  for (int i = 0; i < condition_num; i++) {
    FilterUnit *filter_unit = nullptr;
    rc                      = create_filter_unit(db, default_table, tables, conditions[i], filter_unit);
    if (rc != RC::SUCCESS) {
      delete tmp_stmt;
      LOG_WARN("failed to create filter unit. condition index=%d", i);
      return rc;
    }
    tmp_stmt->filter_units_.push_back(filter_unit);
  }

  stmt = tmp_stmt;
  return rc;
}

RC get_table_and_field(
    Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables, const ParseFieldExpr *field_expr,
    Table *&table, const FieldMeta *&field
)
{
  if (common::is_blank(field_expr->table_name().c_str())) {
    table = default_table;
  } else if (nullptr != tables) {
    auto iter = tables->find(field_expr->table_name().c_str());
    if (iter != tables->end()) {
      table = iter->second;
    }
  } else {
    table = db->find_table(field_expr->table_name().c_str());
  }
  if (nullptr == table) {
    LOG_WARN("No such table: attr.relation_name: %s", field_expr->table_name().c_str());
    return RC::SCHEMA_TABLE_NOT_EXIST;
  }

  field = table->table_meta().field(field_expr->field_name().c_str());
  if (nullptr == field) {
    LOG_WARN("no such field in table: table %s, field %s", table->name(), field_expr->field_name().c_str());
    table = nullptr;
    return RC::SCHEMA_FIELD_NOT_EXIST;
  }

  return RC::SUCCESS;
}

RC FilterStmt::create_filter_unit(
    Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables, const ConditionSqlNode &condition,
    FilterUnit *&filter_unit
)
{
  RC rc = RC::SUCCESS;

  CompOp comp = condition.comp;
  if (comp < EQUAL_TO || comp >= NO_OP) {
    LOG_WARN("invalid compare operator : %d", comp);
    return RC::INVALID_ARGUMENT;
  }

  filter_unit = new FilterUnit;

  switch (condition.left->expr_type()) {
    case ParseExprType::FIELD: {
      Table           *table      = nullptr;
      const FieldMeta *field      = nullptr;
      auto             field_expr = static_cast<const ParseFieldExpr *>(condition.left);
      rc                          = get_table_and_field(db, default_table, tables, field_expr, table, field);
      if (rc != RC::SUCCESS) {
        LOG_WARN("cannot find attr");
        return rc;
      }
      FilterObj filter_obj;
      filter_obj.init_attr(Field(table, field));
      filter_unit->set_left(filter_obj);
    } break;
    case ParseExprType::VALUE: {
      FilterObj filter_obj;
      auto      value_expr = static_cast<const ParseValueExpr *>(condition.left);
      filter_obj.init_value(value_expr->value());
      filter_unit->set_left(filter_obj);
    } break;
    case ParseExprType::VALUE_LIST: {
    } break;
    case ParseExprType::SUBQUERY: {
    } break;
    default: {
    } break;
  }

  switch (condition.right->expr_type()) {
    case ParseExprType::FIELD: {
      Table           *table      = nullptr;
      const FieldMeta *field      = nullptr;
      auto             field_expr = static_cast<const ParseFieldExpr *>(condition.right);
      rc                          = get_table_and_field(db, default_table, tables, field_expr, table, field);
      if (rc != RC::SUCCESS) {
        LOG_WARN("cannot find attr");
        return rc;
      }
      FilterObj filter_obj;
      filter_obj.init_attr(Field(table, field));
      filter_unit->set_right(filter_obj);
    } break;
    case ParseExprType::VALUE: {
      FilterObj filter_obj;
      auto      value_expr = static_cast<const ParseValueExpr *>(condition.right);

      filter_obj.init_value(value_expr->value());
      filter_unit->set_right(filter_obj);
    } break;
    case ParseExprType::VALUE_LIST: {
    } break;
    case ParseExprType::SUBQUERY: {
    } break;
    default: {
    } break;
  }

  filter_unit->set_comp(comp);

  // 检查两个类型是否能够比较

  // 如果一边出现了 null, 则可比较
  if (!filter_unit->left().is_attr && filter_unit->left().value.is_null() ||
      (!filter_unit->right().is_attr && filter_unit->right().value.is_null())) {
    return RC::SUCCESS;
  }

  // 检测左侧为日期属性，右侧为日期字符串的情况 处理完直接return截断，不要影响别的类型的转换
  if (filter_unit->left().is_attr && filter_unit->left().field.attr_type() == DATES &&
      filter_unit->right().value.attr_type() == CHARS) {
    int32_t check = convert_string_to_date(filter_unit->right().value.data());
    if (check == -1)
      return RC::FAILURE;
    Value *change = const_cast<Value *>(&filter_unit->right().value);
    change->set_date(check);
    return rc;
  }

  // 如果左右均为值，有一个非CHARS就都转为FLOATS
  if (!filter_unit->left().is_attr && !filter_unit->right().is_attr) {
    Value &left_ref  = const_cast<Value &>(filter_unit->left().value);
    Value &right_ref = const_cast<Value &>(filter_unit->right().value);
    if (filter_unit->left().value.attr_type() != CHARS || filter_unit->right().value.attr_type() != CHARS) {
      if (!left_ref.type_cast(FLOATS) || !right_ref.type_cast(FLOATS)) {
        return RC::FAILURE;
      }
    }
  } else {
    // 左侧为域，右侧为域
    if (filter_unit->right().is_attr && filter_unit->right().is_attr) {
      if (filter_unit->right().field.attr_type() != filter_unit->left().field.attr_type()) {
        LOG_WARN(
            "Compared Fields type dismatch %s with %s",
            attr_type_to_string(filter_unit->left().field.attr_type()),
            attr_type_to_string(filter_unit->right().field.attr_type())
        );
      }
    }
    // 左侧为域，右侧为值
    else if (filter_unit->left().is_attr && !filter_unit->right().is_attr) {
      // status:1
      if (filter_unit->left().field.attr_type() != CHARS) {
        Value   *right_chg = const_cast<Value *>(&filter_unit->right().value);
        AttrType tar       = right_chg->attr_type() == INTS ? INTS : FLOATS;
        if (!right_chg->type_cast(tar)) {
          return RC::FAILURE;
        }
      }  // status:2
      else if (filter_unit->right().value.attr_type() == FLOATS || filter_unit->right().value.attr_type() == INTS) {
        Value *right_chg = const_cast<Value *>(&filter_unit->right().value);
        // uniform to float for the higher precision
        if (!right_chg->type_cast(FLOATS)) {
          return RC::FAILURE;
        }
      }
    }
  }
  return rc;
}