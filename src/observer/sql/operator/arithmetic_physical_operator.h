#pragma once

#include "sql/expr/tuple.h"
#include "sql/operator/physical_operator.h"

class ArithmeticPhysicalOperator : public PhysicalOperator
{
public:
  ArithmeticPhysicalOperator(std::vector<std::unique_ptr<Expression>> &&expressions)
      : expressions_(std::move(expressions))
  {}

  virtual ~ArithmeticPhysicalOperator() = default;

  PhysicalOperatorType type() const override { return PhysicalOperatorType::ARITHMETIC; }

  std::string name() const override { return "Arith"; }
  std::string param() const override { return ""; }

  RC open(Trx *trx) override { return children_[0]->open(trx); }
  RC next() override
  {
    RC                rc   = RC::SUCCESS;
    PhysicalOperator *oper = children_.front().get();

    while (RC::SUCCESS == (rc = oper->next())) {
      Tuple *tuple = oper->current_tuple();

      if (nullptr == tuple) {
        rc = RC::INTERNAL;
        sql_debug("[arith operator] failed to get tuple from operator");
        break;
      }

      tuple_ = ValueListTuple();
      for (auto &expr : expressions_) {
        Value value;
        rc = expr->get_value(*tuple, value);
        if (rc != RC::SUCCESS) {
          return rc;
        }
        tuple_.add_cell(value);
      }
      break;
    }
    return rc;
  }
  RC close() override { return children_[0]->close(); }

  Tuple *current_tuple() override { return &tuple_; }

  const std::vector<std::unique_ptr<Expression>> &expressions() const { return expressions_; }

private:
  std::vector<std::unique_ptr<Expression>> expressions_;
  ValueListTuple                           tuple_;
};
