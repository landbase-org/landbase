#pragma once

#include "sql/parser/value.h"
#include <memory>
#include <unordered_map>
#include <vector>
enum class ParseExprType
{
  FIELD,
  AGGREGATION,
  VALUE,
  VALUE_LIST,
  SUBQUERY,
  ARITHMETIC
};

/**
 * @description: 聚合类型
 */
enum AggreType
{
  AGGRE_NONE,
  AGGRE_MAX,
  AGGRE_MIN,
  AGGRE_COUNT,
  AGGRE_COUNT_ALL,
  AGGRE_AVG,
  AGGRE_SUM
};
static std::string aggreType2str(AggreType aggre)
{
  static std::unordered_map<AggreType, std::string> m{
      {AGGRE_NONE, "NONE"},
      {AGGRE_MAX, "MAX"},
      {AGGRE_MIN, "MIN"},
      {AGGRE_COUNT, "COUNT"},
      {AGGRE_COUNT_ALL, "COUNT"},
      {AGGRE_AVG, "AVG"},
      {AGGRE_SUM, "SUM"},
  };
  return m.at(aggre);
}

class ParseExpr
{
public:
  ParseExpr()                             = default;
  virtual ~ParseExpr()                    = default;
  virtual ParseExprType expr_type() const = 0;
  virtual AttrType      value_type() { return AttrType::UNDEFINED; }

  void  set_name(const std::string &name) { name_ = name; }
  auto &name() const { return name_; }

private:
  std::string name_;
};

class ParseValueExpr : public ParseExpr
{
public:
  ParseValueExpr() = default;
  ParseValueExpr(Value &value) : value_(value) {}
  ParseExprType expr_type() const override { return ParseExprType::VALUE; }
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
  ParseExprType expr_type() const override { return ParseExprType::VALUE_LIST; }
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
  ParseExprType expr_type() const override { return ParseExprType::FIELD; }

public:
  void  set_table_name(const std::string &table_name) { table_name_ = table_name; }
  auto &table_name() const { return table_name_; }

  void  set_table_alias(const std::string &table_alias) { table_alias_ = table_alias; }
  auto &table_alias() const { return table_alias_; }

  void  set_field_name(const std::string &field_name) { field_name_ = field_name; }
  auto &field_name() const { return field_name_; }

  void  set_alias(const std::string &alias) { field_alias_ = alias; }
  auto &field_alias() const { return field_alias_; }

private:
  std::string table_name_;
  std::string table_alias_;
  std::string field_name_;
  std::string field_alias_;
};

class ParseAggreExpr : public ParseExpr
{
public:
  ParseAggreExpr(ParseFieldExpr *field_expr, AggreType aggre_type)
      : table_name_(field_expr->table_name()),
        field_name_(field_expr->field_name()),
        aggre_type_(aggre_type)
  {}
  ParseExprType expr_type() const override { return ParseExprType::AGGREGATION; }

public:
  void  set_table_name(const std::string &table_name) { table_name_ = table_name; }
  auto &table_name() const { return table_name_; }

  void  set_field_name(const std::string &field_name) { field_name_ = field_name; }
  auto &field_name() const { return field_name_; }

  void set_aggre_type(AggreType aggre_type) { aggre_type_ = aggre_type; }
  auto aggre_type() const { return aggre_type_; }

  void  set_alias(const std::string &alias) { alias_ = alias; }
  auto &alias() const { return alias_; }

private:
  AggreType   aggre_type_;
  std::string table_name_;
  std::string field_name_;
  std::string alias_;
};

class ParseArithmeticExpr : public ParseExpr
{
public:
  enum class Type
  {
    ADD,
    SUB,
    MUL,
    DIV,
    NEGATIVE,
  };
  ParseArithmeticExpr(ParseExpr *left, ParseArithmeticExpr::Type arithmetic_type, ParseExpr *right)
      : left_(left),
        right_(right),
        arithmetic_type_(arithmetic_type)
  {}
  ParseExprType expr_type() const override { return ParseExprType::ARITHMETIC; }
  AttrType      value_type() override
  {
    if (left_ != nullptr) {
      return left_->value_type();
    }
    if (right_ != nullptr) {
      return right_->value_type();
    }
    return AttrType::FLOATS;
  }

public:
  auto &left() const { return left_; }
  auto &right() const { return right_; }
  auto  arithmetic_type() const { return arithmetic_type_; }

private:
  ParseExpr *left_  = nullptr;
  ParseExpr *right_ = nullptr;
  Type       arithmetic_type_;
};
