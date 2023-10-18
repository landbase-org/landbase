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
  UpdatePhysicalOperator(Table *table, std::vector<const FieldMeta *> field_metas, std::vector<const Value *> values)
      : table_(table),
        field_metas_(std::move(field_metas)),
        values_(std::move(values))
  {}

  virtual ~UpdatePhysicalOperator() = default;

  PhysicalOperatorType type() const override { return PhysicalOperatorType::UPDATE; }

  RC open(Trx *trx) override;
  RC next() override;
  RC close() override;

  Tuple *current_tuple() override { return nullptr; }

private:
  Table                         *table_ = nullptr;
  std::vector<const FieldMeta *> field_metas_;
  std::vector<const Value *>     values_;
  Trx                           *trx_ = nullptr;
};
