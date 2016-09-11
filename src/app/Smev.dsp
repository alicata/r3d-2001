# Microsoft Developer Studio Project File - Name="Smev" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 5.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=Smev - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Smev.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Smev.mak" CFG="Smev - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Smev - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Smev - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Smev - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o /win32 "NUL"
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o /win32 "NUL"
# ADD BASE RSC /l 0x809 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x809 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "Smev - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MDd /W3 /GX /Z7 /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /FR /YX"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o /win32 "NUL"
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o /win32 "NUL"
# ADD BASE RSC /l 0x809 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x809 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 opengl32.lib glu32.lib glaux.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# SUBTRACT LINK32 /incremental:no /nodefaultlib

!ENDIF 

# Begin Target

# Name "Smev - Win32 Release"
# Name "Smev - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\apperr.cpp
# End Source File
# Begin Source File

SOURCE=.\appio.cpp
# End Source File
# Begin Source File

SOURCE=.\ccenter.cpp
# End Source File
# Begin Source File

SOURCE=.\clock.cpp
# End Source File
# Begin Source File

SOURCE=.\crust.cpp
# End Source File
# Begin Source File

SOURCE=.\delaunay.cpp
# End Source File
# Begin Source File

SOURCE=.\DialogAlphaShape.cpp
# End Source File
# Begin Source File

SOURCE=.\DialogBarEx.cpp
# End Source File
# Begin Source File

SOURCE=.\DialogOptions.cpp
# End Source File
# Begin Source File

SOURCE=.\DialogRandomizer.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgIntro.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgLocation.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgReconProcess.cpp
# End Source File
# Begin Source File

SOURCE=.\filept2.cpp
# End Source File
# Begin Source File

SOURCE=.\geom.cpp
# End Source File
# Begin Source File

SOURCE=.\geomutil.cpp
# End Source File
# Begin Source File

SOURCE=.\geostat.cpp
# End Source File
# Begin Source File

SOURCE=.\LeftPane.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\math.cpp
# End Source File
# Begin Source File

SOURCE=.\predicates.c
# End Source File
# Begin Source File

SOURCE=.\rabdata.cpp
# End Source File
# Begin Source File

SOURCE=.\rendergl.cpp
# End Source File
# Begin Source File

SOURCE=.\skeleton.cpp
# End Source File
# Begin Source File

SOURCE=.\Smev.cpp
# End Source File
# Begin Source File

SOURCE=.\hlp\Smev.hpj
USERDEP__SMEV_="$(ProjDir)\hlp\AfxCore.rtf"	"$(ProjDir)\hlp\AfxPrint.rtf"	

!IF  "$(CFG)" == "Smev - Win32 Release"

# Begin Custom Build - Making help file...
OutDir=.\Release
ProjDir=.
TargetName=Smev
InputPath=.\hlp\Smev.hpj

"$(OutDir)\$(TargetName).hlp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	call "$(ProjDir)\makehelp.bat"

# End Custom Build

!ELSEIF  "$(CFG)" == "Smev - Win32 Debug"

# Begin Custom Build - Making help file...
OutDir=.\Debug
ProjDir=.
TargetName=Smev
InputPath=.\hlp\Smev.hpj

"$(OutDir)\$(TargetName).hlp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	call "$(ProjDir)\makehelp.bat"

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Smev.rc

!IF  "$(CFG)" == "Smev - Win32 Release"

!ELSEIF  "$(CFG)" == "Smev - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\SmevDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\SmevView.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\visdebug.cpp
# End Source File
# Begin Source File

SOURCE=.\visualize.cpp
# End Source File
# Begin Source File

SOURCE=.\wininfo.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\apperr.h
# End Source File
# Begin Source File

SOURCE=.\appio.h
# End Source File
# Begin Source File

SOURCE=.\ccenter.h
# End Source File
# Begin Source File

SOURCE=.\clock.h
# End Source File
# Begin Source File

SOURCE=.\config.h
# End Source File
# Begin Source File

SOURCE=.\crust.h
# End Source File
# Begin Source File

SOURCE=.\delaunay.h
# End Source File
# Begin Source File

SOURCE=.\DialogAlphaShape.h
# End Source File
# Begin Source File

SOURCE=.\DialogBarEx.h
# End Source File
# Begin Source File

SOURCE=.\DialogOptions.h
# End Source File
# Begin Source File

SOURCE=.\DialogRandomizer.h
# End Source File
# Begin Source File

SOURCE=.\DlgIntro.h
# End Source File
# Begin Source File

SOURCE=.\DlgLocation.h
# End Source File
# Begin Source File

SOURCE=.\DlgReconProcess.h
# End Source File
# Begin Source File

SOURCE=.\filept2.h
# End Source File
# Begin Source File

SOURCE=.\geom.h
# End Source File
# Begin Source File

SOURCE=.\geomutil.h
# End Source File
# Begin Source File

SOURCE=.\geostat.h
# End Source File
# Begin Source File

SOURCE=.\interface.h
# End Source File
# Begin Source File

SOURCE=.\LeftPane.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\math.h
# End Source File
# Begin Source File

SOURCE=.\predicates.h
# End Source File
# Begin Source File

SOURCE=.\rabdata.h
# End Source File
# Begin Source File

SOURCE=.\rendergl.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\Smev.h
# End Source File
# Begin Source File

SOURCE=.\SmevDoc.h
# End Source File
# Begin Source File

SOURCE=.\SmevView.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\STL.h
# End Source File
# Begin Source File

SOURCE=.\visdebug.h
# End Source File
# Begin Source File

SOURCE=.\visualize.h
# End Source File
# Begin Source File

SOURCE=.\wininfo.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\bmp00001.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00002.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00003.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmtreebi.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmtreedo.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmtreefi.bmp
# End Source File
# Begin Source File

SOURCE=.\res\recon3d.bmp
# End Source File
# Begin Source File

SOURCE=.\res\recov256.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Smev.ico
# End Source File
# Begin Source File

SOURCE=.\res\Smev.rc2
# End Source File
# Begin Source File

SOURCE=.\res\SmevDoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\toolbar1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\toolbar_.bmp
# End Source File
# End Group
# Begin Group "Help Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\hlp\AfxCore.rtf
# End Source File
# Begin Source File

SOURCE=.\hlp\AfxPrint.rtf
# End Source File
# Begin Source File

SOURCE=.\hlp\AppExit.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\Bullet.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\CurArw2.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\CurArw4.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\CurHelp.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\EditCopy.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\EditCut.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\EditPast.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\EditUndo.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\FileNew.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\FileOpen.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\FilePrnt.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\FileSave.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\HlpSBar.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\HlpTBar.bmp
# End Source File
# Begin Source File

SOURCE=.\MakeHelp.bat
# End Source File
# Begin Source File

SOURCE=.\hlp\RecFirst.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\RecLast.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\RecNext.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\RecPrev.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\Scmax.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\ScMenu.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\Scmin.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\Smev.cnt
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# Begin Source File

SOURCE=.\Smev.reg
# End Source File
# End Target
# End Project
