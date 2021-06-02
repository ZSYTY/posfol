/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     LP = 258,
     RP = 259,
     LB = 260,
     RB = 261,
     BEG = 262,
     END = 263,
     DOT = 264,
     COMMA = 265,
     COLON = 266,
     MUL = 267,
     DIV = 268,
     MOD = 269,
     UNEQUAL = 270,
     NOT = 271,
     PLUS = 272,
     MINUS = 273,
     GE = 274,
     GT = 275,
     LE = 276,
     LT = 277,
     EQUAL = 278,
     AND = 279,
     OR = 280,
     ASSIGN = 281,
     ADD_ASSIGN = 282,
     SUB_ASSIGN = 283,
     MULTIPLE_ASSIGN = 284,
     DIV_ASSIGN = 285,
     MOD_ASSIGN = 286,
     SEMI = 287,
     ARROR = 288,
     FALSE = 289,
     TRUE = 290,
     PRINT = 291,
     BOOL_TYPE = 292,
     CHAR_TYPE = 293,
     INT_TYPE = 294,
     FLOAT_TYPE = 295,
     FUNC_TYPE = 296,
     VOID_TYPE = 297,
     READ = 298,
     FLOAT = 299,
     INT = 300,
     CHAR = 301,
     STRING = 302,
     ELSE = 303,
     FOR = 304,
     WHILE = 305,
     IF = 306,
     ID = 307,
     PUBLIC = 308,
     PRIVATE = 309,
     IMPLEMENTS = 310,
     NEW = 311,
     CLASS = 312,
     INTERFACE = 313,
     RETURN = 314
   };
#endif
/* Tokens.  */
#define LP 258
#define RP 259
#define LB 260
#define RB 261
#define BEG 262
#define END 263
#define DOT 264
#define COMMA 265
#define COLON 266
#define MUL 267
#define DIV 268
#define MOD 269
#define UNEQUAL 270
#define NOT 271
#define PLUS 272
#define MINUS 273
#define GE 274
#define GT 275
#define LE 276
#define LT 277
#define EQUAL 278
#define AND 279
#define OR 280
#define ASSIGN 281
#define ADD_ASSIGN 282
#define SUB_ASSIGN 283
#define MULTIPLE_ASSIGN 284
#define DIV_ASSIGN 285
#define MOD_ASSIGN 286
#define SEMI 287
#define ARROR 288
#define FALSE 289
#define TRUE 290
#define PRINT 291
#define BOOL_TYPE 292
#define CHAR_TYPE 293
#define INT_TYPE 294
#define FLOAT_TYPE 295
#define FUNC_TYPE 296
#define VOID_TYPE 297
#define READ 298
#define FLOAT 299
#define INT 300
#define CHAR 301
#define STRING 302
#define ELSE 303
#define FOR 304
#define WHILE 305
#define IF 306
#define ID 307
#define PUBLIC 308
#define PRIVATE 309
#define IMPLEMENTS 310
#define NEW 311
#define CLASS 312
#define INTERFACE 313
#define RETURN 314




/* Copy the first part of user declarations.  */
#line 1 "/Users/guoziyang/Documents/posfol1/posfol/parser/parser.y"

//#include "token.h"
#include "../tree/node.h"
#include "../tree/type.h"
#include <stdio.h>
#include <vector>
#include <string>
#include <iostream>
#include "lex.yy.c"
#define PARSER
Block* programBlock;
void yyerror(const char* msg) {
    printf("error from yacc: %s\n", msg);
}


/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 16 "/Users/guoziyang/Documents/posfol1/posfol/parser/parser.y"
{
    std::string* val;
    Node* node;
    Block* block;
    Statement* statement;
    Declaration* declaration;
    Entity* entity;
    VariableDeclaration* variable_declaration;
    ClassDeclaration* class_declaration;
    FunctionDeclaration* function_declaration;
    InterfaceDeclaration* interface_declaration;
    Identifier* identifier;
    Expression* expression;
    LogicStatement* logic_statement;
    IfStatement* if_statement;
    WhileStatement* while_statement;
    ForStatement* for_statement;
    ReturnStatement* return_statement;
    IOStatement* io_stmt;
    std::vector<Identifier*>* id_list;
    std::vector<VariableDeclaration*>* var_decl_list;
    std::vector<Expression*>* expr_list;
}
/* Line 193 of yacc.c.  */
#line 254 "y.tab.cpp"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 267 "y.tab.cpp"

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
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
}
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
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
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
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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
  yytype_int16 yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  21
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   340

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  60
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  48
/* YYNRULES -- Number of rules.  */
#define YYNRULES  126
/* YYNRULES -- Number of states.  */
#define YYNSTATES  253

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   314

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
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
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     6,     8,    11,    13,    15,    17,
      19,    21,    25,    27,    29,    31,    33,    35,    37,    39,
      41,    45,    49,    63,    65,    66,    68,    72,    74,    75,
      77,    82,    85,    89,    96,   105,   106,   108,   111,   113,
     116,   119,   122,   130,   132,   134,   141,   142,   144,   147,
     149,   156,   165,   166,   168,   171,   173,   175,   178,   180,
     182,   186,   190,   194,   198,   202,   206,   208,   212,   214,
     218,   220,   222,   226,   230,   234,   238,   242,   246,   250,
     254,   256,   260,   264,   268,   270,   272,   277,   279,   281,
     287,   289,   293,   296,   299,   301,   305,   310,   312,   316,
     321,   326,   331,   336,   341,   343,   345,   347,   349,   351,
     352,   354,   358,   360,   362,   364,   366,   368,   377,   382,
     383,   391,   403,   407,   410,   416,   422
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      61,     0,    -1,    62,    -1,    -1,    63,    -1,    63,    64,
      -1,    64,    -1,    82,    -1,    65,    -1,    72,    -1,    78,
      -1,    66,    67,    32,    -1,    37,    -1,    38,    -1,    39,
      -1,    40,    -1,    41,    -1,    42,    -1,    52,    -1,    52,
      -1,    52,    26,    46,    -1,    52,    26,    86,    -1,    52,
      26,     5,    68,     6,     3,    70,     4,    33,    66,     7,
      83,     8,    -1,    96,    -1,    -1,    69,    -1,    69,    10,
      52,    -1,    52,    -1,    -1,    71,    -1,    71,    10,    66,
      52,    -1,    66,    52,    -1,    57,    52,    32,    -1,    57,
      52,     7,    73,     8,    32,    -1,    57,    52,    55,    52,
       7,    73,     8,    32,    -1,    -1,    74,    -1,    74,    75,
      -1,    75,    -1,    77,    82,    -1,    77,    65,    -1,    77,
      76,    -1,    52,     3,    70,     4,     7,    83,     8,    -1,
      53,    -1,    54,    -1,    58,    52,     7,    79,     8,    32,
      -1,    -1,    80,    -1,    80,    81,    -1,    81,    -1,    66,
      52,     3,    70,     4,    32,    -1,    66,    52,     3,    70,
       4,     7,    83,     8,    -1,    -1,    84,    -1,    84,    85,
      -1,    85,    -1,    65,    -1,    86,    32,    -1,   101,    -1,
     107,    -1,    94,    26,    86,    -1,    94,    27,    86,    -1,
      94,    28,    86,    -1,    94,    29,    86,    -1,    94,    30,
      86,    -1,    94,    31,    86,    -1,    87,    -1,    87,    25,
      88,    -1,    88,    -1,    88,    24,    89,    -1,    89,    -1,
      90,    -1,    89,    19,    90,    -1,    89,    20,    90,    -1,
      89,    21,    90,    -1,    89,    22,    90,    -1,    89,    23,
      90,    -1,    89,    15,    90,    -1,    90,    17,    91,    -1,
      90,    18,    91,    -1,    91,    -1,    91,    12,    92,    -1,
      91,    13,    92,    -1,    91,    14,    92,    -1,    92,    -1,
      93,    -1,     3,    66,     4,    93,    -1,    94,    -1,    97,
      -1,    56,    52,     3,    99,     4,    -1,    98,    -1,     3,
      86,     4,    -1,    16,    92,    -1,    18,    92,    -1,    52,
      -1,    95,     9,    52,    -1,    95,     5,    86,     6,    -1,
      52,    -1,    95,     9,    52,    -1,    95,     5,    86,     6,
      -1,    95,     3,    99,     4,    -1,    52,     5,    86,     6,
      -1,    96,     5,    86,     6,    -1,    95,     3,    99,     4,
      -1,    45,    -1,    44,    -1,    46,    -1,    35,    -1,    34,
      -1,    -1,   100,    -1,   100,    10,    86,    -1,    86,    -1,
     102,    -1,   104,    -1,   105,    -1,   106,    -1,    51,     3,
      86,     4,     7,    83,     8,   103,    -1,    48,     7,    83,
       8,    -1,    -1,    50,     3,    86,     4,     7,    83,     8,
      -1,    49,     3,    86,    32,    86,    32,    86,     4,     7,
      83,     8,    -1,    59,    86,    32,    -1,    59,    32,    -1,
      43,     3,    94,     4,    32,    -1,    36,     3,    86,     4,
      32,    -1,    36,     3,    47,     4,    32,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    64,    64,    70,    73,    77,    80,    87,    88,    89,
      90,    94,   101,   102,   103,   104,   105,   106,   107,   121,
     125,   130,   134,   138,   144,   147,   151,   155,   163,   167,
     171,   175,   184,   185,   189,   197,   200,   204,   207,   214,
     215,   216,   220,   227,   228,   232,   239,   242,   246,   249,
     256,   262,   280,   283,   287,   290,   297,   298,   299,   300,
     304,   305,   306,   307,   308,   309,   310,   314,   315,   319,
     320,   324,   325,   326,   327,   328,   329,   330,   334,   335,
     336,   340,   341,   342,   343,   347,   348,   352,   353,   354,
     357,   358,   359,   360,   364,   368,   372,   376,   380,   384,
     385,   389,   395,   401,   407,   411,   415,   419,   423,   430,
     433,   437,   440,   448,   449,   450,   451,   455,   461,   464,
     470,   476,   482,   485,   491,   494,   497
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "LP", "RP", "LB", "RB", "BEG", "END",
  "DOT", "COMMA", "COLON", "MUL", "DIV", "MOD", "UNEQUAL", "NOT", "PLUS",
  "MINUS", "GE", "GT", "LE", "LT", "EQUAL", "AND", "OR", "ASSIGN",
  "ADD_ASSIGN", "SUB_ASSIGN", "MULTIPLE_ASSIGN", "DIV_ASSIGN",
  "MOD_ASSIGN", "SEMI", "ARROR", "FALSE", "TRUE", "PRINT", "BOOL_TYPE",
  "CHAR_TYPE", "INT_TYPE", "FLOAT_TYPE", "FUNC_TYPE", "VOID_TYPE", "READ",
  "FLOAT", "INT", "CHAR", "STRING", "ELSE", "FOR", "WHILE", "IF", "ID",
  "PUBLIC", "PRIVATE", "IMPLEMENTS", "NEW", "CLASS", "INTERFACE", "RETURN",
  "$accept", "program", "global_stmts", "global_stmts_nonempty",
  "global_stmt", "varible_decl", "varible_decl_type", "id_and_initial",
  "id_list", "id_list_nonempty", "args_list", "args_list_nonempty",
  "class_decl", "class_stmts", "class_stmts_nonempty", "class_stmt",
  "construction_decl", "access_label", "interface_decl", "interface_stmts",
  "interface_stmts_nonempty", "interface_stmt", "function_decl", "stmts",
  "stmts_nonempty", "stmt", "expr", "expr0", "expr1", "expr2",
  "arithmetic", "term", "factor", "factor_nontype_convert", "entity",
  "entity_inner", "array_entity", "function_call", "literal", "expr_list",
  "expr_list_nonempty", "logical_stmt", "if_stmt", "else_clause",
  "while_stmt", "for_stmt", "return_stmt", "io_stmt", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    60,    61,    62,    62,    63,    63,    64,    64,    64,
      64,    65,    66,    66,    66,    66,    66,    66,    66,    67,
      67,    67,    67,    67,    68,    68,    69,    69,    70,    70,
      71,    71,    72,    72,    72,    73,    73,    74,    74,    75,
      75,    75,    76,    77,    77,    78,    79,    79,    80,    80,
      81,    82,    83,    83,    84,    84,    85,    85,    85,    85,
      86,    86,    86,    86,    86,    86,    86,    87,    87,    88,
      88,    89,    89,    89,    89,    89,    89,    89,    90,    90,
      90,    91,    91,    91,    91,    92,    92,    93,    93,    93,
      93,    93,    93,    93,    94,    94,    94,    95,    95,    95,
      95,    96,    96,    97,    98,    98,    98,    98,    98,    99,
      99,   100,   100,   101,   101,   101,   101,   102,   103,   103,
     104,   105,   106,   106,   107,   107,   107
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     0,     1,     2,     1,     1,     1,     1,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     3,    13,     1,     0,     1,     3,     1,     0,     1,
       4,     2,     3,     6,     8,     0,     1,     2,     1,     2,
       2,     2,     7,     1,     1,     6,     0,     1,     2,     1,
       6,     8,     0,     1,     2,     1,     1,     2,     1,     1,
       3,     3,     3,     3,     3,     3,     1,     3,     1,     3,
       1,     1,     3,     3,     3,     3,     3,     3,     3,     3,
       1,     3,     3,     3,     1,     1,     4,     1,     1,     5,
       1,     3,     2,     2,     1,     3,     4,     1,     3,     4,
       4,     4,     4,     4,     1,     1,     1,     1,     1,     0,
       1,     3,     1,     1,     1,     1,     1,     8,     4,     0,
       7,    11,     3,     2,     5,     5,     5
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,    12,    13,    14,    15,    16,    17,    18,     0,     0,
       0,     2,     4,     6,     8,     0,     9,    10,     7,     0,
       0,     1,     5,    19,     0,    23,    35,    32,     0,    46,
      28,     0,     0,    11,     0,    43,    44,     0,    36,    38,
       0,     0,     0,     0,    47,    49,     0,     0,    29,     0,
       0,     0,   108,   107,   105,   104,   106,    94,     0,     0,
      66,    68,    70,    71,    80,    84,    85,    87,     0,    88,
      90,    24,   106,    21,     0,     0,    37,    18,    40,    41,
      39,    35,     0,     0,    48,    31,     0,     0,    94,     0,
       0,    92,    87,    93,     0,   101,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   109,     0,     0,    27,     0,
      25,   102,    33,    28,     0,    28,    45,    52,     0,     0,
      91,   109,    67,    69,    77,    72,    73,    74,    75,    76,
      78,    79,    81,    82,    83,    60,    61,    62,    63,    64,
      65,   112,     0,   110,     0,    95,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    56,     0,     0,
      53,    55,     0,    58,   113,   114,   115,   116,    59,    30,
       0,    86,     0,   103,     0,    96,    28,    26,     0,    34,
       0,     0,     0,     0,     0,     0,   123,     0,    19,    51,
      54,    57,    89,   111,     0,    52,    50,     0,     0,     0,
       0,     0,     0,     0,   122,     0,     0,     0,     0,     0,
     109,     0,     0,     0,     0,    42,   126,   125,   124,     0,
       0,    52,    52,     0,   100,     0,     0,     0,    52,     0,
     120,   119,     0,     0,     0,   117,    22,    52,    52,     0,
       0,   121,   118
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    10,    11,    12,    13,   167,   168,    24,   119,   120,
      47,    48,    16,    37,    38,    39,    79,    40,    17,    43,
      44,    45,    18,   169,   170,   171,   172,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    25,    69,    70,   152,
     153,   173,   174,   245,   175,   176,   177,   178
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -198
static const yytype_int16 yypact[] =
{
     266,  -198,  -198,  -198,  -198,  -198,  -198,  -198,   -16,   -13,
      45,  -198,   266,  -198,  -198,    -5,  -198,  -198,  -198,    21,
       4,  -198,  -198,    12,    16,    47,   -21,  -198,     2,    66,
      66,   245,   125,  -198,   245,  -198,  -198,    64,   -21,  -198,
     288,    68,    37,    65,    66,  -198,    38,    73,    85,    75,
     245,   245,  -198,  -198,  -198,  -198,  -198,    91,    46,    93,
      72,    78,   153,    25,     8,  -198,  -198,   169,   129,  -198,
    -198,    59,    90,  -198,   118,    94,  -198,   126,  -198,  -198,
    -198,   -21,   134,   112,  -198,  -198,   138,    66,    22,   148,
     151,  -198,  -198,  -198,   145,  -198,   245,   245,   245,   245,
     245,   245,   245,   245,   245,   245,   245,   245,   245,   245,
     245,   245,   245,   245,   245,   245,   245,   104,  -198,   152,
     147,  -198,  -198,    66,   154,    66,  -198,   176,   114,   265,
    -198,   245,    78,   153,    25,    25,    25,    25,    25,    25,
       8,     8,  -198,  -198,  -198,  -198,  -198,  -198,  -198,  -198,
    -198,  -198,   163,   172,   177,   130,   182,   135,   184,   157,
     189,   198,   199,   200,   201,   203,   220,  -198,   155,   221,
     176,  -198,   202,  -198,  -198,  -198,  -198,  -198,  -198,  -198,
     245,  -198,   204,   137,   245,   144,    66,  -198,   223,  -198,
     205,   240,   179,   245,   245,   245,  -198,   207,    11,  -198,
    -198,  -198,  -198,  -198,   229,   176,  -198,   236,   237,   238,
     175,   212,   241,   242,  -198,   214,   243,   217,   218,   225,
     245,   245,   246,   252,    66,  -198,  -198,  -198,  -198,   256,
     230,   176,   176,   260,  -198,   245,   261,   262,   176,   267,
    -198,   161,   269,   271,   275,  -198,  -198,   176,   176,   280,
     285,  -198,  -198
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -198,  -198,  -198,  -198,   282,     6,     0,  -198,  -198,  -198,
    -118,  -198,  -198,   192,  -198,   257,  -198,  -198,  -198,  -198,
    -198,   254,   272,  -197,  -198,   132,   -30,  -198,   219,   216,
     233,   -81,   -37,   185,   -41,   124,  -198,  -198,  -198,  -128,
    -198,  -198,  -198,  -198,  -198,  -198,  -198,  -198
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -101
static const yytype_int16 yytable[] =
{
      15,    59,    73,   182,    74,   158,    14,   160,   216,    92,
      92,    29,    15,    91,    93,    30,    31,    31,    14,    90,
     106,   107,   108,   140,   141,   -97,   -18,   -97,    26,    42,
      46,   -97,    35,    36,   236,   237,    19,    32,    32,    20,
      15,   242,   104,   105,    42,    21,    78,    23,    33,    89,
     249,   250,    34,    27,    41,    92,    92,    92,    92,    92,
      92,    92,    92,    92,    92,    92,    92,    92,   204,   142,
     143,   144,    75,    83,   -18,    81,    28,    86,    49,   145,
     146,   147,   148,   149,   150,   151,   154,   128,    92,    82,
      85,    50,   229,    51,   -97,    87,   -97,    96,    94,    95,
     -97,   151,    97,     1,     2,     3,     4,     5,     6,    52,
      53,   118,     1,     2,     3,     4,     5,     6,     7,    54,
      55,    56,   -20,    46,   121,    46,   122,    88,    49,   123,
      71,    58,   115,   -98,   116,   -98,   197,   125,   117,   -98,
    -100,    50,  -100,    51,   126,   127,  -100,   -99,   131,   -99,
      90,   209,   129,   -99,   203,   130,   155,   157,   156,    52,
      53,   208,   159,   211,   212,   213,   179,   183,    98,    54,
      55,    72,    99,   100,   101,   102,   103,    57,   220,    49,
     116,    58,   184,   185,   117,   186,    46,   187,   188,   189,
     151,   230,    50,   190,    51,   109,   110,   111,   112,   113,
     114,   191,   192,   193,   194,   239,   195,   198,   202,   244,
      52,    53,   161,     1,     2,     3,     4,     5,     6,   162,
      54,    55,    56,    49,   233,   163,   164,   165,    88,   199,
     205,    57,    58,   215,   201,   166,    50,   206,    51,   214,
     217,   218,   219,    49,   221,   222,   223,   224,    49,   226,
     227,   225,   196,   231,    52,    53,    50,   228,    51,   232,
     234,    50,   235,    51,    54,    55,    56,   238,   180,   240,
     241,   243,    57,   124,    52,    53,    58,   246,   247,    52,
      53,    50,   248,    51,    54,    55,    56,   207,   251,    54,
      55,    56,    57,   252,    22,    76,    58,    57,    84,    52,
      53,    58,   200,     1,     2,     3,     4,     5,     6,    54,
      55,    56,    80,   133,   181,   132,   210,    57,     7,     0,
       0,    58,     0,     8,     9,     1,     2,     3,     4,     5,
       6,   134,   135,   136,   137,   138,   139,     0,     0,     0,
      77
};

static const yytype_int16 yycheck[] =
{
       0,    31,    32,   131,    34,   123,     0,   125,   205,    50,
      51,     7,    12,    50,    51,     3,     5,     5,    12,    49,
      12,    13,    14,   104,   105,     3,     4,     5,     7,    29,
      30,     9,    53,    54,   231,   232,    52,    26,    26,    52,
      40,   238,    17,    18,    44,     0,    40,    52,    32,    49,
     247,   248,     5,    32,    52,    96,    97,    98,    99,   100,
     101,   102,   103,   104,   105,   106,   107,   108,   186,   106,
     107,   108,     8,     8,    52,     7,    55,     4,     3,   109,
     110,   111,   112,   113,   114,   115,   116,    87,   129,    52,
      52,    16,   220,    18,     3,    10,     5,    25,    52,     6,
       9,   131,    24,    37,    38,    39,    40,    41,    42,    34,
      35,    52,    37,    38,    39,    40,    41,    42,    52,    44,
      45,    46,    32,   123,     6,   125,    32,    52,     3,     3,
       5,    56,     3,     3,     5,     5,   166,     3,     9,     9,
       3,    16,     5,    18,    32,     7,     9,     3,     3,     5,
     180,   192,     4,     9,   184,     4,    52,    10,     6,    34,
      35,   191,     8,   193,   194,   195,    52,     4,    15,    44,
      45,    46,    19,    20,    21,    22,    23,    52,     3,     3,
       5,    56,    10,     6,     9,     3,   186,    52,     4,    32,
     220,   221,    16,     4,    18,    26,    27,    28,    29,    30,
      31,     3,     3,     3,     3,   235,     3,    52,     4,    48,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,     3,   224,    49,    50,    51,    52,     8,
       7,    52,    56,     4,    32,    59,    16,    32,    18,    32,
       4,     4,     4,     3,    32,     4,     4,    33,     3,    32,
      32,     8,    32,     7,    34,    35,    16,    32,    18,     7,
       4,    16,    32,    18,    44,    45,    46,     7,     3,     8,
       8,     4,    52,    81,    34,    35,    56,     8,     7,    34,
      35,    16,     7,    18,    44,    45,    46,    47,     8,    44,
      45,    46,    52,     8,    12,    38,    56,    52,    44,    34,
      35,    56,   170,    37,    38,    39,    40,    41,    42,    44,
      45,    46,    40,    97,   129,    96,   192,    52,    52,    -1,
      -1,    56,    -1,    57,    58,    37,    38,    39,    40,    41,
      42,    98,    99,   100,   101,   102,   103,    -1,    -1,    -1,
      52
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    37,    38,    39,    40,    41,    42,    52,    57,    58,
      61,    62,    63,    64,    65,    66,    72,    78,    82,    52,
      52,     0,    64,    52,    67,    96,     7,    32,    55,     7,
       3,     5,    26,    32,     5,    53,    54,    73,    74,    75,
      77,    52,    66,    79,    80,    81,    66,    70,    71,     3,
      16,    18,    34,    35,    44,    45,    46,    52,    56,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    95,    97,
      98,     5,    46,    86,    86,     8,    75,    52,    65,    76,
      82,     7,    52,     8,    81,    52,     4,    10,    52,    66,
      86,    92,    94,    92,    52,     6,    25,    24,    15,    19,
      20,    21,    22,    23,    17,    18,    12,    13,    14,    26,
      27,    28,    29,    30,    31,     3,     5,     9,    52,    68,
      69,     6,    32,     3,    73,     3,    32,     7,    66,     4,
       4,     3,    88,    89,    90,    90,    90,    90,    90,    90,
      91,    91,    92,    92,    92,    86,    86,    86,    86,    86,
      86,    86,    99,   100,    86,    52,     6,    10,    70,     8,
      70,    36,    43,    49,    50,    51,    59,    65,    66,    83,
      84,    85,    86,   101,   102,   104,   105,   106,   107,    52,
       3,    93,    99,     4,    10,     6,     3,    52,     4,    32,
       4,     3,     3,     3,     3,     3,    32,    86,    52,     8,
      85,    32,     4,    86,    70,     7,    32,    47,    86,    94,
      95,    86,    86,    86,    32,     4,    83,     4,     4,     4,
       3,    32,     4,     4,    33,     8,    32,    32,    32,    99,
      86,     7,     7,    66,     4,    32,    83,    83,     7,    86,
       8,     8,    83,     4,    48,   103,     8,     7,     7,    83,
      83,     8,     8
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      fprintf (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

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
#ifndef	YYINITDEPTH
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
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

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  
  int yystate;
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;

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
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;


      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
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
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

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
     `$$ = $1'.

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
#line 64 "/Users/guoziyang/Documents/posfol1/posfol/parser/parser.y"
    {
        programBlock = (yyvsp[(1) - (1)].block);
    ;}
    break;

  case 3:
#line 70 "/Users/guoziyang/Documents/posfol1/posfol/parser/parser.y"
    {
        (yyval.block) = new Block();
    ;}
    break;

  case 5:
#line 77 "/Users/guoziyang/Documents/posfol1/posfol/parser/parser.y"
    {
        (yyvsp[(1) - (2)].block)->getStatementList()->push_back((yyvsp[(2) - (2)].statement));
    ;}
    break;

  case 6:
#line 80 "/Users/guoziyang/Documents/posfol1/posfol/parser/parser.y"
    {
        (yyval.block) = new Block();
        (yyval.block)->getStatementList()->push_back((yyvsp[(1) - (1)].statement));
    ;}
    break;

  case 8:
#line 88 "/Users/guoziyang/Documents/posfol1/posfol/parser/parser.y"
    {puts("variable declaration");;}
    break;

  case 11:
#line 94 "/Users/guoziyang/Documents/posfol1/posfol/parser/parser.y"
    {
        (yyval.variable_declaration) = (yyvsp[(2) - (3)].variable_declaration);
        (yyval.variable_declaration)->setVarType((yyvsp[(1) - (3)].identifier));
    ;}
    break;

  case 12:
#line 101 "/Users/guoziyang/Documents/posfol1/posfol/parser/parser.y"
    {(yyval.identifier) = new Identifier(Type::BOOLEAN_DEFINE_TYPE);;}
    break;

  case 13:
#line 102 "/Users/guoziyang/Documents/posfol1/posfol/parser/parser.y"
    {(yyval.identifier) = new Identifier(Type::CHAR_DEFINE_TYPE); puts("char types");;}
    break;

  case 14:
#line 103 "/Users/guoziyang/Documents/posfol1/posfol/parser/parser.y"
    {(yyval.identifier) = new Identifier(Type::INT_DEFINE_TYPE);  puts("int types");}
    break;

  case 15:
#line 104 "/Users/guoziyang/Documents/posfol1/posfol/parser/parser.y"
    {(yyval.identifier) = new Identifier(Type::FLOAT_DEFINE_TYPE); ;}
    break;

  case 16:
#line 105 "/Users/guoziyang/Documents/posfol1/posfol/parser/parser.y"
    {(yyval.identifier) = new Identifier(Type::FUNC_DEFINE_TYPE); ;}
    break;

  case 17:
#line 106 "/Users/guoziyang/Documents/posfol1/posfol/parser/parser.y"
    {(yyval.identifier) = new Identifier(Type::VOID_DEFINE_TYPE); puts("void func type"); ;}
    break;

  case 18:
#line 107 "/Users/guoziyang/Documents/posfol1/posfol/parser/parser.y"
    {(yyval.identifier) = new Identifier(Type::CLASS_DEFINE_TYPE, *((yyvsp[(1) - (1)].val)));;}
    break;

  case 19:
#line 121 "/Users/guoziyang/Documents/posfol1/posfol/parser/parser.y"
    {
        (yyval.variable_declaration) = new VariableDeclaration(nullptr, new Identifier(Type::NAME, *((yyvsp[(1) - (1)].val))));
        //delete $1;
    ;}
    break;

  case 20:
#line 125 "/Users/guoziyang/Documents/posfol1/posfol/parser/parser.y"
    {
        (yyval.variable_declaration) = new VariableDeclaration(nullptr, new Identifier(Type::NAME, *((yyvsp[(1) - (3)].val))), new Identifier(Type::VALUE, *((yyvsp[(3) - (3)].val))));
        //delete $1;
        //delete $3;
    ;}
    break;

  case 21:
#line 130 "/Users/guoziyang/Documents/posfol1/posfol/parser/parser.y"
    {
        (yyval.variable_declaration) = new VariableDeclaration(nullptr, new Identifier(Type::NAME, *((yyvsp[(1) - (3)].val))), (yyvsp[(3) - (3)].expression));
        //delete $1;
    ;}
    break;

  case 22:
#line 134 "/Users/guoziyang/Documents/posfol1/posfol/parser/parser.y"
    {
        (yyval.variable_declaration) = new VariableDeclaration(nullptr, new Identifier(Type::NAME, *((yyvsp[(1) - (13)].val))), new LambdaExpression((yyvsp[(4) - (13)].id_list), (yyvsp[(7) - (13)].var_decl_list), (yyvsp[(10) - (13)].identifier), (yyvsp[(12) - (13)].block)));
        //delete $1;
    ;}
    break;

  case 23:
#line 138 "/Users/guoziyang/Documents/posfol1/posfol/parser/parser.y"
    {
        (yyval.variable_declaration) = new VariableDeclaration(nullptr, (Identifier*)((*(yyvsp[(1) - (1)].expr_list))[0]), new std::vector<Expression*>((yyvsp[(1) - (1)].expr_list)->begin() + 1, (yyvsp[(1) - (1)].expr_list)->end()));
    ;}
    break;

  case 24:
#line 144 "/Users/guoziyang/Documents/posfol1/posfol/parser/parser.y"
    {
        (yyval.id_list) = new std::vector<Identifier*>();
    ;}
    break;

  case 26:
#line 151 "/Users/guoziyang/Documents/posfol1/posfol/parser/parser.y"
    {
        (yyvsp[(1) - (3)].id_list)->push_back(new Identifier(Type::NAME, *((yyvsp[(3) - (3)].val))));
        //delete $3;
    ;}
    break;

  case 27:
#line 155 "/Users/guoziyang/Documents/posfol1/posfol/parser/parser.y"
    {
        (yyval.id_list) = new std::vector<Identifier*>();
        (yyval.id_list)->push_back(new Identifier(Type::NAME, *((yyvsp[(1) - (1)].val))));
        //delete $1;
    ;}
    break;

  case 28:
#line 163 "/Users/guoziyang/Documents/posfol1/posfol/parser/parser.y"
    {
        puts("empty args_list");
        (yyval.var_decl_list) = new std::vector<VariableDeclaration*>();
    ;}
    break;

  case 30:
#line 171 "/Users/guoziyang/Documents/posfol1/posfol/parser/parser.y"
    {
        (yyvsp[(1) - (4)].var_decl_list)->push_back(new VariableDeclaration((yyvsp[(3) - (4)].identifier), new Identifier(Type::NAME, *((yyvsp[(4) - (4)].val)))));
        //delete $4;
    ;}
    break;

  case 31:
#line 175 "/Users/guoziyang/Documents/posfol1/posfol/parser/parser.y"
    {
        puts("args_list_nonempty first one");
        (yyval.var_decl_list) = new std::vector<VariableDeclaration*>();
        (yyval.var_decl_list)->push_back(new VariableDeclaration((yyvsp[(1) - (2)].identifier), new Identifier(Type::NAME, *((yyvsp[(2) - (2)].val)))));
        //delete $2;
    ;}
    break;

  case 33:
#line 185 "/Users/guoziyang/Documents/posfol1/posfol/parser/parser.y"
    {
        (yyval.class_declaration) = new ClassDeclaration(new Identifier(Type::NAME, *((yyvsp[(2) - (6)].val))), (yyvsp[(4) - (6)].block));
        //delete $2;
    ;}
    break;

  case 34:
#line 189 "/Users/guoziyang/Documents/posfol1/posfol/parser/parser.y"
    {
        (yyval.class_declaration) = new ClassDeclaration(new Identifier(Type::NAME, *((yyvsp[(2) - (8)].val))), new Identifier(Type::NAME, *((yyvsp[(4) - (8)].val))), (yyvsp[(6) - (8)].block));
        //delete $2;
        //delete $4;
    ;}
    break;

  case 35:
#line 197 "/Users/guoziyang/Documents/posfol1/posfol/parser/parser.y"
    {
        (yyval.block) = new Block();
    ;}
    break;

  case 36:
#line 200 "/Users/guoziyang/Documents/posfol1/posfol/parser/parser.y"
    {puts("class_stmts_nonempty");;}
    break;

  case 37:
#line 204 "/Users/guoziyang/Documents/posfol1/posfol/parser/parser.y"
    {
        (yyvsp[(1) - (2)].block)->getStatementList()->push_back((yyvsp[(2) - (2)].statement));
    ;}
    break;

  case 38:
#line 207 "/Users/guoziyang/Documents/posfol1/posfol/parser/parser.y"
    {
        (yyval.block) = new Block();
        (yyval.block)->getStatementList()->push_back((yyvsp[(1) - (1)].statement));
    ;}
    break;

  case 39:
#line 214 "/Users/guoziyang/Documents/posfol1/posfol/parser/parser.y"
    {(yyval.statement) = (yyvsp[(2) - (2)].function_declaration);;}
    break;

  case 40:
#line 215 "/Users/guoziyang/Documents/posfol1/posfol/parser/parser.y"
    {(yyval.statement) = (yyvsp[(2) - (2)].variable_declaration);puts("variable declaration");;}
    break;

  case 41:
#line 216 "/Users/guoziyang/Documents/posfol1/posfol/parser/parser.y"
    {(yyval.statement) = (yyvsp[(2) - (2)].function_declaration); puts("construction declaration");;}
    break;

  case 42:
#line 220 "/Users/guoziyang/Documents/posfol1/posfol/parser/parser.y"
    {
        (yyval.function_declaration) = new FunctionDeclaration(new Identifier(Type::NAME, *((yyvsp[(1) - (7)].val))), new Identifier(Type::NAME, *((yyvsp[(1) - (7)].val))), (yyvsp[(3) - (7)].var_decl_list), (yyvsp[(6) - (7)].block));
        //delete $2;
    ;}
    break;

  case 43:
#line 227 "/Users/guoziyang/Documents/posfol1/posfol/parser/parser.y"
    {puts("PUBLIC");;}
    break;

  case 44:
#line 228 "/Users/guoziyang/Documents/posfol1/posfol/parser/parser.y"
    {puts("PRIVATE");;}
    break;

  case 45:
#line 232 "/Users/guoziyang/Documents/posfol1/posfol/parser/parser.y"
    {
        (yyval.interface_declaration) = new InterfaceDeclaration(new Identifier(Type::NAME, *((yyvsp[(2) - (6)].val))), (yyvsp[(4) - (6)].block));
        //delete $2;
    ;}
    break;

  case 46:
#line 239 "/Users/guoziyang/Documents/posfol1/posfol/parser/parser.y"
    {
        (yyval.block) = new Block();
    ;}
    break;

  case 48:
#line 246 "/Users/guoziyang/Documents/posfol1/posfol/parser/parser.y"
    {
        (yyvsp[(1) - (2)].block)->getStatementList()->push_back((yyvsp[(2) - (2)].statement));
    ;}
    break;

  case 49:
#line 249 "/Users/guoziyang/Documents/posfol1/posfol/parser/parser.y"
    {
        (yyval.block) = new Block();
        (yyval.block)->getStatementList()->push_back((yyvsp[(1) - (1)].statement));
    ;}
    break;

  case 50:
#line 256 "/Users/guoziyang/Documents/posfol1/posfol/parser/parser.y"
    {
        (yyval.statement) = new FunctionDeclaration((yyvsp[(1) - (6)].identifier), new Identifier(Type::NAME, *((yyvsp[(2) - (6)].val))), (yyvsp[(4) - (6)].var_decl_list));
    ;}
    break;

  case 51:
#line 262 "/Users/guoziyang/Documents/posfol1/posfol/parser/parser.y"
    {
        (yyval.function_declaration) = new FunctionDeclaration((yyvsp[(1) - (8)].identifier), new Identifier(Type::NAME, *((yyvsp[(2) - (8)].val))), (yyvsp[(4) - (8)].var_decl_list), (yyvsp[(7) - (8)].block));
        //delete $2;
        puts("finish function declaration");
    ;}
    break;

  case 52:
#line 280 "/Users/guoziyang/Documents/posfol1/posfol/parser/parser.y"
    {
        (yyval.block) = new Block();
    ;}
    break;

  case 53:
#line 283 "/Users/guoziyang/Documents/posfol1/posfol/parser/parser.y"
    {puts("stmts_nonempty");;}
    break;

  case 54:
#line 287 "/Users/guoziyang/Documents/posfol1/posfol/parser/parser.y"
    {
        (yyvsp[(1) - (2)].block)->getStatementList()->push_back((yyvsp[(2) - (2)].statement));
    ;}
    break;

  case 55:
#line 290 "/Users/guoziyang/Documents/posfol1/posfol/parser/parser.y"
    {
        (yyval.block) = new Block();
        (yyval.block)->getStatementList()->push_back((yyvsp[(1) - (1)].statement));
    ;}
    break;

  case 60:
#line 304 "/Users/guoziyang/Documents/posfol1/posfol/parser/parser.y"
    {(yyval.expression) = new AssignExpression((yyvsp[(1) - (3)].entity), 0, (yyvsp[(3) - (3)].expression));;}
    break;

  case 61:
#line 305 "/Users/guoziyang/Documents/posfol1/posfol/parser/parser.y"
    {(yyval.expression) = new AssignExpression((yyvsp[(1) - (3)].entity), 1, (yyvsp[(3) - (3)].expression));;}
    break;

  case 62:
#line 306 "/Users/guoziyang/Documents/posfol1/posfol/parser/parser.y"
    {(yyval.expression) = new AssignExpression((yyvsp[(1) - (3)].entity), 2, (yyvsp[(3) - (3)].expression));;}
    break;

  case 63:
#line 307 "/Users/guoziyang/Documents/posfol1/posfol/parser/parser.y"
    {(yyval.expression) = new AssignExpression((yyvsp[(1) - (3)].entity), 3, (yyvsp[(3) - (3)].expression));;}
    break;

  case 64:
#line 308 "/Users/guoziyang/Documents/posfol1/posfol/parser/parser.y"
    {(yyval.expression) = new AssignExpression((yyvsp[(1) - (3)].entity), 4, (yyvsp[(3) - (3)].expression));;}
    break;

  case 65:
#line 309 "/Users/guoziyang/Documents/posfol1/posfol/parser/parser.y"
    {(yyval.expression) = new AssignExpression((yyvsp[(1) - (3)].entity), 5, (yyvsp[(3) - (3)].expression));;}
    break;

  case 67:
#line 314 "/Users/guoziyang/Documents/posfol1/posfol/parser/parser.y"
    {(yyval.expression) = new BinaryOperator((yyvsp[(1) - (3)].expression), 0, (yyvsp[(3) - (3)].expression));;}
    break;

  case 69:
#line 319 "/Users/guoziyang/Documents/posfol1/posfol/parser/parser.y"
    {(yyval.expression) = new BinaryOperator((yyvsp[(1) - (3)].expression), 1, (yyvsp[(3) - (3)].expression));;}
    break;

  case 72:
#line 325 "/Users/guoziyang/Documents/posfol1/posfol/parser/parser.y"
    {(yyval.expression) = new BinaryOperator((yyvsp[(1) - (3)].expression), 2, (yyvsp[(3) - (3)].expression));;}
    break;

  case 73:
#line 326 "/Users/guoziyang/Documents/posfol1/posfol/parser/parser.y"
    {(yyval.expression) = new BinaryOperator((yyvsp[(1) - (3)].expression), 3, (yyvsp[(3) - (3)].expression));;}
    break;

  case 74:
#line 327 "/Users/guoziyang/Documents/posfol1/posfol/parser/parser.y"
    {(yyval.expression) = new BinaryOperator((yyvsp[(1) - (3)].expression), 4, (yyvsp[(3) - (3)].expression));;}
    break;

  case 75:
#line 328 "/Users/guoziyang/Documents/posfol1/posfol/parser/parser.y"
    {(yyval.expression) = new BinaryOperator((yyvsp[(1) - (3)].expression), 5, (yyvsp[(3) - (3)].expression));;}
    break;

  case 76:
#line 329 "/Users/guoziyang/Documents/posfol1/posfol/parser/parser.y"
    {(yyval.expression) = new BinaryOperator((yyvsp[(1) - (3)].expression), 6, (yyvsp[(3) - (3)].expression));;}
    break;

  case 77:
#line 330 "/Users/guoziyang/Documents/posfol1/posfol/parser/parser.y"
    {(yyval.expression) = new BinaryOperator((yyvsp[(1) - (3)].expression), 7, (yyvsp[(3) - (3)].expression));;}
    break;

  case 78:
#line 334 "/Users/guoziyang/Documents/posfol1/posfol/parser/parser.y"
    {(yyval.expression) = new BinaryOperator((yyvsp[(1) - (3)].expression), 8, (yyvsp[(3) - (3)].expression));;}
    break;

  case 79:
#line 335 "/Users/guoziyang/Documents/posfol1/posfol/parser/parser.y"
    {(yyval.expression) = new BinaryOperator((yyvsp[(1) - (3)].expression), 9, (yyvsp[(3) - (3)].expression));;}
    break;

  case 81:
#line 340 "/Users/guoziyang/Documents/posfol1/posfol/parser/parser.y"
    {(yyval.expression) = new BinaryOperator((yyvsp[(1) - (3)].expression), 10, (yyvsp[(3) - (3)].expression));;}
    break;

  case 82:
#line 341 "/Users/guoziyang/Documents/posfol1/posfol/parser/parser.y"
    {(yyval.expression) = new BinaryOperator((yyvsp[(1) - (3)].expression), 11, (yyvsp[(3) - (3)].expression));;}
    break;

  case 83:
#line 342 "/Users/guoziyang/Documents/posfol1/posfol/parser/parser.y"
    {(yyval.expression) = new BinaryOperator((yyvsp[(1) - (3)].expression), 12, (yyvsp[(3) - (3)].expression));;}
    break;

  case 86:
#line 348 "/Users/guoziyang/Documents/posfol1/posfol/parser/parser.y"
    {(yyval.expression) = new TypeConvertOperator((yyvsp[(2) - (4)].identifier), (yyvsp[(4) - (4)].expression));;}
    break;

  case 89:
#line 354 "/Users/guoziyang/Documents/posfol1/posfol/parser/parser.y"
    {
        (yyval.expression) = new ClassNewExpression(new Identifier(Type::NAME, *((yyvsp[(2) - (5)].val))), (yyvsp[(4) - (5)].expr_list));
    ;}
    break;

  case 91:
#line 358 "/Users/guoziyang/Documents/posfol1/posfol/parser/parser.y"
    {(yyval.expression) = (yyvsp[(2) - (3)].expression);;}
    break;

  case 92:
#line 359 "/Users/guoziyang/Documents/posfol1/posfol/parser/parser.y"
    {(yyval.expression) = new UnaryOperator(1, (yyvsp[(2) - (2)].expression));;}
    break;

  case 93:
#line 360 "/Users/guoziyang/Documents/posfol1/posfol/parser/parser.y"
    {(yyval.expression) = new UnaryOperator(0, (yyvsp[(2) - (2)].expression));;}
    break;

  case 94:
#line 364 "/Users/guoziyang/Documents/posfol1/posfol/parser/parser.y"
    {
        (yyval.entity) = new Entity(new Identifier(Type::NAME, *((yyvsp[(1) - (1)].val)))); 
        //delete $1;
    ;}
    break;

  case 95:
#line 368 "/Users/guoziyang/Documents/posfol1/posfol/parser/parser.y"
    {
        (yyval.entity) = new Entity((yyvsp[(1) - (3)].entity), new Identifier(Type::NAME, *((yyvsp[(3) - (3)].val)))); 
        //delete $3;
    ;}
    break;

  case 96:
#line 372 "/Users/guoziyang/Documents/posfol1/posfol/parser/parser.y"
    {(yyval.entity) = new Entity((yyvsp[(1) - (4)].entity), (yyvsp[(3) - (4)].expression));;}
    break;

  case 97:
#line 376 "/Users/guoziyang/Documents/posfol1/posfol/parser/parser.y"
    {
        (yyval.entity) = new Entity(new Identifier(Type::NAME, *((yyvsp[(1) - (1)].val)))); 
        //delete $1;
    ;}
    break;

  case 98:
#line 380 "/Users/guoziyang/Documents/posfol1/posfol/parser/parser.y"
    {
    (yyval.entity) = new Entity((yyvsp[(1) - (3)].entity), new Identifier(Type::NAME, *((yyvsp[(3) - (3)].val)))); 
        //delete $3;
    ;}
    break;

  case 99:
#line 384 "/Users/guoziyang/Documents/posfol1/posfol/parser/parser.y"
    {(yyval.entity) = new Entity((yyvsp[(1) - (4)].entity), (yyvsp[(3) - (4)].expression));;}
    break;

  case 100:
#line 385 "/Users/guoziyang/Documents/posfol1/posfol/parser/parser.y"
    {(yyval.entity) = new Entity((yyvsp[(1) - (4)].entity), (yyvsp[(3) - (4)].expr_list));;}
    break;

  case 101:
#line 389 "/Users/guoziyang/Documents/posfol1/posfol/parser/parser.y"
    {
        (yyval.expr_list) = new std::vector<Expression*>();
        (yyval.expr_list)->push_back(new Identifier(Type::NAME, *((yyvsp[(1) - (4)].val))));
        (yyval.expr_list)->push_back((yyvsp[(3) - (4)].expression));
        //delete $1;
    ;}
    break;

  case 102:
#line 395 "/Users/guoziyang/Documents/posfol1/posfol/parser/parser.y"
    {
        (yyvsp[(1) - (4)].expr_list)->push_back((yyvsp[(3) - (4)].expression));
    ;}
    break;

  case 103:
#line 401 "/Users/guoziyang/Documents/posfol1/posfol/parser/parser.y"
    {
        {(yyval.entity) = new Entity((yyvsp[(1) - (4)].entity), (yyvsp[(3) - (4)].expr_list));}
    ;}
    break;

  case 104:
#line 407 "/Users/guoziyang/Documents/posfol1/posfol/parser/parser.y"
    {
        (yyval.identifier) = new Identifier(Type::VALUE, *((yyvsp[(1) - (1)].val))); 
        //delete $1;
    ;}
    break;

  case 105:
#line 411 "/Users/guoziyang/Documents/posfol1/posfol/parser/parser.y"
    {
        (yyval.identifier) = new Identifier(Type::VALUE, *((yyvsp[(1) - (1)].val))); 
        //delete $1;
    ;}
    break;

  case 106:
#line 415 "/Users/guoziyang/Documents/posfol1/posfol/parser/parser.y"
    {
        (yyval.identifier) = new Identifier(Type::VALUE, *((yyvsp[(1) - (1)].val))); 
        //delete $1;
    ;}
    break;

  case 107:
#line 419 "/Users/guoziyang/Documents/posfol1/posfol/parser/parser.y"
    {
        (yyval.identifier) = new Identifier(Type::VALUE, *((yyvsp[(1) - (1)].val))); 
        //delete $1;
    ;}
    break;

  case 108:
#line 423 "/Users/guoziyang/Documents/posfol1/posfol/parser/parser.y"
    {
        (yyval.identifier) = new Identifier(Type::VALUE, *((yyvsp[(1) - (1)].val))); 
        //delete $1;
    ;}
    break;

  case 109:
#line 430 "/Users/guoziyang/Documents/posfol1/posfol/parser/parser.y"
    {
        (yyval.expr_list) = new std::vector<Expression*>();
    ;}
    break;

  case 111:
#line 437 "/Users/guoziyang/Documents/posfol1/posfol/parser/parser.y"
    {
        (yyvsp[(1) - (3)].expr_list)->push_back((yyvsp[(3) - (3)].expression));
    ;}
    break;

  case 112:
#line 440 "/Users/guoziyang/Documents/posfol1/posfol/parser/parser.y"
    {
        (yyval.expr_list) = new std::vector<Expression*>();
        (yyval.expr_list)->push_back((yyvsp[(1) - (1)].expression));
    ;}
    break;

  case 117:
#line 455 "/Users/guoziyang/Documents/posfol1/posfol/parser/parser.y"
    {
        (yyval.if_statement) = new IfStatement((yyvsp[(3) - (8)].expression), (yyvsp[(6) - (8)].block), (yyvsp[(8) - (8)].block));
    ;}
    break;

  case 118:
#line 461 "/Users/guoziyang/Documents/posfol1/posfol/parser/parser.y"
    {
        (yyval.block) = (yyvsp[(3) - (4)].block);
    ;}
    break;

  case 119:
#line 464 "/Users/guoziyang/Documents/posfol1/posfol/parser/parser.y"
    {
        (yyval.block) = nullptr;
    ;}
    break;

  case 120:
#line 470 "/Users/guoziyang/Documents/posfol1/posfol/parser/parser.y"
    {
        (yyval.while_statement) = new WhileStatement((yyvsp[(3) - (7)].expression), (yyvsp[(6) - (7)].block));
    ;}
    break;

  case 121:
#line 476 "/Users/guoziyang/Documents/posfol1/posfol/parser/parser.y"
    {
        (yyval.for_statement) = new ForStatement((yyvsp[(3) - (11)].expression), (yyvsp[(5) - (11)].expression), (yyvsp[(7) - (11)].expression), (yyvsp[(10) - (11)].block));
    ;}
    break;

  case 122:
#line 482 "/Users/guoziyang/Documents/posfol1/posfol/parser/parser.y"
    {
        (yyval.return_statement) = new ReturnStatement((yyvsp[(2) - (3)].expression));
    ;}
    break;

  case 123:
#line 485 "/Users/guoziyang/Documents/posfol1/posfol/parser/parser.y"
    {
        (yyval.return_statement) = new ReturnStatement();
    ;}
    break;

  case 124:
#line 491 "/Users/guoziyang/Documents/posfol1/posfol/parser/parser.y"
    {
        (yyval.io_stmt) = new IOStatement((yyvsp[(3) - (5)].entity));
    ;}
    break;

  case 125:
#line 494 "/Users/guoziyang/Documents/posfol1/posfol/parser/parser.y"
    {
        (yyval.io_stmt) = new IOStatement((yyvsp[(3) - (5)].expression));
    ;}
    break;

  case 126:
#line 497 "/Users/guoziyang/Documents/posfol1/posfol/parser/parser.y"
    {
        (yyval.io_stmt) = new IOStatement(*((yyvsp[(3) - (5)].val)));
    ;}
    break;


/* Line 1267 of yacc.c.  */
#line 2357 "y.tab.cpp"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;


  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
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

  /* Else will try to reuse look-ahead token after shifting the error
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

  /* Do not reclaim the symbols of the rule which action triggered
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
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
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

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;


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

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
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
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


#line 502 "/Users/guoziyang/Documents/posfol1/posfol/parser/parser.y"


Block* buildTree() {
    yyparse();
    return programBlock;
}
