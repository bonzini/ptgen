/* A Bison parser, made from parse.yy, by GNU bison 1.49b.  */

/* Skeleton parser for Yacc-like parsing with Bison,
   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002 Free Software Foundation, Inc.

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
   Foundation, Inc., 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA.  */

/* As a special exception, when this file is copied by Bison into a
   Bison output file, you may use that output file without restriction.
   This special exception was added by the Free Software Foundation
   in version 1.24 of Bison.  */

/* Written by Richard Stallman by simplifying the original so called
   ``semantic'' parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON	1

/* Pure parsers.  */
#define YYPURE	0

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */
#line 1 "parse.yy"

// Procedural Texture Generator
// Paolo Bonzini
// esame di Elaborazione e Trasmissione delle Immagini
//
// Parser

#include "ptgen.h"

#define YYERROR_VERBOSE 1

static void yyerror (const char *s);

int errors = 0;



/* Tokens.  */
#ifndef YYTOKENTYPE
# if defined (__STDC__) || defined (__cplusplus)
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     LET_ = 258,
     EQ_ = 259,
     NE_ = 260,
     LE_ = 261,
     GE_ = 262,
     ASSIGN_ = 263,
     PERLIN_ = 264,
     NOISE_ = 265,
     CONVOLVE_ = 266,
     APPLY_ = 267,
     TO_ = 268,
     CREATE_ = 269,
     GREYSCALE_ = 270,
     RED_ = 271,
     GREEN_ = 272,
     BLUE_ = 273,
     IMAGE_ = 274,
     SCALE_ = 275,
     BIAS_ = 276,
     SPLINE_ = 277,
     MAP_ = 278,
     WITH_ = 279,
     IF_ = 280,
     DO_ = 281,
     WHILE_ = 282,
     ELSE_ = 283,
     THEN_ = 284,
     AND_ = 285,
     OR_ = 286,
     NOT_ = 287,
     XOR_ = 288,
     X_ = 289,
     Y_ = 290,
     FROM_ = 291,
     RANGE_ = 292,
     OUTPUT_ = 293,
     OPERATION_ = 294,
     BLEND_ = 295,
     REPLACE_ = 296,
     ADD_ = 297,
     SUBTRACT_ = 298,
     MULTIPLY_ = 299,
     SCREEN_ = 300,
     COLOR_ = 301,
     HUE_ = 302,
     VALUE_ = 303,
     SATURATION_ = 304,
     DISSOLVE_ = 305,
     DIFFERENCE_ = 306,
     OVERLAY_ = 307,
     LIGHTEN_ = 308,
     DARKEN_ = 309,
     OPACITY_ = 310,
     KEYWORD_ = 311,
     BUILTIN_FUNC1_ = 312,
     BUILTIN_FUNC2_ = 313,
     DEF_ID_ = 314,
     UNDEF_ID_ = 315,
     IMAGE_DEF_ = 316,
     VECTOR_DEF_ = 317,
     MATRIX_DEF_ = 318,
     NUMBER_DEF_ = 319,
     FUNC_DEF_ = 320,
     NUMBER_ = 321,
     INTEGER_ = 322,
     UMINUS = 323
   };
# endif
  /* POSIX requires `int' for tokens in interfaces.  */
# define YYTOKENTYPE int
#endif /* !YYTOKENTYPE */
#define LET_ 258
#define EQ_ 259
#define NE_ 260
#define LE_ 261
#define GE_ 262
#define ASSIGN_ 263
#define PERLIN_ 264
#define NOISE_ 265
#define CONVOLVE_ 266
#define APPLY_ 267
#define TO_ 268
#define CREATE_ 269
#define GREYSCALE_ 270
#define RED_ 271
#define GREEN_ 272
#define BLUE_ 273
#define IMAGE_ 274
#define SCALE_ 275
#define BIAS_ 276
#define SPLINE_ 277
#define MAP_ 278
#define WITH_ 279
#define IF_ 280
#define DO_ 281
#define WHILE_ 282
#define ELSE_ 283
#define THEN_ 284
#define AND_ 285
#define OR_ 286
#define NOT_ 287
#define XOR_ 288
#define X_ 289
#define Y_ 290
#define FROM_ 291
#define RANGE_ 292
#define OUTPUT_ 293
#define OPERATION_ 294
#define BLEND_ 295
#define REPLACE_ 296
#define ADD_ 297
#define SUBTRACT_ 298
#define MULTIPLY_ 299
#define SCREEN_ 300
#define COLOR_ 301
#define HUE_ 302
#define VALUE_ 303
#define SATURATION_ 304
#define DISSOLVE_ 305
#define DIFFERENCE_ 306
#define OVERLAY_ 307
#define LIGHTEN_ 308
#define DARKEN_ 309
#define OPACITY_ 310
#define KEYWORD_ 311
#define BUILTIN_FUNC1_ 312
#define BUILTIN_FUNC2_ 313
#define DEF_ID_ 314
#define UNDEF_ID_ 315
#define IMAGE_DEF_ 316
#define VECTOR_DEF_ 317
#define MATRIX_DEF_ 318
#define NUMBER_DEF_ 319
#define FUNC_DEF_ 320
#define NUMBER_ 321
#define INTEGER_ 322
#define UMINUS 323




/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

#ifndef YYSTYPE
#line 28 "parse.yy"
typedef union {
  ptgen_object *obj;
  predicate *pred;
  expression *expr;
  seq *seq_expr;
  ptgen_function *fun;
  expr_vector *vec;
  expr_matrix *matr;
  numeric_vector *nvec;
  numeric_matrix *nmatr;
  image *img;
  interpolator *interp;
  int argcount;
  int def_id;
  string *undef_id_name;
  float real;
  unary_operator::op un_op_id;
  binary_operator::op bin_op_id;
} yystype;
/* Line 188 of /usr/share/bison/yacc.c.  */
#line 249 "parse.cc"
# define YYSTYPE yystype
# define YYSTYPE_IS_TRIVIAL 1
#endif

#ifndef YYLTYPE
typedef struct yyltype
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
} yyltype;
# define YYLTYPE yyltype
# define YYLTYPE_IS_TRIVIAL 1
#endif

/* Copy the second part of user declarations.  */


/* Line 208 of /usr/share/bison/yacc.c.  */
#line 270 "parse.cc"

#if ! defined (yyoverflow) || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# if YYSTACK_USE_ALLOCA
#  define YYSTACK_ALLOC alloca
# else
#  ifndef YYSTACK_USE_ALLOCA
#   if defined (alloca) || defined (_ALLOCA_H)
#    define YYSTACK_ALLOC alloca
#   else
#    ifdef __GNUC__
#     define YYSTACK_ALLOC __builtin_alloca
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning. */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
# else
#  if defined (__STDC__) || defined (__cplusplus)
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   define YYSIZE_T size_t
#  endif
#  define YYSTACK_ALLOC malloc
#  define YYSTACK_FREE free
# endif
#endif /* ! defined (yyoverflow) || YYERROR_VERBOSE */


#if (! defined (yyoverflow) \
     && (! defined (__cplusplus) \
	 || (YYLTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  short yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAX (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (short) + sizeof (YYSTYPE))				\
      + YYSTACK_GAP_MAX)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  register YYSIZE_T yyi;		\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];	\
	}					\
      while (0)
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
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAX;	\
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (0)

#endif

/* YYFINAL -- State number of the termination state. */
#define YYFINAL  3
#define YYLAST   494

/* YYNTOKENS -- Number of terminals. */
#define YYNTOKENS  83
/* YYNNTS -- Number of nonterminals. */
#define YYNNTS  68
/* YYNRULES -- Number of rules. */
#define YYNRULES  149
/* YYNRULES -- Number of states. */
#define YYNSTATES  280

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   323

#define YYTRANSLATE(X) \
  ((unsigned)(X) <= YYMAXUTOK ? yytranslate[X] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const unsigned char yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      76,    77,    72,    70,    78,    71,     2,    73,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    75,
      68,    82,    69,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    79,     2,    80,     2,     2,     2,     2,     2,     2,
       2,     2,    81,     2,     2,     2,     2,     2,     2,     2,
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
      65,    66,    67,    74
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const unsigned short yyprhs[] =
{
       0,     0,     3,     7,     8,    10,    13,    14,    15,    16,
      23,    24,    26,    28,    30,    32,    34,    36,    40,    42,
      46,    50,    54,    58,    60,    62,    66,    70,    74,    78,
      85,    90,    92,    94,    97,    99,   106,   111,   116,   120,
     124,   128,   131,   135,   139,   143,   147,   151,   155,   157,
     159,   163,   167,   169,   173,   177,   181,   185,   187,   191,
     195,   198,   200,   202,   205,   210,   214,   216,   220,   221,
     229,   231,   233,   235,   237,   238,   240,   242,   246,   248,
     249,   253,   255,   256,   260,   261,   265,   266,   270,   272,
     276,   280,   282,   284,   286,   288,   290,   292,   294,   296,
     297,   298,   306,   307,   309,   311,   314,   317,   320,   323,
     324,   331,   332,   344,   345,   355,   356,   365,   370,   380,
     381,   393,   394,   402,   403,   405,   406,   410,   412,   419,
     420,   426,   427,   435,   436,   439,   442,   445,   448,   451,
     454,   457,   460,   464,   468,   472,   476,   479,   482,   485
};

/* YYRHS -- A `-1'-separated list of the rules' RHS. */
static const short yyrhs[] =
{
      84,     0,    -1,    86,   125,    85,    -1,    -1,    75,    -1,
      86,    87,    -1,    -1,    -1,    -1,     3,    88,    90,    91,
      89,    75,    -1,    -1,   101,    -1,   104,    -1,    93,    -1,
     124,    -1,   109,    -1,    60,    -1,    92,     8,    95,    -1,
      95,    -1,    59,     8,    94,    -1,    92,     8,    94,    -1,
      76,    94,    77,    -1,    76,    99,    77,    -1,    64,    -1,
      98,    -1,    95,    70,    95,    -1,    95,    71,    95,    -1,
      95,    72,    95,    -1,    95,    73,    95,    -1,    58,    76,
      95,    78,    95,    77,    -1,    57,    76,    95,    77,    -1,
      59,    -1,    92,    -1,    71,    95,    -1,    96,    -1,    25,
      97,    29,    95,    28,    95,    -1,    27,    97,    26,    95,
      -1,   110,    76,   100,    77,    -1,    97,    30,    97,    -1,
      97,    31,    97,    -1,    97,    33,    97,    -1,    32,    97,
      -1,    95,     5,    95,    -1,    95,     4,    95,    -1,    95,
       7,    95,    -1,    95,     6,    95,    -1,    95,    68,    95,
      -1,    95,    69,    95,    -1,    66,    -1,    67,    -1,    94,
      75,    94,    -1,    99,    75,    94,    -1,    95,    -1,   100,
      78,    95,    -1,    92,     8,   102,    -1,    79,   103,    80,
      -1,   103,    78,    95,    -1,    95,    -1,    92,     8,   105,
      -1,    79,   106,    80,    -1,   106,   102,    -1,   102,    -1,
      23,    -1,    22,    23,    -1,   107,   115,    13,   115,    -1,
      92,     8,   111,    -1,   111,    -1,    76,   110,    77,    -1,
      -1,    81,   112,    76,   113,    77,    82,    94,    -1,    65,
      -1,   108,    -1,    57,    -1,    58,    -1,    -1,   114,    -1,
      92,    -1,   114,    78,    92,    -1,    62,    -1,    -1,   116,
      90,   102,    -1,    63,    -1,    -1,   118,    90,   105,    -1,
      -1,   120,    90,   111,    -1,    -1,   122,    90,    94,    -1,
      61,    -1,    76,   125,    77,    -1,    92,     8,   125,    -1,
     126,    -1,   123,    -1,   128,    -1,   133,    -1,   138,    -1,
     140,    -1,   145,    -1,   147,    -1,    -1,    -1,    11,   129,
     127,   123,    24,   117,   130,    -1,    -1,   131,    -1,   132,
      -1,   131,   132,    -1,   132,   131,    -1,    20,   121,    -1,
      21,   121,    -1,    -1,    12,   119,   134,   127,    13,   123,
      -1,    -1,    12,    16,   119,    17,   119,    18,   119,   135,
     127,    13,   123,    -1,    -1,    12,    34,   119,    35,   119,
     136,   127,    13,   123,    -1,    -1,    12,   123,   137,   127,
      13,   123,   149,   150,    -1,    14,    19,    36,   119,    -1,
      14,    19,    36,    16,   119,    17,   119,    18,   119,    -1,
      -1,    14,    19,    36,    16,   123,    17,   123,    18,   123,
     139,   127,    -1,    -1,    14,     9,    10,   141,   127,   142,
     143,    -1,    -1,   131,    -1,    -1,    38,    37,   144,    -1,
     119,    -1,    16,   119,    17,   119,    18,   119,    -1,    -1,
      14,    10,   146,   127,   143,    -1,    -1,    14,    15,    19,
      36,   148,   127,   123,    -1,    -1,    39,    40,    -1,    39,
      50,    -1,    39,    42,    -1,    39,    43,    -1,    39,    51,
      -1,    39,    44,    -1,    39,    45,    -1,    39,    52,    -1,
      39,    41,    46,    -1,    39,    41,    47,    -1,    39,    41,
      48,    -1,    39,    41,    49,    -1,    39,    53,    -1,    39,
      54,    -1,    55,   121,    -1,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const unsigned short yyrline[] =
{
       0,   134,   134,   145,   146,   150,   152,   156,   156,   155,
     163,   166,   168,   169,   170,   171,   204,   208,   218,   221,
     223,   227,   230,   232,   234,   236,   238,   240,   242,   244,
     246,   248,   250,   252,   254,   256,   258,   262,   273,   276,
     278,   280,   282,   284,   286,   288,   290,   292,   296,   299,
     303,   306,   310,   313,   325,   334,   339,   342,   354,   363,
     367,   370,   381,   385,   391,   426,   432,   435,   441,   439,
     444,   446,   448,   450,   455,   457,   461,   463,   470,   472,
     472,   475,   477,   477,   481,   480,   485,   484,   488,   490,
     511,   517,   519,   522,   524,   525,   526,   527,   528,   534,
     539,   537,   552,   553,   554,   555,   556,   559,   564,   571,
     569,   586,   584,   604,   603,   620,   619,   627,   638,   653,
     652,   662,   660,   668,   670,   674,   676,   680,   689,   705,
     703,   712,   710,   718,   721,   723,   725,   727,   729,   731,
     733,   735,   737,   739,   741,   743,   745,   747,   751,   759
};
#endif

#if YYDEBUG || YYERROR_VERBOSE
/* YYTNME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals. */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "\"let\"", "\"==\"", "\"!=\"", "\"<=\"", 
  "\">=\"", "\":=\"", "\"perlin\"", "\"noise\"", "\"convolve\"", 
  "\"apply\"", "\"to\"", "\"create\"", "\"greyscale\"", "\"red\"", 
  "\"green\"", "\"blue\"", "\"image\"", "\"scale\"", "\"bias\"", 
  "\"spline\"", "\"map\"", "\"with\"", "\"if\"", "\"do\"", "\"while\"", 
  "\"else\"", "\"then\"", "\"and\"", "\"or\"", "\"not\"", "\"xor\"", 
  "\"x\"", "\"y\"", "\"from\"", "\"range\"", "\"output\"", 
  "\"operation\"", "\"blend\"", "\"replace\"", "\"add\"", "\"subtract\"", 
  "\"multiply\"", "\"screen\"", "\"color\"", "\"hue\"", "\"value\"", 
  "\"saturation\"", "\"dissolve\"", "\"difference\"", "\"overlay\"", 
  "\"lighten\"", "\"darken\"", "\"opacity\"", "\"unrecognized keyword\"", 
  "\"builtin 1-argument function\"", "\"builtin 2-argument function\"", 
  "DEF_ID_", "\"undefined variable\"", "IMAGE_DEF_", "VECTOR_DEF_", 
  "MATRIX_DEF_", "NUMBER_DEF_", "FUNC_DEF_", "NUMBER_", "INTEGER_", "'<'", 
  "'>'", "'+'", "'-'", "'*'", "'/'", "UMINUS", "';'", "'('", "')'", "','", 
  "'['", "']'", "'f'", "'='", "$accept", "program", "opt_semicolon", 
  "declarations", "decl", "@1", "@2", "scope_pushed", "decl.1", 
  "undef_id", "value_decl", "number", "expression", "func_eval", 
  "predicate", "number_literal", "seq", "arglist", "vector_decl", 
  "vector", "expressions", "matrix_decl", "matrix", "vectors", 
  "interp_type", "interp", "function_decl", "function_with_parens", 
  "function", "@3", "argdecl", "argdecl.1", "vector_param", "@4", 
  "matrix_param", "@5", "function_param", "@6", "number_param", "@7", 
  "image_param", "image_decl", "image", "image_command", "image_pushed", 
  "convolve_command", "@8", "convolve_params", "scale", "bias", 
  "apply_command", "@9", "@10", "@11", "@12", "create_command", "@13", 
  "turbulence_command", "@14", "opt_scale", "out_range", 
  "out_range_function", "noise_command", "@15", "greyscale_command", 
  "@16", "operation", "opt_opacity", 0
};
#endif

/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const unsigned short yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,    60,    62,
      43,    45,    42,    47,   323,    59,    40,    41,    44,    91,
      93,   102,    61
};

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const unsigned char yyr1[] =
{
       0,    83,    84,    85,    85,    86,    86,    88,    89,    87,
      90,    91,    91,    91,    91,    91,    92,    93,    94,    94,
      94,    95,    95,    95,    95,    95,    95,    95,    95,    95,
      95,    95,    95,    95,    95,    95,    95,    96,    97,    97,
      97,    97,    97,    97,    97,    97,    97,    97,    98,    98,
      99,    99,   100,   100,   101,   102,   103,   103,   104,   105,
     106,   106,   107,   107,   108,   109,   110,   110,   112,   111,
     111,   111,   111,   111,   113,   113,   114,   114,   115,   116,
     115,   117,   118,   117,   120,   119,   122,   121,   123,   123,
     124,   125,   125,   126,   126,   126,   126,   126,   126,   127,
     129,   128,   130,   130,   130,   130,   130,   131,   132,   134,
     133,   135,   133,   136,   133,   137,   133,   138,   138,   139,
     138,   141,   140,   142,   142,   143,   143,   144,   144,   146,
     145,   148,   147,   149,   149,   149,   149,   149,   149,   149,
     149,   149,   149,   149,   149,   149,   149,   149,   150,   150
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const unsigned char yyr2[] =
{
       0,     2,     3,     0,     1,     2,     0,     0,     0,     6,
       0,     1,     1,     1,     1,     1,     1,     3,     1,     3,
       3,     3,     3,     1,     1,     3,     3,     3,     3,     6,
       4,     1,     1,     2,     1,     6,     4,     4,     3,     3,
       3,     2,     3,     3,     3,     3,     3,     3,     1,     1,
       3,     3,     1,     3,     3,     3,     3,     1,     3,     3,
       2,     1,     1,     2,     4,     3,     1,     3,     0,     7,
       1,     1,     1,     1,     0,     1,     1,     3,     1,     0,
       3,     1,     0,     3,     0,     3,     0,     3,     1,     3,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       0,     7,     0,     1,     1,     2,     2,     2,     2,     0,
       6,     0,    11,     0,     9,     0,     8,     4,     9,     0,
      11,     0,     7,     0,     1,     0,     3,     1,     6,     0,
       5,     0,     7,     0,     2,     2,     2,     2,     2,     2,
       2,     2,     3,     3,     3,     3,     2,     2,     2,     0
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const unsigned char yydefact[] =
{
       6,     0,     0,     1,     7,   100,    84,     0,    88,     0,
       5,    92,     3,    91,    93,    94,    95,    96,    97,    98,
      10,    99,    84,    84,   109,    10,   115,     0,   129,     0,
       0,     0,     4,     2,     0,     0,     0,     0,    99,     0,
      99,   121,    99,     0,    84,    89,    16,     8,     0,    13,
      11,    12,    15,    14,     0,    84,    84,     0,     0,    62,
      72,    73,    70,    68,    79,    71,    85,     0,    99,   125,
     131,    84,   117,     0,     0,    82,     0,   113,     0,    63,
       0,    78,     0,    10,     0,   123,     0,   130,    99,     0,
       0,     9,     0,     0,    72,    73,    31,    23,    48,    49,
       0,     0,     0,    32,    17,    34,    24,    54,    58,     0,
      65,    90,    81,   102,    10,    84,    99,   110,    74,    79,
       0,   133,    86,   124,   125,    84,     0,    84,     0,     0,
       0,     0,     0,    66,     0,     0,     0,    33,    31,    32,
       0,    18,     0,     0,     0,    57,    61,     0,     0,     0,
       0,     0,     0,     0,    86,   101,   103,   104,     0,   111,
       0,    76,     0,    75,    64,    80,     0,   149,   107,    10,
     122,    84,   127,   126,   132,     0,     0,    41,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    21,     0,    22,    67,     0,    55,
      59,    60,    25,    26,    27,    28,    52,     0,   108,   105,
     106,     0,    83,    99,     0,     0,     0,   134,     0,   136,
     137,   139,   140,   135,   138,   141,   146,   147,    86,   116,
       0,     0,    84,     0,    43,    42,    45,    44,    46,    47,
       0,    38,    39,    40,    36,    30,     0,    19,    20,    50,
      51,    56,    37,     0,     0,   114,     0,    77,   142,   143,
     144,   145,   148,    87,    84,   118,   119,     0,     0,    53,
       0,    69,     0,    99,    35,    29,   112,    84,   120,   128
};

/* YYDEFGOTO[NTERM-NUM]. */
static const short yydefgoto[] =
{
      -1,     1,    33,     2,    10,    20,    73,    34,    47,   103,
      49,   140,   141,   105,   132,   106,   142,   207,    50,   146,
     147,    51,   108,   148,    64,    65,    52,   109,   133,    80,
     162,   163,    82,    83,   113,   114,    24,    25,   168,   169,
      11,    53,    31,    13,    35,    14,    21,   155,   123,   157,
      15,    38,   213,   116,    40,    16,   273,    17,    68,   124,
      87,   173,    18,    42,    19,    88,   167,   229
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -175
static const short yypact[] =
{
    -175,    26,    13,  -175,  -175,  -175,    57,    21,  -175,     1,
    -175,  -175,   -43,  -175,  -175,  -175,  -175,  -175,  -175,  -175,
    -175,  -175,  -175,  -175,  -175,  -175,  -175,    47,  -175,    35,
      28,    -1,  -175,  -175,    19,   -33,    73,    60,  -175,    70,
    -175,  -175,  -175,    63,    89,  -175,  -175,  -175,   126,  -175,
    -175,  -175,  -175,  -175,    84,  -175,  -175,   129,   137,  -175,
    -175,  -175,  -175,  -175,    87,  -175,  -175,   151,  -175,   128,
    -175,   -33,  -175,    92,   238,   105,   156,  -175,   -33,  -175,
      99,  -175,   163,  -175,   -33,   159,   143,  -175,  -175,   164,
     173,  -175,   346,   346,   115,   116,  -175,  -175,  -175,  -175,
     393,   299,   366,  -175,    53,  -175,  -175,  -175,  -175,   117,
     118,  -175,  -175,    65,  -175,  -175,  -175,  -175,    19,    87,
     119,   157,  -175,  -175,   128,   183,   -33,  -175,   -33,   346,
     413,    42,    30,  -175,    11,   393,   393,  -175,   193,   194,
      32,    53,    44,   -38,   393,    53,  -175,    18,    37,   393,
     393,   393,   393,   393,  -175,  -175,   182,   159,   125,  -175,
     192,  -175,   130,   131,  -175,  -175,   103,   155,  -175,  -175,
    -175,  -175,  -175,  -175,  -175,   188,   195,  -175,   393,   393,
     393,   393,   393,   393,   393,   346,   346,   346,   393,   100,
      -3,   413,   413,   413,  -175,   413,  -175,  -175,   393,  -175,
    -175,  -175,    68,    68,  -175,  -175,    53,    81,  -175,  -175,
    -175,   119,  -175,  -175,   -33,   132,    19,  -175,    90,  -175,
    -175,  -175,  -175,  -175,  -175,  -175,  -175,  -175,  -175,  -175,
     413,   198,  -175,   -33,    53,    53,    53,    53,    53,    53,
      59,  -175,   186,   186,    53,  -175,   393,  -175,  -175,  -175,
    -175,    53,  -175,   393,   199,  -175,   413,  -175,  -175,  -175,
    -175,  -175,  -175,  -175,  -175,  -175,  -175,   393,   112,    53,
     -33,  -175,   200,  -175,    53,  -175,  -175,  -175,  -175,  -175
};

/* YYPGOTO[NTERM-NUM].  */
static const short yypgoto[] =
{
    -175,  -175,  -175,  -175,  -175,  -175,  -175,   -17,  -175,   -30,
    -175,  -174,    95,  -175,   -84,  -175,  -175,  -175,  -175,   -68,
    -175,  -175,    61,  -175,  -175,  -175,  -175,   -79,   -19,  -175,
    -175,  -175,    98,  -175,  -175,  -175,   -21,  -175,  -144,  -175,
      -6,  -175,     9,  -175,   -35,  -175,  -175,  -175,   -99,    64,
    -175,  -175,  -175,  -175,  -175,  -175,  -175,  -175,  -175,  -175,
      97,  -175,  -175,  -175,  -175,  -175,  -175,  -175
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.  */
#define YYTABLE_NINF -176
static const short yytable[] =
{
      26,    36,    37,    57,    48,    67,   107,    69,    39,   134,
     208,    12,     5,     6,   156,     7,     4,   247,   248,   249,
      66,   250,   143,    72,     5,     6,     3,     7,     8,    54,
      27,    28,    32,    85,    76,    77,    29,   188,   153,   197,
      30,   185,   186,     9,   187,   177,   178,   179,   180,   181,
      89,   143,   165,   126,    43,   110,   263,    41,   210,   184,
     185,   186,     8,   187,    44,    90,   120,   149,   150,   151,
     152,   139,   117,    22,     8,   246,    45,     9,   121,    46,
     201,   160,   271,   111,   262,   122,   154,   267,   161,     9,
      55,    23,    58,    59,   159,    56,   198,   158,   199,    70,
     139,   241,   242,   243,   172,    71,   175,   193,    75,   194,
     182,   183,   149,   150,   151,   152,   144,   200,     8,   195,
     174,   196,   176,   149,   150,   151,   152,    60,    61,   149,
     150,   151,   152,     9,    74,    62,   258,   259,   260,   261,
     151,   152,    78,   217,   218,   219,   220,   221,   222,    81,
     231,    63,   230,   223,   224,   225,   226,   227,   252,   253,
      79,   139,   139,   139,    84,   139,    86,    91,   112,   104,
     149,   150,   151,   152,   115,   118,   119,   245,   254,   122,
     125,   127,   149,   150,   151,   152,   257,   131,   131,   275,
     128,   135,   136,   153,   -66,   137,   166,   145,   144,   171,
     139,   191,   192,   154,   211,   214,   232,   215,   255,   216,
     228,   265,   270,   233,   256,   264,   185,   164,   277,   212,
     209,   170,     0,     0,   131,     0,   139,   266,     0,     0,
     189,   190,     0,     0,     0,     0,     0,     0,   278,   145,
       0,     0,     0,   272,   202,   203,   204,   205,   206,     5,
       6,     0,     7,     0,     0,     0,   279,     0,     0,     0,
      58,    59,     0,    92,   276,    93,     0,     0,     0,     0,
       0,     0,     0,   234,   235,   236,   237,   238,   239,   240,
     131,   131,   131,   244,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   251,     0,    94,    95,    96,    46,     8,
       0,     0,    97,    62,    98,    99,     0,     0,     0,   100,
       5,     6,     0,     7,   101,     0,     0,   102,     0,    63,
       0,    58,    59,     0,    92,     0,    93,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   268,     0,     0,     0,     0,     0,     0,   269,     0,
       0,     0,     0,     0,     0,     0,    94,    95,   138,    46,
       8,     0,   274,    97,    62,    98,    99,     0,    58,    59,
     100,    92,     0,    93,     0,   101,     0,     0,   129,     0,
      63,     0,     0,     0,     0,     0,     0,     0,    58,    59,
       0,    92,     0,    93,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    94,    95,    96,    46,     0,     0,     0,
      97,    62,    98,    99,     0,    58,    59,   100,    92,     0,
      93,     0,   130,    94,    95,    96,    46,    63,     0,     0,
      97,    62,    98,    99,     0,    58,    59,   100,    92,     0,
      93,     0,   130,     0,     0,   144,     0,    63,     0,     0,
      94,    95,    96,    46,     0,     0,     0,    97,    62,    98,
      99,     0,     0,     0,   100,     0,     0,     0,     0,   130,
      94,    95,   138,    46,    63,     0,     0,    97,    62,    98,
      99,     0,     0,     0,   100,     0,     0,     0,     0,   130,
       0,     0,     0,     0,    63
};

static const short yycheck[] =
{
       6,    22,    23,    38,    34,    40,    74,    42,    25,    93,
     154,     2,    11,    12,   113,    14,     3,   191,   192,   193,
      39,   195,   101,    44,    11,    12,     0,    14,    61,    35,
       9,    10,    75,    68,    55,    56,    15,    26,    76,    77,
      19,    30,    31,    76,    33,   129,     4,     5,     6,     7,
      71,   130,   120,    88,    19,    74,   230,    10,   157,    29,
      30,    31,    61,    33,    36,    71,    83,    70,    71,    72,
      73,   101,    78,    16,    61,    78,    77,    76,    84,    60,
     148,   116,   256,    74,   228,    20,    21,    28,   118,    76,
      17,    34,    22,    23,   115,    35,    78,   114,    80,    36,
     130,   185,   186,   187,   125,    16,   127,    75,    24,    77,
      68,    69,    70,    71,    72,    73,    79,    80,    61,    75,
     126,    77,   128,    70,    71,    72,    73,    57,    58,    70,
      71,    72,    73,    76,     8,    65,    46,    47,    48,    49,
      72,    73,    13,    40,    41,    42,    43,    44,    45,    62,
     171,    81,   169,    50,    51,    52,    53,    54,    77,    78,
      23,   191,   192,   193,    13,   195,    38,    75,    63,    74,
      70,    71,    72,    73,    18,    76,    13,    77,   213,    20,
      37,    17,    70,    71,    72,    73,   216,    92,    93,    77,
      17,    76,    76,    76,    76,   100,    39,   102,    79,    16,
     230,     8,     8,    21,    79,    13,    18,    77,   214,    78,
      55,   232,    13,    18,    82,    17,    30,   119,    18,   158,
     156,   124,    -1,    -1,   129,    -1,   256,   233,    -1,    -1,
     135,   136,    -1,    -1,    -1,    -1,    -1,    -1,   273,   144,
      -1,    -1,    -1,   264,   149,   150,   151,   152,   153,    11,
      12,    -1,    14,    -1,    -1,    -1,   277,    -1,    -1,    -1,
      22,    23,    -1,    25,   270,    27,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   178,   179,   180,   181,   182,   183,   184,
     185,   186,   187,   188,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   198,    -1,    57,    58,    59,    60,    61,
      -1,    -1,    64,    65,    66,    67,    -1,    -1,    -1,    71,
      11,    12,    -1,    14,    76,    -1,    -1,    79,    -1,    81,
      -1,    22,    23,    -1,    25,    -1,    27,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   246,    -1,    -1,    -1,    -1,    -1,    -1,   253,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    57,    58,    59,    60,
      61,    -1,   267,    64,    65,    66,    67,    -1,    22,    23,
      71,    25,    -1,    27,    -1,    76,    -1,    -1,    32,    -1,
      81,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    22,    23,
      -1,    25,    -1,    27,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    57,    58,    59,    60,    -1,    -1,    -1,
      64,    65,    66,    67,    -1,    22,    23,    71,    25,    -1,
      27,    -1,    76,    57,    58,    59,    60,    81,    -1,    -1,
      64,    65,    66,    67,    -1,    22,    23,    71,    25,    -1,
      27,    -1,    76,    -1,    -1,    79,    -1,    81,    -1,    -1,
      57,    58,    59,    60,    -1,    -1,    -1,    64,    65,    66,
      67,    -1,    -1,    -1,    71,    -1,    -1,    -1,    -1,    76,
      57,    58,    59,    60,    81,    -1,    -1,    64,    65,    66,
      67,    -1,    -1,    -1,    71,    -1,    -1,    -1,    -1,    76,
      -1,    -1,    -1,    -1,    81
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const unsigned char yystos[] =
{
       0,    84,    86,     0,     3,    11,    12,    14,    61,    76,
      87,   123,   125,   126,   128,   133,   138,   140,   145,   147,
      88,   129,    16,    34,   119,   120,   123,     9,    10,    15,
      19,   125,    75,    85,    90,   127,   119,   119,   134,    90,
     137,    10,   146,    19,    36,    77,    60,    91,    92,    93,
     101,   104,   109,   124,   123,    17,    35,   127,    22,    23,
      57,    58,    65,    81,   107,   108,   111,   127,   141,   127,
      36,    16,   119,    89,     8,    24,   119,   119,    13,    23,
     112,    62,   115,   116,    13,   127,    38,   143,   148,   119,
     123,    75,    25,    27,    57,    58,    59,    64,    66,    67,
      71,    76,    79,    92,    95,    96,    98,   102,   105,   110,
     111,   125,    63,   117,   118,    18,   136,   123,    76,    13,
      90,   123,    20,   131,   142,    37,   127,    17,    17,    32,
      76,    95,    97,   111,    97,    76,    76,    95,    59,    92,
      94,    95,    99,   110,    79,    95,   102,   103,   106,    70,
      71,    72,    73,    76,    21,   130,   131,   132,    90,   119,
     127,    92,   113,   114,   115,   102,    39,   149,   121,   122,
     143,    16,   119,   144,   123,   119,   123,    97,     4,     5,
       6,     7,    68,    69,    29,    30,    31,    33,    26,    95,
      95,     8,     8,    75,    77,    75,    77,    77,    78,    80,
      80,   102,    95,    95,    95,    95,    95,   100,   121,   132,
     131,    79,   105,   135,    13,    77,    78,    40,    41,    42,
      43,    44,    45,    50,    51,    52,    53,    54,    55,   150,
      90,   119,    18,    18,    95,    95,    95,    95,    95,    95,
      95,    97,    97,    97,    95,    77,    78,    94,    94,    94,
      94,    95,    77,    78,   127,   123,    82,    92,    46,    47,
      48,    49,   121,    94,    17,   119,   123,    28,    95,    95,
      13,    94,   119,   139,    95,    77,   123,    18,   127,   119
};

#if ! defined (YYSIZE_T) && defined (__SIZE_TYPE__)
# define YYSIZE_T __SIZE_TYPE__
#endif
#if ! defined (YYSIZE_T) && defined (size_t)
# define YYSIZE_T size_t
#endif
#if ! defined (YYSIZE_T)
# if defined (__STDC__) || defined (__cplusplus)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# endif
#endif
#if ! defined (YYSIZE_T)
# define YYSIZE_T unsigned int
#endif

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		-2
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrlab1

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
      yychar1 = YYTRANSLATE (yychar);				\
      YYPOPSTACK;						\
      goto yybackup;						\
    }								\
  else								\
    { 								\
      yyerror ("syntax error: cannot back up");			\
      YYERROR;							\
    }								\
while (0)

#define YYTERROR	1
#define YYERRCODE	256

/* YYLLOC_DEFAULT -- Compute the default location (before the actions
   are run).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)           \
  Current.first_line   = Rhs[1].first_line;      \
  Current.first_column = Rhs[1].first_column;    \
  Current.last_line    = Rhs[N].last_line;       \
  Current.last_column  = Rhs[N].last_column;
#endif

/* YYLEX -- calling `yylex' with the right arguments.  */

#define YYLEX	yylex ()

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
} while (0)
# define YYDSYMPRINT(Args)			\
do {						\
  if (yydebug)					\
    yysymprint Args;				\
} while (0)
/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YYDSYMPRINT(Args)
#endif /* !YYDEBUG */

/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   SIZE_MAX < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#if YYMAXDEPTH == 0
# undef YYMAXDEPTH
#endif

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined (__GLIBC__) && defined (_STRING_H)
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
#   if defined (__STDC__) || defined (__cplusplus)
yystrlen (const char *yystr)
#   else
yystrlen (yystr)
     const char *yystr;
#   endif
{
  register const char *yys = yystr;

  while (*yys++ != '\0')
    continue;

  return yys - yystr - 1;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined (__GLIBC__) && defined (_STRING_H) && defined (_GNU_SOURCE)
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
#   if defined (__STDC__) || defined (__cplusplus)
yystpcpy (char *yydest, const char *yysrc)
#   else
yystpcpy (yydest, yysrc)
     char *yydest;
     const char *yysrc;
#   endif
{
  register char *yyd = yydest;
  register const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

#endif /* !YYERROR_VERBOSE */



#if YYDEBUG
/*-----------------------------.
| Print this symbol on YYOUT.  |
`-----------------------------*/

static void
#if defined (__STDC__) || defined (__cplusplus)
yysymprint (FILE* yyout, int yytype, YYSTYPE yyvalue)
#else
yysymprint (yyout, yytype, yyvalue)
    FILE* yyout;
    int yytype;
    YYSTYPE yyvalue;
#endif
{
  /* Pacify ``unused variable'' warnings.  */
  (void) yyvalue;

  if (yytype < YYNTOKENS)
    {
      YYFPRINTF (yyout, "token %s (", yytname[yytype]);
# ifdef YYPRINT
      YYPRINT (yyout, yytoknum[yytype], yyvalue);
# endif
    }
  else
    YYFPRINTF (yyout, "nterm %s (", yytname[yytype]);

  switch (yytype)
    {
      case 90: /* scope_pushed */
#line 161 "parse.yy"
        { cout << "variable scoping placeholder"; };
#line 1051 "parse.cc"
        break;
      case 92: /* undef_id */
#line 203 "parse.yy"
        { printf ("identifier \"%s\"", yyvalue.undef_id_name->c_str()); };
#line 1056 "parse.cc"
        break;
      case 94: /* number */
#line 185 "parse.yy"
        { cout << "expression non-terminal"; };
#line 1061 "parse.cc"
        break;
      case 95: /* expression */
#line 185 "parse.yy"
        { cout << "expression non-terminal"; };
#line 1066 "parse.cc"
        break;
      case 96: /* func_eval */
#line 186 "parse.yy"
        { cout << "expression non-terminal"; };
#line 1071 "parse.cc"
        break;
      case 97: /* predicate */
#line 185 "parse.yy"
        { cout << "expression non-terminal"; };
#line 1076 "parse.cc"
        break;
      case 98: /* number_literal */
#line 185 "parse.yy"
        { cout << "expression non-terminal"; };
#line 1081 "parse.cc"
        break;
      case 99: /* seq */
#line 186 "parse.yy"
        { cout << "expression non-terminal"; };
#line 1086 "parse.cc"
        break;
      case 100: /* arglist */
#line 186 "parse.yy"
        { cout << "expression non-terminal"; };
#line 1091 "parse.cc"
        break;
      case 102: /* vector */
#line 320 "parse.yy"
        { cout << "vector definition non-terminal"; };
#line 1096 "parse.cc"
        break;
      case 103: /* expressions */
#line 320 "parse.yy"
        { cout << "vector definition non-terminal"; };
#line 1101 "parse.cc"
        break;
      case 106: /* vectors */
#line 349 "parse.yy"
        { cout << "matrix definition non-terminal"; };
#line 1106 "parse.cc"
        break;
      case 107: /* interp_type */
#line 377 "parse.yy"
        { cout << "interp definition non-terminal"; };
#line 1111 "parse.cc"
        break;
      case 108: /* interp */
#line 377 "parse.yy"
        { cout << "interp definition non-terminal"; };
#line 1116 "parse.cc"
        break;
      case 110: /* function_with_parens */
#line 185 "parse.yy"
        { cout << "expression non-terminal"; };
#line 1121 "parse.cc"
        break;
      case 111: /* function */
#line 184 "parse.yy"
        { cout << "expression non-terminal"; };
#line 1126 "parse.cc"
        break;
      case 126: /* image_command */
#line 499 "parse.yy"
        { cout << "image definition non-terminal"; };
#line 1131 "parse.cc"
        break;
      case 127: /* image_pushed */
#line 531 "parse.yy"
        { cout << "image placeholder"; };
#line 1136 "parse.cc"
        break;
      case 128: /* convolve_command */
#line 499 "parse.yy"
        { cout << "image definition non-terminal"; };
#line 1141 "parse.cc"
        break;
      case 133: /* apply_command */
#line 499 "parse.yy"
        { cout << "image definition non-terminal"; };
#line 1146 "parse.cc"
        break;
      case 138: /* create_command */
#line 500 "parse.yy"
        { cout << "image definition non-terminal"; };
#line 1151 "parse.cc"
        break;
      case 140: /* turbulence_command */
#line 500 "parse.yy"
        { cout << "image definition non-terminal"; };
#line 1156 "parse.cc"
        break;
      case 145: /* noise_command */
#line 500 "parse.yy"
        { cout << "image definition non-terminal"; };
#line 1161 "parse.cc"
        break;
      case 147: /* greyscale_command */
#line 501 "parse.yy"
        { cout << "image definition non-terminal"; };
#line 1166 "parse.cc"
        break;
      default:
        break;
    }
  YYFPRINTF (yyout, ")");
}
#endif /* YYDEBUG. */


/*----------------------------------------------------------.
| yyreport_parse_error -- report a parse error in YYSTATE.  |
`----------------------------------------------------------*/

static void
#if defined (__STDC__) || defined (__cplusplus)
yyreport_parse_error (int yystate, int yychar, YYSTYPE yyvalue)
#else
yyreport_parse_error (yystate, yychar, yyvalue)
    int yystate;
    int yychar;
    YYSTYPE yyvalue;
#endif
{
#if YYERROR_VERBOSE
  int yyn = yypact[yystate];

  if (YYPACT_NINF < yyn && yyn < YYLAST)
    {
      YYSIZE_T yysize = 0;
      int yytype = YYTRANSLATE (yychar);
      char *yymsg;
      int yyx, yycount;

      yycount = 0;
      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      for (yyx = yyn < 0 ? -yyn : 0;
	   yyx < (int) (sizeof (yytname) / sizeof (char *)); yyx++)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  yysize += yystrlen (yytname[yyx]) + 15, yycount++;
      yysize += yystrlen ("parse error, unexpected ") + 1;
      yysize += yystrlen (yytname[yytype]);
      yymsg = (char *) YYSTACK_ALLOC (yysize);
      if (yymsg != 0)
	{
	  char *yyp = yystpcpy (yymsg, "parse error, unexpected ");
	  yyp = yystpcpy (yyp, yytname[yytype]);

	  if (yycount < 5)
	    {
	      yycount = 0;
	      for (yyx = yyn < 0 ? -yyn : 0;
		   yyx < (int) (sizeof (yytname) / sizeof (char *));
		   yyx++)
		if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
		  {
		    const char *yyq = ! yycount ? ", expecting " : " or ";
		    yyp = yystpcpy (yyp, yyq);
		    yyp = yystpcpy (yyp, yytname[yyx]);
		    yycount++;
		  }
	    }
	  yyerror (yymsg);
	  YYSTACK_FREE (yymsg);
	}
      else
	yyerror ("parse error; also virtual memory exhausted");
    }
  else
#endif /* YYERROR_VERBOSE */
    yyerror ("parse error");

  /* Pacify ``unused variable'' warnings.  */
  (void) yystate;
  (void) yychar;
  (void) yyvalue;
  
}


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
#if defined (__STDC__) || defined (__cplusplus)
yydestruct (int yytype, YYSTYPE yyvalue)
#else
yydestruct (yytype, yyvalue)
    int yytype;
    YYSTYPE yyvalue;
#endif
{
  /* Pacify ``unused variable'' warnings.  */
  (void) yyvalue;

  switch (yytype)
    {
      case 90: /* scope_pushed */
#line 159 "parse.yy"
        { pop_scope(); };
#line 1268 "parse.cc"
        break;
      case 92: /* undef_id */
#line 202 "parse.yy"
        { if (yyvalue.undef_id_name) delete yyvalue.undef_id_name; };
#line 1273 "parse.cc"
        break;
      case 94: /* number */
#line 176 "parse.yy"
        { if (yyvalue.expr) delete yyvalue.expr; };
#line 1278 "parse.cc"
        break;
      case 95: /* expression */
#line 177 "parse.yy"
        { if (yyvalue.expr) delete yyvalue.expr; };
#line 1283 "parse.cc"
        break;
      case 96: /* func_eval */
#line 180 "parse.yy"
        { if (yyvalue.expr) delete yyvalue.expr; };
#line 1288 "parse.cc"
        break;
      case 97: /* predicate */
#line 178 "parse.yy"
        { if (yyvalue.pred) delete yyvalue.pred; };
#line 1293 "parse.cc"
        break;
      case 98: /* number_literal */
#line 179 "parse.yy"
        { if (yyvalue.expr) delete yyvalue.expr; };
#line 1298 "parse.cc"
        break;
      case 99: /* seq */
#line 182 "parse.yy"
        { if (yyvalue.seq_expr) delete yyvalue.seq_expr; };
#line 1303 "parse.cc"
        break;
      case 100: /* arglist */
#line 181 "parse.yy"
        { if (yyvalue.seq_expr) delete yyvalue.seq_expr; };
#line 1308 "parse.cc"
        break;
      case 102: /* vector */
#line 317 "parse.yy"
        { if (yyvalue.vec) delete yyvalue.vec; };
#line 1313 "parse.cc"
        break;
      case 103: /* expressions */
#line 317 "parse.yy"
        { if (yyvalue.vec) delete yyvalue.vec; };
#line 1318 "parse.cc"
        break;
      case 106: /* vectors */
#line 346 "parse.yy"
        { if (yyvalue.matr) delete yyvalue.matr; };
#line 1323 "parse.cc"
        break;
      case 107: /* interp_type */
#line 374 "parse.yy"
        { if (yyvalue.interp) delete yyvalue.interp; };
#line 1328 "parse.cc"
        break;
      case 108: /* interp */
#line 374 "parse.yy"
        { if (yyvalue.interp) delete yyvalue.interp; };
#line 1333 "parse.cc"
        break;
      case 110: /* function_with_parens */
#line 175 "parse.yy"
        { if (yyvalue.fun) delete yyvalue.fun; };
#line 1338 "parse.cc"
        break;
      case 111: /* function */
#line 174 "parse.yy"
        { if (yyvalue.fun) delete yyvalue.fun; };
#line 1343 "parse.cc"
        break;
      case 126: /* image_command */
#line 494 "parse.yy"
        { if (yyvalue.img) delete yyvalue.img; };
#line 1348 "parse.cc"
        break;
      case 127: /* image_pushed */
#line 532 "parse.yy"
        { delete pop_image(); };
#line 1353 "parse.cc"
        break;
      case 128: /* convolve_command */
#line 494 "parse.yy"
        { if (yyvalue.img) delete yyvalue.img; };
#line 1358 "parse.cc"
        break;
      case 133: /* apply_command */
#line 494 "parse.yy"
        { if (yyvalue.img) delete yyvalue.img; };
#line 1363 "parse.cc"
        break;
      case 138: /* create_command */
#line 494 "parse.yy"
        { if (yyvalue.img) delete yyvalue.img; };
#line 1368 "parse.cc"
        break;
      case 140: /* turbulence_command */
#line 494 "parse.yy"
        { if (yyvalue.img) delete yyvalue.img; };
#line 1373 "parse.cc"
        break;
      case 145: /* noise_command */
#line 494 "parse.yy"
        { if (yyvalue.img) delete yyvalue.img; };
#line 1378 "parse.cc"
        break;
      case 147: /* greyscale_command */
#line 494 "parse.yy"
        { if (yyvalue.img) delete yyvalue.img; };
#line 1383 "parse.cc"
        break;
      default:
        break;
    }
}



/* The user can define YYPARSE_PARAM as the name of an argument to be passed
   into yyparse.  The argument should have type void *.
   It should actually point to an object.
   Grammar actions can access the variable by casting it
   to the proper pointer type.  */

#ifdef YYPARSE_PARAM
# if defined (__STDC__) || defined (__cplusplus)
#  define YYPARSE_PARAM_ARG void *YYPARSE_PARAM
#  define YYPARSE_PARAM_DECL
# else
#  define YYPARSE_PARAM_ARG YYPARSE_PARAM
#  define YYPARSE_PARAM_DECL void *YYPARSE_PARAM;
# endif
#else /* !YYPARSE_PARAM */
# define YYPARSE_PARAM_ARG
# define YYPARSE_PARAM_DECL
#endif /* !YYPARSE_PARAM */

/* Prevent warning if -Wstrict-prototypes.  */
#ifdef __GNUC__
# ifdef YYPARSE_PARAM
int yyparse (void *);
# else
int yyparse (void);
# endif
#endif


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of parse errors so far.  */
int yynerrs;


int
yyparse (YYPARSE_PARAM_ARG)
     YYPARSE_PARAM_DECL
{
  
  register int yystate;
  register int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Lookahead token as an internal (translated) token number.  */
  int yychar1 = 0;

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  short	yyssa[YYINITDEPTH];
  short *yyss = yyssa;
  register short *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  register YYSTYPE *yyvsp;



#define YYPOPSTACK   (yyvsp--, yyssp--)

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* When reducing, the number of symbols on the RHS of the reduced
     rule.  */
  int yylen;

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
     have just been pushed. so pushing a state here evens the stacks.
     */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyssp >= yyss + yystacksize - 1)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack. Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	short *yyss1 = yyss;


	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow ("parser stack overflow",
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),

		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyoverflowlab;
# else
      /* Extend the stack our own way.  */
      if (yystacksize >= YYMAXDEPTH)
	goto yyoverflowlab;
      yystacksize *= 2;
      if (yystacksize > YYMAXDEPTH)
	yystacksize = YYMAXDEPTH;

      {
	short *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyoverflowlab;
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

      if (yyssp >= yyss + yystacksize - 1)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

/* Do appropriate processing given the current state.  */
/* Read a lookahead token if we need one and don't already have one.  */
/* yyresume: */

  /* First try to decide what to do without reference to lookahead token.  */

  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* yychar is either YYEMPTY or YYEOF
     or a valid token in external form.  */

  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  /* Convert token to internal form (in yychar1) for indexing tables with.  */

  if (yychar <= 0)		/* This means end of input.  */
    {
      yychar1 = 0;
      yychar = YYEOF;		/* Don't call YYLEX any more.  */

      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yychar1 = YYTRANSLATE (yychar);

      /* We have to keep this `#if YYDEBUG', since we use variables
	 which are defined only if `YYDEBUG' is set.  */
      YYDPRINTF ((stderr, "Next token is "));
      YYDSYMPRINT ((stderr, yychar1, yylval));
      YYDPRINTF ((stderr, "\n"));
    }

  yyn += yychar1;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yychar1)
    goto yydefault;

  yyn = yytable[yyn];

  /* yyn is what to do for this token type in this state.
     Negative => reduce, -yyn is rule number.
     Positive => shift, yyn is new state.
       New state is final state => don't bother to shift,
       just return success.
     0, or most negative number => error.  */

  if (yyn < 0)
    {
      if (yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrlab;

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Shift the lookahead token.  */
  YYDPRINTF ((stderr, "Shifting token %d (%s), ",
	      yychar, yytname[yychar1]));

  /* Discard the token being shifted unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  *++yyvsp = yylval;


  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  yystate = yyn;
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



#if YYDEBUG
  /* We have to keep this `#if YYDEBUG', since we use variables which
     are defined only if `YYDEBUG' is set.  */
  if (yydebug)
    {
      int yyi;

      YYFPRINTF (stderr, "Reducing via rule %d (line %d), ",
		 yyn - 1, yyrline[yyn]);

      /* Print the symbols being reduced, and their result.  */
      for (yyi = yyprhs[yyn]; yyrhs[yyi] >= 0; yyi++)
	YYFPRINTF (stderr, "%s ", yytname[yyrhs[yyi]]);
      YYFPRINTF (stderr, " -> %s\n", yytname[yyr1[yyn]]);
    }
#endif
  switch (yyn)
    {
        case 2:
#line 136 "parse.yy"
    {
	    if (!errors)
	      {
	        yyvsp[-1].img->build_graph ();
	        errors |= int (yyvsp[-1].img->write(*output_file, output_format));
	      }
	  }
    break;

  case 7:
#line 156 "parse.yy"
    { push_scope(); }
    break;

  case 8:
#line 156 "parse.yy"
    { pop_scope(); }
    break;

  case 16:
#line 205 "parse.yy"
    { yyval.undef_id_name = yyvsp[0].undef_id_name; }
    break;

  case 17:
#line 210 "parse.yy"
    { closure c(num_variables());
	    float num = yyvsp[0].expr->evaluate (&c);
	    number_literal *def = new number_literal (num);
	    declare_id (*yyvsp[-2].undef_id_name, NUMBER_DEF_, def);
	    delete yyvsp[-2].undef_id_name;
	    delete yyvsp[0].expr; }
    break;

  case 18:
#line 220 "parse.yy"
    { yyval.expr = yyvsp[0].expr; }
    break;

  case 19:
#line 222 "parse.yy"
    { yyval.expr = new var_assignment(yyvsp[0].expr, yyvsp[-2].def_id); }
    break;

  case 20:
#line 224 "parse.yy"
    { yyval.expr = new var_assignment(yyvsp[0].expr, insert_var (*yyvsp[-2].undef_id_name)); }
    break;

  case 21:
#line 229 "parse.yy"
    { yyval.expr = yyvsp[-1].expr; }
    break;

  case 22:
#line 231 "parse.yy"
    { yyval.expr = yyvsp[-1].seq_expr; }
    break;

  case 23:
#line 233 "parse.yy"
    { yyval.expr = new number_literal (*static_cast<number_literal *>(yyvsp[0].expr)); }
    break;

  case 24:
#line 235 "parse.yy"
    { yyval.expr = yyvsp[0].expr; }
    break;

  case 25:
#line 237 "parse.yy"
    { yyval.expr = new binary_operator(yyvsp[-2].expr, yyvsp[0].expr, binary_operator::PLUS); }
    break;

  case 26:
#line 239 "parse.yy"
    { yyval.expr = new binary_operator(yyvsp[-2].expr, yyvsp[0].expr, binary_operator::MINUS); }
    break;

  case 27:
#line 241 "parse.yy"
    { yyval.expr = new binary_operator(yyvsp[-2].expr, yyvsp[0].expr, binary_operator::TIMES); }
    break;

  case 28:
#line 243 "parse.yy"
    { yyval.expr = new binary_operator(yyvsp[-2].expr, yyvsp[0].expr, binary_operator::DIVIDE); }
    break;

  case 29:
#line 245 "parse.yy"
    { yyval.expr = new binary_operator(yyvsp[-3].expr, yyvsp[-1].expr, yyvsp[-5].bin_op_id); }
    break;

  case 30:
#line 247 "parse.yy"
    { yyval.expr = new unary_operator(yyvsp[-1].expr, yyvsp[-3].un_op_id); }
    break;

  case 31:
#line 249 "parse.yy"
    { yyval.expr = new var_ref(yyvsp[0].def_id); }
    break;

  case 32:
#line 251 "parse.yy"
    { yyval.expr = NULL; yyerror ("undefined variable"); YYERROR; }
    break;

  case 33:
#line 253 "parse.yy"
    { yyval.expr = new unary_operator(yyvsp[0].expr, unary_operator::MINUS); }
    break;

  case 34:
#line 255 "parse.yy"
    { yyval.expr = yyvsp[0].expr; }
    break;

  case 35:
#line 257 "parse.yy"
    { yyval.expr = new if_then_else(yyvsp[-4].pred, yyvsp[-2].expr, yyvsp[0].expr); }
    break;

  case 36:
#line 259 "parse.yy"
    { yyval.expr = new while_do(yyvsp[-2].pred, yyvsp[0].expr); }
    break;

  case 37:
#line 264 "parse.yy"
    { if (yyvsp[-3].fun->get_num_args() != yyvsp[-1].seq_expr->size())
	      {
		yyerror ("argument number mismatch");
		YYERROR;
	      }
	    yyval.expr = new function_eval(yyvsp[-3].fun, yyvsp[-1].seq_expr);
	  }
    break;

  case 38:
#line 275 "parse.yy"
    { yyval.pred = new and_predicate(yyvsp[-2].pred, yyvsp[0].pred); }
    break;

  case 39:
#line 277 "parse.yy"
    { yyval.pred = new or_predicate(yyvsp[-2].pred, yyvsp[0].pred); }
    break;

  case 40:
#line 279 "parse.yy"
    { yyval.pred = new xor_predicate(yyvsp[-2].pred, yyvsp[0].pred); }
    break;

  case 41:
#line 281 "parse.yy"
    { yyval.pred = new not_predicate(yyvsp[0].pred); }
    break;

  case 42:
#line 283 "parse.yy"
    { yyval.pred = new order_predicate(yyvsp[-2].expr, yyvsp[0].expr, order_predicate::NE); }
    break;

  case 43:
#line 285 "parse.yy"
    { yyval.pred = new order_predicate(yyvsp[-2].expr, yyvsp[0].expr, order_predicate::EQ); }
    break;

  case 44:
#line 287 "parse.yy"
    { yyval.pred = new order_predicate(yyvsp[-2].expr, yyvsp[0].expr, order_predicate::GE); }
    break;

  case 45:
#line 289 "parse.yy"
    { yyval.pred = new order_predicate(yyvsp[-2].expr, yyvsp[0].expr, order_predicate::LE); }
    break;

  case 46:
#line 291 "parse.yy"
    { yyval.pred = new order_predicate(yyvsp[-2].expr, yyvsp[0].expr, order_predicate::LT); }
    break;

  case 47:
#line 293 "parse.yy"
    { yyval.pred = new order_predicate(yyvsp[-2].expr, yyvsp[0].expr, order_predicate::GT); }
    break;

  case 48:
#line 298 "parse.yy"
    { yyval.expr = new number_literal(yyvsp[0].real); }
    break;

  case 49:
#line 300 "parse.yy"
    { yyval.expr = new number_literal(yyvsp[0].real); }
    break;

  case 50:
#line 305 "parse.yy"
    { yyval.seq_expr = new seq(); yyval.seq_expr->push_back(yyvsp[-2].expr); yyval.seq_expr->push_back(yyvsp[0].expr); }
    break;

  case 51:
#line 307 "parse.yy"
    { yyval.seq_expr = yyvsp[-2].seq_expr; yyval.seq_expr->push_back(yyvsp[0].expr); }
    break;

  case 52:
#line 312 "parse.yy"
    { yyval.seq_expr = new seq(); yyval.seq_expr->push_back(yyvsp[0].expr); }
    break;

  case 53:
#line 314 "parse.yy"
    { yyval.seq_expr = yyvsp[-2].seq_expr; yyval.seq_expr->push_back(yyvsp[0].expr); }
    break;

  case 54:
#line 327 "parse.yy"
    { closure c(num_variables());
	    numeric_vector *vec = yyvsp[0].vec->evaluate (&c);
	    declare_id (*yyvsp[-2].undef_id_name, VECTOR_DEF_, vec);
	    delete yyvsp[0].vec;
	    delete yyvsp[-2].undef_id_name; }
    break;

  case 55:
#line 336 "parse.yy"
    { yyval.vec = yyvsp[-1].vec; }
    break;

  case 56:
#line 341 "parse.yy"
    { yyval.vec = yyvsp[-2].vec; yyval.vec->push_back (yyvsp[0].expr); }
    break;

  case 57:
#line 343 "parse.yy"
    { yyval.vec = new expr_vector (); yyval.vec->push_back (yyvsp[0].expr); }
    break;

  case 58:
#line 356 "parse.yy"
    { closure c(num_variables());
	    numeric_matrix *matr = yyvsp[0].matr->evaluate (&c);
	    declare_id (*yyvsp[-2].undef_id_name, MATRIX_DEF_, matr);
	    delete yyvsp[0].matr;
	    delete yyvsp[-2].undef_id_name; }
    break;

  case 59:
#line 364 "parse.yy"
    { yyval.matr = yyvsp[-1].matr; }
    break;

  case 60:
#line 369 "parse.yy"
    { yyval.matr = yyvsp[-1].matr; yyval.matr->push_back (yyvsp[0].vec); }
    break;

  case 61:
#line 371 "parse.yy"
    { yyval.matr = new expr_matrix (yyvsp[0].vec->size()); yyval.matr->push_back (yyvsp[0].vec); }
    break;

  case 62:
#line 382 "parse.yy"
    {
	    yyval.interp = new linear_interpolator ();
	  }
    break;

  case 63:
#line 386 "parse.yy"
    {
	    yyval.interp = new spline_interpolator ();
	  }
    break;

  case 64:
#line 393 "parse.yy"
    {
	    yyval.interp = yyvsp[-3].interp;
	    if (yyvsp[-2].nvec->size() != yyvsp[0].nvec->size())
	      {
		yyerror ("mismatch in vector sizes");
		YYERROR;
	      }

	    const numeric_vector &from = *yyvsp[-2].nvec;
	    const numeric_vector &to = *yyvsp[0].nvec;

	    for (int i = 1; i < yyvsp[-2].nvec->size(); i++)
	      {
	        float x0 = from[i - 1];
	        float x1 = from[i];
	        float y0 = to[i - 1];
	        float y1 = to[i];
		if (x0 != x1)
		  yyval.interp->add_range (x0, x1, y0, y1);
	      }

	    if (!yyvsp[-2].nvec->declared) delete yyvsp[-2].nvec;
	    if (!yyvsp[0].nvec->declared) delete yyvsp[0].nvec;
	  }
    break;

  case 65:
#line 428 "parse.yy"
    { declare_id (*yyvsp[-2].undef_id_name, FUNC_DEF_, yyvsp[0].fun);
	    delete yyvsp[-2].undef_id_name; }
    break;

  case 66:
#line 434 "parse.yy"
    { yyval.fun = yyvsp[0].fun; }
    break;

  case 67:
#line 436 "parse.yy"
    { yyval.fun = yyvsp[-1].fun; }
    break;

  case 68:
#line 441 "parse.yy"
    { push_scope (); }
    break;

  case 69:
#line 443 "parse.yy"
    { yyval.fun = new function(yyvsp[0].expr, yyvsp[-3].argcount, num_variables ()); pop_scope (); }
    break;

  case 70:
#line 445 "parse.yy"
    { yyval.fun = yyvsp[0].fun; }
    break;

  case 71:
#line 447 "parse.yy"
    { yyval.fun = new interp_eval(yyvsp[0].interp); }
    break;

  case 72:
#line 449 "parse.yy"
    { yyval.fun = new function(new unary_operator(new var_ref(0), yyvsp[0].un_op_id), 1, 0); }
    break;

  case 73:
#line 451 "parse.yy"
    { yyval.fun = new function(new binary_operator(new var_ref(0),
						  new var_ref(1), yyvsp[0].bin_op_id), 2, 0); }
    break;

  case 74:
#line 456 "parse.yy"
    { yyval.argcount = 0; }
    break;

  case 75:
#line 458 "parse.yy"
    { yyval.argcount = yyvsp[0].argcount; }
    break;

  case 76:
#line 462 "parse.yy"
    { insert_var (*yyvsp[0].undef_id_name); delete yyvsp[0].undef_id_name; yyval.argcount = 1; }
    break;

  case 77:
#line 464 "parse.yy"
    { insert_var (*yyvsp[0].undef_id_name); delete yyvsp[0].undef_id_name; yyval.argcount = yyvsp[-2].argcount + 1; }
    break;

  case 78:
#line 471 "parse.yy"
    { yyval.nvec = yyvsp[0].nvec; }
    break;

  case 79:
#line 472 "parse.yy"
    { push_scope(); }
    break;

  case 80:
#line 472 "parse.yy"
    { pop_scope(); yyval.nvec = yyvsp[0].vec->evaluate(); }
    break;

  case 81:
#line 476 "parse.yy"
    { yyval.nmatr = yyvsp[0].nmatr; }
    break;

  case 82:
#line 477 "parse.yy"
    { push_scope(); }
    break;

  case 83:
#line 477 "parse.yy"
    { pop_scope(); yyval.nmatr = yyvsp[0].matr->evaluate(); }
    break;

  case 84:
#line 481 "parse.yy"
    { push_scope(); }
    break;

  case 85:
#line 481 "parse.yy"
    { pop_scope(); yyval.fun = yyvsp[0].fun; }
    break;

  case 86:
#line 485 "parse.yy"
    { push_scope(); }
    break;

  case 87:
#line 485 "parse.yy"
    { pop_scope(); yyval.real = yyvsp[0].expr->evaluate(); }
    break;

  case 88:
#line 489 "parse.yy"
    { yyval.img = yyvsp[0].img; }
    break;

  case 89:
#line 491 "parse.yy"
    { yyval.img = yyvsp[-1].img; }
    break;

  case 90:
#line 513 "parse.yy"
    { declare_id (*yyvsp[-2].undef_id_name, IMAGE_DEF_, yyvsp[0].img);
	    delete yyvsp[-2].undef_id_name; }
    break;

  case 100:
#line 539 "parse.yy"
    { push_image(new convolve_command ()); }
    break;

  case 101:
#line 541 "parse.yy"
    { if ((yyvsp[-1].nmatr->size() & yyvsp[-1].nmatr->row_size() & 1) == 0)
	      {
		yyerror ("Convolution matrix sizes should be odd");
		YYERROR;
	      }

	    top_image()->set_param (image::CONVOLUTION_MATRIX, yyvsp[-1].nmatr);
	    top_image()->set_param (image::SRC_IMAGE, yyvsp[-3].img);
	    yyval.img = pop_image (); }
    break;

  case 107:
#line 561 "parse.yy"
    { top_image()->set_param (image::SCALE, yyvsp[0].real); }
    break;

  case 108:
#line 566 "parse.yy"
    { top_image()->set_param (image::BIAS, yyvsp[0].real); }
    break;

  case 109:
#line 571 "parse.yy"
    {
	    if (yyvsp[0].fun->get_num_args () != 3 && yyvsp[0].fun->get_num_args () != 1)
	      {
		yyerror ("expected 1- or 3-argument function");
		YYERROR;
	      }
	    push_image (new apply_colormap_command ());
	    top_image()->set_param (image::OUT_RED, yyvsp[0].fun);
	  }
    break;

  case 110:
#line 581 "parse.yy"
    { top_image()->set_param (image::SRC_IMAGE, yyvsp[0].img);
	    yyval.img = pop_image (); }
    break;

  case 111:
#line 586 "parse.yy"
    {
	    if ((yyvsp[-4].fun->get_num_args () != 3 && yyvsp[-4].fun->get_num_args () != 1)
	        || (yyvsp[-2].fun->get_num_args () != 3 && yyvsp[-2].fun->get_num_args () != 1)
	        || (yyvsp[0].fun->get_num_args () != 3 && yyvsp[0].fun->get_num_args () != 1))
	      {
		yyerror ("expected 1- or 3-argument function");
		YYERROR;
	      }
	    push_image (new apply_colormap_command ());
	    top_image()->set_param (image::OUT_RED, yyvsp[-4].fun);
	    top_image()->set_param (image::OUT_GREEN, yyvsp[-2].fun);
	    top_image()->set_param (image::OUT_BLUE, yyvsp[0].fun);
	  }
    break;

  case 112:
#line 600 "parse.yy"
    { top_image()->set_param (image::SRC_IMAGE, yyvsp[0].img);
	    yyval.img = pop_image (); }
    break;

  case 113:
#line 604 "parse.yy"
    {
	    if (yyvsp[-2].fun->get_num_args () != 2 ||
	        yyvsp[0].fun->get_num_args () != 2)
	      {
		yyerror ("expected 2-argument function");
		YYERROR;
	      }
	    push_image (new apply_command ());
	    top_image()->set_param (image::X_DISPLACEMENT, yyvsp[-2].fun);
	    top_image()->set_param (image::Y_DISPLACEMENT, yyvsp[0].fun);
	  }
    break;

  case 114:
#line 616 "parse.yy"
    { top_image()->set_param (image::SRC_IMAGE, yyvsp[0].img);
	    yyval.img = pop_image (); }
    break;

  case 115:
#line 620 "parse.yy"
    { push_image(new apply_op_command ()); }
    break;

  case 116:
#line 622 "parse.yy"
    { top_image()->set_param (image::SRC_IMAGE_2, yyvsp[-6].img);
	    top_image()->set_param (image::SRC_IMAGE, yyvsp[-2].img);
	    yyval.img = pop_image (); }
    break;

  case 117:
#line 629 "parse.yy"
    {
	    if (yyvsp[0].fun->get_num_args () != 2)
	      {
		yyerror ("expected 2-argument function");
		YYERROR;
	      }
	    push_image (new create_from_formula_command ());
	    top_image()->set_param (image::OUT_RED, yyvsp[0].fun);
	    yyval.img = pop_image (); }
    break;

  case 118:
#line 639 "parse.yy"
    {
	    if (yyvsp[-4].fun->get_num_args () != 2 ||
	        yyvsp[-2].fun->get_num_args () != 2 ||
	        yyvsp[0].fun->get_num_args () != 2)
	      {
		yyerror ("expected 2-argument function");
		YYERROR;
	      }
	    push_image (new create_from_formula_command ());
	    top_image()->set_param (image::OUT_RED, yyvsp[-4].fun);
	    top_image()->set_param (image::OUT_GREEN, yyvsp[-2].fun);
	    top_image()->set_param (image::OUT_BLUE, yyvsp[0].fun);
	    yyval.img = pop_image (); }
    break;

  case 119:
#line 653 "parse.yy"
    { push_image (new create_from_channels_command ()); }
    break;

  case 120:
#line 654 "parse.yy"
    { top_image()->set_param (image::OUT_RED, yyvsp[-6].img);
	    top_image()->set_param (image::OUT_GREEN, yyvsp[-4].img);
	    top_image()->set_param (image::OUT_BLUE, yyvsp[-2].img);
	    yyval.img = pop_image (); }
    break;

  case 121:
#line 662 "parse.yy"
    { push_image (new perlin_noise_command ()); }
    break;

  case 122:
#line 665 "parse.yy"
    { yyval.img = pop_image (); }
    break;

  case 123:
#line 669 "parse.yy"
    { }
    break;

  case 124:
#line 671 "parse.yy"
    { }
    break;

  case 125:
#line 675 "parse.yy"
    { }
    break;

  case 126:
#line 677 "parse.yy"
    { }
    break;

  case 127:
#line 682 "parse.yy"
    { if (yyvsp[0].fun->get_num_args () != 1)
	      {
		yyerror ("expected 1-argument function");
		YYERROR;
	      }
	    top_image()->set_param (image::OUT_RED, yyvsp[0].fun);
	  }
    break;

  case 128:
#line 690 "parse.yy"
    { if (yyvsp[-4].fun->get_num_args () != 1
		|| yyvsp[-2].fun->get_num_args () != 1
		|| yyvsp[0].fun->get_num_args () != 1)
	      {
		yyerror ("expected 1-argument function");
		YYERROR;
	      }
	    top_image()->set_param (image::OUT_RED, yyvsp[-4].fun);
	    top_image()->set_param (image::OUT_GREEN, yyvsp[-2].fun);
	    top_image()->set_param (image::OUT_BLUE, yyvsp[0].fun);
	  }
    break;

  case 129:
#line 705 "parse.yy"
    { push_image (new noise_command ()); }
    break;

  case 130:
#line 707 "parse.yy"
    { yyval.img = pop_image (); }
    break;

  case 131:
#line 712 "parse.yy"
    { push_image (new greyscale_command ()); }
    break;

  case 132:
#line 714 "parse.yy"
    { top_image()->set_param (image::SRC_IMAGE, yyvsp[0].img);
	    yyval.img = pop_image (); }
    break;

  case 133:
#line 720 "parse.yy"
    { top_image()->set_param (image::OPERATION, image::BLEND); }
    break;

  case 134:
#line 722 "parse.yy"
    { top_image()->set_param (image::OPERATION, image::BLEND); }
    break;

  case 135:
#line 724 "parse.yy"
    { top_image()->set_param (image::OPERATION, image::DISSOLVE); }
    break;

  case 136:
#line 726 "parse.yy"
    { top_image()->set_param (image::OPERATION, image::ADD); }
    break;

  case 137:
#line 728 "parse.yy"
    { top_image()->set_param (image::OPERATION, image::SUBTRACT); }
    break;

  case 138:
#line 730 "parse.yy"
    { top_image()->set_param (image::OPERATION, image::DIFFERENCE); }
    break;

  case 139:
#line 732 "parse.yy"
    { top_image()->set_param (image::OPERATION, image::MULTIPLY); }
    break;

  case 140:
#line 734 "parse.yy"
    { top_image()->set_param (image::OPERATION, image::SCREEN); }
    break;

  case 141:
#line 736 "parse.yy"
    { top_image()->set_param (image::OPERATION, image::OVERLAY); }
    break;

  case 142:
#line 738 "parse.yy"
    { top_image()->set_param (image::OPERATION, image::COLOR); }
    break;

  case 143:
#line 740 "parse.yy"
    { top_image()->set_param (image::OPERATION, image::HUE); }
    break;

  case 144:
#line 742 "parse.yy"
    { top_image()->set_param (image::OPERATION, image::VALUE); }
    break;

  case 145:
#line 744 "parse.yy"
    { top_image()->set_param (image::OPERATION, image::SATURATION); }
    break;

  case 146:
#line 746 "parse.yy"
    { top_image()->set_param (image::OPERATION, image::LIGHTEN); }
    break;

  case 147:
#line 748 "parse.yy"
    { top_image()->set_param (image::OPERATION, image::DARKEN); }
    break;

  case 148:
#line 753 "parse.yy"
    { if (yyvsp[0].real < 0.0 || yyvsp[0].real > 1.0)
	      {
		yyerror ("expected number between 0 and 1");
		YYERROR;
	       }
	    top_image()->set_param (image::OPACITY, yyvsp[0].real); }
    break;


    }

/* Line 1079 of /usr/share/bison/yacc.c.  */
#line 2471 "parse.cc"

  yyvsp -= yylen;
  yyssp -= yylen;


#if YYDEBUG
  if (yydebug)
    {
      short *yyssp1 = yyss - 1;
      YYFPRINTF (stderr, "state stack now");
      while (yyssp1 != yyssp)
	YYFPRINTF (stderr, " %d", *++yyssp1);
      YYFPRINTF (stderr, "\n");
    }
#endif

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
      yyreport_parse_error (yystate, yychar, yylval);
    }
  goto yyerrlab1;


/*----------------------------------------------------.
| yyerrlab1 -- error raised explicitly by an action.  |
`----------------------------------------------------*/
yyerrlab1:
  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      /* Return failure if at end of input.  */
      if (yychar == YYEOF)
        {
	  /* Pop the error token.  */
          YYPOPSTACK;
	  /* Pop the rest of the stack.  */
	  while (yyssp > yyss)
	    {
	      YYDPRINTF ((stderr, "Error: popping "));
	      YYDSYMPRINT ((stderr,
			    yystos[*yyssp],
			    *yyvsp));
	      YYDPRINTF ((stderr, "\n"));
	      yydestruct (yystos[*yyssp], *yyvsp);
	      YYPOPSTACK;
	    }
	  YYABORT;
        }

      YYDPRINTF ((stderr, "Discarding token %d (%s).\n",
		  yychar, yytname[yychar1]));
      yydestruct (yychar1, yylval);
      yychar = YYEMPTY;
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */

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

      YYDPRINTF ((stderr, "Error: popping "));
      YYDSYMPRINT ((stderr,
		    yystos[*yyssp], *yyvsp));
      YYDPRINTF ((stderr, "\n"));

      yydestruct (yystos[yystate], *yyvsp);
      yyvsp--;
      yystate = *--yyssp;


#if YYDEBUG
      if (yydebug)
	{
	  short *yyssp1 = yyss - 1;
	  YYFPRINTF (stderr, "Error: state stack now");
	  while (yyssp1 != yyssp)
	    YYFPRINTF (stderr, " %d", *++yyssp1);
	  YYFPRINTF (stderr, "\n");
	}
#endif
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  YYDPRINTF ((stderr, "Shifting error token, "));

  *++yyvsp = yylval;


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
/*----------------------------------------------.
| yyoverflowlab -- parser overflow comes here.  |
`----------------------------------------------*/
yyoverflowlab:
  yyerror ("parser stack overflow");
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  return yyresult;
}


#line 761 "parse.yy"


void
yyerror (const char *s)
{
  errors = 1;
  fprintf (stderr, "line %d: %s\n", yylineno, s);
}

