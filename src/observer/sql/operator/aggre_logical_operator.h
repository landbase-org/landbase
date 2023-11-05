#pragma once
#include "logical_operator.h"
#include "sql/expr/expression.h"
#include "sql/stmt/groupby_stml.h"
#include "sql/stmt/order_by_stmt.h"
#include "storage/field/field.h"
#include <memory>
/**
 * @brief sort 表示对表进行排序
 * @ingroup LogicalOperator
 */

class AggreLogicalOperator : public LogicalOperator
{
public:
  AggreLogicalOperator(
      std::vector<std::unique_ptr<AggreExpression>> &&aggre_expre,
      std::vector<std::unique_ptr<FieldExpr>> &&field_exprs, GroupByStmt *groupby_stmt = nullptr
  )
      : aggre_exprs_(std::move(aggre_expre)),
        field_exprs_(std::move(field_exprs)),
        groupby_stmt_(groupby_stmt)
  {}

  virtual ~AggreLogicalOperator() {}
  LogicalOperatorType                            type() const override { return LogicalOperatorType::AGGREGATION; }
  std::vector<std::unique_ptr<AggreExpression>> &aggre_exprs() { return aggre_exprs_; }
  std::vector<std::unique_ptr<FieldExpr>>       &field_exprs() { return field_exprs_; }
  GroupByStmt                                   *groupby_stmt() const { return groupby_stmt_; }

private:
  std::vector<std::unique_ptr<AggreExpression>> aggre_exprs_;
  std::vector<std::unique_ptr<FieldExpr>>       field_exprs_;
  GroupByStmt                                  *groupby_stmt_{nullptr};
};