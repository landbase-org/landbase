#pragma once

#include "physical_operator.h"
#include "sql/expr/tuple.h"
#include "sql/parser/value.h"
#include "sql/stmt/order_by_stmt.h"
#include "storage/trx/trx.h"
#include <utility>
#include <vector>

class OrderByStmt;

/**
 * @brief 进行排序的物理算子
 * @ingroup PhysicalOperator
 * @details 以vector<Value>的形式深拷贝取出Project子算子的所有Tuple，按照需求Sort之后，
 *          建一个ValueListTuple，返回current_tuple。目前使用STL的Sort
 */
class OrderPhysicalOperator : public PhysicalOperator
{
public:
  explicit OrderPhysicalOperator(std::vector<OrderByUnit *> order_units) : order_units_(order_units) {}

  virtual ~OrderPhysicalOperator();

  PhysicalOperatorType type() const override { return PhysicalOperatorType::ORDER_BY; }

  RC open(Trx *trx) override;
  RC next() override;
  RC close() override;

  Tuple *current_tuple() override;
  void   print_infor();

private:
  RC get_inited();

public:
  using ValueGrp = std::vector<Value>;

private:
  bool                                  is_inited_ = false;  // 是否已经初始化
  std::vector<std::pair<int, bool>>     ord_idx_asc;         // 表示order的第idx个cell是否为ASC排序
  std::vector<OrderByUnit *>            order_units_;
  std::vector<ValueGrp *>               ori_data;
  std::vector<ValueListTuple>::iterator ordered_iter_;
  std::vector<ValueListTuple>          *ordered_tuple;
};