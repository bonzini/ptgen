// Procedural Texture Generator
// Paolo Bonzini
// esame di Elaborazione e Trasmissione delle Immagini
//
// Classe astratta ptgen_object

#ifndef PTGEN_OBJECT_H
#define PTGEN_OBJECT_H

class ptgen_object
  {
  public:
    int declared;
    ptgen_object () : declared (false) { };

    virtual ~ptgen_object()
      {
      };
  };

#endif
