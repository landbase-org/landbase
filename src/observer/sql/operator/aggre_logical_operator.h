#pragma once
#include "logical_operator.h"
#include "sql/expr/expression.h"
#include "sql/stmt/order_by_stmt.h"
#include <memory>

/**
 * @brief sort 表示对表进行排序
 * @ingroup LogicalOperator
 */

class AggreLogicalOperator : public LogicalOperator
{
public:
  AggreLogicalOperator(std::vector<std::unique_ptr<AggreExpression>> &&expressions)
  {
    aggre_expressions.swap(expressions);
  }
  virtual ~AggreLogicalOperator() {}
  LogicalOperatorType                            type() const override { return LogicalOperatorType::AGGREGATION; }
  std::vector<std::unique_ptr<AggreExpression>> &get_aggre_exprs() { return aggre_expressions; }

private:
  std::vector<std::unique_ptr<AggreExpression>> aggre_expressions;
};