#include "common/log/log.h"
#include "order_by_stmt.h"

OrderByStmt::~OrderByStmt()
{
  for (OrderByUnit *order : order_units_) {
    delete order;
  }
  order_units_.clear();
}

RC OrderByStmt::create(
    Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables, const OrderSqlNode *orderbys,
    int order_num, OrderByStmt *&stmt
)
{
  RC rc = RC::SUCCESS;
  stmt  = nullptr;

  OrderByStmt *tmp_stmt = new OrderByStmt();
  for (int i = 0; i < order_num; i++) {
    OrderByUnit *orderby_unit = nullptr;
    rc                        = create_orderby_unit(db, default_table, tables, orderbys[i], orderby_unit);
    if (rc != RC::SUCCESS) {
      delete tmp_stmt;
      LOG_WARN("failed to create orderby unit. orderby index=%d", i);
      return rc;
    }
    tmp_stmt->order_units_.push_back(orderby_unit);
  }

  stmt = tmp_stmt;
  return rc;
}
RC create_orderby_unit(
    Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables, const ConditionSqlNode &condition,
    OrderByUnit *&order_unit
)
{
  return RC::SUCCESS;
}