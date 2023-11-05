/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_YACC_SQL_HPP_INCLUDED
# define YY_YY_YACC_SQL_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    SEMICOLON = 258,               /* SEMICOLON  */
    CREATE = 259,                  /* CREATE  */
    DROP = 260,                    /* DROP  */
    TABLE = 261,                   /* TABLE  */
    TABLES = 262,                  /* TABLES  */
    INDEX = 263,                   /* INDEX  */
    UNIQUE = 264,                  /* UNIQUE  */
    CALC = 265,                    /* CALC  */
    SELECT = 266,                  /* SELECT  */
    INNER = 267,                   /* INNER  */
    JOIN = 268,                    /* JOIN  */
    ORDER = 269,                   /* ORDER  */
    ASC = 270,                     /* ASC  */
    BY = 271,                      /* BY  */
    DESC = 272,                    /* DESC  */
    SHOW = 273,                    /* SHOW  */
    SYNC = 274,                    /* SYNC  */
    INSERT = 275,                  /* INSERT  */
    DELETE = 276,                  /* DELETE  */
    UPDATE = 277,                  /* UPDATE  */
    LBRACE = 278,                  /* LBRACE  */
    RBRACE = 279,                  /* RBRACE  */
    COMMA = 280,                   /* COMMA  */
    TRX_BEGIN = 281,               /* TRX_BEGIN  */
    TRX_COMMIT = 282,              /* TRX_COMMIT  */
    TRX_ROLLBACK = 283,            /* TRX_ROLLBACK  */
    INT_T = 284,                   /* INT_T  */
    STRING_T = 285,                /* STRING_T  */
    TEXT_T = 286,                  /* TEXT_T  */
    FLOAT_T = 287,                 /* FLOAT_T  */
    DATE_T = 288,                  /* DATE_T  */
    NULL_T = 289,                  /* NULL_T  */
    HELP = 290,                    /* HELP  */
    EXIT = 291,                    /* EXIT  */
    DOT = 292,                     /* DOT  */
    INTO = 293,                    /* INTO  */
    VALUES = 294,                  /* VALUES  */
    AS = 295,                      /* AS  */
    FROM = 296,                    /* FROM  */
    WHERE = 297,                   /* WHERE  */
    AND = 298,                     /* AND  */
    OR = 299,                      /* OR  */
    SET = 300,                     /* SET  */
    ON = 301,                      /* ON  */
    LOAD = 302,                    /* LOAD  */
    DATA = 303,                    /* DATA  */
    INFILE = 304,                  /* INFILE  */
    EXPLAIN = 305,                 /* EXPLAIN  */
    EQ = 306,                      /* EQ  */
    LT = 307,                      /* LT  */
    GT = 308,                      /* GT  */
    LE = 309,                      /* LE  */
    GE = 310,                      /* GE  */
    NE = 311,                      /* NE  */
    SUM = 312,                     /* SUM  */
    COUNT = 313,                   /* COUNT  */
    AVG = 314,                     /* AVG  */
    MIN = 315,                     /* MIN  */
    MAX = 316,                     /* MAX  */
    IS_ = 317,                     /* IS_  */
    NOT = 318,                     /* NOT  */
    LK = 319,                      /* LK  */
    IN_OP = 320,                   /* IN_OP  */
    EXISTS_OP = 321,               /* EXISTS_OP  */
    NUMBER = 322,                  /* NUMBER  */
    FLOAT = 323,                   /* FLOAT  */
    ID = 324,                      /* ID  */
    SSS = 325,                     /* SSS  */
    UMINUS = 326                   /* UMINUS  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 125 "yacc_sql.y"

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

#line 170 "yacc_sql.hpp"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif




int yyparse (const char * sql_string, ParsedSqlResult * sql_result, void * scanner);


#endif /* !YY_YY_YACC_SQL_HPP_INCLUDED  */
