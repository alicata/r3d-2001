// /////////////////////////////////////////////////
// appio.h
//
// author:			Aaron Licata
// creation date:	01/09/00
// last modified:	01/09/00
//
// Header file for application i/o handling

#ifndef APPIO_H
#define APPIO_H

// Output Modes
#define APPOUT_STDOUT     1
#define APPOUT_STDERR     2
#define APPOUT_LOGFILE    4
#define APPOUT_MAINWINDOW 8
#define APPOUT_AUXSCREEN  16

#define APPOUT_LOGFILE_NAME "logfile.txt"

// Macros
#define AppOutN(msg) AppOut(msg);AppEndl()

// Application and environment dependent I/O functions
void AppOut(char *message);
void AppOut(double value);
void AppOut(int value);
void AppEndl();
void AppOutLn(int length);
void AppOutMode(int mode);
void AppOutEnableCounter(bool enabled);
void AppGetKey();

#endif
