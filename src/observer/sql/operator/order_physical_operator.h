#pragma once

#include "event/sql_debug.h"
#include "physical_operator.h"
#include "sql/expr/tuple.h"
#include "sql/parser/value.h"
#include "sql/stmt/order_by_stmt.h"
#include "storage/trx/trx.h"

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
  explicit OrderPhysicalOperator(std::vector<OrderByUnit *> order_units) : order_reqs(order_units)
  {
    // 拿到排序字段
    for (auto unit : order_units) {
      TupleCellSpec temp(unit->get_table()->name(), unit->get_fields()->name());
      order_rules.emplace_back(temp, unit->get_asc());
    }
    // 拿到比较规则
    comprule = [&](Tuple *const &left, Tuple *const &right) -> bool {
      RC    rc = RC::SUCCESS;
      Value vleft, vright;

      for (auto [spec, asc] : order_rules) {
        rc = left->find_cell(spec, vleft);
        if (rc != RC::SUCCESS) {
          sql_debug("ORDER: get comp left value failed");
        }
        rc = right->find_cell(spec, vright);
        if (rc != RC::SUCCESS) {
          sql_debug("ORDER: get comp right value failed");
        }

        auto comp_result = Value::compare_value(vleft, vright);

        switch (comp_result) {
          case EQUAL_TO: {
            continue;
          } break;
          case LESS_THAN: {
            return asc;
          } break;
          case GREAT_THAN: {
            return !asc;
          } break;
          default: {
            sql_debug(
                "Error at compare value,left: %s, right: %s", vleft.to_string().c_str(), vright.to_string().c_str()
            );
            continue;
          } break;
        }
      }
      // return Default Value
      return false;
    };
  }

  virtual ~OrderPhysicalOperator();

  PhysicalOperatorType type() const override { return PhysicalOperatorType::ORDER_BY; }

  RC open(Trx *trx) override;
  RC next() override;
  RC close() override;

  Tuple *current_tuple() override;
  void   print_infor();

  /**
   * @brief     // here is may a JoinTuple or a RowTuple
      // the idea before: get its data here need tell whether is RowTuple
      // now change the order of tuples here don't need to tell Tuple's type
      // projecttuple -> childtuple
      // if Rowtuple -> Rows(record)
      // if Join     -> Joins(left ptr->Rowtuple(record), right ptr->Rowtuple(record))
   *
   */

private:
  RC initialize();

private:
  std::function<bool(Tuple *const &left, Tuple *const &right)> comprule;
  bool                                                         is_inited_ = false;  // 是否已经初始化
  std::vector<std::pair<TupleCellSpec, bool>> order_rules;  // 表示order的第idx个cell是否为ASC排序
  std::vector<OrderByUnit *>                  order_reqs;
  std::vector<Tuple *>::iterator              iterator_;
  std::vector<Tuple *>                        ordered_tuples_;
};