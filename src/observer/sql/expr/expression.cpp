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

#include "sql/expr/expression.h"
#include "common/log/log.h"
#include "sql/expr/tuple.h"
#include "sql/expr/tuple_cell.h"
#include "sql/parser/parse_defs.h"
#include "sql/parser/value.h"
#include "storage/field/field.h"
#include <cassert>
#include <memory>

using namespace std;

//////////////////////////////////////////////////////////////////////////
//////////////////////////////!Expression/////////////////////////////////
//////////////////////////////////////////////////////////////////////////
RC Expression::create(
    const ExprNode &node, const std::unordered_map<std::string, Table *> &table_map, const std::vector<Table *> &tables,
    Expression *&res_expr, Db *db
)
{
  switch (node.type_) {
    case ExprType::FIELD: {
      return FieldExpr::create(node, table_map, tables, res_expr);
    } break;
    case ExprType::AGGREGATION: {
      return AggreExpression::create(node, table_map, tables, res_expr);
    } break;
    case ExprType::VALUE:
    case ExprType::NONE:
    case ExprType::STAR:
    case ExprType::CAST:
    case ExprType::COMPARISON:
    case ExprType::CONJUNCTION:
    case ExprType::ARITHMETIC: {
      LOG_ERROR("not compliment other type");
      // DEFALT; 如果到时候需要再加
    } break;
  }
  return RC::SUCCESS;
}

RC FieldExpr::get_value(const Tuple &tuple, Value &value) const
{
  return tuple.find_cell(TupleCellSpec(table_name(), field_name()), value);
}

bool FieldExpr::is_null(char *data) const { return field_.is_null(data); }

RC FieldExpr::create(
    const std::vector<RelAttrSqlNode> &nodes, const std::unordered_map<std::string, Table *> &table_map,
    const std::vector<Table *> &tables, std::vector<Expression *> &res_expr, Db *db
)
{
  // 获取所有的wildcard
  auto wildcard_fields = [](Table *table, std::vector<Expression *> &field_metas) {
    const TableMeta &table_meta = table->table_meta();
    const int        field_num  = table_meta.field_num();
    for (int i = table_meta.sys_field_num(); i < field_num; i++) {
      field_metas.push_back(new FieldExpr(table, table_meta.field(i)));
    }
  };

  for (auto &relation_attr : nodes) {
    const auto table_name = relation_attr.relation_name;
    const auto field_name = relation_attr.attribute_name;
    const auto aggre_type = AGGRE_NONE;
    if (table_name == "*" || field_name == "") {
      LOG_WARN("no fields type err=%s.%s", table_name.c_str(), field_name.c_str());
      return RC::SCHEMA_FIELD_MISSING;
    }

    if (table_name == "" && field_name == "*") {
      for (const auto table : tables) {
        wildcard_fields(table, res_expr);
      }
    } else if (table_name == "" && field_name != "*") {  // field_name != "*"
      if (tables.size() != 1) {
        LOG_WARN("invalid. I do not know the attr's table. attr=%s", relation_attr.attribute_name.c_str());
        return RC::SCHEMA_FIELD_MISSING;
      }

      Table           *table      = tables[0];
      const FieldMeta *field_meta = table->table_meta().field(relation_attr.attribute_name.c_str());
      if (nullptr == field_meta) {
        LOG_WARN("no such field. field=%s.%s.%s", db->name(), table->name(), relation_attr.attribute_name.c_str());
        return RC::SCHEMA_FIELD_MISSING;
      }
      res_expr.push_back(new FieldExpr(table, field_meta));
    } else {  // table_name != "*"
      auto iter = table_map.find(table_name);
      if (iter == table_map.end()) {
        LOG_WARN("no such table in from list: %s", table_name.c_str());
        return RC::SCHEMA_FIELD_MISSING;
      }

      Table *table = iter->second;
      if (field_name == "*") {
        wildcard_fields(table, res_expr);
      } else {
        const FieldMeta *field_meta = table->table_meta().field(field_name.c_str());
        if (nullptr == field_meta) {
          LOG_WARN("no such field. field=%s.%s.%s", db->name(), table->name(), field_name.c_str());
          return RC::SCHEMA_FIELD_MISSING;
        }
        res_expr.push_back(new FieldExpr(table, field_meta));
      }
    }
  }

  // 设置输出的表名
  for (auto expr : res_expr) {
    auto        x = dynamic_cast<FieldExpr *>(expr);
    std::string name;
    if (tables.size() == 1) {
      name = x->field_name();
    } else {
      name += x->table_name();
      name += ".";
      name += x->field_name();
    }
    x->set_name(name);
  }
  return RC::SUCCESS;
}

RC FieldExpr::create(
    const ExprNode &node, const std::unordered_map<std::string, Table *> &table_map, const std::vector<Table *> &tables,
    Expression *&res_expr
)
{
  assert(node.type_ == ExprType::FIELD);
  const auto &[table_name, field_name] = node.rel_attr_;
  const Table     *table;
  const FieldMeta *field_meta;

  if (table_name == "") {  // table_name 为空
    if (tables.size() != 1) {
      LOG_WARN("invalid. I do not know the attr's table. attr=%s", field_name.c_str());
      return RC::SCHEMA_FIELD_MISSING;
    }

    table      = tables.front();  // 只有一个表
    field_meta = table->table_meta().field(field_name.c_str());
    if (nullptr == field_meta) {
      LOG_WARN("no such field. field=%s.%s", table->name(), field_name.c_str());
      return RC::SCHEMA_FIELD_MISSING;
    }
  } else {
    auto iter = table_map.find(table_name);
    if (iter == table_map.end()) {
      LOG_WARN("no such table in from list: %s", table_name.c_str());
      return RC::SCHEMA_FIELD_MISSING;
    }

    table      = iter->second;
    field_meta = table->table_meta().field(field_name.c_str());
    if (nullptr == field_meta) {
      LOG_WARN("no such field. field=%s.%s", table->name(), field_name.c_str());
      return RC::SCHEMA_FIELD_MISSING;
    }
  }

  res_expr = new FieldExpr(table, field_meta);
  return RC::SUCCESS;
}

RC ValueExpr::get_value(const Tuple &tuple, Value &value) const
{
  value = value_;
  return RC::SUCCESS;
}

/////////////////////////////////////////////////////////////////////////////////
CastExpr::CastExpr(unique_ptr<Expression> child, AttrType cast_type) : child_(std::move(child)), cast_type_(cast_type)
{}

CastExpr::~CastExpr() {}

RC CastExpr::cast(const Value &value, Value &cast_value) const
{
  RC rc = RC::SUCCESS;
  if (this->value_type() == value.attr_type()) {
    cast_value = value;
    return rc;
  }

  switch (cast_type_) {
    case BOOLEANS: {
      bool val = value.get_boolean();
      cast_value.set_boolean(val);
    } break;
    default: {
      rc = RC::INTERNAL;
      LOG_WARN("unsupported convert from type %d to %d", child_->value_type(), cast_type_);
    }
  }
  return rc;
}

RC CastExpr::get_value(const Tuple &tuple, Value &cell) const
{
  RC rc = child_->get_value(tuple, cell);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  return cast(cell, cell);
}

RC CastExpr::try_get_value(Value &value) const
{
  RC rc = child_->try_get_value(value);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  return cast(value, value);
}

////////////////////////////////////////////////////////////////////////////////

ComparisonExpr::ComparisonExpr(CompOp comp, unique_ptr<Expression> left, unique_ptr<Expression> right)
    : comp_(comp),
      left_(std::move(left)),
      right_(std::move(right))
{}

ComparisonExpr::~ComparisonExpr() {}

RC ComparisonExpr::compare_value(const Value &left, const Value &right, bool &result) const
{
  // TODO : 完善此处对比较结果的处理
  result = left.compare(comp_, right);

  return RC::SUCCESS;
}

RC ComparisonExpr::try_get_value(Value &cell) const
{
  if (left_->type() == ExprType::VALUE && right_->type() == ExprType::VALUE) {
    ValueExpr   *left_value_expr  = static_cast<ValueExpr *>(left_.get());
    ValueExpr   *right_value_expr = static_cast<ValueExpr *>(right_.get());
    const Value &left_cell        = left_value_expr->get_value();
    const Value &right_cell       = right_value_expr->get_value();

    bool value = false;

    RC rc = compare_value(left_cell, right_cell, value);

    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to compare tuple cells. rc=%s", strrc(rc));
    } else {
      cell.set_boolean(value);
    }
    return rc;
  }

  return RC::INVALID_ARGUMENT;
}

RC ComparisonExpr::get_value(const Tuple &tuple, Value &value) const
{
  Value left_value;
  Value right_value;

  RC rc = left_->get_value(tuple, left_value);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to get value of left expression. rc=%s", strrc(rc));
    return rc;
  }
  rc = right_->get_value(tuple, right_value);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to get value of right expression. rc=%s", strrc(rc));
    return rc;
  }

  bool bool_value = false;
  rc              = compare_value(left_value, right_value, bool_value);
  if (rc == RC::SUCCESS) {
    value.set_boolean(bool_value);
  }
  return rc;
}

////////////////////////////////////////////////////////////////////////////////
ConjunctionExpr::ConjunctionExpr(Type type, vector<unique_ptr<Expression>> &children)
    : conjunction_type_(type),
      children_(std::move(children))
{}

RC ConjunctionExpr::get_value(const Tuple &tuple, Value &value) const
{
  RC rc = RC::SUCCESS;
  if (children_.empty()) {
    value.set_boolean(true);
    return rc;
  }

  Value tmp_value;
  for (const unique_ptr<Expression> &expr : children_) {
    rc = expr->get_value(tuple, tmp_value);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to get value by child expression. rc=%s", strrc(rc));
      return rc;
    }
    bool bool_value = tmp_value.get_boolean();
    if ((conjunction_type_ == Type::AND && !bool_value) || (conjunction_type_ == Type::OR && bool_value)) {
      value.set_boolean(bool_value);
      return rc;
    }
  }

  bool default_value = (conjunction_type_ == Type::AND);
  value.set_boolean(default_value);
  return rc;
}

////////////////////////////////////////////////////////////////////////////////

ArithmeticExpr::ArithmeticExpr(ArithmeticExpr::Type type, Expression *left, Expression *right)
    : arithmetic_type_(type),
      left_(left),
      right_(right)
{}
ArithmeticExpr::ArithmeticExpr(ArithmeticExpr::Type type, unique_ptr<Expression> left, unique_ptr<Expression> right)
    : arithmetic_type_(type),
      left_(std::move(left)),
      right_(std::move(right))
{}

AttrType ArithmeticExpr::value_type() const
{
  if (!right_) {
    return left_->value_type();
  }

  if (left_->value_type() == AttrType::INTS && right_->value_type() == AttrType::INTS &&
      arithmetic_type_ != Type::DIV) {
    return AttrType::INTS;
  }

  return AttrType::FLOATS;
}

RC ArithmeticExpr::calc_value(const Value &left_value, const Value &right_value, Value &value) const
{
  RC rc = RC::SUCCESS;

  const AttrType target_type = value_type();

  switch (arithmetic_type_) {
    case Type::ADD: {
      if (target_type == AttrType::INTS) {
        value.set_int(left_value.get_int() + right_value.get_int());
      } else {
        value.set_float(left_value.get_float() + right_value.get_float());
      }
    } break;

    case Type::SUB: {
      if (target_type == AttrType::INTS) {
        value.set_int(left_value.get_int() - right_value.get_int());
      } else {
        value.set_float(left_value.get_float() - right_value.get_float());
      }
    } break;

    case Type::MUL: {
      if (target_type == AttrType::INTS) {
        value.set_int(left_value.get_int() * right_value.get_int());
      } else {
        value.set_float(left_value.get_float() * right_value.get_float());
      }
    } break;

    case Type::DIV: {
      if (target_type == AttrType::INTS) {
        if (right_value.get_int() == 0) {
          // NOTE:
          // 设置为整数最大值是不正确的。通常的做法是设置为NULL，但是当前的miniob没有NULL概念，所以这里设置为整数最大值。
          value.set_int(numeric_limits<int>::max());
        } else {
          value.set_int(left_value.get_int() / right_value.get_int());
        }
      } else {
        if (right_value.get_float() > -EPSILON && right_value.get_float() < EPSILON) {
          // NOTE:
          // 设置为浮点数最大值是不正确的。通常的做法是设置为NULL，但是当前的miniob没有NULL概念，所以这里设置为浮点数最大值。
          value.set_float(numeric_limits<float>::max());
        } else {
          value.set_float(left_value.get_float() / right_value.get_float());
        }
      }
    } break;

    case Type::NEGATIVE: {
      if (target_type == AttrType::INTS) {
        value.set_int(-left_value.get_int());
      } else {
        value.set_float(-left_value.get_float());
      }
    } break;

    default: {
      rc = RC::INTERNAL;
      LOG_WARN("unsupported arithmetic type. %d", arithmetic_type_);
    } break;
  }
  return rc;
}

RC ArithmeticExpr::get_value(const Tuple &tuple, Value &value) const
{
  RC rc = RC::SUCCESS;

  Value left_value;
  Value right_value;

  rc = left_->get_value(tuple, left_value);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to get value of left expression. rc=%s", strrc(rc));
    return rc;
  }
  rc = right_->get_value(tuple, right_value);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to get value of right expression. rc=%s", strrc(rc));
    return rc;
  }
  return calc_value(left_value, right_value, value);
}

RC ArithmeticExpr::try_get_value(Value &value) const
{
  RC rc = RC::SUCCESS;

  Value left_value;
  Value right_value;

  rc = left_->try_get_value(left_value);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to get value of left expression. rc=%s", strrc(rc));
    return rc;
  }

  if (right_) {
    rc = right_->try_get_value(right_value);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to get value of right expression. rc=%s", strrc(rc));
      return rc;
    }
  }

  return calc_value(left_value, right_value, value);
}

////////////////////////////////////////////////////////////////////////////////
//////!aggregation/////////
////////////////////////////////////////////////////////////////////////////////
AggreExpression::AggreExpression(AggreExpression &expr)
{
  type_ = expr.type_;
  if (expr.field_ != nullptr) {
    field_ = new FieldExpr(expr.field_->field());
  }
  if (expr.value_ != nullptr) {
    value_ = new ValueExpr(expr.value_->get_value());
  }
}

AggreExpression::~AggreExpression()
{
  if (value_ != nullptr) {
    delete value_;
  }
  if (field_ != nullptr) {
    delete field_;
  }
};

/**
 * tuple 这里的tuple是AggregationTuple
 */
RC AggreExpression::get_value(const Tuple &tuple, Value &value) const
{
  TupleCellSpec spec(table_name(), field_name());
  spec.set_aggre_type(type_);

  return tuple.find_cell(spec, value);
}

std::string AggreExpression::name() const
{
  // 之后的alias在这里修改
  std::string name_str = "";
  if (full_table_name_) {
    name_str += get_aggre_type_str() + "(";
    name_str += table_name();
    name_str += ".";
    name_str += field_name();
    name_str += ')';
  } else {
    name_str += get_aggre_type_str() + "(";
    name_str += has_param_value() ? value_->get_value().to_string() : field_->field_name();
    name_str += ')';
  }
  return name_str;
}

AttrType AggreExpression::get_return_value_type() const
{
  switch (type_) {
    case AGGRE_MAX: return field_->value_type();
    case AGGRE_MIN: return field_->value_type();
    case AGGRE_SUM: return field_->value_type();
    case AGGRE_AVG: return FLOATS;
    case AGGRE_COUNT: return INTS;
    case AGGRE_COUNT_ALL: return INTS;
    case AGGRE_NONE: return UNDEFINED;
  }
  return UNDEFINED;
}

void AggreExpression::get_aggre_expression(Expression *expr, std::vector<unique_ptr<AggreExpression>> &aggrfunc_exprs)
{
  if (auto x = dynamic_cast<AggreExpression *>(expr)) {
    // deep_copy一个aggre对象
    aggrfunc_exprs.push_back(std::make_unique<AggreExpression>(*x));
  }
}

RC AggreExpression::create(
    const ExprNode &node, const std::unordered_map<std::string, Table *> &table_map, const std::vector<Table *> &tables,
    Expression *&res_expr, Db *db
)
{
  assert(node.type_ == ExprType::AGGREGATION);

  RC          rc         = RC::SUCCESS;
  Table      *table      = tables.front();
  const auto &aggre_node = node.aggre_;

  const auto &rel_attr             = aggre_node.attribute_name;
  const auto &[rel, attr]          = rel_attr;
  const auto      &aggre_type      = aggre_node.aggre_type;
  auto             field_meta      = table->table_meta().field(attr.c_str());
  Expression      *field_expr      = nullptr;  // FieldExpr 表达式
  AggreExpression *aggre_expr      = nullptr;
  bool             full_table_name = tables.size() > 1;  // 当前默认是两张表及以上显示rel.attr

  // attr为“*”但是attr_type不为COUNT
  if (attr == "*" && aggre_type != AGGRE_COUNT) {
    LOG_WARN("Aggregation type %s cannot match parameters '*'", aggreType2str(aggre_type).c_str());
    return RC::FAILURE;
  }

  // aggre_type 为COUNT 需要特判
  if (aggre_type == AGGRE_COUNT) {  // 如果是COUNT的情况， 那么COUNT（attr)可以为任何字符，使用Value存储该字符
    auto &change = const_cast<AggreType &>(aggre_type);

    if (attr == "*") {  // 如果是COUNT（*）那么是查询所有包括空的表， 否则之查询当前列
      change = AGGRE_COUNT_ALL;
      aggre_expr =
          new AggreExpression(aggre_type, new FieldExpr(tables[0], tables[0]->table_meta().field(1)), full_table_name);
      auto value_expr = new ValueExpr(Value(attr.c_str()));
      aggre_expr->set_param_value(value_expr);
      res_expr = aggre_expr;
      return rc;
    }

    // attr 字段不为“*”
    if (RC::SUCCESS != (rc = Expression::create(ExprNode(rel_attr), table_map, tables, field_expr, db))) {
      LOG_ERROR("Aggregation attr name:%s not created succ.", attr.c_str());
      return rc;
    }
    aggre_expr = new AggreExpression(aggre_type, static_cast<FieldExpr *>(field_expr), full_table_name);
    res_expr   = aggre_expr;
    return rc;
  }

  // aggre_type 为其他
  rc = Expression::create(ExprNode(aggre_node.attribute_name), table_map, tables, field_expr, db);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("AggreExpression Create Param Expression Failed. RC = %d:%s", rc, strrc(rc));
    return rc;
  }
  aggre_expr = new AggreExpression(aggre_type, static_cast<FieldExpr *>(field_expr), full_table_name);
  res_expr   = aggre_expr;
  return rc;
}