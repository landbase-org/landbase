#include "order_physical_operator.h"
#include "common/log/log.h"
#include "common/rc.h"
#include "event/sql_debug.h"
#include "sql/expr/tuple.h"
#include "sql/expr/tuple_cell.h"
#include "sql/parser/comp_op.h"
#include "sql/parser/value.h"
#include <bits/iterator_concepts.h>
#include <future>
#define THRESHOULD 1000
// #define PARREL

/**
 * @brief 多线程排序
 *
 * @param begin
 * @param end
 * @param rule
 */
void p_sort(
    std::vector<Tuple *>::iterator begin, std::vector<Tuple *>::iterator end,
    std::function<bool(Tuple *const &left, Tuple *const &right)> rule
)
{
#ifdef PARREL
  if (end - begin < THRESHOULD) {
    std::sort(begin, end, rule);
    return;
  }
  int  mid   = (end - begin) >> 1;
  auto front = std::async(std::launch::async, p_sort, begin, begin + mid, rule);
  auto back  = std::async(std::launch::async, p_sort, begin + mid + 1, end, rule);
  front.wait();
  back.wait();
  std::inplace_merge(begin, begin + mid, end, rule);
  return;
#else
  std::sort(begin, end, rule);
#endif
}

RC OrderPhysicalOperator::initialize()
{
  // 取出数据
  bool got_rules = false;
  while (RC::SUCCESS == children_[0]->next()) {
    Tuple *tup_ptr = children_[0]->current_tuple();
    if (tup_ptr == nullptr) {
      sql_debug("Faild to get Row/Join");
      return RC::INTERNAL;
    }
    ordered_tuples_.emplace_back(tup_ptr);
  }

  // 排序
  p_sort(ordered_tuples_.begin(), ordered_tuples_.end(), comprule);

  iterator_  = ordered_tuples_.begin();
  is_inited_ = true;

  return RC::SUCCESS;
}

OrderPhysicalOperator::~OrderPhysicalOperator()
{
  order_rules.clear();
  order_reqs.clear();
  ordered_tuples_.clear();
}

RC OrderPhysicalOperator::open(Trx *trx)
{
  if (children_.size() > 1) {
    sql_debug("Order should only have one child -> TableScan/Join");
    return RC::INTERNAL;
  }

  return children_[0]->open(trx);
}

RC OrderPhysicalOperator::next()
{

  if (!is_inited_) {
    RC rc = RC::SUCCESS;
    rc    = initialize();
    if (RC::SUCCESS != rc) {
      sql_debug("Error at Order-init");
      return rc;
    }
  } else {
    if (ordered_tuples_.empty()) {
      return RC::RECORD_EOF;
    } else {
      iterator_++;
      return iterator_ == ordered_tuples_.end() ? RC::RECORD_EOF : RC::SUCCESS;
    }
  }
  // Return Default Value
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
  if (ordered_tuples_.empty()) {
    return nullptr;
  }
  return *iterator_;
}

void OrderPhysicalOperator::print_infor()
{
  for (auto tuple : ordered_tuples_) {
    Value  temp;
    string res;
    for (int i{1}; i < tuple->cell_num(); i++) {
      tuple->cell_at(i, temp);
      res += temp.get_string();
    }
    LOG_DEBUG("%s", res.c_str());
  }
}
