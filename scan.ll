%{
// Procedural Texture Generator
// Paolo Bonzini
// esame di Elaborazione e Trasmissione delle Immagini
//
// Scanner

#include "ptgen.h"

int yylineno = 1;
%}

%x COMMENT

%option nounput
%option noyywrap
%option never-interactive

%%

<INITIAL,COMMENT>{
  \n+				yylineno += yyleng;
  [ 	\f]+
}

<INITIAL>{
"/*"				BEGIN (COMMENT);
"//"[^\n]*

"let"				return LET_;
"=="				return EQ_;
"!="				return NE_;
"<="				return LE_;
">="				return GE_;
":="				return ASSIGN_;
"perlin"			return PERLIN_;
"noise"				return NOISE_;
"convolve"			return CONVOLVE_;
"create"			return CREATE_;
"apply"				return APPLY_;
"greyscale"			return GREYSCALE_;
"red"				return RED_;
"green"				return GREEN_;
"blue"				return BLUE_;
"image"				return IMAGE_;
"to"				return TO_;
"scale"				return SCALE_;
"bias"				return BIAS_;
"spline"			return SPLINE_;
"map"				return MAP_;
"with"				return WITH_;
"if"				return IF_;
"do"				return DO_;
"while"				return WHILE_;
"else"				return ELSE_;
"then"				return THEN_;
"and"				return AND_;
"or"				return OR_;
"not"				return NOT_;
"xor"				return XOR_;
"x"				return X_;
"y"				return Y_;
"range"				return RANGE_;
"output"			return OUTPUT_;
"operation"			return OPERATION_;
"blend"				return BLEND_;
"replace"			return REPLACE_;
"dissolve"			return DISSOLVE_;
"add"				return ADD_;
"subtract"			return SUBTRACT_;
"difference"			return DIFFERENCE_;
"overlay"			return OVERLAY_;
"multiply"			return MULTIPLY_;
"screen"			return SCREEN_;
"color"				return COLOR_;
"hue"				return HUE_;
"value"				return VALUE_;
"saturation"			return SATURATION_;
"lighten"			return LIGHTEN_;
"darken"			return DARKEN_;
"opacity"			return OPACITY_;
"from"				return FROM_;

"atan2"				yylval.bin_op_id = binary_operator::ATAN2; return BUILTIN_FUNC2_;
"hypot"				yylval.bin_op_id = binary_operator::HYPOT; return BUILTIN_FUNC2_;
"min"				yylval.bin_op_id = binary_operator::MIN; return BUILTIN_FUNC2_;
"max"				yylval.bin_op_id = binary_operator::MAX; return BUILTIN_FUNC2_;
"rand"				yylval.un_op_id = unary_operator::RAND; return BUILTIN_FUNC1_;
"frac"				yylval.un_op_id = unary_operator::FRAC; return BUILTIN_FUNC1_;
"tile"				yylval.un_op_id = unary_operator::TILE; return BUILTIN_FUNC1_;
"acos"				yylval.un_op_id = unary_operator::ACOS; return BUILTIN_FUNC1_;
"asin"				yylval.un_op_id = unary_operator::ASIN; return BUILTIN_FUNC1_;
"atan"				yylval.un_op_id = unary_operator::ATAN; return BUILTIN_FUNC1_;
"cos"				yylval.un_op_id = unary_operator::COS; return BUILTIN_FUNC1_;
"sin"				yylval.un_op_id = unary_operator::SIN; return BUILTIN_FUNC1_;
"tan"				yylval.un_op_id = unary_operator::TAN; return BUILTIN_FUNC1_;
"log"				yylval.un_op_id = unary_operator::LOG; return BUILTIN_FUNC1_;
"exp"				yylval.un_op_id = unary_operator::EXP; return BUILTIN_FUNC1_;
"cosh"				yylval.un_op_id = unary_operator::COSH; return BUILTIN_FUNC1_;
"sinh"				yylval.un_op_id = unary_operator::SINH; return BUILTIN_FUNC1_;
"tanh"				yylval.un_op_id = unary_operator::TANH; return BUILTIN_FUNC1_;
"sqr"				yylval.un_op_id = unary_operator::SQR; return BUILTIN_FUNC1_;
"sqrt"				yylval.un_op_id = unary_operator::SQRT; return BUILTIN_FUNC1_;
"abs"				yylval.un_op_id = unary_operator::ABS; return BUILTIN_FUNC1_;
"clamp"				yylval.un_op_id = unary_operator::CLAMP; return BUILTIN_FUNC1_;
"pixel"				yylval.un_op_id = unary_operator::PIXEL; return BUILTIN_FUNC1_;

"["|"]"|[-+*/()=<>,;f]		return *yytext;

[A-Z_][A-Za-z0-9_]*		{
				  string key(yytext);
  				  symtab_entry &entry = lookup_sym (key);
				  if (!entry)
				    {
				      yylval.undef_id_name = new string(yytext);
				      return UNDEF_ID_;
				    }

			          if (entry.kind != DEF_ID_)
				    yylval.obj = entry.obj;
				  else
				    yylval.def_id = entry.id;

				  return entry.kind;
				}

"e"				{
				  yylval.real = 2.71828182846;
				  return NUMBER_;
				}

"pi"				{
				  yylval.real = 3.1415926535;
				  return NUMBER_;
				}

0|[1-9][0-9]*			{
				  char *end;
				  yylval.real = std::strtod (yytext, &end);
				  return INTEGER_;
				}

(0|[1-9][0-9]*)(\.[0-9]+)?(e[+-]?[0-9]+)?	{
				  char *end;
				  yylval.real = std::strtod (yytext, &end);
				  return NUMBER_;
				}

[a-z]+				return KEYWORD_;

.				{
				  cout << "line " << yylineno
				       << ": invalid character " << *yytext << endl;

				  errors++;
				}
}

<COMMENT>{
[^*\n]*"*"*\n			yylineno++;
[^*\n]*"*"+[^/*]
[^*\n]*"*"+"/"			BEGIN (INITIAL);
}

