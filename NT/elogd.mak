# Microsoft Developer Studio Generated NMAKE File, Based on elogd.dsp
!IF "$(CFG)" == ""
CFG=elogd - Win32 Debug
!MESSAGE No configuration specified. Defaulting to elogd - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "elogd - Win32 Release" && "$(CFG)" != "elogd - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "elogd.mak" CFG="elogd - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "elogd - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "elogd - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "elogd - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\elogd.exe" "$(OUTDIR)\elogd.bsc"


CLEAN :
	-@erase "$(INTDIR)\elogd.obj"
	-@erase "$(INTDIR)\regex.obj"
	-@erase "$(INTDIR)\mxml.obj"
	-@erase "$(INTDIR)\elogd.sbr"
	-@erase "$(INTDIR)\regex.sbr"
	-@erase "$(INTDIR)\mxml.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\elogd.bsc"
	-@erase "$(OUTDIR)\elogd.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /ML /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\elogd.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\elogd.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\elogd.sbr" "$(INTDIR)\regex.sbr" "$(INTDIR)\mxml.sbr"

"$(OUTDIR)\elogd.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=wsock32.lib advapi32.lib /nologo /subsystem:console /stack:4000000 /incremental:no /pdb:"$(OUTDIR)\elogd.pdb" /machine:I386 /out:"$(OUTDIR)\elogd.exe" 
LINK32_OBJS= \
	"$(INTDIR)\elogd.obj" "$(INTDIR)\regex.obj" "$(INTDIR)\mxml.obj"
 
"$(OUTDIR)\elogd.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "elogd - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\elogd.exe" "$(OUTDIR)\elogd.bsc"


CLEAN :
	-@erase "$(INTDIR)\elogd.obj"
	-@erase "$(INTDIR)\elogd.sbr"
	-@erase "$(INTDIR)\regex.obj"
	-@erase "$(INTDIR)\regex.sbr"
	-@erase "$(INTDIR)\mxml.obj"
	-@erase "$(INTDIR)\mxml.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\elogd.bsc"
	-@erase "$(OUTDIR)\elogd.exe"
	-@erase "$(OUTDIR)\elogd.ilk"
	-@erase "$(OUTDIR)\elogd.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MLd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\elogd.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\elogd.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\elogd.sbr" "$(INTDIR)\regex.sbr" "$(INTDIR)\mxml.sbr" 

"$(OUTDIR)\elogd.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=wsock32.lib advapi32.lib /nologo /subsystem:console /stack:4000000 /incremental:yes /pdb:"$(OUTDIR)\elogd.pdb" /debug /machine:I386 /out:"$(OUTDIR)\elogd.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\elogd.obj" "$(INTDIR)\regex.obj" "$(INTDIR)\mxml.obj"

"$(OUTDIR)\elogd.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("elogd.dep")
!INCLUDE "elogd.dep"
!ELSE 
!MESSAGE Warning: cannot find "elogd.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "elogd - Win32 Release" || "$(CFG)" == "elogd - Win32 Debug"
SOURCE=..\src\elogd.c

"$(INTDIR)\elogd.obj"	"$(INTDIR)\elogd.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE=..\src\regex.c
"$(INTDIR)\regex.obj"	"$(INTDIR)\regex.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE=..\src\mxml.c
"$(INTDIR)\mxml.obj"	"$(INTDIR)\mxml.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) /D "STRLCPY_DEFINED" $(SOURCE)

!ENDIF 

