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
  if (children_.size() > 1) {
    LOG_WARN("Order should only have one child -> TableScan/Join");
    return RC::INTERNAL;
  }

  return children_[0]->open(trx);
}

RC AggrePhysicalOperator::next()
{
  RC                rc   = RC::SUCCESS;
  PhysicalOperator *oper = children_.front().get();

  return oper->next();
}

RC AggrePhysicalOperator::close()
{
  children_[0]->close();
  return RC::SUCCESS;
}

Tuple *AggrePhysicalOperator::current_tuple() { return children_[0]->current_tuple(); }
