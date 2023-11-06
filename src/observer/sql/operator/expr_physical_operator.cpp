#include "sql/operator/expr_physical_operator.h"
#include "sql/expr/tuple.h"
#include "sql/parser/value.h"
#include <vector>

// 打开子算子 --> 扫表算子
RC ExprPhysicalOperator::open(Trx *trx)
{
  if (children_.empty()) {
    value_only = true;
    return RC::SUCCESS;
  } else {
    return children_[0]->open(trx);
  }
}

// 子算子的下一个 / 或者只有一个常值表达式
RC ExprPhysicalOperator::next()
{
  if (children_.empty()) {
    if (!value_used) {
      value_used = true;
      return RC::SUCCESS;
    } else {
      return RC::RECORD_EOF;
    }
  } else {
    return children_[0]->next();
  }
}

// 关闭子算子？
RC ExprPhysicalOperator::close() { return RC::SUCCESS; }

// 返回子算子加工过后的tuple / 或者返回常值表达式的值
// EXPRESSION：表达式出现在where条件时要考虑怎么做
Tuple *ExprPhysicalOperator::current_tuple()
{
  // TODOX: 开始计算返回值
  if (value_only) {
    tuple_ = new ExpressionTuple(exprs_);
    return tuple_;
  } else {
    // TODOX: 在此处是否需要把所有的field表达式的值拿到
    Tuple *child_tuple = children_.front()->current_tuple();
    tuple_             = new ExpressionTuple(exprs_);
    // tuple_->set_tuple(child_tuple);
    return tuple_;
  }
}