/* A Bison parser, made by GNU Bison 3.7.6.  */

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
#define YYBISON 30706

/* Bison version string.  */
#define YYBISON_VERSION "3.7.6"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "vsopc.y"

    #include <iostream>
    #include <vector>
    #include <set>
    #include <cstring>

    #include "AbstractSyntaxTree.hpp"

    #define YYERROR_VERBOSE 1

    const std::string PROGRAM_USAGE = "Program usage: ./vsopc -l <SOURCE-FILE> or ./vsopc -p <SOURCE-FILE>";

    extern FILE *yyin;
    std::string fileName;
    Program *abstractSyntaxTree;

    int yylex();

    void yyerror(const std::string message);
    void lexicalError(const std::string& message);
    void syntaxError(const std::string& message);

#line 94 "vsopc.tab.c"

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

#include "vsopc.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_AND = 3,                        /* "and"  */
  YYSYMBOL_BOOL = 4,                       /* "bool"  */
  YYSYMBOL_CLASS = 5,                      /* "class"  */
  YYSYMBOL_DO = 6,                         /* "do"  */
  YYSYMBOL_ELSE = 7,                       /* "else"  */
  YYSYMBOL_EXTENDS = 8,                    /* "extends"  */
  YYSYMBOL_FALSE = 9,                      /* "false"  */
  YYSYMBOL_IF = 10,                        /* "if"  */
  YYSYMBOL_IN = 11,                        /* "in"  */
  YYSYMBOL_INT32 = 12,                     /* "int32"  */
  YYSYMBOL_ISNULL = 13,                    /* "isnull"  */
  YYSYMBOL_LET = 14,                       /* "let"  */
  YYSYMBOL_NEW = 15,                       /* "new"  */
  YYSYMBOL_NOT = 16,                       /* "not"  */
  YYSYMBOL_SELF = 17,                      /* "self"  */
  YYSYMBOL_STRING = 18,                    /* "string"  */
  YYSYMBOL_THEN = 19,                      /* "then"  */
  YYSYMBOL_TRUE = 20,                      /* "true"  */
  YYSYMBOL_UNIT = 21,                      /* "unit"  */
  YYSYMBOL_WHILE = 22,                     /* "while"  */
  YYSYMBOL_LBRACE = 23,                    /* "{"  */
  YYSYMBOL_RBRACE = 24,                    /* "}"  */
  YYSYMBOL_LPAR = 25,                      /* "("  */
  YYSYMBOL_RPAR = 26,                      /* ")"  */
  YYSYMBOL_COLON = 27,                     /* ":"  */
  YYSYMBOL_SEMICOLON = 28,                 /* ";"  */
  YYSYMBOL_COMMA = 29,                     /* ","  */
  YYSYMBOL_PLUS = 30,                      /* "+"  */
  YYSYMBOL_MINUS = 31,                     /* "-"  */
  YYSYMBOL_TIMES = 32,                     /* "*"  */
  YYSYMBOL_DIV = 33,                       /* "/"  */
  YYSYMBOL_POW = 34,                       /* "^"  */
  YYSYMBOL_DOT = 35,                       /* "."  */
  YYSYMBOL_EQUAL = 36,                     /* "="  */
  YYSYMBOL_LOWER = 37,                     /* "<"  */
  YYSYMBOL_LOWER_EQUAL = 38,               /* "<="  */
  YYSYMBOL_ASSIGN = 39,                    /* "<-"  */
  YYSYMBOL_INVALID_HEX_NUMBER = 40,        /* INVALID_HEX_NUMBER  */
  YYSYMBOL_INVALID_CHAR = 41,              /* INVALID_CHAR  */
  YYSYMBOL_INVALID_EOF_STRING = 42,        /* INVALID_EOF_STRING  */
  YYSYMBOL_INVALID_EOF_COMMENT = 43,       /* INVALID_EOF_COMMENT  */
  YYSYMBOL_INVALID_INTEGER_LITERAL = 44,   /* INVALID_INTEGER_LITERAL  */
  YYSYMBOL_INTEGER_LITERAL = 45,           /* INTEGER_LITERAL  */
  YYSYMBOL_TYPE_IDENTIFIER = 46,           /* TYPE_IDENTIFIER  */
  YYSYMBOL_OBJECT_IDENTIFIER = 47,         /* OBJECT_IDENTIFIER  */
  YYSYMBOL_STRING_LITERAL = 48,            /* STRING_LITERAL  */
  YYSYMBOL_UNARYMINUS = 49,                /* UNARYMINUS  */
  YYSYMBOL_EMBEDDED = 50,                  /* EMBEDDED  */
  YYSYMBOL_YYACCEPT = 51,                  /* $accept  */
  YYSYMBOL_Program = 52,                   /* Program  */
  YYSYMBOL_ProgramContinued = 53,          /* ProgramContinued  */
  YYSYMBOL_Class = 54,                     /* Class  */
  YYSYMBOL_ClassBody = 55,                 /* ClassBody  */
  YYSYMBOL_Field = 56,                     /* Field  */
  YYSYMBOL_Method = 57,                    /* Method  */
  YYSYMBOL_Type = 58,                      /* Type  */
  YYSYMBOL_Formals = 59,                   /* Formals  */
  YYSYMBOL_FormalsContinued = 60,          /* FormalsContinued  */
  YYSYMBOL_Formal = 61,                    /* Formal  */
  YYSYMBOL_Block = 62,                     /* Block  */
  YYSYMBOL_BlockExpr = 63,                 /* BlockExpr  */
  YYSYMBOL_Expr = 64,                      /* Expr  */
  YYSYMBOL_If = 65,                        /* If  */
  YYSYMBOL_While = 66,                     /* While  */
  YYSYMBOL_Let = 67,                       /* Let  */
  YYSYMBOL_Args = 68,                      /* Args  */
  YYSYMBOL_ArgsExprList = 69,              /* ArgsExprList  */
  YYSYMBOL_Literal = 70,                   /* Literal  */
  YYSYMBOL_InvalidToken = 71               /* InvalidToken  */
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

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
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
# define YYCOPY_NEEDED 1
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
#define YYFINAL  5
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   288

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  51
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  21
/* YYNRULES -- Number of rules.  */
#define YYNRULES  69
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  136

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   305


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
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,   126,   126,   130,   131,   134,   137,   142,   143,   145,
     149,   150,   153,   156,   157,   158,   159,   160,   163,   164,
     168,   169,   173,   176,   180,   181,   185,   186,   187,   188,
     189,   190,   191,   192,   193,   194,   195,   196,   197,   198,
     199,   200,   201,   202,   203,   204,   205,   206,   207,   208,
     209,   210,   213,   214,   217,   220,   221,   224,   225,   228,
     229,   233,   234,   235,   236,   239,   241,   243,   245,   247
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if 1
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  static const char *const yy_sname[] =
  {
  "end of file", "error", "invalid token", "and", "bool", "class", "do",
  "else", "extends", "false", "if", "in", "int32", "isnull", "let", "new",
  "not", "self", "string", "then", "true", "unit", "while", "{", "}", "(",
  ")", ":", ";", ",", "+", "-", "*", "/", "^", ".", "=", "<", "<=", "<-",
  "INVALID_HEX_NUMBER", "INVALID_CHAR", "INVALID_EOF_STRING",
  "INVALID_EOF_COMMENT", "INVALID_INTEGER_LITERAL", "INTEGER_LITERAL",
  "TYPE_IDENTIFIER", "OBJECT_IDENTIFIER", "STRING_LITERAL", "UNARYMINUS",
  "EMBEDDED", "$accept", "Program", "ProgramContinued", "Class",
  "ClassBody", "Field", "Method", "Type", "Formals", "FormalsContinued",
  "Formal", "Block", "BlockExpr", "Expr", "If", "While", "Let", "Args",
  "ArgsExprList", "Literal", "InvalidToken", YY_NULLPTR
  };
  return yy_sname[yysymbol];
}
#endif

#ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305
};
#endif

#define YYPACT_NINF (-39)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  ((Yyn) == YYTABLE_NINF)

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      -1,   -30,    26,    -1,    -6,   -39,   -39,    -1,    -7,     9,
     -39,    23,    -2,     5,     9,     9,     9,    11,     6,   -39,
     -39,   -39,    37,    35,    39,    34,   -39,   -39,   -39,   -39,
     -39,   -17,   -39,     6,    42,    11,   -39,   -39,    97,   -39,
       6,    34,   -39,    97,    97,    28,    30,    97,   -39,   -39,
      97,    97,    57,    97,   -39,   -39,   -39,   -39,   -39,   -39,
     -18,   -39,   -39,     0,   -39,   -39,   -39,   -39,   -39,    55,
     -39,   124,   -15,    62,   -39,   134,   143,   160,   -39,   179,
     -15,    97,    97,    97,   -39,    97,    97,    97,    97,    97,
      47,    97,    97,    97,   -39,    97,     6,    97,    97,    60,
     -39,   196,    69,   241,   134,    58,    58,   -15,   -15,   -15,
      78,   250,   250,   250,   215,    29,   241,   160,   -39,    97,
     -39,   -39,    97,    97,    97,    97,   -39,   196,    82,   241,
     241,   232,   -39,   -39,    97,   241
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     3,     0,     1,     2,     3,     0,     7,
       4,     0,     0,     0,     7,     7,     7,    18,     0,     5,
       8,     9,     0,     0,     0,    20,    15,    14,    16,    17,
      13,     0,     6,     0,     0,     0,    19,    10,     0,    22,
       0,    20,    64,     0,     0,     0,     0,     0,    46,    63,
       0,     0,     0,     0,    66,    65,    68,    69,    67,    61,
      45,    62,    50,     0,    26,    27,    28,    47,    51,     0,
      21,     0,    41,     0,    44,    30,     0,    24,    48,     0,
      40,    57,     0,     0,    11,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    12,     0,     0,     0,     0,     0,
      49,    59,     0,    29,    31,    36,    35,    38,    37,    39,
       0,    34,    33,    32,    52,     0,    54,    24,    23,     0,
      58,    42,    57,     0,     0,     0,    25,    59,     0,    53,
      55,     0,    60,    43,     0,    56
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -39,   -39,   102,   115,    27,   -39,   -39,   -32,   -39,    75,
      83,    52,     7,   -38,   -39,   -39,   -39,     1,     2,   -39,
     -39
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     2,     6,     7,    13,    14,    15,    31,    24,    36,
      25,    62,    99,   101,    64,    65,    66,   102,   120,    67,
      68
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      63,    39,     8,    83,     1,    71,    72,    81,    69,    75,
      26,    37,    76,    77,    79,    80,     4,     9,    27,    89,
      90,    82,    38,    17,    28,    18,     5,    29,    84,    19,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    11,
     124,    20,    21,    22,   103,   104,    16,   105,   106,   107,
     108,   109,    30,   111,   112,   113,    12,   114,    23,   116,
     117,    32,    33,    35,   115,    34,    42,    43,   125,    40,
      44,    45,    46,    47,    48,    73,    74,    49,    51,    50,
      51,   127,    52,    78,   118,   129,   130,   131,    53,    96,
      87,    88,    89,    90,   110,   121,   135,    54,    55,    56,
      57,    58,    59,   122,    60,    61,    42,    43,   133,    10,
      44,    45,    46,    47,    48,     3,    70,    49,    41,    50,
      51,    94,    52,   128,   126,     0,     0,    83,    53,   132,
       0,     0,     0,     0,     0,     0,     0,    54,    55,    56,
      57,    58,    59,    95,    60,    61,    83,     0,     0,    97,
       0,     0,     0,     0,    85,    86,    87,    88,    89,    90,
      91,    92,    93,    83,    85,    86,    87,    88,    89,    90,
      91,    92,    93,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    83,     0,     0,     0,     0,     0,    98,     0,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    83,
       0,     0,     0,     0,     0,   100,     0,     0,     0,    85,
      86,    87,    88,    89,    90,    91,    92,    93,    83,     0,
       0,     0,   123,     0,     0,   119,    85,    86,    87,    88,
      89,    90,    91,    92,    93,    83,     0,     0,     0,     0,
       0,     0,     0,   134,    83,    85,    86,    87,    88,    89,
      90,    91,    92,    93,     0,     0,     0,     0,     0,     0,
       0,     0,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      85,    86,    87,    88,    89,    90,    -1,    -1,    -1
};

static const yytype_int16 yycheck[] =
{
      38,    33,     8,     3,     5,    43,    44,    25,    40,    47,
       4,    28,    50,    51,    52,    53,    46,    23,    12,    34,
      35,    39,    39,    25,    18,    27,     0,    21,    28,    24,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    46,
      11,    14,    15,    16,    82,    83,    23,    85,    86,    87,
      88,    89,    46,    91,    92,    93,    47,    95,    47,    97,
      98,    24,    27,    29,    96,    26,     9,    10,    39,    27,
      13,    14,    15,    16,    17,    47,    46,    20,    23,    22,
      23,   119,    25,    26,    24,   123,   124,   125,    31,    27,
      32,    33,    34,    35,    47,    26,   134,    40,    41,    42,
      43,    44,    45,    25,    47,    48,     9,    10,    26,     7,
      13,    14,    15,    16,    17,     0,    41,    20,    35,    22,
      23,    69,    25,   122,   117,    -1,    -1,     3,    31,   127,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    40,    41,    42,
      43,    44,    45,    19,    47,    48,     3,    -1,    -1,     6,
      -1,    -1,    -1,    -1,    30,    31,    32,    33,    34,    35,
      36,    37,    38,     3,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    30,    31,    32,    33,    34,    35,    36,
      37,    38,     3,    -1,    -1,    -1,    -1,    -1,    28,    -1,
      30,    31,    32,    33,    34,    35,    36,    37,    38,     3,
      -1,    -1,    -1,    -1,    -1,    26,    -1,    -1,    -1,    30,
      31,    32,    33,    34,    35,    36,    37,    38,     3,    -1,
      -1,    -1,     7,    -1,    -1,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,     3,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    11,     3,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      30,    31,    32,    33,    34,    35,    36,    37,    38
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     5,    52,    54,    46,     0,    53,    54,     8,    23,
      53,    46,    47,    55,    56,    57,    23,    25,    27,    24,
      55,    55,    55,    47,    59,    61,     4,    12,    18,    21,
      46,    58,    24,    27,    26,    29,    60,    28,    39,    58,
      27,    61,     9,    10,    13,    14,    15,    16,    17,    20,
      22,    23,    25,    31,    40,    41,    42,    43,    44,    45,
      47,    48,    62,    64,    65,    66,    67,    70,    71,    58,
      60,    64,    64,    47,    46,    64,    64,    64,    26,    64,
      64,    25,    39,     3,    28,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    62,    19,    27,     6,    28,    63,
      26,    64,    68,    64,    64,    64,    64,    64,    64,    64,
      47,    64,    64,    64,    64,    58,    64,    64,    24,    29,
      69,    26,    25,     7,    11,    39,    63,    64,    68,    64,
      64,    64,    69,    26,    11,    64
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    51,    52,    53,    53,    54,    54,    55,    55,    55,
      56,    56,    57,    58,    58,    58,    58,    58,    59,    59,
      60,    60,    61,    62,    63,    63,    64,    64,    64,    64,
      64,    64,    64,    64,    64,    64,    64,    64,    64,    64,
      64,    64,    64,    64,    64,    64,    64,    64,    64,    64,
      64,    64,    65,    65,    66,    67,    67,    68,    68,    69,
      69,    70,    70,    70,    70,    71,    71,    71,    71,    71
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     0,     2,     5,     7,     0,     2,     2,
       4,     6,     7,     1,     1,     1,     1,     1,     0,     2,
       0,     3,     3,     4,     0,     3,     1,     1,     1,     3,
       2,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       2,     2,     4,     6,     2,     1,     1,     1,     2,     3,
       1,     1,     4,     6,     4,     6,     8,     0,     2,     0,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        YY_LAC_DISCARD ("YYBACKUP");                              \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
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


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

# ifndef YY_LOCATION_PRINT
#  if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

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

#   define YY_LOCATION_PRINT(File, Loc)          \
  yy_location_print_ (File, &(Loc))

#  else
#   define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#  endif
# endif /* !defined YY_LOCATION_PRINT */


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value, Location); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  YY_USE (yylocationp);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yykind < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yykind], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  YY_LOCATION_PRINT (yyo, *yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yykind, yyvaluep, yylocationp);
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
                 int yyrule)
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
                       &(yylsp[(yyi + 1) - (yynrhs)]));
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule); \
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


/* Given a state stack such that *YYBOTTOM is its bottom, such that
   *YYTOP is either its top or is YYTOP_EMPTY to indicate an empty
   stack, and such that *YYCAPACITY is the maximum number of elements it
   can hold without a reallocation, make sure there is enough room to
   store YYADD more elements.  If not, allocate a new stack using
   YYSTACK_ALLOC, copy the existing elements, and adjust *YYBOTTOM,
   *YYTOP, and *YYCAPACITY to reflect the new capacity and memory
   location.  If *YYBOTTOM != YYBOTTOM_NO_FREE, then free the old stack
   using YYSTACK_FREE.  Return 0 if successful or if no reallocation is
   required.  Return YYENOMEM if memory is exhausted.  */
static int
yy_lac_stack_realloc (YYPTRDIFF_T *yycapacity, YYPTRDIFF_T yyadd,
#if YYDEBUG
                      char const *yydebug_prefix,
                      char const *yydebug_suffix,
#endif
                      yy_state_t **yybottom,
                      yy_state_t *yybottom_no_free,
                      yy_state_t **yytop, yy_state_t *yytop_empty)
{
  YYPTRDIFF_T yysize_old =
    *yytop == yytop_empty ? 0 : *yytop - *yybottom + 1;
  YYPTRDIFF_T yysize_new = yysize_old + yyadd;
  if (*yycapacity < yysize_new)
    {
      YYPTRDIFF_T yyalloc = 2 * yysize_new;
      yy_state_t *yybottom_new;
      /* Use YYMAXDEPTH for maximum stack size given that the stack
         should never need to grow larger than the main state stack
         needs to grow without LAC.  */
      if (YYMAXDEPTH < yysize_new)
        {
          YYDPRINTF ((stderr, "%smax size exceeded%s", yydebug_prefix,
                      yydebug_suffix));
          return YYENOMEM;
        }
      if (YYMAXDEPTH < yyalloc)
        yyalloc = YYMAXDEPTH;
      yybottom_new =
        YY_CAST (yy_state_t *,
                 YYSTACK_ALLOC (YY_CAST (YYSIZE_T,
                                         yyalloc * YYSIZEOF (*yybottom_new))));
      if (!yybottom_new)
        {
          YYDPRINTF ((stderr, "%srealloc failed%s", yydebug_prefix,
                      yydebug_suffix));
          return YYENOMEM;
        }
      if (*yytop != yytop_empty)
        {
          YYCOPY (yybottom_new, *yybottom, yysize_old);
          *yytop = yybottom_new + (yysize_old - 1);
        }
      if (*yybottom != yybottom_no_free)
        YYSTACK_FREE (*yybottom);
      *yybottom = yybottom_new;
      *yycapacity = yyalloc;
    }
  return 0;
}

/* Establish the initial context for the current lookahead if no initial
   context is currently established.

   We define a context as a snapshot of the parser stacks.  We define
   the initial context for a lookahead as the context in which the
   parser initially examines that lookahead in order to select a
   syntactic action.  Thus, if the lookahead eventually proves
   syntactically unacceptable (possibly in a later context reached via a
   series of reductions), the initial context can be used to determine
   the exact set of tokens that would be syntactically acceptable in the
   lookahead's place.  Moreover, it is the context after which any
   further semantic actions would be erroneous because they would be
   determined by a syntactically unacceptable token.

   YY_LAC_ESTABLISH should be invoked when a reduction is about to be
   performed in an inconsistent state (which, for the purposes of LAC,
   includes consistent states that don't know they're consistent because
   their default reductions have been disabled).  Iff there is a
   lookahead token, it should also be invoked before reporting a syntax
   error.  This latter case is for the sake of the debugging output.

   For parse.lac=full, the implementation of YY_LAC_ESTABLISH is as
   follows.  If no initial context is currently established for the
   current lookahead, then check if that lookahead can eventually be
   shifted if syntactic actions continue from the current context.
   Report a syntax error if it cannot.  */
#define YY_LAC_ESTABLISH                                                \
do {                                                                    \
  if (!yy_lac_established)                                              \
    {                                                                   \
      YYDPRINTF ((stderr,                                               \
                  "LAC: initial context established for %s\n",          \
                  yysymbol_name (yytoken)));                            \
      yy_lac_established = 1;                                           \
      switch (yy_lac (yyesa, &yyes, &yyes_capacity, yyssp, yytoken))    \
        {                                                               \
        case YYENOMEM:                                                  \
          goto yyexhaustedlab;                                          \
        case 1:                                                         \
          goto yyerrlab;                                                \
        }                                                               \
    }                                                                   \
} while (0)

/* Discard any previous initial lookahead context because of Event,
   which may be a lookahead change or an invalidation of the currently
   established initial context for the current lookahead.

   The most common example of a lookahead change is a shift.  An example
   of both cases is syntax error recovery.  That is, a syntax error
   occurs when the lookahead is syntactically erroneous for the
   currently established initial context, so error recovery manipulates
   the parser stacks to try to find a new initial context in which the
   current lookahead is syntactically acceptable.  If it fails to find
   such a context, it discards the lookahead.  */
#if YYDEBUG
# define YY_LAC_DISCARD(Event)                                           \
do {                                                                     \
  if (yy_lac_established)                                                \
    {                                                                    \
      YYDPRINTF ((stderr, "LAC: initial context discarded due to "       \
                  Event "\n"));                                          \
      yy_lac_established = 0;                                            \
    }                                                                    \
} while (0)
#else
# define YY_LAC_DISCARD(Event) yy_lac_established = 0
#endif

/* Given the stack whose top is *YYSSP, return 0 iff YYTOKEN can
   eventually (after perhaps some reductions) be shifted, return 1 if
   not, or return YYENOMEM if memory is exhausted.  As preconditions and
   postconditions: *YYES_CAPACITY is the allocated size of the array to
   which *YYES points, and either *YYES = YYESA or *YYES points to an
   array allocated with YYSTACK_ALLOC.  yy_lac may overwrite the
   contents of either array, alter *YYES and *YYES_CAPACITY, and free
   any old *YYES other than YYESA.  */
static int
yy_lac (yy_state_t *yyesa, yy_state_t **yyes,
        YYPTRDIFF_T *yyes_capacity, yy_state_t *yyssp, yysymbol_kind_t yytoken)
{
  yy_state_t *yyes_prev = yyssp;
  yy_state_t *yyesp = yyes_prev;
  /* Reduce until we encounter a shift and thereby accept the token.  */
  YYDPRINTF ((stderr, "LAC: checking lookahead %s:", yysymbol_name (yytoken)));
  if (yytoken == YYSYMBOL_YYUNDEF)
    {
      YYDPRINTF ((stderr, " Always Err\n"));
      return 1;
    }
  while (1)
    {
      int yyrule = yypact[+*yyesp];
      if (yypact_value_is_default (yyrule)
          || (yyrule += yytoken) < 0 || YYLAST < yyrule
          || yycheck[yyrule] != yytoken)
        {
          /* Use the default action.  */
          yyrule = yydefact[+*yyesp];
          if (yyrule == 0)
            {
              YYDPRINTF ((stderr, " Err\n"));
              return 1;
            }
        }
      else
        {
          /* Use the action from yytable.  */
          yyrule = yytable[yyrule];
          if (yytable_value_is_error (yyrule))
            {
              YYDPRINTF ((stderr, " Err\n"));
              return 1;
            }
          if (0 < yyrule)
            {
              YYDPRINTF ((stderr, " S%d\n", yyrule));
              return 0;
            }
          yyrule = -yyrule;
        }
      /* By now we know we have to simulate a reduce.  */
      YYDPRINTF ((stderr, " R%d", yyrule - 1));
      {
        /* Pop the corresponding number of values from the stack.  */
        YYPTRDIFF_T yylen = yyr2[yyrule];
        /* First pop from the LAC stack as many tokens as possible.  */
        if (yyesp != yyes_prev)
          {
            YYPTRDIFF_T yysize = yyesp - *yyes + 1;
            if (yylen < yysize)
              {
                yyesp -= yylen;
                yylen = 0;
              }
            else
              {
                yyesp = yyes_prev;
                yylen -= yysize;
              }
          }
        /* Only afterwards look at the main stack.  */
        if (yylen)
          yyesp = yyes_prev -= yylen;
      }
      /* Push the resulting state of the reduction.  */
      {
        yy_state_fast_t yystate;
        {
          const int yylhs = yyr1[yyrule] - YYNTOKENS;
          const int yyi = yypgoto[yylhs] + *yyesp;
          yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyesp
                     ? yytable[yyi]
                     : yydefgoto[yylhs]);
        }
        if (yyesp == yyes_prev)
          {
            yyesp = *yyes;
            YY_IGNORE_USELESS_CAST_BEGIN
            *yyesp = YY_CAST (yy_state_t, yystate);
            YY_IGNORE_USELESS_CAST_END
          }
        else
          {
            if (yy_lac_stack_realloc (yyes_capacity, 1,
#if YYDEBUG
                                      " (", ")",
#endif
                                      yyes, yyesa, &yyesp, yyes_prev))
              {
                YYDPRINTF ((stderr, "\n"));
                return YYENOMEM;
              }
            YY_IGNORE_USELESS_CAST_BEGIN
            *++yyesp = YY_CAST (yy_state_t, yystate);
            YY_IGNORE_USELESS_CAST_END
          }
        YYDPRINTF ((stderr, " G%d", yystate));
      }
    }
}

/* Context of a parse error.  */
typedef struct
{
  yy_state_t *yyssp;
  yy_state_t *yyesa;
  yy_state_t **yyes;
  YYPTRDIFF_T *yyes_capacity;
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

  int yyx;
  for (yyx = 0; yyx < YYNTOKENS; ++yyx)
    {
      yysymbol_kind_t yysym = YY_CAST (yysymbol_kind_t, yyx);
      if (yysym != YYSYMBOL_YYerror && yysym != YYSYMBOL_YYUNDEF)
        switch (yy_lac (yyctx->yyesa, yyctx->yyes, yyctx->yyes_capacity, yyctx->yyssp, yysym))
          {
          case YYENOMEM:
            return YYENOMEM;
          case 1:
            continue;
          default:
            if (!yyarg)
              ++yycount;
            else if (yycount == yyargn)
              return 0;
            else
              yyarg[yycount++] = yysym;
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
       In the first two cases, it might appear that the current syntax
       error should have been detected in the previous state when yy_lac
       was invoked.  However, at that time, there might have been a
       different syntax error that discarded a different initial context
       during error recovery, leaving behind the current lookahead.
  */
  if (yyctx->yytoken != YYSYMBOL_YYEMPTY)
    {
      int yyn;
      YYDPRINTF ((stderr, "Constructing syntax error message\n"));
      if (yyarg)
        yyarg[yycount] = yyctx->yytoken;
      ++yycount;
      yyn = yypcontext_expected_tokens (yyctx,
                                        yyarg ? yyarg + 1 : yyarg, yyargn - 1);
      if (yyn == YYENOMEM)
        return YYENOMEM;
      else if (yyn == 0)
        YYDPRINTF ((stderr, "No expected tokens.\n"));
      else
        yycount += yyn;
    }
  return yycount;
}

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.  In order to see if a particular token T is a
   valid looakhead, invoke yy_lac (YYESA, YYES, YYES_CAPACITY, YYSSP, T).

   Return 0 if *YYMSG was successfully written.  Return -1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return YYENOMEM if the
   required number of bytes is too large to store or if
   yy_lac returned YYENOMEM.  */
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
          = yysize + yystrlen (yysymbol_name (yyarg[yyi]));
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
          yyp = yystpcpy (yyp, yysymbol_name (yyarg[yyi++]));
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
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
{
  YY_USE (yyvaluep);
  YY_USE (yylocationp);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Location data for the lookahead symbol.  */
YYLTYPE yylloc
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
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

    yy_state_t yyesa[20];
    yy_state_t *yyes = yyesa;
    YYPTRDIFF_T yyes_capacity = 20 < YYMAXDEPTH ? 20 : YYMAXDEPTH;

  /* Whether LAC context is established.  A Boolean.  */
  int yy_lac_established = 0;
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
    goto yyexhaustedlab;
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
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
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
      yychar = yylex ();
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
    {
      YY_LAC_ESTABLISH;
      goto yydefault;
    }
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      YY_LAC_ESTABLISH;
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
  YY_LAC_DISCARD ("shift");
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
  {
    int yychar_backup = yychar;
    switch (yyn)
      {
  case 2: /* Program: Class ProgramContinued  */
#line 126 "vsopc.y"
                                {(yyvsp[0].program)->addClass((yyvsp[-1].cls)); 
                                 (yyval.program) = (yyvsp[0].program); 
                                 abstractSyntaxTree = (yyval.program);}
#line 1837 "vsopc.tab.c"
    break;

  case 3: /* ProgramContinued: %empty  */
#line 130 "vsopc.y"
                              { (yyval.program) = new Program(); }
#line 1843 "vsopc.tab.c"
    break;

  case 4: /* ProgramContinued: Class ProgramContinued  */
#line 131 "vsopc.y"
                                                         {(yyvsp[0].program)->addClass((yyvsp[-1].cls)); 
                                          (yyval.program) = (yyvsp[0].program);}
#line 1850 "vsopc.tab.c"
    break;

  case 5: /* Class: "class" TYPE_IDENTIFIER "{" ClassBody "}"  */
#line 134 "vsopc.y"
                                                     {std::vector<Field*> fields = (yyvsp[-1].classBody)->getFields();
                                                               std::vector<Method*> methods = (yyvsp[-1].classBody)->getMethods();
                                                               (yyval.cls) = new Class((yyvsp[-3].stringValue), "Object", fields, methods);}
#line 1858 "vsopc.tab.c"
    break;

  case 6: /* Class: "class" TYPE_IDENTIFIER "extends" TYPE_IDENTIFIER "{" ClassBody "}"  */
#line 137 "vsopc.y"
                                                                                {std::vector<Field*> fields = (yyvsp[-1].classBody)->getFields();
                                                                                       std::vector<Method*> methods = (yyvsp[-1].classBody)->getMethods();
                                                                                       (yyval.cls) = new Class((yyvsp[-5].stringValue), (yyvsp[-3].stringValue), fields, methods);}
#line 1866 "vsopc.tab.c"
    break;

  case 7: /* ClassBody: %empty  */
#line 142 "vsopc.y"
                 {(yyval.classBody) = new ClassBody();}
#line 1872 "vsopc.tab.c"
    break;

  case 8: /* ClassBody: Field ClassBody  */
#line 143 "vsopc.y"
                          {(yyvsp[0].classBody)->addField((yyvsp[-1].field));
                                      (yyval.classBody) = (yyvsp[0].classBody);}
#line 1879 "vsopc.tab.c"
    break;

  case 9: /* ClassBody: Method ClassBody  */
#line 145 "vsopc.y"
                           {(yyvsp[0].classBody)->addMethod((yyvsp[-1].method));
                                       (yyval.classBody) = (yyvsp[0].classBody);}
#line 1886 "vsopc.tab.c"
    break;

  case 10: /* Field: OBJECT_IDENTIFIER ":" Type ";"  */
#line 149 "vsopc.y"
                                              {(yyval.field) = new Field((yyvsp[-3].stringValue), (yyvsp[-1].stringValue), NULL);}
#line 1892 "vsopc.tab.c"
    break;

  case 11: /* Field: OBJECT_IDENTIFIER ":" Type "<-" Expr ";"  */
#line 150 "vsopc.y"
                                                             {(yyval.field) = new Field((yyvsp[-5].stringValue), (yyvsp[-3].stringValue), (yyvsp[-1].expression));}
#line 1898 "vsopc.tab.c"
    break;

  case 12: /* Method: OBJECT_IDENTIFIER "(" Formals ")" ":" Type Block  */
#line 153 "vsopc.y"
                                                            {(yyval.method) = new Method((yyvsp[-6].stringValue), (yyvsp[-4].formals), (yyvsp[-1].stringValue), new Block((yyvsp[0].args)));}
#line 1904 "vsopc.tab.c"
    break;

  case 13: /* Type: TYPE_IDENTIFIER  */
#line 156 "vsopc.y"
                      {(yyval.stringValue) = (yyvsp[0].stringValue);}
#line 1910 "vsopc.tab.c"
    break;

  case 14: /* Type: "int32"  */
#line 157 "vsopc.y"
                      {(yyval.stringValue) = (char *) "int32";}
#line 1916 "vsopc.tab.c"
    break;

  case 15: /* Type: "bool"  */
#line 158 "vsopc.y"
                      {(yyval.stringValue) = (char *) "bool";}
#line 1922 "vsopc.tab.c"
    break;

  case 16: /* Type: "string"  */
#line 159 "vsopc.y"
                      {(yyval.stringValue) = (char *) "string";}
#line 1928 "vsopc.tab.c"
    break;

  case 17: /* Type: "unit"  */
#line 160 "vsopc.y"
                      {(yyval.stringValue) = (char *) "unit";}
#line 1934 "vsopc.tab.c"
    break;

  case 18: /* Formals: %empty  */
#line 163 "vsopc.y"
               {(yyval.formals) = new Formals();}
#line 1940 "vsopc.tab.c"
    break;

  case 19: /* Formals: Formal FormalsContinued  */
#line 164 "vsopc.y"
                                  {(yyvsp[0].formals)->addFormal((yyvsp[-1].formal));
                                   (yyval.formals) = (yyvsp[0].formals);}
#line 1947 "vsopc.tab.c"
    break;

  case 20: /* FormalsContinued: %empty  */
#line 168 "vsopc.y"
                        {(yyval.formals) = new Formals();}
#line 1953 "vsopc.tab.c"
    break;

  case 21: /* FormalsContinued: "," Formal FormalsContinued  */
#line 169 "vsopc.y"
                                                 {(yyvsp[0].formals)->addFormal((yyvsp[-1].formal));
                                                  (yyval.formals) = (yyvsp[0].formals);}
#line 1960 "vsopc.tab.c"
    break;

  case 22: /* Formal: OBJECT_IDENTIFIER ":" Type  */
#line 173 "vsopc.y"
                                     {(yyval.formal) = new Formal((yyvsp[-2].stringValue), (yyvsp[0].stringValue));}
#line 1966 "vsopc.tab.c"
    break;

  case 23: /* Block: "{" Expr BlockExpr "}"  */
#line 176 "vsopc.y"
                                    {(yyvsp[-1].args)->addExpr((yyvsp[-2].expression));
                                     (yyval.args) = (yyvsp[-1].args);}
#line 1973 "vsopc.tab.c"
    break;

  case 24: /* BlockExpr: %empty  */
#line 180 "vsopc.y"
                 {(yyval.args) = new Args();}
#line 1979 "vsopc.tab.c"
    break;

  case 25: /* BlockExpr: ";" Expr BlockExpr  */
#line 181 "vsopc.y"
                                   {(yyvsp[0].args)->addExpr((yyvsp[-1].expression));
                                    (yyval.args) = (yyvsp[0].args);}
#line 1986 "vsopc.tab.c"
    break;

  case 29: /* Expr: OBJECT_IDENTIFIER "<-" Expr  */
#line 188 "vsopc.y"
                                        {(yyval.expression) = new Assign((yyvsp[-2].stringValue), (yyvsp[0].expression));}
#line 1992 "vsopc.tab.c"
    break;

  case 30: /* Expr: "not" Expr  */
#line 189 "vsopc.y"
                   {(yyval.expression) = new Not((yyvsp[0].expression));}
#line 1998 "vsopc.tab.c"
    break;

  case 31: /* Expr: Expr "and" Expr  */
#line 190 "vsopc.y"
                        {(yyval.expression) = new And((yyvsp[-2].expression), (yyvsp[0].expression));}
#line 2004 "vsopc.tab.c"
    break;

  case 32: /* Expr: Expr "<=" Expr  */
#line 191 "vsopc.y"
                                {(yyval.expression) = new LowerEqual((yyvsp[-2].expression), (yyvsp[0].expression));}
#line 2010 "vsopc.tab.c"
    break;

  case 33: /* Expr: Expr "<" Expr  */
#line 192 "vsopc.y"
                          {(yyval.expression) = new Lower((yyvsp[-2].expression), (yyvsp[0].expression));}
#line 2016 "vsopc.tab.c"
    break;

  case 34: /* Expr: Expr "=" Expr  */
#line 193 "vsopc.y"
                          {(yyval.expression) = new Equal((yyvsp[-2].expression), (yyvsp[0].expression));}
#line 2022 "vsopc.tab.c"
    break;

  case 35: /* Expr: Expr "-" Expr  */
#line 194 "vsopc.y"
                          {(yyval.expression) = new Minus((yyvsp[-2].expression), (yyvsp[0].expression));}
#line 2028 "vsopc.tab.c"
    break;

  case 36: /* Expr: Expr "+" Expr  */
#line 195 "vsopc.y"
                         {(yyval.expression) = new Plus((yyvsp[-2].expression), (yyvsp[0].expression));}
#line 2034 "vsopc.tab.c"
    break;

  case 37: /* Expr: Expr "/" Expr  */
#line 196 "vsopc.y"
                        {(yyval.expression) = new Div((yyvsp[-2].expression), (yyvsp[0].expression));}
#line 2040 "vsopc.tab.c"
    break;

  case 38: /* Expr: Expr "*" Expr  */
#line 197 "vsopc.y"
                          {(yyval.expression) = new Times((yyvsp[-2].expression), (yyvsp[0].expression));}
#line 2046 "vsopc.tab.c"
    break;

  case 39: /* Expr: Expr "^" Expr  */
#line 198 "vsopc.y"
                        {(yyval.expression) = new Pow((yyvsp[-2].expression), (yyvsp[0].expression));}
#line 2052 "vsopc.tab.c"
    break;

  case 40: /* Expr: "-" Expr  */
#line 199 "vsopc.y"
                                      {(yyval.expression) = new UnaryMinus((yyvsp[0].expression));}
#line 2058 "vsopc.tab.c"
    break;

  case 41: /* Expr: "isnull" Expr  */
#line 200 "vsopc.y"
                      {(yyval.expression) = new IsNull((yyvsp[0].expression));}
#line 2064 "vsopc.tab.c"
    break;

  case 42: /* Expr: OBJECT_IDENTIFIER "(" Args ")"  */
#line 201 "vsopc.y"
                                           {(yyval.expression) = new Call(NULL, (yyvsp[-3].stringValue), (yyvsp[-1].args));}
#line 2070 "vsopc.tab.c"
    break;

  case 43: /* Expr: Expr "." OBJECT_IDENTIFIER "(" Args ")"  */
#line 202 "vsopc.y"
                                                    {(yyval.expression) = new Call((yyvsp[-5].expression), (yyvsp[-3].stringValue), (yyvsp[-1].args));}
#line 2076 "vsopc.tab.c"
    break;

  case 44: /* Expr: "new" TYPE_IDENTIFIER  */
#line 203 "vsopc.y"
                              {(yyval.expression) = new New((yyvsp[0].stringValue));}
#line 2082 "vsopc.tab.c"
    break;

  case 45: /* Expr: OBJECT_IDENTIFIER  */
#line 204 "vsopc.y"
                            {(yyval.expression) = new ObjectIdentifier((yyvsp[0].stringValue));}
#line 2088 "vsopc.tab.c"
    break;

  case 46: /* Expr: "self"  */
#line 205 "vsopc.y"
               {(yyval.expression) = new Self();}
#line 2094 "vsopc.tab.c"
    break;

  case 48: /* Expr: "(" ")"  */
#line 207 "vsopc.y"
                    {(yyval.expression) = new Unit();}
#line 2100 "vsopc.tab.c"
    break;

  case 49: /* Expr: "(" Expr ")"  */
#line 208 "vsopc.y"
                         {(yyval.expression) = (yyvsp[-1].expression);}
#line 2106 "vsopc.tab.c"
    break;

  case 50: /* Expr: Block  */
#line 209 "vsopc.y"
                {(yyval.expression) = new Block((yyvsp[0].args));}
#line 2112 "vsopc.tab.c"
    break;

  case 52: /* If: "if" Expr "then" Expr  */
#line 213 "vsopc.y"
                      {(yyval.expression) = new If((yyvsp[-2].expression), (yyvsp[0].expression), NULL);}
#line 2118 "vsopc.tab.c"
    break;

  case 53: /* If: "if" Expr "then" Expr "else" Expr  */
#line 214 "vsopc.y"
                                      {(yyval.expression) = new If((yyvsp[-4].expression), (yyvsp[-2].expression), (yyvsp[0].expression));}
#line 2124 "vsopc.tab.c"
    break;

  case 54: /* While: "while" Expr "do" Expr  */
#line 217 "vsopc.y"
                          {(yyval.expression) = new While((yyvsp[-2].expression), (yyvsp[0].expression));}
#line 2130 "vsopc.tab.c"
    break;

  case 55: /* Let: "let" OBJECT_IDENTIFIER ":" Type "in" Expr  */
#line 220 "vsopc.y"
                                              {(yyval.expression) = new Let((yyvsp[-4].stringValue), (yyvsp[-2].stringValue), (yyvsp[0].expression), NULL);}
#line 2136 "vsopc.tab.c"
    break;

  case 56: /* Let: "let" OBJECT_IDENTIFIER ":" Type "<-" Expr "in" Expr  */
#line 221 "vsopc.y"
                                                               {(yyval.expression) = new Let((yyvsp[-6].stringValue), (yyvsp[-4].stringValue), (yyvsp[0].expression), (yyvsp[-2].expression));}
#line 2142 "vsopc.tab.c"
    break;

  case 57: /* Args: %empty  */
#line 224 "vsopc.y"
            {(yyval.args) = new Args();}
#line 2148 "vsopc.tab.c"
    break;

  case 58: /* Args: Expr ArgsExprList  */
#line 225 "vsopc.y"
                            {(yyvsp[0].args)->addExpr((yyvsp[-1].expression)); 
                             (yyval.args) = (yyvsp[0].args);}
#line 2155 "vsopc.tab.c"
    break;

  case 59: /* ArgsExprList: %empty  */
#line 228 "vsopc.y"
                    {(yyval.args) = new Args();}
#line 2161 "vsopc.tab.c"
    break;

  case 60: /* ArgsExprList: "," Expr ArgsExprList  */
#line 229 "vsopc.y"
                                  {(yyvsp[0].args)->addExpr((yyvsp[-1].expression));
                                   (yyval.args) = (yyvsp[0].args);}
#line 2168 "vsopc.tab.c"
    break;

  case 61: /* Literal: INTEGER_LITERAL  */
#line 233 "vsopc.y"
                         {(yyval.expression) = new IntegerLiteral((yyvsp[0].intValue));}
#line 2174 "vsopc.tab.c"
    break;

  case 62: /* Literal: STRING_LITERAL  */
#line 234 "vsopc.y"
                         {(yyval.expression) = new StringLiteral((yyvsp[0].stringValue));}
#line 2180 "vsopc.tab.c"
    break;

  case 63: /* Literal: "true"  */
#line 235 "vsopc.y"
               {(yyval.expression) = new BooleanLiteral(true);}
#line 2186 "vsopc.tab.c"
    break;

  case 64: /* Literal: "false"  */
#line 236 "vsopc.y"
                {(yyval.expression) = new BooleanLiteral(false);}
#line 2192 "vsopc.tab.c"
    break;

  case 65: /* InvalidToken: INVALID_CHAR  */
#line 239 "vsopc.y"
                           {lexicalError(std::string("invalid character ") + std::string((yyvsp[0].stringValue)));
                        YYERROR;}
#line 2199 "vsopc.tab.c"
    break;

  case 66: /* InvalidToken: INVALID_HEX_NUMBER  */
#line 241 "vsopc.y"
                             {lexicalError(std::string("invalid hexadecimal number ") + std::string((yyvsp[0].stringValue)));
                        YYERROR;}
#line 2206 "vsopc.tab.c"
    break;

  case 67: /* InvalidToken: INVALID_INTEGER_LITERAL  */
#line 243 "vsopc.y"
                                  {lexicalError(std::string("invalid literal value ") + std::string((yyvsp[0].stringValue)));
                        YYERROR;}
#line 2213 "vsopc.tab.c"
    break;

  case 68: /* InvalidToken: INVALID_EOF_STRING  */
#line 245 "vsopc.y"
                             {lexicalError(std::string("unexpected end-of-file without \" closing "));
                        YYERROR;}
#line 2220 "vsopc.tab.c"
    break;

  case 69: /* InvalidToken: INVALID_EOF_COMMENT  */
#line 247 "vsopc.y"
                              {lexicalError(std::string("unexpected end-of-file without *) closing"));
                        YYERROR;}
#line 2227 "vsopc.tab.c"
    break;


#line 2231 "vsopc.tab.c"

        default: break;
      }
    if (yychar_backup != yychar)
      YY_LAC_DISCARD ("yychar change");
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
          = {yyssp, yyesa, &yyes, &yyes_capacity, yytoken, &yylloc};
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        if (yychar != YYEMPTY)
          YY_LAC_ESTABLISH;
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
        yyerror (yymsgp);
        if (yysyntax_error_status == YYENOMEM)
          goto yyexhaustedlab;
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
                      yytoken, &yylval, &yylloc);
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
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  /* If the stack popping above didn't lose the initial context for the
     current lookahead token, the shift below will for sure.  */
  YY_LAC_DISCARD ("error recovery");

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
  goto yyreturn;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;


#if 1
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturn;
#endif


/*-------------------------------------------------------.
| yyreturn -- parsing is finished, clean up and return.  |
`-------------------------------------------------------*/
yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, yylsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  if (yyes != yyesa)
    YYSTACK_FREE (yyes);
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
  return yyresult;
}

#line 250 "vsopc.y"


void yyerror(const std::string message){
    std::cerr << fileName << ":" << yylloc.first_line << ":";
    std::cerr << yylloc.first_column << ": ";
    std::cerr << message << std::endl;
}

void lexicalError(const std::string& message){
    std::cerr << fileName << ":" << yylloc.first_line << ":";
    std::cerr << yylloc.first_column << ": " << "lexical error: ";
    std::cerr << message << std::endl;
}

void syntaxError(const std::string& message){
    std::cerr << fileName << ":" << yylloc.first_line << ":";
    std::cerr << yylloc.first_column << ": " << "syntax error: ";
    std::cerr << message << std::endl;
}

void semanticError(const std::string& message){
    std::cerr << fileName << ":" << yylloc.first_line << ":";
    std::cerr << yylloc.first_column << ": " << "semantic error: ";
    std::cerr << message << std::endl;
}

/* Converts a character to its hexadecimal value */
static std::string hexConvert(char character){
    std::string ret = "\\xhh";
    std::string ref = "0123456789abcdef";

    ret[2] = ref[character / 16];
    ret[3] = ref[character % 16];

    return ret;
}

/* Encode a string according to the statement */
static std::string encodeString(char *string){
    std::string ret = "\"";

    while(*string){

        if(*string != '\"' && *string != '\\'){
            if(*string >= 32 && *string <= 126)
                ret += *string;
            else 
                ret += hexConvert(*string);
        }
        else
            ret += hexConvert(*string);
        
        ++string;
    }

    return ret + "\"";
}

int main(int argc, char** argv){
    /* Check arguments */
    if(argc != 3){
        std::cerr << PROGRAM_USAGE << std::endl;
        return EXIT_FAILURE;
    }

    /* Check if expected option */
    std::string flag = argv[1];
    if (flag != "-l" && flag != "-p" && flag != "-c") {
        std::cerr << PROGRAM_USAGE << std::endl;
        return EXIT_FAILURE;
    }

    /* Open vsop source file */
    fileName = argv[2];
    yyin = fopen(argv[2], "r");
    if(!yyin){
        std::cerr << "Can't open file " << fileName << std::endl;
        return EXIT_FAILURE;
    }

    /* Start lexer */
    if(flag == "-l"){
        int token;

        while((token = yylex()) != 0){
            switch(token)
            {
                case INVALID_HEX_NUMBER:
                    lexicalError(std::string("invalid hexadecimal number ") + std::string(yylval.stringValue));
                    return EXIT_FAILURE;
                case INVALID_CHAR:
                    lexicalError(std::string("invalid character ") + std::string(yylval.stringValue));
                    return EXIT_FAILURE;
                case INVALID_EOF_STRING:
                    lexicalError(std::string("unexpected end-of-file without \" closing"));
                    return EXIT_FAILURE;
                case INVALID_EOF_COMMENT:
                    lexicalError(std::string("unexpected end-of-file without *) closing"));
                    return EXIT_FAILURE;
                case INVALID_INTEGER_LITERAL:
                    lexicalError(std::string("invalid literal value ") + std::string(yylval.stringValue));
                    return EXIT_FAILURE;
                default:
                    break;
            }

            std::cout << yylloc.first_line << "," << yylloc.first_column << ",";
            switch(token){
                case AND:
                    std::cout << "and";
                    break;
                case BOOL:	
                    std::cout << "bool";								
                    break;
                case CLASS:	
                    std::cout << "class";								
                    break;
                case DO:
                    std::cout << "do";									
                    break;
                case ELSE:
                    std::cout << "else";
                    break;
                case EXTENDS:
                    std::cout << "extends";
                    break;
                case FALSE:
                    std::cout << "false";
                    break;
                case IF:
                    std::cout << "if";
                    break;
                case IN:
                    std::cout << "in";
                    break;
                case INT32:				
                    std::cout << "int32";
                    break;
                case ISNULL:
                    std::cout << "isnull";
                    break;
                case LET:
                    std::cout << "let";
                    break;
                case NEW:
                    std::cout << "new";
                    break;
                case NOT:
                    std::cout << "not";
                    break;
                case SELF:	
                    std::cout << "self";    
                    break;
                case STRING:
                    std::cout << "string";
                    break;
                case THEN:
                    std::cout << "then";						
                    break;
                case TRUE:
                    std::cout << "true";
                    break;
                case UNIT:
                    std::cout << "unit";			
                    break;
                case WHILE:
                    std::cout << "while";
                    break;
                case LBRACE:
                    std::cout << "lbrace";			
                    break;
                case RBRACE:
                    std::cout << "rbrace";
                    break;
                case LPAR:
                    std::cout << "lpar";
                    break;
                case RPAR:		
                    std::cout << "rpar";
                    break;
                case COLON:
                    std::cout << "colon";
                    break;
                case SEMICOLON:
                    std::cout << "semicolon";
                    break;
                case COMMA:
                    std::cout << "comma";
                    break;
                case PLUS:
                    std::cout << "plus";
                    break;
                case MINUS:
                    std::cout << "minus";
                    break;
                case TIMES:
                    std::cout << "times";
                    break;
                case DIV:
                    std::cout << "div";
                    break;
                case POW:
                    std::cout << "pow";
                    break;
                case DOT:
                    std::cout << "dot";
                    break;
                case EQUAL:
                    std::cout << "equal";
                    break;
                case LOWER:
                    std::cout << "lower";
                    break;
                case LOWER_EQUAL:
                    std::cout << "lower-equal";
                    break;
                case ASSIGN:
                    std::cout << "assign";
                    break;
                case INTEGER_LITERAL:
                    std::cout << "integer-literal," << yylval.intValue;		
                    break;
	        case TYPE_IDENTIFIER:
                    std::cout << "type-identifier," << yylval.stringValue;
                    break;
		case OBJECT_IDENTIFIER:
                    std::cout << "object-identifier," << yylval.stringValue;
                    break;
                case STRING_LITERAL:
                    std::cout << "string-literal," << encodeString(yylval.stringValue);
                    break;
                default:
                    break;
            }

            std::cout << std::endl;
        }
    }

    /* Start parser */
    if(flag == "-p") {
        abstractSyntaxTree = new Program();
        if(yyparse()) {
            return EXIT_FAILURE;
        }else{
            std::cout << abstractSyntaxTree->eval() << std::endl;
        }
    }

    /* Start semantic analyzer */
    if(flag == "-c") {
        abstractSyntaxTree = new Program();
        if(yyparse()) {
            return EXIT_FAILURE;
        }else{

            /* Check for class, field, method, and formal redefinitions */
            for(Class *cls: abstractSyntaxTree->getClasses())
            {
                std::string className = cls->getName();
                if(abstractSyntaxTree->classesMap.find(className) != abstractSyntaxTree->classesMap.end())
                    semanticError("redefinition of class " + className);
                else 
                    abstractSyntaxTree->classesMap[className] = cls;

                for(Field *field: cls->getFields())
                {
                    std::string fieldName = field->getName();
                    if(cls->fieldsMap.find(fieldName) != cls->fieldsMap.end())
                        semanticError("redefinition of field " + fieldName);
                    else
                        cls->fieldsMap[fieldName] = field;
                }

                for(Method *method: cls->getMethods())
                {
                    std::string methodName = method->getName();
                    if(cls->methodsMap.find(methodName) != cls->methodsMap.end())
                        semanticError("redefinition of method " + methodName);
                    else
                        cls->methodsMap[methodName] = method;
                    

                    for(Formal *formal: method->getFormals())
                    {
                        std::string formalName = formal->getName();
                        if(method->formalsMap.find(formalName) != method->formalsMap.end())
                            semanticError("redefinition of the formal " + formalName);
                        else 
                            method->formalsMap[formalName] = formal;
                    }
                }
            }

            /* Check for inheritance */
            std::set<std::string> parentSet;

            for(Class *cls: abstractSyntaxTree->getClasses())
            {
                std::string parent = cls->getParent();
                while(parent != "Object")
                {
                    /* Cycle in inheritance */
                    if(parentSet.find(parent) != parentSet.end())
                    {
                        semanticError("class " + cls->getName() + " cannot extends parent class " + parent);
                        break;
                    }
                    else
                    {
                        /* Parent class has not been defined */
                        if(abstractSyntaxTree->classesMap.find(parent) == abstractSyntaxTree->classesMap.end())
                        {
                           semanticError("class " + parent + " is not defined");
                           break; 
                        }

                        parentSet.insert(parent);
                        parent = abstractSyntaxTree->classesMap[parent]->getParent();
                    }
                }

                parentSet.clear(); 
            }

            /* Check for overrides */ 
            for(Class *cls: abstractSyntaxTree->getClasses())
            {
                /* Field */
                for(Field *field: cls->getFields())
                {
                    std::string parent = cls->getParent();
                    while(parent != "Object")
                    {
                        if(abstractSyntaxTree->classesMap[parent]->fieldsMap.find(field->getName()) != abstractSyntaxTree->classesMap[parent]->fieldsMap.end())
                            semanticError("field " + field->getName() + " of class " + cls->getName() + " is overriden");
                        
                        parent = abstractSyntaxTree->classesMap[parent]->getParent();
                    }
                }

                for(Method *method: cls->getMethods())
                {
                    std::string parent = cls->getParent();
                    while(parent != "Object")
                    {
                        if(abstractSyntaxTree->classesMap[parent]->methodsMap.find(method->getName()) != abstractSyntaxTree->classesMap[parent]->methodsMap.end())
                        {
                            Method *m =  abstractSyntaxTree->classesMap[parent]->methodsMap[method->getName()];
                            if(m->getRetType() != method->getRetType())
                                semanticError("method " + method->getName() + " of class " + cls->getName() + " overriden with type " + method->getRetType() + " but parent type was " + m->getRetType());
                            
                            if(m->getFormals().size() != method->getFormals().size())
                            {
                                semanticError("method " + method->getName() + " of class " + cls->getName() + " overriden with " + std::to_string(method->getFormals().size()) + " formals but parent class has " + std::to_string(m->getFormals().size()) + " formals");
                                break;
                            }

                            unsigned int i = 0;
                            for(Formal *formal: method->getFormals())
                            {
                                if(m->getFormals(i)->getName() != formal->getName())
                                    semanticError("method " + method->getName() + " of class " + cls->getName() + " overriden with " + formal->getName() + " as formal name in place " + std::to_string(i) + " but parent class has " + m->getFormals(i)->getName() + " as formal name in this position");
                                
                                if(m->getFormals(i)->getType() != formal->getType())
                                    semanticError("method " + method->getName() + " of class " + cls->getName() + " overriden with " + formal->getType() + " as formal type in place " + std::to_string(i) + " but parent class has " + m->getFormals(i)->getType() + " as formal type in this position");
                            }
                        }

                        parent = abstractSyntaxTree->classesMap[parent]->getParent();
                    }
                }
            }
        }
    }

    fclose(yyin);

    return EXIT_SUCCESS;
}
