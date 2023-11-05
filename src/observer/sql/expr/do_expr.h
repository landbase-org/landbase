#pragma once

#include "sql/expr/expression.h"
#include "sql/expr/sub_query_expr.h"

RC do_expr(Trx *trx, Expression *expr, Tuple *tuple);
RC do_conjunction_expr(Trx *trx, ConjunctionExpr *conj_expr, Tuple *tuple);
RC do_comparison_expr(Trx *trx, ComparisonExpr *comp_expr, Tuple *tuple);
RC do_in_expr(Trx *trx, InExpr *in_expr, Tuple *tuple);
RC do_exists_expr(Trx *trx, ExistsExpr *exists_expr, Tuple *tuple);
RC do_subquery_expr(Trx *trx, SubQueryExpr *subquery_expr, Tuple *tuple);
