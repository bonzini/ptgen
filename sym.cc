// Procedural Texture Generator
// Paolo Bonzini
// esame di Elaborazione e Trasmissione delle Immagini
//
// Routine di gestione della symbol table

#include "ptgen.h"

typedef map <string, symtab_entry *> symtab;

// Classe symtab_stack

// Usata internamente per gestire l'utilizzo di piu'
// tabelle dei simboli (delle quali vengono usate sempre
// solo la piu' interna per le variabili locali e la piu'
// esterna per le variabili globali.
class symtab_stack : public vector <symtab *>
  {
  public:
    /* Push the global scope */
    symtab_stack () : vector <symtab *> () { push_scope (); };
    ~symtab_stack () { while (size()) pop_scope(); };
    int active_scopes() { return size() - 1; };
    symtab *global() { return front(); };
    symtab *local() { return back(); };
  };

symtab_stack symbols;
symtab_entry symtab_entry::null_entry (0,0,NULL);

// Ritorna il numero di variabili definite nello scope piu' interno
int num_variables ()
{
  return symbols.active_scopes() == 0
	   ? 0
	   : symbols.local()->size();
}

// Dichiara un identificatore globale con il nome KEY associato
// all'oggetto WHAT.  KIND e' il token che lo scanner restituira'
// quando trovera' l'identificatore nel programma.
bool declare_id (const string &key, int kind, ptgen_object *what)
{
  if (lookup_sym (key))
    return false;

  what->declared = true;

  symtab_entry *entry = new symtab_entry (kind, num_variables(), what);
  symtab::value_type key_val (key, entry);
  symbols.global()->insert (key_val);
  return true;
}

// Cerca un identificatore locale o globale con il nome KEY e
// ritorna l'oggetto associato.
symtab_entry &lookup_sym (const string &key)
{
  symtab *local = symbols.local();
  symtab::iterator result = local->find (key);
  if (result == local->end())
    {
      symtab *global = symbols.global();
      result = global->find (key);
      if (result == global->end())
        return symtab_entry::null_entry;
    }

  symtab::value_type &found = *result;
  return *(found.second);
}

// Definisce una variabile (identificatore locale) con il nome KEY
// e ritorna un numero progressivo ad essa associato.
int insert_var (const string &key)
{
  int id = num_variables();
  symtab_entry *entry = new symtab_entry (DEF_ID_, id, NULL);
  symtab::value_type key_val (key, entry);

  symbols.local()->insert (key_val);
  return id;
}

// Aggiunge uno scope che verra' usato per le variabili locali.
void push_scope ()
{
  symbols.push_back (new symtab());
}

// Elimina lo scope piu' interno attualmente in uso.
void pop_scope ()
{
  symtab *tab = symbols.back ();
  symbols.pop_back ();

  while (tab->size())
    {
      symtab::iterator it = tab->begin();
      symtab::value_type &key_val = *tab->begin();
      delete key_val.second;
      tab->erase (it);
    }

  delete tab;
}

