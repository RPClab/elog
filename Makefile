#
# Simple makefile for elogd
#
# S. Ritt, May 12th 2000
#
# add "-DUSE_CRYPT" and "-lcrypt" to use crypt() function
#

CC = gcc
LIBS = 

ifeq ($(OSTYPE),solaris)
CC = gcc
LIBS = -lsocket -lnsl
endif

all: elogd elog

elog: elog.c
	$(CC) -o elog elog.c $(LIBS)

elogd: elogd.c
	$(CC) -o elogd elogd.c $(LIBS)

