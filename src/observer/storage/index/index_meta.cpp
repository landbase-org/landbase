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
// Created by Wangyunlai.wyl on 2021/5/18.
//

#include "storage/index/index_meta.h"
#include "common/lang/string.h"
#include "common/log/log.h"
#include "storage/field/field.h"
#include "storage/field/field_meta.h"
#include "storage/table/table_meta.h"
#include "json/json.h"
#include <algorithm>
#include <cstddef>

const static Json::StaticString FIELD_NAME("name");
const static Json::StaticString FIELD_FIELD_NAME("field_name");
const static Json::StaticString FIELD_UNIQUE("unique");

RC IndexMeta::init(const char *name, const std::vector<std::string> &field_names, bool unique)
{
  if (common::is_blank(name)) {
    LOG_ERROR("Failed to init index, name is empty.");
    return RC::INVALID_ARGUMENT;
  }

  name_   = name;
  fields_ = field_names;
  unique_ = unique;
  return RC::SUCCESS;
}

RC IndexMeta::init(const char *name, const std::vector<FieldMeta> &fields, bool unique)
{
  std::vector<std::string> field_names;
  for (const auto &field : fields) {
    field_names.emplace_back(field.name());
  }

  return init(name, field_names, unique);
}

void IndexMeta::to_json(Json::Value &json_value) const
{
  json_value[FIELD_NAME]   = name_;
  json_value[FIELD_UNIQUE] = unique_;
  for (int i = 0; i < fields_.size(); i++) {
    json_value[FIELD_FIELD_NAME][i] = fields_[i];
  }
}

RC IndexMeta::from_json(const TableMeta &table, const Json::Value &json_value, IndexMeta &index)
{
  const Json::Value &name_value   = json_value[FIELD_NAME];
  const Json::Value &field_values = json_value[FIELD_FIELD_NAME];
  const Json::Value &unique_value = json_value[FIELD_UNIQUE];
  if (!name_value.isString()) {
    LOG_ERROR("Index name is not a string. json value=%s", name_value.toStyledString().c_str());
    return RC::INTERNAL;
  }

  if (!unique_value.isBool()) {
    LOG_ERROR("Index name is not a bool. json value=%s", unique_value.toStyledString().c_str());
    return RC::INTERNAL;
  }

  // fields;
  std::vector<std::string> field_names;
  for (auto field_value : field_values) {
    if (!field_value.isString()) {
      LOG_ERROR(
          "Field name of index [%s] is not a string. json value=%s",
          name_value.asCString(),
          field_value.toStyledString().c_str()
      );
      return RC::INTERNAL;
    }

    const FieldMeta *field = table.field(field_value.asCString());
    if (nullptr == field) {
      LOG_ERROR("Deserialize index [%s]: no such field: %s", name_value.asCString(), field_value.asCString());
      return RC::SCHEMA_FIELD_MISSING;
    }

    field_names.push_back(field->name());
  }

  return index.init(name_value.asCString(), field_names, unique_value.asBool());
}

const char *IndexMeta::name() const { return name_.c_str(); }
const bool  IndexMeta::is_unique() const { return unique_; }

const char                     *IndexMeta::field() const { return fields_[0].c_str(); }
const std::vector<std::string> *IndexMeta::fields() const { return &fields_; }

void IndexMeta::desc(std::ostream &os) const
{
  os << "index name=" << name_ << ", fields=";

  for (size_t i = 0; i < fields_.size(); i++) {
    if (i != 0) {
      os << ',';
    }
    os << fields_[i];
  }
  os << ';';
}