// Procedural Texture Generator
// Paolo Bonzini
// esame di Elaborazione e Trasmissione delle Immagini
//
// Routine di gestione della symbol table

#ifndef PTGEN_SYM_H
#define PTGEN_SYM_H

// Classe symtab_entry.
//
// Rappresenta una voce in una tabella dei simboli.

struct symtab_entry {
  int kind;
  int id;
  ptgen_object *obj;

  symtab_entry (int _kind, int _id, ptgen_object *_obj) : kind (_kind), id(_id), obj(_obj) { };
  ~symtab_entry () { delete obj; };

  bool operator== (symtab_entry &e) { return this == &e; }
  bool operator! () { return this == &null_entry; }
  operator bool () { return this != &null_entry; }

  static symtab_entry null_entry;
};

// Dichiara un identificatore globale con il nome KEY associato
// all'oggetto WHAT.  KIND e' il token che lo scanner restituira'
// quando trovera' l'identificatore nel programma.
bool declare_id (const string &x, int kind, ptgen_object *what);

// Cerca un identificatore locale o globale con il nome KEY e
// ritorna l'oggetto associato.
symtab_entry &lookup_sym (const string &x);

// Definisce una variabile (identificatore locale) con il nome KEY
// e ritorna un numero progressivo ad essa associato.
int insert_var (const string &x);

// Ritorna il numero di variabili definite nello scope piu' interno
int num_variables ();

// Aggiunge uno scope che verra' usato per le variabili locali.
void push_scope ();

// Elimina lo scope piu' interno attualmente in uso.
void pop_scope ();

#endif
