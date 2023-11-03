#pragma once

#include "event/sql_debug.h"
#include "physical_operator.h"
#include "sql/expr/expression.h"
#include "sql/expr/tuple.h"
#include "sql/parser/value.h"
#include "sql/stmt/order_by_stmt.h"
#include "storage/trx/trx.h"
#include <memory>

/**
 * @brief 进行aggre_fun的物理算子
 * @ingroup AggrePhysicalOperator
 * @details
 */
class AggrePhysicalOperator : public PhysicalOperator
{
public:
  AggrePhysicalOperator(std::vector<std::unique_ptr<AggreExpression>> &&expressions)
      : expressions_(std::move(expressions))
  {}

  virtual ~AggrePhysicalOperator() = default;

  PhysicalOperatorType type() const override { return PhysicalOperatorType::AGGREGATION; }
  RC                   open(Trx *trx) override;
  RC                   next() override;
  RC                   close() override;
  Tuple               *current_tuple() override;

private:
  std::vector<std::unique_ptr<AggreExpression>> expressions_;
  // AggregationTuple                              tuple_;
};