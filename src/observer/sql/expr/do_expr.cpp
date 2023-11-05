#include "sql/expr/do_expr.h"
#include "common/rc.h"
#include "storage/trx/trx.h"

RC do_expr(Trx *trx, Expression *expression, Tuple *tuple)
{
  RC rc = RC::SUCCESS;
  switch (expression->type()) {
    case ExprType::CONJUNCTION: {
      rc = do_conjunction_expr(trx, static_cast<ConjunctionExpr *>(expression), tuple);
      if (rc != RC::SUCCESS) {
        sql_debug("[do_expr] failed to do conjunction expr");
      }
    } break;
    case ExprType::COMPARISON: {
      rc = do_comparison_expr(trx, static_cast<ComparisonExpr *>(expression), tuple);
      if (rc != RC::SUCCESS) {
        sql_debug("[do_expr] failed to do comparison expr");
      }
    } break;
    case ExprType::IN: {
      rc = do_in_expr(trx, static_cast<InExpr *>(expression), tuple);
      if (rc != RC::SUCCESS) {
        sql_debug("[do_expr] failed to do in expr");
      }
    } break;
    case ExprType::EXISTS: {
      rc = do_exists_expr(trx, static_cast<ExistsExpr *>(expression), tuple);
      if (rc != RC::SUCCESS) {
        sql_debug("[do_expr] failed to do exists expr");
      }
    } break;
    case ExprType::SUBQUERY: {
      rc = do_subquery_expr(trx, static_cast<SubQueryExpr *>(expression), tuple);
      if (rc != RC::SUCCESS) {
        sql_debug("[do_expr] failed to do subquery expr");
      }
    } break;
    default: {
      sql_debug("[do_expr] uninplemented ExprType");
    } break;
  }

  return rc;
}

RC do_conjunction_expr(Trx *trx, ConjunctionExpr *conj_expr, Tuple *tuple)
{
  RC    rc       = RC::SUCCESS;
  auto &children = conj_expr->children();
  for (auto &child : children) {
    switch (child->type()) {
      case ExprType::CONJUNCTION: {
        auto expr = static_cast<ConjunctionExpr *>(child.get());
        rc        = do_conjunction_expr(trx, expr, tuple);
        if (rc != RC::SUCCESS) {
          sql_debug("[do_conjunction_expr] failed to do conjunction expr");
        }
      } break;
      case ExprType::COMPARISON: {
        auto expr = static_cast<ComparisonExpr *>(child.get());
        rc        = do_comparison_expr(trx, expr, tuple);
        if (rc != RC::SUCCESS) {
          sql_debug("[do_conjunction_expr] failed to do comparison expr");
        }
      } break;
      case ExprType::IN: {
        auto expr = static_cast<InExpr *>(child.get());
        rc        = do_in_expr(trx, expr, tuple);
        if (rc != RC::SUCCESS) {
          sql_debug("[do_conjunction_expr] failed to do in expr");
        }
      } break;
      case ExprType::EXISTS: {
        auto expr = static_cast<ExistsExpr *>(child.get());
        rc        = do_exists_expr(trx, expr, tuple);
        if (rc != RC::SUCCESS) {
          sql_debug("[do_conjunction_expr] failed to do subquery expr");
        }
      } break;
      case ExprType::SUBQUERY: {
        auto expr = static_cast<SubQueryExpr *>(child.get());
        rc        = do_subquery_expr(trx, expr, tuple);
        if (rc != RC::SUCCESS) {
          sql_debug("[do_conjunction_expr] failed to do subquery expr");
        }
      } break;
      default: {
        sql_debug("uninplemented ExprType");
      } break;
    }
  }
  return rc;
}
RC do_comparison_expr(Trx *trx, ComparisonExpr *comp_expr, Tuple *tuple)
{
  // 左右都有可能是子查询
  RC    rc         = RC::SUCCESS;
  auto &left_expr  = comp_expr->left();
  auto &right_expr = comp_expr->right();
  if (left_expr->type() == ExprType::SUBQUERY) {
    auto subquery_expr = static_cast<SubQueryExpr *>(left_expr.get());
    rc                 = do_subquery_expr(trx, subquery_expr, tuple);
    if (rc != RC::SUCCESS) {
      sql_debug("[do_comparison_expr] failed to execute left expression");
    }
    // 检查子查询的结果是否是合法
    if (subquery_expr->value_list().size() > 1) {
      sql_debug("[do_comparison_expr] subquery result is not valid");
      return RC::INTERNAL;
    }
  }
  if (right_expr->type() == ExprType::SUBQUERY) {
    auto subquery_expr = static_cast<SubQueryExpr *>(right_expr.get());
    rc                 = do_subquery_expr(trx, subquery_expr, tuple);
    if (rc != RC::SUCCESS) {
      sql_debug("[do_comparison_expr] failed to execute right expression");
    }
    // 检查子查询的结果是否是合法
    if (subquery_expr->value_list().size() > 1) {
      sql_debug("[do_comparison_expr] subquery result is not valid");
      return RC::INTERNAL;
    }
  }
  return rc;
}
RC do_in_expr(Trx *trx, InExpr *in_expr, Tuple *tuple)
{
  // 左右都有可能是子查询
  RC    rc         = RC::SUCCESS;
  auto &left_expr  = in_expr->left();
  auto &right_expr = in_expr->right();
  if (left_expr->type() == ExprType::SUBQUERY) {
    auto subquery_expr = static_cast<SubQueryExpr *>(left_expr.get());
    rc                 = do_subquery_expr(trx, subquery_expr, tuple);
    if (rc != RC::SUCCESS) {
      sql_debug("[do_in_expr] failed to execute left expression");
    }
  }
  if (right_expr->type() == ExprType::SUBQUERY) {
    auto subquery_expr = static_cast<SubQueryExpr *>(right_expr.get());
    rc                 = do_subquery_expr(trx, subquery_expr, tuple);
    if (rc != RC::SUCCESS) {
      sql_debug("[do_in_expr] failed to execute right expression");
    }
  }
  return rc;
}

RC do_exists_expr(Trx *trx, ExistsExpr *exists_expr, Tuple *tuple)
{
  // 右侧一定是一个子查询
  auto subquery_expr = static_cast<SubQueryExpr *>(exists_expr->right().get());
  RC   rc            = do_subquery_expr(trx, subquery_expr, tuple);
  if (rc != RC::SUCCESS) {
    sql_debug("[do_exists_expr] failed to do exists expr");
  }
  return rc;
}

RC do_subquery_expr(Trx *trx, SubQueryExpr *subquery_expr, Tuple *tuple)
{
  RC rc = RC::SUCCESS;
  if (subquery_expr->need_parent_tuple()) {
    if (tuple == nullptr) {
      return RC::SUCCESS;
    }
    subquery_expr->set_parent_tuple(tuple);
    rc = subquery_expr->executor(trx);
    if (rc != RC::SUCCESS) {
      sql_debug("[do_subquery_expr] failed to execute subquery expr");
    }
  } else {
    rc = subquery_expr->executor(trx);
    if (rc != RC::SUCCESS) {
      sql_debug("[do_subquery_expr] failed to execute subquery expr");
    }
  }
  return rc;
}
