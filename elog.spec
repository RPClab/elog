# OpenSSH privilege separation requires a user & group ID

Name:       elog
Summary:    elog is a standalone electronic web logbook
Version:    2.5.5
Release:    4
Copyright:  GPL
Group:      Applications/Networking
Source:     http://midas.psi.ch/elog/download/elog-%{version}.tar.gz
Vendor:     Stefan Ritt <stefan.ritt@psi.ch>
URL:        http://midas.psi.ch/elog
BuildRoot:  /tmp/%{name}-root
Prefix:     /usr/local

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
%{_sbindir}/useradd -d %{prefix}/elog -s /bin/false \
   -g elog -M -r elog 2>/dev/null || :

%build
make
sed "s#\@PREFIX\@#%{prefix}#g" elogd.init_template > elogd.init

%install
mkdir -p $RPM_BUILD_ROOT%{prefix}/elog
mkdir -p $RPM_BUILD_ROOT%{prefix}/sbin
mkdir -p $RPM_BUILD_ROOT%{prefix}/bin
mkdir -p $RPM_BUILD_ROOT/etc/rc.d/init.d
install -m 0755 elogd $RPM_BUILD_ROOT%{prefix}/sbin
install -m 0755 elog  $RPM_BUILD_ROOT%{prefix}/bin
install -m 0755 elconv $RPM_BUILD_ROOT%{prefix}/bin

install -m 0644 eloghelp* $RPM_BUILD_ROOT%{prefix}/elog
install -m 0644 eloglang* $RPM_BUILD_ROOT%{prefix}/elog
cp -r themes $RPM_BUILD_ROOT%{prefix}/elog
cp -r logbooks $RPM_BUILD_ROOT%{prefix}/elog
install -m 0644 elogd.cfg $RPM_BUILD_ROOT%{prefix}/elog
install -m 0755 elogd.init $RPM_BUILD_ROOT/etc/rc.d/init.d/elogd

mkdir -p $RPM_BUILD_ROOT%{_mandir}/man1
mkdir -p $RPM_BUILD_ROOT%{_mandir}/man8
install -m 644 man/elog.1 $RPM_BUILD_ROOT%{_mandir}/man1
install -m 644 man/elconv.1 $RPM_BUILD_ROOT%{_mandir}/man1
install -m 644 man/elogd.8 $RPM_BUILD_ROOT%{_mandir}/man8

%post
chown -R elog:elog $RPM_BUILD_ROOT%{prefix}/elog

%clean
rm -rf $RPM_BUILD_ROOT

%files
%defattr(-,root,root)
%doc	README COPYING doc
%prefix/bin/*
%prefix/sbin/elogd
%prefix/elog/eloghelp*
%prefix/elog/eloglang*
%prefix/elog/themes
%prefix/elog/logbooks
%config(noreplace) %prefix/elog/elogd.cfg
/etc/rc.d/init.d/elogd
%{_mandir}/man1/*
%{_mandir}/man8/*
