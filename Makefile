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
SRVDIR     = $(ROOT)/usr/lib/systemd/system

# flag for SSL support
USE_SSL    = 1

# flag for Kerberos support, please turn on if you need Kerberos
USE_KRB5   = 0

# flag for LDAP support, please turn on if you need LDAP
USE_LDAP   = 0

# flag for PAM support, please turn on if you need PAM
USE_PAM    = 0

#############################################################

# Default compilation flags unless stated otherwise.
CFLAGS += -O3 -funroll-loops -fomit-frame-pointer -W -Wall -Wno-deprecated-declarations -Imxml

CC = gcc
IFLAGS = -kr -nut -i3 -l110
EXECS = elog elogd elconv
OBJS = mxml.o crypt.o regex.o
GIT_REVISION = src/git-revision.h
BINOWNER = bin
BINGROUP = bin

# Option to use our own implementation of strlcat, strlcpy
NEED_STRLCPY = 1

INSTALL = `which install`
RM = /bin/rm -f

OSTYPE = $(shell uname)

ifeq ($(OSTYPE),SunOS)
CC = gcc
LIBS += -lsocket -lnsl
CFLAGS =
INSTALL = /usr/ucb/install
RM = /usr/bin/rm -f
endif

ifeq ($(OSTYPE),OpenBSD)
LIBS += -lcrypto
endif

ifeq ($(OSTYPE),Darwin)
OSTYPE=darwin
endif

ifeq ($(OSTYPE),darwin)
CC = cc
BINOWNER = root
BINGROUP = admin
NEED_STRLCPY =
CFLAGS += -I/opt/local/include
endif

ifeq ($(OSTYPE),FreeBSD)
CC = gcc
BINOWNER = root
BINGROUP = wheel
endif

ifeq ($(OSTYPE),Linux)
CC = gcc
endif

ifdef USE_SSL
ifneq ($(USE_SSL),0)
CFLAGS += -DHAVE_SSL
LIBS += -lssl
endif
endif

ifdef USE_KRB5
ifneq ($(USE_KRB5),0)
CFLAGS += -DHAVE_KRB5
LIBS += -lkrb5
endif
endif

ifdef USE_LDAP
ifneq ($(USE_LDAP),0)
CFLAGS += -DHAVE_LDAP
LIBS += -lldap
endif
endif

ifdef USE_PAM
ifneq ($(USE_PAM),0)
CFLAGS += -DHAVE_PAM
LIBS += -lpam
endif
endif

ifdef NEED_STRLCPY
OBJS += strlcpy.o
endif

WHOAMI = $(shell whoami)
ifeq ($(WHOAMI),root)
BINFLAGS = -o ${BINOWNER} -g ${BINGROUP}
endif

all: $(EXECS)

# put current GIT revision into header file to be included by programs
$(GIT_REVISION): src/elogd.c src/elog.c
	type git &> /dev/null; if [ $$? -eq 1 ]; then REV="unknown" ;else REV=`git log -n 1 --pretty=format:"%ad - %h"`; fi; echo \#define GIT_REVISION \"$$REV\" > $(GIT_REVISION)

regex.o: src/regex.c src/regex.h
	$(CC) $(CFLAGS) -w -c -o regex.o src/regex.c

crypt.o: src/crypt.c
	$(CC) $(CFLAGS) -w -c -o crypt.o src/crypt.c

auth.o: src/auth.c
	$(CC) $(CFLAGS) -w -c -o auth.o src/auth.c

mxml.o: mxml/mxml.c mxml/mxml.h
	$(CC) $(CFLAGS) -c -o mxml.o mxml/mxml.c

strlcpy.o: mxml/strlcpy.c mxml/strlcpy.h
	$(CC) $(CFLAGS) -c -o strlcpy.o mxml/strlcpy.c

elogd: src/elogd.c auth.o $(OBJS) $(GIT_REVISION)
	$(CC) $(CFLAGS) -o elogd src/elogd.c auth.o $(OBJS) $(LIBS)

elog: src/elog.c $(OBJS) $(GIT_REVISION)
	$(CC) $(CFLAGS) -o elog src/elog.c $(OBJS) $(LIBS)

debug: src/elogd.c auth.o $(OBJS)
	$(CC) -g $(CFLAGS) -O0 -o elogd src/elogd.c auth.o $(OBJS) $(LIBS)

%: src/%.c
	$(CC) $(CFLAGS) -o $@ $< $(LIBS)

indent:
	for src in src/*.c; do \
		d2u $$src; \
		indent $(IFLAGS) $$src; \
		u2d $$src; \
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
	@$(INSTALL) -v -m 0755 ${BINFLAGS} elogd $(SDESTDIR)

install: $(EXECS)
	@$(INSTALL) -m 0755 -d $(DESTDIR) $(SDESTDIR) $(MANDIR)/man1/ $(MANDIR)/man8/
	@$(INSTALL) -m 0755 -d $(ELOGDIR)/scripts/ $(ELOGDIR)/resources/ $(ELOGDIR)/ssl/ $(ELOGDIR)/themes/default/icons
	@$(INSTALL) -m 0755 -d $(ELOGDIR)/logbooks/demo
	@$(INSTALL) -m 0755 -d $(ELOGDIR)/logbooks/demo/2001
	@$(INSTALL) -v -m 0755 ${BINFLAGS} elog elconv $(DESTDIR)
	@$(INSTALL) -v -m 0755 ${BINFLAGS} elogd $(SDESTDIR)
	@$(INSTALL) -v -m 0644 man/elog.1 man/elconv.1 $(MANDIR)/man1/
	@$(INSTALL) -v -m 0644 man/elogd.8 $(MANDIR)/man8/
	@$(INSTALL) -v -m 0644 scripts/*.js $(ELOGDIR)/scripts/

	@echo "Installing CKeditor to $(ELOGDIR)/scripts/ckeditor"
	@cp -r scripts/* $(ELOGDIR)/scripts

	@echo "Installing resources to $(ELOGDIR)/resources"
	@$(INSTALL) -m 0644 resources/* $(ELOGDIR)/resources/
	@if [ ! -f $(ELOGDIR)/ssl/server.crt ]; then  \
	  $(INSTALL) -v -m 0644 ssl/server.crt $(ELOGDIR)/ssl/ ;\
	fi
	@if [ ! -f $(ELOGDIR)/ssl/server.key ]; then  \
	  $(INSTALL) -v -m 0644 ssl/server.key $(ELOGDIR)/ssl/ ;\
	fi

	@echo "Installing themes to $(ELOGDIR)/themes"
	@cp -r themes/* $(ELOGDIR)/themes

	@echo "Installing example logbook to $(ELOGDIR)/logbooks/demo"
	@if [ ! -f $(ELOGDIR)/logbooks/demo/2001 ]; then  \
	  $(INSTALL) -v -m 0644 logbooks/demo/2001/* $(ELOGDIR)/logbooks/demo/2001 ; \
	fi

	@if [ ! -f $(ELOGDIR)/elogd.cfg ]; then  \
	  $(INSTALL) -v -m 644 elogd.cfg $(ELOGDIR)/elogd.cfg ; \
	fi


ifneq ($(OSTYPE),darwin)
	@sed "s#\@PREFIX\@#$(PREFIX)#g" elogd.init_template > elogd.init
	@if [ ! -f $(RCDIR)/elogd ]; then  \
	  $(INSTALL) -v -m 0755 -D elogd.init $(RCDIR)/elogd ; \
	fi
endif

ifneq ("$(wildcard $(SRVDIR))", "")
	@$(INSTALL) -v -m 0644 -D elogd.service $(SRVDIR)
	@echo The elogd service can now be started with 
	@echo "  sudo systemctl start elogd"
endif

ifeq ($(OSTYPE),darwin)
	@$(INSTALL) -v -m 0644 elogd.plist /Library/LaunchDaemons/ch.psi.elogd.plist
	@echo The elogd service can now be started with 
	@echo "  sudo launchctl load /Library/LaunchDaemons/ch.psi.elogd.plist"
endif

restart:
	$(RCDIR)/elogd restart
clean:
	-$(RM) *~ $(EXECS) regex.o crypt.o auth.o mxml.o strlcpy.o locext
