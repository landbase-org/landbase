#include "update_physical_operator.h"
#include "event/sql_debug.h"
#include "storage/index/index.h"
#include "storage/trx/trx.h"

RC UpdatePhysicalOperator::open(Trx *trx)
{
  if (children_.empty()) {
    return RC::SUCCESS;
  }

  std::unique_ptr<PhysicalOperator> &child = children_[0];
  RC                                 rc    = child->open(trx);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to open child operator: %s", strrc(rc));
    return rc;
  }

  trx_ = trx;

  auto &indexs = table_->get_indexes();
  for (auto &index : indexs) {
    if (index->is_unique()) {
      auto &index_field_metas = index->field_metas();
      for (auto &index_field_meta : index_field_metas) {
        for (int i = 0; i < field_metas_.size(); ++i) {
          if (index_field_meta.offset() == field_metas_[i]->offset() && !values_[i]->is_null()) {
            has_unique_index_ = true;
            return RC::SUCCESS;
          }
        }
      }
    }
  }

  return RC::SUCCESS;
}

RC UpdatePhysicalOperator::next()
{
  RC rc = RC::SUCCESS;
  if (children_.empty()) {
    return RC::RECORD_EOF;
  }

  auto &child = children_[0];
  while (RC::SUCCESS == (rc = child->next())) {
    if (has_unique_index_) {
      rc = child->next();
      if (rc == RC::SUCCESS) {
        sql_debug("update multi record with unique index");
        return RC::RECORD_DUPLICATE_KEY;
      }
    }

    Tuple *tuple = child->current_tuple();
    if (nullptr == tuple) {
      LOG_WARN("failed to get current record: %s", strrc(rc));
      return rc;
    }

    RowTuple *row_tuple = dynamic_cast<RowTuple *>(tuple);
    if (row_tuple == nullptr) {
      sql_debug("failed to cast tuple to row tuple");
      return RC::INTERNAL;
    }
    Record &record = row_tuple->record();

    rc = trx_->update_record(table_, record, field_metas_, values_);

    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to update record: %s", strrc(rc));
      return rc;
    }
  }

  return RC::RECORD_EOF;
}

RC UpdatePhysicalOperator::close()
{
  if (!children_.empty()) {
    return children_[0]->close();
  }
  return RC::SUCCESS;
}
