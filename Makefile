#
# Simple makefile for elogd
#
# S. Ritt, May 12th 2000
# install/clean section by Th. Bullinger, Apr. 26th, 2002
#
# add "-DHAVE_CRYPT" and "-lcrypt" to use crypt() function
#

CC = gcc
LIBS = 
CFLAGS = -O3 -funroll-loops -fomit-frame-pointer -W -Wall
DFLAGS = -g -O -W -Wall
IFLAGS = -kr -nut -i3 -l90
EXECS = elog elogd elconv
DESTDIR = /usr/local/bin
SDESTDIR = /usr/local/sbin
MANDIR = /usr/local/man

INSTALL = /usr/bin/install
RM = /bin/rm

ifeq ($(OSTYPE),solaris)
CC = gcc
LIBS = -lsocket -lnsl
CFLAGS =
INSTALL = /usr/ucb/install
RM = /usr/bin/rm
endif

ifeq ($(OSTYPE),darwin)
CC = cc
endif

all: $(EXECS)

debug: src/elogd.c
	$(CC) $(DFLAGS) -o elogd src/elogd.c $(LIBS)

%: src/%.c
	$(CC) $(CFLAGS) -o $@ $< $(LIBS)

indent:
	indent $(IFLAGS) src/elogd.c
	indent $(IFLAGS) src/elog.c
	indent $(IFLAGS) src/elconv.c
	indent $(IFLAGS) src/locext.c

loc:
	locext src\elogd.c eloglang.brazilian
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

clean:
	-$(RM) *~ $(EXECS)
