// Procedural Texture Generator
// Paolo Bonzini
// esame di Elaborazione e Trasmissione delle Immagini
//
// Routine di gestione delle interpolazioni

#ifndef PTGEN_INTERP_H
#define PTGEN_INTERP_H

// Classe astratta interpolator.
//
// Rappresenta una funzione a un argomento definita tramite alcune coppie
// (x,y) che vengono imposte.  Tra i valori forniti l'oggetto compie una
// interpolazione con un algoritmo che dipende dalla classe concreta.

class interpolator: public ptgen_object
  {

  public:
    virtual void add_range (float x0, float x1, float y0, float y1) = 0;
    virtual float apply (float x) const = 0;
  };

// Classe spline_interpolator.
//
// Rappresenta una funzione a un argomento che interpola tramite spline
// tra le coppie (x,y) che vengono fornite.

class spline_interpolator: public interpolator
{
  typedef multimap<float, float> key_map;
  float last_x, last_y;
  key_map key_array;

  mutable bool deriv_ok;
  mutable int n;
  mutable float *x_val;
  mutable float *y_val;
  mutable float *y2_val;

  void compute_derivs () const;
  void add_key (float x, float y);
  void solve_tridiag(float *sub, float *diag, float *sup, float *b, int n) const;
  void linearize_tree () const;

  public:
    spline_interpolator () : last_x(0.0), last_y(0.0), key_array(),
			     deriv_ok(false), n(0), x_val (NULL), y_val(NULL),
			     y2_val (NULL)
      { };

    ~spline_interpolator ();

    void add_range (float x0, float x1, float y0, float y1)
    {
      if (!key_array.size())
        add_key (x0, y0);

      add_key (x1, y1);
    };

    float apply (float x) const;
};

// Classe spline_interpolator.
//
// Rappresenta una funzione a un argomento che interpola linearmente
// tra le coppie (x,y) che vengono fornite.

class linear_interpolator: public interpolator
  {
    class interpolator_range
      {
        float x0, x1, m, q;

      public:
        interpolator_range (float _x0, float _x1, float _y0, float _y1) :
          x0(_x0), x1(_x1), m((_y1-_y0)/(_x1-_x0)), q(_y0-m*_x0)
          { };

        bool in_range (float x) const { return x <= x1 && x >= x0; };
        float apply (float x) const { return m * x + q; };
      };

    typedef vector<interpolator_range> range_vec;

    range_vec ranges;
    mutable interpolator_range const *cache;

  public:
    linear_interpolator () : interpolator(), ranges(), cache(NULL) { };

    void add_range (float x0, float x1, float y0, float y1) {
      ranges.push_back (interpolator_range(x0, x1, y0, y1));
    }

    float apply (float x) const {
      if (cache && cache->in_range (x))
        return cache->apply (x);

      for (range_vec::const_iterator it = ranges.begin(); it < ranges.end(); it++)
	if ((*it).in_range (x))
	  {
	    cache = &(*it);
	    return cache->apply (x);
	  }

      cache = NULL;
      return x;
    }
  };

#endif
