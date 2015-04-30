===========================================
Recovery3D V1.1   (release date 07/05/01)
===========================================

Contents
---------
1 - Installation Instructions for Windows98/NT4.0
2 - Quick Start
3 - Known Bugs
4 - Trouble-shooting



1 - Installation Instructions for Windows98 from Floppy Disk
-----------------------------------------------------------
STEP 1. download R3d.zip from http://com399.tripod.com
STEP 2. unzip R3d.zip by double-clicking on its icon
STEP 3. run Recovery3d.exe


2 - Quick Start
-----------------------------------------------------------
STEP 1. run Recovery3d.exe
STEP 2. from File menu choose: Import/In-Memory Rabbit Data
STEP 3. from Reconstruction menu choose: Surface Reconstruction
STEP 4. wait for a few minutes for the surface to appear 

3 - Known Bugs
-----------------------------------------------------------
At the moment, there is a memory leak in Recovery3D. This is 
more evident when processing large data such as point clouds
of more than 1000 or 2000 points. I will fix this problem 
as soon as I have some time.  

4 - Trouble-shooting
-----------------------------------------------------------

You might get a linking error when starting Recovery3D. 
Make sure the following list of DLLs are present in you 
windows system directory (i.e. c:\windows\system for Windows98 
and c:\winnt\system32 for WindowsNT4.0). If you do not have these 
DLLs or if in doubt just download MFCDLL.ZIP from: 

http://com399.tripod.com\mfcdll.zip

OPENGL32.dll
GLU32.dll
glut32.dll

MSVCRTD.dll
MSVCIRTD.dll
MSVCP50D.dll
MFC42D.dll
MFCO42D.dll

Unzip the missing DLLs to the directory where Recovery3D.exe is or your 
system directory.

NOTE: opengl32.dll and glut.dll have to be downloaded separately
OpenGL DLLs are available at http://www.opengl.org.
The other DLLs are available via Microsoft web site http://www.microsoft.com

