// Procedural Texture Generator
// Paolo Bonzini
// esame di Elaborazione e Trasmissione delle Immagini
//
// Routine di scrittura di un immagine in formato PNG

#ifndef PTGEN_PNGWRITE_H
#define PTGEN_PNGWRITE_H

// Scrive un file PNG utilizzando la libreria libpng.  Se questa non
// e' disponibile, o se c'e' un errore, ritorna false.

bool write_png (ostream & os, const char *img, int width, int height);

#endif
