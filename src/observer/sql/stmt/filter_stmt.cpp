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
#include "event/sql_debug.h"
#include "sql/expr/expression.h"
#include "sql/expr/sub_query_expr.h"
#include "sql/parser/parse_defs.h"
#include "sql/parser/value.h"
#include "sql/stmt/select_stmt.h"
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
      sql_debug("failed to create filter unit. condition index=%d", i);
      return rc;
    }
    tmp_stmt->filter_units_.push_back(filter_unit);
  }

  stmt = tmp_stmt;
  // 设置是否全为or
  if (condition_num > 1) {
    stmt->has_or_ = conditions[1].has_or;
  }
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
    sql_debug("No such table: attr.relation_name: %s", field_expr->table_name().c_str());
    return RC::SCHEMA_TABLE_NOT_EXIST;
  }

  field = table->table_meta().field(field_expr->field_name().c_str());
  if (nullptr == field) {
    sql_debug("no such field in table: table %s, field %s", table->name(), field_expr->field_name().c_str());
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
    sql_debug("invalid compare operator : %d", comp);
    return RC::INVALID_ARGUMENT;
  }

  filter_unit = new FilterUnit;

  // 创建左边的表达式
  Expression *left_expr = nullptr;
  switch (condition.left->expr_type()) {
    case ParseExprType::FIELD: {
      Table           *table      = nullptr;
      const FieldMeta *field      = nullptr;
      auto             field_expr = static_cast<const ParseFieldExpr *>(condition.left);
      rc                          = get_table_and_field(db, default_table, tables, field_expr, table, field);
      if (rc != RC::SUCCESS) {
        sql_debug("cannot find attr");
        return rc;
      }
      left_expr = new FieldExpr(Field(table, field));
    } break;
    case ParseExprType::VALUE: {
      auto value_expr = static_cast<const ParseValueExpr *>(condition.left);
      left_expr       = new ValueExpr(value_expr->value());
    } break;
    case ParseExprType::VALUE_LIST: {
      auto value_list_expr = static_cast<const ParseValueListExpr *>(condition.left);
      left_expr            = new ValueListExpr(value_list_expr->value_list());
    } break;
    case ParseExprType::SUBQUERY: {
      auto  sub_query_expr = static_cast<const ParseSubQueryExpr *>(condition.left);
      Stmt *stmt           = nullptr;
      rc                   = SelectStmt::create(db, *sub_query_expr->sub_query(), stmt);
      if (rc != RC::SUCCESS) {
        sql_debug("create sub query select stmt failed");
        return rc;
      }
      auto select_stmt = static_cast<SelectStmt *>(stmt);
      left_expr        = new SubQueryExpr(select_stmt);
    } break;
    default: {
    } break;
  }
  if (left_expr == nullptr) {
    sql_debug("left_expr is nullptr");
    return RC::UNIMPLENMENT;
  }
  filter_unit->set_left(left_expr);

  // 创建右边的表达式
  Expression *right_expr = nullptr;
  switch (condition.right->expr_type()) {
    case ParseExprType::FIELD: {
      Table           *table      = nullptr;
      const FieldMeta *field      = nullptr;
      auto             field_expr = static_cast<const ParseFieldExpr *>(condition.right);
      rc                          = get_table_and_field(db, default_table, tables, field_expr, table, field);
      if (rc != RC::SUCCESS) {
        sql_debug("cannot find attr");
        return rc;
      }
      right_expr = new FieldExpr(Field(table, field));
    } break;
    case ParseExprType::VALUE: {
      auto value_expr = static_cast<const ParseValueExpr *>(condition.right);
      right_expr      = new ValueExpr(value_expr->value());
    } break;
    case ParseExprType::VALUE_LIST: {
      auto value_list_expr = static_cast<const ParseValueListExpr *>(condition.right);
      right_expr           = new ValueListExpr(value_list_expr->value_list());
    } break;
    case ParseExprType::SUBQUERY: {
      auto  sub_query_expr = static_cast<const ParseSubQueryExpr *>(condition.right);
      Stmt *stmt           = nullptr;
      rc                   = SelectStmt::create(db, *sub_query_expr->sub_query(), stmt);
      if (rc != RC::SUCCESS) {
        sql_debug("create sub query select stmt failed");
        return rc;
      }
      auto select_stmt = static_cast<SelectStmt *>(stmt);
      right_expr       = new SubQueryExpr(select_stmt);
    } break;
    default: {
    } break;
  }
  if (right_expr == nullptr) {
    sql_debug("right_expr is nullptr");
    return RC::UNIMPLENMENT;
  }
  filter_unit->set_right(right_expr);
  // 设置比较符
  filter_unit->set_comp(comp);

  // 检查两个类型是否能够比较
  // 如果类型相同肯定能比较
  if (left_expr->value_type() == right_expr->value_type()) {
    return RC::SUCCESS;
  }

  // 接下来分四种情况讨论
  // 字符串与整数比较时会转成整数类型，字符串/整数与浮点数比较时会转成浮点数类型
  if (left_expr->type() == ExprType::FIELD && right_expr->type() == ExprType::VALUE) {
    // 左侧字段，右侧值
    auto   tmp_expr = static_cast<ValueExpr *>(right_expr);
    Value &value    = tmp_expr->get_value();

    // 如果右侧为null，直接返回
    if (value.is_null()) {
      return RC::SUCCESS;
    }

    // 检测左侧为日期属性，右侧为日期字符串的情况 处理完直接return截断，不要影响别的类型的转换
    if (left_expr->value_type() == DATES && right_expr->value_type() == CHARS) {
      int32_t check = convert_string_to_date(value.data());
      if (check == -1) {
        sql_debug("convert_string_to_date failed");
        return RC::FAILURE;
      }
      value.set_date(check);
      return RC::SUCCESS;
      // 如果左侧为字符串，转为 float
    } else if (right_expr->value_type() == CHARS) {
      if (!value.type_cast(FLOATS)) {
        return RC::FAILURE;
      }
      return RC::SUCCESS;
    } else {
      sql_debug(
          "Compared Fields type dismatch %s with %s",
          attr_type_to_string(left_expr->value_type()),
          attr_type_to_string(right_expr->value_type())
      );
    }
  } else if (left_expr->type() == ExprType::VALUE && right_expr->type() == ExprType::VALUE) {
    // 左侧值，右侧值
    // 如果一边出现了 null, 则可比较
    if (left_expr->value_type() == NULLS || right_expr->value_type() == NULLS) {
      return RC::SUCCESS;
      // 如果左右均为值，有一个非CHARS就都转为FLOATS
    } else if (left_expr->value_type() != CHARS || right_expr->value_type() != CHARS) {
      auto   left_value_expr  = static_cast<ValueExpr *>(left_expr);
      auto   right_value_expr = static_cast<ValueExpr *>(right_expr);
      Value &left_value       = left_value_expr->get_value();
      Value &right_value      = right_value_expr->get_value();
      if (!left_value.type_cast(FLOATS) || !right_value.type_cast(FLOATS)) {
        return RC::FAILURE;
      }
    }
  } else if (left_expr->type() == ExprType::FIELD && right_expr->type() == ExprType::FIELD) {
    // 左边字段，右边字段
    sql_debug(
        "Compared Fields type dismatch %s with %s",
        attr_type_to_string(left_expr->value_type()),
        attr_type_to_string(right_expr->value_type())
    );
  } else {
    // 左边值，右边字段
    //  where exists (select id from user);
    if (right_expr->type() == ExprType::SUBQUERY) {
      return RC::SUCCESS;
    };
    if (left_expr->value_type() == NULLS) {
      return RC::SUCCESS;
    }
    sql_debug("Unimplemented");
  }

  return rc;
}