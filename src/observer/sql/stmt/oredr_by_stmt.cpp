#include "common/lang/string.h"
#include "common/log/log.h"
#include "event/sql_debug.h"
#include "order_by_stmt.h"
#include "sql/parser/parse_defs.h"
#include "storage/field/field_meta.h"
#include "storage/table/table.h"
RC get_unit_info(
    Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables, const RelAttrSqlNode &attr,
    Table *&table, const FieldMeta *&field
)
{
  if (common::is_blank(attr.relation_name.c_str())) {
    table = default_table;
  } else if (nullptr != tables) {
    auto iter = tables->find(attr.relation_name);
    if (iter != tables->end()) {
      table = iter->second;
    }
  } else {
    table = db->find_table(attr.relation_name.c_str());
  }
  if (nullptr == table) {
    sql_debug("No such table: attr.relation_name: %s", attr.relation_name.c_str());
    return RC::SCHEMA_TABLE_NOT_EXIST;
  }

  field = table->table_meta().field(attr.attribute_name.c_str());
  if (nullptr == field) {
    sql_debug("no such field in table: table %s, field %s", table->name(), attr.attribute_name.c_str());
    table = nullptr;
    return RC::SCHEMA_FIELD_NOT_EXIST;
  }

  return RC::SUCCESS;
}
void OrderByUnit::set_table(Table *table) { order_table_ = table; }
void OrderByUnit::set_order(OrderType type_input) { is_asc = type_input == OrderType::ORDER_ASC; }
void OrderByUnit::set_field_meta(const FieldMeta *&filed_meta) { order_field = *filed_meta; }

OrderByStmt::~OrderByStmt()
{
  for (auto &unit_ptr : order_units_)
    delete unit_ptr;
  order_units_.clear();
}

RC OrderByStmt::create(
    Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables, const OrderSqlNode *orderbys,
    int order_num, OrderByStmt *&stmt
)
{
  RC rc = RC::SUCCESS;

  stmt = new OrderByStmt();
  for (int i = 0; i < order_num; i++) {
    OrderByUnit *orderby_unit = nullptr;
    rc                        = create_orderby_unit(db, default_table, tables, orderbys[i], orderby_unit);
    if (rc != RC::SUCCESS) {
      delete stmt;
      stmt = nullptr;
      sql_debug("failed to create orderby unit. orderby index=%d", i);
      return rc;
    }
    stmt->order_units_.emplace_back(orderby_unit);
  }

  return rc;
}

RC OrderByStmt::create_orderby_unit(
    Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables, const OrderSqlNode &orderby,
    OrderByUnit *&order_unit
)
{
  Table           *table_tmp = nullptr;
  const FieldMeta *field_mt  = nullptr;
  RC               rc        = get_unit_info(db, default_table, tables, orderby.rel_attr, table_tmp, field_mt);
  if (rc != RC::SUCCESS) {
    sql_debug("Order field not found");
    return rc;
  }

  order_unit = new OrderByUnit();
  order_unit->set_table(table_tmp);
  order_unit->set_field_meta(field_mt);
  order_unit->set_order(orderby.order_type);
  return RC::SUCCESS;
}