// Procedural Texture Generator
// Paolo Bonzini
// esame di Elaborazione e Trasmissione delle Immagini
//
// Dichiarazioni e inclusioni

#ifndef PTGEN_PTGEN_H
#define PTGEN_PTGEN_H

#include "config.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <utility>
#include <string>
#include <cstdlib>

using std::string;
using std::pair;
using std::cout;
using std::cerr;
using std::ofstream;
using std::ostream;
using std::vector;
using std::endl;
using std::map;
using std::multimap;

enum image_file_format { OUT_PPM, OUT_PNG };

#include "rand.h"
#include "objects.h"
#include "sym.h"
#include "interp.h"
#include "expr.h"
#include "matrices.h"
#include "images.h"
#include "parse.h"
#include "pngwrite.h"

extern ostream *output_file;
extern image_file_format output_format;
extern int errors, yylineno;
extern int yylex ();
extern int yyparse ();

#endif
