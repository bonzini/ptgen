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

#ifndef BISON_PARSE_H
# define BISON_PARSE_H

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
/* Line 1292 of /usr/share/bison/yacc.c.  */
#line 199 "y.tab.h"
# define YYSTYPE yystype
#endif

extern YYSTYPE yylval;


#endif /* not BISON_PARSE_H */

