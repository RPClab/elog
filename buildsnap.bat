@echo on
rem Usage: build_elog <version> like "build 100"
rem Build ELOG distribution

set version=%1

cd nt
nmake -f elogd.mak CFG="elogd - Win32 Release"
cd ..

rem map network drive
net use n: /d > nul
net use n: \\pc2075\midas mi_das /user:midas

copy nt\Release\elogd.exe n:\html\elog\download\windows\elogd-snapshot.exe

