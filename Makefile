#
# Simple makefile for elogd
#
# S. Ritt, May 12th 2000
# install/clean section by Th. Bullinger, Apr. 26th, 2002
#
# add "-DUSE_CRYPT" and "-lcrypt" to use crypt() function
#

CC = gcc
LIBS = 
CFLAGS = -g -O
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

%: %.c
	$(CC) $(CFLAGS) -o $@ $< $(LIBS)

install: $(EXECS)
	$(INSTALL) -m 0755 -o bin -g bin elog elconv $(DESTDIR)
	$(INSTALL) -m 0755 -o bin -g bin elogd $(SDESTDIR)
	$(INSTALL) -m 0644 man/elog.1 man/elconv.1 $(MANDIR)/man1/
	$(INSTALL) -m 0644 man/elogd.8 $(MANDIR)/man8/

clean:
	-$(RM) *~ $(EXECS)
