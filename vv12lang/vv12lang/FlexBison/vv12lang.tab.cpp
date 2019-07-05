/* A Bison parser, made by GNU Bison 3.1.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018 Free Software Foundation, Inc.

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "vv12lang.y" /* yacc.c:339  */

#include <stdio.h>
#include <stdlib.h>
#include "../vv12lang/proc.h"
#define YYDEBUG 1
extern int yylex(void);
int yyerror(char const *str){
    extern char *yytext;
    extern int gLine;
    vv12::Interpreter::getInp()->syntaxExit(1003, gLine, yytext);
    return 0;
}

#line 80 "vv12lang.tab.cpp" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "vv12lang.tab.h".  */
#ifndef YY_YY_VV12LANG_TAB_H_INCLUDED
# define YY_YY_VV12LANG_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 14 "vv12lang.y" /* yacc.c:355  */

#include "../vv12lang/proc.h"

#line 114 "vv12lang.tab.cpp" /* yacc.c:355  */

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    IDENTIFIER = 258,
    LOCAL_IDENTIFIER = 259,
    INT_LITERAL = 260,
    DOUBLE_LITERAL = 261,
    STR_LITERAL = 262,
    CRLF = 263,
    ADD = 264,
    SUB = 265,
    MUL = 266,
    DIV = 267,
    EQ = 268,
    NE = 269,
    LT = 270,
    GT = 271,
    LE = 272,
    GE = 273,
    SEMICOLON = 274,
    COMMA = 275,
    COLON = 276,
    MULASS = 277,
    DIVASS = 278,
    ADDASS = 279,
    SUBASS = 280,
    ASS = 281,
    PRINTN = 282,
    PRINT = 283,
    WHILE = 284,
    IF = 285,
    ELSE = 286,
    FOR = 287,
    BREAK = 288,
    CONTINUE = 289,
    RETURN = 290,
    FUNCTION = 291,
    ARRAY = 292,
    LC = 293,
    RC = 294,
    LP = 295,
    RP = 296,
    LB = 297,
    RB = 298
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 17 "vv12lang.y" /* yacc.c:355  */

    const char* fixedString;
    vv12::Expression* expression;
    vv12::Statement* statement;
    vv12::StatementList* statementList;
	vv12::ParameterList* parameterList;
	vv12::ArgumentList* argumentList;
	vv12::ArrKeyValueList* arraykeyvalueList;
    vv12::ArrKeytList* arraykeyList;
    vv12::Root* root;

#line 182 "vv12lang.tab.cpp" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_VV12LANG_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 199 "vv12lang.tab.cpp" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

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

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
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


#if ! defined yyoverflow || YYERROR_VERBOSE

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
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  59
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   197

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  44
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  27
/* YYNRULES -- Number of rules.  */
#define YYNRULES  75
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  144

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   298

#define YYTRANSLATE(YYX)                                                \
  ((unsigned) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
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
      35,    36,    37,    38,    39,    40,    41,    42,    43
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    51,    51,    57,    61,    67,    68,    69,    70,    71,
      72,    73,    76,    80,    84,    90,    94,   100,   104,   110,
     114,   120,   124,   128,   132,   138,   142,   148,   155,   158,
     162,   168,   171,   172,   176,   180,   184,   188,   192,   198,
     199,   203,   209,   210,   214,   218,   222,   228,   229,   233,
     239,   240,   244,   250,   251,   257,   258,   259,   260,   261,
     267,   271,   278,   281,   285,   291,   295,   301,   305,   311,
     315,   319,   325,   329,   335,   339
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "IDENTIFIER", "LOCAL_IDENTIFIER",
  "INT_LITERAL", "DOUBLE_LITERAL", "STR_LITERAL", "CRLF", "ADD", "SUB",
  "MUL", "DIV", "EQ", "NE", "LT", "GT", "LE", "GE", "SEMICOLON", "COMMA",
  "COLON", "MULASS", "DIVASS", "ADDASS", "SUBASS", "ASS", "PRINTN",
  "PRINT", "WHILE", "IF", "ELSE", "FOR", "BREAK", "CONTINUE", "RETURN",
  "FUNCTION", "ARRAY", "LC", "RC", "LP", "RP", "LB", "RB", "$accept",
  "root", "statement_list", "statement", "expression_statement",
  "compound_statement", "selection_statement", "iteration_statement",
  "jump_statement", "internal_statement", "function_define_statement",
  "parameter_list", "expression", "assign_expression",
  "equality_expression", "relational_expression", "add_expression",
  "mul_expression", "postfix_expression", "primary_expression",
  "internal_expression", "argument_list",
  "initialize_array_key_value_list", "identifier_array_expression",
  "arraykey_list", "identifier_expression", "constart_expression", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298
};
# endif

#define YYPACT_NINF -41

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-41)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     116,   -34,   -40,   -41,   -41,   -41,   -41,    23,    23,   -35,
     -31,   116,    53,    66,    15,    79,    72,    51,    23,   106,
     116,   -41,   -41,   -41,   -41,   -41,   -41,   -41,   -41,   109,
     -41,    19,    21,    34,    39,   -41,   -41,   -41,    99,   155,
     -41,    23,    10,    84,    84,   119,   122,    23,    23,    23,
     -41,   -41,   -41,   123,    92,    23,   -41,    65,   121,   -41,
     -41,   -41,    23,    23,    23,    23,    23,    23,    23,    23,
      59,    59,    23,    23,    23,    23,    23,    23,   -41,   -16,
     -41,    98,    23,   -41,   -41,   101,   114,   128,   -41,   182,
     166,   -10,     4,   -41,   -41,    21,   -41,   -41,    21,    34,
      34,    34,    34,    39,    39,   -40,   -41,   -41,   -41,   -41,
     -41,   -41,   -41,   -41,    23,   -41,   -41,   145,   116,   116,
      23,   -41,    26,    23,   -41,    23,   -41,   -41,   -41,   -41,
     158,   149,   187,   154,   -41,   172,   116,   116,   -41,   -41,
      23,   -41,   -41,   -41
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    72,    73,    75,    74,    59,    12,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       2,     3,     5,     6,     7,     8,     9,    10,    11,     0,
      31,    32,    39,    42,    47,    50,    53,    56,    55,    57,
      58,    62,     0,    67,    68,     0,     0,     0,     0,     0,
      22,    21,    23,     0,     0,    62,    15,     0,     0,     1,
       4,    13,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    63,     0,
      69,     0,     0,    25,    26,     0,     0,     0,    24,    28,
      63,     0,     0,    16,    14,    40,    55,    57,    41,    43,
      44,    45,    46,    48,    49,    72,    51,    52,    34,    37,
      38,    35,    36,    33,     0,    54,    70,     0,     0,     0,
       0,    29,     0,     0,    60,     0,    61,    64,    71,    19,
      18,     0,     0,     0,    65,     0,     0,     0,    30,    27,
       0,    17,    20,    66
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -41,   -41,   177,    -8,   -41,    63,   -41,   -41,   -41,   -41,
     -41,   -41,    -7,    62,   -41,    14,   118,    40,   -41,    44,
     -41,   140,   -41,    95,   195,   105,   -41
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,   122,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    79,    92,    38,    43,    39,    40
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      45,    46,    42,    49,   114,    47,    41,    53,    42,    48,
     114,    58,    60,     1,     2,     3,     4,     5,     1,     2,
       3,     4,     5,    52,   125,   115,     1,     2,     3,     4,
       5,   124,    62,    63,    78,    81,    64,    65,    66,    67,
      85,    86,    87,    68,    69,   126,   132,    16,    90,    60,
      70,    71,    16,    80,     1,     2,     3,     4,     5,     6,
      16,    50,   105,     2,     3,     4,     5,   133,     1,     2,
       3,     4,     5,     6,    51,   117,    95,    98,     7,     8,
       9,    10,    54,    11,    12,    13,    14,    15,    16,    17,
      56,    18,     7,     8,     9,    10,    16,    11,    12,    13,
      14,    15,    16,    17,    93,    18,    59,   127,   103,   104,
     129,   130,    55,   131,   106,   107,   134,    61,   135,     1,
       2,     3,     4,     5,     6,    72,    82,    83,   141,   142,
      84,    88,    89,   143,   108,   109,   110,   111,   112,   113,
      94,   116,   118,     7,     8,     9,    10,   120,    11,    12,
      13,    14,    15,    16,    17,   119,    18,    96,    96,    96,
      96,    96,    96,    96,    96,    96,    96,    97,    97,    97,
      97,    97,    97,    97,    97,    97,    97,    73,    74,    75,
      76,    77,    99,   100,   101,   102,   121,   123,   128,   136,
     137,   138,    17,   140,    57,    91,   139,    44
};

static const yytype_uint8 yycheck[] =
{
       7,     8,    42,    11,    20,    40,    40,    14,    42,    40,
      20,    18,    20,     3,     4,     5,     6,     7,     3,     4,
       5,     6,     7,     8,    20,    41,     3,     4,     5,     6,
       7,    41,    13,    14,    41,    42,    15,    16,    17,    18,
      47,    48,    49,     9,    10,    41,    20,    37,    55,    57,
      11,    12,    37,    43,     3,     4,     5,     6,     7,     8,
      37,     8,     3,     4,     5,     6,     7,    41,     3,     4,
       5,     6,     7,     8,     8,    82,    62,    63,    27,    28,
      29,    30,     3,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    27,    28,    29,    30,    37,    32,    33,    34,
      35,    36,    37,    38,    39,    40,     0,   114,    68,    69,
     118,   119,    40,   120,    70,    71,   123,     8,   125,     3,
       4,     5,     6,     7,     8,    26,    42,     8,   136,   137,
       8,     8,    40,   140,    72,    73,    74,    75,    76,    77,
      19,    43,    41,    27,    28,    29,    30,    19,    32,    33,
      34,    35,    36,    37,    38,    41,    40,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    22,    23,    24,
      25,    26,    64,    65,    66,    67,     4,    21,    43,    31,
      41,     4,    38,    21,    17,    55,   133,     2
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,     5,     6,     7,     8,    27,    28,    29,
      30,    32,    33,    34,    35,    36,    37,    38,    40,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    67,    69,
      70,    40,    42,    68,    68,    56,    56,    40,    40,    47,
       8,     8,     8,    56,     3,    40,    39,    46,    56,     0,
      47,     8,    13,    14,    15,    16,    17,    18,     9,    10,
      11,    12,    26,    22,    23,    24,    25,    26,    56,    65,
      43,    56,    42,     8,     8,    56,    56,    56,     8,    40,
      56,    65,    66,    39,    19,    59,    67,    69,    59,    60,
      60,    60,    60,    61,    61,     3,    63,    63,    57,    57,
      57,    57,    57,    57,    20,    41,    43,    56,    41,    41,
      19,     4,    55,    21,    41,    20,    41,    56,    43,    47,
      47,    56,    20,    41,    56,    56,    31,    41,     4,    49,
      21,    47,    47,    56
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    44,    45,    46,    46,    47,    47,    47,    47,    47,
      47,    47,    48,    48,    48,    49,    49,    50,    50,    51,
      51,    52,    52,    52,    52,    53,    53,    54,    55,    55,
      55,    56,    57,    57,    57,    57,    57,    57,    57,    58,
      58,    58,    59,    59,    59,    59,    59,    60,    60,    60,
      61,    61,    61,    62,    62,    63,    63,    63,    63,    63,
      64,    64,    65,    65,    65,    66,    66,    67,    67,    68,
      68,    68,    69,    69,    70,    70
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     2,     3,     2,     3,     7,     5,     5,
       7,     2,     2,     2,     3,     3,     3,     6,     0,     1,
       3,     1,     1,     3,     3,     3,     3,     3,     3,     1,
       3,     3,     1,     3,     3,     3,     3,     1,     3,     3,
       1,     3,     3,     1,     4,     1,     1,     1,     1,     1,
       4,     4,     0,     1,     3,     3,     5,     2,     2,     2,
       3,     4,     1,     1,     1,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
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
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



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

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
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


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
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
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
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
            /* Fall through.  */
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

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
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
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
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
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
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
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
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
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

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

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
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

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
| yyreduce -- Do a reduction.  |
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


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 52 "vv12lang.y" /* yacc.c:1651  */
    {
        (yyval.root) = vv12::Interpreter::getInp()->createRoot((yyvsp[0].statementList));
    }
#line 1393 "vv12lang.tab.cpp" /* yacc.c:1651  */
    break;

  case 3:
#line 58 "vv12lang.y" /* yacc.c:1651  */
    {
        (yyval.statementList) = vv12::Interpreter::getInp()->createStatementList((yyvsp[0].statement));
    }
#line 1401 "vv12lang.tab.cpp" /* yacc.c:1651  */
    break;

  case 4:
#line 62 "vv12lang.y" /* yacc.c:1651  */
    {
        (yyval.statementList) = vv12::Interpreter::getInp()->createStatementList((yyvsp[-1].statementList),(yyvsp[0].statement));
    }
#line 1409 "vv12lang.tab.cpp" /* yacc.c:1651  */
    break;

  case 12:
#line 77 "vv12lang.y" /* yacc.c:1651  */
    {
        (yyval.statement) = vv12::Interpreter::getInp()->createStatement<vv12::ExpressionStm>();
    }
#line 1417 "vv12lang.tab.cpp" /* yacc.c:1651  */
    break;

  case 13:
#line 81 "vv12lang.y" /* yacc.c:1651  */
    {
        (yyval.statement) = vv12::Interpreter::getInp()->createStatement<vv12::ExpressionStm>((yyvsp[-1].expression));
    }
#line 1425 "vv12lang.tab.cpp" /* yacc.c:1651  */
    break;

  case 14:
#line 85 "vv12lang.y" /* yacc.c:1651  */
    {
		(yyval.statement) = vv12::Interpreter::getInp()->createStatement<vv12::ExpressionStm>((yyvsp[-1].expression));
	}
#line 1433 "vv12lang.tab.cpp" /* yacc.c:1651  */
    break;

  case 15:
#line 91 "vv12lang.y" /* yacc.c:1651  */
    {
        (yyval.statement) = vv12::Interpreter::getInp()->createStatement<vv12::BlockStm>();
    }
#line 1441 "vv12lang.tab.cpp" /* yacc.c:1651  */
    break;

  case 16:
#line 95 "vv12lang.y" /* yacc.c:1651  */
    {
        (yyval.statement) = vv12::Interpreter::getInp()->createStatement<vv12::BlockStm>((yyvsp[-1].statementList));
    }
#line 1449 "vv12lang.tab.cpp" /* yacc.c:1651  */
    break;

  case 17:
#line 101 "vv12lang.y" /* yacc.c:1651  */
    {
        (yyval.statement) = vv12::Interpreter::getInp()->createStatement<vv12::IfElsStm>((yyvsp[-4].expression),(yyvsp[-2].statement),(yyvsp[0].statement));
    }
#line 1457 "vv12lang.tab.cpp" /* yacc.c:1651  */
    break;

  case 18:
#line 105 "vv12lang.y" /* yacc.c:1651  */
    {
        (yyval.statement) = vv12::Interpreter::getInp()->createStatement<vv12::IfStm>((yyvsp[-2].expression),(yyvsp[0].statement));
    }
#line 1465 "vv12lang.tab.cpp" /* yacc.c:1651  */
    break;

  case 19:
#line 111 "vv12lang.y" /* yacc.c:1651  */
    {
        (yyval.statement) = vv12::Interpreter::getInp()->createStatement<vv12::WhileStm>((yyvsp[-2].expression),(yyvsp[0].statement));
    }
#line 1473 "vv12lang.tab.cpp" /* yacc.c:1651  */
    break;

  case 20:
#line 115 "vv12lang.y" /* yacc.c:1651  */
    {
        (yyval.statement) = vv12::Interpreter::getInp()->createStatement<vv12::ForStm>((yyvsp[-5].statement),(yyvsp[-4].expression),(yyvsp[-2].expression),(yyvsp[0].statement));
    }
#line 1481 "vv12lang.tab.cpp" /* yacc.c:1651  */
    break;

  case 21:
#line 121 "vv12lang.y" /* yacc.c:1651  */
    {
        (yyval.statement) = vv12::Interpreter::getInp()->createStatement<vv12::ContinueStm>();
    }
#line 1489 "vv12lang.tab.cpp" /* yacc.c:1651  */
    break;

  case 22:
#line 125 "vv12lang.y" /* yacc.c:1651  */
    {
        (yyval.statement) = vv12::Interpreter::getInp()->createStatement<vv12::BreakStm>();
    }
#line 1497 "vv12lang.tab.cpp" /* yacc.c:1651  */
    break;

  case 23:
#line 129 "vv12lang.y" /* yacc.c:1651  */
    {
        (yyval.statement) = vv12::Interpreter::getInp()->createStatement<vv12::ReturnStm>();
    }
#line 1505 "vv12lang.tab.cpp" /* yacc.c:1651  */
    break;

  case 24:
#line 133 "vv12lang.y" /* yacc.c:1651  */
    {
        (yyval.statement) = vv12::Interpreter::getInp()->createStatement<vv12::ReturnStm>((yyvsp[-1].expression));
    }
#line 1513 "vv12lang.tab.cpp" /* yacc.c:1651  */
    break;

  case 25:
#line 139 "vv12lang.y" /* yacc.c:1651  */
    {
        (yyval.statement) = vv12::Interpreter::getInp()->createStatement<vv12::PrintStm>((yyvsp[-1].expression),true);
    }
#line 1521 "vv12lang.tab.cpp" /* yacc.c:1651  */
    break;

  case 26:
#line 143 "vv12lang.y" /* yacc.c:1651  */
    {
        (yyval.statement) = vv12::Interpreter::getInp()->createStatement<vv12::PrintStm>((yyvsp[-1].expression),false);
    }
#line 1529 "vv12lang.tab.cpp" /* yacc.c:1651  */
    break;

  case 27:
#line 149 "vv12lang.y" /* yacc.c:1651  */
    {
        (yyval.statement) = vv12::Interpreter::getInp()->createFunctionDefineStm((yyvsp[-4].fixedString),(yyvsp[-2].parameterList),(yyvsp[0].statement));
    }
#line 1537 "vv12lang.tab.cpp" /* yacc.c:1651  */
    break;

  case 28:
#line 155 "vv12lang.y" /* yacc.c:1651  */
    {
        (yyval.parameterList) = vv12::Interpreter::getInp()->createParameterList();
    }
#line 1545 "vv12lang.tab.cpp" /* yacc.c:1651  */
    break;

  case 29:
#line 159 "vv12lang.y" /* yacc.c:1651  */
    {
        (yyval.parameterList) = vv12::Interpreter::getInp()->createParameterList((yyvsp[0].fixedString));
    }
#line 1553 "vv12lang.tab.cpp" /* yacc.c:1651  */
    break;

  case 30:
#line 163 "vv12lang.y" /* yacc.c:1651  */
    {
        (yyval.parameterList) = vv12::Interpreter::getInp()->createParameterList((yyvsp[-2].parameterList),(yyvsp[0].fixedString));
    }
#line 1561 "vv12lang.tab.cpp" /* yacc.c:1651  */
    break;

  case 33:
#line 173 "vv12lang.y" /* yacc.c:1651  */
    {
        (yyval.expression) = vv12::Interpreter::getInp()->createAssExp((yyvsp[-2].expression),(yyvsp[0].expression));
    }
#line 1569 "vv12lang.tab.cpp" /* yacc.c:1651  */
    break;

  case 34:
#line 177 "vv12lang.y" /* yacc.c:1651  */
    {
        (yyval.expression) = vv12::Interpreter::getInp()->createAssignArrExp((yyvsp[-2].expression),(yyvsp[0].expression));
    }
#line 1577 "vv12lang.tab.cpp" /* yacc.c:1651  */
    break;

  case 35:
#line 181 "vv12lang.y" /* yacc.c:1651  */
    {
        (yyval.expression) = vv12::Interpreter::getInp()->createToAssExp((yyvsp[-2].expression),(yyvsp[0].expression), vv12::ExpressionType::addAssExp);
    }
#line 1585 "vv12lang.tab.cpp" /* yacc.c:1651  */
    break;

  case 36:
#line 185 "vv12lang.y" /* yacc.c:1651  */
    {
        (yyval.expression) = vv12::Interpreter::getInp()->createToAssExp((yyvsp[-2].expression),(yyvsp[0].expression), vv12::ExpressionType::subAssExp);
    }
#line 1593 "vv12lang.tab.cpp" /* yacc.c:1651  */
    break;

  case 37:
#line 189 "vv12lang.y" /* yacc.c:1651  */
    {
        (yyval.expression) = vv12::Interpreter::getInp()->createToAssExp((yyvsp[-2].expression),(yyvsp[0].expression), vv12::ExpressionType::mulAssExp);
    }
#line 1601 "vv12lang.tab.cpp" /* yacc.c:1651  */
    break;

  case 38:
#line 193 "vv12lang.y" /* yacc.c:1651  */
    {
        (yyval.expression) = vv12::Interpreter::getInp()->createToAssExp((yyvsp[-2].expression),(yyvsp[0].expression), vv12::ExpressionType::divAssExp);
    }
#line 1609 "vv12lang.tab.cpp" /* yacc.c:1651  */
    break;

  case 40:
#line 200 "vv12lang.y" /* yacc.c:1651  */
    {
        (yyval.expression) = vv12::Interpreter::getInp()->createRelationalExp((yyvsp[-2].expression),(yyvsp[0].expression),vv12::ExpressionType::eqExp);
    }
#line 1617 "vv12lang.tab.cpp" /* yacc.c:1651  */
    break;

  case 41:
#line 204 "vv12lang.y" /* yacc.c:1651  */
    {
        (yyval.expression) = vv12::Interpreter::getInp()->createRelationalExp((yyvsp[-2].expression),(yyvsp[0].expression),vv12::ExpressionType::neExp);
    }
#line 1625 "vv12lang.tab.cpp" /* yacc.c:1651  */
    break;

  case 43:
#line 211 "vv12lang.y" /* yacc.c:1651  */
    {
        (yyval.expression) = vv12::Interpreter::getInp()->createRelationalExp((yyvsp[-2].expression),(yyvsp[0].expression),vv12::ExpressionType::ltExp);
    }
#line 1633 "vv12lang.tab.cpp" /* yacc.c:1651  */
    break;

  case 44:
#line 215 "vv12lang.y" /* yacc.c:1651  */
    {
        (yyval.expression) = vv12::Interpreter::getInp()->createRelationalExp((yyvsp[-2].expression),(yyvsp[0].expression),vv12::ExpressionType::gtExp);
    }
#line 1641 "vv12lang.tab.cpp" /* yacc.c:1651  */
    break;

  case 45:
#line 219 "vv12lang.y" /* yacc.c:1651  */
    {
        (yyval.expression) = vv12::Interpreter::getInp()->createRelationalExp((yyvsp[-2].expression),(yyvsp[0].expression),vv12::ExpressionType::leExp);
    }
#line 1649 "vv12lang.tab.cpp" /* yacc.c:1651  */
    break;

  case 46:
#line 223 "vv12lang.y" /* yacc.c:1651  */
    {
        (yyval.expression) = vv12::Interpreter::getInp()->createRelationalExp((yyvsp[-2].expression),(yyvsp[0].expression),vv12::ExpressionType::geExp);
    }
#line 1657 "vv12lang.tab.cpp" /* yacc.c:1651  */
    break;

  case 48:
#line 230 "vv12lang.y" /* yacc.c:1651  */
    {
        (yyval.expression) = vv12::Interpreter::getInp()->createBinaryExp((yyvsp[-2].expression),(yyvsp[0].expression),vv12::ExpressionType::addExp);
    }
#line 1665 "vv12lang.tab.cpp" /* yacc.c:1651  */
    break;

  case 49:
#line 234 "vv12lang.y" /* yacc.c:1651  */
    {
        (yyval.expression) = vv12::Interpreter::getInp()->createBinaryExp((yyvsp[-2].expression),(yyvsp[0].expression),vv12::ExpressionType::subExp);
    }
#line 1673 "vv12lang.tab.cpp" /* yacc.c:1651  */
    break;

  case 51:
#line 241 "vv12lang.y" /* yacc.c:1651  */
    {
        (yyval.expression) = vv12::Interpreter::getInp()->createBinaryExp((yyvsp[-2].expression),(yyvsp[0].expression),vv12::ExpressionType::mulExp);
    }
#line 1681 "vv12lang.tab.cpp" /* yacc.c:1651  */
    break;

  case 52:
#line 245 "vv12lang.y" /* yacc.c:1651  */
    {
        (yyval.expression) = vv12::Interpreter::getInp()->createBinaryExp((yyvsp[-2].expression),(yyvsp[0].expression),vv12::ExpressionType::divExp);
    }
#line 1689 "vv12lang.tab.cpp" /* yacc.c:1651  */
    break;

  case 54:
#line 252 "vv12lang.y" /* yacc.c:1651  */
    {
        (yyval.expression) = vv12::Interpreter::getInp()->createFunctionCallExp((yyvsp[-3].fixedString),(yyvsp[-1].argumentList));
    }
#line 1697 "vv12lang.tab.cpp" /* yacc.c:1651  */
    break;

  case 59:
#line 262 "vv12lang.y" /* yacc.c:1651  */
    {
        (yyval.expression) = vv12::Interpreter::getInp()->createStringLiteralExp();
    }
#line 1705 "vv12lang.tab.cpp" /* yacc.c:1651  */
    break;

  case 60:
#line 268 "vv12lang.y" /* yacc.c:1651  */
    {
        (yyval.expression) = vv12::Interpreter::getInp()->createArrayInitValueExp((yyvsp[-1].argumentList));
    }
#line 1713 "vv12lang.tab.cpp" /* yacc.c:1651  */
    break;

  case 61:
#line 272 "vv12lang.y" /* yacc.c:1651  */
    {
        (yyval.expression) = vv12::Interpreter::getInp()->createArrayInitKeyValueExp((yyvsp[-1].arraykeyvalueList));
    }
#line 1721 "vv12lang.tab.cpp" /* yacc.c:1651  */
    break;

  case 62:
#line 278 "vv12lang.y" /* yacc.c:1651  */
    {
        (yyval.argumentList) = vv12::Interpreter::getInp()->createArgumentList();
    }
#line 1729 "vv12lang.tab.cpp" /* yacc.c:1651  */
    break;

  case 63:
#line 282 "vv12lang.y" /* yacc.c:1651  */
    {
        (yyval.argumentList) = vv12::Interpreter::getInp()->createArgumentList((yyvsp[0].expression));
    }
#line 1737 "vv12lang.tab.cpp" /* yacc.c:1651  */
    break;

  case 64:
#line 286 "vv12lang.y" /* yacc.c:1651  */
    {
        (yyval.argumentList) = vv12::Interpreter::getInp()->createArgumentList((yyvsp[-2].argumentList),(yyvsp[0].expression));
    }
#line 1745 "vv12lang.tab.cpp" /* yacc.c:1651  */
    break;

  case 65:
#line 292 "vv12lang.y" /* yacc.c:1651  */
    {
        (yyval.arraykeyvalueList) = vv12::Interpreter::getInp()->createArrKeyValueList((yyvsp[-2].expression),(yyvsp[0].expression));
    }
#line 1753 "vv12lang.tab.cpp" /* yacc.c:1651  */
    break;

  case 66:
#line 296 "vv12lang.y" /* yacc.c:1651  */
    {
        (yyval.arraykeyvalueList) = vv12::Interpreter::getInp()->createArrKeyValueList((yyvsp[-4].arraykeyvalueList),(yyvsp[-2].expression),(yyvsp[0].expression));
    }
#line 1761 "vv12lang.tab.cpp" /* yacc.c:1651  */
    break;

  case 67:
#line 302 "vv12lang.y" /* yacc.c:1651  */
    {
        (yyval.expression) = vv12::Interpreter::getInp()->createArrayExp((yyvsp[-1].fixedString),(yyvsp[0].arraykeyList),false);
    }
#line 1769 "vv12lang.tab.cpp" /* yacc.c:1651  */
    break;

  case 68:
#line 306 "vv12lang.y" /* yacc.c:1651  */
    {
        (yyval.expression) = vv12::Interpreter::getInp()->createArrayExp((yyvsp[-1].fixedString),(yyvsp[0].arraykeyList),true);
    }
#line 1777 "vv12lang.tab.cpp" /* yacc.c:1651  */
    break;

  case 69:
#line 312 "vv12lang.y" /* yacc.c:1651  */
    {
        (yyval.arraykeyList) = vv12::Interpreter::getInp()->createArrKeytList();
    }
#line 1785 "vv12lang.tab.cpp" /* yacc.c:1651  */
    break;

  case 70:
#line 316 "vv12lang.y" /* yacc.c:1651  */
    {
        (yyval.arraykeyList) = vv12::Interpreter::getInp()->createArrKeytList((yyvsp[-1].expression));
    }
#line 1793 "vv12lang.tab.cpp" /* yacc.c:1651  */
    break;

  case 71:
#line 320 "vv12lang.y" /* yacc.c:1651  */
    {
        (yyval.arraykeyList) = vv12::Interpreter::getInp()->createArrKeytList((yyvsp[-3].arraykeyList),(yyvsp[-1].expression));
    }
#line 1801 "vv12lang.tab.cpp" /* yacc.c:1651  */
    break;

  case 72:
#line 326 "vv12lang.y" /* yacc.c:1651  */
    {
        (yyval.expression) = vv12::Interpreter::getInp()->createVariableExp((yyvsp[0].fixedString),false);
    }
#line 1809 "vv12lang.tab.cpp" /* yacc.c:1651  */
    break;

  case 73:
#line 330 "vv12lang.y" /* yacc.c:1651  */
    {
        (yyval.expression) = vv12::Interpreter::getInp()->createVariableExp((yyvsp[0].fixedString),true);
    }
#line 1817 "vv12lang.tab.cpp" /* yacc.c:1651  */
    break;

  case 74:
#line 336 "vv12lang.y" /* yacc.c:1651  */
    {
        (yyval.expression) = (yyvsp[0].expression);
    }
#line 1825 "vv12lang.tab.cpp" /* yacc.c:1651  */
    break;

  case 75:
#line 340 "vv12lang.y" /* yacc.c:1651  */
    {
        (yyval.expression) = (yyvsp[0].expression);
    }
#line 1833 "vv12lang.tab.cpp" /* yacc.c:1651  */
    break;


#line 1837 "vv12lang.tab.cpp" /* yacc.c:1651  */
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
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



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
                      yytoken, &yylval);
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

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

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

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

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 344 "vv12lang.y" /* yacc.c:1910  */
