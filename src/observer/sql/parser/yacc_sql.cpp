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


#line 116 "yacc_sql.cpp"

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
  YYSYMBOL_ROUND = 62,                     /* ROUND  */
  YYSYMBOL_LENGTH = 63,                    /* LENGTH  */
  YYSYMBOL_DATE_FORMAT = 64,               /* DATE_FORMAT  */
  YYSYMBOL_NUMBER = 65,                    /* NUMBER  */
  YYSYMBOL_FLOAT = 66,                     /* FLOAT  */
  YYSYMBOL_ID = 67,                        /* ID  */
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
  YYSYMBOL_func_node = 103,                /* func_node  */
  YYSYMBOL_func_list = 104,                /* func_list  */
  YYSYMBOL_aggre_node_list_opt = 105,      /* aggre_node_list_opt  */
  YYSYMBOL_aggre_node_list = 106,          /* aggre_node_list  */
  YYSYMBOL_aggre_node = 107,               /* aggre_node  */
  YYSYMBOL_rel_attr_list_opt = 108,        /* rel_attr_list_opt  */
  YYSYMBOL_rel_attr_list = 109,            /* rel_attr_list  */
  YYSYMBOL_rel_attr = 110,                 /* rel_attr  */
  YYSYMBOL_join_node = 111,                /* join_node  */
  YYSYMBOL_select_join_list = 112,         /* select_join_list  */
  YYSYMBOL_join_list = 113,                /* join_list  */
  YYSYMBOL_select_order_list = 114,        /* select_order_list  */
  YYSYMBOL_order_list = 115,               /* order_list  */
  YYSYMBOL_order_node = 116,               /* order_node  */
  YYSYMBOL_order_type = 117,               /* order_type  */
  YYSYMBOL_rel_list = 118,                 /* rel_list  */
  YYSYMBOL_where = 119,                    /* where  */
  YYSYMBOL_condition_list = 120,           /* condition_list  */
  YYSYMBOL_condition = 121,                /* condition  */
  YYSYMBOL_calc_stmt = 122,                /* calc_stmt  */
  YYSYMBOL_expression_list = 123,          /* expression_list  */
  YYSYMBOL_expression = 124,               /* expression  */
  YYSYMBOL_comp_op = 125,                  /* comp_op  */
  YYSYMBOL_aggre_type = 126,               /* aggre_type  */
  YYSYMBOL_load_data_stmt = 127,           /* load_data_stmt  */
  YYSYMBOL_explain_stmt = 128,             /* explain_stmt  */
  YYSYMBOL_set_variable_stmt = 129,        /* set_variable_stmt  */
  YYSYMBOL_opt_semicolon = 130,            /* opt_semicolon  */
  YYSYMBOL_id_list = 131,                  /* id_list  */
  YYSYMBOL_rel_name = 132,                 /* rel_name  */
  YYSYMBOL_attr_name = 133                 /* attr_name  */
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
#define YYFINAL  77
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   285

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  74
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  60
/* YYNRULES -- Number of rules.  */
#define YYNRULES  143
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  268

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
       0,   231,   231,   239,   240,   241,   242,   243,   244,   245,
     246,   247,   248,   249,   250,   251,   252,   253,   254,   255,
     256,   257,   258,   259,   263,   269,   274,   280,   286,   292,
     298,   305,   311,   319,   332,   349,   358,   368,   387,   390,
     403,   412,   425,   428,   432,   439,   442,   443,   444,   445,
     448,   458,   463,   472,   477,   486,   490,   494,   499,   505,
     517,   534,   543,   554,   586,   597,   607,   618,   629,   637,
     646,   658,   663,   672,   677,   683,   688,   696,   708,   713,
     719,   724,   732,   737,   751,   761,   764,   774,   779,   788,
     791,   802,   807,   819,   827,   828,   829,   838,   841,   846,
     855,   858,   864,   867,   872,   879,   891,   903,   915,   931,
     941,   946,   957,   960,   963,   966,   969,   973,   976,   984,
     985,   986,   987,   988,   989,   990,   991,   992,   993,   997,
     998,   999,  1000,  1001,  1006,  1019,  1027,  1037,  1038,  1043,
    1048,  1055,  1062,  1066
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
  "NE", "SUM", "COUNT", "AVG", "MIN", "MAX", "IS_", "NOT", "LK", "ROUND",
  "LENGTH", "DATE_FORMAT", "NUMBER", "FLOAT", "ID", "SSS", "'+'", "'-'",
  "'*'", "'/'", "UMINUS", "$accept", "commands", "command_wrapper",
  "exit_stmt", "help_stmt", "sync_stmt", "begin_stmt", "commit_stmt",
  "rollback_stmt", "drop_table_stmt", "show_tables_stmt",
  "desc_table_stmt", "create_index_stmt", "show_index_stmt",
  "drop_index_stmt", "create_table_stmt", "attr_def_list", "attr_def",
  "nullable", "number", "type", "insert_stmt", "value_list_list",
  "value_list", "value", "delete_stmt", "update_stmt", "update_list",
  "select_stmt", "func_node", "func_list", "aggre_node_list_opt",
  "aggre_node_list", "aggre_node", "rel_attr_list_opt", "rel_attr_list",
  "rel_attr", "join_node", "select_join_list", "join_list",
  "select_order_list", "order_list", "order_node", "order_type",
  "rel_list", "where", "condition_list", "condition", "calc_stmt",
  "expression_list", "expression", "comp_op", "aggre_type",
  "load_data_stmt", "explain_stmt", "set_variable_stmt", "opt_semicolon",
  "id_list", "rel_name", "attr_name", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-202)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-142)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     158,    30,    26,    87,   -50,   -58,    33,  -202,   -21,   -20,
      -6,  -202,  -202,  -202,  -202,  -202,     6,    55,   158,   115,
      84,  -202,  -202,  -202,  -202,  -202,  -202,  -202,  -202,  -202,
    -202,  -202,  -202,  -202,  -202,  -202,  -202,  -202,  -202,  -202,
    -202,  -202,    36,    60,   121,    67,    89,    87,  -202,  -202,
    -202,  -202,    87,  -202,  -202,    61,   131,   151,   160,   108,
    -202,  -202,   156,    85,   157,  -202,   152,  -202,  -202,  -202,
     150,   120,   123,   149,   147,   155,  -202,  -202,  -202,  -202,
     171,   153,   130,  -202,   161,     0,  -202,    87,    87,    87,
      87,    87,    -3,    -3,    -3,   103,  -202,  -202,  -202,  -202,
    -202,   164,   181,  -202,   190,   -49,   -40,   154,   176,   175,
     162,    -8,   163,   165,   166,   173,   167,  -202,  -202,    35,
      35,  -202,  -202,   192,    66,   198,     5,   199,    77,  -202,
     168,    85,   -49,  -202,  -202,  -202,  -202,   200,    93,  -202,
     177,   -14,  -202,   189,    92,   202,   205,   169,  -202,    87,
      87,  -202,   170,    87,    87,  -202,    -2,  -202,  -202,   206,
      -8,   213,   159,   159,  -202,   201,    -8,   172,  -202,   234,
    -202,  -202,  -202,  -202,   -18,   165,   217,   178,   220,     9,
      13,  -202,    27,    42,   231,   168,  -202,   175,   235,  -202,
      94,  -202,   223,  -202,  -202,  -202,  -202,  -202,  -202,   188,
     193,  -202,    93,    93,    93,  -202,   203,   182,   185,  -202,
     222,  -202,   202,  -202,  -202,   126,   178,  -202,   186,  -202,
     191,   168,  -202,   242,  -202,  -202,    -8,    -8,  -202,  -202,
    -202,  -202,  -202,  -202,  -202,    -8,  -202,  -202,   233,  -202,
    -202,  -202,   194,   146,  -202,  -202,   216,   244,  -202,  -202,
     148,  -202,   -25,  -202,  -202,    93,   -49,  -202,  -202,  -202,
      38,   238,  -202,  -202,  -202,  -202,   -49,  -202
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,    79,     0,     0,    26,     0,     0,
       0,    27,    28,    29,    25,    24,     0,     0,     0,     0,
     137,    23,    22,    15,    16,    17,    18,     9,    10,    11,
      12,    14,    13,     8,     5,     7,     6,     4,     3,    19,
      20,    21,     0,     0,     0,     0,     0,     0,    58,    55,
      56,    57,     0,   118,   109,   110,     0,     0,     0,   142,
     143,    71,    64,    74,    78,    80,     0,    82,    32,    31,
       0,     0,     0,     0,     0,     0,   135,     1,   138,     2,
       0,     0,     0,    30,     0,     0,   117,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   129,   131,   130,   133,
     132,     0,    73,    75,     0,     0,     0,     0,     0,   100,
       0,     0,     0,     0,     0,     0,     0,   116,   111,   112,
     113,   114,   115,     0,     0,     0,     0,     0,     0,    72,
      97,     0,     0,    81,   142,    83,    35,     0,   102,    59,
       0,   100,   136,     0,     0,    38,     0,     0,    36,     0,
       0,    68,     0,     0,     0,   141,    85,    98,    76,     0,
       0,    50,     0,     0,   101,   103,     0,     0,    60,     0,
      46,    47,    48,    49,    42,     0,     0,     0,     0,     0,
       0,    65,     0,     0,     0,     0,    87,   100,    86,    77,
       0,    53,     0,   119,   120,   121,   122,   123,   124,   127,
       0,   125,     0,     0,   102,    61,     0,     0,     0,    44,
       0,    41,    38,    37,   139,     0,     0,    69,     0,    70,
       0,     0,    99,    89,    88,    51,     0,     0,   128,   126,
     106,   108,   105,   107,   104,     0,   134,    45,     0,    43,
      39,    33,     0,     0,    66,    67,     0,     0,    63,    54,
       0,    62,    42,   140,    34,   102,     0,    52,    40,    84,
      94,    90,    91,    95,    96,    93,     0,    92
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -202,  -202,   246,  -202,  -202,  -202,  -202,  -202,  -202,  -202,
    -202,  -202,  -202,  -202,  -202,  -202,    53,    91,    15,  -202,
    -202,  -202,  -202,    41,  -110,  -202,  -202,  -202,  -202,   174,
    -202,  -202,  -202,   139,  -202,  -202,    -4,    83,  -202,  -202,
    -202,  -202,     7,  -202,  -202,  -135,  -201,  -202,  -202,   187,
     -45,   109,  -202,  -202,  -202,  -202,  -202,    59,  -126,   179
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,   176,   145,   211,   238,
     174,    34,   161,   190,    53,    35,    36,   141,    37,    61,
      62,   101,   102,   103,    63,    64,   163,   186,   187,   188,
     248,   261,   262,   265,   156,   139,   164,   165,    38,    54,
      55,   202,   104,    39,    40,    41,    79,   215,    66,    67
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      65,   142,    85,   234,   157,   208,   168,    86,   209,    68,
     184,   167,    56,    57,    58,   209,    71,    59,    59,    72,
      47,    60,    60,   185,   117,    48,   138,   134,   162,   152,
      48,    60,    45,   217,    46,   210,    42,   218,    43,    44,
      69,    70,   210,   119,   120,   121,   122,   124,   126,   128,
     191,   219,   223,   263,   259,   264,   205,    49,    50,   222,
      51,    73,    49,    50,    59,    51,   220,    52,    60,    88,
      89,    90,    91,    74,    88,    89,    90,    91,    88,    89,
      90,    91,    88,    89,    90,    91,    87,    78,   123,   125,
     127,   150,   230,   232,   162,   246,    88,    89,    90,    91,
      75,   133,   154,    80,   179,   180,    90,    91,   182,   183,
      47,    88,    89,    90,    91,    77,   249,   191,   225,   226,
      48,   170,   171,   172,   173,   251,    48,    81,   159,    82,
      88,    89,    90,    91,    83,    88,    89,    90,    91,    96,
      97,    98,    99,   100,  -141,   162,    88,    89,    90,    91,
     241,   242,    49,    50,    92,    51,    84,    52,    49,    50,
      59,    51,     1,     2,    60,    56,    57,    58,     3,     4,
     254,   242,   257,   226,    93,     5,     6,     7,     8,     9,
      10,    95,   105,    94,    11,    12,    13,   108,   106,   107,
     109,   110,    14,    15,   113,   111,   114,   115,   231,   233,
      16,   112,    17,   130,   116,    18,   131,   193,   194,   195,
     196,   197,   198,   132,   137,   138,   147,   149,   199,   200,
     201,   136,   151,   160,   153,   166,   169,   175,   177,   140,
     189,   143,   144,   146,   148,   155,   178,   181,   192,   206,
     207,   213,   204,   216,   221,   214,   227,   184,   228,   236,
     237,   235,   260,   244,   229,   239,   247,   252,   245,   255,
     256,   253,   260,   266,    76,   240,   212,   258,   250,   129,
     158,   224,   203,   267,   118,   243,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   135
};

static const yytype_int16 yycheck[] =
{
       4,   111,    47,   204,   130,    23,   141,    52,    33,    67,
      12,    25,    62,    63,    64,    33,    37,    67,    67,    39,
      23,    71,    71,    25,    24,    33,    40,    67,   138,    24,
      33,    71,     6,    24,     8,    60,     6,    24,     8,     9,
       7,     8,    60,    88,    89,    90,    91,    92,    93,    94,
     160,    24,   187,    15,   255,    17,   166,    65,    66,   185,
      68,    67,    65,    66,    67,    68,    24,    70,    71,    69,
      70,    71,    72,    67,    69,    70,    71,    72,    69,    70,
      71,    72,    69,    70,    71,    72,    25,     3,    92,    93,
      94,    25,   202,   203,   204,   221,    69,    70,    71,    72,
      45,   105,    25,    67,   149,   150,    71,    72,   153,   154,
      23,    69,    70,    71,    72,     0,   226,   227,    24,    25,
      33,    29,    30,    31,    32,   235,    33,    67,   132,     8,
      69,    70,    71,    72,    67,    69,    70,    71,    72,    54,
      55,    56,    57,    58,    36,   255,    69,    70,    71,    72,
      24,    25,    65,    66,    23,    68,    67,    70,    65,    66,
      67,    68,     4,     5,    71,    62,    63,    64,    10,    11,
      24,    25,    24,    25,    23,    17,    18,    19,    20,    21,
      22,    25,    25,    23,    26,    27,    28,    67,    36,    39,
      67,    42,    34,    35,    23,    48,    43,    67,   202,   203,
      42,    46,    44,    39,    43,    47,    25,    48,    49,    50,
      51,    52,    53,    23,    38,    40,    43,    25,    59,    60,
      61,    67,    24,    23,    25,    48,    37,    25,    23,    67,
      24,    68,    67,    67,    67,    67,    67,    67,    25,    67,
       6,    24,    41,    23,    13,    67,    23,    12,    60,    67,
      65,    48,   256,    67,    61,    33,    14,    24,    67,    43,
      16,    67,   266,    25,    18,   212,   175,   252,   227,    95,
     131,   188,   163,   266,    87,   216,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   106
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     4,     5,    10,    11,    17,    18,    19,    20,    21,
      22,    26,    27,    28,    34,    35,    42,    44,    47,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    95,    99,   100,   102,   122,   127,
     128,   129,     6,     8,     9,     6,     8,    23,    33,    65,
      66,    68,    70,    98,   123,   124,    62,    63,    64,    67,
      71,   103,   104,   108,   109,   110,   132,   133,    67,     7,
       8,    37,    39,    67,    67,    45,    76,     0,     3,   130,
      67,    67,     8,    67,    67,   124,   124,    25,    69,    70,
      71,    72,    23,    23,    23,    25,    54,    55,    56,    57,
      58,   105,   106,   107,   126,    25,    36,    39,    67,    67,
      42,    48,    46,    23,    43,    67,    43,    24,   123,   124,
     124,   124,   124,   110,   124,   110,   124,   110,   124,   103,
      39,    25,    23,   110,    67,   133,    67,    38,    40,   119,
      67,   101,    98,    68,    67,    91,    67,    43,    67,    25,
      25,    24,    24,    25,    25,    67,   118,   132,   107,   110,
      23,    96,    98,   110,   120,   121,    48,    25,   119,    37,
      29,    30,    31,    32,    94,    25,    90,    23,    67,   124,
     124,    67,   124,   124,    12,    25,   111,   112,   113,    24,
      97,    98,    25,    48,    49,    50,    51,    52,    53,    59,
      60,    61,   125,   125,    41,    98,    67,     6,    23,    33,
      60,    92,    91,    24,    67,   131,    23,    24,    24,    24,
      24,    13,   132,   119,   111,    24,    25,    23,    60,    61,
      98,   110,    98,   110,   120,    48,    67,    65,    93,    33,
      90,    24,    25,   131,    67,    67,   132,    14,   114,    98,
      97,    98,    24,    67,    24,    43,    16,    24,    92,   120,
     110,   115,   116,    15,    17,   117,    25,   116
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
     100,   101,   101,   102,   102,   103,   103,   103,   103,   103,
     103,   104,   104,   105,   105,   106,   106,   107,   108,   108,
     109,   109,   110,   110,   111,   112,   112,   113,   113,   114,
     114,   115,   115,   116,   117,   117,   117,   118,   118,   118,
     119,   119,   120,   120,   120,   121,   121,   121,   121,   122,
     123,   123,   124,   124,   124,   124,   124,   124,   124,   125,
     125,   125,   125,   125,   125,   125,   125,   125,   125,   126,
     126,   126,   126,   126,   127,   128,   129,   130,   130,   131,
     131,   132,   133,   133
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
       5,     3,     5,     8,     2,     5,     7,     7,     4,     6,
       6,     1,     3,     1,     0,     1,     3,     4,     1,     0,
       1,     3,     1,     3,     5,     0,     1,     1,     2,     0,
       3,     1,     3,     2,     0,     1,     1,     0,     1,     3,
       0,     2,     0,     1,     3,     3,     3,     3,     3,     2,
       1,     3,     3,     3,     3,     3,     3,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     2,     1,     2,     1,
       1,     1,     1,     1,     7,     2,     4,     0,     1,     1,
       3,     1,     1,     1
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
#line 232 "yacc_sql.y"
  {
    std::unique_ptr<ParsedSqlNode> sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[-1].sql_node));
    sql_result->add_sql_node(std::move(sql_node));
  }
#line 1841 "yacc_sql.cpp"
    break;

  case 24: /* exit_stmt: EXIT  */
#line 263 "yacc_sql.y"
         {
      (void)yynerrs;  // 这么写为了消除yynerrs未使用的告警。如果你有更好的方法欢迎提PR
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXIT);
    }
#line 1850 "yacc_sql.cpp"
    break;

  case 25: /* help_stmt: HELP  */
#line 269 "yacc_sql.y"
         {
      (yyval.sql_node) = new ParsedSqlNode(SCF_HELP);
    }
#line 1858 "yacc_sql.cpp"
    break;

  case 26: /* sync_stmt: SYNC  */
#line 274 "yacc_sql.y"
         {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SYNC);
    }
#line 1866 "yacc_sql.cpp"
    break;

  case 27: /* begin_stmt: TRX_BEGIN  */
#line 280 "yacc_sql.y"
               {
      (yyval.sql_node) = new ParsedSqlNode(SCF_BEGIN);
    }
#line 1874 "yacc_sql.cpp"
    break;

  case 28: /* commit_stmt: TRX_COMMIT  */
#line 286 "yacc_sql.y"
               {
      (yyval.sql_node) = new ParsedSqlNode(SCF_COMMIT);
    }
#line 1882 "yacc_sql.cpp"
    break;

  case 29: /* rollback_stmt: TRX_ROLLBACK  */
#line 292 "yacc_sql.y"
                  {
      (yyval.sql_node) = new ParsedSqlNode(SCF_ROLLBACK);
    }
#line 1890 "yacc_sql.cpp"
    break;

  case 30: /* drop_table_stmt: DROP TABLE ID  */
#line 298 "yacc_sql.y"
                  {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_TABLE);
      (yyval.sql_node)->drop_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 1900 "yacc_sql.cpp"
    break;

  case 31: /* show_tables_stmt: SHOW TABLES  */
#line 305 "yacc_sql.y"
                {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SHOW_TABLES);
    }
#line 1908 "yacc_sql.cpp"
    break;

  case 32: /* desc_table_stmt: DESC ID  */
#line 311 "yacc_sql.y"
             {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DESC_TABLE);
      (yyval.sql_node)->desc_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 1918 "yacc_sql.cpp"
    break;

  case 33: /* create_index_stmt: CREATE INDEX ID ON ID LBRACE id_list RBRACE  */
#line 320 "yacc_sql.y"
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
#line 1935 "yacc_sql.cpp"
    break;

  case 34: /* create_index_stmt: CREATE UNIQUE INDEX ID ON ID LBRACE id_list RBRACE  */
#line 333 "yacc_sql.y"
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
#line 1953 "yacc_sql.cpp"
    break;

  case 35: /* show_index_stmt: SHOW INDEX FROM ID  */
#line 350 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SHOW_INDEX);
      (yyval.sql_node)->show_index.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 1963 "yacc_sql.cpp"
    break;

  case 36: /* drop_index_stmt: DROP INDEX ID ON ID  */
#line 359 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_INDEX);
      (yyval.sql_node)->drop_index.index_name = (yyvsp[-2].string);
      (yyval.sql_node)->drop_index.relation_name = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 1975 "yacc_sql.cpp"
    break;

  case 37: /* create_table_stmt: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE  */
#line 369 "yacc_sql.y"
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
#line 1995 "yacc_sql.cpp"
    break;

  case 38: /* attr_def_list: %empty  */
#line 387 "yacc_sql.y"
    {
      (yyval.attr_infos) = nullptr;
    }
#line 2003 "yacc_sql.cpp"
    break;

  case 39: /* attr_def_list: COMMA attr_def attr_def_list  */
#line 391 "yacc_sql.y"
    {
      if ((yyvsp[0].attr_infos) != nullptr) {
        (yyval.attr_infos) = (yyvsp[0].attr_infos);
      } else {
        (yyval.attr_infos) = new std::vector<AttrInfoSqlNode>;
      }
      (yyval.attr_infos)->emplace_back(*(yyvsp[-1].attr_info));
      delete (yyvsp[-1].attr_info);
    }
#line 2017 "yacc_sql.cpp"
    break;

  case 40: /* attr_def: ID type LBRACE number RBRACE nullable  */
#line 404 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-4].number);
      (yyval.attr_info)->name = (yyvsp[-5].string);
      (yyval.attr_info)->length = (yyvsp[-2].number);
      (yyval.attr_info)->nullable = (yyvsp[0].nullable);
      free((yyvsp[-5].string));
    }
#line 2030 "yacc_sql.cpp"
    break;

  case 41: /* attr_def: ID type nullable  */
#line 413 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-1].number);
      (yyval.attr_info)->name = (yyvsp[-2].string);
      (yyval.attr_info)->length = 4;
      (yyval.attr_info)->nullable = (yyvsp[0].nullable);
      free((yyvsp[-2].string));
    }
#line 2043 "yacc_sql.cpp"
    break;

  case 42: /* nullable: %empty  */
#line 425 "yacc_sql.y"
    {
      (yyval.nullable) = true; // 字段默认是可以为null的
    }
#line 2051 "yacc_sql.cpp"
    break;

  case 43: /* nullable: NOT NULL_T  */
#line 429 "yacc_sql.y"
    {
      (yyval.nullable) = false;
    }
#line 2059 "yacc_sql.cpp"
    break;

  case 44: /* nullable: NULL_T  */
#line 433 "yacc_sql.y"
    {
      (yyval.nullable) = true;
    }
#line 2067 "yacc_sql.cpp"
    break;

  case 45: /* number: NUMBER  */
#line 439 "yacc_sql.y"
           {(yyval.number) = (yyvsp[0].number);}
#line 2073 "yacc_sql.cpp"
    break;

  case 46: /* type: INT_T  */
#line 442 "yacc_sql.y"
               { (yyval.number)=INTS; }
#line 2079 "yacc_sql.cpp"
    break;

  case 47: /* type: STRING_T  */
#line 443 "yacc_sql.y"
               { (yyval.number)=CHARS; }
#line 2085 "yacc_sql.cpp"
    break;

  case 48: /* type: FLOAT_T  */
#line 444 "yacc_sql.y"
               { (yyval.number)=FLOATS; }
#line 2091 "yacc_sql.cpp"
    break;

  case 49: /* type: DATE_T  */
#line 445 "yacc_sql.y"
               { (yyval.number)=DATES;}
#line 2097 "yacc_sql.cpp"
    break;

  case 50: /* insert_stmt: INSERT INTO ID VALUES value_list_list  */
#line 449 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_INSERT);
      (yyval.sql_node)->insertion.relation_name = (yyvsp[-2].string);
      (yyval.sql_node)->insertion.values_list = *(yyvsp[0].value_list_list);
      free((yyvsp[-2].string));
    }
#line 2108 "yacc_sql.cpp"
    break;

  case 51: /* value_list_list: LBRACE value_list RBRACE  */
#line 459 "yacc_sql.y"
    {
      (yyval.value_list_list) = new std::vector<std::vector<Value>>{*(yyvsp[-1].value_list)};
      delete (yyvsp[-1].value_list);
    }
#line 2117 "yacc_sql.cpp"
    break;

  case 52: /* value_list_list: value_list_list COMMA LBRACE value_list RBRACE  */
#line 464 "yacc_sql.y"
    {
      (yyval.value_list_list)->emplace_back(*(yyvsp[-1].value_list));
      delete (yyvsp[-1].value_list);
    }
#line 2126 "yacc_sql.cpp"
    break;

  case 53: /* value_list: value  */
#line 473 "yacc_sql.y"
  {
    (yyval.value_list) = new std::vector<Value>{*(yyvsp[0].value)};
    delete (yyvsp[0].value); /* relese the pointer*/
  }
#line 2135 "yacc_sql.cpp"
    break;

  case 54: /* value_list: value_list COMMA value  */
#line 478 "yacc_sql.y"
  {
    (yyval.value_list)->emplace_back(*(yyvsp[0].value));
    delete (yyvsp[0].value);
  }
#line 2144 "yacc_sql.cpp"
    break;

  case 55: /* value: NUMBER  */
#line 486 "yacc_sql.y"
           {
      (yyval.value) = new Value((int)(yyvsp[0].number));
      (yyloc) = (yylsp[0]);
    }
#line 2153 "yacc_sql.cpp"
    break;

  case 56: /* value: FLOAT  */
#line 490 "yacc_sql.y"
           {
      (yyval.value) = new Value((float)(yyvsp[0].floats));
      (yyloc) = (yylsp[0]);
    }
#line 2162 "yacc_sql.cpp"
    break;

  case 57: /* value: SSS  */
#line 494 "yacc_sql.y"
         {
      char *tmp = common::substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
      (yyval.value) = new Value(tmp);
      free(tmp);
    }
#line 2172 "yacc_sql.cpp"
    break;

  case 58: /* value: NULL_T  */
#line 499 "yacc_sql.y"
             {
      (yyval.value) = new Value();
    }
#line 2180 "yacc_sql.cpp"
    break;

  case 59: /* delete_stmt: DELETE FROM ID where  */
#line 506 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DELETE);
      (yyval.sql_node)->deletion.relation_name = (yyvsp[-1].string);
      if ((yyvsp[0].condition_list) != nullptr) {
        (yyval.sql_node)->deletion.conditions.swap(*(yyvsp[0].condition_list));
        delete (yyvsp[0].condition_list);
      }
      free((yyvsp[-1].string));
    }
#line 2194 "yacc_sql.cpp"
    break;

  case 60: /* update_stmt: UPDATE ID SET update_list where  */
#line 518 "yacc_sql.y"
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
#line 2212 "yacc_sql.cpp"
    break;

  case 61: /* update_list: ID EQ value  */
#line 535 "yacc_sql.y"
    {
      (yyval.update_list) = new std::pair<std::vector<std::string>, std::vector<Value>>;
      (yyval.update_list)->first.emplace_back((yyvsp[-2].string));
      (yyval.update_list)->second.emplace_back(*(yyvsp[0].value));

      delete (yyvsp[-2].string);
      delete (yyvsp[0].value);
    }
#line 2225 "yacc_sql.cpp"
    break;

  case 62: /* update_list: update_list COMMA ID EQ value  */
#line 544 "yacc_sql.y"
    {
      (yyval.update_list) = (yyvsp[-4].update_list);
      (yyval.update_list)->first.emplace_back((yyvsp[-2].string));
      (yyval.update_list)->second.emplace_back(*(yyvsp[0].value));
      delete (yyvsp[-2].string);
      delete (yyvsp[0].value);
    }
#line 2237 "yacc_sql.cpp"
    break;

  case 63: /* select_stmt: SELECT rel_attr_list_opt aggre_node_list_opt FROM rel_list select_join_list where select_order_list  */
#line 555 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SELECT);
      if ((yyvsp[-6].rel_attr_list) != nullptr) {
        (yyval.sql_node)->selection.attributes.swap(*(yyvsp[-6].rel_attr_list));
        delete (yyvsp[-6].rel_attr_list);
      }
      if ((yyvsp[-5].aggre_node_list) != nullptr) {
        (yyval.sql_node)->selection.aggregations.swap(*(yyvsp[-5].aggre_node_list));
        delete (yyvsp[-5].aggre_node_list);
      }
      // if ($4 != nullptr) {
      //   $$->selection.functions.swap(*$4);
      //   delete $4;
      // }
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
#line 2273 "yacc_sql.cpp"
    break;

  case 64: /* select_stmt: SELECT func_list  */
#line 587 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SELECT);
      if ((yyvsp[0].func_list) != nullptr) {
        (yyval.sql_node)->selection.functions.swap(*(yyvsp[0].func_list));
        delete (yyvsp[0].func_list);
      }
    }
#line 2285 "yacc_sql.cpp"
    break;

  case 65: /* func_node: LENGTH LBRACE expression RBRACE ID  */
#line 598 "yacc_sql.y"
    {
      (yyval.func_node) = new FunctionNode;
      (yyval.func_node)->f_type = FuncType::LENGTH_;
      (yyval.func_node)->left = (yyvsp[-2].expression);
      if ((yyvsp[0].string) != nullptr) {
        (yyval.func_node)->res_name = (yyvsp[0].string);
        delete (yyvsp[0].string);
      }
    }
#line 2299 "yacc_sql.cpp"
    break;

  case 66: /* func_node: ROUND LBRACE expression COMMA expression RBRACE ID  */
#line 608 "yacc_sql.y"
    {
      (yyval.func_node) = new FunctionNode;
      (yyval.func_node)->f_type = FuncType::ROUND_;
      (yyval.func_node)->left = (yyvsp[-4].expression);
      (yyval.func_node)->right = (yyvsp[-2].expression);
      if ((yyvsp[0].string) != nullptr) {
        (yyval.func_node)->res_name = (yyvsp[0].string);
        delete (yyvsp[0].string);
      }
    }
#line 2314 "yacc_sql.cpp"
    break;

  case 67: /* func_node: DATE_FORMAT LBRACE expression COMMA expression RBRACE ID  */
#line 619 "yacc_sql.y"
    {
      (yyval.func_node) = new FunctionNode;
      (yyval.func_node)->f_type = FuncType::DATE_FORMAT_;
      (yyval.func_node)->left = (yyvsp[-4].expression);
      (yyval.func_node)->right = (yyvsp[-2].expression);
      if ((yyvsp[0].string) != nullptr) {
        (yyval.func_node)->res_name = (yyvsp[0].string);
        delete (yyvsp[0].string);
      }
    }
#line 2329 "yacc_sql.cpp"
    break;

  case 68: /* func_node: LENGTH LBRACE rel_attr RBRACE  */
#line 630 "yacc_sql.y"
    {
      (yyval.func_node) = new FunctionNode;
      (yyval.func_node)->res_name = token_name(sql_string,&(yyloc));
      (yyval.func_node)->f_type = FuncType::LENGTH_;
      (yyval.func_node)->rel_attr = *(yyvsp[-1].rel_attr);
      delete (yyvsp[-1].rel_attr);
    }
#line 2341 "yacc_sql.cpp"
    break;

  case 69: /* func_node: ROUND LBRACE rel_attr COMMA expression RBRACE  */
#line 638 "yacc_sql.y"
    {
      (yyval.func_node) = new FunctionNode;
      (yyval.func_node)->res_name = token_name(sql_string,&(yyloc));
      (yyval.func_node)->f_type = FuncType::ROUND_;
      (yyval.func_node)->rel_attr = *(yyvsp[-3].rel_attr);
      (yyval.func_node)->right = (yyvsp[-1].expression);
      delete (yyvsp[-3].rel_attr);
    }
#line 2354 "yacc_sql.cpp"
    break;

  case 70: /* func_node: DATE_FORMAT LBRACE rel_attr COMMA expression RBRACE  */
#line 647 "yacc_sql.y"
    {
      (yyval.func_node) = new FunctionNode;
      (yyval.func_node)->res_name = token_name(sql_string,&(yyloc));
      (yyval.func_node)->f_type = FuncType::DATE_FORMAT_;
      (yyval.func_node)->rel_attr = *(yyvsp[-3].rel_attr);
      (yyval.func_node)->right = (yyvsp[-1].expression);
      delete (yyvsp[-3].rel_attr);
    }
#line 2367 "yacc_sql.cpp"
    break;

  case 71: /* func_list: func_node  */
#line 659 "yacc_sql.y"
    {
      (yyval.func_list) = new std::vector<FunctionNode>{*(yyvsp[0].func_node)};
      delete (yyvsp[0].func_node);
    }
#line 2376 "yacc_sql.cpp"
    break;

  case 72: /* func_list: func_list COMMA func_node  */
#line 664 "yacc_sql.y"
    {
      (yyval.func_list)->emplace_back(*(yyvsp[0].func_node));
      delete (yyvsp[0].func_node);
    }
#line 2385 "yacc_sql.cpp"
    break;

  case 73: /* aggre_node_list_opt: aggre_node_list  */
#line 673 "yacc_sql.y"
    {
      (yyval.aggre_node_list) = (yyvsp[0].aggre_node_list);
    }
#line 2393 "yacc_sql.cpp"
    break;

  case 74: /* aggre_node_list_opt: %empty  */
#line 677 "yacc_sql.y"
    {
      (yyval.aggre_node_list) = nullptr;
    }
#line 2401 "yacc_sql.cpp"
    break;

  case 75: /* aggre_node_list: aggre_node  */
#line 684 "yacc_sql.y"
    {
      (yyval.aggre_node_list) = new std::vector<AggreSqlNode>{*(yyvsp[0].aggre_node)}; 
      delete (yyvsp[0].aggre_node); 
    }
#line 2410 "yacc_sql.cpp"
    break;

  case 76: /* aggre_node_list: aggre_node_list COMMA aggre_node  */
#line 689 "yacc_sql.y"
    {
      (yyval.aggre_node_list)->emplace_back(*(yyvsp[0].aggre_node)); 
      delete (yyvsp[0].aggre_node); 
    }
#line 2419 "yacc_sql.cpp"
    break;

  case 77: /* aggre_node: aggre_type LBRACE rel_attr RBRACE  */
#line 697 "yacc_sql.y"
    {
      (yyval.aggre_node) = new AggreSqlNode;
      (yyval.aggre_node)->aggre_type = (yyvsp[-3].aggre_type); 
      if ((yyvsp[-1].rel_attr) != nullptr) {
        (yyval.aggre_node)->attribute_name = *(yyvsp[-1].rel_attr); 
        delete (yyvsp[-1].rel_attr); 
      }
    }
#line 2432 "yacc_sql.cpp"
    break;

  case 78: /* rel_attr_list_opt: rel_attr_list  */
#line 709 "yacc_sql.y"
    {
      (yyval.rel_attr_list) = (yyvsp[0].rel_attr_list); 
    }
#line 2440 "yacc_sql.cpp"
    break;

  case 79: /* rel_attr_list_opt: %empty  */
#line 713 "yacc_sql.y"
    {
      (yyval.rel_attr_list) = nullptr; 
    }
#line 2448 "yacc_sql.cpp"
    break;

  case 80: /* rel_attr_list: rel_attr  */
#line 720 "yacc_sql.y"
    {
      (yyval.rel_attr_list) = new std::vector<RelAttrSqlNode>{*(yyvsp[0].rel_attr)}; 
      delete (yyvsp[0].rel_attr); 
    }
#line 2457 "yacc_sql.cpp"
    break;

  case 81: /* rel_attr_list: rel_attr_list COMMA rel_attr  */
#line 725 "yacc_sql.y"
    {
      (yyval.rel_attr_list)->emplace_back(*(yyvsp[0].rel_attr)); 
      delete (yyvsp[0].rel_attr); 
    }
#line 2466 "yacc_sql.cpp"
    break;

  case 82: /* rel_attr: attr_name  */
#line 733 "yacc_sql.y"
    {
      (yyval.rel_attr) = new RelAttrSqlNode{"", (yyvsp[0].string)};
      free((yyvsp[0].string));
    }
#line 2475 "yacc_sql.cpp"
    break;

  case 83: /* rel_attr: rel_name DOT attr_name  */
#line 738 "yacc_sql.y"
    {
      (yyval.rel_attr) = new RelAttrSqlNode{(yyvsp[-2].string), (yyvsp[0].string)};
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 2485 "yacc_sql.cpp"
    break;

  case 84: /* join_node: INNER JOIN rel_name ON condition_list  */
#line 752 "yacc_sql.y"
    {
      (yyval.join_node) = new JoinSqlNode{(yyvsp[-2].string),*(yyvsp[0].condition_list)};
      delete (yyvsp[-2].string);
      delete (yyvsp[0].condition_list);
    }
#line 2495 "yacc_sql.cpp"
    break;

  case 85: /* select_join_list: %empty  */
#line 761 "yacc_sql.y"
    {
      (yyval.join_list) = nullptr; 
    }
#line 2503 "yacc_sql.cpp"
    break;

  case 86: /* select_join_list: join_list  */
#line 765 "yacc_sql.y"
    {
      (yyval.join_list) = (yyvsp[0].join_list); 
    }
#line 2511 "yacc_sql.cpp"
    break;

  case 87: /* join_list: join_node  */
#line 775 "yacc_sql.y"
    {
      (yyval.join_list) = new std::vector<JoinSqlNode>{*(yyvsp[0].join_node)};
      delete (yyvsp[0].join_node);   
    }
#line 2520 "yacc_sql.cpp"
    break;

  case 88: /* join_list: join_list join_node  */
#line 780 "yacc_sql.y"
    {
      (yyval.join_list)->emplace_back(*(yyvsp[0].join_node));
      delete (yyvsp[0].join_node);
    }
#line 2529 "yacc_sql.cpp"
    break;

  case 89: /* select_order_list: %empty  */
#line 788 "yacc_sql.y"
    {
      (yyval.order_list) = nullptr; // 没有order
    }
#line 2537 "yacc_sql.cpp"
    break;

  case 90: /* select_order_list: ORDER BY order_list  */
#line 792 "yacc_sql.y"
    {
      (yyval.order_list) = (yyvsp[0].order_list);
    }
#line 2545 "yacc_sql.cpp"
    break;

  case 91: /* order_list: order_node  */
#line 803 "yacc_sql.y"
    {
      (yyval.order_list) = new std::vector<OrderSqlNode>{*(yyvsp[0].order_node)};
      delete (yyvsp[0].order_node);
    }
#line 2554 "yacc_sql.cpp"
    break;

  case 92: /* order_list: order_list COMMA order_node  */
#line 808 "yacc_sql.y"
    {
      (yyval.order_list)->emplace_back(*(yyvsp[0].order_node));
      delete (yyvsp[0].order_node);
    }
#line 2563 "yacc_sql.cpp"
    break;

  case 93: /* order_node: rel_attr order_type  */
#line 820 "yacc_sql.y"
    {
      (yyval.order_node) = new OrderSqlNode{*(yyvsp[-1].rel_attr),(yyvsp[0].order_type)};
      delete (yyvsp[-1].rel_attr);
    }
#line 2572 "yacc_sql.cpp"
    break;

  case 94: /* order_type: %empty  */
#line 827 "yacc_sql.y"
           { (yyval.order_type) = ORDER_ASC; }
#line 2578 "yacc_sql.cpp"
    break;

  case 95: /* order_type: ASC  */
#line 828 "yacc_sql.y"
           { (yyval.order_type) = ORDER_ASC; }
#line 2584 "yacc_sql.cpp"
    break;

  case 96: /* order_type: DESC  */
#line 829 "yacc_sql.y"
           { (yyval.order_type) = ORDER_DESC; }
#line 2590 "yacc_sql.cpp"
    break;

  case 97: /* rel_list: %empty  */
#line 838 "yacc_sql.y"
    {
      (yyval.relation_list) = nullptr;
    }
#line 2598 "yacc_sql.cpp"
    break;

  case 98: /* rel_list: rel_name  */
#line 842 "yacc_sql.y"
    {
      (yyval.relation_list) = new std::vector<std::string>{(yyvsp[0].string)};
      free((yyvsp[0].string)); 
    }
#line 2607 "yacc_sql.cpp"
    break;

  case 99: /* rel_list: rel_list COMMA rel_name  */
#line 847 "yacc_sql.y"
    {
      (yyval.relation_list)->emplace_back((yyvsp[0].string)); 
      free((yyvsp[0].string));
    }
#line 2616 "yacc_sql.cpp"
    break;

  case 100: /* where: %empty  */
#line 855 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 2624 "yacc_sql.cpp"
    break;

  case 101: /* where: WHERE condition_list  */
#line 858 "yacc_sql.y"
                           {
      (yyval.condition_list) = (yyvsp[0].condition_list);
    }
#line 2632 "yacc_sql.cpp"
    break;

  case 102: /* condition_list: %empty  */
#line 864 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 2640 "yacc_sql.cpp"
    break;

  case 103: /* condition_list: condition  */
#line 867 "yacc_sql.y"
                {
      (yyval.condition_list) = new std::vector<ConditionSqlNode>;
      (yyval.condition_list)->emplace_back(*(yyvsp[0].condition));
      delete (yyvsp[0].condition);
    }
#line 2650 "yacc_sql.cpp"
    break;

  case 104: /* condition_list: condition AND condition_list  */
#line 872 "yacc_sql.y"
                                   {
      (yyval.condition_list) = (yyvsp[0].condition_list);
      (yyval.condition_list)->emplace_back(*(yyvsp[-2].condition));
      delete (yyvsp[-2].condition);
    }
#line 2660 "yacc_sql.cpp"
    break;

  case 105: /* condition: rel_attr comp_op value  */
#line 880 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_attr = 1;
      (yyval.condition)->left_attr = *(yyvsp[-2].rel_attr);
      (yyval.condition)->right_is_attr = 0;
      (yyval.condition)->right_value = *(yyvsp[0].value);
      (yyval.condition)->comp = (yyvsp[-1].comp);

      delete (yyvsp[-2].rel_attr);
      delete (yyvsp[0].value);
    }
#line 2676 "yacc_sql.cpp"
    break;

  case 106: /* condition: value comp_op value  */
#line 892 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_attr = 0;
      (yyval.condition)->left_value = *(yyvsp[-2].value);
      (yyval.condition)->right_is_attr = 0;
      (yyval.condition)->right_value = *(yyvsp[0].value);
      (yyval.condition)->comp = (yyvsp[-1].comp);

      delete (yyvsp[-2].value);
      delete (yyvsp[0].value);
    }
#line 2692 "yacc_sql.cpp"
    break;

  case 107: /* condition: rel_attr comp_op rel_attr  */
#line 904 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_attr = 1;
      (yyval.condition)->left_attr = *(yyvsp[-2].rel_attr);
      (yyval.condition)->right_is_attr = 1;
      (yyval.condition)->right_attr = *(yyvsp[0].rel_attr);
      (yyval.condition)->comp = (yyvsp[-1].comp);

      delete (yyvsp[-2].rel_attr);
      delete (yyvsp[0].rel_attr);
    }
#line 2708 "yacc_sql.cpp"
    break;

  case 108: /* condition: value comp_op rel_attr  */
#line 916 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_attr = 0;
      (yyval.condition)->left_value = *(yyvsp[-2].value);
      (yyval.condition)->right_is_attr = 1;
      (yyval.condition)->right_attr = *(yyvsp[0].rel_attr);
      (yyval.condition)->comp = (yyvsp[-1].comp);

      delete (yyvsp[-2].value);
      delete (yyvsp[0].rel_attr);
    }
#line 2724 "yacc_sql.cpp"
    break;

  case 109: /* calc_stmt: CALC expression_list  */
#line 932 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CALC);
      std::reverse((yyvsp[0].expression_list)->begin(), (yyvsp[0].expression_list)->end());
      (yyval.sql_node)->calc.expressions.swap(*(yyvsp[0].expression_list));
      delete (yyvsp[0].expression_list);
    }
#line 2735 "yacc_sql.cpp"
    break;

  case 110: /* expression_list: expression  */
#line 942 "yacc_sql.y"
    {
      (yyval.expression_list) = new std::vector<Expression*>;
      (yyval.expression_list)->emplace_back((yyvsp[0].expression));
    }
#line 2744 "yacc_sql.cpp"
    break;

  case 111: /* expression_list: expression COMMA expression_list  */
#line 947 "yacc_sql.y"
    {
      if ((yyvsp[0].expression_list) != nullptr) {
        (yyval.expression_list) = (yyvsp[0].expression_list);
      } else {
        (yyval.expression_list) = new std::vector<Expression *>;
      }
      (yyval.expression_list)->emplace_back((yyvsp[-2].expression));
    }
#line 2757 "yacc_sql.cpp"
    break;

  case 112: /* expression: expression '+' expression  */
#line 957 "yacc_sql.y"
                              {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::ADD, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2765 "yacc_sql.cpp"
    break;

  case 113: /* expression: expression '-' expression  */
#line 960 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::SUB, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2773 "yacc_sql.cpp"
    break;

  case 114: /* expression: expression '*' expression  */
#line 963 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::MUL, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2781 "yacc_sql.cpp"
    break;

  case 115: /* expression: expression '/' expression  */
#line 966 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::DIV, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2789 "yacc_sql.cpp"
    break;

  case 116: /* expression: LBRACE expression RBRACE  */
#line 969 "yacc_sql.y"
                               {
      (yyval.expression) = (yyvsp[-1].expression);
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
    }
#line 2798 "yacc_sql.cpp"
    break;

  case 117: /* expression: '-' expression  */
#line 973 "yacc_sql.y"
                                  {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::NEGATIVE, (yyvsp[0].expression), nullptr, sql_string, &(yyloc));
    }
#line 2806 "yacc_sql.cpp"
    break;

  case 118: /* expression: value  */
#line 976 "yacc_sql.y"
            {
      (yyval.expression) = new ValueExpr(*(yyvsp[0].value));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[0].value);
    }
#line 2816 "yacc_sql.cpp"
    break;

  case 119: /* comp_op: EQ  */
#line 984 "yacc_sql.y"
         { (yyval.comp) = EQUAL_TO; }
#line 2822 "yacc_sql.cpp"
    break;

  case 120: /* comp_op: LT  */
#line 985 "yacc_sql.y"
         { (yyval.comp) = LESS_THAN; }
#line 2828 "yacc_sql.cpp"
    break;

  case 121: /* comp_op: GT  */
#line 986 "yacc_sql.y"
         { (yyval.comp) = GREAT_THAN; }
#line 2834 "yacc_sql.cpp"
    break;

  case 122: /* comp_op: LE  */
#line 987 "yacc_sql.y"
         { (yyval.comp) = LESS_EQUAL; }
#line 2840 "yacc_sql.cpp"
    break;

  case 123: /* comp_op: GE  */
#line 988 "yacc_sql.y"
         { (yyval.comp) = GREAT_EQUAL; }
#line 2846 "yacc_sql.cpp"
    break;

  case 124: /* comp_op: NE  */
#line 989 "yacc_sql.y"
         { (yyval.comp) = NOT_EQUAL; }
#line 2852 "yacc_sql.cpp"
    break;

  case 125: /* comp_op: LK  */
#line 990 "yacc_sql.y"
         { (yyval.comp) = LIKE; }
#line 2858 "yacc_sql.cpp"
    break;

  case 126: /* comp_op: NOT LK  */
#line 991 "yacc_sql.y"
             { (yyval.comp) = NOT_LIKE;}
#line 2864 "yacc_sql.cpp"
    break;

  case 127: /* comp_op: IS_  */
#line 992 "yacc_sql.y"
          { (yyval.comp) = IS;}
#line 2870 "yacc_sql.cpp"
    break;

  case 128: /* comp_op: IS_ NOT  */
#line 993 "yacc_sql.y"
              { (yyval.comp) = IS_NOT;}
#line 2876 "yacc_sql.cpp"
    break;

  case 129: /* aggre_type: SUM  */
#line 997 "yacc_sql.y"
            { (yyval.aggre_type) = AGGRE_SUM; }
#line 2882 "yacc_sql.cpp"
    break;

  case 130: /* aggre_type: AVG  */
#line 998 "yacc_sql.y"
            { (yyval.aggre_type) = AGGRE_AVG; }
#line 2888 "yacc_sql.cpp"
    break;

  case 131: /* aggre_type: COUNT  */
#line 999 "yacc_sql.y"
            { (yyval.aggre_type) = AGGRE_COUNT; }
#line 2894 "yacc_sql.cpp"
    break;

  case 132: /* aggre_type: MAX  */
#line 1000 "yacc_sql.y"
            { (yyval.aggre_type) = AGGRE_MAX; }
#line 2900 "yacc_sql.cpp"
    break;

  case 133: /* aggre_type: MIN  */
#line 1001 "yacc_sql.y"
            { (yyval.aggre_type) = AGGRE_MIN; }
#line 2906 "yacc_sql.cpp"
    break;

  case 134: /* load_data_stmt: LOAD DATA INFILE SSS INTO TABLE ID  */
#line 1007 "yacc_sql.y"
    {
      char *tmp_file_name = common::substr((yyvsp[-3].string), 1, strlen((yyvsp[-3].string)) - 2);
      
      (yyval.sql_node) = new ParsedSqlNode(SCF_LOAD_DATA);
      (yyval.sql_node)->load_data.relation_name = (yyvsp[0].string);
      (yyval.sql_node)->load_data.file_name = tmp_file_name;
      free((yyvsp[0].string));
      free(tmp_file_name);
    }
#line 2920 "yacc_sql.cpp"
    break;

  case 135: /* explain_stmt: EXPLAIN command_wrapper  */
#line 1020 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXPLAIN);
      (yyval.sql_node)->explain.sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[0].sql_node));
    }
#line 2929 "yacc_sql.cpp"
    break;

  case 136: /* set_variable_stmt: SET ID EQ value  */
#line 1028 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SET_VARIABLE);
      (yyval.sql_node)->set_variable.name  = (yyvsp[-2].string);
      (yyval.sql_node)->set_variable.value = *(yyvsp[0].value);
      free((yyvsp[-2].string));
      delete (yyvsp[0].value);
    }
#line 2941 "yacc_sql.cpp"
    break;

  case 139: /* id_list: ID  */
#line 1044 "yacc_sql.y"
    {
      (yyval.id_list) = new std::vector<std::string>{(yyvsp[0].string)}; 
      free((yyvsp[0].string)); 
    }
#line 2950 "yacc_sql.cpp"
    break;

  case 140: /* id_list: id_list COMMA ID  */
#line 1049 "yacc_sql.y"
    {
      (yyval.id_list)->emplace_back((yyvsp[0].string));
      free((yyvsp[0].string));
    }
#line 2959 "yacc_sql.cpp"
    break;

  case 141: /* rel_name: ID  */
#line 1055 "yacc_sql.y"
             { (yyval.string) = (yyvsp[0].string); }
#line 2965 "yacc_sql.cpp"
    break;

  case 142: /* attr_name: ID  */
#line 1063 "yacc_sql.y"
    {
      (yyval.string) = (yyvsp[0].string);
    }
#line 2973 "yacc_sql.cpp"
    break;

  case 143: /* attr_name: '*'  */
#line 1067 "yacc_sql.y"
    {
      // 使用malloc为了和他的free配合
      char *str = (char *)malloc(strlen("*") + 1);  // 加1用于存储字符串结束符'\0'
      strcpy(str, "*");
      (yyval.string) = str;
    }
#line 2984 "yacc_sql.cpp"
    break;


#line 2988 "yacc_sql.cpp"

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

#line 1073 "yacc_sql.y"

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
