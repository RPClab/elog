; elog.nsi
;
; This script will install the elog system
;

; The name of the installer
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

; Pages
Page components
Page directory
Page instfiles

UninstPage uninstConfirm
UninstPage instfiles

;----------------------------------------------
; Main system
Section "ELOG system (required)"

  ; root directory
  SetOutPath $INSTDIR

  File COPYING
  File README

  File nt\release\elogd.exe
  File nt\release\elog.exe
  File nt\release\elconv.exe
  File eloghelp_en.html

  ; doc directory
  SetOutPath $INSTDIR\doc
  File doc\*.*

  ; src directory
  SetOutPath $INSTDIR\src
  File src\*.c

  ; config file
  SetOutPath $INSTDIR
  IfFileExists $INSTDIR\elogd.cfg 0 cfgNotExist
    MessageBox MB_YESNO|MB_ICONQUESTION "Would you like to overwrite your existing elogd.cfg?" IDNO cfgNotOverwrite
  cfgNotExist:
    File elogd.cfg ; overwrite file
  cfgNotOverwrite:

  ; themes 
  SetOutPath $INSTDIR\themes\default

  IfFileExists $INSTDIR\themes\default\default.css 0 themesNotExist
    MessageBox MB_YESNO|MB_ICONQUESTION "Would you like to overwrite your existing theme files?" IDNO themesNotOverwrite
  themesNotExist:
    File themes\default\*.css
    File themes\default\*.gif
    SetOutPath $INSTDIR\themes\default\icons
    File themes\default\icons\*.*
  themesNotOverwrite:

  ; demo logbook
  IfFileExists $INSTDIR\logbooks\demo\011108a.log 0 logbNotExist
    MessageBox MB_YESNO|MB_ICONQUESTION "Would you like to overwrite your existing demo logbook?" IDNO logbNotOverwrite
  logbNotExist:
    SetOutPath $INSTDIR\logbooks\demo
    File logbooks\demo\*
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
Section "Multi-language support"
  SetOutPath $INSTDIR
  File eloghelp_ge.html
  File eloghelp_fr.html
  File eloghelp_sp.html
  File eloghelp_du.html
  File eloghelp_br.html
  File eloghelp_ja.html
  File eloghelp_it.html
  File eloghelp_en.html
  File eloglang.german
  File eloglang.french
  File eloglang.spanish
  File eloglang.dutch
  File eloglang.brazilian
  File eloglang.japanese
  File eloglang.italian
  File eloglang.danish
SectionEnd

; optional section
Section "Start Menu Shortcuts"
  CreateDirectory "$SMPROGRAMS\ELOG"
  CreateShortCut "$SMPROGRAMS\ELOG\ELOG server.lnk" "$INSTDIR\elogd.exe" "" "$INSTDIR\elogd.exe" 0 
  Delete "$SMPROGRAMS\ELOG\Demo Logbook (start server first!).lnk"
  WriteINIStr "$SMPROGRAMS\ELOG\Demo Logbook (start server first!).url" \
              "InternetShortcut" "URL" "http://localhost:8080/demo/"
  CreateShortCut "$SMPROGRAMS\ELOG\ELOG Documentation.lnk" "$INSTDIR\doc\index.html"
  CreateShortCut "$SMPROGRAMS\ELOG\Uninstall ELOG.lnk" "$INSTDIR\uninst_elog.exe" "" "$INSTDIR\uninst_elog.exe" 0
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

  Delete $INSTDIR\eloghelp_en.html
  Delete $INSTDIR\eloghelp_fr.html
  Delete $INSTDIR\eloghelp_ge.html
  Delete $INSTDIR\eloghelp_sp.html
  Delete $INSTDIR\eloghelp_du.html
  Delete $INSTDIR\eloghelp_it.html
  Delete $INSTDIR\eloghelp_ja.html
  Delete $INSTDIR\eloghelp_br.html
  Delete $INSTDIR\eloglang.french
  Delete $INSTDIR\eloglang.german
  Delete $INSTDIR\eloglang.spanish
  Delete $INSTDIR\eloglang.dutch
  Delete $INSTDIR\eloglang.brazilian
  Delete $INSTDIR\eloglang.italian
  Delete $INSTDIR\eloglang.japanese
  Delete $INSTDIR\eloglang.danish

  Delete $INSTDIR\doc\*
  RMDir $INSTDIR\doc

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
  Delete "$SMPROGRAMS\ELOG\*.*"

  ; remove directories used.
  RMDir "$SMPROGRAMS\ELOG"
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

; eof
