# OpenSSH privilege separation requires a user & group ID

Name:       elog
Summary:    elog is a standalone electronic web logbook
Version:    3.1.3
Release:    1
License:    GPL
Group:      Applications/Networking
Source:     http://midas.psi.ch/elog/download/elog-%{version}.tar.gz
Vendor:     Stefan Ritt <stefan.ritt@psi.ch>
URL:        http://midas.psi.ch/elog
BuildRoot:  /tmp/%{name}-root
Prefix:     /usr/local
BuildRequires: openssl-devel >= 0.9.8e

%description
ELOG is part of a family of applications known as weblogs. 
Their general purpose is : 

1. To make it easy for people to put information online in a chronological
   fashion, in the form of short, time-stamped text messages ("entries") 
   with optional HTML markup for presentation, and optional file attachments 
   (images, archives, etc.) 

2. To make it easy for other people to access this information through a 
   Web interface, browse entries, search, download files, and optionally add, 
   update, delete or comment on entries. 

ELOG is a remarkable implementation of a weblog in at least two respects : 

- Its simplicity of use: you don't need to be a seasoned server operator 
and/or an experimented database administrator to run ELOG ; one executable 
file (under Unix or Windows), a simple configuration text file, and it works. 
No Web server or relational database required. It is also easy to translate 
the interface to the appropriate language for your users. 

- Its versatility: through its single configuration file, ELOG can be made 
to display an infinity of variants of the weblog concept. There are options 
for what to display, how to display it, what commands are available and to whom, 
access control, etc. Moreover, a single server can host several weblogs, and 
each weblog can be totally different from the rest. 

%changelog
* Fri Aug 29 2014 Stefan Ritt <stefan.ritt@psi.ch>
- Added BuildRequires, thanks to Stefan Roiser from CERN
* Fri Oct 24 2005 Stefan Ritt <stefan.ritt@psi.ch>
- Added resources/ directory
* Fri Mar 14 2003 Stefan Ritt <stefan.ritt@psi.ch>
- Added %post to change ownership of elog files
* Thu Jan 30 2003 Stefan Ritt <stefan.ritt@psi.ch>
- Added installation of man pages, thanks to Serge Droz <serge.droz@psi.ch>
* Tue Aug 13 2002 Stefan Ritt <stefan.ritt@psi.ch>
- Added elog group and user, thanks to Nicolas Chuche [nchuche@teaser.fr]
* Tue Jun 18 2002 Stefan Ritt <stefan.ritt@psi.ch>
- Put elogd.init into TAR file, add logbooks directory, put elogd in sbin/
* Tue Jun 18 2002 Serge Droz <serge.droz@psi.ch>
- Update to 2.0.0
* Mon Jun  3 2002 Serge Droz <serge.droz@psi.ch>
- Update to 1.3.6 
* Fri May 31 2002 Serge Droz <serge.droz@psi.ch>
- Initial RPM


%prep
%setup -q

%pre
%{_sbindir}/groupadd -r elog 2>/dev/null || :
%{_sbindir}/useradd -d / -s /bin/false \
   -g elog -M -r elog 2>/dev/null || :

%build
make
sed "s#\@PREFIX\@#%{prefix}#g" elogd.init_template > elogd.init

%install
make install ROOT=$RPM_BUILD_ROOT MANDIR=$RPM_BUILD_ROOT%{_mandir}

%post
chown -R elog:elog $RPM_BUILD_ROOT%{prefix}/elog

%clean
rm -rf $RPM_BUILD_ROOT

%files
%defattr(-,root,root)
/etc/rc.d/init.d/elogd
%{_mandir}/man1/*
%{_mandir}/man8/*
%doc	README COPYING doc
%defattr(-,elog,elog)
%prefix/bin/*
%prefix/sbin/elogd
%prefix/elog/resources
%prefix/elog/ssl
%prefix/elog/themes
%prefix/elog/scripts
%prefix/elog/logbooks
%config(noreplace) %prefix/elog/elogd.cfg
