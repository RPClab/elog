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
CFLAGS = -g -O
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

%: src/%.c
	$(CC) $(CFLAGS) -o $@ $< $(LIBS)

indent:
	indent $(IFLAGS) src/elogd.c
	indent $(IFLAGS) src/elog.c
	indent $(IFLAGS) src/elconv.c


install: $(EXECS)
	$(INSTALL) -m 0755 -d $(DESTDIR) $(SDESTDIR) $(MANDIR)/man1/ $(MANDIR)/man8/
	$(INSTALL) -m 0755 -o bin -g bin elog elconv $(DESTDIR)
	$(INSTALL) -m 0755 -o bin -g bin elogd $(SDESTDIR)
	$(INSTALL) -m 0644 man/elog.1 man/elconv.1 $(MANDIR)/man1/
	$(INSTALL) -m 0644 man/elogd.8 $(MANDIR)/man8/

clean:
	-$(RM) *~ $(EXECS)
