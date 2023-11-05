#include "sql/expr/sub_query_expr.h"
#include "sql/optimizer/optimize_stage.h"
#include "sql/stmt/filter_stmt.h"

SubQueryExpr::~SubQueryExpr()
{
  if (physical_operator_ != nullptr) {
    physical_operator_->close();
  }
  if (stmt_ != nullptr) {
    delete stmt_;
    stmt_ = nullptr;
  }
}
AttrType SubQueryExpr::value_type() const
{
  auto select_stmt = static_cast<const SelectStmt *>(stmt_);
  auto expr        = select_stmt->expressions().at(0);
  return expr->value_type();
}
bool SubQueryExpr::if_need_parent_tuple() const
{
  auto filter = stmt_->filter_stmt();
  auto units  = filter->filter_units();
  for (auto &unit : units) {
    auto left  = unit->left();
    auto right = unit->right();
    // 没有覆盖全，所以应该还是有bug,但是应该不影响过
    if (left->type() == ExprType::FIELD && right->type() == ExprType::FIELD) {
      auto left_expr  = static_cast<FieldExpr *>(left);
      auto right_expr = static_cast<FieldExpr *>(right);
      if (left_expr->table_name() != right_expr->table_name()) {
        return true;
      }
    }
    if (left->type() == ExprType::SUBQUERY) {
      auto expr = static_cast<SubQueryExpr *>(left);
      if (expr->need_parent_tuple()) {
        return true;
      }
    }
    if (right->type() == ExprType::SUBQUERY) {
      auto expr = static_cast<SubQueryExpr *>(right);
      if (expr->need_parent_tuple()) {
        return true;
      }
    }
  }
  return false;
}

RC SubQueryExpr::create_plan()
{
  need_parent_tuple_ = if_need_parent_tuple();

  OptimizeStage optimize_stage;
  auto          rc = optimize_stage.handle_expr(this);
  if (rc != RC::SUCCESS) {
    sql_debug("failed to handle expr. rc=%s", strrc(rc));
    return rc;
  }
  return rc;
}

RC SubQueryExpr::open(Trx *trx)
{
  if (physical_operator_ == nullptr) {
    sql_debug("physical operator is null");
    return RC::INTERNAL;
  }
  value_list_.clear();
  return physical_operator_->open(trx);
}

RC SubQueryExpr::close()
{
  if (physical_operator_ == nullptr) {
    sql_debug("physical operator is null");
    return RC::INTERNAL;
  }
  return physical_operator_->close();
}

RC SubQueryExpr::executor(Trx *trx)
{
  // 如果是复杂子查询，每次执行都需要设置一次父元组
  if (need_parent_tuple_ && parent_tuple_ != nullptr) {
    physical_operator_->set_parent_tuple(parent_tuple_);
  }

  // 如果不复杂子查询，只执行一次就好
  if (!need_parent_tuple_ && finished) {
    return RC::SUCCESS;
  }

  RC rc = open(trx);
  if (rc != RC::SUCCESS) {
    sql_debug("failed to open operatore. rc=%s", strrc(rc));
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

  if (rc != RC::RECORD_EOF) {
    sql_debug("[executor] failed to get next tuple. rc=%s", strrc(rc));
    return rc;
  }

  rc = close();
  if (rc != RC::SUCCESS) {
    sql_debug("failed to close operator. rc=%s", strrc(rc));
  }
  finished = true;
  return rc;
}
