#include "update_logical_operator.h"

UpdateLogicalOperator::UpdateLogicalOperator(
    Table *table, std::vector<const FieldMeta *> field_metas, std::vector<const Value *> values
)
    : table_(table),
      field_metas_(std::move(field_metas)),
      values_(std::move(values))
{}
