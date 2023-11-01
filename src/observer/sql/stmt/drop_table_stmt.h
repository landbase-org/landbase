#pragma once

#include <string>

#include "event/sql_debug.h"
#include "sql/stmt/stmt.h"

/**
 * @brief Drop Table Statement
 * @ingroup Statement
 * @details 只需要一个表名
 */
class DropTableStmt : public Stmt
{
public:
  DropTableStmt(const std::string &table_name) : table_name_(table_name){};
  virtual ~DropTableStmt() = default;

  StmtType type() const override { return StmtType::DROP_TABLE; }

  const std::string &table_name() const { return table_name_; }

  static RC create(Db *db, const DropTableSqlNode &drop_table, Stmt *&stmt)
  {
    stmt = new DropTableStmt(drop_table.relation_name);
    LOG_INFO("drop table statement: table name %s", drop_table.relation_name.c_str());
    return RC::SUCCESS;
  }

private:
  std::string table_name_;
};