#include "tuple.h"
#include "common/log/log.h"
#include "sql/expr/expression.h"
#include "sql/parser/parse_defs.h"
#include "sql/parser/value.h"
#include "storage/field/field.h"
#include <cstddef>

/***********************
 *   AGGREGATIONTUPLE  *
 ***********************/
RC AggregationTuple::cell_at(int index, Value &cell) const  // 在expressions_中的第i个数据
{
  if (tuple_ == nullptr) {
    return RC::EMPTY;
  }
  return tuple_->cell_at(index, cell);
}

RC AggregationTuple::find_cell(const TupleCellSpec &spec, Value &cell) const
{
  if (nullptr == tuple_) {
    LOG_INFO("empty table");
    // return RC::TUPLE_NOT_EXIST;
  }

  // 当前只可能在aggre中找到
  if (AggreType::AGGRE_NONE != spec.aggre_type()) {
    for (size_t i = 0; i < aggre_exprs_->size(); i++) {
      const auto &expr = (*aggre_exprs_)[i];
      if (spec == *expr) {
        cell = aggre_resluts_[i];
        LOG_INFO("Field is found in aggre_exprs");
        return RC::SUCCESS;
      }
    }
  }
  return RC::NOTFOUND;

  for (size_t i = 0; i < field_exprs_.size(); i++) {
    auto &expr = field_exprs_[i];
    if (spec == expr.field()) {
      cell = field_results_[i];
      LOG_INFO("Field is found from field_exprs");
      return RC::SUCCESS;
    }
  }

  return RC::NOTFOUND;
}

void AggregationTuple::init(std::vector<std::unique_ptr<AggreExpression>> *aggre_exprs)
{
  count_ = 0;
  size_  = aggre_exprs->size();
  counts_.resize(size_);
  all_null_.resize(size_);
  aggre_resluts_.resize(size_);
  field_results_.resize(size_);
  field_exprs_.resize(size_);
  aggre_exprs_ = aggre_exprs;
  // 设置result的默认值
  for (size_t i = 0; i < size_; ++i) {
    if ((*aggre_exprs_)[i]->get_aggre_type() == AGGRE_COUNT_ALL ||
        (*aggre_exprs_)[i]->get_aggre_type() == AGGRE_COUNT) {
      aggre_resluts_[i].set_int(0);
    }
  }
}

void AggregationTuple::do_aggregation_begin()
{
  // 初始化count_和all_null_
  count_ = 0;
  for (size_t i = 0; i < size_; i++) {
    all_null_[i] = true;
    counts_[i]   = 0;
  }
}

void AggregationTuple::do_aggregation()
{
  count_++;

  Value cur_value;
  for (size_t i = 0; i < size_; i++) {
    const auto &expr = (*aggre_exprs_)[i];
    expr->get_value(*tuple_, cur_value);
    AggreType aggre_type = expr->get_aggre_type();

    if (cur_value.is_null()) {
      continue;
    }
    // 不为null
    counts_[i]++;
    if (AggreType::AGGRE_COUNT_ALL == aggre_type || AggreType::AGGRE_COUNT == aggre_type) {
      continue;
    }

    all_null_[i] = false;
    if (aggre_resluts_[i].is_null()) {
      if (AggreType::AGGRE_AVG == aggre_type ||
          AggreType::AGGRE_SUM == aggre_type) {  // 如果是AGGRE_AVG或者AGGRE_SUM的话，应该初始话为0
        Value tmp_value;
        if (cur_value.attr_type() == INTS) {
          tmp_value.set_int(0);
        } else if (cur_value.attr_type() == FLOATS) {
          tmp_value.set_float(0);
        } else {
          tmp_value.set_float(0);
          LOG_WARN("Invalid attr Type");
        }
        aggre_resluts_[i] = tmp_value;
      } else {  // 其他类型（MAX，MIN）初始话为数据的本身
        aggre_resluts_[i] = cur_value;
      }
    }

    auto &res = aggre_resluts_[i];
    switch (expr->get_aggre_type()) {
      case AGGRE_MAX: res = std::max(res, cur_value); break;
      case AGGRE_MIN: res = std::min(res, cur_value); break;
      case AGGRE_AVG:
      case AGGRE_SUM: res = res + cur_value; break;
      default: LOG_ERROR("Not support AggreType"); break;
    }
  }
}
void AggregationTuple::do_aggregation_end()
{
  for (size_t i = 0; i < size_; i++) {
    const auto &expr       = (*aggre_exprs_)[i];
    Value      &res        = aggre_resluts_[i];  // 最后处理结果
    AggreType   aggre_type = expr->get_aggre_type();

    // 如果这列的所有数据都是NULL且不为COUNT, 那么当前列的结果为NULL
    if (all_null_[i] && AggreType::AGGRE_COUNT_ALL != aggre_type && AggreType::AGGRE_COUNT != aggre_type) {
      res.set_null();
      continue;
    }

    switch (aggre_type) {
      case AGGRE_COUNT: res.set_int(counts_[i]); break;
      case AGGRE_COUNT_ALL: res.set_int(count_); break;  // 包含为空的数据
      case AGGRE_AVG: {
        int tot = counts_[i];
        if (res.attr_type() == INTS) {
          int val = res.get_int();
          if (val % tot == 0) {
            res.set_int(val / tot);
          } else {
            res.set_float(1. * val / tot);
          }
        } else {
          res.set_float(res.get_float() / tot);
        }
      } break;
      default: break;  // 其他类型不需要做处理
    }
  }
}