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
  YYSYMBOL_FLOAT_T = 31,                   /* FLOAT_T  */
  YYSYMBOL_DATE_T = 32,                    /* DATE_T  */
  YYSYMBOL_NULL_T = 33,                    /* NULL_T  */
  YYSYMBOL_HELP = 34,                      /* HELP  */
  YYSYMBOL_EXIT = 35,                      /* EXIT  */
  YYSYMBOL_DOT = 36,                       /* DOT  */
  YYSYMBOL_INTO = 37,                      /* INTO  */
  YYSYMBOL_VALUES = 38,                    /* VALUES  */
  YYSYMBOL_FROM = 39,                      /* FROM  */
  YYSYMBOL_WHERE = 40,                     /* WHERE  */
  YYSYMBOL_AND = 41,                       /* AND  */
  YYSYMBOL_SET = 42,                       /* SET  */
  YYSYMBOL_ON = 43,                        /* ON  */
  YYSYMBOL_LOAD = 44,                      /* LOAD  */
  YYSYMBOL_DATA = 45,                      /* DATA  */
  YYSYMBOL_INFILE = 46,                    /* INFILE  */
  YYSYMBOL_EXPLAIN = 47,                   /* EXPLAIN  */
  YYSYMBOL_EQ = 48,                        /* EQ  */
  YYSYMBOL_LT = 49,                        /* LT  */
  YYSYMBOL_GT = 50,                        /* GT  */
  YYSYMBOL_LE = 51,                        /* LE  */
  YYSYMBOL_GE = 52,                        /* GE  */
  YYSYMBOL_NE = 53,                        /* NE  */
  YYSYMBOL_SUM = 54,                       /* SUM  */
  YYSYMBOL_COUNT = 55,                     /* COUNT  */
  YYSYMBOL_AVG = 56,                       /* AVG  */
  YYSYMBOL_MIN = 57,                       /* MIN  */
  YYSYMBOL_MAX = 58,                       /* MAX  */
  YYSYMBOL_IS_ = 59,                       /* IS_  */
  YYSYMBOL_NOT = 60,                       /* NOT  */
  YYSYMBOL_LK = 61,                        /* LK  */
  YYSYMBOL_IN_OP = 62,                     /* IN_OP  */
  YYSYMBOL_EXIST_OP = 63,                  /* EXIST_OP  */
  YYSYMBOL_NUMBER = 64,                    /* NUMBER  */
  YYSYMBOL_FLOAT = 65,                     /* FLOAT  */
  YYSYMBOL_ID = 66,                        /* ID  */
  YYSYMBOL_AGGRE_ATTR = 67,                /* AGGRE_ATTR  */
  YYSYMBOL_SSS = 68,                       /* SSS  */
  YYSYMBOL_69_ = 69,                       /* '+'  */
  YYSYMBOL_70_ = 70,                       /* '-'  */
  YYSYMBOL_71_ = 71,                       /* '*'  */
  YYSYMBOL_72_ = 72,                       /* '/'  */
  YYSYMBOL_UMINUS = 73,                    /* UMINUS  */
  YYSYMBOL_YYACCEPT = 74,                  /* $accept  */
  YYSYMBOL_commands = 75,                  /* commands  */
  YYSYMBOL_command_wrapper = 76,           /* command_wrapper  */
  YYSYMBOL_exit_stmt = 77,                 /* exit_stmt  */
  YYSYMBOL_help_stmt = 78,                 /* help_stmt  */
  YYSYMBOL_sync_stmt = 79,                 /* sync_stmt  */
  YYSYMBOL_begin_stmt = 80,                /* begin_stmt  */
  YYSYMBOL_commit_stmt = 81,               /* commit_stmt  */
  YYSYMBOL_rollback_stmt = 82,             /* rollback_stmt  */
  YYSYMBOL_drop_table_stmt = 83,           /* drop_table_stmt  */
  YYSYMBOL_show_tables_stmt = 84,          /* show_tables_stmt  */
  YYSYMBOL_desc_table_stmt = 85,           /* desc_table_stmt  */
  YYSYMBOL_create_index_stmt = 86,         /* create_index_stmt  */
  YYSYMBOL_show_index_stmt = 87,           /* show_index_stmt  */
  YYSYMBOL_drop_index_stmt = 88,           /* drop_index_stmt  */
  YYSYMBOL_create_table_stmt = 89,         /* create_table_stmt  */
  YYSYMBOL_attr_def_list = 90,             /* attr_def_list  */
  YYSYMBOL_attr_def = 91,                  /* attr_def  */
  YYSYMBOL_nullable = 92,                  /* nullable  */
  YYSYMBOL_number = 93,                    /* number  */
  YYSYMBOL_type = 94,                      /* type  */
  YYSYMBOL_insert_stmt = 95,               /* insert_stmt  */
  YYSYMBOL_value_list_list = 96,           /* value_list_list  */
  YYSYMBOL_value_list = 97,                /* value_list  */
  YYSYMBOL_value = 98,                     /* value  */
  YYSYMBOL_delete_stmt = 99,               /* delete_stmt  */
  YYSYMBOL_update_stmt = 100,              /* update_stmt  */
  YYSYMBOL_update_list = 101,              /* update_list  */
  YYSYMBOL_select_stmt = 102,              /* select_stmt  */
  YYSYMBOL_selector = 103,                 /* selector  */
  YYSYMBOL_rel_attr_aggre = 104,           /* rel_attr_aggre  */
  YYSYMBOL_aggre_node = 105,               /* aggre_node  */
  YYSYMBOL_rel_attr = 106,                 /* rel_attr  */
  YYSYMBOL_attr_list = 107,                /* attr_list  */
  YYSYMBOL_join_node = 108,                /* join_node  */
  YYSYMBOL_select_join_list = 109,         /* select_join_list  */
  YYSYMBOL_join_list = 110,                /* join_list  */
  YYSYMBOL_select_order_list = 111,        /* select_order_list  */
  YYSYMBOL_order_list = 112,               /* order_list  */
  YYSYMBOL_order_node = 113,               /* order_node  */
  YYSYMBOL_order_type = 114,               /* order_type  */
  YYSYMBOL_rel_list = 115,                 /* rel_list  */
  YYSYMBOL_parse_expr = 116,               /* parse_expr  */
  YYSYMBOL_where = 117,                    /* where  */
  YYSYMBOL_condition_list = 118,           /* condition_list  */
  YYSYMBOL_condition = 119,                /* condition  */
  YYSYMBOL_calc_stmt = 120,                /* calc_stmt  */
  YYSYMBOL_expression_list = 121,          /* expression_list  */
  YYSYMBOL_expression = 122,               /* expression  */
  YYSYMBOL_comp_op = 123,                  /* comp_op  */
  YYSYMBOL_in_op = 124,                    /* in_op  */
  YYSYMBOL_exist_op = 125,                 /* exist_op  */
  YYSYMBOL_aggre_type = 126,               /* aggre_type  */
  YYSYMBOL_load_data_stmt = 127,           /* load_data_stmt  */
  YYSYMBOL_explain_stmt = 128,             /* explain_stmt  */
  YYSYMBOL_set_variable_stmt = 129,        /* set_variable_stmt  */
  YYSYMBOL_opt_semicolon = 130,            /* opt_semicolon  */
  YYSYMBOL_aggre_attr_list = 131,          /* aggre_attr_list  */
  YYSYMBOL_aggre_attr_name = 132,          /* aggre_attr_name  */
  YYSYMBOL_id_list = 133,                  /* id_list  */
  YYSYMBOL_rel_name = 134,                 /* rel_name  */
  YYSYMBOL_attr_name = 135                 /* attr_name  */
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
typedef yytype_uint8 yy_state_t;

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
#define YYLAST   247

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  74
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  62
/* YYNRULES -- Number of rules.  */
#define YYNRULES  145
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  250

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   324


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
       2,     2,    71,    69,     2,    70,     2,    72,     2,     2,
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
      65,    66,    67,    68,    73
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   230,   230,   238,   239,   240,   241,   242,   243,   244,
     245,   246,   247,   248,   249,   250,   251,   252,   253,   254,
     255,   256,   257,   258,   262,   268,   273,   279,   285,   291,
     297,   304,   310,   318,   331,   348,   357,   367,   386,   389,
     402,   411,   424,   427,   431,   438,   441,   442,   443,   444,
     447,   457,   462,   471,   476,   485,   489,   493,   498,   504,
     516,   533,   542,   553,   580,   585,   597,   601,   614,   631,
     636,   650,   655,   668,   678,   681,   691,   696,   705,   708,
     719,   724,   736,   744,   745,   746,   755,   758,   763,   771,
     776,   783,   787,   795,   798,   801,   809,   812,   817,   824,
     833,   846,   856,   861,   872,   875,   878,   881,   884,   888,
     891,   899,   900,   901,   902,   903,   904,   905,   906,   907,
     908,   912,   913,   917,   918,   921,   922,   923,   924,   925,
     930,   943,   951,   961,   962,   967,   970,   975,   983,   987,
     994,  1001,  1006,  1013,  1020,  1024
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
  "TRX_ROLLBACK", "INT_T", "STRING_T", "FLOAT_T", "DATE_T", "NULL_T",
  "HELP", "EXIT", "DOT", "INTO", "VALUES", "FROM", "WHERE", "AND", "SET",
  "ON", "LOAD", "DATA", "INFILE", "EXPLAIN", "EQ", "LT", "GT", "LE", "GE",
  "NE", "SUM", "COUNT", "AVG", "MIN", "MAX", "IS_", "NOT", "LK", "IN_OP",
  "EXIST_OP", "NUMBER", "FLOAT", "ID", "AGGRE_ATTR", "SSS", "'+'", "'-'",
  "'*'", "'/'", "UMINUS", "$accept", "commands", "command_wrapper",
  "exit_stmt", "help_stmt", "sync_stmt", "begin_stmt", "commit_stmt",
  "rollback_stmt", "drop_table_stmt", "show_tables_stmt",
  "desc_table_stmt", "create_index_stmt", "show_index_stmt",
  "drop_index_stmt", "create_table_stmt", "attr_def_list", "attr_def",
  "nullable", "number", "type", "insert_stmt", "value_list_list",
  "value_list", "value", "delete_stmt", "update_stmt", "update_list",
  "select_stmt", "selector", "rel_attr_aggre", "aggre_node", "rel_attr",
  "attr_list", "join_node", "select_join_list", "join_list",
  "select_order_list", "order_list", "order_node", "order_type",
  "rel_list", "parse_expr", "where", "condition_list", "condition",
  "calc_stmt", "expression_list", "expression", "comp_op", "in_op",
  "exist_op", "aggre_type", "load_data_stmt", "explain_stmt",
  "set_variable_stmt", "opt_semicolon", "aggre_attr_list",
  "aggre_attr_name", "id_list", "rel_name", "attr_name", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-187)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-144)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     106,   129,     7,    21,   -37,   -54,    80,  -187,    32,    -8,
      39,  -187,  -187,  -187,  -187,  -187,    63,     2,   106,    76,
      75,  -187,  -187,  -187,  -187,  -187,  -187,  -187,  -187,  -187,
    -187,  -187,  -187,  -187,  -187,  -187,  -187,  -187,  -187,  -187,
    -187,  -187,    65,    70,   131,    83,    88,    21,  -187,  -187,
    -187,  -187,    21,  -187,  -187,    26,  -187,  -187,  -187,  -187,
    -187,   136,  -187,    -1,  -187,  -187,  -187,   142,   137,  -187,
    -187,  -187,   135,   109,   110,   138,   130,   133,  -187,  -187,
    -187,  -187,   154,   140,   115,  -187,   141,    12,  -187,    21,
      21,    21,    21,    21,   -37,   116,    36,   -41,   119,   148,
     147,   123,   -25,   120,   124,   125,   149,   128,  -187,  -187,
      37,    37,  -187,  -187,  -187,  -187,    10,  -187,  -187,  -187,
    -187,  -187,   168,   171,  -187,   172,  -187,  -187,   174,     0,
    -187,   150,   -14,  -187,   162,    89,   175,   178,   143,  -187,
     189,   116,  -187,   147,   191,    36,  -187,   -25,   179,    -6,
     144,  -187,  -187,  -187,   107,  -187,   164,     9,   -25,   145,
    -187,   200,  -187,  -187,  -187,  -187,   -19,   124,   184,   151,
     187,   116,  -187,   198,  -187,  -187,   172,    90,  -187,   190,
     122,   192,  -187,  -187,  -187,  -187,  -187,  -187,  -187,   155,
     100,  -187,  -187,     9,     9,     9,  -187,  -187,   166,   152,
     156,  -187,   186,  -187,   175,  -187,  -187,   127,   151,   180,
     205,  -187,  -187,   -25,   -25,  -187,  -187,  -187,  -187,  -187,
    -187,  -187,  -187,   -25,  -187,   201,  -187,  -187,  -187,   158,
     139,     9,    35,  -187,   146,  -187,   -23,  -187,  -187,  -187,
      55,   197,  -187,  -187,  -187,  -187,  -187,  -187,    35,  -187
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,    26,     0,     0,
       0,    27,    28,    29,    25,    24,     0,     0,     0,     0,
     133,    23,    22,    15,    16,    17,    18,     9,    10,    11,
      12,    14,    13,     8,     5,     7,     6,     4,     3,    19,
      20,    21,     0,     0,     0,     0,     0,     0,    58,    55,
      56,    57,     0,   110,   101,   102,   125,   127,   126,   129,
     128,   144,   145,     0,    64,    67,    66,     0,     0,    69,
      32,    31,     0,     0,     0,     0,     0,     0,   131,     1,
     134,     2,     0,     0,     0,    30,     0,     0,   109,     0,
       0,     0,     0,     0,     0,    86,   135,     0,     0,     0,
      93,     0,     0,     0,     0,     0,     0,     0,   108,   103,
     104,   105,   106,   107,    65,   143,    74,    87,    45,   144,
     140,   139,     0,     0,   136,    71,    70,    35,     0,    96,
      59,     0,    93,   132,     0,     0,    38,     0,     0,    36,
       0,     0,    76,    93,    75,     0,    68,     0,    50,     0,
       0,   123,    89,    90,     0,    94,    97,     0,     0,     0,
      60,     0,    46,    47,    48,    49,    42,     0,     0,     0,
       0,     0,    88,    78,    77,   137,    72,     0,    53,     0,
       0,     0,   124,   111,   112,   113,   114,   115,   116,   119,
       0,   117,   121,     0,     0,    96,    95,    61,     0,     0,
       0,    44,     0,    41,    38,    37,   141,     0,     0,     0,
       0,    63,    51,     0,     0,    92,    91,   120,   118,   122,
      99,   100,    98,     0,   130,     0,    43,    39,    33,     0,
       0,    96,     0,    54,     0,    62,    42,   142,    34,    73,
      83,    79,    80,    52,    40,    84,    85,    82,     0,    81
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -187,  -187,   208,  -187,  -187,  -187,  -187,  -187,  -187,  -187,
    -187,  -187,  -187,  -187,  -187,  -187,    23,    62,    -5,    30,
    -187,  -187,  -187,  -147,  -101,  -187,  -187,  -187,    84,  -187,
     153,  -187,    -4,  -187,    91,  -187,  -187,  -187,  -187,   -16,
    -187,  -187,  -141,   -82,  -186,  -187,  -187,   157,    52,  -187,
    -187,  -187,  -187,  -187,  -187,  -187,  -187,  -187,    92,    28,
     -92,   -90
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,   168,   136,   203,   121,
     166,    34,   148,   177,    53,    35,    36,   132,    37,    63,
      64,    65,   153,   122,   142,   143,   144,   211,   241,   242,
     247,   116,   154,   130,   155,   156,    38,    54,    55,   193,
     194,   157,    67,    39,    40,    41,    81,   123,   124,   207,
      68,    69
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      66,   133,   180,   117,   200,     4,   125,   126,    48,   222,
     201,   159,    70,    45,   201,    46,   196,    56,    57,    58,
      59,    60,   140,   149,    94,   119,   129,    48,   152,    61,
      62,    74,   149,    48,    62,   141,   108,   202,    95,    49,
      50,   202,    48,    51,    47,   239,   178,    77,   178,   172,
     160,    89,   220,   221,    48,   176,   152,   197,    49,    50,
     150,   173,    51,   151,    49,    50,    61,   234,    51,    73,
     245,    62,   246,    49,    50,    61,    79,    51,    80,   209,
      62,    90,    91,    92,    93,    49,    50,    71,    72,    51,
      66,    52,   152,   152,   152,    90,    91,    92,    93,    87,
     118,    61,   119,   120,    88,    75,    62,    62,    92,    93,
       1,     2,   233,   178,   212,   213,     3,     4,   162,   163,
     164,   165,   235,     5,     6,     7,     8,     9,    10,    76,
     152,    82,    11,    12,    13,    42,    83,    43,    44,    84,
      14,    15,   110,   111,   112,   113,   215,   213,    16,    85,
      17,   228,   229,    18,    86,   183,   184,   185,   186,   187,
     188,   218,   219,   238,   229,    96,   189,   190,   191,   192,
     243,   213,  -143,    97,    98,    99,   100,   104,   102,   103,
     101,   106,   115,   105,   107,   127,   128,   129,   134,   131,
     135,   137,   138,   145,   139,   146,  -138,   147,   158,   161,
     167,   169,   171,   140,   179,   195,   199,   182,   205,   170,
     208,   198,   210,   214,   223,   217,   216,   206,   224,   226,
     118,   232,   248,   231,   237,   236,    78,   227,   240,   204,
     225,   244,   249,   181,     0,   174,   230,   175,     0,     0,
       0,     0,     0,     0,   240,     0,   109,   114
};

static const yytype_int16 yycheck[] =
{
       4,   102,   149,    95,    23,    11,    96,    97,    33,   195,
      33,    25,    66,     6,    33,     8,   157,    54,    55,    56,
      57,    58,    12,    23,    25,    66,    40,    33,   129,    66,
      71,    39,    23,    33,    71,    25,    24,    60,    39,    64,
      65,    60,    33,    68,    23,   231,   147,    45,   149,   141,
     132,    25,   193,   194,    33,   145,   157,   158,    64,    65,
      60,   143,    68,    63,    64,    65,    66,   214,    68,    37,
      15,    71,    17,    64,    65,    66,     0,    68,     3,   171,
      71,    69,    70,    71,    72,    64,    65,     7,     8,    68,
      94,    70,   193,   194,   195,    69,    70,    71,    72,    47,
      64,    66,    66,    67,    52,    66,    71,    71,    71,    72,
       4,     5,   213,   214,    24,    25,    10,    11,    29,    30,
      31,    32,   223,    17,    18,    19,    20,    21,    22,    66,
     231,    66,    26,    27,    28,     6,    66,     8,     9,     8,
      34,    35,    90,    91,    92,    93,    24,    25,    42,    66,
      44,    24,    25,    47,    66,    48,    49,    50,    51,    52,
      53,    61,    62,    24,    25,    23,    59,    60,    61,    62,
      24,    25,    36,    36,    39,    66,    66,    23,    48,    46,
      42,    66,    66,    43,    43,    66,    38,    40,    68,    66,
      66,    66,    43,    25,    66,    24,    24,    23,    48,    37,
      25,    23,    13,    12,    25,    41,     6,    63,    24,    66,
      23,    66,    14,    23,    48,    60,    24,    66,    66,    33,
      64,    16,    25,    43,    66,    24,    18,   204,   232,   167,
     200,   236,   248,   149,    -1,   144,   208,   145,    -1,    -1,
      -1,    -1,    -1,    -1,   248,    -1,    89,    94
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     4,     5,    10,    11,    17,    18,    19,    20,    21,
      22,    26,    27,    28,    34,    35,    42,    44,    47,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    95,    99,   100,   102,   120,   127,
     128,   129,     6,     8,     9,     6,     8,    23,    33,    64,
      65,    68,    70,    98,   121,   122,    54,    55,    56,    57,
      58,    66,    71,   103,   104,   105,   106,   126,   134,   135,
      66,     7,     8,    37,    39,    66,    66,    45,    76,     0,
       3,   130,    66,    66,     8,    66,    66,   122,   122,    25,
      69,    70,    71,    72,    25,    39,    23,    36,    39,    66,
      66,    42,    48,    46,    23,    43,    66,    43,    24,   121,
     122,   122,   122,   122,   104,    66,   115,   134,    64,    66,
      67,    93,   107,   131,   132,   135,   135,    66,    38,    40,
     117,    66,   101,    98,    68,    66,    91,    66,    43,    66,
      12,    25,   108,   109,   110,    25,    24,    23,    96,    23,
      60,    63,    98,   106,   116,   118,   119,   125,    48,    25,
     117,    37,    29,    30,    31,    32,    94,    25,    90,    23,
      66,    13,   134,   117,   108,   132,   135,    97,    98,    25,
      97,   102,    63,    48,    49,    50,    51,    52,    53,    59,
      60,    61,    62,   123,   124,    41,   116,    98,    66,     6,
      23,    33,    60,    92,    91,    24,    66,   133,    23,   134,
      14,   111,    24,    25,    23,    24,    24,    60,    61,    62,
     116,   116,   118,    48,    66,    93,    33,    90,    24,    25,
     133,    43,    16,    98,    97,    98,    24,    66,    24,   118,
     106,   112,   113,    24,    92,    15,    17,   114,    25,   113
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    74,    75,    76,    76,    76,    76,    76,    76,    76,
      76,    76,    76,    76,    76,    76,    76,    76,    76,    76,
      76,    76,    76,    76,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    86,    87,    88,    89,    90,    90,
      91,    91,    92,    92,    92,    93,    94,    94,    94,    94,
      95,    96,    96,    97,    97,    98,    98,    98,    98,    99,
     100,   101,   101,   102,   103,   103,   104,   104,   105,   106,
     106,   107,   107,   108,   109,   109,   110,   110,   111,   111,
     112,   112,   113,   114,   114,   114,   115,   115,   115,   116,
     116,   116,   116,   117,   117,   117,   118,   118,   118,   119,
     119,   120,   121,   121,   122,   122,   122,   122,   122,   122,
     122,   123,   123,   123,   123,   123,   123,   123,   123,   123,
     123,   124,   124,   125,   125,   126,   126,   126,   126,   126,
     127,   128,   129,   130,   130,   131,   131,   131,   132,   132,
     132,   133,   133,   134,   135,   135
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     2,     2,     8,     9,     4,     5,     7,     0,     3,
       6,     3,     0,     2,     1,     1,     1,     1,     1,     1,
       5,     3,     5,     1,     3,     1,     1,     1,     1,     4,
       5,     3,     5,     7,     1,     3,     1,     1,     4,     1,
       3,     1,     3,     5,     0,     1,     1,     2,     0,     3,
       1,     3,     2,     0,     1,     1,     0,     1,     3,     1,
       1,     3,     3,     0,     2,     3,     0,     1,     3,     3,
       3,     2,     1,     3,     3,     3,     3,     3,     3,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     2,     1,
       2,     1,     2,     1,     2,     1,     1,     1,     1,     1,
       7,     2,     4,     0,     1,     0,     1,     3,     1,     1,
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
#line 231 "yacc_sql.y"
  {
    std::unique_ptr<ParsedSqlNode> sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[-1].sql_node));
    sql_result->add_sql_node(std::move(sql_node));
  }
#line 1832 "yacc_sql.cpp"
    break;

  case 24: /* exit_stmt: EXIT  */
#line 262 "yacc_sql.y"
         {
      (void)yynerrs;  // 这么写为了消除yynerrs未使用的告警。如果你有更好的方法欢迎提PR
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXIT);
    }
#line 1841 "yacc_sql.cpp"
    break;

  case 25: /* help_stmt: HELP  */
#line 268 "yacc_sql.y"
         {
      (yyval.sql_node) = new ParsedSqlNode(SCF_HELP);
    }
#line 1849 "yacc_sql.cpp"
    break;

  case 26: /* sync_stmt: SYNC  */
#line 273 "yacc_sql.y"
         {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SYNC);
    }
#line 1857 "yacc_sql.cpp"
    break;

  case 27: /* begin_stmt: TRX_BEGIN  */
#line 279 "yacc_sql.y"
               {
      (yyval.sql_node) = new ParsedSqlNode(SCF_BEGIN);
    }
#line 1865 "yacc_sql.cpp"
    break;

  case 28: /* commit_stmt: TRX_COMMIT  */
#line 285 "yacc_sql.y"
               {
      (yyval.sql_node) = new ParsedSqlNode(SCF_COMMIT);
    }
#line 1873 "yacc_sql.cpp"
    break;

  case 29: /* rollback_stmt: TRX_ROLLBACK  */
#line 291 "yacc_sql.y"
                  {
      (yyval.sql_node) = new ParsedSqlNode(SCF_ROLLBACK);
    }
#line 1881 "yacc_sql.cpp"
    break;

  case 30: /* drop_table_stmt: DROP TABLE ID  */
#line 297 "yacc_sql.y"
                  {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_TABLE);
      (yyval.sql_node)->drop_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 1891 "yacc_sql.cpp"
    break;

  case 31: /* show_tables_stmt: SHOW TABLES  */
#line 304 "yacc_sql.y"
                {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SHOW_TABLES);
    }
#line 1899 "yacc_sql.cpp"
    break;

  case 32: /* desc_table_stmt: DESC ID  */
#line 310 "yacc_sql.y"
             {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DESC_TABLE);
      (yyval.sql_node)->desc_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 1909 "yacc_sql.cpp"
    break;

  case 33: /* create_index_stmt: CREATE INDEX ID ON ID LBRACE id_list RBRACE  */
#line 319 "yacc_sql.y"
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
#line 1926 "yacc_sql.cpp"
    break;

  case 34: /* create_index_stmt: CREATE UNIQUE INDEX ID ON ID LBRACE id_list RBRACE  */
#line 332 "yacc_sql.y"
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
#line 1944 "yacc_sql.cpp"
    break;

  case 35: /* show_index_stmt: SHOW INDEX FROM ID  */
#line 349 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SHOW_INDEX);
      (yyval.sql_node)->show_index.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 1954 "yacc_sql.cpp"
    break;

  case 36: /* drop_index_stmt: DROP INDEX ID ON ID  */
#line 358 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_INDEX);
      (yyval.sql_node)->drop_index.index_name = (yyvsp[-2].string);
      (yyval.sql_node)->drop_index.relation_name = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 1966 "yacc_sql.cpp"
    break;

  case 37: /* create_table_stmt: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE  */
#line 368 "yacc_sql.y"
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
#line 1986 "yacc_sql.cpp"
    break;

  case 38: /* attr_def_list: %empty  */
#line 386 "yacc_sql.y"
    {
      (yyval.attr_infos) = nullptr;
    }
#line 1994 "yacc_sql.cpp"
    break;

  case 39: /* attr_def_list: COMMA attr_def attr_def_list  */
#line 390 "yacc_sql.y"
    {
      if ((yyvsp[0].attr_infos) != nullptr) {
        (yyval.attr_infos) = (yyvsp[0].attr_infos);
      } else {
        (yyval.attr_infos) = new std::vector<AttrInfoSqlNode>;
      }
      (yyval.attr_infos)->emplace_back(*(yyvsp[-1].attr_info));
      delete (yyvsp[-1].attr_info);
    }
#line 2008 "yacc_sql.cpp"
    break;

  case 40: /* attr_def: ID type LBRACE number RBRACE nullable  */
#line 403 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-4].number);
      (yyval.attr_info)->name = (yyvsp[-5].string);
      (yyval.attr_info)->length = (yyvsp[-2].number);
      (yyval.attr_info)->nullable = (yyvsp[0].nullable);
      free((yyvsp[-5].string));
    }
#line 2021 "yacc_sql.cpp"
    break;

  case 41: /* attr_def: ID type nullable  */
#line 412 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-1].number);
      (yyval.attr_info)->name = (yyvsp[-2].string);
      (yyval.attr_info)->length = 4;
      (yyval.attr_info)->nullable = (yyvsp[0].nullable);
      free((yyvsp[-2].string));
    }
#line 2034 "yacc_sql.cpp"
    break;

  case 42: /* nullable: %empty  */
#line 424 "yacc_sql.y"
    {
      (yyval.nullable) = true; // 字段默认是可以为null的
    }
#line 2042 "yacc_sql.cpp"
    break;

  case 43: /* nullable: NOT NULL_T  */
#line 428 "yacc_sql.y"
    {
      (yyval.nullable) = false;
    }
#line 2050 "yacc_sql.cpp"
    break;

  case 44: /* nullable: NULL_T  */
#line 432 "yacc_sql.y"
    {
      (yyval.nullable) = true;
    }
#line 2058 "yacc_sql.cpp"
    break;

  case 45: /* number: NUMBER  */
#line 438 "yacc_sql.y"
           {(yyval.number) = (yyvsp[0].number);}
#line 2064 "yacc_sql.cpp"
    break;

  case 46: /* type: INT_T  */
#line 441 "yacc_sql.y"
               { (yyval.number)=INTS; }
#line 2070 "yacc_sql.cpp"
    break;

  case 47: /* type: STRING_T  */
#line 442 "yacc_sql.y"
               { (yyval.number)=CHARS; }
#line 2076 "yacc_sql.cpp"
    break;

  case 48: /* type: FLOAT_T  */
#line 443 "yacc_sql.y"
               { (yyval.number)=FLOATS; }
#line 2082 "yacc_sql.cpp"
    break;

  case 49: /* type: DATE_T  */
#line 444 "yacc_sql.y"
               { (yyval.number)=DATES;}
#line 2088 "yacc_sql.cpp"
    break;

  case 50: /* insert_stmt: INSERT INTO ID VALUES value_list_list  */
#line 448 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_INSERT);
      (yyval.sql_node)->insertion.relation_name = (yyvsp[-2].string);
      (yyval.sql_node)->insertion.values_list = *(yyvsp[0].value_list_list);
      free((yyvsp[-2].string));
    }
#line 2099 "yacc_sql.cpp"
    break;

  case 51: /* value_list_list: LBRACE value_list RBRACE  */
#line 458 "yacc_sql.y"
    {
      (yyval.value_list_list) = new std::vector<std::vector<Value>>{*(yyvsp[-1].value_list)};
      delete (yyvsp[-1].value_list);
    }
#line 2108 "yacc_sql.cpp"
    break;

  case 52: /* value_list_list: value_list_list COMMA LBRACE value_list RBRACE  */
#line 463 "yacc_sql.y"
    {
      (yyval.value_list_list)->emplace_back(*(yyvsp[-1].value_list));
      delete (yyvsp[-1].value_list);
    }
#line 2117 "yacc_sql.cpp"
    break;

  case 53: /* value_list: value  */
#line 472 "yacc_sql.y"
  {
    (yyval.value_list) = new std::vector<Value>{*(yyvsp[0].value)};
    delete (yyvsp[0].value); /* relese the pointer*/
  }
#line 2126 "yacc_sql.cpp"
    break;

  case 54: /* value_list: value_list COMMA value  */
#line 477 "yacc_sql.y"
  {
    (yyval.value_list)->emplace_back(*(yyvsp[0].value));
    delete (yyvsp[0].value);
  }
#line 2135 "yacc_sql.cpp"
    break;

  case 55: /* value: NUMBER  */
#line 485 "yacc_sql.y"
           {
      (yyval.value) = new Value((int)(yyvsp[0].number));
      (yyloc) = (yylsp[0]);
    }
#line 2144 "yacc_sql.cpp"
    break;

  case 56: /* value: FLOAT  */
#line 489 "yacc_sql.y"
           {
      (yyval.value) = new Value((float)(yyvsp[0].floats));
      (yyloc) = (yylsp[0]);
    }
#line 2153 "yacc_sql.cpp"
    break;

  case 57: /* value: SSS  */
#line 493 "yacc_sql.y"
         {
      char *tmp = common::substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
      (yyval.value) = new Value(tmp);
      free(tmp);
    }
#line 2163 "yacc_sql.cpp"
    break;

  case 58: /* value: NULL_T  */
#line 498 "yacc_sql.y"
             {
      (yyval.value) = new Value();
    }
#line 2171 "yacc_sql.cpp"
    break;

  case 59: /* delete_stmt: DELETE FROM ID where  */
#line 505 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DELETE);
      (yyval.sql_node)->deletion.relation_name = (yyvsp[-1].string);
      if ((yyvsp[0].condition_list) != nullptr) {
        (yyval.sql_node)->deletion.conditions.swap(*(yyvsp[0].condition_list));
        delete (yyvsp[0].condition_list);
      }
      free((yyvsp[-1].string));
    }
#line 2185 "yacc_sql.cpp"
    break;

  case 60: /* update_stmt: UPDATE ID SET update_list where  */
#line 517 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_UPDATE);
      (yyval.sql_node)->update.relation_name = (yyvsp[-3].string);
      (yyval.sql_node)->update.attr_list = (yyvsp[-1].update_list)->first;
      (yyval.sql_node)->update.value_list = (yyvsp[-1].update_list)->second;

      if ((yyvsp[0].condition_list) != nullptr) {
        (yyval.sql_node)->update.conditions.swap(*(yyvsp[0].condition_list));
        delete (yyvsp[0].condition_list);
      }
      free((yyvsp[-3].string));
      delete (yyvsp[-1].update_list);
    }
#line 2203 "yacc_sql.cpp"
    break;

  case 61: /* update_list: ID EQ value  */
#line 534 "yacc_sql.y"
    {
      (yyval.update_list) = new std::pair<std::vector<std::string>, std::vector<Value>>;
      (yyval.update_list)->first.emplace_back((yyvsp[-2].string));
      (yyval.update_list)->second.emplace_back(*(yyvsp[0].value));

      delete (yyvsp[-2].string);
      delete (yyvsp[0].value);
    }
#line 2216 "yacc_sql.cpp"
    break;

  case 62: /* update_list: update_list COMMA ID EQ value  */
#line 543 "yacc_sql.y"
    {
      (yyval.update_list) = (yyvsp[-4].update_list);
      (yyval.update_list)->first.emplace_back((yyvsp[-2].string));
      (yyval.update_list)->second.emplace_back(*(yyvsp[0].value));
      delete (yyvsp[-2].string);
      delete (yyvsp[0].value);
    }
#line 2228 "yacc_sql.cpp"
    break;

  case 63: /* select_stmt: SELECT selector FROM rel_list select_join_list where select_order_list  */
#line 554 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SELECT);
      if ((yyvsp[-5].rel_attr_list) != nullptr) {
        (yyval.sql_node)->selection.attributes.swap(*(yyvsp[-5].rel_attr_list));
        delete (yyvsp[-5].rel_attr_list);
      }
      if ((yyvsp[-3].relation_list) != nullptr) {
        (yyval.sql_node)->selection.relations.swap(*(yyvsp[-3].relation_list));
        delete (yyvsp[-3].relation_list);
      }
      if ((yyvsp[-2].join_list) != nullptr) {
        (yyval.sql_node)->selection.joinctions.swap(*(yyvsp[-2].join_list));
        delete (yyvsp[-2].join_list);
      }
      if ((yyvsp[-1].condition_list) != nullptr) {
        (yyval.sql_node)->selection.conditions.swap(*(yyvsp[-1].condition_list));
        delete (yyvsp[-1].condition_list);
      }
      if ((yyvsp[0].order_list) != nullptr) {
        (yyval.sql_node)->selection.orders.swap(*(yyvsp[0].order_list));
        delete (yyvsp[0].order_list);
      }
    }
#line 2256 "yacc_sql.cpp"
    break;

  case 64: /* selector: rel_attr_aggre  */
#line 581 "yacc_sql.y"
    {
      (yyval.rel_attr_list) = new std::vector<RelAttrSqlNode>{*(yyvsp[0].rel_attr)}; 
      delete (yyvsp[0].rel_attr);  
    }
#line 2265 "yacc_sql.cpp"
    break;

  case 65: /* selector: selector COMMA rel_attr_aggre  */
#line 586 "yacc_sql.y"
    {
      (yyval.rel_attr_list)->emplace_back(*(yyvsp[0].rel_attr)); 
      delete (yyvsp[0].rel_attr); 
    }
#line 2274 "yacc_sql.cpp"
    break;

  case 66: /* rel_attr_aggre: rel_attr  */
#line 598 "yacc_sql.y"
    {
      (yyval.rel_attr) = (yyvsp[0].rel_attr); 
    }
#line 2282 "yacc_sql.cpp"
    break;

  case 67: /* rel_attr_aggre: aggre_node  */
#line 602 "yacc_sql.y"
    {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->aggretion_node = *(yyvsp[0].aggre_node); 
      delete (yyvsp[0].aggre_node); 
    }
#line 2292 "yacc_sql.cpp"
    break;

  case 68: /* aggre_node: aggre_type LBRACE aggre_attr_list RBRACE  */
#line 615 "yacc_sql.y"
    {
      (yyval.aggre_node) = new AggreTypeNode;
      (yyval.aggre_node)->aggre_type = (yyvsp[-3].aggre_type); 
      if ((yyvsp[-1].aggre_attr_list) != nullptr) {
        (yyval.aggre_node)->attribute_names.swap(*(yyvsp[-1].aggre_attr_list)); 
        delete (yyvsp[-1].aggre_attr_list); 
      }
    }
#line 2305 "yacc_sql.cpp"
    break;

  case 69: /* rel_attr: attr_name  */
#line 632 "yacc_sql.y"
    {
      (yyval.rel_attr) = new RelAttrSqlNode{"", (yyvsp[0].string)};
      free((yyvsp[0].string));
    }
#line 2314 "yacc_sql.cpp"
    break;

  case 70: /* rel_attr: rel_name DOT attr_name  */
#line 637 "yacc_sql.y"
    {
      (yyval.rel_attr) = new RelAttrSqlNode{(yyvsp[-2].string), (yyvsp[0].string)};
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 2324 "yacc_sql.cpp"
    break;

  case 71: /* attr_list: attr_name  */
#line 651 "yacc_sql.y"
    {
      (yyval.relation_list) = new std::vector<std::string>{(yyvsp[0].string)};
      free((yyvsp[0].string)); 
    }
#line 2333 "yacc_sql.cpp"
    break;

  case 72: /* attr_list: attr_list COMMA attr_name  */
#line 656 "yacc_sql.y"
    {
      (yyval.relation_list)->emplace_back((yyvsp[0].string)); 
      free((yyvsp[0].string));
    }
#line 2342 "yacc_sql.cpp"
    break;

  case 73: /* join_node: INNER JOIN rel_name ON condition_list  */
#line 669 "yacc_sql.y"
    {
      (yyval.join_node) = new JoinSqlNode{(yyvsp[-2].string),*(yyvsp[0].condition_list)};
      delete (yyvsp[-2].string);
      delete (yyvsp[0].condition_list);
    }
#line 2352 "yacc_sql.cpp"
    break;

  case 74: /* select_join_list: %empty  */
#line 678 "yacc_sql.y"
    {
      (yyval.join_list) = nullptr; 
    }
#line 2360 "yacc_sql.cpp"
    break;

  case 75: /* select_join_list: join_list  */
#line 682 "yacc_sql.y"
    {
      (yyval.join_list) = (yyvsp[0].join_list); 
    }
#line 2368 "yacc_sql.cpp"
    break;

  case 76: /* join_list: join_node  */
#line 692 "yacc_sql.y"
    {
      (yyval.join_list) = new std::vector<JoinSqlNode>{*(yyvsp[0].join_node)};
      delete (yyvsp[0].join_node);   
    }
#line 2377 "yacc_sql.cpp"
    break;

  case 77: /* join_list: join_list join_node  */
#line 697 "yacc_sql.y"
    {
      (yyval.join_list)->emplace_back(*(yyvsp[0].join_node));
      delete (yyvsp[0].join_node);
    }
#line 2386 "yacc_sql.cpp"
    break;

  case 78: /* select_order_list: %empty  */
#line 705 "yacc_sql.y"
    {
      (yyval.order_list) = nullptr; // 没有order
    }
#line 2394 "yacc_sql.cpp"
    break;

  case 79: /* select_order_list: ORDER BY order_list  */
#line 709 "yacc_sql.y"
    {
      (yyval.order_list) = (yyvsp[0].order_list);
    }
#line 2402 "yacc_sql.cpp"
    break;

  case 80: /* order_list: order_node  */
#line 720 "yacc_sql.y"
    {
      (yyval.order_list) = new std::vector<OrderSqlNode>{*(yyvsp[0].order_node)};
      delete (yyvsp[0].order_node);
    }
#line 2411 "yacc_sql.cpp"
    break;

  case 81: /* order_list: order_list COMMA order_node  */
#line 725 "yacc_sql.y"
    {
      (yyval.order_list)->emplace_back(*(yyvsp[0].order_node));
      delete (yyvsp[0].order_node);
    }
#line 2420 "yacc_sql.cpp"
    break;

  case 82: /* order_node: rel_attr order_type  */
#line 737 "yacc_sql.y"
    {
      (yyval.order_node) = new OrderSqlNode{*(yyvsp[-1].rel_attr),(yyvsp[0].order_type)};
      delete (yyvsp[-1].rel_attr);
    }
#line 2429 "yacc_sql.cpp"
    break;

  case 83: /* order_type: %empty  */
#line 744 "yacc_sql.y"
           { (yyval.order_type) = ORDER_ASC; }
#line 2435 "yacc_sql.cpp"
    break;

  case 84: /* order_type: ASC  */
#line 745 "yacc_sql.y"
           { (yyval.order_type) = ORDER_ASC; }
#line 2441 "yacc_sql.cpp"
    break;

  case 85: /* order_type: DESC  */
#line 746 "yacc_sql.y"
           { (yyval.order_type) = ORDER_DESC; }
#line 2447 "yacc_sql.cpp"
    break;

  case 86: /* rel_list: %empty  */
#line 755 "yacc_sql.y"
    {
      (yyval.relation_list) = nullptr;
    }
#line 2455 "yacc_sql.cpp"
    break;

  case 87: /* rel_list: rel_name  */
#line 759 "yacc_sql.y"
    {
      (yyval.relation_list) = new std::vector<std::string>{(yyvsp[0].string)};
      free((yyvsp[0].string)); 
    }
#line 2464 "yacc_sql.cpp"
    break;

  case 88: /* rel_list: rel_list COMMA rel_name  */
#line 764 "yacc_sql.y"
    {
      (yyval.relation_list)->emplace_back((yyvsp[0].string)); 
      free((yyvsp[0].string));
    }
#line 2473 "yacc_sql.cpp"
    break;

  case 89: /* parse_expr: value  */
#line 772 "yacc_sql.y"
    {
      (yyval.parse_expr) = new ParseValueExpr(*(yyvsp[0].value));
      delete (yyvsp[0].value);
    }
#line 2482 "yacc_sql.cpp"
    break;

  case 90: /* parse_expr: rel_attr  */
#line 777 "yacc_sql.y"
    {
      std::string &table_name = (yyvsp[0].rel_attr)->relation_name;
      std::string &field_name = (yyvsp[0].rel_attr)->attribute_name;
      (yyval.parse_expr) = new ParseFieldExpr(table_name,field_name);
      delete (yyvsp[0].rel_attr);
    }
#line 2493 "yacc_sql.cpp"
    break;

  case 91: /* parse_expr: LBRACE select_stmt RBRACE  */
#line 784 "yacc_sql.y"
    {
      (yyval.parse_expr) = new ParseSubQueryExpr((yyvsp[-1].sql_node)->selection);
    }
#line 2501 "yacc_sql.cpp"
    break;

  case 92: /* parse_expr: LBRACE value_list RBRACE  */
#line 788 "yacc_sql.y"
    {
      (yyval.parse_expr) = new ParseValueListExpr(*(yyvsp[-1].value_list));
      delete (yyvsp[-1].value_list);
    }
#line 2510 "yacc_sql.cpp"
    break;

  case 93: /* where: %empty  */
#line 795 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 2518 "yacc_sql.cpp"
    break;

  case 94: /* where: WHERE condition_list  */
#line 798 "yacc_sql.y"
                           {
      (yyval.condition_list) = (yyvsp[0].condition_list);
    }
#line 2526 "yacc_sql.cpp"
    break;

  case 95: /* where: WHERE exist_op parse_expr  */
#line 802 "yacc_sql.y"
    {
      (yyval.condition_list) = new std::vector<ConditionSqlNode>;
      (yyval.condition_list)->emplace_back(ConditionSqlNode{nullptr,(yyvsp[-1].comp),(yyvsp[0].parse_expr)});
    }
#line 2535 "yacc_sql.cpp"
    break;

  case 96: /* condition_list: %empty  */
#line 809 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 2543 "yacc_sql.cpp"
    break;

  case 97: /* condition_list: condition  */
#line 812 "yacc_sql.y"
                {
      (yyval.condition_list) = new std::vector<ConditionSqlNode>;
      (yyval.condition_list)->emplace_back(*(yyvsp[0].condition));
      delete (yyvsp[0].condition);
    }
#line 2553 "yacc_sql.cpp"
    break;

  case 98: /* condition_list: condition AND condition_list  */
#line 817 "yacc_sql.y"
                                   {
      (yyval.condition_list) = (yyvsp[0].condition_list);
      (yyval.condition_list)->emplace_back(*(yyvsp[-2].condition));
      delete (yyvsp[-2].condition);
    }
#line 2563 "yacc_sql.cpp"
    break;

  case 99: /* condition: parse_expr comp_op parse_expr  */
#line 825 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left = (yyvsp[-2].parse_expr);

      (yyval.condition)->comp = (yyvsp[-1].comp);

      (yyval.condition)->right = (yyvsp[0].parse_expr);
    }
#line 2576 "yacc_sql.cpp"
    break;

  case 100: /* condition: parse_expr in_op parse_expr  */
#line 834 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left = (yyvsp[-2].parse_expr);

      (yyval.condition)->comp = (yyvsp[-1].comp);

      (yyval.condition)->right = (yyvsp[0].parse_expr);
    }
#line 2589 "yacc_sql.cpp"
    break;

  case 101: /* calc_stmt: CALC expression_list  */
#line 847 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CALC);
      std::reverse((yyvsp[0].expression_list)->begin(), (yyvsp[0].expression_list)->end());
      (yyval.sql_node)->calc.expressions.swap(*(yyvsp[0].expression_list));
      delete (yyvsp[0].expression_list);
    }
#line 2600 "yacc_sql.cpp"
    break;

  case 102: /* expression_list: expression  */
#line 857 "yacc_sql.y"
    {
      (yyval.expression_list) = new std::vector<Expression*>;
      (yyval.expression_list)->emplace_back((yyvsp[0].expression));
    }
#line 2609 "yacc_sql.cpp"
    break;

  case 103: /* expression_list: expression COMMA expression_list  */
#line 862 "yacc_sql.y"
    {
      if ((yyvsp[0].expression_list) != nullptr) {
        (yyval.expression_list) = (yyvsp[0].expression_list);
      } else {
        (yyval.expression_list) = new std::vector<Expression *>;
      }
      (yyval.expression_list)->emplace_back((yyvsp[-2].expression));
    }
#line 2622 "yacc_sql.cpp"
    break;

  case 104: /* expression: expression '+' expression  */
#line 872 "yacc_sql.y"
                              {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::ADD, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2630 "yacc_sql.cpp"
    break;

  case 105: /* expression: expression '-' expression  */
#line 875 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::SUB, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2638 "yacc_sql.cpp"
    break;

  case 106: /* expression: expression '*' expression  */
#line 878 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::MUL, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2646 "yacc_sql.cpp"
    break;

  case 107: /* expression: expression '/' expression  */
#line 881 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::DIV, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2654 "yacc_sql.cpp"
    break;

  case 108: /* expression: LBRACE expression RBRACE  */
#line 884 "yacc_sql.y"
                               {
      (yyval.expression) = (yyvsp[-1].expression);
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
    }
#line 2663 "yacc_sql.cpp"
    break;

  case 109: /* expression: '-' expression  */
#line 888 "yacc_sql.y"
                                  {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::NEGATIVE, (yyvsp[0].expression), nullptr, sql_string, &(yyloc));
    }
#line 2671 "yacc_sql.cpp"
    break;

  case 110: /* expression: value  */
#line 891 "yacc_sql.y"
            {
      (yyval.expression) = new ValueExpr(*(yyvsp[0].value));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[0].value);
    }
#line 2681 "yacc_sql.cpp"
    break;

  case 111: /* comp_op: EQ  */
#line 899 "yacc_sql.y"
         { (yyval.comp) = EQUAL_TO; }
#line 2687 "yacc_sql.cpp"
    break;

  case 112: /* comp_op: LT  */
#line 900 "yacc_sql.y"
         { (yyval.comp) = LESS_THAN; }
#line 2693 "yacc_sql.cpp"
    break;

  case 113: /* comp_op: GT  */
#line 901 "yacc_sql.y"
         { (yyval.comp) = GREAT_THAN; }
#line 2699 "yacc_sql.cpp"
    break;

  case 114: /* comp_op: LE  */
#line 902 "yacc_sql.y"
         { (yyval.comp) = LESS_EQUAL; }
#line 2705 "yacc_sql.cpp"
    break;

  case 115: /* comp_op: GE  */
#line 903 "yacc_sql.y"
         { (yyval.comp) = GREAT_EQUAL; }
#line 2711 "yacc_sql.cpp"
    break;

  case 116: /* comp_op: NE  */
#line 904 "yacc_sql.y"
         { (yyval.comp) = NOT_EQUAL; }
#line 2717 "yacc_sql.cpp"
    break;

  case 117: /* comp_op: LK  */
#line 905 "yacc_sql.y"
         { (yyval.comp) = LIKE; }
#line 2723 "yacc_sql.cpp"
    break;

  case 118: /* comp_op: NOT LK  */
#line 906 "yacc_sql.y"
             { (yyval.comp) = NOT_LIKE;}
#line 2729 "yacc_sql.cpp"
    break;

  case 119: /* comp_op: IS_  */
#line 907 "yacc_sql.y"
          { (yyval.comp) = IS;}
#line 2735 "yacc_sql.cpp"
    break;

  case 120: /* comp_op: IS_ NOT  */
#line 908 "yacc_sql.y"
              { (yyval.comp) = IS_NOT;}
#line 2741 "yacc_sql.cpp"
    break;

  case 121: /* in_op: IN_OP  */
#line 912 "yacc_sql.y"
            {(yyval.comp) = IN;}
#line 2747 "yacc_sql.cpp"
    break;

  case 122: /* in_op: NOT IN_OP  */
#line 913 "yacc_sql.y"
                {(yyval.comp) = NOT_IN;}
#line 2753 "yacc_sql.cpp"
    break;

  case 123: /* exist_op: EXIST_OP  */
#line 917 "yacc_sql.y"
               {(yyval.comp) = EXIST;}
#line 2759 "yacc_sql.cpp"
    break;

  case 124: /* exist_op: NOT EXIST_OP  */
#line 918 "yacc_sql.y"
                   {(yyval.comp) = NOT_EXIST;}
#line 2765 "yacc_sql.cpp"
    break;

  case 125: /* aggre_type: SUM  */
#line 921 "yacc_sql.y"
            { (yyval.aggre_type) = AGGRE_SUM; }
#line 2771 "yacc_sql.cpp"
    break;

  case 126: /* aggre_type: AVG  */
#line 922 "yacc_sql.y"
            { (yyval.aggre_type) = AGGRE_AVG; }
#line 2777 "yacc_sql.cpp"
    break;

  case 127: /* aggre_type: COUNT  */
#line 923 "yacc_sql.y"
            { (yyval.aggre_type) = AGGRE_COUNT; }
#line 2783 "yacc_sql.cpp"
    break;

  case 128: /* aggre_type: MAX  */
#line 924 "yacc_sql.y"
            { (yyval.aggre_type) = AGGRE_MAX; }
#line 2789 "yacc_sql.cpp"
    break;

  case 129: /* aggre_type: MIN  */
#line 925 "yacc_sql.y"
            { (yyval.aggre_type) = AGGRE_MIN; }
#line 2795 "yacc_sql.cpp"
    break;

  case 130: /* load_data_stmt: LOAD DATA INFILE SSS INTO TABLE ID  */
#line 931 "yacc_sql.y"
    {
      char *tmp_file_name = common::substr((yyvsp[-3].string), 1, strlen((yyvsp[-3].string)) - 2);
      
      (yyval.sql_node) = new ParsedSqlNode(SCF_LOAD_DATA);
      (yyval.sql_node)->load_data.relation_name = (yyvsp[0].string);
      (yyval.sql_node)->load_data.file_name = tmp_file_name;
      free((yyvsp[0].string));
      free(tmp_file_name);
    }
#line 2809 "yacc_sql.cpp"
    break;

  case 131: /* explain_stmt: EXPLAIN command_wrapper  */
#line 944 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXPLAIN);
      (yyval.sql_node)->explain.sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[0].sql_node));
    }
#line 2818 "yacc_sql.cpp"
    break;

  case 132: /* set_variable_stmt: SET ID EQ value  */
#line 952 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SET_VARIABLE);
      (yyval.sql_node)->set_variable.name  = (yyvsp[-2].string);
      (yyval.sql_node)->set_variable.value = *(yyvsp[0].value);
      free((yyvsp[-2].string));
      delete (yyvsp[0].value);
    }
#line 2830 "yacc_sql.cpp"
    break;

  case 135: /* aggre_attr_list: %empty  */
#line 967 "yacc_sql.y"
    {
      (yyval.aggre_attr_list) = nullptr; 
    }
#line 2838 "yacc_sql.cpp"
    break;

  case 136: /* aggre_attr_list: aggre_attr_name  */
#line 971 "yacc_sql.y"
    {
      (yyval.aggre_attr_list) = new std::vector<std::string>{(yyvsp[0].string)};
      free((yyvsp[0].string)); 
    }
#line 2847 "yacc_sql.cpp"
    break;

  case 137: /* aggre_attr_list: attr_list COMMA aggre_attr_name  */
#line 976 "yacc_sql.y"
    {
      (yyval.aggre_attr_list)->emplace_back((yyvsp[0].string)); 
      free((yyvsp[0].string));
    }
#line 2856 "yacc_sql.cpp"
    break;

  case 138: /* aggre_attr_name: attr_name  */
#line 984 "yacc_sql.y"
    {
      (yyval.string) = (yyvsp[0].string); 
    }
#line 2864 "yacc_sql.cpp"
    break;

  case 139: /* aggre_attr_name: number  */
#line 988 "yacc_sql.y"
    {
      int str_len = snprintf(NULL, 0, "%d", (yyvsp[0].number));
      char *str = (char *)malloc((str_len + 1) * sizeof(char));
      snprintf(str, str_len + 1, "%d", (yyvsp[0].number));
      (yyval.string) = str;
    }
#line 2875 "yacc_sql.cpp"
    break;

  case 140: /* aggre_attr_name: AGGRE_ATTR  */
#line 995 "yacc_sql.y"
    {
      (yyval.string) = (yyvsp[0].string); 
    }
#line 2883 "yacc_sql.cpp"
    break;

  case 141: /* id_list: ID  */
#line 1002 "yacc_sql.y"
    {
      (yyval.id_list) = new std::vector<std::string>{(yyvsp[0].string)}; 
      free((yyvsp[0].string)); 
    }
#line 2892 "yacc_sql.cpp"
    break;

  case 142: /* id_list: id_list COMMA ID  */
#line 1007 "yacc_sql.y"
    {
      (yyval.id_list)->emplace_back((yyvsp[0].string));
      free((yyvsp[0].string));
    }
#line 2901 "yacc_sql.cpp"
    break;

  case 143: /* rel_name: ID  */
#line 1013 "yacc_sql.y"
             { (yyval.string) = (yyvsp[0].string); }
#line 2907 "yacc_sql.cpp"
    break;

  case 144: /* attr_name: ID  */
#line 1021 "yacc_sql.y"
    {
      (yyval.string) = (yyvsp[0].string);
    }
#line 2915 "yacc_sql.cpp"
    break;

  case 145: /* attr_name: '*'  */
#line 1025 "yacc_sql.y"
    {
      // 使用malloc为了和他的free配合
      char *str = (char *)malloc(strlen("*") + 1);  // 加1用于存储字符串结束符'\0'
      strcpy(str, "*");
      (yyval.string) = str;
    }
#line 2926 "yacc_sql.cpp"
    break;


#line 2930 "yacc_sql.cpp"

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

#line 1031 "yacc_sql.y"

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
