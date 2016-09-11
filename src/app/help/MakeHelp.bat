@echo off
REM -- First make map file from Microsoft Visual C++ generated resource.h
echo // MAKEHELP.BAT generated Help Map file.  Used by SMEV.HPJ. >"hlp\Smev.hm"
echo. >>"hlp\Smev.hm"
echo // Commands (ID_* and IDM_*) >>"hlp\Smev.hm"
makehm ID_,HID_,0x10000 IDM_,HIDM_,0x10000 resource.h >>"hlp\Smev.hm"
echo. >>"hlp\Smev.hm"
echo // Prompts (IDP_*) >>"hlp\Smev.hm"
makehm IDP_,HIDP_,0x30000 resource.h >>"hlp\Smev.hm"
echo. >>"hlp\Smev.hm"
echo // Resources (IDR_*) >>"hlp\Smev.hm"
makehm IDR_,HIDR_,0x20000 resource.h >>"hlp\Smev.hm"
echo. >>"hlp\Smev.hm"
echo // Dialogs (IDD_*) >>"hlp\Smev.hm"
makehm IDD_,HIDD_,0x20000 resource.h >>"hlp\Smev.hm"
echo. >>"hlp\Smev.hm"
echo // Frame Controls (IDW_*) >>"hlp\Smev.hm"
makehm IDW_,HIDW_,0x50000 resource.h >>"hlp\Smev.hm"
REM -- Make help for Project SMEV


echo Building Win32 Help files
start /wait hcw /C /E /M "hlp\Smev.hpj"
if errorlevel 1 goto :Error
if not exist "hlp\Smev.hlp" goto :Error
if not exist "hlp\Smev.cnt" goto :Error
echo.
if exist Debug\nul copy "hlp\Smev.hlp" Debug
if exist Debug\nul copy "hlp\Smev.cnt" Debug
if exist Release\nul copy "hlp\Smev.hlp" Release
if exist Release\nul copy "hlp\Smev.cnt" Release
echo.
goto :done

:Error
echo hlp\Smev.hpj(1) : error: Problem encountered creating help file

:done
echo.
