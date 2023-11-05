
%{

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
#include <utility>

#include "common/log/log.h"
#include "common/lang/string.h"
#include "sql/parser/parse_defs.h"
#include "sql/parser/yacc_sql.hpp"
#include "sql/parser/lex_sql.h"
#include "sql/expr/expression.h"
#include "sql/parser/parse_expr_defs.h"

using namespace std;

string token_name(const char *sql_string, YYLTYPE *llocp)
{
  return string(sql_string + llocp->first_column, llocp->last_column - llocp->first_column + 1);
}

int yyerror(YYLTYPE *llocp, const char *sql_string, ParsedSqlResult *sql_result, yyscan_t scanner, const char *msg)
{
  std::unique_ptr<ParsedSqlNode> error_sql_node = std::make_unique<ParsedSqlNode>(SCF_ERROR);
  error_sql_node->error.error_msg = msg;
  error_sql_node->error.line = llocp->first_line;
  error_sql_node->error.column = llocp->first_column;
  sql_result->add_sql_node(std::move(error_sql_node));
  return 0;
}

ArithmeticExpr *create_arithmetic_expression(ArithmeticExpr::Type type,
                                             Expression *left,
                                             Expression *right,
                                             const char *sql_string,
                                             YYLTYPE *llocp)
{
  ArithmeticExpr *expr = new ArithmeticExpr(type, left, right);
  expr->set_name(token_name(sql_string, llocp));
  return expr;
}

%}

%define api.pure full
%define parse.error verbose
/** 启用位置标识 **/
%locations
%lex-param { yyscan_t scanner }
/** 这些定义了在yyparse函数中的参数 **/
%parse-param { const char * sql_string }
%parse-param { ParsedSqlResult * sql_result }
%parse-param { void * scanner }

//标识tokens
%token  SEMICOLON
        CREATE
        DROP
        TABLE
        TABLES
        INDEX
        UNIQUE
        CALC
        SELECT
        INNER
        JOIN
        ORDER
        ASC
        BY
        DESC
        SHOW
        SYNC
        INSERT
        DELETE
        UPDATE
        LBRACE
        RBRACE
        COMMA
        TRX_BEGIN
        TRX_COMMIT
        TRX_ROLLBACK
        INT_T
        STRING_T
        TEXT_T
        FLOAT_T
        DATE_T
        NULL_T
        HELP
        EXIT
        DOT //QUOTE
        INTO
        VALUES
        AS
        FROM
        WHERE
        AND
        OR
        SET
        ON
        LOAD
        DATA
        INFILE
        EXPLAIN
        EQ
        LT
        GT
        LE
        GE
        NE
        SUM
        COUNT
        AVG
        MIN
        MAX
        IS_ // 加 _ 是为了防止和comp_op冲突
        NOT
        LK
        IN_OP
        EXISTS_OP

/** union 中定义各种数据类型，真实生成的代码也是union类型，所以不能有非POD类型的数据 **/
%union {
  ParsedSqlNode *                   sql_node;
  ConditionSqlNode *                condition;
  Value *                           value;
  enum CompOp                       comp;
  enum AggreType                    aggre_type;
  enum OrderType                    order_type;
  AggreSqlNode *                    aggre_node;
  std::vector<AggreSqlNode> *       aggre_node_list;
  std::vector<AggreSqlNode> *       aggre_node_list_opt;  // opt表示可以选择，可以有也可以没有
  RelAttrSqlNode *                  rel_attr;
  std::vector<RelAttrSqlNode> *     rel_attr_list;
  std::vector<AttrInfoSqlNode> *    attr_infos;
  AttrInfoSqlNode *                 attr_info;
  Expression *                      expression;
  ParseExpr *                       parse_expr;
  JoinSqlNode *                     join_node;
  OrderSqlNode *                    order_node;
  std::vector<Expression *> *       expression_list;
  std::vector<Value> *              value_list;
  std::vector<std::vector<Value>> * value_list_list; 
  std::vector<std::string> *        id_list;
  std::pair<std::vector<std::string>, std::vector<ParseExpr *>> * update_list;
  std::vector<ConditionSqlNode> *   condition_list;
  AttrSqlNode                     * rel_node;
  std::vector<AttrSqlNode> *        relation_list;
  std::vector<std::string> *        aggre_attr_list;
  std::vector<JoinSqlNode> *        join_list;
  std::vector<OrderSqlNode> *       order_list;
  char *                            string; // 是char*类型, 需要free
  int                               number;
  float                             floats;
  bool                              nullable;
}

%token <number> NUMBER
%token <floats> FLOAT
%token <string> ID
%token <string> SSS

//非终结符

/** type 定义了各种解析后的结果输出的是什么类型。类型对应了 union 中的定义的成员变量名称 **/
%type <number>              type
%type <condition>           condition
%type <value>               value
%type <number>              number
%type <comp>                comp_op
%type <comp>                in_op
%type <comp>                exists_op
%type <aggre_type>          aggre_type
%type <order_type>          order_type
%type <aggre_node>          aggre_node
%type <aggre_node_list>     aggre_node_list
%type <aggre_node_list>     aggre_node_list_opt
%type <rel_attr>            rel_attr        // (table column)
%type <rel_attr_list>       rel_attr_list
%type <rel_attr_list>       rel_attr_list_opt
%type <attr_infos>          attr_def_list
%type <attr_info>           attr_def
%type <nullable>            nullable // 用于标识字段是否可以为 null
%type <value_list>          value_list
%type <value_list_list>     value_list_list
%type <update_list>         update_list
%type <condition_list>      where
%type <condition_list>      condition_list
%type <rel_node>            rel_node
%type <relation_list>       rel_list
%type <id_list>             id_list
%type <expression>          expression
%type <expression_list>     expression_list
%type <parse_expr>          parse_expr;
%type <join_node>           join_node
%type <join_list>           join_list
%type <order_node>          order_node
%type <order_list>          order_list
%type <order_list>          select_order_list
%type <join_list>           select_join_list
%type <sql_node>            calc_stmt
%type <sql_node>            select_stmt
%type <sql_node>            insert_stmt
%type <sql_node>            update_stmt
%type <sql_node>            delete_stmt
%type <sql_node>            create_table_stmt
%type <sql_node>            drop_table_stmt
%type <sql_node>            show_tables_stmt
%type <sql_node>            desc_table_stmt
%type <sql_node>            create_index_stmt
%type <sql_node>            drop_index_stmt
%type <sql_node>            show_index_stmt
%type <sql_node>            sync_stmt
%type <sql_node>            begin_stmt
%type <sql_node>            commit_stmt
%type <sql_node>            rollback_stmt
%type <sql_node>            load_data_stmt
%type <sql_node>            explain_stmt
%type <sql_node>            set_variable_stmt
%type <sql_node>            help_stmt
%type <sql_node>            exit_stmt
%type <sql_node>            command_wrapper
%type <string>              rel_name  // 表名
%type <string>              attr_name // 列名
// commands should be a list but I use a single command instead
%type <sql_node>            commands

%left '+' '-'
%left '*' '/'
%nonassoc UMINUS
%%

commands: command_wrapper opt_semicolon  //commands or sqls. parser starts here.
  {
    std::unique_ptr<ParsedSqlNode> sql_node = std::unique_ptr<ParsedSqlNode>($1);
    sql_result->add_sql_node(std::move(sql_node));
  }
  ;

command_wrapper:
    calc_stmt
  | select_stmt
  | insert_stmt
  | update_stmt
  | delete_stmt
  | create_table_stmt
  | drop_table_stmt
  | show_tables_stmt
  | desc_table_stmt
  | create_index_stmt
  | drop_index_stmt
  | show_index_stmt
  | sync_stmt
  | begin_stmt
  | commit_stmt
  | rollback_stmt
  | load_data_stmt
  | explain_stmt
  | set_variable_stmt
  | help_stmt
  | exit_stmt
    ;

exit_stmt:      
    EXIT {
      (void)yynerrs;  // 这么写为了消除yynerrs未使用的告警。如果你有更好的方法欢迎提PR
      $$ = new ParsedSqlNode(SCF_EXIT);
    };

help_stmt:
    HELP {
      $$ = new ParsedSqlNode(SCF_HELP);
    };

sync_stmt:
    SYNC {
      $$ = new ParsedSqlNode(SCF_SYNC);
    }
    ;

begin_stmt:
    TRX_BEGIN  {
      $$ = new ParsedSqlNode(SCF_BEGIN);
    }
    ;

commit_stmt:
    TRX_COMMIT {
      $$ = new ParsedSqlNode(SCF_COMMIT);
    }
    ;

rollback_stmt:
    TRX_ROLLBACK  {
      $$ = new ParsedSqlNode(SCF_ROLLBACK);
    }
    ;

drop_table_stmt:    /*drop table 语句的语法解析树*/
    DROP TABLE ID {
      $$ = new ParsedSqlNode(SCF_DROP_TABLE);
      $$->drop_table.relation_name = $3;
      free($3);
    };

show_tables_stmt:
    SHOW TABLES {
      $$ = new ParsedSqlNode(SCF_SHOW_TABLES);
    }
    ;

desc_table_stmt:
    DESC ID  {
      $$ = new ParsedSqlNode(SCF_DESC_TABLE);
      $$->desc_table.relation_name = $2;
      free($2);
    }
    ;
    
create_index_stmt:    /*create index 语句的语法解析树*/
     CREATE INDEX ID ON ID LBRACE id_list RBRACE
    {
      $$ = new ParsedSqlNode(SCF_CREATE_INDEX);
      CreateIndexSqlNode &create_index = $$->create_index;
      create_index.index_name = $3;
      create_index.relation_name = $5;
      if ($7 != nullptr) {
        create_index.attribute_names.swap(*$7); 
        delete $7; 
      }
      free($3);
      free($5);
    }
    | CREATE UNIQUE INDEX ID ON ID LBRACE id_list RBRACE
    {
      $$ = new ParsedSqlNode(SCF_CREATE_INDEX);
      CreateIndexSqlNode &create_index = $$->create_index;
      create_index.unique = true;
      create_index.index_name = $4;
      create_index.relation_name = $6;
      if ($8 != nullptr) {
        create_index.attribute_names.swap(*$8); 
        delete $8; 
      }
      free($4);
      free($6);
    }
    ;

show_index_stmt:    /*show index 语法解析树*/
    SHOW INDEX FROM ID
    {
      $$ = new ParsedSqlNode(SCF_SHOW_INDEX);
      $$->show_index.relation_name = $4;
      free($4);
    }
    ;

drop_index_stmt:      /*drop index 语句的语法解析树*/
    DROP INDEX ID ON ID
    {
      $$ = new ParsedSqlNode(SCF_DROP_INDEX);
      $$->drop_index.index_name = $3;
      $$->drop_index.relation_name = $5;
      free($3);
      free($5);
    }
    ;
create_table_stmt:    /*create table 语句的语法解析树*/
    CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE
    {
      $$ = new ParsedSqlNode(SCF_CREATE_TABLE);
      CreateTableSqlNode &create_table = $$->create_table;
      create_table.relation_name = $3;
      free($3);

      std::vector<AttrInfoSqlNode> *src_attrs = $6;

      if (src_attrs != nullptr) {
        create_table.attr_infos.swap(*src_attrs);
      }
      create_table.attr_infos.emplace_back(*$5);
      std::reverse(create_table.attr_infos.begin(), create_table.attr_infos.end());
      delete $5;
    }
    ;
attr_def_list:
    /* empty */
    {
      $$ = nullptr;
    }
    | COMMA attr_def attr_def_list
    {
      if ($3 != nullptr) {
        $$ = $3;
      } else {
        $$ = new std::vector<AttrInfoSqlNode>;
      }
      $$->emplace_back(*$2);
      delete $2;
    }
    ;
    
attr_def:
    ID type LBRACE number RBRACE nullable
    {
      $$ = new AttrInfoSqlNode;
      $$->type = (AttrType)$2;
      $$->name = $1;
      $$->length = $4;
      $$->nullable = $6;
      free($1);
    }
    | ID type nullable
    {
      $$ = new AttrInfoSqlNode;
      $$->type = (AttrType)$2;
      $$->name = $1;
      if($$->type==TEXTS){
        $$->length = 65535;
      }else{
        $$->length = 4;
      }
      $$->nullable = $3;
      free($1);
    }
    ;

nullable:
    /* empty */
    {
      $$ = true; // 字段默认是可以为null的
    }
    | NOT NULL_T
    {
      $$ = false;
    }
    | NULL_T
    {
      $$ = true;
    }
    ;

number:
    NUMBER {$$ = $1;}
    ;
type:
    INT_T      { $$=INTS; }
    | STRING_T { $$=CHARS; }
    | TEXT_T   { $$=TEXTS; }
    | FLOAT_T  { $$=FLOATS; }
    | DATE_T   { $$=DATES;}
    ;
insert_stmt:        /*insert   语句的语法解析树*/
    INSERT INTO ID VALUES value_list_list  
    {
      $$ = new ParsedSqlNode(SCF_INSERT);
      $$->insertion.relation_name = $3;
      $$->insertion.values_list = *$5;
      free($3);
    }
    ;

value_list_list:
      LBRACE value_list RBRACE 
    {
      $$ = new std::vector<std::vector<Value>>{*$2};
      delete $2;
    }
    | value_list_list COMMA LBRACE value_list RBRACE
    {
      $$->emplace_back(*$4);
      delete $4;
    }
    ;


value_list:
    value /* return a pointer */
  {
    $$ = new std::vector<Value>{*$1};
    delete $1; /* relese the pointer*/
  }
  | value_list COMMA value
  {
    $$->emplace_back(*$3);
    delete $3;
  }
  ;


value:
    NUMBER {
      $$ = new Value((int)$1);
      @$ = @1;
    }
    |FLOAT {
      $$ = new Value((float)$1);
      @$ = @1;
    }
    |SSS {
      char *tmp = common::substr($1,1,strlen($1)-2);
      $$ = new Value(tmp);
      free(tmp);
    }
    | NULL_T {
      $$ = new Value();
    }
    ;
    
delete_stmt:    /*  delete 语句的语法解析树*/
    DELETE FROM ID where 
    {
      $$ = new ParsedSqlNode(SCF_DELETE);
      $$->deletion.relation_name = $3;
      if ($4 != nullptr) {
        $$->deletion.conditions.swap(*$4);
        delete $4;
      }
      free($3);
    }
    ;
update_stmt:      /*  update 语句的语法解析树*/
    UPDATE ID SET update_list where 
    {
      $$ = new ParsedSqlNode(SCF_UPDATE);
      $$->update.relation_name = $2;
      $$->update.attr_list = $4->first;
      $$->update.expr_list = $4->second;

      if ($5 != nullptr) {
        $$->update.conditions.swap(*$5);
        delete $5;
      }
      free($2);
      delete $4;
    }
    ;

update_list:
    ID EQ parse_expr
    {
      $$ = new std::pair<std::vector<std::string>, std::vector<ParseExpr *>>;
      $$->first.emplace_back($1);
      $$->second.emplace_back($3);

      delete $1;
    }
    | update_list COMMA ID EQ parse_expr
    {
      $$ = $1;
      $$->first.emplace_back($3);
      $$->second.emplace_back($5);
      delete $3;
    }
    ;

select_stmt:        /*  select 语句的语法解析树*/
    SELECT rel_attr_list_opt aggre_node_list_opt FROM rel_list select_join_list where select_order_list
    {
      $$ = new ParsedSqlNode(SCF_SELECT);
      if ($2 != nullptr) {
        $$->selection.attributes.swap(*$2);
        delete $2;
      }
      if ($3 != nullptr) {
        $$->selection.aggregations.swap(*$3);
        delete $3;
      }
      if ($5 != nullptr) {
        $$->selection.relations.swap(*$5);
        delete $5;
      }
      if ($6 != nullptr) {
        $$->selection.joinctions.swap(*$6);
        delete $6;
      }
      if ($7 != nullptr) {
        $$->selection.conditions.swap(*$7);
        delete $7;
      }
      if ($8 != nullptr) {
        $$->selection.orders.swap(*$8);
        delete $8;
      }
    }
    ;


aggre_node_list_opt:
      aggre_node_list
    {
      $$ = $1;
    }
    | /* empty */
    {
      $$ = nullptr;
    }
    ;

aggre_node_list:
      aggre_node
    {
      $$ = new std::vector<AggreSqlNode>{*$1}; 
      delete $1; 
    }
    | aggre_node_list COMMA aggre_node
    {
      $$->emplace_back(*$3); 
      delete $3; 
    }
    ;

aggre_node:
      aggre_type LBRACE rel_attr RBRACE
    {
      $$ = new AggreSqlNode;
      $$->aggre_type = $1;
      if ($3 != nullptr) {
        $$->attribute_name = *$3; 
        delete $3; 
      }
    }
    | aggre_type LBRACE rel_attr RBRACE AS rel_name
    {
      $$ = new AggreSqlNode;
      $$->aggre_type = $1;
      if ($3 != nullptr) {
        $$->attribute_name = *$3; 
        delete $3; 
      }
      if($6 != nullptr){
        $$->alias = $6;
        free($6);
      }
    }
    | aggre_type LBRACE rel_attr RBRACE rel_name
    {
      $$ = new AggreSqlNode;
      $$->aggre_type = $1;
      if ($3 != nullptr) {
        $$->attribute_name = *$3; 
        delete $3; 
      }
      if($5 != nullptr){
        $$->alias = $5;
        free($5);
      }
    }
    ;

rel_attr_list_opt:
      rel_attr_list
    {
      $$ = $1; 
    }
    | /* empty */
    {
      $$ = nullptr; 
    }
    ;

rel_attr_list:
      rel_attr
    {
      $$ = new std::vector<RelAttrSqlNode>{*$1}; 
      delete $1; 
    }
    | rel_attr_list COMMA rel_attr
    {
      $$->emplace_back(*$3); 
      delete $3; 
    }
    ;

rel_attr:
     attr_name
    {
      $$ = new RelAttrSqlNode{"","", $1,""};
      free($1);
    }
    | attr_name attr_name
    {
      $$ = new RelAttrSqlNode{"","", $1,$2};
      free($1);
      free($2);
    }
    | attr_name AS attr_name
    {
      $$ = new RelAttrSqlNode{"","", $1,$3};
      free($1);
      free($3);
    }
    | rel_name DOT attr_name
    {
      $$ = new RelAttrSqlNode{$1,$1,$3,""};
      free($1);
      free($3);
    }
    | rel_name DOT attr_name attr_name
    {
      $$ = new RelAttrSqlNode{$1,$1,$3,$4};
      free($1);
      free($3);
      free($4);
    }
    | rel_name DOT attr_name AS attr_name
    {
      $$ = new RelAttrSqlNode{$1,$1,$3,$5};
      free($1);
      free($3);
      free($5);
    }
    ;


/**
 * @description: JoinSql节点，包括表名和一些列条件
 * @return {JoinSqlNode*} 
 */
join_node:
      INNER JOIN rel_name ON condition_list
    {
      $$ = new JoinSqlNode{$3,*$5};
      delete $3;
      delete $5;
    }
    ;

select_join_list:
      /*empty*/
    {
      $$ = nullptr; 
    }
    | join_list
    {
      $$ = $1; 
    }
    ;
/**
 * @description: 递归解析所有的join
 * @return {std::vector<JoinSqlNode>*} 
 */
 join_list:
     join_node
    {
      $$ = new std::vector<JoinSqlNode>{*$1};
      delete $1;   
    }
    | join_list join_node
    {
      $$->emplace_back(*$2);
      delete $2;
    }
    ;

select_order_list:
      /* empty */
    {
      $$ = nullptr; // 没有order
    }
    | ORDER BY order_list
    {
      $$ = $3;
    }
    ;

/**
 * @description: 递归解析所有的orderby
 * @return {OrderSqlNode*} 
 */
order_list:
      order_node
    {
      $$ = new std::vector<OrderSqlNode>{*$1};
      delete $1;
    }
    | order_list COMMA order_node
    {
      $$->emplace_back(*$3);
      delete $3;
    }
    ;

/**
 * @description: OrderBy Sql Node
 * @return {std::vector<OrderSqlNode>*} 
 */
order_node:
      rel_attr order_type
    {
      $$ = new OrderSqlNode{*$1,$2};
      delete $1;
    }
    ;

order_type:
           { $$ = ORDER_ASC; }
    | ASC  { $$ = ORDER_ASC; }
    | DESC { $$ = ORDER_DESC; }
    ;

rel_node:
    rel_name
    {
      $$ = new AttrSqlNode{$1,""};
      free($1);
    }
    | rel_name rel_name
    {
      $$ = new AttrSqlNode{$1,$2};
      free($1);
      free($2);
    }
    | rel_name AS rel_name
    {
      $$ = new AttrSqlNode{$1,$3};
      free($1);
      free($3);
    }
    ;

/**
 * @description: 获取表名的列表
 * @return {std::vector<std::string>*} 
 */
rel_list:
      /* empty */
    {
      $$ = nullptr;
    }
    | rel_node
    {
      $$ = new std::vector<AttrSqlNode>{*$1};
      delete $1; 
    }
    | rel_list COMMA rel_node
    {
      $$->emplace_back(*$3); 
      delete $3;
    }
    ;

parse_expr: 
    value
    {
      $$ = new ParseValueExpr(*$1);
      delete $1;
    }
    | rel_attr
    {
      std::string &table_name = $1->relation_name;
      std::string &field_name = $1->attribute_name;
      $$ = new ParseFieldExpr(table_name,field_name);
      delete $1;
    }
    | LBRACE select_stmt RBRACE
    {
      $$ = new ParseSubQueryExpr($2->selection);
    }
    | LBRACE value_list RBRACE 
    {
      $$ = new ParseValueListExpr(*$2);
      delete $2;
    }

where:
    /* empty */
    {
      $$ = nullptr;
    }
    | WHERE exists_op LBRACE select_stmt RBRACE
    {
      $$ = new std::vector<ConditionSqlNode>;
      //TODO: 这里糊了一下，其实左边是没有表达式的，但是为了方便，这里就先这样写了
      ParseExpr * left = new ParseValueExpr();
      ParseExpr *  right = new ParseSubQueryExpr($4->selection);
      $$->emplace_back(ConditionSqlNode{left,$2,right});
    }
    | WHERE condition_list 
    {
      $$ = $2;
    }
    ;
condition_list:
    /* empty */
    {
      $$ = nullptr;
    }
    | condition {
      $$ = new std::vector<ConditionSqlNode>;
      $$->emplace_back(*$1);
      delete $1;
    }
    | condition AND condition_list {
      $$ = $3;
      $1->has_or = false;
      $$->emplace_back(*$1);
      delete $1;
    }
    | condition OR condition_list {
      $$ = $3;
      $1->has_or = true;
      $$->emplace_back(*$1);
      delete $1;
    }
    ;
condition:
    parse_expr comp_op parse_expr
    {
      $$ = new ConditionSqlNode;
      $$->left = $1;

      $$->comp = $2;

      $$->right = $3;
    }
    | parse_expr in_op parse_expr
    {
      $$ = new ConditionSqlNode;
      $$->left = $1;

      $$->comp = $2;

      $$->right = $3;
    }
    ;


calc_stmt:
    CALC expression_list
    {
      $$ = new ParsedSqlNode(SCF_CALC);
      std::reverse($2->begin(), $2->end());
      $$->calc.expressions.swap(*$2);
      delete $2;
    }
    ;

expression_list:
    expression
    {
      $$ = new std::vector<Expression*>;
      $$->emplace_back($1);
    }
    | expression COMMA expression_list
    {
      if ($3 != nullptr) {
        $$ = $3;
      } else {
        $$ = new std::vector<Expression *>;
      }
      $$->emplace_back($1);
    }
    ;
expression:
    expression '+' expression {
      $$ = create_arithmetic_expression(ArithmeticExpr::Type::ADD, $1, $3, sql_string, &@$);
    }
    | expression '-' expression {
      $$ = create_arithmetic_expression(ArithmeticExpr::Type::SUB, $1, $3, sql_string, &@$);
    }
    | expression '*' expression {
      $$ = create_arithmetic_expression(ArithmeticExpr::Type::MUL, $1, $3, sql_string, &@$);
    }
    | expression '/' expression {
      $$ = create_arithmetic_expression(ArithmeticExpr::Type::DIV, $1, $3, sql_string, &@$);
    }
    | LBRACE expression RBRACE {
      $$ = $2;
      $$->set_name(token_name(sql_string, &@$));
    }
    | '-' expression %prec UMINUS {
      $$ = create_arithmetic_expression(ArithmeticExpr::Type::NEGATIVE, $2, nullptr, sql_string, &@$);
    }
    | value {
      $$ = new ValueExpr(*$1);
      $$->set_name(token_name(sql_string, &@$));
      delete $1;
    }
    ;

comp_op:
      EQ { $$ = EQUAL_TO; }
    | LT { $$ = LESS_THAN; }
    | GT { $$ = GREAT_THAN; }
    | LE { $$ = LESS_EQUAL; }
    | GE { $$ = GREAT_EQUAL; }
    | NE { $$ = NOT_EQUAL; }
    | LK { $$ = LIKE; }
    | NOT LK { $$ = NOT_LIKE;}
    | IS_ { $$ = IS;}
    | IS_ NOT { $$ = IS_NOT;}
    ;

in_op:
      IN_OP {$$ = IN;}
    | NOT IN_OP {$$ = NOT_IN;}
    ;

exists_op:
      EXISTS_OP {$$ = EXISTS;}
    | NOT EXISTS_OP {$$ = NOT_EXISTS;}
    ;

aggre_type:
      SUM   { $$ = AGGRE_SUM; }
    | AVG   { $$ = AGGRE_AVG; }
    | COUNT { $$ = AGGRE_COUNT; }
    | MAX   { $$ = AGGRE_MAX; }
    | MIN   { $$ = AGGRE_MIN; }
    ;

load_data_stmt:
    LOAD DATA INFILE SSS INTO TABLE ID 
    {
      char *tmp_file_name = common::substr($4, 1, strlen($4) - 2);
      
      $$ = new ParsedSqlNode(SCF_LOAD_DATA);
      $$->load_data.relation_name = $7;
      $$->load_data.file_name = tmp_file_name;
      free($7);
      free(tmp_file_name);
    }
    ;

explain_stmt:
    EXPLAIN command_wrapper
    {
      $$ = new ParsedSqlNode(SCF_EXPLAIN);
      $$->explain.sql_node = std::unique_ptr<ParsedSqlNode>($2);
    }
    ;

set_variable_stmt:
    SET ID EQ value
    {
      $$ = new ParsedSqlNode(SCF_SET_VARIABLE);
      $$->set_variable.name  = $2;
      $$->set_variable.value = *$4;
      free($2);
      delete $4;
    }
    ;

opt_semicolon: /*empty*/
    | SEMICOLON
    ;


id_list:
      ID
    {
      $$ = new std::vector<std::string>{$1}; 
      free($1); 
    }
    | id_list COMMA ID
    {
      $$->emplace_back($3);
      free($3);
    }
    ;

rel_name: 
    ID 
    {
       $$ = $1; 
    }
    ;

/**
 * @description: 返回列名, 列名可能为 `*`, 在此进行特判
 * @return {*} char *
 */
attr_name:
      ID // ID 返回的是一个new的数据
    {
      $$ = $1;
    }
    | '*'
    {
      // 使用malloc为了和他的free配合
      char *str = (char *)malloc(strlen("*") + 1);  // 加1用于存储字符串结束符'\0'
      strcpy(str, "*");
      $$ = str;
    }
%%
//_____________________________________________________________________
extern void scan_string(const char *str, yyscan_t scanner);

int sql_parse(const char *s, ParsedSqlResult *sql_result) {
  yyscan_t scanner;
  yylex_init(&scanner);
  scan_string(s, scanner);
  int result = yyparse(s, sql_result, scanner);
  yylex_destroy(scanner);
  return result;
}
