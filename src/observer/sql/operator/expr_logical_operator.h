#include "logical_operator.h"
#include "sql/expr/expression.h"
#include <memory>
#include <vector>

class ExprLogicalOperator : public LogicalOperator
{
public:
  ExprLogicalOperator(std::vector<Expression *> const &exprs) : exprs_(exprs) {}
  virtual ~ExprLogicalOperator() = default;

  virtual LogicalOperatorType      type() const override { return LogicalOperatorType::EXPRESSION; }
  const std::vector<Expression *> &get_exprs() { return exprs_; }

private:
  std::vector<Expression *> exprs_;
};