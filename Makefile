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
CFLAGS = -march=i586
EXECS = elog elogd
DESTDIR = /usr/local/sbin

INSTALL=/usr/bin/install
RM=/bin/rm

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

elog: elog.c
	$(CC) $(CFLAGS) -o elog elog.c $(LIBS)

elogd: elogd.c
	$(CC) $(CFLAGS) -o elogd elogd.c $(LIBS)

install: $(EXECS)
	$(INSTALL) -m 0755 -o bin -g bin $(EXECS) $(DESTDIR)

clean:
	-$(RM) *~ $(EXECS)
