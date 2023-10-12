#include "update_logical_operator.h"

UpdateLogicalOperator::UpdateLogicalOperator(Table *table, const FieldMeta *field_meta, const Value *value)
    : table_(table),
      field_meta_(field_meta),
      value_(value)
{}
