SUBDIRS = . tests doc
AUTOMAKE_OPTIONS = foreign

bin_PROGRAMS = ptgen
ptgen_SOURCES = scan.ll parse.yy \
		matrices.cc ptgen.cc interp.cc images.cc \
		sym.cc expr.cc pngwrite.cc
noinst_HEADERS = parse.h ptgen.h matrices.h interp.h rand.h \
		 images.h sym.h expr.h objects.h pngwrite.h
AM_LFLAGS = -Cfe
AM_YFLAGS = -dv
AM_CXXFLAGS = -Wall

parse.h: parse.cc
