#pragma once
#include "sql/expr/expression.h"
#include "sql/operator/physical_operator.h"

class SubQueryExpr : public ValueListExpr
{
public:
  ExprType type() const override { return ExprType::SUBQUERY; }
  AttrType value_type() const override { return value_list_.front().attr_type(); }
  RC       try_get_value(Value &value) const override
  {
    if (value_list_.size() == 1) {
      value = value_list_.front();
      return RC::SUCCESS;
    }
    sql_debug("ValueListExpr::value_list_ size is %d", value_list_.size());
    return RC::FAILURE;
  }
  RC executor(Trx *trx) { sql_debug("unimplemented"); }

private:
  Trx                              *trx_;
  bool                              finished = false;
  std::unique_ptr<PhysicalOperator> physical_operator_;
};