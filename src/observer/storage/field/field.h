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
// Created by Wangyunlai on 2022/07/05.
//

#pragma once

#include "sql/parser/parse_defs.h"
#include "storage/field/field_meta.h"
#include "storage/table/table.h"

/**
 * @brief 字段
 *
 */
class Field
{
public:
  Field() = default;
  Field(const Table *table, const FieldMeta *field) : table_(table), field_(field) {}
  Field(const Table *table, const std::string &table_alias, const FieldMeta *field, const std::string &field_alias)
      : table_(table),
        table_alias_(table_alias),
        field_(field),
        field_alias_(field_alias)
  {}
  Field(const Field &) = default;

  const Table     *table() const { return table_; }
  const FieldMeta *meta() const { return field_; }

  const AggreType aggre_type() const { return aggre_type_; }
  const void      set_aggre_type(AggreType aggre_type) { aggre_type_ = aggre_type; }
  AttrType        attr_type() const { return field_->type(); }

  const char *table_name() const { return table_->name(); }
  const auto &table_alias() const { return table_alias_; }
  const char *field_name() const { return field_->name(); }
  const auto &field_alias() const { return field_alias_; }

  void set_table(const Table *table) { this->table_ = table; }
  void set_field(const FieldMeta *field) { this->field_ = field; }

  void set_int(Record &record, int value);
  int  get_int(const Record &record);

  const char *get_data(const Record &record);

  /**
   * @brief 传入一个record数据，查询该record中该字段是否为null
   *
   * @param data Record data
   * @return true 该字段为null
   * @return false  该字段不为null
   */
  bool is_null(char *data) const;

private:
  const Table     *table_ = nullptr;
  const FieldMeta *field_ = nullptr;
  AggreType        aggre_type_{AGGRE_NONE};
  std::string      table_alias_;
  std::string      field_alias_;  // COUNT的时候, COUNT(123)都可能, 用这个字段存储
};
