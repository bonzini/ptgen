// Procedural Texture Generator
// Paolo Bonzini
// esame di Elaborazione e Trasmissione delle Immagini
//
// Routine di gestione di matrici e vettori
//
// La maggior parte delle definizioni servono per fornire anche per
// queste classi gli operatori e i tipi che vengono definiti dalla
// classe vector della STL.

#ifndef PTGEN_MATRICES_H
#define PTGEN_MATRICES_H

// Classe numeric_vector.
//
// Rappresenta una matrice gia' valutata.

class numeric_vector : public ptgen_object
  {
    typedef vector<float> float_vec;
    float_vec numbers;

  public:
    typedef float_vec::iterator iterator;
    typedef float_vec::const_iterator const_iterator;
    typedef float_vec::reference reference;
    typedef float_vec::const_reference const_reference;

    numeric_vector (): ptgen_object(), numbers () { };
    reference operator[] (int i) { return numbers[i]; };
    const_reference operator[] (int i) const { return numbers[i]; };

    int size (void) const { return numbers.size(); }
    void push_back (float number) { numbers.push_back(number); }

    iterator begin() { return numbers.begin(); }
    iterator end() { return numbers.end(); }

    const_iterator begin() const { return numbers.begin(); }
    const_iterator end() const { return numbers.end(); }
  };

// Classe numeric_matrix.
//
// Rappresenta una matrice gia' valutata.

class numeric_matrix : public ptgen_object
  {
    typedef vector<numeric_vector *> complex_matr;
    complex_matr rows;
    int n_columns;

  public:
    typedef complex_matr::iterator iterator;
    typedef complex_matr::const_iterator const_iterator;

    numeric_matrix (int columns): ptgen_object(), rows (), n_columns (columns) { };
    ~numeric_matrix ();

    numeric_vector &operator[] (int i) const { return *(rows[i]); };

    bool push_back (numeric_vector *row) { 
      if (row->size() == n_columns)
        {
          rows.push_back (row);
          return true;
        }
      else
        return false;
    }

    int size (void) const { return rows.size(); }
    int row_size (void) const { return n_columns; }

    iterator begin() { return rows.begin(); }
    iterator end() { return rows.end(); }

    const_iterator begin() const { return rows.begin(); }
    const_iterator end() const { return rows.end(); }
  };

// Classe expr_vector.
//
// Rappresenta la definizione di un vettore prima di essere
// valutata.

class expr_vector : public ptgen_object
  {
    typedef vector<expression * > expr_vec;
    expr_vec exprs;

  public:
    typedef expr_vec::iterator iterator;
    typedef expr_vec::const_iterator const_iterator;

    expr_vector (): ptgen_object(), exprs () { };
    ~expr_vector ();

    expression &operator[] (int i) const { return *(exprs[i]); };
    int size (void) const { return exprs.size(); }
    void push_back (expression *expr) { exprs.push_back(expr); }

    iterator begin() { return exprs.begin(); }
    iterator end() { return exprs.end(); }

    const_iterator begin() const { return exprs.begin(); }
    const_iterator end() const { return exprs.end(); }

    numeric_vector *evaluate () const
      {
        closure c(num_variables());
        return evaluate (&c);
      }

    numeric_vector *evaluate (closure *c) const;
  };

// Classe expr_matrix.
//
// Rappresenta la definizione di una matrice prima di essere
// valutata.

class expr_matrix : public ptgen_object
  {
    typedef vector<expr_vector *> expr_matr;
    expr_matr rows;
    int n_columns;

  public:
    typedef expr_matr::iterator iterator;
    typedef expr_matr::const_iterator const_iterator;

    expr_matrix (int columns): ptgen_object(), rows (), n_columns (columns) { };
    ~expr_matrix ();

    expr_vector &operator[] (int i) const { return *(rows[i]); };

    bool push_back (expr_vector *row) { 
      if (row->size() == n_columns)
        {
          rows.push_back (row);
          return true;
        }
      else
        return false;
    }

    int size (void) const { return rows.size(); }
    int row_size (void) const { return n_columns; }

    iterator begin() { return rows.begin(); }
    iterator end() { return rows.end(); }

    const_iterator begin() const { return rows.begin(); }
    const_iterator end() const { return rows.end(); }

    numeric_matrix *evaluate () const
      {
        closure c(num_variables());
        return evaluate (&c);
      }

    numeric_matrix *evaluate (closure *c) const;
  };

#endif
