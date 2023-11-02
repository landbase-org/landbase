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
  virtual ParseExprType expr_type() = 0;
};

class ParseValueExpr : public ParseExpr
{
public:
  ParseValueExpr(Value &value) : value_(value) {}
  ParseExprType expr_type() { return ParseExprType::VALUE; }

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
  ParseExprType expr_type() { return ParseExprType::VALUE_LIST; }

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
  ParseExprType expr_type() { return ParseExprType::FIELD; }

public:
  auto &table_name() const { return table_name_; }
  auto &field_name() const { return field_name_; }

private:
  std::string table_name_;
  std::string field_name_;
};
