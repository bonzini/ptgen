// Procedural Texture Generator
// Paolo Bonzini
// esame di Elaborazione e Trasmissione delle Immagini
//
// Routine di valutazione delle espressioni

#ifndef PTGEN_EXPR_H
#define PTGEN_EXPR_H

// Classe closure.
//
// Rappresenta gli argomenti e le variabili usate nella valutazione
// di una funzione.  Creare un oggetto per ogni valutazione permette
// la ricorsione.
class closure
  {
    int num_vars;
    float *variables;
  public:
    explicit closure (int nvars) : num_vars (nvars), variables (NULL)
      {
        variables = new float [num_vars];
      }

    ~closure ()
      {
        delete[] variables;
      }

    inline int get_num_vars () const
      {
        return num_vars;
      }

    inline float get_var (int n)
      {
        return variables[n];
      }

    inline void set_var (int n, float value)
      {
        variables[n] = value;
      }
  };

// Classe astratta expression.
//
// Un'espressione puo' essere valutata ritornando un oggetto float.
class expression : public ptgen_object
  {
  public:
    expression () : ptgen_object () {};
    float evaluate () const 
      {
        closure c(num_variables());
        return evaluate (&c);
      }

    virtual float evaluate (closure *c) const = 0;
  };

// Classe seq.
//
// Rappresenta una sequenza di espressioni; quando valutata ritorna
// il valore dell'ultima espressione, ma viene usata anche per contenere
// gli argomenti di una funzione definita dall'utente

class seq : public expression
  {
    vector <expression*> stmts;

  public:
    seq () : expression (), stmts() {};
    ~seq ()
      {
	this->expression::~expression ();
        for (vector <expression*>::iterator it = stmts.begin();
	     it < stmts.end(); it++)
	  delete *it;
       }

    void push_back (expression *stmt)
      {
        stmts.push_back (stmt);
      }

    int size () const
      {
        return stmts.size();
      }

    void fill_closure (closure *dest, closure *src) const;
    virtual float evaluate (closure *c) const;
  };

// Classe astratta ptgen_function.
//
// Rappresenta un'espressione che chiama una funzione definita dall'utente.
// Contiene metodi aggiuntivi per unire in una sola chiamata la creazione
// dell'oggetto closure e la valutazione vera e propria.

class ptgen_function : public expression
  {
    int num_args;
    int num_vars;

  public:
    ptgen_function (int num_arguments, int num_variables) : num_args (num_arguments), num_vars (num_variables) {};

    virtual float apply (float x) const = 0;
    virtual float apply (float x, float y) const = 0;
    virtual float apply (float r, float g, float b,
			 float rw, float gw, float bw) const = 0;

    inline int get_num_args () const
      {
	return num_args;
      }

    inline int get_num_vars () const
      {
	return num_vars;
      }

    closure new_closure () const
      {
        return closure (get_num_args() + get_num_vars());
      }
  };

// Classe interp_eval.
//
// Rappresenta un'espressione che chiama un interpolatore.
// I metodi aggiuntivi per unire in una sola chiamata la creazione
// dell'oggetto closure e la valutazione vera e propria chiamano
// direttamente l'interpolatore senza creare inutilmente l'oggetto.

class interp_eval : public ptgen_function
  {
    interpolator *interp;

  public:
    interp_eval (interpolator *_interp) : ptgen_function (1, 0), interp(_interp) { };

    ~interp_eval()
      {
	this->ptgen_function::~ptgen_function ();
      }

    float apply (float x) const
      {
        float f = interp->apply(x);
	if (f < 0.0) return 0.0;
	if (f < 1.0) return f;
	return 1.0;
      }

    float apply (float x, float y) const
      {
        float f = interp->apply(x);
	if (f < 0.0) return 0.0;
	if (f < 1.0) return f;
	return 1.0;
      }

    float apply (float r, float g, float b,
			 float rw, float gw, float bw) const
      {
        float f = interp->apply(r * rw + g * gw + b * bw);
	if (f < 0.0) return 0.0;
	if (f < 1.0) return f;
	return 1.0;
      }

    float evaluate (closure *c) const
      {
        return interp->apply(c->get_var(0));
      }
  };

// Classe function.
//
// Rappresenta un'espressione che chiama una funzione definita
// con la sua espressione matematica.

class function : public ptgen_function
  {
    expression *definition;

  public:
    function (expression *_definition, int _num_args, int _num_vars) : ptgen_function (_num_args, _num_vars), definition(_definition) {};

    ~function()
      {
	this->ptgen_function::~ptgen_function ();
        delete definition;
      }

    float apply (float x) const
      {
        closure c(1 + get_num_vars());
        c.set_var(0, x);
	float f = definition->evaluate(&c);
	if (f < 0.0) return 0.0;
	if (f < 1.0) return f;
	return 1.0;
      }

    float apply (float x, float y) const
      {
        closure c(2 + get_num_vars());
        c.set_var(0, x);
        c.set_var(1, y);
	float f = definition->evaluate(&c);
	if (f < 0.0) return 0.0;
	if (f < 1.0) return f;
	return 1.0;
      }

    float apply (float r, float g, float b,
			 float rw, float gw, float bw) const
      {
	float f;
	if (get_num_args() == 1)
	  {
	    closure c(1 + get_num_vars());
	    c.set_var(0, r * rw + g * gw + b * bw);
	    f = definition->evaluate(&c);
          }
	else
	  {
	    closure c(3 + get_num_vars());
	    c.set_var(0, r);
	    c.set_var(1, g);
	    c.set_var(2, b);
	    f = definition->evaluate(&c);
          }
	if (f < 0.0) return 0.0;
	if (f < 1.0) return f;
	return 1.0;
      }

    float evaluate (closure *c) const
      {
        return definition->evaluate(c);
      }
  };

// Classe unary_operator.
//
// Rappresenta una funzione built-in ad un argomento, sia un operatore
// come il meno unario, sia una funzione matematica come seno o coseno

class unary_operator : public expression
  {
  public:
    enum op { RAND, TILE, FRAC, COS, SIN, TAN, ACOS, ASIN, ATAN,
              LOG, EXP, COSH, SINH, TANH, MINUS, SQR, SQRT, ABS, CLAMP,
	      PIXEL };

  private:
    expression *num;
    enum op op_id;

  public:
    unary_operator (expression *_num, enum op _op_id) : expression (), num(_num), op_id(_op_id) {};
    ~unary_operator()
      {
	this->expression::~expression ();
        delete num;
      }

    float evaluate (closure *c) const;
  };

// Classe binary_operator.
//
// Rappresenta una funzione built-in a due argomento, sia un operatore
// aritmetico, sia una funzione matematica come hypot

class binary_operator : public expression
  {
  public:
    enum op { PLUS, MINUS, TIMES, DIVIDE, MIN, MAX, HYPOT, ATAN2 };

  private:
    expression *lhs, *rhs;
    enum op op_id;

  public:
    binary_operator (expression *_lhs, expression *_rhs, enum op _op_id) : expression (), lhs(_lhs), rhs(_rhs), op_id(_op_id) {};
    ~binary_operator()
      {
	this->expression::~expression ();
        delete lhs;
        delete rhs;
      }

    float evaluate (closure *c) const;
  };

// Classe var_assignment.
//
// Rappresenta un'assegnamento e come in C ritorna il valore assegnato

class var_assignment : public expression
  {
    expression *num;
    int id;

  public:
    var_assignment (expression *_num, int _id) : expression (), num(_num), id(_id) {};
    ~var_assignment()
      {
	this->expression::~expression ();
        delete num;
      }

    float evaluate (closure *c) const;
  };

// Classe var_ref.
//
// Rappresenta un riferimento a una variabile

class var_ref : public expression
  {
    int id;

  public:
    var_ref (int _id) : expression (), id(_id) {};
    float evaluate (closure *c) const;
  };

// Classe number_literal.
//
// Rappresenta un numero

class number_literal : public expression
  {
    float num;

  public:
    number_literal (float _num) : expression (), num(_num) {};
    float evaluate (closure *c) const;
  };

// Classe astratta predicate.
//
// L'interfaccia esposta dalle sottoclassi di predicate e'
// la stessa delle sottoclass di expr, ma il metodo evaluate
// ritorna bool.  E' necessario comunque passare un puntatore
// a closure per valutare le espressioni.

class predicate : public ptgen_object
  {
  public:
    predicate () : ptgen_object () {};
    virtual bool evaluate (closure *c) const = 0;
  };

// Classe order_predicate.
//
// Implementa gli operatori relazionali.

class order_predicate : public predicate
  {
  public:
    enum op { EQ, LT, LE, GT, GE, NE };

  private:
    expression *lhs, *rhs;
    enum op op_id;

  public:
    order_predicate (expression *_lhs, expression *_rhs, enum op _op_id) : predicate (), lhs(_lhs), rhs(_rhs), op_id(_op_id) {};
    ~order_predicate()
      {
	this->predicate::~predicate ();
        delete lhs;
        delete rhs;
      }

    bool evaluate (closure *c) const;
  };

// Classe astratta bin_predicate.
//
// Superclasse per gli operatori booleani binari.

class bin_predicate : public predicate
  {
  protected:
    predicate *lhs, *rhs;

  public:
    bin_predicate (predicate *_lhs, predicate *_rhs) : predicate (), lhs(_lhs), rhs(_rhs) {};
    ~bin_predicate()
      {
	this->predicate::~predicate ();
        delete lhs;
        delete rhs;
      }

  };

// Classi and_predicate, or_predicate e xor_predicate
//
// Implementano gli operatori booleani binari.

class and_predicate : public bin_predicate
  {
  public:
    and_predicate (predicate *_lhs, predicate *_rhs) : bin_predicate (_lhs, _rhs) {};
    bool evaluate (closure *c) const;
  };

class or_predicate : public bin_predicate
  {
  public:
    or_predicate (predicate *_lhs, predicate *_rhs) : bin_predicate (_lhs, _rhs) {};
    bool evaluate (closure *c) const;
  };

class xor_predicate : public bin_predicate
  {
  public:
    xor_predicate (predicate *_lhs, predicate *_rhs) : bin_predicate (_lhs, _rhs) {};
    bool evaluate (closure *c) const;
  };

// Classe not_predicate
//
// Implementa ovviamente l'operatore not.

class not_predicate : public predicate
  {
  protected:
    predicate *pred;

  public:
    not_predicate (predicate *_pred) : predicate (), pred(_pred) {};
    ~not_predicate()
      {
	this->predicate::~predicate ();
        delete pred;
      }

    bool evaluate (closure *c) const;
  };

// Classe if_then_else
//
// Ritorna il risultato della valutazione di un'espressione
// a seconda del valore (vero/falso) del predicato.  L'operatore
// ?: del C valuta sono uno dei due operandi, per cui solo una
// delle due espressioni viene valutata.

class if_then_else : public expression
  {
    predicate *cond;
    expression *then_expr, *else_expr;

  public:
    if_then_else (predicate *_cond, expression *_then, expression *_else): cond(_cond), then_expr (_then), else_expr (_else) {};
    ~if_then_else()
      {
	this->expression::~expression ();
        delete cond;
        delete then_expr;
        delete else_expr;
      }

    float evaluate (closure *c) const;
  };

// Classe while_do
//
// Ritorna il risultato dell'ultima valutazione dell'espressione,
// o zero se gia' all'ingresso del ciclo il predicato e' falso.

class while_do : public expression
  {
    predicate *cond;
    expression *body;

  public:
    while_do (predicate *_cond, expression *_body): cond(_cond), body (_body) {};
    ~while_do()
      {
	this->expression::~expression ();
        delete cond;
        delete body;
      }

    float evaluate (closure *c) const;
  };

// Classe function_eval
//
// Rappresenta la valutazione di una funzione definita dall'utente
// Crea un nuovo oggetto closure e lo passa all'oggetto function

class function_eval : public expression
  {
    ptgen_function *f;
    seq *arguments;

  public:
    function_eval (ptgen_function *_f, seq *_arguments) : expression (), f(_f), arguments(_arguments) {};
    ~function_eval ()
      {
	this->expression::~expression ();
        delete arguments;
      }

    inline int get_num_args () const
      {
        return arguments->size();
      }

    float evaluate (closure *c) const;
  };

#endif
