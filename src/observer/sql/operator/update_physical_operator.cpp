#include "update_physical_operator.h"
#include "event/sql_debug.h"
#include "sql/expr/sub_query_expr.h"
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

  for (auto &expr : expr_list_) {
    switch (expr->type()) {
      case ExprType::SUBQUERY: {
        auto sub_query_expr = static_cast<SubQueryExpr *>(expr.get());
        rc                  = sub_query_expr->executor(trx);
        if (rc != RC::SUCCESS) {
          sql_debug("failed to execute sub query expr");
          return rc;
        }
      } break;
      case ExprType::VALUE: {
      } break;
      default: {
        sql_debug("invalid expr type: %d", expr->type());
      } break;
    }
  }

  for (auto &expr : expr_list_) {
    switch (expr->type()) {
      case ExprType::VALUE: {
        auto value_expr = static_cast<ValueExpr *>(expr.get());
        value_list_.emplace_back(value_expr->get_value());
      } break;
      case ExprType::SUBQUERY:
      case ExprType::VALUELIST: {
        auto value_list_expr = static_cast<ValueListExpr *>(expr.get());
        auto value_list      = value_list_expr->value_list();
        if (value_list.empty()) {
          this->value_list_.emplace_back(Value());
        } else if (value_list.size() != 1) {
          invalid_sub_query_ = true;
          this->value_list_.emplace_back(value_list.front());
        } else {
          this->value_list_.emplace_back(value_list.front());
        }
      } break;
      default: {
        sql_debug("invalid expr type: %d", expr->type());
      } break;
    }
  }

  // 检查是否有唯一索引
  auto &indexs = table_->get_indexes();
  for (auto &index : indexs) {
    if (index->is_unique()) {
      auto &index_field_metas = index->field_metas();
      for (auto &index_field_meta : index_field_metas) {
        for (int i = 0; i < field_metas_.size(); ++i) {
          if (index_field_meta.offset() == field_metas_[i]->offset()) {
            if (value_list_[i].attr_type() == NULLS) {
              has_unique_index_ = true;
              return RC::SUCCESS;
            }
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
    if (invalid_sub_query_) {
      sql_debug("invalid sub query");
      return RC::INTERNAL;
    }

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
    // 待更新的记录
    Record &record = row_tuple->record();
    // 更新后的记录
    auto &table_meta  = table_->table_meta();
    int   record_size = table_meta.record_size();
    auto  new_data    = new char[record_size];
    memcpy(new_data, record.data(), record_size);  // 新的数据
    Record new_record;
    new_record.set_data(new_data, record_size);
    new_record.set_rid(record.rid());

    // 更新字段
    // 从parser阶段开始 field_metas 和 values 的数量一定一直是一致的
    // null 值的处理
    auto       bitmap = table_->table_meta().bitmap_of_null_field(new_record.data());
    const auto size   = field_metas_.size();
    for (int i = 0; i < size; ++i) {
      int field_index = table_meta.field_index(field_metas_[i]);
      if (value_list_[i].is_null()) {
        bitmap.set_bit(field_index);
      } else {
        bitmap.clear_bit(field_index);
        new_record.set_value(field_metas_[i], &value_list_[i]);
      }
    }

    rc = trx_->update_record(table_, record, new_record);

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
