@echo on
rem Usage: build_elog <version> like "build 100"
rem Build ELOG distribution

set version=%1

cd nt
nmake -f elog.mak CFG="elog - Win32 Release"
nmake -f elogd.mak CFG="elogd - Win32 Release"
nmake -f elconv.mak CFG="elconv - Win32 Release"
cd ..

rem map network drive
net use m: /d > nul
net use m: \\pc2075\midas mi_das /user:midas

"\program files\NSIS\makensis" /DVERSION=%version% elog.nsi

copy elog%version%.exe m:\html\elog\download\windows\
