%{
// Procedural Texture Generator
// Paolo Bonzini
// esame di Elaborazione e Trasmissione delle Immagini
//
// Parser

#include "ptgen.h"

#define YYERROR_VERBOSE 1

static void yyerror (const char *s);

int errors = 0;

%}

/* The SR conflicts are caused by the two BUILTIN_FUNCx_ -> function
   rules.  These are correctly solved by shifting the ( and
   creating a single tree node -- creating an anonymous function and
   evaluating it would be way too inefficient. */
%expect 2
%debug
%defines
%output="y.tab.c"
%verbose

%union {
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
}

%token LET_ "let"
%token EQ_ "=="
%token NE_ "!="
%token LE_ "<="
%token GE_ ">="
%token ASSIGN_ ":="
%token PERLIN_ "perlin"
%token NOISE_ "noise"
%token CONVOLVE_ "convolve"
%token APPLY_ "apply"
%token TO_ "to"
%token CREATE_ "create"
%token GREYSCALE_ "greyscale"
%token RED_ "red"
%token GREEN_ "green"
%token BLUE_ "blue"
%token IMAGE_ "image"
%token SCALE_ "scale"
%token BIAS_ "bias"
%token SPLINE_ "spline"
%token MAP_ "map"
%token WITH_ "with"
%token IF_ "if"
%token DO_ "do"
%token WHILE_ "while"
%token ELSE_ "else"
%token THEN_ "then"
%token AND_ "and"
%token OR_ "or"
%token NOT_ "not"
%token XOR_ "xor"
%token X_ "x"
%token Y_ "y"
%token FROM_ "from"
%token RANGE_ "range"
%token OUTPUT_ "output"
%token OPERATION_ "operation"
%token BLEND_ "blend"
%token REPLACE_ "replace"
%token ADD_ "add"
%token SUBTRACT_ "subtract"
%token MULTIPLY_ "multiply"
%token SCREEN_ "screen"
%token COLOR_ "color"
%token HUE_ "hue"
%token VALUE_ "value"
%token SATURATION_ "saturation"
%token DISSOLVE_ "dissolve"
%token DIFFERENCE_ "difference"
%token OVERLAY_ "overlay"
%token LIGHTEN_ "lighten"
%token DARKEN_ "darken"
%token OPACITY_ "opacity"

%token KEYWORD_ "unrecognized keyword"

%token <un_op_id> BUILTIN_FUNC1_ "builtin 1-argument function"
%token <bin_op_id> BUILTIN_FUNC2_ "builtin 2-argument function"
%token <def_id> DEF_ID_
%token <undef_id_name> UNDEF_ID_ "undefined variable"
%token <img> IMAGE_DEF_
%token <nvec> VECTOR_DEF_
%token <nmatr> MATRIX_DEF_
%token <expr> NUMBER_DEF_
%token <fun> FUNC_DEF_
%token <real> NUMBER_
%token <real> INTEGER_

%right ":="
%left "if" "while"
%nonassoc "<=" '<' ">=" '>' "==" "!="
%left "or" "xor"
%left "and"
%left '+' '-'
%left '*' '/'
%right UMINUS "not"

%%

%type <img> image;
%type <fun> function_param;
%type <real> number_param;
%type <nmatr> matrix_param;
%type <nvec> vector_param;
%type <img> image_param;

program:
	declarations image opt_semicolon
	  {
	    if (!errors)
	      {
	        $2->build_graph ();
	        errors |= int ($2->write(*output_file, output_format));
	      }
	  }
	;

opt_semicolon:
	|
	';'
	;

declarations:
	declarations decl
	|
	;

decl:
	"let" { push_scope(); } scope_pushed decl.1 { pop_scope(); } ';'
	;

%destructor { pop_scope(); } scope_pushed;

%printer { cout << "variable scoping placeholder"; } scope_pushed;

scope_pushed:
	;

decl.1:
	vector_decl
	| matrix_decl
	| value_decl
	| image_decl
	| function_decl
	;

%destructor { if ($$) delete $$; } function;
%destructor { if ($$) delete $$; } function_with_parens;
%destructor { if ($$) delete $$; } number;
%destructor { if ($$) delete $$; } expression;
%destructor { if ($$) delete $$; } predicate;
%destructor { if ($$) delete $$; } number_literal;
%destructor { if ($$) delete $$; } func_eval;
%destructor { if ($$) delete $$; } arglist;
%destructor { if ($$) delete $$; } seq;

%printer { cout << "expression non-terminal"; } function
	function_with_parens number expression predicate number_literal
	arglist seq func_eval;

%type <expr> number;
%type <expr> expression;
%type <expr> func_eval;
%type <pred> predicate;
%type <expr> number_literal;
%type <seq_expr> arglist;
%type <seq_expr> seq;
%type <fun> function;
%type <fun> function_with_parens;
%type <undef_id_name> undef_id;

/* This non-terminal is here to provide a destructor and to duplicate
   the string before flex goes on with the lexing.  */

%destructor { if ($$) delete $$; } undef_id;
%printer { printf ("identifier \"%s\"", $$->c_str()); } undef_id;
undef_id: UNDEF_ID_ 
	  { $$ = $1; }
	;

value_decl:
	undef_id ":=" expression
	  { closure c(num_variables());
	    float num = $3->evaluate (&c);
	    number_literal *def = new number_literal (num);
	    declare_id (*$1, NUMBER_DEF_, def);
	    delete $1;
	    delete $3; }
	;

number:
	expression
	  { $$ = $1; }
	| DEF_ID_ ":=" number
	  { $$ = new var_assignment($3, $1); }
	| undef_id ":=" number
	  { $$ = new var_assignment($3, insert_var (*$1)); }
	;

expression:
	'(' number ')'
	  { $$ = $2; }
	| '(' seq ')'
	  { $$ = $2; }
	| NUMBER_DEF_
	  { $$ = new number_literal (*static_cast<number_literal *>($1)); }
	| number_literal
	  { $$ = $1; }
	| expression '+' expression
	  { $$ = new binary_operator($1, $3, binary_operator::PLUS); }
	| expression '-' expression
	  { $$ = new binary_operator($1, $3, binary_operator::MINUS); }
	| expression '*' expression
	  { $$ = new binary_operator($1, $3, binary_operator::TIMES); }
	| expression '/' expression
	  { $$ = new binary_operator($1, $3, binary_operator::DIVIDE); }
	| BUILTIN_FUNC2_ '(' expression ',' expression ')'
	  { $$ = new binary_operator($3, $5, $1); }
	| BUILTIN_FUNC1_ '(' expression ')'
	  { $$ = new unary_operator($3, $1); }
	| DEF_ID_
	  { $$ = new var_ref($1); }
	| undef_id
	  { $$ = NULL; yyerror ("undefined variable"); YYERROR; }
	| '-' expression %prec UMINUS
	  { $$ = new unary_operator($2, unary_operator::MINUS); }
	| func_eval
	  { $$ = $1; }
	| "if" predicate "then" expression "else" expression %prec "if"
	  { $$ = new if_then_else($2, $4, $6); }
	| "while" predicate "do" expression %prec "while"
	  { $$ = new while_do($2, $4); }
	;

func_eval:
	function_with_parens '(' arglist ')'
	  { if ($1->get_num_args() != $3->size())
	      {
		yyerror ("argument number mismatch");
		YYERROR;
	      }
	    $$ = new function_eval($1, $3);
	  }
	;

predicate :
	predicate "and" predicate
	  { $$ = new and_predicate($1, $3); }
	| predicate "or" predicate
	  { $$ = new or_predicate($1, $3); }
	| predicate "xor" predicate
	  { $$ = new xor_predicate($1, $3); }
	| "not" predicate
	  { $$ = new not_predicate($2); }
	| expression "!=" expression
	  { $$ = new order_predicate($1, $3, order_predicate::NE); }
	| expression "==" expression
	  { $$ = new order_predicate($1, $3, order_predicate::EQ); }
	| expression ">=" expression
	  { $$ = new order_predicate($1, $3, order_predicate::GE); }
	| expression "<=" expression
	  { $$ = new order_predicate($1, $3, order_predicate::LE); }
	| expression '<' expression
	  { $$ = new order_predicate($1, $3, order_predicate::LT); }
	| expression '>' expression
	  { $$ = new order_predicate($1, $3, order_predicate::GT); }
	;

number_literal:
	NUMBER_
	  { $$ = new number_literal($1); }
	| INTEGER_
	  { $$ = new number_literal($1); }
	;

seq:
	number ';' number
	  { $$ = new seq(); $$->push_back($1); $$->push_back($3); }
	| seq ';' number
	  { $$ = $1; $$->push_back($3); }
	;

arglist:
	expression
	  { $$ = new seq(); $$->push_back($1); }
	| arglist ',' expression
	  { $$ = $1; $$->push_back($3); }
	;

%destructor { if ($$) delete $$; } vector expressions;

%printer { cout << "vector definition non-terminal"; }
	vector expressions;

%type <vec> vector;
%type <vec> expressions;

vector_decl:
	undef_id ":=" vector
	  { closure c(num_variables());
	    numeric_vector *vec = $3->evaluate (&c);
	    declare_id (*$1, VECTOR_DEF_, vec);
	    delete $3;
	    delete $1; }
	;

vector:
	'[' expressions ']'
	  { $$ = $2; }
	;

expressions:
	expressions ',' expression
	  { $$ = $1; $$->push_back ($3); }
	| expression
	  { $$ = new expr_vector (); $$->push_back ($1); }
	;

%destructor { if ($$) delete $$; } vectors;

%printer { cout << "matrix definition non-terminal"; }
	matrix vectors;

%type <matr> matrix;
%type <matr> vectors;

matrix_decl:
	undef_id ":=" matrix
	  { closure c(num_variables());
	    numeric_matrix *matr = $3->evaluate (&c);
	    declare_id (*$1, MATRIX_DEF_, matr);
	    delete $3;
	    delete $1; }
	;

matrix: '[' vectors ']'
	  { $$ = $2; }
	;

vectors:
	vectors vector
	  { $$ = $1; $$->push_back ($2); }
	| vector
	  { $$ = new expr_matrix ($1->size()); $$->push_back ($1); }
	;

%destructor { if ($$) delete $$; } interp interp_type;

%printer { cout << "interp definition non-terminal"; }
	interp interp_type;

%type <interp> interp interp_type;

interp_type: "map"
	  {
	    $$ = new linear_interpolator ();
	  }
	| "spline" "map"
	  {
	    $$ = new spline_interpolator ();
	  }
	;

interp:
	interp_type vector_param "to" vector_param
	  {
	    $$ = $1;
	    if ($2->size() != $4->size())
	      {
		yyerror ("mismatch in vector sizes");
		YYERROR;
	      }

	    const numeric_vector &from = *$2;
	    const numeric_vector &to = *$4;

	    for (int i = 1; i < $2->size(); i++)
	      {
	        float x0 = from[i - 1];
	        float x1 = from[i];
	        float y0 = to[i - 1];
	        float y1 = to[i];
		if (x0 != x1)
		  $$->add_range (x0, x1, y0, y1);
	      }

	    if (!$2->declared) delete $2;
	    if (!$4->declared) delete $4;
	  }
	;

%printer { cout << "function definition non-terminal"; }
	argdecl argdecl.1;

%type <argcount> argdecl;
%type <argcount> argdecl.1;

// FIXME: allow recursion
function_decl:
	undef_id ":=" function
	  { declare_id (*$1, FUNC_DEF_, $3);
	    delete $1; }
	;

function_with_parens:
	function
	  { $$ = $1; }
	| '(' function_with_parens ')'
	  { $$ = $2; }
	;

function:
	'f'
	  { push_scope (); }
	  '(' argdecl ')' '=' number
	  { $$ = new function($7, $4, num_variables ()); pop_scope (); }
	| FUNC_DEF_
	  { $$ = $1; }
	| interp
	  { $$ = new interp_eval($1); }
	| BUILTIN_FUNC1_
	  { $$ = new function(new unary_operator(new var_ref(0), $1), 1, 0); }
	| BUILTIN_FUNC2_
	  { $$ = new function(new binary_operator(new var_ref(0),
						  new var_ref(1), $1), 2, 0); }
	;

argdecl: 
	  { $$ = 0; }
	| argdecl.1
	  { $$ = $1; }
	;

argdecl.1: undef_id
	  { insert_var (*$1); delete $1; $$ = 1; }
	| argdecl.1 ',' undef_id
	  { insert_var (*$3); delete $3; $$ = $1 + 1; }
	;

%printer { cout << "parameter to command"; }
	function_param number_param matrix_param image_param;

vector_param:
	VECTOR_DEF_ { $$ = $1; }
	| { push_scope(); } scope_pushed vector { pop_scope(); $$ = $3->evaluate(); }
	;

matrix_param:
	MATRIX_DEF_ { $$ = $1; }
	| { push_scope(); } scope_pushed matrix { pop_scope(); $$ = $3->evaluate(); }
	;

function_param:
	{ push_scope(); } scope_pushed function { pop_scope(); $$ = $3; }
	;

number_param:
	{ push_scope(); } scope_pushed number { pop_scope(); $$ = $3->evaluate(); }
	;

image_param: IMAGE_DEF_
	  { $$ = $1; }
	| '(' image ')'
	  { $$ = $2; }
	;

%destructor { if ($$) delete $$; } image_command convolve_command apply_command
	create_command turbulence_command noise_command
	greyscale_command;

%printer { cout << "image definition non-terminal"; }
	image_command convolve_command apply_command
	create_command turbulence_command noise_command
	greyscale_command;

%type <img> image_command;
%type <img> convolve_command;
%type <img> apply_command;
%type <img> create_command;
%type <img> turbulence_command;
%type <img> noise_command;
%type <img> greyscale_command;

image_decl:
	undef_id ":=" image
	  { declare_id (*$1, IMAGE_DEF_, $3);
	    delete $1; }
	;

image:
	image_command
	| image_param
	;

image_command:
	convolve_command
	| apply_command
	| create_command
	| turbulence_command
	| noise_command
	| greyscale_command
	;

%printer { cout << "image placeholder"; } image_pushed;
%destructor { delete pop_image(); } image_pushed;

image_pushed:
	;

convolve_command:
	"convolve"
	  { push_image(new convolve_command ()); } image_pushed
	  image_param "with" matrix_param convolve_params
	  { if (($6->size() & $6->row_size() & 1) == 0)
	      {
		yyerror ("Convolution matrix sizes should be odd");
		YYERROR;
	      }

	    top_image()->set_param (image::CONVOLUTION_MATRIX, $6);
	    top_image()->set_param (image::SRC_IMAGE, $4);
	    $$ = pop_image (); }
	;

convolve_params:
	| scale
	| bias
	| scale bias
	| bias scale
	;

scale:
	"scale" number_param
	  { top_image()->set_param (image::SCALE, $2); }
	;

bias:
	"bias" number_param
	  { top_image()->set_param (image::BIAS, $2); }
	;

apply_command:
	"apply" function_param
	  {
	    if ($2->get_num_args () != 3 && $2->get_num_args () != 1)
	      {
		yyerror ("expected 1- or 3-argument function");
		YYERROR;
	      }
	    push_image (new apply_colormap_command ());
	    top_image()->set_param (image::OUT_RED, $2);
	  } image_pushed
	  "to" image_param
	  { top_image()->set_param (image::SRC_IMAGE, $6);
	    $$ = pop_image (); }

	| "apply" "red" function_param "green" function_param
	  "blue" function_param
	  {
	    if (($3->get_num_args () != 3 && $3->get_num_args () != 1)
	        || ($5->get_num_args () != 3 && $5->get_num_args () != 1)
	        || ($7->get_num_args () != 3 && $7->get_num_args () != 1))
	      {
		yyerror ("expected 1- or 3-argument function");
		YYERROR;
	      }
	    push_image (new apply_colormap_command ());
	    top_image()->set_param (image::OUT_RED, $3);
	    top_image()->set_param (image::OUT_GREEN, $5);
	    top_image()->set_param (image::OUT_BLUE, $7);
	  } image_pushed
	  "to" image_param
	  { top_image()->set_param (image::SRC_IMAGE, $11);
	    $$ = pop_image (); }

	| "apply" "x" function_param "y" function_param
	  {
	    if ($3->get_num_args () != 2 ||
	        $5->get_num_args () != 2)
	      {
		yyerror ("expected 2-argument function");
		YYERROR;
	      }
	    push_image (new apply_command ());
	    top_image()->set_param (image::X_DISPLACEMENT, $3);
	    top_image()->set_param (image::Y_DISPLACEMENT, $5);
	  } image_pushed
	  "to" image_param
	  { top_image()->set_param (image::SRC_IMAGE, $9);
	    $$ = pop_image (); }

	| "apply" image_param
	  { push_image(new apply_op_command ()); } image_pushed
	  "to" image_param operation opt_opacity
	  { top_image()->set_param (image::SRC_IMAGE_2, $2);
	    top_image()->set_param (image::SRC_IMAGE, $6);
	    $$ = pop_image (); }
	;

create_command:
	"create" "image" "from" function_param
	  {
	    if ($4->get_num_args () != 2)
	      {
		yyerror ("expected 2-argument function");
		YYERROR;
	      }
	    push_image (new create_from_formula_command ());
	    top_image()->set_param (image::OUT_RED, $4);
	    $$ = pop_image (); }
	| "create" "image" "from" "red" function_param "green" function_param "blue" function_param
	  {
	    if ($5->get_num_args () != 2 ||
	        $7->get_num_args () != 2 ||
	        $9->get_num_args () != 2)
	      {
		yyerror ("expected 2-argument function");
		YYERROR;
	      }
	    push_image (new create_from_formula_command ());
	    top_image()->set_param (image::OUT_RED, $5);
	    top_image()->set_param (image::OUT_GREEN, $7);
	    top_image()->set_param (image::OUT_BLUE, $9);
	    $$ = pop_image (); }
	| "create" "image" "from" "red" image_param "green" image_param "blue" image_param 
	  { push_image (new create_from_channels_command ()); } image_pushed
	  { top_image()->set_param (image::OUT_RED, $5);
	    top_image()->set_param (image::OUT_GREEN, $7);
	    top_image()->set_param (image::OUT_BLUE, $9);
	    $$ = pop_image (); }
	;

turbulence_command:
	"create" "perlin" "noise"
	  { push_image (new perlin_noise_command ()); } image_pushed
	  opt_scale
	  out_range
	  { $$ = pop_image (); }
	;

opt_scale:
	  { }
	| scale
	  { }
	;

out_range:
	  { }
	| "output" "range" out_range_function
	  { }
	;

out_range_function:
	function_param
	  { if ($1->get_num_args () != 1)
	      {
		yyerror ("expected 1-argument function");
		YYERROR;
	      }
	    top_image()->set_param (image::OUT_RED, $1);
	  }
	| "red" function_param "green" function_param "blue" function_param
	  { if ($2->get_num_args () != 1
		|| $4->get_num_args () != 1
		|| $6->get_num_args () != 1)
	      {
		yyerror ("expected 1-argument function");
		YYERROR;
	      }
	    top_image()->set_param (image::OUT_RED, $2);
	    top_image()->set_param (image::OUT_GREEN, $4);
	    top_image()->set_param (image::OUT_BLUE, $6);
	  }
	;

noise_command:
	"create" "noise"
	  { push_image (new noise_command ()); } image_pushed
	  out_range
	  { $$ = pop_image (); }
	;

greyscale_command:
	"create" "greyscale" "image" "from"
	  { push_image (new greyscale_command ()); } image_pushed
	  image_param
	  { top_image()->set_param (image::SRC_IMAGE, $7);
	    $$ = pop_image (); }
	;

operation:
	/* empty */
	  { top_image()->set_param (image::OPERATION, image::BLEND); }
	| "operation" "blend"
	  { top_image()->set_param (image::OPERATION, image::BLEND); }
	| "operation" "dissolve"
	  { top_image()->set_param (image::OPERATION, image::DISSOLVE); }
	| "operation" "add"
	  { top_image()->set_param (image::OPERATION, image::ADD); }
	| "operation" "subtract"
	  { top_image()->set_param (image::OPERATION, image::SUBTRACT); }
	| "operation" "difference"
	  { top_image()->set_param (image::OPERATION, image::DIFFERENCE); }
	| "operation" "multiply"
	  { top_image()->set_param (image::OPERATION, image::MULTIPLY); }
	| "operation" "screen"
	  { top_image()->set_param (image::OPERATION, image::SCREEN); }
	| "operation" "overlay"
	  { top_image()->set_param (image::OPERATION, image::OVERLAY); }
	| "operation" "replace" "color"
	  { top_image()->set_param (image::OPERATION, image::COLOR); }
	| "operation" "replace" "hue"
	  { top_image()->set_param (image::OPERATION, image::HUE); }
	| "operation" "replace" "value"
	  { top_image()->set_param (image::OPERATION, image::VALUE); }
        | "operation" "replace" "saturation"
	  { top_image()->set_param (image::OPERATION, image::SATURATION); }
	| "operation" "lighten"
	  { top_image()->set_param (image::OPERATION, image::LIGHTEN); }
	| "operation" "darken"
	  { top_image()->set_param (image::OPERATION, image::DARKEN); }
	;

opt_opacity:
	"opacity" number_param
	  { if ($2 < 0.0 || $2 > 1.0)
	      {
		yyerror ("expected number between 0 and 1");
		YYERROR;
	       }
	    top_image()->set_param (image::OPACITY, $2); }
	| /* empty */
	;
%%

void
yyerror (const char *s)
{
  errors = 1;
  fprintf (stderr, "line %d: %s\n", yylineno, s);
}
