// Procedural Texture Generator
// Paolo Bonzini
// esame di Elaborazione e Trasmissione delle Immagini
//
// Driver

#include "ptgen.h"
#include <getopt.h>
#include <ctime>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <sstream>

using std::istringstream;
using std::exit;
using std::strcmp;

ostream *output_file = &cout;
enum image_file_format output_format = OUT_PPM;

// Routine per interpretare il parametro -S (--seed).
int
parse_seed (const char *c)
{
  istringstream iss(c);
  int seed;
  iss >> seed;

  return (bool) iss ? seed : -1;
}

// Routine per interpretare il parametro -s (--size).  Deve essere
// una potenza di due, l'AND qua sotto controlla questo.
int
parse_size (const char *c)
{
  istringstream iss(c);
  int size;
  iss >> size;

  return (size & (size - 1)) == 0 && (bool) iss ? size : -1;
}

// Stampa l'help.
void
usage(int exit_status)
{
  cerr << "Usage: ptgen [OPTIONS...] INPUT-FILE\n"
"\n"
" -o, --output-file=NAME   set output file name (- = stdout)\n"
" -f, --file-format=FORMAT set output file format (ppm, png)\n"
" -s, --size=SIZE          set output size (must be power of two)\n"
" -S, --seed=NUMBER        set random number seed\n\n";

  exit (exit_status);
}

int
main (int argc, char **argv)
{
  const char *output_filename = NULL;
  const char *default_output_filename = "ptgen.ppm";
  int size = 256;
  int seed = std::time(0);

  while (1)
    {
      static struct option long_options[] =
        {
          /* These options set a flag. */
          {"help",    no_argument, 	      0, 'h'},
          {"file-format", required_argument,  0, 'f'},
          {"output-file",  required_argument, 0, 'o'},
          {"size",    required_argument,      0, 's'},
          {"seed",    required_argument,      0, 'S'},
          {0, 0, 0, 0}
        };
      /* `getopt_long' stores the option index here. */
      int option_index = 0;
      int c;

      c = getopt_long (argc, argv, "f:o:s:S:y",
                       long_options, &option_index);

      /* Detect the end of the options. */
      if (c == -1)
        break;

      switch (c)
        {
	case 0:
	  break;

        case 'y':
	  { extern int yydebug; yydebug = 1; }
          break;

        case 'o':
          output_filename = optarg;
          break;

        case 'f':
          if (strcmp (optarg, "ppm") == 0)
	    {
	      output_format = OUT_PPM;
  	      default_output_filename = "ptgen.ppm";
	    }
#ifdef HAVE_LIBPNG
	  else if (strcmp (optarg, "png") == 0)
	    {
	      output_format = OUT_PNG;
  	      default_output_filename = "ptgen.png";
	    }
#endif
	  else
	    {
	      cerr << "Invalid file format" << endl;
	      usage (1);
	    }
          break;

        case 'S':
          if ((seed = parse_seed (optarg)) == -1)
	    {
	      cerr << "Wrong syntax for --seed option" << endl;
	      usage (1);
	    }

	  break;

        case 's':
          if ((size = parse_size (optarg)) == -1)
	    {
	      cerr << "Wrong syntax for --size option" << endl;
	      usage (1);
	    }

          break;

        case 'h':
	  usage (0);
	  break;

        case '?':
          /* `getopt_long' already printed an error message. */
	  usage (1);

        default:
          abort ();
        }
    }

  if (argc - optind == 1)
    {
      extern FILE *yyin;
      if (strcmp (argv[optind], "-"))
        {
	  yyin = fopen (argv[optind], "r");
	  if (!yyin)
	    {
	      cerr << "File not found." << endl;
	      exit (1);
	    }
	}
    }
  else
    usage (1);

  image::set_size (size, size);
  randf.set_seed (28111979L, seed);

  if (!output_filename)
    output_filename = default_output_filename;

  ofstream *ofs = NULL;
  bool use_cout = strcmp(output_filename, "-") == 0;
  if (!use_cout)
    output_file = ofs = new ofstream (output_filename, ofstream::binary);

  yyparse ();
  if (!use_cout)
    {
      ofs->close();
      delete ofs;
    }

  exit (errors ? 1 : 0);
}

