#pragma once
#include "sql/expr/expression.h"
#include "sql/operator/physical_operator.h"
#include "sql/optimizer/optimize_stage.h"
#include "sql/stmt/select_stmt.h"
#include "sql/stmt/stmt.h"

class SubQueryExpr : public ValueListExpr
{
public:
  SubQueryExpr(SelectStmt *stmt) : stmt_(stmt) {}
  ~SubQueryExpr() override
  {
    if (physical_operator_ != nullptr) {
      physical_operator_->close();
    }
    if (stmt_ != nullptr) {
      delete stmt_;
      stmt_ = nullptr;
    }
  }
  AttrType value_type() const override
  {
    auto select_stmt = static_cast<const SelectStmt *>(stmt_);
    return select_stmt->query_fields().front().attr_type();
  }
  ExprType type() const override { return ExprType::SUBQUERY; }
  RC       executor(Trx *trx)
  {
    trx_ = trx;
    OptimizeStage optimize_stage;
    auto          rc = optimize_stage.handle_expr(this);
    if (rc != RC::SUCCESS) {
      sql_debug("failed to handle expr. rc=%s", strrc(rc));
      return rc;
    }
    rc = physical_operator_->open(trx);
    if (rc != RC::SUCCESS) {
      sql_debug("failed to open physical operator. rc=%s", strrc(rc));
      return rc;
    }

    while (RC::SUCCESS == (rc = physical_operator_->next())) {
      Tuple *tuple = physical_operator_->current_tuple();
      // TODO: 现在报错其实是早了
      // update user set name = (select name from user where id = 1) where id = 2;
      // 如果where id = 2 没有返回值，即使子查询返回多个值也不报错。
      if (tuple->cell_num() != 1) {
        sql_debug("invalid tuple cell num. cell_num=%d", tuple->cell_num());
        return RC::INTERNAL;
      }
      Value value;
      rc = tuple->cell_at(0, value);
      if (rc != RC::SUCCESS) {
        sql_debug("failed to get cell. rc=%s", strrc(rc));
        return rc;
      }
      value_list_.push_back(value);
    }
    return RC::SUCCESS;
  }

  auto stmt() const { return stmt_; }
  void set_operator(std::unique_ptr<PhysicalOperator> oper) { physical_operator_ = std::move(oper); }

private:
  Trx                              *trx_               = nullptr;
  SelectStmt                       *stmt_              = nullptr;
  std::unique_ptr<PhysicalOperator> physical_operator_ = nullptr;
};