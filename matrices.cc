// Procedural Texture Generator
// Paolo Bonzini
// esame di Elaborazione e Trasmissione delle Immagini
//
// Routine di gestione di matrici e vettori

#include "ptgen.h"

// Classe numeric_matrix.
//
// Rappresenta una matrice gia' valutata.

numeric_matrix::~numeric_matrix()
{
  for (iterator it = begin(); it < end(); it++)
    {
      numeric_vector *vec = (*it);
      delete vec;
    }
}

// Classe expr_matrix.
//
// Rappresenta la definizione di una matrice prima di essere
// valutata.

expr_matrix::~expr_matrix()
{
  for (iterator it = begin(); it < end(); it++)
    {
      expr_vector *vec = (*it);
      delete vec;
    }
}

numeric_matrix *expr_matrix::evaluate (closure *c) const
{
  numeric_matrix *matr = new numeric_matrix (row_size()); 
  for (const_iterator it = begin(); it < end(); it++)
    matr->push_back ((*it)->evaluate (c));

  return matr;
}

// Classe expr_vector.
//
// Rappresenta la definizione di un vettore prima di essere
// valutata.

expr_vector::~expr_vector()
{
  for (iterator it = begin(); it < end(); it++)
    {
      expression *expr = (*it);
      delete expr;
    }
}

numeric_vector *expr_vector::evaluate (closure *c) const
{
  numeric_vector *vec = new numeric_vector (); 
  for (const_iterator it = begin(); it < end(); it++)
    vec->push_back ((*it)->evaluate (c));

  return vec;
}


