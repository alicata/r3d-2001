@echo off
echo ***************************************
echo 	    SAVE CURRENT LOGFILE
echo ***************************************

set date=190900
set version=0

REM CREATE DIRECTORY IF DOES NOT EXIST
if exist log goto COPYLOG0
mkdir log

REM MAKE COPY AS VERSION 0 IF NO OTHER COPY EXIST
:COPYLOG0
if exist==log\log%param%.txt goto COPYLOG1
set version=0
set param=%date%.%version%
copy logfile.txt log\log%param%.txt
goto END

REM MAKE DIFFERENT VERSION COPY NOT TO OVERRIVED THE PREV
:COPYLOG1
set version=1
set param=%date%.%version%
copy logfile.txt log\log%param%.txt
goto END

:END

echo ****************
echo  LOGFILE SAVED!
echo ****************