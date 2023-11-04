#include "aggre_physical_operator.h"
#include "common/log/log.h"
#include "common/rc.h"
#include "sql/expr/tuple.h"
#include "sql/expr/tuple_cell.h"
#include "sql/parser/comp_op.h"
#include "sql/parser/value.h"
#include <bits/iterator_concepts.h>
#include <future>

RC AggrePhysicalOperator::open(Trx *trx)
{
  if (children_.size() != 1) {
    LOG_WARN("predicate operator must has one child");
    return RC::INTERNAL;
  }

  return children_[0]->open(trx);
}

RC AggrePhysicalOperator::next()
{
  if (is_record_eof) {
    return RC::RECORD_EOF;
  }

  RC                rc   = RC::SUCCESS;
  PhysicalOperator *oper = children_.front().get();

  while (RC::SUCCESS == (rc = oper->next())) {
    tuple_.set_tuple(oper->current_tuple());  // 将当前列放在tuple_中
    if (!is_started_) {
      tuple_.do_aggregation_begin();
      is_started_ = true;
    }

    // 做聚合运算
    tuple_.do_aggregation();
  }

  if (RC::RECORD_EOF == rc) {
    is_record_eof = true;
    if (!is_started_) {  // 如果没有开始则表名当前表为空表
      tuple_.do_aggregation_end();
    }
    return RC::SUCCESS;
  }

  return rc;
}

RC AggrePhysicalOperator::close()
{
  children_[0]->close();
  return RC::SUCCESS;
}

Tuple *AggrePhysicalOperator::current_tuple() { return &tuple_; }
