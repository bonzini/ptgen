// Procedural Texture Generator
// Paolo Bonzini
// esame di Elaborazione e Trasmissione delle Immagini
//
// Routine di gestione delle interpolazioni

#include "ptgen.h"
#include <cfloat>

// Classe spline_interpolator.
//
// Applica un'interpolazione tramite spline tra le coppie (x,y) fornite
// all'oggetto.

spline_interpolator::~spline_interpolator ()
{
  if (x_val)
    delete[] x_val;

  if (y_val)
    delete[] y_val;

  if (y2_val)
    delete[] y2_val;
}

void
spline_interpolator::add_key (float x, float y)
{
  if (deriv_ok == true)
    return;

  pair<float, float> new_key (x, y);
  key_array.insert(new_key);
  last_x = x;
  last_y = y;
}

float
spline_interpolator::apply (float x) const
{
  if (!deriv_ok)
    {
      if (!x_val)
        linearize_tree();

      // Ci sono chiavi?  Se no assume y=x.
      if (!key_array.size())
        return x;

      // Una sola chiave?  Se no assume y=costante.
      if (key_array.size() == 1)
        return y_val[0];

      // Questo e' il punto di non ritorno?
      compute_derivs ();
      deriv_ok = true;
    }

  // Prima della prima chiave ritorna la y corrispondente.
  if (x <= x_val[0])
    return y_val[0];

  // Dopo l'ultima chiave ritorna la y corrispondente.
  if (x >= x_val[n - 1])
    return y_val[n - 1];

  // Trova l'intervallo corretto tramite ricerca binaria.
  int klo = 0;
  int khi = n - 1;
  while (khi - klo > 1)
    {
      int k = (khi + klo) >> 1;
      if (x_val[k] > x)
	khi = k;
      else
	klo = k;
    }

  // Interpola tra i due valori piu' vicini.
  float h = x_val[khi] - x_val[klo];
  float a = x_val[khi] - x;
  float b = x - x_val[klo];
  float y = ((-y2_val[klo] / 6 * (b+h) * a + y_val[khi]) * b +
             (-y2_val[khi] / 6 * (a+h) * b + y_val[klo]) * a) / h;

  return y;
}

void
spline_interpolator::solve_tridiag(float *sub, float *diag, float *sup, float *y2, int n) const
{
  /* Risolve un sistema lineare n x n con una matrice tridiagonale,
     cioe'   a(i,i-1) = sub[i]  per 2<=i<=n
             a(i,i)   = diag[i] per 1<=i<=n
             a(i,i+1) = sup[i]  per 1<=i<=n-1

     (the values sub[1], sup[n] are ignored)
     Usa l'algoritmo di Gauss senza pivoting.
     I termini noti in y2 sono sovrascritti con la soluzione.
     NOTA: tutti gli array usano 1...n, 0 e' inutilizzato! */

  for(int i = 2; i < n; i++)
    {
      sub[i] = sub[i] / diag[i-1];
      diag[i] = diag[i] - sub[i] * sup[i-1];
      y2[i] = y2[i] - sub[i] * y2[i-1];
    }

  y2[n] = y2[n] / diag[n];
  for(int i = n - 2; i > 0; i--)
    y2[i] = (y2[i] - sup[i] * y2[i+1]) / diag[i];
}

void
spline_interpolator::linearize_tree () const
{
  x_val = new float[key_array.size()];
  y_val = new float[key_array.size()];

  // Copia da key_map (ordinato secondo le x) in due array
  for (key_map::const_iterator it = key_array.begin(); it != key_array.end();
       n++, it++)
    {
      x_val[n] = (*it).first;
      y_val[n] = (*it).second;
    }
}

// Calcola le seconde derivate della cubica per ciascuna delle chiavi
// (nodi) della spline.
void
spline_interpolator::compute_derivs () const
{
  int np = key_array.size();

  y2_val = new float[np];
  for (int i = 1; i < np; i++)
    y2_val[i] = 0.0;

  if (np>2)
    {
      float *sub = new float[np-1];
      float *diag = new float[np-1];
      float *sup = new float[np-1];

      for (int i = 1; i < np - 1; i++)
        {
	  float dx1 = x_val[i+1] - x_val[i];
	  float dy1 = y_val[i+1] - y_val[i];
          float dx = x_val[i] - x_val[i-1];
          float dy = y_val[i] - y_val[i-1];

          sup[i] = dx1 / 6;
          sub[i] = dx / 6;
          diag[i] = (dx1 + dx) / 3;
          y2_val[i] = dy1 / dx1 - dy / dx;
        }

      solve_tridiag(sub, diag, sup, y2_val, np - 1);
      y2_val[np - 1] = 0.0;
      delete[] diag;
      delete[] sup;
      delete[] sub;
    }

}
