#pragma once

#include "sql/parser/value.h"
#include <memory>
#include <vector>
enum class ParseExprType
{
  FIELD,
  VALUE,
  VALUE_LIST,
  SUBQUERY,
};

class ParseExpr
{
public:
  ParseExpr()                       = default;
  virtual ~ParseExpr()              = default;
  virtual ParseExprType expr_type() = 0;
  virtual AttrType      value_type() { return AttrType::UNDEFINED; }
};

class ParseValueExpr : public ParseExpr
{
public:
  ParseValueExpr() = default;
  ParseValueExpr(Value &value) : value_(value) {}
  ParseExprType expr_type() override { return ParseExprType::VALUE; }
  AttrType      value_type() override { return value_.attr_type(); }
  bool          is_null() const { return value_.is_null(); }

public:
  auto &value() { return value_; };
  auto &value() const { return value_; };

private:
  Value value_;
};

class ParseValueListExpr : public ParseExpr
{
public:
  ParseValueListExpr(std::vector<Value> &value_list) : value_list_(value_list) {}
  ParseExprType expr_type() override { return ParseExprType::VALUE_LIST; }
  AttrType      value_type() override
  {
    if (!value_list_.empty()) {
      return value_list_.front().attr_type();
    }
    return AttrType::UNDEFINED;
  }

public:
  auto &value_list() { return value_list_; }
  auto &value_list() const { return value_list_; }

private:
  std::vector<Value> value_list_;
};

class ParseFieldExpr : public ParseExpr
{
public:
  ParseFieldExpr(std::string table_name, std::string field_name) : table_name_(table_name), field_name_(field_name) {}
  ParseFieldExpr(std::string table_name, std::string table_alias, std::string field_alias, std::string field_name)
      : table_name_(table_name),
        table_alias_(table_alias),
        field_name_(field_name),
        field_alias_(field_alias)
  {}
  ParseExprType expr_type() { return ParseExprType::FIELD; }

public:
  void  set_table_name(std::string &table_name) { table_name_ = table_name; }
  auto &table_name() const { return table_name_; }
  auto &table_alias() const { return table_alias_; }
  auto &field_name() const { return field_name_; }
  auto &field_alias() const { return field_alias_; }

private:
  std::string table_name_;
  std::string table_alias_;
  std::string field_name_;
  std::string field_alias_;
};
