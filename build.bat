@echo on
rem Usage: build_elog <version> like "build 234-5"
rem Build ELOG distribution

set version=%1

call makegit.bat

cl /O2 /Ob2 /Oi /Ot /I "\mxml" /I "\openssl\include" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_CRT_SECURE_NO_DEPRECATE" /D "_CRT_NONSTDC_NO_DEPRECATE" /D "_VC80_UPGRADE=0x0710" /D _USING_V110_SDK71_ /D "_MBCS" /D "HAVE_SSL" /GF /FD /EHsc /MT /Gy /Fo".\NT\Release/" /W3 /nologo /c /Zi /TC src\elogd.c
cl /O2 /Ob2 /Oi /Ot /I "\mxml" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_CRT_SECURE_NO_DEPRECATE" /D "_CRT_NONSTDC_NO_DEPRECATE" /D "_VC80_UPGRADE=0x0710" /D _USING_V110_SDK71_ /D "_MBCS" /GF /FD /EHsc /MT /Gy /Fo".\NT\Release/" /w /nologo /c /Zi /TC src\regex.c
cl /O2 /Ob2 /Oi /Ot /I "\mxml" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_CRT_SECURE_NO_DEPRECATE" /D "_CRT_NONSTDC_NO_DEPRECATE" /D "_VC80_UPGRADE=0x0710" /D _USING_V110_SDK71_ /D "_MBCS" /GF /FD /EHsc /MT /Gy /Fo".\NT\Release/" /w /nologo /c /Zi /TC src\crypt.c
cl /O2 /Ob2 /Oi /Ot /I "\mxml" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_CRT_SECURE_NO_DEPRECATE" /D "_CRT_NONSTDC_NO_DEPRECATE" /D "_VC80_UPGRADE=0x0710" /D _USING_V110_SDK71_ /D "_MBCS" /GF /FD /EHsc /MT /Gy /Fo".\NT\Release/" /w /nologo /c /Zi /TC src\auth.c
cl /O2 /Ob2 /Oi /Ot /I "\mxml" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_CRT_SECURE_NO_DEPRECATE" /D "_CRT_NONSTDC_NO_DEPRECATE" /D "_VC80_UPGRADE=0x0710" /D _USING_V110_SDK71_ /D "_MBCS" /GF /FD /EHsc /MT /Gy /Fo".\NT\Release/" /W3 /nologo /c /Zi /TC \mxml\mxml.c
cl /O2 /Ob2 /Oi /Ot /I "\mxml" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_CRT_SECURE_NO_DEPRECATE" /D "_CRT_NONSTDC_NO_DEPRECATE" /D "_VC80_UPGRADE=0x0710" /D _USING_V110_SDK71_ /D "_MBCS" /GF /FD /EHsc /MT /Gy /Fo".\NT\Release/" /W3 /nologo /c /Zi /TC \mxml\strlcpy.c

link "/OUT:.\NT\Release/elogd.exe" /INCREMENTAL:NO /DEBUG /SUBSYSTEM:CONSOLE /STACK:4000000 /MACHINE:X86 wsock32.lib advapi32.lib ".\NT\Release\elogd.obj" ".\NT\Release\mxml.obj" ".\NT\Release\regex.obj" ".\NT\Release\crypt.obj" ".\NT\Release\auth.obj" ".\NT\Release\strlcpy.obj" "\openssl\lib\vc\ssleay32MD.lib" "\openssl\lib\vc\libeay32MD.lib"

cl /O2 /Ob2 /Oi /Ot /I "\mxml" /I "\openssl\include" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_CRT_SECURE_NO_DEPRECATE" /D "_CRT_NONSTDC_NO_DEPRECATE" /D "_VC80_UPGRADE=0x0710" /D _USING_V110_SDK71_ /D "_MBCS" /D "HAVE_SSL" /GF /FD /EHsc /MT /Gy /Fo".\NT\Release/" /W3 /nologo /c /Zi /TC src\elog.c
link "/OUT:.\NT\Release/elog.exe" /INCREMENTAL:NO /DEBUG /SUBSYSTEM:CONSOLE /MACHINE:X86 wsock32.lib ".\NT\Release\elog.obj" ".\NT\Release\crypt.obj" ".\NT\Release\strlcpy.obj" "\openssl\lib\vc\ssleay32MD.lib" "\openssl\lib\vc\libeay32MD.lib"
cl /O2 /Ob2 /Oi /Ot /I "\mxml" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_CRT_SECURE_NO_DEPRECATE" /D "_CRT_NONSTDC_NO_DEPRECATE" /D "_VC80_UPGRADE=0x0710" /D _USING_V110_SDK71_ /D "_MBCS" /GF /FD /EHsc /MT /Gy /Fo".\NT\Release/" /W3 /nologo /c /Zi /TC src\elconv.c
link "/OUT:.\NT\Release/elconv.exe" /INCREMENTAL:NO /DEBUG /SUBSYSTEM:CONSOLE /MACHINE:X86 wsock32.lib ".\NT\Release\elconv.obj"

"\program files (x86)\NSIS\makensis" /DVERSION=%version% elog.nsi

\cygwin\bin\scp elog%version%.exe ritt@llc:html/elog/download/windows/
\cygwin\bin\scp elog%version%.exe ritt@llc:html/elog/download/windows/elog-latest.exe
\cygwin\bin\ssh ritt@llc chmod 666 html/elog/download/windows/elog%version%.exe
\cygwin\bin\ssh ritt@llc chmod 666 html/elog/download/windows/elog-latest.exe

