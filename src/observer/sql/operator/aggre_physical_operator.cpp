#include "aggre_physical_operator.h"
#include "common/log/log.h"
#include "common/rc.h"
#include "sql/expr/tuple.h"
#include "sql/expr/tuple_cell.h"
#include "sql/parser/comp_op.h"
#include "sql/parser/value.h"
#include "sql/stmt/groupby_stml.h"
#include <bits/iterator_concepts.h>
#include <future>
#include <memory>

RC AggrePhysicalOperator::open(Trx *trx)
{
  if (children_.size() != 1) {
    return RC::SUCCESS;
  }

  return children_[0]->open(trx);
}

RC AggrePhysicalOperator::next()
{
  if (is_record_eof_) {
    return RC::RECORD_EOF;
  }

  // select count(*) from table where 1=0;
  // 此时children_是空的，直接返回结果
  if (children_.empty()) {
    is_record_eof_ = true;
    return RC::SUCCESS;
  }

  Tuple            *son_tuple     = nullptr;
  RC                rc            = RC::SUCCESS;
  PhysicalOperator *oper          = children_.front().get();
  const auto       &groupby_units = groupby_stmt_->groupby_units();

  if (!is_started_) {
    rc = oper->next();
    if (rc != RC::SUCCESS) {
      LOG_INFO("aggregation a empty table");
      is_record_eof_ = true;
      return RC::SUCCESS;
    }
    tuple_.set_tuple(oper->current_tuple());  // 初始化alue
    son_tuple = oper->current_tuple();
    tuple_.update_field_values();
    is_started_ = true;

    for (const auto &unit : *groupby_units) {
      Value value;
      unit->expr()->get()->get_value(*son_tuple, value);
      values_.push_back(value);
    }
  }

  while (true) {
    // 只有当是开始的时候或则不是新group的时候才获取下一个组
    // 因为如果是新的组， 那么上一组的最后一次获取的数据为当前组的第一行数据， 不需要获取新数据
    if (!is_new_group_) {
      rc = oper->next();
      if (rc != RC::SUCCESS) {
        LOG_INFO("aggregation a empty table");
        break;
      }
      tuple_.set_tuple(oper->current_tuple());
    }
    son_tuple = oper->current_tuple();

    if (is_new_group_) {  // 如果是新的group要初始化aggre数据
      tuple_.do_aggregation_begin();
      tuple_.update_field_values();
      is_new_group_ = false;
    }

    // 首先需要判断当前是否是新的组别
    for (size_t i = 0; i < groupby_units->size(); i++) {
      const std::unique_ptr<GroupByUnit> &unit = (*groupby_units)[i];
      Value                               value;
      unit->expr()->get()->get_value(*son_tuple, value);
      if (value != values_[i]) {  // 值不相等， 是新的group
        values_[i]    = value;
        is_new_group_ = true;
      }
    }
    if (is_new_group_) {
      tuple_.do_aggregation_end();
      return rc;
    }

    // 做聚合运算
    tuple_.do_aggregation();
  }

  if (RC::RECORD_EOF == rc) {  // 最后一次
    is_record_eof_ = true;
    if (is_started_) {  // 如果没有开始则表名当前表为空表
      tuple_.do_aggregation_end();
    }
    return RC::SUCCESS;
  }

  return rc;
}

RC AggrePhysicalOperator::close()
{
  // 聚合是有可能没有子opererator的，例如select count(*) from table where 1=0;
  // 这种情况下，children_是空的
  if (children_.empty()) {
    return RC::SUCCESS;
  }
  children_[0]->close();
  return RC::SUCCESS;
}

Tuple *AggrePhysicalOperator::current_tuple() { return &tuple_; }
