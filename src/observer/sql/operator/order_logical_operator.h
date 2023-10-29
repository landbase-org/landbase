#pragma once
#include "logical_operator.h"
#include "sql/stmt/order_by_stmt.h"

/**
 * @brief sort 表示对表进行排序
 * @ingroup LogicalOperator
 */

class OrderLogicalOperator : public LogicalOperator
{
public:
  OrderLogicalOperator(const std::vector<OrderByUnit *> &units) : order_units_(units) {}
  virtual ~OrderLogicalOperator() { order_units_.clear(); }
  LogicalOperatorType        type() const override { return LogicalOperatorType::ORDER_BY; }
  std::vector<OrderByUnit *> get_units() const { return order_units_; }

private:
  std::vector<OrderByUnit *> order_units_;
};