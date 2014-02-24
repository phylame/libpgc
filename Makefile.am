AUTOMAKE_OPTIONS=foreign
SUBDIRS=src test
EXTRA_DIST=doc
#AM_CPPFLAGS=-I$(top_srcdir)/include

# for shared libries
LDFLAGS=-fPIC -shared
moduledir=$(prefix)/lib
module_PROGRAMS=libxgc.so
libxgc_so_SOURCES=xgc.c list.c array.c stack.c
