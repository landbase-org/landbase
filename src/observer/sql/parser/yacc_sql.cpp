/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 2

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 2 "yacc_sql.y"


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


#line 117 "yacc_sql.cpp"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "yacc_sql.hpp"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_SEMICOLON = 3,                  /* SEMICOLON  */
  YYSYMBOL_CREATE = 4,                     /* CREATE  */
  YYSYMBOL_DROP = 5,                       /* DROP  */
  YYSYMBOL_TABLE = 6,                      /* TABLE  */
  YYSYMBOL_TABLES = 7,                     /* TABLES  */
  YYSYMBOL_INDEX = 8,                      /* INDEX  */
  YYSYMBOL_UNIQUE = 9,                     /* UNIQUE  */
  YYSYMBOL_CALC = 10,                      /* CALC  */
  YYSYMBOL_SELECT = 11,                    /* SELECT  */
  YYSYMBOL_INNER = 12,                     /* INNER  */
  YYSYMBOL_JOIN = 13,                      /* JOIN  */
  YYSYMBOL_ORDER = 14,                     /* ORDER  */
  YYSYMBOL_ASC = 15,                       /* ASC  */
  YYSYMBOL_BY = 16,                        /* BY  */
  YYSYMBOL_DESC = 17,                      /* DESC  */
  YYSYMBOL_SHOW = 18,                      /* SHOW  */
  YYSYMBOL_SYNC = 19,                      /* SYNC  */
  YYSYMBOL_INSERT = 20,                    /* INSERT  */
  YYSYMBOL_DELETE = 21,                    /* DELETE  */
  YYSYMBOL_UPDATE = 22,                    /* UPDATE  */
  YYSYMBOL_LBRACE = 23,                    /* LBRACE  */
  YYSYMBOL_RBRACE = 24,                    /* RBRACE  */
  YYSYMBOL_COMMA = 25,                     /* COMMA  */
  YYSYMBOL_TRX_BEGIN = 26,                 /* TRX_BEGIN  */
  YYSYMBOL_TRX_COMMIT = 27,                /* TRX_COMMIT  */
  YYSYMBOL_TRX_ROLLBACK = 28,              /* TRX_ROLLBACK  */
  YYSYMBOL_INT_T = 29,                     /* INT_T  */
  YYSYMBOL_STRING_T = 30,                  /* STRING_T  */
  YYSYMBOL_TEXT_T = 31,                    /* TEXT_T  */
  YYSYMBOL_FLOAT_T = 32,                   /* FLOAT_T  */
  YYSYMBOL_DATE_T = 33,                    /* DATE_T  */
  YYSYMBOL_NULL_T = 34,                    /* NULL_T  */
  YYSYMBOL_HELP = 35,                      /* HELP  */
  YYSYMBOL_EXIT = 36,                      /* EXIT  */
  YYSYMBOL_DOT = 37,                       /* DOT  */
  YYSYMBOL_INTO = 38,                      /* INTO  */
  YYSYMBOL_VALUES = 39,                    /* VALUES  */
  YYSYMBOL_AS = 40,                        /* AS  */
  YYSYMBOL_FROM = 41,                      /* FROM  */
  YYSYMBOL_WHERE = 42,                     /* WHERE  */
  YYSYMBOL_AND = 43,                       /* AND  */
  YYSYMBOL_OR = 44,                        /* OR  */
  YYSYMBOL_SET = 45,                       /* SET  */
  YYSYMBOL_ON = 46,                        /* ON  */
  YYSYMBOL_LOAD = 47,                      /* LOAD  */
  YYSYMBOL_DATA = 48,                      /* DATA  */
  YYSYMBOL_INFILE = 49,                    /* INFILE  */
  YYSYMBOL_EXPLAIN = 50,                   /* EXPLAIN  */
  YYSYMBOL_EQ = 51,                        /* EQ  */
  YYSYMBOL_LT = 52,                        /* LT  */
  YYSYMBOL_GT = 53,                        /* GT  */
  YYSYMBOL_LE = 54,                        /* LE  */
  YYSYMBOL_GE = 55,                        /* GE  */
  YYSYMBOL_NE = 56,                        /* NE  */
  YYSYMBOL_SUM = 57,                       /* SUM  */
  YYSYMBOL_COUNT = 58,                     /* COUNT  */
  YYSYMBOL_AVG = 59,                       /* AVG  */
  YYSYMBOL_MIN = 60,                       /* MIN  */
  YYSYMBOL_MAX = 61,                       /* MAX  */
  YYSYMBOL_IS_ = 62,                       /* IS_  */
  YYSYMBOL_NOT = 63,                       /* NOT  */
  YYSYMBOL_LK = 64,                        /* LK  */
  YYSYMBOL_IN_OP = 65,                     /* IN_OP  */
  YYSYMBOL_EXISTS_OP = 66,                 /* EXISTS_OP  */
  YYSYMBOL_GROUP = 67,                     /* GROUP  */
  YYSYMBOL_HAVING = 68,                    /* HAVING  */
  YYSYMBOL_NUMBER = 69,                    /* NUMBER  */
  YYSYMBOL_FLOAT = 70,                     /* FLOAT  */
  YYSYMBOL_ID = 71,                        /* ID  */
  YYSYMBOL_SSS = 72,                       /* SSS  */
  YYSYMBOL_73_ = 73,                       /* '+'  */
  YYSYMBOL_74_ = 74,                       /* '-'  */
  YYSYMBOL_75_ = 75,                       /* '*'  */
  YYSYMBOL_76_ = 76,                       /* '/'  */
  YYSYMBOL_UMINUS = 77,                    /* UMINUS  */
  YYSYMBOL_YYACCEPT = 78,                  /* $accept  */
  YYSYMBOL_commands = 79,                  /* commands  */
  YYSYMBOL_command_wrapper = 80,           /* command_wrapper  */
  YYSYMBOL_exit_stmt = 81,                 /* exit_stmt  */
  YYSYMBOL_help_stmt = 82,                 /* help_stmt  */
  YYSYMBOL_sync_stmt = 83,                 /* sync_stmt  */
  YYSYMBOL_begin_stmt = 84,                /* begin_stmt  */
  YYSYMBOL_commit_stmt = 85,               /* commit_stmt  */
  YYSYMBOL_rollback_stmt = 86,             /* rollback_stmt  */
  YYSYMBOL_drop_table_stmt = 87,           /* drop_table_stmt  */
  YYSYMBOL_show_tables_stmt = 88,          /* show_tables_stmt  */
  YYSYMBOL_desc_table_stmt = 89,           /* desc_table_stmt  */
  YYSYMBOL_create_index_stmt = 90,         /* create_index_stmt  */
  YYSYMBOL_show_index_stmt = 91,           /* show_index_stmt  */
  YYSYMBOL_drop_index_stmt = 92,           /* drop_index_stmt  */
  YYSYMBOL_create_table_stmt = 93,         /* create_table_stmt  */
  YYSYMBOL_attr_def_list = 94,             /* attr_def_list  */
  YYSYMBOL_attr_def = 95,                  /* attr_def  */
  YYSYMBOL_nullable = 96,                  /* nullable  */
  YYSYMBOL_number = 97,                    /* number  */
  YYSYMBOL_type = 98,                      /* type  */
  YYSYMBOL_insert_stmt = 99,               /* insert_stmt  */
  YYSYMBOL_value_list_list = 100,          /* value_list_list  */
  YYSYMBOL_value_list = 101,               /* value_list  */
  YYSYMBOL_value = 102,                    /* value  */
  YYSYMBOL_delete_stmt = 103,              /* delete_stmt  */
  YYSYMBOL_update_stmt = 104,              /* update_stmt  */
  YYSYMBOL_update_list = 105,              /* update_list  */
  YYSYMBOL_select_stmt = 106,              /* select_stmt  */
  YYSYMBOL_groupby_having_node_opt = 107,  /* groupby_having_node_opt  */
  YYSYMBOL_groupby_having_node = 108,      /* groupby_having_node  */
  YYSYMBOL_rel_attr_aggre_list = 109,      /* rel_attr_aggre_list  */
  YYSYMBOL_rel_attr_aggre_node = 110,      /* rel_attr_aggre_node  */
  YYSYMBOL_aggre_node = 111,               /* aggre_node  */
  YYSYMBOL_rel_attr_list = 112,            /* rel_attr_list  */
  YYSYMBOL_rel_attr = 113,                 /* rel_attr  */
  YYSYMBOL_join_node = 114,                /* join_node  */
  YYSYMBOL_select_join_list = 115,         /* select_join_list  */
  YYSYMBOL_join_list = 116,                /* join_list  */
  YYSYMBOL_select_order_list = 117,        /* select_order_list  */
  YYSYMBOL_order_list = 118,               /* order_list  */
  YYSYMBOL_order_node = 119,               /* order_node  */
  YYSYMBOL_order_type = 120,               /* order_type  */
  YYSYMBOL_rel_node = 121,                 /* rel_node  */
  YYSYMBOL_rel_list = 122,                 /* rel_list  */
  YYSYMBOL_parse_expr = 123,               /* parse_expr  */
  YYSYMBOL_where = 124,                    /* where  */
  YYSYMBOL_condition_list = 125,           /* condition_list  */
  YYSYMBOL_condition = 126,                /* condition  */
  YYSYMBOL_calc_stmt = 127,                /* calc_stmt  */
  YYSYMBOL_expression_list = 128,          /* expression_list  */
  YYSYMBOL_expression = 129,               /* expression  */
  YYSYMBOL_comp_op = 130,                  /* comp_op  */
  YYSYMBOL_in_op = 131,                    /* in_op  */
  YYSYMBOL_exists_op = 132,                /* exists_op  */
  YYSYMBOL_aggre_type = 133,               /* aggre_type  */
  YYSYMBOL_load_data_stmt = 134,           /* load_data_stmt  */
  YYSYMBOL_explain_stmt = 135,             /* explain_stmt  */
  YYSYMBOL_set_variable_stmt = 136,        /* set_variable_stmt  */
  YYSYMBOL_opt_semicolon = 137,            /* opt_semicolon  */
  YYSYMBOL_id_list = 138,                  /* id_list  */
  YYSYMBOL_rel_name = 139,                 /* rel_name  */
  YYSYMBOL_attr_name = 140                 /* attr_name  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int16 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if 1

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* 1 */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE) \
             + YYSIZEOF (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  79
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   279

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  78
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  63
/* YYNRULES -- Number of rules.  */
#define YYNRULES  155
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  274

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   328


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,    75,    73,     2,    74,     2,    76,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    77
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   240,   240,   248,   249,   250,   251,   252,   253,   254,
     255,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   272,   278,   283,   289,   295,   301,
     307,   314,   320,   328,   341,   358,   367,   377,   396,   399,
     412,   421,   438,   441,   445,   452,   455,   456,   457,   458,
     459,   462,   472,   477,   486,   491,   500,   504,   508,   513,
     519,   531,   548,   556,   566,   600,   605,   611,   616,   625,
     630,   638,   643,   652,   657,   666,   679,   684,   692,   697,
     703,   709,   715,   722,   737,   747,   750,   760,   765,   774,
     777,   788,   793,   805,   813,   814,   815,   819,   824,   830,
     844,   847,   852,   860,   865,   872,   876,   881,   892,   895,
     903,   910,   913,   918,   924,   932,   941,   954,   964,   969,
     980,   983,   986,   989,   992,   996,   999,  1007,  1008,  1009,
    1010,  1011,  1012,  1013,  1014,  1015,  1016,  1020,  1021,  1025,
    1026,  1030,  1031,  1032,  1033,  1034,  1038,  1051,  1059,  1069,
    1070,  1075,  1080,  1088,  1099,  1103
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if 1
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "SEMICOLON", "CREATE",
  "DROP", "TABLE", "TABLES", "INDEX", "UNIQUE", "CALC", "SELECT", "INNER",
  "JOIN", "ORDER", "ASC", "BY", "DESC", "SHOW", "SYNC", "INSERT", "DELETE",
  "UPDATE", "LBRACE", "RBRACE", "COMMA", "TRX_BEGIN", "TRX_COMMIT",
  "TRX_ROLLBACK", "INT_T", "STRING_T", "TEXT_T", "FLOAT_T", "DATE_T",
  "NULL_T", "HELP", "EXIT", "DOT", "INTO", "VALUES", "AS", "FROM", "WHERE",
  "AND", "OR", "SET", "ON", "LOAD", "DATA", "INFILE", "EXPLAIN", "EQ",
  "LT", "GT", "LE", "GE", "NE", "SUM", "COUNT", "AVG", "MIN", "MAX", "IS_",
  "NOT", "LK", "IN_OP", "EXISTS_OP", "GROUP", "HAVING", "NUMBER", "FLOAT",
  "ID", "SSS", "'+'", "'-'", "'*'", "'/'", "UMINUS", "$accept", "commands",
  "command_wrapper", "exit_stmt", "help_stmt", "sync_stmt", "begin_stmt",
  "commit_stmt", "rollback_stmt", "drop_table_stmt", "show_tables_stmt",
  "desc_table_stmt", "create_index_stmt", "show_index_stmt",
  "drop_index_stmt", "create_table_stmt", "attr_def_list", "attr_def",
  "nullable", "number", "type", "insert_stmt", "value_list_list",
  "value_list", "value", "delete_stmt", "update_stmt", "update_list",
  "select_stmt", "groupby_having_node_opt", "groupby_having_node",
  "rel_attr_aggre_list", "rel_attr_aggre_node", "aggre_node",
  "rel_attr_list", "rel_attr", "join_node", "select_join_list",
  "join_list", "select_order_list", "order_list", "order_node",
  "order_type", "rel_node", "rel_list", "parse_expr", "where",
  "condition_list", "condition", "calc_stmt", "expression_list",
  "expression", "comp_op", "in_op", "exists_op", "aggre_type",
  "load_data_stmt", "explain_stmt", "set_variable_stmt", "opt_semicolon",
  "id_list", "rel_name", "attr_name", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-190)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-154)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     158,   140,    81,    87,   -38,   -53,   111,  -190,     3,    34,
      42,  -190,  -190,  -190,  -190,  -190,    79,   107,   158,    84,
     155,  -190,  -190,  -190,  -190,  -190,  -190,  -190,  -190,  -190,
    -190,  -190,  -190,  -190,  -190,  -190,  -190,  -190,  -190,  -190,
    -190,  -190,    89,    93,   166,    96,   112,    87,  -190,  -190,
    -190,  -190,    87,  -190,  -190,    49,  -190,  -190,  -190,  -190,
    -190,   152,  -190,    44,  -190,  -190,  -190,   167,   154,    67,
    -190,  -190,   151,   124,   125,   153,   146,   160,  -190,  -190,
    -190,  -190,   177,   156,   130,  -190,   161,    25,  -190,    87,
      87,    87,    87,    87,   -38,   133,   -35,    64,    64,  -190,
    -190,   135,   178,   174,   147,   -25,   162,   149,   164,   173,
     165,  -190,  -190,    61,    61,  -190,  -190,  -190,  -190,  -190,
      13,   -32,   203,    72,  -190,  -190,   205,    45,  -190,   179,
     -12,  -190,   191,   101,   206,   209,   168,  -190,   220,   133,
    -190,   174,   225,   133,  -190,   -23,    64,  -190,   -25,   213,
      -5,   175,  -190,  -190,  -190,   159,  -190,    97,   219,   221,
       1,   172,  -190,   239,  -190,  -190,  -190,  -190,  -190,    -8,
     149,   222,   176,   226,   133,  -190,   234,  -190,  -190,   133,
    -190,  -190,   120,  -190,   227,   141,   228,  -190,  -190,  -190,
    -190,  -190,  -190,  -190,   188,   106,  -190,  -190,     1,     1,
       1,     1,   242,   -35,  -190,   204,   183,   189,  -190,   223,
    -190,   206,  -190,  -190,   148,   176,   214,   243,   194,  -190,
    -190,   -25,   -25,  -190,  -190,  -190,  -190,  -190,  -190,  -190,
    -190,  -190,   240,   241,     1,  -190,  -190,   244,  -190,  -190,
    -190,   192,   157,     1,   -35,   251,  -190,  -190,  -190,   163,
    -190,  -190,  -190,     0,  -190,  -190,  -190,   136,   245,  -190,
     -35,  -190,  -190,  -190,  -190,  -190,   -35,   -15,  -190,  -190,
     -35,     1,  -190,  -190
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,    26,     0,     0,
       0,    27,    28,    29,    25,    24,     0,     0,     0,     0,
     149,    23,    22,    15,    16,    17,    18,     9,    10,    11,
      12,    14,    13,     8,     5,     7,     6,     4,     3,    19,
      20,    21,     0,     0,     0,     0,     0,     0,    59,    56,
      57,    58,     0,   126,   117,   118,   141,   143,   142,   145,
     144,   154,   155,     0,    69,    71,    72,     0,     0,    78,
      32,    31,     0,     0,     0,     0,     0,     0,   147,     1,
     150,     2,     0,     0,     0,    30,     0,     0,   125,     0,
       0,     0,     0,     0,     0,   100,     0,     0,     0,   154,
      79,     0,     0,   108,     0,     0,     0,     0,     0,     0,
       0,   124,   119,   120,   121,   122,   123,    70,   153,   101,
      85,    97,     0,    81,    80,    35,     0,   111,    60,     0,
     108,   148,     0,     0,    38,     0,     0,    36,     0,     0,
      87,   108,    86,     0,    98,    73,     0,    82,     0,    51,
       0,     0,   139,   103,   104,     0,   110,   112,     0,     0,
       0,     0,    61,     0,    46,    47,    48,    49,    50,    42,
       0,     0,     0,     0,     0,   102,    89,    88,    99,     0,
      75,    83,     0,    54,     0,     0,     0,   140,   127,   128,
     129,   130,   131,   132,   135,     0,   133,   137,     0,     0,
     111,   111,     0,     0,    62,     0,     0,     0,    44,     0,
      41,    38,    37,   151,     0,     0,     0,     0,    66,    74,
      52,     0,     0,   106,   105,   136,   134,   138,   115,   116,
     113,   114,     0,     0,     0,   146,    45,     0,    43,    39,
      33,     0,     0,   111,     0,     0,    64,    65,    55,     0,
     109,   107,    63,    42,   152,    34,    84,    94,    90,    91,
       0,    53,    40,    95,    96,    93,     0,    67,    76,    92,
       0,   111,    77,    68
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -190,  -190,   253,  -190,  -190,  -190,  -190,  -190,  -190,  -190,
    -190,  -190,  -190,  -190,  -190,  -190,    58,   102,    20,  -190,
    -190,  -190,  -190,  -145,     4,  -190,  -190,  -190,  -136,  -190,
    -190,  -190,   180,  -190,  -190,    -4,   134,  -190,  -190,  -190,
    -190,     9,  -190,   138,  -190,  -156,  -114,  -189,  -190,  -190,
     190,    36,  -190,  -190,  -190,    -3,  -190,  -190,  -190,  -190,
      63,   -93,   -66
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,   171,   134,   210,   237,
     169,    34,   149,   182,   153,    35,    36,   130,    37,   246,
     247,    63,    64,    65,   267,   154,   140,   141,   142,   218,
     258,   259,   265,   119,   120,   155,   128,   156,   157,    38,
      54,    55,   198,   199,   158,   159,    39,    40,    41,    81,
     214,    68,    69
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      66,    67,   121,   100,   204,   185,     4,    53,   143,    48,
     270,   230,   231,   161,   186,   207,   162,   179,    70,    56,
      57,    58,    59,    60,   150,   138,   208,   176,   144,    48,
     127,   123,   124,    61,   208,    48,    61,    62,   139,   118,
      62,    73,   228,   229,    49,    50,   121,    51,   118,   111,
     178,    53,   180,   271,   256,   209,    53,   147,    56,    57,
      58,    59,    60,   209,    49,    50,   232,    51,   150,    94,
      49,    50,    61,    51,    89,    74,    62,   249,   252,    48,
     181,   216,   273,    87,    79,    95,   219,    45,    88,    46,
      66,    67,   122,    53,    53,    53,    53,    53,    90,    91,
      92,    93,    56,    57,    58,    59,    60,    98,   151,   131,
      47,   152,   146,    75,    49,    50,    61,    51,    71,    72,
      62,    48,    90,    91,    92,    93,   113,   114,   115,   116,
     164,   165,   166,   167,   168,    99,    92,    93,    99,    62,
     200,   201,    62,    99,   220,   221,    42,    62,    43,    44,
      76,   263,   183,   264,   183,    77,    49,    50,    80,    51,
      82,    52,     1,     2,    83,   223,   221,    85,     3,     4,
     226,   227,   240,   241,    84,     5,     6,     7,     8,     9,
      10,   255,   241,    86,    11,    12,    13,   261,   221,  -153,
      96,    97,   101,    14,    15,   102,   103,   105,   104,   233,
     107,   109,   108,    16,   118,    17,   125,   110,    18,   106,
     188,   189,   190,   191,   192,   193,   127,   126,   129,   136,
     133,   194,   195,   196,   197,   248,   183,   145,   148,   163,
     160,   170,   172,   174,   132,   135,   137,   138,   184,   173,
     257,   187,   202,   205,   203,   206,   212,   213,   217,   215,
     222,   225,   224,     4,   235,   234,   268,   238,   236,   244,
     243,   245,   257,   254,   250,   251,   272,   260,   253,   239,
     266,    78,   211,   262,   117,   269,   177,   175,   242,   112
};

static const yytype_int16 yycheck[] =
{
       4,     4,    95,    69,   160,   150,    11,     3,    40,    34,
      25,   200,   201,    25,   150,    23,   130,    40,    71,    57,
      58,    59,    60,    61,    23,    12,    34,   141,   121,    34,
      42,    97,    98,    71,    34,    34,    71,    75,    25,    71,
      75,    38,   198,   199,    69,    70,   139,    72,    71,    24,
     143,    47,   145,    68,   243,    63,    52,   123,    57,    58,
      59,    60,    61,    63,    69,    70,   202,    72,    23,    25,
      69,    70,    71,    72,    25,    41,    75,   222,   234,    34,
     146,   174,   271,    47,     0,    41,   179,     6,    52,     8,
      94,    94,    96,    89,    90,    91,    92,    93,    73,    74,
      75,    76,    57,    58,    59,    60,    61,    40,    63,   105,
      23,    66,    40,    71,    69,    70,    71,    72,     7,     8,
      75,    34,    73,    74,    75,    76,    90,    91,    92,    93,
      29,    30,    31,    32,    33,    71,    75,    76,    71,    75,
      43,    44,    75,    71,    24,    25,     6,    75,     8,     9,
      71,    15,   148,    17,   150,    48,    69,    70,     3,    72,
      71,    74,     4,     5,    71,    24,    25,    71,    10,    11,
      64,    65,    24,    25,     8,    17,    18,    19,    20,    21,
      22,    24,    25,    71,    26,    27,    28,    24,    25,    37,
      23,    37,    41,    35,    36,    71,    71,    51,    45,   203,
      23,    71,    46,    45,    71,    47,    71,    46,    50,    49,
      51,    52,    53,    54,    55,    56,    42,    39,    71,    46,
      71,    62,    63,    64,    65,   221,   222,    24,    23,    38,
      51,    25,    23,    13,    72,    71,    71,    12,    25,    71,
     244,    66,    23,    71,    23,     6,    24,    71,    14,    23,
      23,    63,    24,    11,    71,    51,   260,    34,    69,    16,
      46,    67,   266,    71,    24,    24,   270,    16,    24,   211,
      25,    18,   170,   253,    94,   266,   142,   139,   215,    89
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     4,     5,    10,    11,    17,    18,    19,    20,    21,
      22,    26,    27,    28,    35,    36,    45,    47,    50,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    99,   103,   104,   106,   127,   134,
     135,   136,     6,     8,     9,     6,     8,    23,    34,    69,
      70,    72,    74,   102,   128,   129,    57,    58,    59,    60,
      61,    71,    75,   109,   110,   111,   113,   133,   139,   140,
      71,     7,     8,    38,    41,    71,    71,    48,    80,     0,
       3,   137,    71,    71,     8,    71,    71,   129,   129,    25,
      73,    74,    75,    76,    25,    41,    23,    37,    40,    71,
     140,    41,    71,    71,    45,    51,    49,    23,    46,    71,
      46,    24,   128,   129,   129,   129,   129,   110,    71,   121,
     122,   139,   113,   140,   140,    71,    39,    42,   124,    71,
     105,   102,    72,    71,    95,    71,    46,    71,    12,    25,
     114,   115,   116,    40,   139,    24,    40,   140,    23,   100,
      23,    63,    66,   102,   113,   123,   125,   126,   132,   133,
      51,    25,   124,    38,    29,    30,    31,    32,    33,    98,
      25,    94,    23,    71,    13,   121,   124,   114,   139,    40,
     139,   140,   101,   102,    25,   101,   106,    66,    51,    52,
      53,    54,    55,    56,    62,    63,    64,    65,   130,   131,
      43,    44,    23,    23,   123,    71,     6,    23,    34,    63,
      96,    95,    24,    71,   138,    23,   139,    14,   117,   139,
      24,    25,    23,    24,    24,    63,    64,    65,   123,   123,
     125,   125,   106,   113,    51,    71,    69,    97,    34,    94,
      24,    25,   138,    46,    16,    67,   107,   108,   102,   101,
      24,    24,   123,    24,    71,    24,   125,   113,   118,   119,
      16,    24,    96,    15,    17,   120,    25,   112,   113,   119,
      25,    68,   113,   125
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    78,    79,    80,    80,    80,    80,    80,    80,    80,
      80,    80,    80,    80,    80,    80,    80,    80,    80,    80,
      80,    80,    80,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    90,    90,    91,    92,    93,    94,    94,
      95,    95,    96,    96,    96,    97,    98,    98,    98,    98,
      98,    99,   100,   100,   101,   101,   102,   102,   102,   102,
     103,   104,   105,   105,   106,   107,   107,   108,   108,   109,
     109,   110,   110,   111,   111,   111,   112,   112,   113,   113,
     113,   113,   113,   113,   114,   115,   115,   116,   116,   117,
     117,   118,   118,   119,   120,   120,   120,   121,   121,   121,
     122,   122,   122,   123,   123,   123,   123,   123,   124,   124,
     124,   125,   125,   125,   125,   126,   126,   127,   128,   128,
     129,   129,   129,   129,   129,   129,   129,   130,   130,   130,
     130,   130,   130,   130,   130,   130,   130,   131,   131,   132,
     132,   133,   133,   133,   133,   133,   134,   135,   136,   137,
     137,   138,   138,   139,   140,   140
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     2,     2,     8,     9,     4,     5,     7,     0,     3,
       6,     3,     0,     2,     1,     1,     1,     1,     1,     1,
       1,     5,     3,     5,     1,     3,     1,     1,     1,     1,
       4,     5,     3,     5,     8,     1,     0,     3,     5,     1,
       3,     1,     1,     4,     6,     5,     1,     3,     1,     2,
       3,     3,     4,     5,     5,     0,     1,     1,     2,     0,
       3,     1,     3,     2,     0,     1,     1,     1,     2,     3,
       0,     1,     3,     1,     1,     3,     3,     4,     0,     5,
       2,     0,     1,     3,     3,     3,     3,     2,     1,     3,
       3,     3,     3,     3,     3,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     2,     1,     2,     1,     2,     1,
       2,     1,     1,     1,     1,     1,     7,     2,     4,     0,
       1,     1,     3,     1,     1,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (&yylloc, sql_string, sql_result, scanner, YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF

/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)


/* YYLOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

# ifndef YYLOCATION_PRINT

#  if defined YY_LOCATION_PRINT

   /* Temporary convenience wrapper in case some people defined the
      undocumented and private YY_LOCATION_PRINT macros.  */
#   define YYLOCATION_PRINT(File, Loc)  YY_LOCATION_PRINT(File, *(Loc))

#  elif defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static int
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  int res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
}

#   define YYLOCATION_PRINT  yy_location_print_

    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT(File, Loc)  YYLOCATION_PRINT(File, &(Loc))

#  else

#   define YYLOCATION_PRINT(File, Loc) ((void) 0)
    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT  YYLOCATION_PRINT

#  endif
# endif /* !defined YYLOCATION_PRINT */


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value, Location, sql_string, sql_result, scanner); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  YY_USE (yylocationp);
  YY_USE (sql_string);
  YY_USE (sql_result);
  YY_USE (scanner);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  YYLOCATION_PRINT (yyo, yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yykind, yyvaluep, yylocationp, sql_string, sql_result, scanner);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp,
                 int yyrule, const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)],
                       &(yylsp[(yyi + 1) - (yynrhs)]), sql_string, sql_result, scanner);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule, sql_string, sql_result, scanner); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


/* Context of a parse error.  */
typedef struct
{
  yy_state_t *yyssp;
  yysymbol_kind_t yytoken;
  YYLTYPE *yylloc;
} yypcontext_t;

/* Put in YYARG at most YYARGN of the expected tokens given the
   current YYCTX, and return the number of tokens stored in YYARG.  If
   YYARG is null, return the number of expected tokens (guaranteed to
   be less than YYNTOKENS).  Return YYENOMEM on memory exhaustion.
   Return 0 if there are more than YYARGN expected tokens, yet fill
   YYARG up to YYARGN. */
static int
yypcontext_expected_tokens (const yypcontext_t *yyctx,
                            yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  int yyn = yypact[+*yyctx->yyssp];
  if (!yypact_value_is_default (yyn))
    {
      /* Start YYX at -YYN if negative to avoid negative indexes in
         YYCHECK.  In other words, skip the first -YYN actions for
         this state because they are default actions.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;
      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yyx;
      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
        if (yycheck[yyx + yyn] == yyx && yyx != YYSYMBOL_YYerror
            && !yytable_value_is_error (yytable[yyx + yyn]))
          {
            if (!yyarg)
              ++yycount;
            else if (yycount == yyargn)
              return 0;
            else
              yyarg[yycount++] = YY_CAST (yysymbol_kind_t, yyx);
          }
    }
  if (yyarg && yycount == 0 && 0 < yyargn)
    yyarg[0] = YYSYMBOL_YYEMPTY;
  return yycount;
}




#ifndef yystrlen
# if defined __GLIBC__ && defined _STRING_H
#  define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
# else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
# endif
#endif

#ifndef yystpcpy
# if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#  define yystpcpy stpcpy
# else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
# endif
#endif

#ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
      char const *yyp = yystr;
      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
#endif


static int
yy_syntax_error_arguments (const yypcontext_t *yyctx,
                           yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yyctx->yytoken != YYSYMBOL_YYEMPTY)
    {
      int yyn;
      if (yyarg)
        yyarg[yycount] = yyctx->yytoken;
      ++yycount;
      yyn = yypcontext_expected_tokens (yyctx,
                                        yyarg ? yyarg + 1 : yyarg, yyargn - 1);
      if (yyn == YYENOMEM)
        return YYENOMEM;
      else
        yycount += yyn;
    }
  return yycount;
}

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return -1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return YYENOMEM if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                const yypcontext_t *yyctx)
{
  enum { YYARGS_MAX = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  yysymbol_kind_t yyarg[YYARGS_MAX];
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* Actual size of YYARG. */
  int yycount = yy_syntax_error_arguments (yyctx, yyarg, YYARGS_MAX);
  if (yycount == YYENOMEM)
    return YYENOMEM;

  switch (yycount)
    {
#define YYCASE_(N, S)                       \
      case N:                               \
        yyformat = S;                       \
        break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
    }

  /* Compute error message size.  Don't count the "%s"s, but reserve
     room for the terminator.  */
  yysize = yystrlen (yyformat) - 2 * yycount + 1;
  {
    int yyi;
    for (yyi = 0; yyi < yycount; ++yyi)
      {
        YYPTRDIFF_T yysize1
          = yysize + yytnamerr (YY_NULLPTR, yytname[yyarg[yyi]]);
        if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
          yysize = yysize1;
        else
          return YYENOMEM;
      }
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return -1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yytname[yyarg[yyi++]]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, YYLTYPE *yylocationp, const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
{
  YY_USE (yyvaluep);
  YY_USE (yylocationp);
  YY_USE (sql_string);
  YY_USE (sql_result);
  YY_USE (scanner);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}






/*----------.
| yyparse.  |
`----------*/

int
yyparse (const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
{
/* Lookahead token kind.  */
int yychar;


/* The semantic value of the lookahead symbol.  */
/* Default value used for initialization, for pacifying older GCCs
   or non-GCC compilers.  */
YY_INITIAL_VALUE (static YYSTYPE yyval_default;)
YYSTYPE yylval YY_INITIAL_VALUE (= yyval_default);

/* Location data for the lookahead symbol.  */
static YYLTYPE yyloc_default
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
YYLTYPE yylloc = yyloc_default;

    /* Number of syntax errors so far.  */
    int yynerrs = 0;

    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

    /* The location stack: array, bottom, top.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls = yylsa;
    YYLTYPE *yylsp = yyls;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

  /* The locations where the error started and ended.  */
  YYLTYPE yyerror_range[3];

  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  yylsp[0] = yylloc;
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yyls1, yysize * YYSIZEOF (*yylsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
        yyls = yyls1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex (&yylval, &yylloc, scanner);
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      yyerror_range[1] = yylloc;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
  *++yylsp = yylloc;

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  yyerror_range[1] = yyloc;
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* commands: command_wrapper opt_semicolon  */
#line 241 "yacc_sql.y"
  {
    std::unique_ptr<ParsedSqlNode> sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[-1].sql_node));
    sql_result->add_sql_node(std::move(sql_node));
  }
#line 1856 "yacc_sql.cpp"
    break;

  case 24: /* exit_stmt: EXIT  */
#line 272 "yacc_sql.y"
         {
      (void)yynerrs;  // 这么写为了消除yynerrs未使用的告警。如果你有更好的方法欢迎提PR
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXIT);
    }
#line 1865 "yacc_sql.cpp"
    break;

  case 25: /* help_stmt: HELP  */
#line 278 "yacc_sql.y"
         {
      (yyval.sql_node) = new ParsedSqlNode(SCF_HELP);
    }
#line 1873 "yacc_sql.cpp"
    break;

  case 26: /* sync_stmt: SYNC  */
#line 283 "yacc_sql.y"
         {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SYNC);
    }
#line 1881 "yacc_sql.cpp"
    break;

  case 27: /* begin_stmt: TRX_BEGIN  */
#line 289 "yacc_sql.y"
               {
      (yyval.sql_node) = new ParsedSqlNode(SCF_BEGIN);
    }
#line 1889 "yacc_sql.cpp"
    break;

  case 28: /* commit_stmt: TRX_COMMIT  */
#line 295 "yacc_sql.y"
               {
      (yyval.sql_node) = new ParsedSqlNode(SCF_COMMIT);
    }
#line 1897 "yacc_sql.cpp"
    break;

  case 29: /* rollback_stmt: TRX_ROLLBACK  */
#line 301 "yacc_sql.y"
                  {
      (yyval.sql_node) = new ParsedSqlNode(SCF_ROLLBACK);
    }
#line 1905 "yacc_sql.cpp"
    break;

  case 30: /* drop_table_stmt: DROP TABLE ID  */
#line 307 "yacc_sql.y"
                  {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_TABLE);
      (yyval.sql_node)->drop_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 1915 "yacc_sql.cpp"
    break;

  case 31: /* show_tables_stmt: SHOW TABLES  */
#line 314 "yacc_sql.y"
                {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SHOW_TABLES);
    }
#line 1923 "yacc_sql.cpp"
    break;

  case 32: /* desc_table_stmt: DESC ID  */
#line 320 "yacc_sql.y"
             {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DESC_TABLE);
      (yyval.sql_node)->desc_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 1933 "yacc_sql.cpp"
    break;

  case 33: /* create_index_stmt: CREATE INDEX ID ON ID LBRACE id_list RBRACE  */
#line 329 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CREATE_INDEX);
      CreateIndexSqlNode &create_index = (yyval.sql_node)->create_index;
      create_index.index_name = (yyvsp[-5].string);
      create_index.relation_name = (yyvsp[-3].string);
      if ((yyvsp[-1].id_list) != nullptr) {
        create_index.attribute_names.swap(*(yyvsp[-1].id_list)); 
        delete (yyvsp[-1].id_list); 
      }
      free((yyvsp[-5].string));
      free((yyvsp[-3].string));
    }
#line 1950 "yacc_sql.cpp"
    break;

  case 34: /* create_index_stmt: CREATE UNIQUE INDEX ID ON ID LBRACE id_list RBRACE  */
#line 342 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CREATE_INDEX);
      CreateIndexSqlNode &create_index = (yyval.sql_node)->create_index;
      create_index.unique = true;
      create_index.index_name = (yyvsp[-5].string);
      create_index.relation_name = (yyvsp[-3].string);
      if ((yyvsp[-1].id_list) != nullptr) {
        create_index.attribute_names.swap(*(yyvsp[-1].id_list)); 
        delete (yyvsp[-1].id_list); 
      }
      free((yyvsp[-5].string));
      free((yyvsp[-3].string));
    }
#line 1968 "yacc_sql.cpp"
    break;

  case 35: /* show_index_stmt: SHOW INDEX FROM ID  */
#line 359 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SHOW_INDEX);
      (yyval.sql_node)->show_index.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 1978 "yacc_sql.cpp"
    break;

  case 36: /* drop_index_stmt: DROP INDEX ID ON ID  */
#line 368 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_INDEX);
      (yyval.sql_node)->drop_index.index_name = (yyvsp[-2].string);
      (yyval.sql_node)->drop_index.relation_name = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 1990 "yacc_sql.cpp"
    break;

  case 37: /* create_table_stmt: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE  */
#line 378 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CREATE_TABLE);
      CreateTableSqlNode &create_table = (yyval.sql_node)->create_table;
      create_table.relation_name = (yyvsp[-4].string);
      free((yyvsp[-4].string));

      std::vector<AttrInfoSqlNode> *src_attrs = (yyvsp[-1].attr_infos);

      if (src_attrs != nullptr) {
        create_table.attr_infos.swap(*src_attrs);
      }
      create_table.attr_infos.emplace_back(*(yyvsp[-2].attr_info));
      std::reverse(create_table.attr_infos.begin(), create_table.attr_infos.end());
      delete (yyvsp[-2].attr_info);
    }
#line 2010 "yacc_sql.cpp"
    break;

  case 38: /* attr_def_list: %empty  */
#line 396 "yacc_sql.y"
    {
      (yyval.attr_infos) = nullptr;
    }
#line 2018 "yacc_sql.cpp"
    break;

  case 39: /* attr_def_list: COMMA attr_def attr_def_list  */
#line 400 "yacc_sql.y"
    {
      if ((yyvsp[0].attr_infos) != nullptr) {
        (yyval.attr_infos) = (yyvsp[0].attr_infos);
      } else {
        (yyval.attr_infos) = new std::vector<AttrInfoSqlNode>;
      }
      (yyval.attr_infos)->emplace_back(*(yyvsp[-1].attr_info));
      delete (yyvsp[-1].attr_info);
    }
#line 2032 "yacc_sql.cpp"
    break;

  case 40: /* attr_def: ID type LBRACE number RBRACE nullable  */
#line 413 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-4].number);
      (yyval.attr_info)->name = (yyvsp[-5].string);
      (yyval.attr_info)->length = (yyvsp[-2].number);
      (yyval.attr_info)->nullable = (yyvsp[0].nullable);
      free((yyvsp[-5].string));
    }
#line 2045 "yacc_sql.cpp"
    break;

  case 41: /* attr_def: ID type nullable  */
#line 422 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-1].number);
      (yyval.attr_info)->name = (yyvsp[-2].string);
      if((yyval.attr_info)->type==TEXTS){
        (yyval.attr_info)->length = 65535;
      }else{
        (yyval.attr_info)->length = 4;
      }
      (yyval.attr_info)->nullable = (yyvsp[0].nullable);
      free((yyvsp[-2].string));
    }
#line 2062 "yacc_sql.cpp"
    break;

  case 42: /* nullable: %empty  */
#line 438 "yacc_sql.y"
    {
      (yyval.nullable) = true; // 字段默认是可以为null的
    }
#line 2070 "yacc_sql.cpp"
    break;

  case 43: /* nullable: NOT NULL_T  */
#line 442 "yacc_sql.y"
    {
      (yyval.nullable) = false;
    }
#line 2078 "yacc_sql.cpp"
    break;

  case 44: /* nullable: NULL_T  */
#line 446 "yacc_sql.y"
    {
      (yyval.nullable) = true;
    }
#line 2086 "yacc_sql.cpp"
    break;

  case 45: /* number: NUMBER  */
#line 452 "yacc_sql.y"
           {(yyval.number) = (yyvsp[0].number);}
#line 2092 "yacc_sql.cpp"
    break;

  case 46: /* type: INT_T  */
#line 455 "yacc_sql.y"
               { (yyval.number)=INTS; }
#line 2098 "yacc_sql.cpp"
    break;

  case 47: /* type: STRING_T  */
#line 456 "yacc_sql.y"
               { (yyval.number)=CHARS; }
#line 2104 "yacc_sql.cpp"
    break;

  case 48: /* type: TEXT_T  */
#line 457 "yacc_sql.y"
               { (yyval.number)=TEXTS; }
#line 2110 "yacc_sql.cpp"
    break;

  case 49: /* type: FLOAT_T  */
#line 458 "yacc_sql.y"
               { (yyval.number)=FLOATS; }
#line 2116 "yacc_sql.cpp"
    break;

  case 50: /* type: DATE_T  */
#line 459 "yacc_sql.y"
               { (yyval.number)=DATES;}
#line 2122 "yacc_sql.cpp"
    break;

  case 51: /* insert_stmt: INSERT INTO ID VALUES value_list_list  */
#line 463 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_INSERT);
      (yyval.sql_node)->insertion.relation_name = (yyvsp[-2].string);
      (yyval.sql_node)->insertion.values_list = *(yyvsp[0].value_list_list);
      free((yyvsp[-2].string));
    }
#line 2133 "yacc_sql.cpp"
    break;

  case 52: /* value_list_list: LBRACE value_list RBRACE  */
#line 473 "yacc_sql.y"
    {
      (yyval.value_list_list) = new std::vector<std::vector<Value>>{*(yyvsp[-1].value_list)};
      delete (yyvsp[-1].value_list);
    }
#line 2142 "yacc_sql.cpp"
    break;

  case 53: /* value_list_list: value_list_list COMMA LBRACE value_list RBRACE  */
#line 478 "yacc_sql.y"
    {
      (yyval.value_list_list)->emplace_back(*(yyvsp[-1].value_list));
      delete (yyvsp[-1].value_list);
    }
#line 2151 "yacc_sql.cpp"
    break;

  case 54: /* value_list: value  */
#line 487 "yacc_sql.y"
  {
    (yyval.value_list) = new std::vector<Value>{*(yyvsp[0].value)};
    delete (yyvsp[0].value); /* relese the pointer*/
  }
#line 2160 "yacc_sql.cpp"
    break;

  case 55: /* value_list: value_list COMMA value  */
#line 492 "yacc_sql.y"
  {
    (yyval.value_list)->emplace_back(*(yyvsp[0].value));
    delete (yyvsp[0].value);
  }
#line 2169 "yacc_sql.cpp"
    break;

  case 56: /* value: NUMBER  */
#line 500 "yacc_sql.y"
           {
      (yyval.value) = new Value((int)(yyvsp[0].number));
      (yyloc) = (yylsp[0]);
    }
#line 2178 "yacc_sql.cpp"
    break;

  case 57: /* value: FLOAT  */
#line 504 "yacc_sql.y"
           {
      (yyval.value) = new Value((float)(yyvsp[0].floats));
      (yyloc) = (yylsp[0]);
    }
#line 2187 "yacc_sql.cpp"
    break;

  case 58: /* value: SSS  */
#line 508 "yacc_sql.y"
         {
      char *tmp = common::substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
      (yyval.value) = new Value(tmp);
      free(tmp);
    }
#line 2197 "yacc_sql.cpp"
    break;

  case 59: /* value: NULL_T  */
#line 513 "yacc_sql.y"
             {
      (yyval.value) = new Value();
    }
#line 2205 "yacc_sql.cpp"
    break;

  case 60: /* delete_stmt: DELETE FROM ID where  */
#line 520 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DELETE);
      (yyval.sql_node)->deletion.relation_name = (yyvsp[-1].string);
      if ((yyvsp[0].condition_list) != nullptr) {
        (yyval.sql_node)->deletion.conditions.swap(*(yyvsp[0].condition_list));
        delete (yyvsp[0].condition_list);
      }
      free((yyvsp[-1].string));
    }
#line 2219 "yacc_sql.cpp"
    break;

  case 61: /* update_stmt: UPDATE ID SET update_list where  */
#line 532 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_UPDATE);
      (yyval.sql_node)->update.relation_name = (yyvsp[-3].string);
      (yyval.sql_node)->update.attr_list = (yyvsp[-1].update_list)->first;
      (yyval.sql_node)->update.expr_list = (yyvsp[-1].update_list)->second;

      if ((yyvsp[0].condition_list) != nullptr) {
        (yyval.sql_node)->update.conditions.swap(*(yyvsp[0].condition_list));
        delete (yyvsp[0].condition_list);
      }
      free((yyvsp[-3].string));
      delete (yyvsp[-1].update_list);
    }
#line 2237 "yacc_sql.cpp"
    break;

  case 62: /* update_list: ID EQ parse_expr  */
#line 549 "yacc_sql.y"
    {
      (yyval.update_list) = new std::pair<std::vector<std::string>, std::vector<ParseExpr *>>;
      (yyval.update_list)->first.emplace_back((yyvsp[-2].string));
      (yyval.update_list)->second.emplace_back((yyvsp[0].parse_expr));

      delete (yyvsp[-2].string);
    }
#line 2249 "yacc_sql.cpp"
    break;

  case 63: /* update_list: update_list COMMA ID EQ parse_expr  */
#line 557 "yacc_sql.y"
    {
      (yyval.update_list) = (yyvsp[-4].update_list);
      (yyval.update_list)->first.emplace_back((yyvsp[-2].string));
      (yyval.update_list)->second.emplace_back((yyvsp[0].parse_expr));
      delete (yyvsp[-2].string);
    }
#line 2260 "yacc_sql.cpp"
    break;

  case 64: /* select_stmt: SELECT rel_attr_aggre_list FROM rel_list select_join_list where select_order_list groupby_having_node_opt  */
#line 567 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SELECT);
      if ((yyvsp[-6].rel_attr_aggre_list) != nullptr) {
        (yyval.sql_node)->selection.attributes.swap(*(yyvsp[-6].rel_attr_aggre_list));
        delete (yyvsp[-6].rel_attr_aggre_list);
      }
      if ((yyvsp[-4].relation_list) != nullptr) {
        (yyval.sql_node)->selection.relations.swap(*(yyvsp[-4].relation_list));
        delete (yyvsp[-4].relation_list);
      }
      if ((yyvsp[-3].join_list) != nullptr) {
        (yyval.sql_node)->selection.joinctions.swap(*(yyvsp[-3].join_list));
        delete (yyvsp[-3].join_list);
      }
      if ((yyvsp[-2].condition_list) != nullptr) {
        (yyval.sql_node)->selection.conditions.swap(*(yyvsp[-2].condition_list));
        delete (yyvsp[-2].condition_list);
      }
      if ((yyvsp[-1].order_list) != nullptr) {
        (yyval.sql_node)->selection.orders.swap(*(yyvsp[-1].order_list));
        delete (yyvsp[-1].order_list);
      }
      if ((yyvsp[0].groupby_having_node) != nullptr) { // GROUPBY
        (yyval.sql_node)->selection.groupbys.swap((*(yyvsp[0].groupby_having_node)).rel_attrs);
        if ((*(yyvsp[0].groupby_having_node)).havings.size()) {
          (yyval.sql_node)->selection.havings.swap((*(yyvsp[0].groupby_having_node)).havings);
        }
        delete (yyvsp[0].groupby_having_node); 
      }
    }
#line 2295 "yacc_sql.cpp"
    break;

  case 65: /* groupby_having_node_opt: groupby_having_node  */
#line 601 "yacc_sql.y"
    {
      (yyval.groupby_having_node) = (yyvsp[0].groupby_having_node); 
    }
#line 2303 "yacc_sql.cpp"
    break;

  case 66: /* groupby_having_node_opt: %empty  */
#line 605 "yacc_sql.y"
    {
      (yyval.groupby_having_node) = nullptr; 
    }
#line 2311 "yacc_sql.cpp"
    break;

  case 67: /* groupby_having_node: GROUP BY rel_attr_list  */
#line 612 "yacc_sql.y"
    {
      (yyval.groupby_having_node) = new GroupByHavingSqlNode{*(yyvsp[0].rel_attr_list)}; 
      delete (yyvsp[0].rel_attr_list); 
    }
#line 2320 "yacc_sql.cpp"
    break;

  case 68: /* groupby_having_node: GROUP BY rel_attr_list HAVING condition_list  */
#line 617 "yacc_sql.y"
    {
      (yyval.groupby_having_node) = new GroupByHavingSqlNode{*(yyvsp[-2].rel_attr_list), *(yyvsp[0].condition_list)}; 
      delete (yyvsp[-2].rel_attr_list); 
      delete (yyvsp[0].condition_list); 
    }
#line 2330 "yacc_sql.cpp"
    break;

  case 69: /* rel_attr_aggre_list: rel_attr_aggre_node  */
#line 626 "yacc_sql.y"
    {
      (yyval.rel_attr_aggre_list) = new std::vector<RelAttrSqlNode>{*(yyvsp[0].rel_attr_aggre_node)}; 
      delete (yyvsp[0].rel_attr_aggre_node); 
    }
#line 2339 "yacc_sql.cpp"
    break;

  case 70: /* rel_attr_aggre_list: rel_attr_aggre_list COMMA rel_attr_aggre_node  */
#line 631 "yacc_sql.y"
    {
      (yyval.rel_attr_aggre_list)->emplace_back(*(yyvsp[0].rel_attr_aggre_node)); 
      delete (yyvsp[0].rel_attr_aggre_node); 
    }
#line 2348 "yacc_sql.cpp"
    break;

  case 71: /* rel_attr_aggre_node: aggre_node  */
#line 639 "yacc_sql.y"
    {
      (yyval.rel_attr_aggre_node) = new RelAttrSqlNode(*(yyvsp[0].rel_attr));
      delete (yyvsp[0].rel_attr); 
    }
#line 2357 "yacc_sql.cpp"
    break;

  case 72: /* rel_attr_aggre_node: rel_attr  */
#line 644 "yacc_sql.y"
    {
      (yyval.rel_attr_aggre_node) = new RelAttrSqlNode(*(yyvsp[0].rel_attr)); 
      delete (yyvsp[0].rel_attr); 
    }
#line 2366 "yacc_sql.cpp"
    break;

  case 73: /* aggre_node: aggre_type LBRACE rel_attr RBRACE  */
#line 653 "yacc_sql.y"
    {
      (yyval.rel_attr) = (yyvsp[-1].rel_attr);
      (yyval.rel_attr)->aggre_type = (yyvsp[-3].aggre_type);
    }
#line 2375 "yacc_sql.cpp"
    break;

  case 74: /* aggre_node: aggre_type LBRACE rel_attr RBRACE AS rel_name  */
#line 658 "yacc_sql.y"
    {
      (yyval.rel_attr) = (yyvsp[-3].rel_attr);
      (yyval.rel_attr)->aggre_type = (yyvsp[-5].aggre_type);
      if((yyvsp[0].string) != nullptr){
        (yyval.rel_attr)->field_alias = (yyvsp[0].string);
        free((yyvsp[0].string));
      }
    }
#line 2388 "yacc_sql.cpp"
    break;

  case 75: /* aggre_node: aggre_type LBRACE rel_attr RBRACE rel_name  */
#line 667 "yacc_sql.y"
    {
      (yyval.rel_attr) = (yyvsp[-2].rel_attr);
      (yyval.rel_attr)->aggre_type = (yyvsp[-4].aggre_type);
      if((yyvsp[0].string) != nullptr){
        (yyval.rel_attr)->field_alias = (yyvsp[0].string);
        free((yyvsp[0].string));
      }
    }
#line 2401 "yacc_sql.cpp"
    break;

  case 76: /* rel_attr_list: rel_attr  */
#line 680 "yacc_sql.y"
    {
      (yyval.rel_attr_list) = new std::vector<RelAttrSqlNode>{*(yyvsp[0].rel_attr)}; 
      delete (yyvsp[0].rel_attr); 
    }
#line 2410 "yacc_sql.cpp"
    break;

  case 77: /* rel_attr_list: rel_attr_list COMMA rel_attr  */
#line 685 "yacc_sql.y"
    {
      (yyval.rel_attr_list)->emplace_back(*(yyvsp[0].rel_attr)); 
      delete (yyvsp[0].rel_attr); 
    }
#line 2419 "yacc_sql.cpp"
    break;

  case 78: /* rel_attr: attr_name  */
#line 693 "yacc_sql.y"
    {
      (yyval.rel_attr) = new RelAttrSqlNode{"","", (yyvsp[0].string),""};
      free((yyvsp[0].string));
    }
#line 2428 "yacc_sql.cpp"
    break;

  case 79: /* rel_attr: attr_name attr_name  */
#line 698 "yacc_sql.y"
    {
      (yyval.rel_attr) = new RelAttrSqlNode{"","", (yyvsp[-1].string),(yyvsp[0].string)};
      free((yyvsp[-1].string));
      free((yyvsp[0].string));
    }
#line 2438 "yacc_sql.cpp"
    break;

  case 80: /* rel_attr: attr_name AS attr_name  */
#line 704 "yacc_sql.y"
    {
      (yyval.rel_attr) = new RelAttrSqlNode{"","", (yyvsp[-2].string),(yyvsp[0].string)};
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 2448 "yacc_sql.cpp"
    break;

  case 81: /* rel_attr: rel_name DOT attr_name  */
#line 710 "yacc_sql.y"
    {
      (yyval.rel_attr) = new RelAttrSqlNode{(yyvsp[-2].string),(yyvsp[-2].string),(yyvsp[0].string),""};
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 2458 "yacc_sql.cpp"
    break;

  case 82: /* rel_attr: rel_name DOT attr_name attr_name  */
#line 716 "yacc_sql.y"
    {
      (yyval.rel_attr) = new RelAttrSqlNode{(yyvsp[-3].string),(yyvsp[-3].string),(yyvsp[-1].string),(yyvsp[0].string)};
      free((yyvsp[-3].string));
      free((yyvsp[-1].string));
      free((yyvsp[0].string));
    }
#line 2469 "yacc_sql.cpp"
    break;

  case 83: /* rel_attr: rel_name DOT attr_name AS attr_name  */
#line 723 "yacc_sql.y"
    {
      (yyval.rel_attr) = new RelAttrSqlNode{(yyvsp[-4].string),(yyvsp[-4].string),(yyvsp[-2].string),(yyvsp[0].string)};
      free((yyvsp[-4].string));
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 2480 "yacc_sql.cpp"
    break;

  case 84: /* join_node: INNER JOIN rel_name ON condition_list  */
#line 738 "yacc_sql.y"
    {
      (yyval.join_node) = new JoinSqlNode{(yyvsp[-2].string),*(yyvsp[0].condition_list)};
      delete (yyvsp[-2].string);
      delete (yyvsp[0].condition_list);
    }
#line 2490 "yacc_sql.cpp"
    break;

  case 85: /* select_join_list: %empty  */
#line 747 "yacc_sql.y"
    {
      (yyval.join_list) = nullptr; 
    }
#line 2498 "yacc_sql.cpp"
    break;

  case 86: /* select_join_list: join_list  */
#line 751 "yacc_sql.y"
    {
      (yyval.join_list) = (yyvsp[0].join_list); 
    }
#line 2506 "yacc_sql.cpp"
    break;

  case 87: /* join_list: join_node  */
#line 761 "yacc_sql.y"
    {
      (yyval.join_list) = new std::vector<JoinSqlNode>{*(yyvsp[0].join_node)};
      delete (yyvsp[0].join_node);   
    }
#line 2515 "yacc_sql.cpp"
    break;

  case 88: /* join_list: join_list join_node  */
#line 766 "yacc_sql.y"
    {
      (yyval.join_list)->emplace_back(*(yyvsp[0].join_node));
      delete (yyvsp[0].join_node);
    }
#line 2524 "yacc_sql.cpp"
    break;

  case 89: /* select_order_list: %empty  */
#line 774 "yacc_sql.y"
    {
      (yyval.order_list) = nullptr; // 没有order
    }
#line 2532 "yacc_sql.cpp"
    break;

  case 90: /* select_order_list: ORDER BY order_list  */
#line 778 "yacc_sql.y"
    {
      (yyval.order_list) = (yyvsp[0].order_list);
    }
#line 2540 "yacc_sql.cpp"
    break;

  case 91: /* order_list: order_node  */
#line 789 "yacc_sql.y"
    {
      (yyval.order_list) = new std::vector<OrderSqlNode>{*(yyvsp[0].order_node)};
      delete (yyvsp[0].order_node);
    }
#line 2549 "yacc_sql.cpp"
    break;

  case 92: /* order_list: order_list COMMA order_node  */
#line 794 "yacc_sql.y"
    {
      (yyval.order_list)->emplace_back(*(yyvsp[0].order_node));
      delete (yyvsp[0].order_node);
    }
#line 2558 "yacc_sql.cpp"
    break;

  case 93: /* order_node: rel_attr order_type  */
#line 806 "yacc_sql.y"
    {
      (yyval.order_node) = new OrderSqlNode{*(yyvsp[-1].rel_attr),(yyvsp[0].order_type)};
      delete (yyvsp[-1].rel_attr);
    }
#line 2567 "yacc_sql.cpp"
    break;

  case 94: /* order_type: %empty  */
#line 813 "yacc_sql.y"
           { (yyval.order_type) = ORDER_ASC; }
#line 2573 "yacc_sql.cpp"
    break;

  case 95: /* order_type: ASC  */
#line 814 "yacc_sql.y"
           { (yyval.order_type) = ORDER_ASC; }
#line 2579 "yacc_sql.cpp"
    break;

  case 96: /* order_type: DESC  */
#line 815 "yacc_sql.y"
           { (yyval.order_type) = ORDER_DESC; }
#line 2585 "yacc_sql.cpp"
    break;

  case 97: /* rel_node: rel_name  */
#line 820 "yacc_sql.y"
    {
      (yyval.rel_node) = new AttrSqlNode{(yyvsp[0].string),""};
      free((yyvsp[0].string));
    }
#line 2594 "yacc_sql.cpp"
    break;

  case 98: /* rel_node: rel_name rel_name  */
#line 825 "yacc_sql.y"
    {
      (yyval.rel_node) = new AttrSqlNode{(yyvsp[-1].string),(yyvsp[0].string)};
      free((yyvsp[-1].string));
      free((yyvsp[0].string));
    }
#line 2604 "yacc_sql.cpp"
    break;

  case 99: /* rel_node: rel_name AS rel_name  */
#line 831 "yacc_sql.y"
    {
      (yyval.rel_node) = new AttrSqlNode{(yyvsp[-2].string),(yyvsp[0].string)};
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 2614 "yacc_sql.cpp"
    break;

  case 100: /* rel_list: %empty  */
#line 844 "yacc_sql.y"
    {
      (yyval.relation_list) = nullptr;
    }
#line 2622 "yacc_sql.cpp"
    break;

  case 101: /* rel_list: rel_node  */
#line 848 "yacc_sql.y"
    {
      (yyval.relation_list) = new std::vector<AttrSqlNode>{*(yyvsp[0].rel_node)};
      delete (yyvsp[0].rel_node); 
    }
#line 2631 "yacc_sql.cpp"
    break;

  case 102: /* rel_list: rel_list COMMA rel_node  */
#line 853 "yacc_sql.y"
    {
      (yyval.relation_list)->emplace_back(*(yyvsp[0].rel_node)); 
      delete (yyvsp[0].rel_node);
    }
#line 2640 "yacc_sql.cpp"
    break;

  case 103: /* parse_expr: value  */
#line 861 "yacc_sql.y"
    {
      (yyval.parse_expr) = new ParseValueExpr(*(yyvsp[0].value));
      delete (yyvsp[0].value);
    }
#line 2649 "yacc_sql.cpp"
    break;

  case 104: /* parse_expr: rel_attr  */
#line 866 "yacc_sql.y"
    {
      std::string &table_name = (yyvsp[0].rel_attr)->relation_name;
      std::string &field_name = (yyvsp[0].rel_attr)->attribute_name;
      (yyval.parse_expr) = new ParseFieldExpr(table_name,field_name);
      delete (yyvsp[0].rel_attr);
    }
#line 2660 "yacc_sql.cpp"
    break;

  case 105: /* parse_expr: LBRACE select_stmt RBRACE  */
#line 873 "yacc_sql.y"
    {
      (yyval.parse_expr) = new ParseSubQueryExpr((yyvsp[-1].sql_node)->selection);
    }
#line 2668 "yacc_sql.cpp"
    break;

  case 106: /* parse_expr: LBRACE value_list RBRACE  */
#line 877 "yacc_sql.y"
    {
      (yyval.parse_expr) = new ParseValueListExpr(*(yyvsp[-1].value_list));
      delete (yyvsp[-1].value_list);
    }
#line 2677 "yacc_sql.cpp"
    break;

  case 107: /* parse_expr: aggre_type LBRACE rel_attr RBRACE  */
#line 882 "yacc_sql.y"
    {
      std::string &table_name = (yyvsp[-1].rel_attr)->relation_name;
      std::string &field_name = (yyvsp[-1].rel_attr)->attribute_name;
      (yyval.parse_expr) = new ParseAggreExpr(table_name, field_name, (yyvsp[-3].aggre_type)); 
      delete (yyvsp[-1].rel_attr);
    }
#line 2688 "yacc_sql.cpp"
    break;

  case 108: /* where: %empty  */
#line 892 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 2696 "yacc_sql.cpp"
    break;

  case 109: /* where: WHERE exists_op LBRACE select_stmt RBRACE  */
#line 896 "yacc_sql.y"
    {
      (yyval.condition_list) = new std::vector<ConditionSqlNode>;
      //TODO: 这里糊了一下，其实左边是没有表达式的，但是为了方便，这里就先这样写了
      ParseExpr * left = new ParseValueExpr();
      ParseExpr *  right = new ParseSubQueryExpr((yyvsp[-1].sql_node)->selection);
      (yyval.condition_list)->emplace_back(ConditionSqlNode{left,(yyvsp[-3].comp),right});
    }
#line 2708 "yacc_sql.cpp"
    break;

  case 110: /* where: WHERE condition_list  */
#line 904 "yacc_sql.y"
    {
      (yyval.condition_list) = (yyvsp[0].condition_list);
    }
#line 2716 "yacc_sql.cpp"
    break;

  case 111: /* condition_list: %empty  */
#line 910 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 2724 "yacc_sql.cpp"
    break;

  case 112: /* condition_list: condition  */
#line 913 "yacc_sql.y"
                {
      (yyval.condition_list) = new std::vector<ConditionSqlNode>;
      (yyval.condition_list)->emplace_back(*(yyvsp[0].condition));
      delete (yyvsp[0].condition);
    }
#line 2734 "yacc_sql.cpp"
    break;

  case 113: /* condition_list: condition AND condition_list  */
#line 918 "yacc_sql.y"
                                   {
      (yyval.condition_list) = (yyvsp[0].condition_list);
      (yyvsp[-2].condition)->has_or = false;
      (yyval.condition_list)->emplace_back(*(yyvsp[-2].condition));
      delete (yyvsp[-2].condition);
    }
#line 2745 "yacc_sql.cpp"
    break;

  case 114: /* condition_list: condition OR condition_list  */
#line 924 "yacc_sql.y"
                                  {
      (yyval.condition_list) = (yyvsp[0].condition_list);
      (yyvsp[-2].condition)->has_or = true;
      (yyval.condition_list)->emplace_back(*(yyvsp[-2].condition));
      delete (yyvsp[-2].condition);
    }
#line 2756 "yacc_sql.cpp"
    break;

  case 115: /* condition: parse_expr comp_op parse_expr  */
#line 933 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left = (yyvsp[-2].parse_expr);

      (yyval.condition)->comp = (yyvsp[-1].comp);

      (yyval.condition)->right = (yyvsp[0].parse_expr);
    }
#line 2769 "yacc_sql.cpp"
    break;

  case 116: /* condition: parse_expr in_op parse_expr  */
#line 942 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left = (yyvsp[-2].parse_expr);

      (yyval.condition)->comp = (yyvsp[-1].comp);

      (yyval.condition)->right = (yyvsp[0].parse_expr);
    }
#line 2782 "yacc_sql.cpp"
    break;

  case 117: /* calc_stmt: CALC expression_list  */
#line 955 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CALC);
      std::reverse((yyvsp[0].expression_list)->begin(), (yyvsp[0].expression_list)->end());
      (yyval.sql_node)->calc.expressions.swap(*(yyvsp[0].expression_list));
      delete (yyvsp[0].expression_list);
    }
#line 2793 "yacc_sql.cpp"
    break;

  case 118: /* expression_list: expression  */
#line 965 "yacc_sql.y"
    {
      (yyval.expression_list) = new std::vector<Expression*>;
      (yyval.expression_list)->emplace_back((yyvsp[0].expression));
    }
#line 2802 "yacc_sql.cpp"
    break;

  case 119: /* expression_list: expression COMMA expression_list  */
#line 970 "yacc_sql.y"
    {
      if ((yyvsp[0].expression_list) != nullptr) {
        (yyval.expression_list) = (yyvsp[0].expression_list);
      } else {
        (yyval.expression_list) = new std::vector<Expression *>;
      }
      (yyval.expression_list)->emplace_back((yyvsp[-2].expression));
    }
#line 2815 "yacc_sql.cpp"
    break;

  case 120: /* expression: expression '+' expression  */
#line 980 "yacc_sql.y"
                              {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::ADD, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2823 "yacc_sql.cpp"
    break;

  case 121: /* expression: expression '-' expression  */
#line 983 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::SUB, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2831 "yacc_sql.cpp"
    break;

  case 122: /* expression: expression '*' expression  */
#line 986 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::MUL, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2839 "yacc_sql.cpp"
    break;

  case 123: /* expression: expression '/' expression  */
#line 989 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::DIV, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2847 "yacc_sql.cpp"
    break;

  case 124: /* expression: LBRACE expression RBRACE  */
#line 992 "yacc_sql.y"
                               {
      (yyval.expression) = (yyvsp[-1].expression);
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
    }
#line 2856 "yacc_sql.cpp"
    break;

  case 125: /* expression: '-' expression  */
#line 996 "yacc_sql.y"
                                  {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::NEGATIVE, (yyvsp[0].expression), nullptr, sql_string, &(yyloc));
    }
#line 2864 "yacc_sql.cpp"
    break;

  case 126: /* expression: value  */
#line 999 "yacc_sql.y"
            {
      (yyval.expression) = new ValueExpr(*(yyvsp[0].value));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[0].value);
    }
#line 2874 "yacc_sql.cpp"
    break;

  case 127: /* comp_op: EQ  */
#line 1007 "yacc_sql.y"
         { (yyval.comp) = EQUAL_TO; }
#line 2880 "yacc_sql.cpp"
    break;

  case 128: /* comp_op: LT  */
#line 1008 "yacc_sql.y"
         { (yyval.comp) = LESS_THAN; }
#line 2886 "yacc_sql.cpp"
    break;

  case 129: /* comp_op: GT  */
#line 1009 "yacc_sql.y"
         { (yyval.comp) = GREAT_THAN; }
#line 2892 "yacc_sql.cpp"
    break;

  case 130: /* comp_op: LE  */
#line 1010 "yacc_sql.y"
         { (yyval.comp) = LESS_EQUAL; }
#line 2898 "yacc_sql.cpp"
    break;

  case 131: /* comp_op: GE  */
#line 1011 "yacc_sql.y"
         { (yyval.comp) = GREAT_EQUAL; }
#line 2904 "yacc_sql.cpp"
    break;

  case 132: /* comp_op: NE  */
#line 1012 "yacc_sql.y"
         { (yyval.comp) = NOT_EQUAL; }
#line 2910 "yacc_sql.cpp"
    break;

  case 133: /* comp_op: LK  */
#line 1013 "yacc_sql.y"
         { (yyval.comp) = LIKE; }
#line 2916 "yacc_sql.cpp"
    break;

  case 134: /* comp_op: NOT LK  */
#line 1014 "yacc_sql.y"
             { (yyval.comp) = NOT_LIKE;}
#line 2922 "yacc_sql.cpp"
    break;

  case 135: /* comp_op: IS_  */
#line 1015 "yacc_sql.y"
          { (yyval.comp) = IS;}
#line 2928 "yacc_sql.cpp"
    break;

  case 136: /* comp_op: IS_ NOT  */
#line 1016 "yacc_sql.y"
              { (yyval.comp) = IS_NOT;}
#line 2934 "yacc_sql.cpp"
    break;

  case 137: /* in_op: IN_OP  */
#line 1020 "yacc_sql.y"
            {(yyval.comp) = IN;}
#line 2940 "yacc_sql.cpp"
    break;

  case 138: /* in_op: NOT IN_OP  */
#line 1021 "yacc_sql.y"
                {(yyval.comp) = NOT_IN;}
#line 2946 "yacc_sql.cpp"
    break;

  case 139: /* exists_op: EXISTS_OP  */
#line 1025 "yacc_sql.y"
                {(yyval.comp) = EXISTS;}
#line 2952 "yacc_sql.cpp"
    break;

  case 140: /* exists_op: NOT EXISTS_OP  */
#line 1026 "yacc_sql.y"
                    {(yyval.comp) = NOT_EXISTS;}
#line 2958 "yacc_sql.cpp"
    break;

  case 141: /* aggre_type: SUM  */
#line 1030 "yacc_sql.y"
            { (yyval.aggre_type) = AGGRE_SUM; }
#line 2964 "yacc_sql.cpp"
    break;

  case 142: /* aggre_type: AVG  */
#line 1031 "yacc_sql.y"
            { (yyval.aggre_type) = AGGRE_AVG; }
#line 2970 "yacc_sql.cpp"
    break;

  case 143: /* aggre_type: COUNT  */
#line 1032 "yacc_sql.y"
            { (yyval.aggre_type) = AGGRE_COUNT; }
#line 2976 "yacc_sql.cpp"
    break;

  case 144: /* aggre_type: MAX  */
#line 1033 "yacc_sql.y"
            { (yyval.aggre_type) = AGGRE_MAX; }
#line 2982 "yacc_sql.cpp"
    break;

  case 145: /* aggre_type: MIN  */
#line 1034 "yacc_sql.y"
            { (yyval.aggre_type) = AGGRE_MIN; }
#line 2988 "yacc_sql.cpp"
    break;

  case 146: /* load_data_stmt: LOAD DATA INFILE SSS INTO TABLE ID  */
#line 1039 "yacc_sql.y"
    {
      char *tmp_file_name = common::substr((yyvsp[-3].string), 1, strlen((yyvsp[-3].string)) - 2);
      
      (yyval.sql_node) = new ParsedSqlNode(SCF_LOAD_DATA);
      (yyval.sql_node)->load_data.relation_name = (yyvsp[0].string);
      (yyval.sql_node)->load_data.file_name = tmp_file_name;
      free((yyvsp[0].string));
      free(tmp_file_name);
    }
#line 3002 "yacc_sql.cpp"
    break;

  case 147: /* explain_stmt: EXPLAIN command_wrapper  */
#line 1052 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXPLAIN);
      (yyval.sql_node)->explain.sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[0].sql_node));
    }
#line 3011 "yacc_sql.cpp"
    break;

  case 148: /* set_variable_stmt: SET ID EQ value  */
#line 1060 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SET_VARIABLE);
      (yyval.sql_node)->set_variable.name  = (yyvsp[-2].string);
      (yyval.sql_node)->set_variable.value = *(yyvsp[0].value);
      free((yyvsp[-2].string));
      delete (yyvsp[0].value);
    }
#line 3023 "yacc_sql.cpp"
    break;

  case 151: /* id_list: ID  */
#line 1076 "yacc_sql.y"
    {
      (yyval.id_list) = new std::vector<std::string>{(yyvsp[0].string)}; 
      free((yyvsp[0].string)); 
    }
#line 3032 "yacc_sql.cpp"
    break;

  case 152: /* id_list: id_list COMMA ID  */
#line 1081 "yacc_sql.y"
    {
      (yyval.id_list)->emplace_back((yyvsp[0].string));
      free((yyvsp[0].string));
    }
#line 3041 "yacc_sql.cpp"
    break;

  case 153: /* rel_name: ID  */
#line 1089 "yacc_sql.y"
    {
       (yyval.string) = (yyvsp[0].string); 
    }
#line 3049 "yacc_sql.cpp"
    break;

  case 154: /* attr_name: ID  */
#line 1100 "yacc_sql.y"
    {
      (yyval.string) = (yyvsp[0].string);
    }
#line 3057 "yacc_sql.cpp"
    break;

  case 155: /* attr_name: '*'  */
#line 1104 "yacc_sql.y"
    {
      // 使用malloc为了和他的free配合
      char *str = (char *)malloc(strlen("*") + 1);  // 加1用于存储字符串结束符'\0'
      strcpy(str, "*");
      (yyval.string) = str;
    }
#line 3068 "yacc_sql.cpp"
    break;


#line 3072 "yacc_sql.cpp"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      {
        yypcontext_t yyctx
          = {yyssp, yytoken, &yylloc};
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == -1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *,
                             YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (yymsg)
              {
                yysyntax_error_status
                  = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
                yymsgp = yymsg;
              }
            else
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = YYENOMEM;
              }
          }
        yyerror (&yylloc, sql_string, sql_result, scanner, yymsgp);
        if (yysyntax_error_status == YYENOMEM)
          YYNOMEM;
      }
    }

  yyerror_range[1] = yylloc;
  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval, &yylloc, sql_string, sql_result, scanner);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, yylsp, sql_string, sql_result, scanner);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  ++yylsp;
  YYLLOC_DEFAULT (*yylsp, yyerror_range, 2);

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (&yylloc, sql_string, sql_result, scanner, YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc, sql_string, sql_result, scanner);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, yylsp, sql_string, sql_result, scanner);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
  return yyresult;
}

#line 1110 "yacc_sql.y"

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
