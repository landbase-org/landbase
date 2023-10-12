#include "update_physical_operator.h"
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

  return RC::SUCCESS;
}

// TODO: 将更新交于事务处理，目前事务不完善，暂时交由物理操作处理
RC UpdatePhysicalOperator::next()
{
  RC rc = RC::SUCCESS;
  if (children_.empty()) {
    return RC::RECORD_EOF;
  }

  // 找到所有和该字段有关的索引
  auto indexs = table_->find_indexes_by_field(field_meta_->name());

  PhysicalOperator *child = children_[0].get();
  while (RC::SUCCESS == (rc = child->next())) {
    Tuple *tuple = child->current_tuple();
    if (nullptr == tuple) {
      LOG_WARN("failed to get current record: %s", strrc(rc));
      return rc;
    }

    RowTuple *row_tuple = static_cast<RowTuple *>(tuple);
    Record   &record    = row_tuple->record();

    // 删除之前的索引
    if (!indexs.empty()) {
      for (auto index : indexs) {
        rc = index->delete_entry(record.data(), &record.rid());
        if (rc != RC::SUCCESS) {
          LOG_WARN("failed to delete index entry; table: %s, index: %s.", table_->name(), index->index_meta().name());
          return rc;
        }
      }
    }

    // 更新字段
    record.set_value(field_meta_->offset(), value_);

    // 插入新的索引
    if (!indexs.empty()) {
      for (auto index : indexs) {
        rc = index->insert_entry(record.data(), &record.rid());
        if (rc != RC::SUCCESS) {
          LOG_WARN("failed to delete index entry; table: %s, index: %s.", table_->name(), index->index_meta().name());
          return rc;
        }
      }
    }

    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to delete record: %s", strrc(rc));
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
