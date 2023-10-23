/* Copyright (c) 2021 OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by Meiyi
//

#pragma once

#include <climits>
#include <float.h>
#include <memory>
#include <stddef.h>
#include <string>
#include <unordered_map>
#include <vector>

#include "sql/parser/comp_op.h"
#include "sql/parser/value.h"

class Expression;

/**
 * @defgroup SQLParser SQL Parser
 */

/**
 * @description: Order类型
 */
enum OrderType
{
  NONE,  // 无ORDER要求
  ORDER_ASC,   // 升序
  ORDER_DESC   // 降序
};

/**
 * @description: 聚合类型
 */
enum AggreType
{
  AGGRE_NONE,
  AGGRE_MAX,
  AGGRE_MIN,
  AGGRE_COUNT,
  AGGRE_AVG,
  AGGRE_SUM
};
static std::string aggreType2str(AggreType aggre)
{
  static std::unordered_map<AggreType, std::string> m{
      {AGGRE_NONE, "NONE"},
      {AGGRE_MAX, "MAX"},
      {AGGRE_MIN, "MIN"},
      {AGGRE_COUNT, "COUNT"},
      {AGGRE_AVG, "AVG"},
      {AGGRE_SUM, "SUM"},
  };
  return m.at(aggre);
}

/**
 * @description: 计算Aggre的类型
 * @return {*}
 */
class AggreCalc
{
  using date = int32_t;
  // 每次执行更新操作 `count` 更新一次, 便于求avg的值
  // 求 avg 和 sum都统一更新sum

public:
  AggreCalc() = delete;
  // AggreType: MIN, MAX, AVG, COUNT, SUM
  AggreCalc(AggreType aggre_type, Value value) : aggre_type_(aggre_type), value_(value)
  {
    attr_type_ = value.attr_type();
    i_count++;

    switch (attr_type_) {
      case CHARS: {
        switch (aggre_type_) {
          case AGGRE_MAX: s_max = value.get_string(); break;
          case AGGRE_MIN: s_min = value.get_string(); break;
          default: break;
        }
      } break;
      case DATES: {
        switch (aggre_type_) {
          case AGGRE_MAX: d_max = value.get_date(); break;
          case AGGRE_MIN: d_min = value.get_date(); break;
          default: break;
        }
      } break;
      case INTS: {
        switch (aggre_type_) {
          case AGGRE_MAX: i_max = value.get_int(); break;
          case AGGRE_MIN: i_min = value.get_int(); break;
          case AGGRE_AVG:
          case AGGRE_SUM: i_sum += value.get_int(); break;
          default: break;
        }
      } break;
      case FLOATS: {
        switch (aggre_type_) {
          case AGGRE_MAX: f_max = value.get_float(); break;
          case AGGRE_MIN: f_min = value.get_float(); break;
          case AGGRE_AVG:
          case AGGRE_SUM: f_sum += value.get_float(); break;
          default: break;
        }
      }
      default: break;
    }
  }

  void update(Value value)
  {
    i_count++;

    switch (attr_type_) {
      case CHARS: {
        switch (aggre_type_) {
          case AGGRE_MAX: s_max = std::max(s_max, value.get_string()); break;
          case AGGRE_MIN: s_min = std::min(s_min, value.get_string()); break;
          default: break;
        }
      } break;
      case DATES: {
        switch (aggre_type_) {
          case AGGRE_MAX: d_max = std::max(d_max, value.get_date()); break;
          case AGGRE_MIN: d_min = std::min(d_min, value.get_date()); break;
          default: break;
        }
      } break;
      case INTS: {
        switch (aggre_type_) {
          case AGGRE_MAX: i_max = std::max(i_max, value.get_int()); break;
          case AGGRE_MIN: i_min = std::min(i_min, value.get_int()); break;
          case AGGRE_AVG:
          case AGGRE_SUM: i_sum += value.get_int(); break;
          default: break;
        }
      } break;
      case FLOATS: {
        switch (aggre_type_) {
          case AGGRE_MAX: f_max = std::max(f_max, value.get_float()); break;
          case AGGRE_MIN: f_min = std::min(f_min, value.get_float()); break;
          case AGGRE_AVG:
          case AGGRE_SUM: f_sum += value.get_float(); break;
          default: break;
        }
      }
      default: break;
    }
  }

  const Value get_value()
  {
    if (aggre_type_ == AGGRE_COUNT)
      return Value((int)i_count);

    switch (attr_type_) {
      case CHARS: {
        switch (aggre_type_) {
          case AGGRE_MAX: value_.set_string(s_max.c_str()); break;
          case AGGRE_MIN: value_.set_string(s_min.c_str()); break;
          default: break;
        }
      } break;
      case DATES: {
        switch (aggre_type_) {
          case AGGRE_MAX: value_.set_date(d_max); break;
          case AGGRE_MIN: value_.set_date(d_min); break;
          default: break;
        }
      } break;
      case INTS: {
        switch (aggre_type_) {
          case AGGRE_MAX: value_.set_int(i_max); break;
          case AGGRE_MIN: value_.set_int(i_min); break;
          case AGGRE_AVG: {
            if (i_sum % i_count == 0) {
              value_.set_int(i_sum / i_count);
            } else {  // 如果结果为小数, 需要转化为FLOAT类型的value
              value_.set_type(FLOATS);
              value_.set_float(static_cast<float>(i_sum) / i_count);
            }
          } break;
          case AGGRE_SUM: value_.set_int(i_sum); break;
          default: break;
        }
      } break;
      case FLOATS: {
        switch (aggre_type_) {
          case AGGRE_MAX: value_.set_float(f_max); break;
          case AGGRE_MIN: value_.set_float(f_min); break;
          case AGGRE_AVG: value_.set_float(f_sum / i_count); break;
          case AGGRE_SUM: value_.set_float(f_sum); break;
          default: break;
        }
      }
      default: break;
    }
    return value_;
  }

private:
  AggreType   aggre_type_;
  Value       value_;
  AttrType    attr_type_;
  std::string s_min;
  std::string s_max;

  date d_min;
  date d_max;

  int       i_max{INT_MIN};
  int       i_min{INT_MAX};
  float     i_avg{0};  // 结果可能有小数
  long long i_sum{0};
  long long i_count{0};

  double f_sum{0};
  double f_avg{0};
  float  f_max{FLT_MIN};
  float  f_min{FLT_MAX};
};
/**
 * @description: aggretion 节点
 */
struct AggreTypeNode
{
  std::vector<std::string> attribute_names;         ///< 可能是多个字段
  AggreType                aggre_type{AGGRE_NONE};  ///< 聚合类型
};

/**
 * @brief 描述一个属性
 * @ingroup SQLParser
 * @details 属性，或者说字段(column, field)
 * Rel -> Relation
 * Attr -> Attribute
 */
struct RelAttrSqlNode
{
  std::string   relation_name;   ///< relation name (may be NULL) 表名
  std::string   attribute_name;  ///< attribute name              属性名
  AggreTypeNode aggretion_node;
};

/**
 * @brief 表示一个条件比较
 * @ingroup SQLParser
 * @details 条件比较就是SQL查询中的 where a>b 这种。
 * 一个条件比较是有两部分组成的，称为左边和右边。
 * 左边和右边理论上都可以是任意的数据，比如是字段（属性，列），也可以是数值常量。
 * 这个结构中记录的仅仅支持字段和值。
 */
struct ConditionSqlNode
{
  int left_is_attr;              ///< TRUE if left-hand side is an attribute
                                 ///< 1时，操作符左边是属性名，0时，是属性值
  Value          left_value;     ///< left-hand side value if left_is_attr = FALSE
  RelAttrSqlNode left_attr;      ///< left-hand side attribute
  CompOp         comp;           ///< comparison operator
  int            right_is_attr;  ///< TRUE if right-hand side is an attribute
                                 ///< 1时，操作符右边是属性名，0时，是属性值
  RelAttrSqlNode right_attr;     ///< right-hand side attribute if right_is_attr = TRUE 右边的属性
  Value          right_value;    ///< right-hand side value if right_is_attr = FALSE
};

/**
 * @brief 描述一个Join语句
 * @ingroup SQLParser
 */
struct JoinSqlNode
{
  std::string                   join_relation;
  std::vector<ConditionSqlNode> join_conditions;
};

struct OrderSqlNode
{
  RelAttrSqlNode rel_attr;
  OrderType      order_type = OrderType::ORDER_ASC;
};

/**
 * @brief 描述一个select语句
 * @ingroup SQLParser
 * @details 一个正常的select语句描述起来比这个要复杂很多，这里做了简化。
 * 一个select语句由三部分组成，分别是select, from, where。
 * select部分表示要查询的字段，from部分表示要查询的表，where部分表示查询的条件。
 * 比如 from 中可以是多个表，也可以是另一个查询语句，这里仅仅支持表，也就是 relations。
 * where 条件 conditions，这里表示使用AND串联起来多个条件。正常的SQL语句会有OR，NOT等，
 * 甚至可以包含复杂的表达式。
 */

struct SelectSqlNode
{
  std::vector<RelAttrSqlNode>   attributes;  ///< attributes in select clause
  std::vector<std::string>      relations;   ///< 查询的表
  std::vector<ConditionSqlNode> conditions;  ///< 查询条件，使用AND串联起来多个条件
  std::vector<JoinSqlNode>      joinctions;  ///< Join-list
  std::vector<OrderSqlNode>     orders;      ///< Order-requirements
};

/**
 * @brief 算术表达式计算的语法树
 * @ingroup SQLParser
 */
struct CalcSqlNode
{
  std::vector<Expression *> expressions;  ///< calc clause

  ~CalcSqlNode();
};

/**
 * @brief 描述一个insert语句
 * @ingroup SQLParser
 * @details 于Selects类似，也做了很多简化
 */
struct InsertSqlNode
{
  std::string                     relation_name;  ///< Relation to insert into
  std::vector<std::vector<Value>> values_list;  // 要插入的值的list, 插入n行数据, 每行(fields)有m个数据
};

/**
 * @brief 描述一个delete语句
 * @ingroup SQLParser
 */
struct DeleteSqlNode
{
  std::string                   relation_name;  ///< Relation to delete from
  std::vector<ConditionSqlNode> conditions;
};

/**
 * @brief 描述一个update语句
 * @ingroup SQLParser
 */
struct UpdateSqlNode
{
  std::string                   relation_name;   ///< Relation to update
  std::vector<std::string>      attr_list;       ///< 更新的字段
  std::vector<Value>            value_list;      ///< 更新的值
  std::vector<ConditionSqlNode> conditions;
};

/**
 * @brief 描述一个属性
 * @ingroup SQLParser
 * @details 属性，或者说字段(column, field)
 * Rel -> Relation
 * Attr -> Attribute
 */
struct AttrInfoSqlNode
{
  AttrType    type;    ///< Type of attribute
  std::string name;    ///< Attribute name
  size_t      length;  ///< Length of attribute
};

/**
 * @brief 描述一个create table语句
 * @ingroup SQLParser
 * @details 这里也做了很多简化。
 */
struct CreateTableSqlNode
{
  std::string                  relation_name;  ///< Relation name
  std::vector<AttrInfoSqlNode> attr_infos;     ///< attributes
};

/**
 * @brief 描述一个drop table语句
 * @ingroup SQLParser
 */
struct DropTableSqlNode
{
  std::string relation_name;  ///< 要删除的表名
};

/**
 * @brief 描述一个create index语句
 * @ingroup SQLParser
 * @details 创建索引时，需要指定索引名，表名，字段名。
 * 正常的SQL语句中，一个索引可能包含了多个字段，这里仅支持一个字段。
 */
struct CreateIndexSqlNode
{
  std::string              index_name;       ///< Index name
  std::string              relation_name;    ///< Relation name
  std::vector<std::string> attribute_names;  ///< Attribute name
  bool                     unique{false};
};

/**
 * @brief 描述一个show index语句
 * @ingroup SQLParser
 * @details
 */
struct ShowIndexSqlNode
{
  std::string relation_name;  ///< Relation name
};

/**
 * @brief 描述一个drop index语句
 * @ingroup SQLParser
 */
struct DropIndexSqlNode
{
  std::string index_name;     ///< Index name
  std::string relation_name;  ///< Relation name
};

/**
 * @brief 描述一个desc table语句
 * @ingroup SQLParser
 * @details desc table 是查询表结构信息的语句
 */
struct DescTableSqlNode
{
  std::string relation_name;
};

/**
 * @brief 描述一个load data语句
 * @ingroup SQLParser
 * @details 从文件导入数据到表中。文件中的每一行就是一条数据，每行的数据类型、字段个数都与表保持一致
 */
struct LoadDataSqlNode
{
  std::string relation_name;
  std::string file_name;
};

/**
 * @brief 设置变量的值
 * @ingroup SQLParser
 * @note 当前还没有查询变量
 */
struct SetVariableSqlNode
{
  std::string name;
  Value       value;
};

class ParsedSqlNode;

/**
 * @brief 描述一个explain语句
 * @ingroup SQLParser
 * @details 会创建operator的语句，才能用explain输出执行计划。
 * 一个command就是一个语句，比如select语句，insert语句等。
 * 可能改成SqlCommand更合适。
 */
struct ExplainSqlNode
{
  std::unique_ptr<ParsedSqlNode> sql_node;
};

/**
 * @brief 解析SQL语句出现了错误
 * @ingroup SQLParser
 * @details 当前解析时并没有处理错误的行号和列号
 */
struct ErrorSqlNode
{
  std::string error_msg;
  int         line;
  int         column;
};

/**
 * @brief 表示一个SQL语句的类型
 * @ingroup SQLParser
 */
enum SqlCommandFlag
{
  SCF_ERROR = 0,
  SCF_CALC,
  SCF_SELECT,
  SCF_INSERT,
  SCF_UPDATE,
  SCF_DELETE,
  SCF_CREATE_TABLE,
  SCF_DROP_TABLE,
  SCF_CREATE_INDEX,
  SCF_SHOW_INDEX,
  SCF_DROP_INDEX,
  SCF_SYNC,
  SCF_SHOW_TABLES,
  SCF_DESC_TABLE,
  SCF_BEGIN,  ///< 事务开始语句，可以在这里扩展只读事务
  SCF_COMMIT,
  SCF_CLOG_SYNC,
  SCF_ROLLBACK,
  SCF_LOAD_DATA,
  SCF_HELP,
  SCF_EXIT,
  SCF_EXPLAIN,
  SCF_SET_VARIABLE,  ///< 设置变量
};
/**
 * @brief 表示一个SQL语句
 * @ingroup SQLParser
 */
class ParsedSqlNode
{
public:
  enum SqlCommandFlag flag;
  ErrorSqlNode        error;
  CalcSqlNode         calc;
  SelectSqlNode       selection;
  InsertSqlNode       insertion;
  DeleteSqlNode       deletion;
  UpdateSqlNode       update;
  CreateTableSqlNode  create_table;
  DropTableSqlNode    drop_table;
  CreateIndexSqlNode  create_index;
  ShowIndexSqlNode    show_index;
  DropIndexSqlNode    drop_index;
  DescTableSqlNode    desc_table;
  LoadDataSqlNode     load_data;
  ExplainSqlNode      explain;
  SetVariableSqlNode  set_variable;

public:
  ParsedSqlNode();
  explicit ParsedSqlNode(SqlCommandFlag flag);
};

/**
 * @brief 表示语法解析后的数据
 * @ingroup SQLParser
 */
class ParsedSqlResult
{
public:
  void                                         add_sql_node(std::unique_ptr<ParsedSqlNode> sql_node);
  std::vector<std::unique_ptr<ParsedSqlNode>> &sql_nodes() { return sql_nodes_; }

private:
  std::vector<std::unique_ptr<ParsedSqlNode>> sql_nodes_;  ///< 这里记录SQL命令。虽然看起来支持多个，但是当前仅处理一个
};
