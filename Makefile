#
# Simple makefile for elogd
#
# S. Ritt, May 12th 2000
# install/clean section by Th. Bullinger, Apr. 26th, 2002
#

ifndef DEBUG
# Default compilation flags unless stated otherwise.
# Add "-DHAVE_CRYPT" and "-lcrypt" to use crypt() function.
CFLAGS += -O3 -funroll-loops -fomit-frame-pointer -W -Wall
else
# Build with e.g. 'make DEBUG=1' to turn on debugging.
CFLAGS += -g -O -W -Wall -DDEBUG=1
endif

CC = gcc
IFLAGS = -kr -nut -i3 -l110
EXECS = elog elogd elconv
DESTDIR = /usr/local/bin
SDESTDIR = /usr/local/sbin
MANDIR = /usr/local/man
MXMLDIR = ../mxml

INSTALL = /usr/bin/install
RM = /bin/rm

ifeq ($(OSTYPE),solaris)
CC = gcc
LIBS += -lsocket -lnsl
CFLAGS =
INSTALL = /usr/ucb/install
RM = /usr/bin/rm
endif

ifeq ($(OSTYPE),darwin)
CC = cc
endif

all: $(EXECS)

regex.o: src/regex.c src/regex.h
	$(CC) $(CFLAGS) -c -o regex.o src/regex.c

mxml.o: $(MXMLDIR)/mxml.c $(MXMLDIR)/mxml.h
	$(CC) $(CFLAGS) -DHAVE_STRLCPY -c -o mxml.o $(MXMLDIR)/mxml.c

strlcpy.o: $(MXMLDIR)/strlcpy.c $(MXMLDIR)/strlcpy.h
	$(CC) $(CFLAGS) -c -o strlcpy.o $(MXMLDIR)/strlcpy.c

elogd: src/elogd.c regex.o mxml.o strlcpy.o
	$(CC) $(CFLAGS) -I$(MXMLDIR) -o elogd src/elogd.c regex.o mxml.o strlcpy.o $(LIBS)

debug: src/elogd.c regex.o mxml.o strlcpy.o
	$(CC) -g -I$(MXMLDIR) -o elogd src/elogd.c regex.o mxml.o strlcpy.o $(LIBS)

%: src/%.c
	$(CC) $(CFLAGS) -o $@ $< $(LIBS)

indent:
	indent $(IFLAGS) src/elogd.c
	indent $(IFLAGS) src/elog.c
	indent $(IFLAGS) src/elconv.c
	indent $(IFLAGS) src/locext.c

loc:
	locext src\elogd.c eloglang.brazilian
	locext src\elogd.c eloglang.bulgarian
	locext src\elogd.c eloglang.dutch
	locext src\elogd.c eloglang.french
	locext src\elogd.c eloglang.german
	locext src\elogd.c eloglang.spanish
	locext src\elogd.c eloglang.italian
	locext src\elogd.c eloglang.japanese
	locext src\elogd.c eloglang.danish

install: $(EXECS)
	$(INSTALL) -m 0755 -d $(DESTDIR) $(SDESTDIR) $(MANDIR)/man1/ $(MANDIR)/man8/
	$(INSTALL) -m 0755 -o bin -g bin elog elconv $(DESTDIR)
	$(INSTALL) -m 0755 -o bin -g bin elogd $(SDESTDIR)
	$(INSTALL) -m 0644 man/elog.1 man/elconv.1 $(MANDIR)/man1/
	$(INSTALL) -m 0644 man/elogd.8 $(MANDIR)/man8/

restart:
	/etc/rc.d/init.d/elogd restart
clean:
	-$(RM) *~ $(EXECS) regex.o mxml.o strlcpy.o

