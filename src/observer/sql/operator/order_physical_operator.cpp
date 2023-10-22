#include "order_physical_operator.h"
#include "common/log/log.h"
#include "common/rc.h"
#include "sql/expr/tuple.h"
#include "sql/expr/tuple_cell.h"
#include "sql/parser/comp_op.h"
#include "sql/parser/value.h"
#include <algorithm>
#include <functional>

RC OrderPhysicalOperator::get_inited()
{
  // get all the vector<Value>
  bool got_rules = false;
  while (RC::SUCCESS == children_[0]->next()) {
    Tuple *tup_ptr = children_[0]->current_tuple();
    if (tup_ptr == nullptr) {
      LOG_WARN("Order's child has no tuple");
      return RC::INTERNAL;
    }
    if (!got_rules) {
      auto tuple_spec = dynamic_cast<ProjectTuple *>(tup_ptr)->get_tuple_cell_spec();
      for (auto unit : order_units_) {
        for (size_t idx{0}; idx < tuple_spec.size(); idx++) {
          if (strcmp(tuple_spec[idx]->table_name(), unit->get_table()->name()) == 0 &&
              strcmp(tuple_spec[idx]->field_name(), unit->get_fields()->name()) == 0) {
            ord_idx_asc.emplace_back(make_pair(idx, unit->get_asc()));
          }
        }
      }
      got_rules = true;
    }
    ValueGrp *val_vec = new ValueGrp();
    Value     temp;
    for (int i{0}; i < tup_ptr->cell_num(); i++) {
      tup_ptr->cell_at(i, temp);
      val_vec->emplace_back(temp);
    }
    req_tuples_.emplace_back(val_vec);
  }
  // order the ValueGrp with order rules
  std::function<bool(ValueGrp * &left, ValueGrp * &right)> cmprule = [&](ValueGrp *&left, ValueGrp *&right) -> bool {
    for (auto [idx, asc] : ord_idx_asc) {
      if (asc) {
        // 升序
        if ((*left)[idx].compare(CompOp::LESS_THAN, (*right)[idx]))
          return true;
        else if ((*left)[idx].compare(CompOp::GREAT_THAN, (*right)[idx]))
          return false;
      } else {
        // 降序
        if ((*left)[idx].compare(CompOp::GREAT_THAN, (*right)[idx]))
          return true;
        else if ((*left)[idx].compare(CompOp::LESS_THAN, (*right)[idx]))
          return false;
      }
    }
    // return a default value
    return false;
  };

  sort(req_tuples_.begin(), req_tuples_.end(), cmprule);

  for (auto unit : order_units_) {}
  ordered_iter_ = req_tuples_.begin();
  is_inited_    = true;

  return RC::SUCCESS;
}

OrderPhysicalOperator::~OrderPhysicalOperator()
{
  for (auto order_unit : order_units_) {
    delete order_unit;
  }
  order_units_.clear();
  for (auto valgrp : req_tuples_) {
    valgrp->clear();
    delete valgrp;
  }
  req_tuples_.clear();
  ord_idx_asc.clear();
}

RC OrderPhysicalOperator::open(Trx *trx)
{
  if (children_.size() > 1) {
    LOG_WARN("order should only have one child -> project");
    return RC::INTERNAL;
  }

  return children_[0]->open(trx);
}

RC OrderPhysicalOperator::next()
{
  if (is_inited_) {
    if (req_tuples_.empty()) {
      return RC::RECORD_EOF;
    } else {
      ordered_iter_++;
      return ordered_iter_ != req_tuples_.end() ? RC::SUCCESS : RC::RECORD_EOF;
    }
  }
  // get inited
  RC rc = get_inited();
  if (RC::SUCCESS != rc) {
    LOG_WARN("Error at get data and sort");
    return RC::INTERNAL;
  }
  return RC::SUCCESS;
}

RC OrderPhysicalOperator::close()
{
  if (!children_.empty()) {
    return children_[0]->close();
  }
  return RC::SUCCESS;
}

Tuple *OrderPhysicalOperator::current_tuple()
{
  // new a ValueListTuple
  ValueListTuple *ret = new ValueListTuple();
  ret->set_cells(*(*ordered_iter_));
  return ret;
}

void OrderPhysicalOperator::print_infor()
{
  for (auto valgrp : req_tuples_) {
    std::string line;
    for (auto &item : *valgrp) {
      line += item.to_string();
    }
    LOG_INFO("ORDERBY:%s", line.c_str());
  }
}
