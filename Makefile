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

ifndef MANDIR
MANDIR     = $(ROOT)$(PREFIX)/man
endif

ELOGDIR    = $(ROOT)$(PREFIX)/elog
DESTDIR    = $(ROOT)$(PREFIX)/bin
SDESTDIR   = $(ROOT)$(PREFIX)/sbin
RCDIR      = $(ROOT)/etc/rc.d/init.d

#############################################################

# Default compilation flags unless stated otherwise.
# Add "-DHAVE_CRYPT" and "-lcrypt" to use crypt() function.
CFLAGS += -O3 -funroll-loops -fomit-frame-pointer -W -Wall

CC = gcc
IFLAGS = -kr -nut -i3 -l110
EXECS = elog elogd elconv
MXMLDIR = ../mxml
BINOWNER = bin
BINGROUP = bin

INSTALL = `which install`
RM = /bin/rm -f

OSTYPE = $(shell /bin/uname)

ifeq ($(OSTYPE),SunOS)
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

ifeq ($(OSTYPE),FreeBSD)
CC = gcc
BINOWNER = root
BINGROUP = wheel
endif

ifeq ($(OSTYPE),Linux)
CC = gcc
endif

CFLAGS += -DOS_$(OSTYPE)

all: $(EXECS)

regex.o: src/regex.c src/regex.h
	$(CC) $(CFLAGS) -w -c -o regex.o src/regex.c

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
	for src in src/*.c; do \
		indent $(IFLAGS) $$src; \
	done

ifeq ($(OSTYPE),CYGWIN_NT-5.1)
loc: locext.exe
	for lang in resources/eloglang*; do \
	  ./locext.exe src/elogd.c $$lang; echo locext src/elogd.c $$lang;\
	done
else
locext: src/locext.c
loc: locext
	@for lang in resources/eloglang*; do \
	  ./locext src/elogd.c $$lang; echo locext src/elogd.c $$lang;\
	done
endif

update: $(EXECS)
	@$(INSTALL) -v -m 0755 -o ${BINOWNER} -g ${BINGROUP} elogd $(SDESTDIR)

install: $(EXECS)
	@$(INSTALL) -m 0755 -d $(DESTDIR) $(SDESTDIR) $(MANDIR)/man1/ $(MANDIR)/man8/
	@$(INSTALL) -m 0755 -d $(ELOGDIR)/scripts/ $(ELOGDIR)/resources/ $(ELOGDIR)/themes/default/icons 
	@$(INSTALL) -m 0755 -d $(ELOGDIR)/logbooks/demo
	@$(INSTALL) -v -m 0755 -o ${BINOWNER} -g ${BINGROUP} elog elconv $(DESTDIR)
	@$(INSTALL) -v -m 0755 -o ${BINOWNER} -g ${BINGROUP} elogd $(SDESTDIR)
	@$(INSTALL) -v -m 0644 man/elog.1 man/elconv.1 $(MANDIR)/man1/
	@$(INSTALL) -v -m 0644 man/elogd.8 $(MANDIR)/man8/
	@$(INSTALL) -v -m 0644 man/elogd.8 $(MANDIR)/man8/
	@$(INSTALL) -v -m 0644 scripts/* $(ELOGDIR)/scripts/

	@echo "Installing resources to $(ELOGDIR)/resources"	
	@$(INSTALL) -m 0644 resources/* $(ELOGDIR)/resources/

	@echo "Installing themes to $(ELOGDIR)/themes"	
	@$(INSTALL) -m 0644 themes/default/icons/* $(ELOGDIR)/themes/default/icons/
	@for file in `find themes/default -type f | grep -v .svn` ; \
          do \
          $(INSTALL) -D -m 0644 $$file $(ELOGDIR)/themes/default/`basename $$file` ;\
          done

	@echo "Installing example logbook to $(ELOGDIR)/logbooks/demo"	
	@if [ ! -f $(ELOGDIR)/logbooks/demo ]; then  \
	  $(INSTALL) -v -m 0644 logbooks/demo/* $(ELOGDIR)/logbooks/demo ; \
	fi

	@sed "s#\@PREFIX\@#$(PREFIX)#g" elogd.init_template > elogd.init
	@$(INSTALL) -v -D -m 0755 elogd.init $(RCDIR)/elogd

	@if [ ! -f $(ELOGDIR)/elogd.cfg ]; then  \
	  $(INSTALL) -v -m 644 elogd.cfg $(ELOGDIR)/elogd.cfg ; \
	fi

restart:
	$(RCDIR)/elogd restart
clean:
	-$(RM) *~ $(EXECS) regex.o mxml.o strlcpy.o locext

