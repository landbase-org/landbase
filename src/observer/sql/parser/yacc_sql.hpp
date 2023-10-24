/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
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
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

#ifndef YY_YY_YACC_SQL_HPP_INCLUDED
# define YY_YY_YACC_SQL_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    SEMICOLON = 258,
    CREATE = 259,
    DROP = 260,
    TABLE = 261,
    TABLES = 262,
    INDEX = 263,
    CALC = 264,
    SELECT = 265,
    INNER = 266,
    JOIN = 267,
    ORDER = 268,
    ASC = 269,
    BY = 270,
    DESC = 271,
    SHOW = 272,
    SYNC = 273,
    INSERT = 274,
    DELETE = 275,
    UPDATE = 276,
    LBRACE = 277,
    RBRACE = 278,
    COMMA = 279,
    TRX_BEGIN = 280,
    TRX_COMMIT = 281,
    TRX_ROLLBACK = 282,
    INT_T = 283,
    STRING_T = 284,
    FLOAT_T = 285,
    DATE_T = 286,
    HELP = 287,
    EXIT = 288,
    DOT = 289,
    INTO = 290,
    VALUES = 291,
    FROM = 292,
    WHERE = 293,
    AND = 294,
    SET = 295,
    ON = 296,
    LOAD = 297,
    DATA = 298,
    INFILE = 299,
    EXPLAIN = 300,
    EQ = 301,
    LT = 302,
    GT = 303,
    LE = 304,
    GE = 305,
    NE = 306,
    SUM = 307,
    COUNT = 308,
    AVG = 309,
    MIN = 310,
    MAX = 311,
    NOT = 312,
    LK = 313,
    NUMBER = 314,
    FLOAT = 315,
    ID = 316,
    AGGRE_ATTR = 317,
    SSS = 318,
    UMINUS = 319
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 116 "yacc_sql.y"

  ParsedSqlNode *                   sql_node;
  ConditionSqlNode *                condition;
  Value *                           value;
  enum CompOp                       comp;
  enum AggreType                    aggre_type;
  enum OrderType                    order_type;
  AggreTypeNode *                   aggre_node;
  RelAttrSqlNode *                  rel_attr;
  std::vector<AttrInfoSqlNode> *    attr_infos;
  AttrInfoSqlNode *                 attr_info;
  Expression *                      expression;
  JoinSqlNode *                     join_node;
  OrderSqlNode *                    order_node;
  std::vector<Expression *> *       expression_list;
  std::vector<Value> *              value_list;
  std::vector<std::vector<Value>> * value_list_list; 
  std::pair<std::vector<std::string>, std::vector<Value>> * update_list;
  std::vector<ConditionSqlNode> *   condition_list;
  std::vector<RelAttrSqlNode> *     rel_attr_list;
  std::vector<std::string> *        relation_list;
  std::vector<std::string> *        aggre_attr_list;
  std::vector<JoinSqlNode> *        join_list;
  std::vector<OrderSqlNode> *       order_list;
  char *                            string; // 是char*类型, 需要free
  int                               number;
  float                             floats;

#line 151 "yacc_sql.hpp"

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
