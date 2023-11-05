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
  AggrePhysicalOperator(std::vector<std::unique_ptr<AggreExpression>> aggre_exprs)
  {
    // 初始化aggre_tuple
    // 这里传递的是aggre_exprs的指针（真的是绝）
    tuple_.init(std::move(aggre_exprs));
  }

  virtual ~AggrePhysicalOperator() = default;

  PhysicalOperatorType type() const override { return PhysicalOperatorType::AGGREGATION; }
  RC                   open(Trx *trx) override;
  RC                   next() override;
  RC                   close() override;
  Tuple               *current_tuple() override;

private:
  bool             is_started_{false};
  bool             is_record_eof{false};
  AggregationTuple tuple_;
};