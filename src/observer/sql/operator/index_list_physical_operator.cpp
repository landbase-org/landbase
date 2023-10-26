#include "index_list_physical_operator.h"

IndexListPhysicalOperator::IndexListPhysicalOperator(std::string table_name, const std::vector<Index *> &indexes)
    : indexes_(indexes),
      table_name_(table_name)
{
  cur_index_idx_  = 0;
  cur_fields_idx_ = 0;
  started_        = false;
}

PhysicalOperatorType IndexListPhysicalOperator::type() const { return PhysicalOperatorType::INDEX_LIST; }

RC IndexListPhysicalOperator::open(Trx *) { return RC::SUCCESS; }

RC IndexListPhysicalOperator::next()
{
  if (indexes_.empty()) {
    return RC::RECORD_EOF;
  }
  if (!started_) {
    started_ = true;
  } else if (++cur_fields_idx_ == indexes_[cur_index_idx_]->field_metas().size()) {
    // 当前field_meta约越界了 需要证据爱index_idx
    if (++cur_index_idx_ == indexes_.size()) {
      return RC::RECORD_EOF;
    }
    cur_fields_idx_ = 0;
  }
  return RC::SUCCESS;
}

RC IndexListPhysicalOperator::close() { return RC::SUCCESS; }

Tuple *IndexListPhysicalOperator::current_tuple()  // 获取当前迭代器中的结果
{
  if (cur_index_idx_ == indexes_.size()) {
    return nullptr;
  }

  vector<Value> cells;
  const auto   &index_meta = indexes_[cur_index_idx_]->index_meta();
  const auto   &field_meta = indexes_[cur_index_idx_]->field_metas()[cur_fields_idx_];
  cells.push_back(Value(table_name_.c_str()));                    // 表名
  cells.push_back(Value(!index_meta.is_unique()));                // Non_unique
  cells.push_back(Value(index_meta.name()));                      // 索引名称
  cells.push_back(Value(static_cast<int>(cur_fields_idx_ + 1)));  // 索引序号, 当前是单索引, 默认为1
  cells.push_back(Value(indexes_[cur_index_idx_]->field_metas()[cur_fields_idx_].name()));  // 索引的列表名称
  tuple_.set_cells(cells);

  return &tuple_;
}