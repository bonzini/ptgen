// Procedural Texture Generator
// Paolo Bonzini
// esame di Elaborazione e Trasmissione delle Immagini
//
// Routine di scrittura di un immagine in formato PNG

#include "ptgen.h"
#include <getopt.h>
#include <ctime>
#include <cstdio>
#include "config.h"

#ifdef HAVE_LIBPNG
#include "png.h"
#include <ptgen.h>

// The png_jmpbuf() macro, used in error handling, became available in
// libpng version 1.0.6.  If you want to be able to run your code with older
// versions of libpng, you must define the macro yourself (but only if it
// is not already defined by libpng!).

#ifndef png_jmpbuf
#  define png_jmpbuf(png_ptr) ((png_ptr)->jmpbuf)
#endif

static void user_write_data(png_structp, png_bytep, unsigned int);
static void user_flush_data(png_structp);

void user_write_data(png_structp png_ptr, png_bytep data, unsigned int length)
{
  ostream *os = reinterpret_cast <ostream *> (png_get_io_ptr(png_ptr));
  os->write (reinterpret_cast <const char *> (data), length);
}

void user_flush_data(png_structp png_ptr)
{
}


// Scrive un file PNG utilizzando la libreria libpng.  Il codice
// e' preso dalla documentazione della libreria.

bool write_png (ostream & os, const char *img, int width, int height)
{
  png_structp png_ptr;
  png_infop info_ptr;

  // Create and initialize the png_struct with the desired error handler
  // functions.  If you want to use the default stderr and longjump method,
  // you can supply NULL for the last three parameters.  We also check that
  // the library version is compatible with the one used at compile time,
  // in case we are using dynamically linked libraries.
  //
  png_ptr = png_create_write_struct (PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

  if (png_ptr == NULL)
    return false;

  // Allocate/initialize the image information data.
  info_ptr = png_create_info_struct (png_ptr);
  if (info_ptr == NULL)
    {
      png_destroy_write_struct (&png_ptr, (png_infopp) NULL);
      return (false);
    }

  // Set error handling.
  if (setjmp (png_jmpbuf (png_ptr)))
    {
      // If we get here, we had a problem reading the file
      png_destroy_write_struct (&png_ptr, &info_ptr);
      return (false);
    }

  png_set_write_fn (png_ptr, static_cast <void *> (&os),
		    user_write_data, user_flush_data);

  // set the zlib compression level
  png_set_compression_level(png_ptr, Z_BEST_COMPRESSION);

  png_set_IHDR (png_ptr, info_ptr, width, height, 8, PNG_COLOR_TYPE_RGB,
		PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_BASE,
		PNG_FILTER_TYPE_BASE);

  png_text text_ptr[1];
  text_ptr[0].key = "Author";
  text_ptr[0].text = PACKAGE_STRING;
  text_ptr[0].compression = PNG_TEXT_COMPRESSION_NONE;
#ifdef PNG_iTXt_SUPPORTED
  text_ptr[0].lang = NULL;
#endif
  png_set_text (png_ptr, info_ptr, text_ptr, 1);

  // The easiest way to write the image (you may have a different memory
  // layout, however, so choose what fits your needs best).  You need to
  // use the first method if you aren't handling interlacing yourself.
  //
  png_bytep *row_pointers = new png_bytep[height];
  for (int k = 0; k < height; k++)
    row_pointers[k] = reinterpret_cast <png_byte *> (
			const_cast <char *> (img + k * width * 3));

  png_write_info (png_ptr, info_ptr);
  png_write_image (png_ptr, row_pointers);
  png_write_end (png_ptr, info_ptr);
  png_destroy_write_struct (&png_ptr, &info_ptr);

  return (true);
}

#else

// Niente libpng, ritorna errore.
bool write_png (ostream & os, const char *img, int width, int height)
{
  return (false);
}

#endif
