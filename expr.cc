// Procedural Texture Generator
// Paolo Bonzini
// esame di Elaborazione e Trasmissione delle Immagini
//
// Routine di valutazione delle espressioni

#include "ptgen.h"
#include <cmath>

// Classe seq.
//
// Rappresenta una sequenza di espressioni; quando valutata ritorna
// il valore dell'ultima espressione, ma viene usata anche per contenere
// gli argomenti di una funzione definita dall'utente

float seq::evaluate (closure *c) const
{
  float result = 0.0;
  for (vector <expression*>::const_iterator it = stmts.begin();
       it < stmts.end(); it++)
    result = (*it)->evaluate (c);

  return result;
}

void seq::fill_closure (closure *dest, closure *src) const
{
  int i = 0;

  // Valuta le espressioni e ne assegna ciascuna a una variabile
  for (vector <expression*>::const_iterator it = stmts.begin();
       it < stmts.end(); it++)
    dest->set_var (i++, (*it)->evaluate (src));
}

// Classe unary_operator.
//
// Rappresenta una funzione built-in ad un argomento, sia un operatore
// come il meno unario, sia una funzione matematica come seno o coseno

float unary_operator::evaluate (closure *c) const
{
  float n;
  double dummy;

  n = num->evaluate (c);
  switch (op_id)
  {
    case RAND: return randf() * n;
    case FRAC: n = std::modf (n, &dummy); return n < 0 ? n + 1.0 : n;
    case ACOS: return std::acos(n);
    case ASIN: return std::asin(n);
    case ATAN: return std::atan(n);
    case COS: return std::cos(n);
    case SIN: return std::sin(n);
    case TAN: return std::tan(n);
    case LOG: return std::log(n);
    case EXP: return std::exp(n);
    case COSH: return std::cosh(n);
    case SINH: return std::sinh(n);
    case TANH: return std::tanh(n);
    case MINUS: return -n;
    case SQR: return n*n;
    case SQRT: return std::sqrt(n);
    case ABS: return n < 0.0 ? -n : n;
    case CLAMP: return n < 0.0 ? 0.0 : n > 1.0 ? 1.0 : n;
    case PIXEL: return n * image::width;
    case TILE: 
      n = n < 0.0 ? -n : n;
      n = 2 * std::modf (n / 2, &dummy);
      return n < 1 ? n : 2-n;
  }

  abort ();
}

// Classe binary_operator.
//
// Rappresenta una funzione built-in a due argomento, sia un operatore
// aritmetico, sia una funzione matematica come hypot

float binary_operator::evaluate (closure *c) const
{
  float n1, n2;
  n1 = lhs->evaluate (c);
  n2 = rhs->evaluate (c);
  switch (op_id)
  {
    case PLUS: return n1 + n2;
    case MINUS: return n1 - n2;
    case TIMES: return n1 * n2;
    case DIVIDE: return n1 / n2;
    case HYPOT: return std::sqrt (n1*n1+n2*n2);
    case ATAN2: return std::atan2 (n1, n2);
    case MIN: return n1 < n2 ? n1 : n2;
    case MAX: return n1 > n2 ? n1 : n2;
  }

  abort ();
}

// Classe var_assignment.
//
// Rappresenta un'assegnamento e come in C ritorna il valore assegnato

float var_assignment::evaluate (closure *c) const
{
  float n;
  n = num->evaluate (c);
  c->set_var(id, n);
  return n;
}

// Classe var_ref.
//
// Rappresenta un riferimento a una variabile

float var_ref::evaluate (closure *c) const
{
  return c->get_var(id);
}

// Classe number_literal.
//
// Rappresenta un numero

float number_literal::evaluate (closure *c) const
{
  return num;
}

// Classe order_predicate.
//
// Implementa gli operatori relazionali

bool order_predicate::evaluate (closure *c) const
{
  float n1, n2;
  n1 = lhs->evaluate (c);
  n2 = rhs->evaluate (c);

  switch (op_id) {
    case EQ: return n1 == n2;
    case NE: return n1 != n2;
    case LE: return n1 <= n2;
    case LT: return n1 < n2;
    case GE: return n1 >= n2;
    case GT: return n1 > n2;
  }

  abort ();
};

// Classi and_predicate, or_predicate e xor_predicate
//
// Implementano gli operatori booleani binari.

bool and_predicate::evaluate (closure *c) const
{
  return lhs->evaluate(c) && rhs->evaluate(c);
};

bool or_predicate::evaluate (closure *c) const
{
  return lhs->evaluate(c) || rhs->evaluate(c);
};

bool xor_predicate::evaluate (closure *c) const
{
  return lhs->evaluate(c) ^ rhs->evaluate(c);
};

// Classe not_predicate
//
// Implementa ovviamente l'operatore not.

bool not_predicate::evaluate (closure *c) const
{
  return !pred->evaluate(c);
};

// Classe if_then_else
//
// Ritorna il risultato della valutazione di un'espressione
// a seconda del valore (vero/falso) del predicato.  L'operatore
// ?: del C valuta sono uno dei due operandi, per cui solo una
// delle due espressioni viene valutata.

float if_then_else::evaluate (closure *c) const
{
  return cond->evaluate(c) ? then_expr->evaluate(c) : else_expr->evaluate(c);
};

// Classe while_do
//
// Ritorna il risultato dell'ultima valutazione dell'espressione,
// o zero se gia' all'ingresso del ciclo il predicato e' falso.

float while_do::evaluate (closure *c) const
{
  float n = 0.0;
  while (cond->evaluate(c))
    n = body->evaluate(c);

  return n;
};

// Classe function_eval
//
// Rappresenta la valutazione di una funzione definita dall'utente
// Crea un nuovo oggetto closure e lo passa all'oggetto function

float function_eval::evaluate (closure *c) const
{
  closure new_c = f->new_closure();
  arguments->fill_closure (&new_c, c);
  return f->evaluate (&new_c);
}
