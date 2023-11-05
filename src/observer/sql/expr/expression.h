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

#include <cstddef>
#include <memory>
#include <string.h>
#include <string>
#include <unordered_map>
#include <unordered_set>

#include "common/lang/string.h"
#include "common/log/log.h"
#include "event/sql_debug.h"
#include "sql/parser/parse_defs.h"
#include "sql/parser/value.h"
#include "storage/db/db.h"
#include "storage/field/field.h"
#include "storage/field/field_meta.h"
#include "storage/table/table.h"
class Tuple;

/**
 * @defgroup Expression
 * @brief 表达式
 */

/**
 * @brief 表达式类型
 * @ingroup Expression
 */
enum class ExprType
{
  NONE,
  STAR,         ///< 星号，表示所有字段
  FIELD,        ///< 字段。在实际执行时，根据行数据内容提取对应字段的值
  VALUE,        ///< 常量值
  CAST,         ///< 需要做类型转换的表达式
  COMPARISON,   ///< 需要做比较的表达式
  CONJUNCTION,  ///< 多个表达式使用同一种关系(AND或OR)来联结
  ARITHMETIC,   ///< 算术运算
  IN,
  EXISTS,
  VALUELIST,
  SUBQUERY,
  AGGREGATION,  ///< 聚合运算
};

/**
 * @brief 表达式的抽象描述
 * @ingroup Expression
 * @details 在SQL的元素中，任何需要得出值的元素都可以使用表达式来描述
 * 比如获取某个字段的值、比较运算、类型转换
 * 当然还有一些当前没有实现的表达式，比如算术运算。
 *
 * 通常表达式的值，是在真实的算子运算过程中，拿到具体的tuple后
 * 才能计算出来真实的值。但是有些表达式可能就表示某一个固定的
 * 值，比如ValueExpr。
 */
class Expression
{
public:
  Expression()          = default;
  virtual ~Expression() = default;

  /**
   * @brief 根据具体的tuple，来计算当前表达式的值。tuple有可能是一个具体某个表的行数据
   */
  virtual RC get_value(const Tuple &tuple, Value &value) const = 0;

  /**
   * @brief 在没有实际运行的情况下，也就是无法获取tuple的情况下，尝试获取表达式的值
   * @details 有些表达式的值是固定的，比如ValueExpr，这种情况下可以直接获取值
   */
  virtual RC try_get_value(Value &value) const { return RC::UNIMPLENMENT; }

  /**
   * @brief 表达式的类型
   * 可以根据表达式类型来转换为具体的子类
   */
  virtual ExprType type() const = 0;

  /**
   * @brief 表达式值的类型
   * @details 一个表达式运算出结果后，只有一个值
   */
  virtual AttrType value_type() const = 0;

  /**
   * @brief 表达式的名字，比如是字段名称，或者用户在执行SQL语句时输入的内容
   */
  virtual std::string name() const { return name_; }  // 这里是输出结果显示的table_name
  virtual void        set_name(std::string name) { name_ = name; }

private:
  std::string name_;
};

/**
 * @brief 字段表达式
 * @ingroup Expression
 */
class FieldExpr : public Expression
{
public:
  FieldExpr() = default;
  FieldExpr(const Table *table, const FieldMeta *field) : field_(table, field) {}
  FieldExpr(const Table *table, const std::string table_alias, const FieldMeta *field, std::string field_alias)
      : field_(table, table_alias, field, field_alias)
  {}
  FieldExpr(const Field &field) : field_(field) {}

  virtual ~FieldExpr() = default;

  ExprType type() const override { return ExprType::FIELD; }
  AttrType value_type() const override { return field_.attr_type(); }

  Field &field() { return field_; }

  const Field &field() const { return field_; }

  const char *table_name() const { return field_.table_name(); }
  const auto &table_alias() const { return field_.table_alias(); }
  const char *field_name() const { return field_.field_name(); }
  const auto &field_alias() const { return field_.field_alias(); }

  const AggreType aggre_type() const { return field_.aggre_type(); }

  RC get_value(const Tuple &tuple, Value &value) const override;

  bool is_null(char *data) const;

  /**
   * 用于初始化field_meta的时候， 例如rel.attr, rel.*, *, attr的情况
   */
  static RC create(
      const SelectSqlNode &select_sql_node, const std::unordered_map<std::string, Table *> &table_map,
      const std::vector<Table *> &tables, std::vector<Expression *> &res_expr, Db *db
  );

  /**
   * 用于知道rel_attr的情况下构建对应的FieldExpr;
   */
  static RC create(
      const RelAttrSqlNode &node, const std::unordered_map<std::string, Table *> &table_map,
      const std::vector<Table *> &tables, Expression *&res_expr
  );

private:
  Field field_;
};

/**
 * @brief 常量值表达式
 * @ingroup Expression
 */
class ValueExpr : public Expression
{
public:
  ValueExpr() = default;
  explicit ValueExpr(const Value &value) : value_(value) {}

  virtual ~ValueExpr() = default;

  RC get_value(const Tuple &tuple, Value &value) const override;
  RC try_get_value(Value &value) const override
  {
    value = value_;
    return RC::SUCCESS;
  }

  ExprType type() const override { return ExprType::VALUE; }

  AttrType value_type() const override { return value_.attr_type(); }

  void get_value(Value &value) const { value = value_; }

  const Value &get_value() const { return value_; }

  auto &get_value() { return value_; }

  bool is_null() const { return value_.is_null(); }

private:
  Value value_;
};

/**
 * @brief 类型转换表达式
 * @ingroup Expression
 */
class CastExpr : public Expression
{
public:
  CastExpr(std::unique_ptr<Expression> child, AttrType cast_type);
  virtual ~CastExpr();

  ExprType type() const override { return ExprType::CAST; }
  RC       get_value(const Tuple &tuple, Value &value) const override;

  RC try_get_value(Value &value) const override;

  AttrType value_type() const override { return cast_type_; }

  std::unique_ptr<Expression> &child() { return child_; }

private:
  RC cast(const Value &value, Value &cast_value) const;

private:
  std::unique_ptr<Expression> child_;      ///< 从这个表达式转换
  AttrType                    cast_type_;  ///< 想要转换成这个类型
};

/**
 * @brief 比较表达式
 * @ingroup Expression
 */
class ComparisonExpr : public Expression
{
public:
  ComparisonExpr(CompOp comp, std::unique_ptr<Expression> left, std::unique_ptr<Expression> right);
  virtual ~ComparisonExpr();

  ExprType type() const override { return ExprType::COMPARISON; }

  RC get_value(const Tuple &tuple, Value &value) const override;

  AttrType value_type() const override { return BOOLEANS; }

  CompOp comp() const { return comp_; }

  std::unique_ptr<Expression> &left() { return left_; }
  std::unique_ptr<Expression> &right() { return right_; }

  /**
   * 尝试在没有tuple的情况下获取当前表达式的值
   * 在优化的时候，可能会使用到
   */
  RC try_get_value(Value &value) const override;

  /**
   * compare the two tuple cells
   * @param value the result of comparison
   */
  RC compare_value(const Value &left, const Value &right, bool &value) const;

private:
  CompOp                      comp_;
  std::unique_ptr<Expression> left_;
  std::unique_ptr<Expression> right_;
};

/**
 * @brief 联结表达式
 * @ingroup Expression
 * 多个表达式使用同一种关系(AND或OR)来联结
 * 当前miniob仅有AND操作
 */
class ConjunctionExpr : public Expression
{
public:
  enum class Type
  {
    AND,
    OR,
  };

public:
  ConjunctionExpr(Type type, std::vector<std::unique_ptr<Expression>> &children);
  virtual ~ConjunctionExpr() = default;

  ExprType type() const override { return ExprType::CONJUNCTION; }

  AttrType value_type() const override { return BOOLEANS; }

  RC get_value(const Tuple &tuple, Value &value) const override;

  Type conjunction_type() const { return conjunction_type_; }

  std::vector<std::unique_ptr<Expression>> &children() { return children_; }

private:
  Type                                     conjunction_type_;
  std::vector<std::unique_ptr<Expression>> children_;
};

/**
 * @brief 算术表达式
 * @ingroup Expression
 */
class ArithmeticExpr : public Expression
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

public:
  ArithmeticExpr(Type type, Expression *left, Expression *right);
  ArithmeticExpr(Type type, std::unique_ptr<Expression> left, std::unique_ptr<Expression> right);
  virtual ~ArithmeticExpr() = default;

  ExprType type() const override { return ExprType::ARITHMETIC; }

  AttrType value_type() const override;

  RC get_value(const Tuple &tuple, Value &value) const override;
  RC try_get_value(Value &value) const override;

  Type arithmetic_type() const { return arithmetic_type_; }

  std::unique_ptr<Expression> &left() { return left_; }
  std::unique_ptr<Expression> &right() { return right_; }

private:
  RC calc_value(const Value &left_value, const Value &right_value, Value &value) const;

private:
  Type                        arithmetic_type_;
  std::unique_ptr<Expression> left_;
  std::unique_ptr<Expression> right_;
};

class ValueListExpr : public Expression
{
public:
  ValueListExpr() = default;
  ValueListExpr(const std::vector<Value> &value_list) : value_list_(value_list) {}
  ExprType type() const override { return ExprType::VALUELIST; }
  AttrType value_type() const override { return value_list_.front().attr_type(); }
  RC       get_value(const Tuple &tuple, Value &value) const override { return try_get_value(value); }
  RC       try_get_value(Value &value) const override
  {
    if (value_list_.empty()) {
      value = Value();
    } else if (value_list_.size() == 1) {
      value = value_list_.front();
    } else {
      sql_debug("ValueListExpr::value_list_ size is %d", value_list_.size());
      return RC::INTERNAL;
    }
    return RC::SUCCESS;
  }

  bool has_values() { return !value_list_.empty(); }

public:
  auto &value_list() const { return value_list_; }
  auto &value_list() { return value_list_; }
  bool  contains(const Value &value) const
  {
    return std::find(value_list_.begin(), value_list_.end(), value) != value_list_.end();
  }

protected:
  std::vector<Value> value_list_;
};

/**
 * @brief In 表达式
 * @ingroup Expression
 * left_ : FieldExpr, ValueExpr, 返回一个值的SubQueryExor, 和返回一个值的ValueListExpr
 * right_: SubQueryExpr, ValueListExpr
 */
class InExpr : public Expression
{
public:
  InExpr(std::unique_ptr<Expression> left, CompOp comp, std::unique_ptr<Expression> right)
      : left_(std::move(left)),
        comp_(comp),
        right_(std::move(right))
  {}
  ExprType type() const override { return ExprType::IN; }
  AttrType value_type() const override { return BOOLEANS; }
  RC       get_value(const Tuple &tuple, Value &value) const override
  {
    Value left_value;

    RC rc = left_->get_value(tuple, left_value);
    if (rc != RC::SUCCESS) {
      sql_debug("failed to get value of left expression. rc=%s", strrc(rc));
      return rc;
    }

    auto right_expr = static_cast<ValueListExpr *>(right_.get());
    bool bool_value = right_expr->contains(left_value);
    if (comp_ == CompOp::NOT_IN) {
      bool_value = !bool_value;
    }
    value.set_boolean(bool_value);
    return rc;
  }

  auto &left() { return left_; }
  auto &right() { return right_; }

private:
  CompOp                      comp_;
  std::unique_ptr<Expression> left_;
  std::unique_ptr<Expression> right_;
};

/**
 * @brief Exists 表达式
 * @ingroup Expression
 * right_: SubQueryExpr
 */
class ExistsExpr : public Expression
{
public:
  ExistsExpr(CompOp comp, std::unique_ptr<Expression> right) : comp_(comp), right_(std::move(right)) {}
  ExprType type() const override { return ExprType::EXISTS; }
  AttrType value_type() const override { return BOOLEANS; }
  RC       get_value(const Tuple &tuple, Value &value) const override { return try_get_value(value); }
  RC       try_get_value(Value &value) const override
  {
    // TODO: 还可以优化，比如将right_改为 ValueListExpr?
    auto value_list_expr = static_cast<ValueListExpr *>(right_.get());

    bool result = (value_list_expr->has_values()) ^ (comp_ == CompOp::NOT_EXISTS);
    value.set_boolean(result);
    return RC::SUCCESS;
  }

  auto &right() { return right_; }
  auto &sub_expr() { return right_; }

private:
  CompOp                      comp_;
  std::unique_ptr<Expression> right_;
};

class AggreExpression : public Expression
{
public:
  AggreExpression() = default;
  AggreExpression(AggreExpression &expr);
  AggreExpression(const std::string &alias, AggreType type, const FieldExpr *field, bool full_table_name = false)
      : alias_(alias),
        type_(type),
        full_table_name_(full_table_name),
        field_(field)
  {}
  virtual ~AggreExpression();

public:
  // 关于ValueExpr 和 FieldExpr的获取的复制
  void             set_param_value(const ValueExpr *value) { value_ = value; }
  const ValueExpr *get_param_value() const { return value_; }
  bool             has_param_value() const { return nullptr != value_; }

  const Field     &field() const { return field_->field(); }
  const FieldExpr &fieldexpr() const { return *field_; }

  const char *table_name() const { return field_->table_name(); }
  const auto &table_alias() const { return field_->table_alias(); }
  const char *field_name() const { return field_->field_name(); }
  const auto &field_alias() const { return field_->field_alias(); }
  AggreType   get_aggre_type() const { return type_; }
  std::string get_aggre_type_str() const { return aggreType2str(type_); };
  void        set_full_table_name(bool flag) { full_table_name_ = flag; }
  bool        is_full_table_name() { return full_table_name_; }

public:
  AttrType value_type() const override
  {
    switch (type_) {
      case AGGRE_MAX: return field_->value_type();
      case AGGRE_MIN: return field_->value_type();
      case AGGRE_SUM: return field_->value_type();
      case AGGRE_AVG: return FLOATS;
      case AGGRE_COUNT: return INTS;
      case AGGRE_COUNT_ALL: return INTS;
      default: {
        sql_debug("invalid aggre type. aggre_type=%d", type_);
      } break;
    }
    return UNDEFINED;
  };
  ExprType type() const override { return ExprType::AGGREGATION; }
  RC       get_value(const Tuple &tuple, Value &value) const override;
  /**
   * @brief 返回列表的名字
   * @example MAX(id), COUNT(*) 等字段
   */
  std::string name() const override;
  const auto &alias() const { return alias_; }

public:
  static void get_aggre_expression(Expression *expr, std::vector<std::unique_ptr<AggreExpression>> &aggrfunc_exprs);
  static RC   create(
        const AggreSqlNode &node, const std::unordered_map<std::string, Table *> &table_map,
        const std::vector<Table *> &tables, Expression *&res_expr, Db *db = nullptr
    );

private:
  AggreType        type_{AggreType::AGGRE_NONE};
  bool             full_table_name_{false};  // 是否需要显示完整的表名， 用于子查询
  const FieldExpr *field_ = nullptr;
  const ValueExpr *value_ = nullptr;  // 用来存储COUNT（attr）的值
  std::string      alias_;
};