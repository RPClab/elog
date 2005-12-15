# Simple makefile for elogd
#
# S. Ritt, May 12th 2000
# install/clean section by Th. Bullinger, Apr. 26th, 2002
#############################################################

#
# Directories for installation, modify if needed
#

ifndef PREFIX
PREFIX     = /usr/local
endif

ELOGDIR    = $(PREFIX)/elog
DESTDIR    = $(PREFIX)/bin
SDESTDIR   = $(PREFIX)/sbin
MANDIR     = $(PREFIX)/man
RCDIR      = /etc/rc.d/init.d

#############################################################

ifndef DEBUG
# Default compilation flags unless stated otherwise.
# Add "-DHAVE_CRYPT" and "-lcrypt" to use crypt() function.
CFLAGS += -O3 -funroll-loops -fomit-frame-pointer -W -Wall
else
# Build with e.g. 'make DEBUG=1' to turn on debugging.
CFLAGS += -g -O -W -Wall
endif

CC = gcc
IFLAGS = -kr -nut -i3 -l110
EXECS = elog elogd elconv
DESTDIR = /usr/local/bin
SDESTDIR = /usr/local/sbin
MANDIR = /usr/local/man
MXMLDIR = ../mxml
BINOWNER = bin
BINGROUP = bin

INSTALL = /usr/bin/install
RM = /bin/rm -f

OSTYPE = $(shell uname)

ifeq ($(OSTYPE),solaris)
CC = gcc
LIBS += -lsocket -lnsl
CFLAGS =
INSTALL = /usr/ucb/install
RM = /usr/bin/rm -f
endif

ifeq ($(OSTYPE),Darwin)
OSTYPE=darwin
endif

ifeq ($(OSTYPE),darwin)
CC = cc
BINOWNER = root
BINGROUP = admin
endif

all: $(EXECS)

regex.o: src/regex.c src/regex.h
	$(CC) $(CFLAGS) -c -o regex.o src/regex.c

mxml.o: $(MXMLDIR)/mxml.c $(MXMLDIR)/mxml.h
	$(CC) $(CFLAGS) -c -o mxml.o $(MXMLDIR)/mxml.c

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
	locext src\elogd.c resources\eloglang.brazilian
	locext src\elogd.c resources\eloglang.bulgarian 
	locext src\elogd.c resources\eloglang.dutch
	locext src\elogd.c resources\eloglang.french
	locext src\elogd.c resources\eloglang.german
	locext src\elogd.c resources\eloglang.spanish
	locext src\elogd.c resources\eloglang.italian
	locext src\elogd.c resources\eloglang.japanese
	locext src\elogd.c resources\eloglang.danish
	locext src\elogd.c resources\eloglang.zh_CN-GB2312
	locext src\elogd.c resources\eloglang.zh_CN-UTF8

install: $(EXECS)
	$(INSTALL) -m 0755 -d $(DESTDIR) $(SDESTDIR) $(MANDIR)/man1/ $(MANDIR)/man8/
	$(INSTALL) -v -m 0755 -o ${BINOWNER} -g ${BINGROUP} elog elconv $(DESTDIR)
	$(INSTALL) -v -m 0755 -o ${BINOWNER} -g ${BINGROUP} elogd $(SDESTDIR)
	$(INSTALL) -v -m 0644 man/elog.1 man/elconv.1 $(MANDIR)/man1/
	$(INSTALL) -v -m 0644 man/elogd.8 $(MANDIR)/man8/
	$(INSTALL) -v -m 0644 man/elogd.8 $(MANDIR)/man8/

	@echo "Installing scripts to $(ELOGDIR)/scripts/"
	@for file in `find scripts -type f | grep -v .svn` ; \
          do \
          install -D -m 644 $$file $(ELOGDIR)/scripts/`basename $$file` ; \
          done
	@echo "Installing resources to $(ELOGDIR)/resources/"
	@for file in `find resources -type f | grep -v .svn` ; \
          do \
          install -D -m 644 $$file $(ELOGDIR)/resources/`basename $$file` ; \
          done
	@echo "Installing themes to $(ELOGDIR)/themes/"
	@for file in `find themes/default -type f | grep -v .svn` ; \
          do \
          install -D -m 644 $$file $(ELOGDIR)/themes/default/`basename $$file` ; \
          done
	@for file in `find themes/default/icons -type f | grep -v .svn` ; \
          do \
          install -D -m 644 $$file $(ELOGDIR)/themes/default/icons/`basename $$file` ; \
          done

	@if [ ! -f $(ELOGDIR)/elogd.cfg ]; then  \
	  install -v -m 644 elogd.cfg $(ELOGDIR)/elogd.cfg ; \
	fi

	@sed "s#\@PREFIX\@#$(PREFIX)#g" elogd.init_template > elogd.init
	install -v -D -m 755 elogd.init $(RCDIR)/elogd

restart:
	$(RCDIR)/elogd restart
clean:
	-$(RM) *~ $(EXECS) regex.o mxml.o strlcpy.o

