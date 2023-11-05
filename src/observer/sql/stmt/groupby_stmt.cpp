#include "groupby_stml.h"
RC GroupByUnit::create(
    Db *db, const std::unordered_map<std::string, Table *> &table_map, const std::vector<Table *> &tables,
    const GroupBySqlNode &groupby, std::unique_ptr<GroupByUnit> *groupby_unit
)
{
  RC          rc   = RC::SUCCESS;
  Expression *expr = nullptr;
  rc               = FieldExpr::create(groupby, table_map, tables, expr);
  if (rc != RC::SUCCESS) {
    LOG_WARN("cannot create FieldExpr when create groupby unit");
    return rc;
  }

  std::unique_ptr<GroupByUnit> new_unit(new GroupByUnit(std::move(std::unique_ptr<Expression>(expr))));
  *groupby_unit = std::move(new_unit);
  return rc;
}

RC GroupByStmt::create(
    Db *db, const std::unordered_map<std::string, Table *> &table_map, const std::vector<Table *> &tables,
    const std::vector<GroupBySqlNode> &groupby_nodes, GroupByStmt *&stmt
)
{
  RC           rc       = RC::SUCCESS;
  GroupByStmt *new_stmt = new GroupByStmt;
  for (auto node : groupby_nodes) {
    std::unique_ptr<GroupByUnit> new_unit = nullptr;
    rc                                    = GroupByUnit::create(db, table_map, tables, node, &new_unit);
    if (rc != RC::SUCCESS) {
      LOG_WARN(
          "failed to create group by unit, rel=%s attr=%s", node.relation_name.c_str(), node.attribute_name.c_str()
      );
      return rc;
    }
    new_stmt->add_unit(std::move(new_unit));
  }
  stmt = new_stmt;
  return rc;
}