#pragma once

#include "sql/operator/physical_operator.h"

class Trx;
class UpdateStmt;

/**
 * @brief 物理算子，更新
 * @ingroup PhysicalOperator
 */
class UpdatePhysicalOperator : public PhysicalOperator
{
public:
  UpdatePhysicalOperator(
      Table *table, std::vector<const FieldMeta *> field_metas, std::vector<std::unique_ptr<Expression>> &expr_list
  )
      : table_(table),
        field_metas_(std::move(field_metas)),
        expr_list_(std::move(expr_list))
  {}

  virtual ~UpdatePhysicalOperator() = default;

  PhysicalOperatorType type() const override { return PhysicalOperatorType::UPDATE; }

  RC open(Trx *trx) override;
  RC next() override;
  RC close() override;

  Tuple *current_tuple() override { return nullptr; }

private:
  Trx                                     *trx_   = nullptr;
  Table                                   *table_ = nullptr;
  std::vector<const FieldMeta *>           field_metas_;
  std::vector<std::unique_ptr<Expression>> expr_list_;  // 用于存放valueexpr或者subqueryexpr
  std::vector<Value>                       value_list_;
  bool                                     invalid_value_list_ = false;
  bool                                     has_unique_index_   = false;
};
