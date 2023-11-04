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

#include "sql/stmt/update_stmt.h"
#include "sql/expr/sub_query_expr.h"
#include "storage/db/db.h"

UpdateStmt::UpdateStmt(
    Table *table, FilterStmt *filter_stmt, std::vector<const FieldMeta *> &field_meta,
    std::vector<std::unique_ptr<Expression>> &expr_list
)
    : table_(table),
      filter_stmt_(filter_stmt),
      field_metas_(std::move(field_meta)),
      expr_list_(std::move(expr_list))
{}

UpdateStmt::~UpdateStmt()
{
  if (filter_stmt_ != nullptr) {
    delete filter_stmt_;
    filter_stmt_ = nullptr;
  }
}

RC UpdateStmt::create(Db *db, UpdateSqlNode &update, Stmt *&stmt)
{
  // 检查参数
  const char *table_name = update.relation_name.c_str();
  if (nullptr == db || nullptr == table_name) {
    LOG_WARN("invalid argument. db=%p, table_name=%p", db, table_name);
    return RC::INVALID_ARGUMENT;
  }

  // 查找表
  Table *table = db->find_table(table_name);
  if (nullptr == table) {
    LOG_WARN("no such table. db=%s, table_name=%s", db->name(), table_name);
    return RC::SCHEMA_TABLE_NOT_EXIST;
  }

  // 查找字段元信息
  std::vector<const FieldMeta *> field_metas;
  for (auto &field_name : update.attr_list) {
    auto field_meta = table->table_meta().field(field_name.c_str());
    if (field_meta == nullptr) {
      LOG_ERROR("Fail to find field %s in table %s", field_name.c_str(), table->name());
      return RC::SCHEMA_FIELD_NOT_EXIST;
    }
    field_metas.push_back(field_meta);
  }

  // 检查字段和值的类型是否匹配
  const auto size = field_metas.size();
  for (int i = 0; i < size; i++) {
    if (update.expr_list[i]->expr_type() != ParseExprType::VALUE) {
      continue;
    }
    auto value_expr = static_cast<ParseValueExpr *>(update.expr_list[i]);
    if (value_expr->is_null()) {
      if (field_metas[i]->nullable()) {
        continue;
      } else {
        LOG_ERROR("Field %s is not nullable", field_metas[i]->name());
        return RC::SCHEMA_FIELD_NOT_NULLABLE;
      }
    }

    if (field_metas[i]->type() != value_expr->value_type()) {
      // 日期格式特殊处理
      if (field_metas[i]->type() == DATES && value_expr->value_type() == CHARS) {
        auto   &value   = value_expr->value();
        int32_t dateval = convert_string_to_date(value.data());
        value.set_date(dateval);
        continue;
      }
      LOG_ERROR(
          "Fail to update %s, field type(%d) and value type(%d) mismatch",
          table->name(),
          field_metas[i]->type(),
          value_expr->value_type()
      );
      return RC::INVALID_ARGUMENT;
    }
  }

  // 新建 expr_list
  std::vector<std::unique_ptr<Expression>> expr_list;
  for (auto &expr : update.expr_list) {
    switch (expr->expr_type()) {
      case ParseExprType::VALUE: {
        auto value_expr = static_cast<ParseValueExpr *>(expr);
        expr_list.emplace_back(new ValueExpr(value_expr->value()));
      } break;
      case ParseExprType::VALUE_LIST: {
        auto value_list_expr = static_cast<ParseValueListExpr *>(expr);
        expr_list.emplace_back(new ValueListExpr(value_list_expr->value_list()));
      } break;
      case ParseExprType::SUBQUERY: {
        auto  sub_query_expr = static_cast<ParseSubQueryExpr *>(expr);
        Stmt *stmt           = nullptr;
        RC    rc             = SelectStmt::create(db, *sub_query_expr->sub_query(), stmt);
        if (rc != RC::SUCCESS) {
          sql_debug("create sub query select stmt failed");
          return rc;
        }
        auto select_stmt = static_cast<SelectStmt *>(stmt);
        expr_list.emplace_back(new SubQueryExpr(select_stmt));
      } break;
      default: {
        sql_debug("invalid expr type: %d", expr->expr_type());
      } break;
    }
  }

  // 设置过滤条件
  std::unordered_map<std::string, Table *> table_map;
  table_map.insert(std::pair<std::string, Table *>(std::string(table_name), table));

  FilterStmt *filter_stmt = nullptr;
  RC          rc          = FilterStmt::create(
      db, table, &table_map, update.conditions.data(), static_cast<int>(update.conditions.size()), filter_stmt
  );
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to create filter statement. rc=%d:%s", rc, strrc(rc));
    return rc;
  }

  // 新建 Stmt
  stmt = new UpdateStmt(table, filter_stmt, field_metas, expr_list);
  return RC::SUCCESS;
}
