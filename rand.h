// Procedural Texture Generator
// Paolo Bonzini
// esame di Elaborazione e Trasmissione delle Immagini
//
// Numeri casuali

#ifndef PTGEN_RAND_H
#define PTGEN_RAND_H

// Classe rng.
//
// Definisce un buon generatore di numeri casuali.

class rng {
  unsigned long s1;
  unsigned long s2;

public:
  rng (unsigned long seed1 = 28111979L, unsigned long seed2 = 17031980L) : s1(seed1), s2(seed2) { };

  void set_seed (unsigned long seed1, unsigned long seed2) 
    {
      s1 = seed1;
      s2 = seed2;
    };

  inline float operator() ()
    {
      s1 = 30903 * (s1 & 65535) + (s1>>16);
      s2 = 18000 * (s2 & 65535) + (s2>>16);
      return ((s1<<16)+s2) / 4294967295.0;
    };
};

extern rng randf; // declared in images.cc

#endif
