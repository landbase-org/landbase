#pragma once

#include "sql/operator/logical_operator.h"

/**
 * @brief 逻辑算子，用于执行update语句
 * @ingroup LogicalOperator
 */
class UpdateLogicalOperator : public LogicalOperator
{
public:
  UpdateLogicalOperator(Table *table, std::vector<const FieldMeta *> field_metas, std::vector<const Value *> values);
  virtual ~UpdateLogicalOperator() = default;

  LogicalOperatorType type() const override { return LogicalOperatorType::UPDATE; }
  Table              *table() const { return table_; }
  const auto         &field_metas() const { return field_metas_; }
  const auto         &values() const { return values_; }

private:
  Table                         *table_ = nullptr;
  std::vector<const FieldMeta *> field_metas_;
  std::vector<const Value *>     values_;
};
