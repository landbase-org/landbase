#pragma once
#include "sql/expr/expression.h"
#include "sql/operator/physical_operator.h"
#include "sql/stmt/select_stmt.h"

class SubQueryExpr : public ValueListExpr
{
public:
  SubQueryExpr(SelectStmt *stmt) : stmt_(stmt) { create_plan(); }
  ~SubQueryExpr() override;
  AttrType value_type() const override;
  ExprType type() const override { return ExprType::SUBQUERY; }
  bool     if_need_parent_tuple() const;
  bool     need_parent_tuple() const { return need_parent_tuple_; }
  RC       create_plan();

  RC   open(Trx *trx);
  RC   executor(Trx *trx);
  RC   close();
  void set_parent_tuple(Tuple *tuple) { parent_tuple_ = tuple; }
  auto stmt() const { return stmt_; }
  void set_operator(std::unique_ptr<PhysicalOperator> oper) { physical_operator_ = std::move(oper); }

private:
  SelectStmt                       *stmt_              = nullptr;
  bool                              need_parent_tuple_ = false;
  bool                              finished           = false;
  Tuple                            *parent_tuple_      = nullptr;
  std::unique_ptr<PhysicalOperator> physical_operator_ = nullptr;
};