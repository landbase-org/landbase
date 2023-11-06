#pragma once

#include "event/sql_debug.h"
#include "physical_operator.h"
#include "sql/expr/expression.h"
#include "sql/expr/tuple.h"
#include "sql/parser/value.h"
#include "sql/stmt/groupby_stml.h"
#include "sql/stmt/order_by_stmt.h"
#include "storage/field/field.h"
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
  AggrePhysicalOperator(
      std::vector<std::unique_ptr<AggreExpression>> &&aggre_exprs,
      std::vector<std::unique_ptr<FieldExpr>> &&field_exprs, GroupByStmt *groupby_stmt
  )
      : groupby_stmt_(groupby_stmt)
  {
    // 初始化aggre_tuple
    tuple_.init(std::move(aggre_exprs), std::move(field_exprs));
  }
  virtual ~AggrePhysicalOperator() = default;

  PhysicalOperatorType type() const override { return PhysicalOperatorType::AGGREGATION; }
  RC                   open(Trx *trx) override;
  RC                   next() override;
  RC                   close() override;
  Tuple               *current_tuple() override;

private:
  bool               is_started_{false};
  bool               is_record_eof_{false};
  bool               is_new_group_{true};
  GroupByStmt       *groupby_stmt_;
  AggregationTuple   tuple_;
  std::vector<Value> values_;  // 当前列表的数据用于比较数据是否相同
};