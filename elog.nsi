; elog.nsi
;
; This script will install the elog system
;

; The name of the installer
;--------------------------------
;Include Modern UI

!include "MUI.nsh"

;--------------------------------
;General

Name "ELOG"

; The file to write
OutFile "elog${VERSION}.exe"

; Overwrite setting
SetOverwrite on

; The default installation directory
InstallDir $PROGRAMFILES\ELOG
; Registry key to check for directory (so if you install again, it will 
; overwrite the old one automatically)
InstallDirRegKey HKLM SOFTWARE\ELOG "Install_Dir"

; The text to prompt the user to enter a directory
ComponentText "This will install the ELOG electronic logbook server on your computer. Select which optional things you want installed."
; The text to prompt the user to enter a directory
DirText "Choose a directory to install in to:"

;--------------------------------
;Pages

!insertmacro MUI_PAGE_WELCOME
!insertmacro MUI_PAGE_LICENSE "COPYING"
!insertmacro MUI_PAGE_COMPONENTS
!insertmacro MUI_PAGE_DIRECTORY
!insertmacro MUI_PAGE_INSTFILES

!insertmacro MUI_UNPAGE_CONFIRM
!insertmacro MUI_UNPAGE_INSTFILES

;--------------------------------
;Languages

!insertmacro MUI_LANGUAGE "English"

;--------------------------------
;Installer Sections

!define MUI_ABORTWARNING

;----------------------------------------------
; Main system
Section "ELOG system (required)" SecSystem

  ; root directory
  SetOutPath $INSTDIR

  File COPYING
  File README

  ; stop service to replace elogd.exe
  ExecWait 'net stop "ELOG server"'
  ExecWait 'net stop elogd'
  Sleep 2000

  File nt\release\elogd.exe
  File nt\release\elog.exe
  File nt\release\elconv.exe
  File \windows\system32\libeay32.dll
  File \windows\system32\ssleay32.dll
  File nt\msvcr90.dll
  File nt\msvcr100.dll
  File nt\msvcr110.dll

  ; doc directory
  SetOutPath $INSTDIR\doc
  File doc\*.*

  ; script directory
  SetOutPath $INSTDIR\scripts
  File /r scripts\*.*

  ; resources directory
  SetOutPath $INSTDIR\resources
  File resources\eloghelp_english.html

  ; ssl directory
  SetOutPath $INSTDIR\ssl
  File ssl\*.*

  ; src directory
  SetOutPath $INSTDIR\src
  File src\*.c
  File \mxml\mxml.c
  File \mxml\mxml.h
  File \mxml\strlcpy.c
  File \mxml\strlcpy.h

  ; config file
  SetOutPath $INSTDIR
  IfFileExists $INSTDIR\elogd.cfg 0 cfgNotExist
    MessageBox MB_YESNO|MB_ICONQUESTION "Would you like to overwrite your existing elogd.cfg?" IDNO cfgNotOverwrite
  cfgNotExist:
    File elogd.cfg ; overwrite file
  cfgNotOverwrite:

  ; themes 
  SetOutPath $INSTDIR\themes\default
  File themes\default\*.css
  File themes\default\*.png
  File themes\default\*.ico
  File themes\default\*.png
  SetOutPath $INSTDIR\themes\default\icons
  File themes\default\icons\*.*

  ; demo logbook
  IfFileExists $INSTDIR\logbooks\demo\2001\011108a.log 0 logbNotExist
    MessageBox MB_YESNO|MB_ICONQUESTION "Would you like to overwrite your existing demo logbook?" IDNO logbNotOverwrite
  logbNotExist:
    SetOutPath $INSTDIR\logbooks\demo\2001
    File logbooks\demo\2001\*
  logbNotOverwrite:
    
  SetOutPath $INSTDIR
  
  ; Write the installation path into the registry
  WriteRegStr HKLM SOFTWARE\ELOG "Install_Dir" "$INSTDIR"
  ; Write the uninstall keys for Windows
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\ELOG" "DisplayName" "ELOG electronic logbook (remove only)"
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\ELOG" "UninstallString" '"$INSTDIR\uninst_elog.exe"'
  
  WriteUninstaller "uninst_elog.exe"
  
SectionEnd

; optional section
Section "Multi-language support" SecLang
  SetOutPath $INSTDIR\resources
  File resources\*.*
SectionEnd

; optional section
Section "Start Menu Shortcuts" SecStart
  SetOutPath $INSTDIR
  CreateDirectory "$SMPROGRAMS\ELOG"
  CreateDirectory "$SMPROGRAMS\ELOG\ELOG Server"
  CreateShortCut "$SMPROGRAMS\ELOG\ELOG Server\Start ELOG server manually.lnk" "$INSTDIR\elogd.exe" "" "$INSTDIR\themes\default\favicon.ico"
  CreateShortCut "$SMPROGRAMS\ELOG\ELOG Server\Register ELOG server service.lnk" "$INSTDIR\elogd.exe" "-install" "$INSTDIR\themes\default\favicon.ico"
  CreateShortCut "$SMPROGRAMS\ELOG\ELOG Server\Unregister ELOG server service.lnk" "$INSTDIR\elogd.exe" "-remove" "$INSTDIR\themes\default\favicon.ico"
  Delete "$SMPROGRAMS\ELOG\Demo Logbook (requires running server).lnk"
  WriteINIStr "$SMPROGRAMS\ELOG\Demo Logbook (requires running server).url" \
              "InternetShortcut" "URL" "http://localhost:8080/demo/"
  CreateShortCut "$SMPROGRAMS\ELOG\ELOG Documentation.lnk" "$INSTDIR\doc\index.html"
  CreateShortCut "$SMPROGRAMS\ELOG\Uninstall ELOG.lnk" "$INSTDIR\uninst_elog.exe" "" "$INSTDIR\uninst_elog.exe" 0
SectionEnd

; optional section
Section "Register ELOG Server Service" SecService
;  WriteRegExpandStr HKLM SYSTEM\CurrentControlSet\Services\elogd ImagePath '"$INSTDIR\elogd.exe" -D -c "$INSTDIR\elogd.cfg"'
  ExecWait "$INSTDIR\elogd.exe -install"
SectionEnd

; display readme file

Function .onInstSuccess
  MessageBox MB_YESNO|MB_ICONQUESTION \
             "Setup has completed. View readme file now?" \
             IDNO NoReadme
    ExecShell open '$INSTDIR\doc\index.html'
  NoReadme:
FunctionEnd

; uninstall stuff

UninstallText "This will uninstall ELOG."

; special uninstall section.
Section "Uninstall"
  ; remove service
  ExecWait "$INSTDIR\elogd.exe -remove"

  ; remove registry keys
  DeleteRegKey HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\ELOG"
  DeleteRegKey HKLM SOFTWARE\ELOG

  ; remove files
  Delete $INSTDIR\COPYING
  Delete $INSTDIR\README
  Delete $INSTDIR\elog.exe
  Delete $INSTDIR\elogd.exe
  Delete $INSTDIR\elconv.exe
  Delete $INSTDIR\elogd.cfg

  Delete $INSTDIR\eloghelp_*.html
  Delete $INSTDIR\eloglang.*

  Delete $INSTDIR\doc\*
  RMDir $INSTDIR\doc

  Delete $INSTDIR\scripts\*
  RMDir $INSTDIR\scripts

  Delete $INSTDIR\resources\*
  RMDir $INSTDIR\resources

  Delete $INSTDIR\src\*
  RMDir $INSTDIR\src

  Delete $INSTDIR\themes\default\icons\*.*
  RMDir $INSTDIR\themes\default\icons
  Delete $INSTDIR\themes\default\*.*
  RMDir $INSTDIR\themes\default
  RMDir $INSTDIR\themes

  Delete $INSTDIR\logbooks\demo\*.*
  RMDir $INSTDIR\logbooks\demo
  RMDir $INSTDIR\logbooks
  
  ; MUST REMOVE UNINSTALLER, too
  Delete $INSTDIR\uninst_elog.exe

  ; remove shortcuts, if any.
  Delete "$SMPROGRAMS\ELOG\ELOG Server\*.*"
  RMDir "$SMPROGRAMS\ELOG\ELOG Server"
  Delete "$SMPROGRAMS\ELOG\*.*"
  RMDir "$SMPROGRAMS\ELOG"

  ; remove directories used.
  RMDir "$INSTDIR"

  ; if $INSTDIR was removed, skip these next ones
  IfFileExists $INSTDIR 0 Removed 
    MessageBox MB_YESNO|MB_ICONQUESTION \
      "Remove all files in your ELOG directory? (If you have anything\
 you created that you want to keep, click No)" IDNO Removed
    Delete $INSTDIR\*.* ; this would be skipped if the user hits no
    RMDir /r $INSTDIR
    IfFileExists $INSTDIR 0 Removed 
      MessageBox MB_OK|MB_ICONEXCLAMATION \
                 "Note: $INSTDIR could not be removed."
  Removed:

SectionEnd

;--------------------------------
;Descriptions

!insertmacro MUI_FUNCTION_DESCRIPTION_BEGIN
  !insertmacro MUI_DESCRIPTION_TEXT ${SecSystem} "Installs ELOG system, documentation, source code and an example logbook"
  !insertmacro MUI_DESCRIPTION_TEXT ${SecLang} "Installs support for different languages which can be switched during runtime"
  !insertmacro MUI_DESCRIPTION_TEXT ${SecStart} "Installs start menu shortcuts for ELOG"
  !insertmacro MUI_DESCRIPTION_TEXT ${SecService} "Installs ELOG server as a Windows Service, so that it gets started automatically when Windows boots"
!insertmacro MUI_FUNCTION_DESCRIPTION_END

; eof
