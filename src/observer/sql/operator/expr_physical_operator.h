#include "physical_operator.h"
#include "sql/expr/expression.h"
#include "sql/expr/tuple.h"
#include <memory>

class ExprPhysicalOperator : public PhysicalOperator
{
public:
  explicit ExprPhysicalOperator(const std::vector<Expression *> &exprs)
  {
    for (auto &raw : exprs) {
      exprs_.emplace_back(raw);
    }
  }
  ~ExprPhysicalOperator() = default;

  PhysicalOperatorType type() const override { return PhysicalOperatorType::EXPRESSION; }

  // 打开子算子 --> 扫表算子
  RC open(Trx *trx) override;

  // 子算子的下一个 / 或者只有一个常值表达式
  RC next() override;

  // 关闭子算子？
  RC close() override;

  // 返回子算子加工过后的tuple / 或者返回常值表达式的值
  // EXPRESSION：表达式出现在where条件时要考虑怎么做
  Tuple *current_tuple() override;

private:
  // ValueListTuple / ExpressionTuple    tuple_;
  bool                                     value_used = false;
  bool                                     value_only = false;
  std::vector<std::unique_ptr<Expression>> exprs_;
  ExpressionTuple                         *tuple_;
};