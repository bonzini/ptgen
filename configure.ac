# Process this file with autoconf to produce a configure script.
AC_INIT(ptgen, 1.0, bonzini@gnu.org)
AM_INIT_AUTOMAKE

AC_CONFIG_SRCDIR([parse.yy])
AC_CONFIG_HEADER([config.h])

AC_PROG_CC

# Look for libpng-config.  Get the flags from it.
AC_CHECK_PROGS(LIBPNG_CONFIG, libpng-config libpng12-config, no)
if test "$LIBPNG_CONFIG" != no; then
  save_LIBS="$LIBS"
  save_CFLAGS="$CFLAGS"
  save_CPPFLAGS="$CPPFLAGS"
  LIBS="$LIBS `$LIBPNG_CONFIG --ldflags | tr '\n' ' '`"
  CFLAGS="$CFLAGS `$LIBPNG_CONFIG --ccopts | tr '\n' ' '`"
  CPPFLAGS="$CPPFLAGS `$LIBPNG_CONFIG --cppflags --I_opts | tr '\n' ' '`"
fi

# Now look for the library archive and includes.  Also do so
# if libpng-config is not there, hoping that no special flags
# are necessary.
HAVE_LIBPNG=false
AC_CHECK_LIB(png, png_write_image,
  [AC_CHECK_HEADER(png.h,
    [AC_DEFINE(HAVE_LIBPNG, 1, [Define if libpng is available])
     HAVE_LIBPNG=:
     LIBS="$LIBS -lpng"])
])

# If the feature tests failed, reset the flags. :-(
if test $HAVE_LIBPNG != :; then
  LIBS="$save_LIBS"
  CFLAGS="$save_CFLAGS"
  CPPFLAGS="$save_CPPFLAGS"
fi

AM_CONDITIONAL(HAVE_LIBPNG, $HAVE_LIBPNG)

# Checks for programs.
AC_PROG_CXX
AM_PROG_LEX
AM_MISSING_PROG(YACC, bison)

AC_CONFIG_FILES(Makefile tests/Makefile doc/Makefile)
AC_OUTPUT
