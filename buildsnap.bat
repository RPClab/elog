@echo on
cd nt
nmake -f elogd.mak CFG="elogd - Win32 Release"
cd ..

scp nt\Release\elogd.exe midas@midas:html/elog/download/windows/elogd-snapshot.exe

