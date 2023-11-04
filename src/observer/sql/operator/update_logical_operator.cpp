#include "update_logical_operator.h"

UpdateLogicalOperator::UpdateLogicalOperator(
    Table *table, std::vector<const FieldMeta *> field_metas, std::vector<std::unique_ptr<Expression>> &expr_list
)
    : table_(table),
      field_metas_(std::move(field_metas)),
      expr_list_(std::move(expr_list))
{}
