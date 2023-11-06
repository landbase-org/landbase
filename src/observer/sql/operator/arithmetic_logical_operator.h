#pragma once

#include <memory>
#include <vector>

#include "sql/operator/logical_operator.h"

/**
 * @brief 算术运算
 * @details
 */
class ArithmeticLogicalOperator : public LogicalOperator
{
public:
  ArithmeticLogicalOperator(std::vector<std::unique_ptr<Expression>> &&expressions) { expressions_.swap(expressions); }
  virtual ~ArithmeticLogicalOperator() = default;

  LogicalOperatorType type() const override { return LogicalOperatorType::ARITHMETIC; }
};
