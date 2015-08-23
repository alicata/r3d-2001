// ////////////////////////////////////////////////////////
// appio.cpp
//
// author:		Aaron Licata
//
// creation date:	01/09/00
// last modified:	01/09/00
//
// purpose: implementaion file for application i/o handling
//
// /////////////////////////////////////////////////////////

#include <iostream.h>
#include <fstream.h>

// OS dependent includes
#ifdef WIN32
	#include <conio.h>
#elif WIN32

#elif LINUX

#elif MSDOS

#endif

#include "clock.h"
#include "appio.h"



// ////////// global variables //////////////////
bool fileLogIsEnabled = false;
bool globalCounterIsEnabled = false;
bool timeStampIsEnabled = true;
long globalCounter = 0;				// unique ouput line id
int appOutMode = APPOUT_STDOUT;			// mode of operation
ofstream appLogFile;				// output log file 



// ///////////////////////////////////////////////////////////
// function: AppOutEnableFileLog()
//
// creation date:	01/09/00
// last modified:	03/10/00
// purpose: start logging activity
//
// arguments: none
//
// return value: none
// ///////////////////////////////////////////////////////////

void AppOutEnableFileLog()
{
	appLogFile.open(APPOUT_LOGFILE_NAME);
	fileLogIsEnabled = true;
}



// ///////////////////////////////////////////////////////////
// function: AppOutDisableFileLog()
//
// creation date:	01/09/00
// last modified:	01/10/00
// purpose: stop logging activity
//
// arguments: none
//
// return value: none
// ///////////////////////////////////////////////////////////

void AppOutDisableFileLog()
{
	appLogFile.close();
	fileLogIsEnabled = false;
}



// ///////////////////////////////////////////////////////////
// function: AppOutMode()
//
// creation date:	03/09/00
// last modified:	09/10/00
// purpose: change mode of outputting information
//
// arguments: chosen mode 
//
// return value: none
// ///////////////////////////////////////////////////////////

void AppOutMode(int mode) 
{

	if (mode == APPOUT_LOGFILE)
	{
		AppOutEnableFileLog();
	}
	else if (appOutMode == APPOUT_LOGFILE)
	{
		AppOutDisableFileLog();
	}
	appOutMode = mode;
}



// ///////////////////////////////////////////////////////////
// function: AppOut()
//
// creation date:	01/09/00
// last modified:	11/10/00
// purpose: ouput a string message 
//
// arguments: message to ouput 
//
// return value: none
// ///////////////////////////////////////////////////////////
void AppOut(char *message)
{
	if (globalCounterIsEnabled)
	{
		globalCounter++;
	}

	switch (appOutMode)
	{
	case APPOUT_STDOUT:
			if (globalCounterIsEnabled) cout << globalCounter << ":";
			cout << message;
			break;
	case APPOUT_STDERR:
			if (globalCounterIsEnabled) cerr << globalCounter << ":";
			cerr << message;
			break;
	case APPOUT_LOGFILE:
			if (globalCounterIsEnabled) appLogFile << globalCounter << ":";
			if (fileLogIsEnabled)
			{	
				appLogFile << message;
			}
			break;
	}
}



// ///////////////////////////////////////////////////////////
// function: AppOut()
//
// creation date:	01/09/00
// last modified:	11/10/00
// purpose: ouput a double value
//
// arguments: value to ouput 
//
// return value: none
// ///////////////////////////////////////////////////////////

void AppOut(double value)
{
	if (globalCounterIsEnabled)
	{
		globalCounter++;
	}

	switch (appOutMode)
	{
	case APPOUT_STDOUT:
			cout << value;
			break;
	case APPOUT_STDERR:
			cerr << value;
			break;
	case APPOUT_LOGFILE:
			if (fileLogIsEnabled)
			{	
				appLogFile << value;
			}
			break;
	}
}




// ///////////////////////////////////////////////////////////
// function: AppOut()
//
// creation date:	01/09/00
// last modified:	11/10/00
// purpose: ouput a integer value
//
// arguments: value to ouput 
//
// return value: none
// ///////////////////////////////////////////////////////////

void AppOut(int value)
{
	if (globalCounterIsEnabled)
	{
		globalCounter++;
	}

	switch (appOutMode)
	{
	case APPOUT_STDOUT:
			cout << value;
			break;
	case APPOUT_STDERR:
			cerr << value;
			break;
	case APPOUT_LOGFILE:
			if (fileLogIsEnabled)
			{	
				appLogFile << value;
			}
			break;
	}
}




// ///////////////////////////////////////////////////////////
// function: AppEndl()
//
// creation date:	01/09/00
// last modified:	11/10/00
// purpose: ouput a new line
//
// arguments: none
//
// return value: none
// ///////////////////////////////////////////////////////////

void AppEndl() 
{
	switch (appOutMode)
	{
	case APPOUT_STDOUT:
			cout << endl;
			break;
	case APPOUT_STDERR:
			cerr << endl;
			break;
	case APPOUT_LOGFILE:
			if (fileLogIsEnabled)
			{	
				appLogFile << endl;
			}
			break;
	}
}


// ///////////////////////////////////////////////////////////
// function: AppOutLn()
//
// creation date:	01/09/00
// last modified:	11/10/00
// purpose: ouput a line of '-' characters
//
// arguments: length of line
//
// return value: none
// ///////////////////////////////////////////////////////////

void AppOutLn(int length)
{
	int i;
	char timeStamp[80];

	GetTimeStamp(timeStamp);
	switch (appOutMode)
	{
	case APPOUT_STDOUT:
			for (i=0; i<length/2;i++)
			{
				cout << "-";
			}
			if (timeStampIsEnabled) cout << timeStamp;
			for (i=0; i<length/2;i++)
			{
				cout << "-";
			}
			cout << endl;
			break;
	case APPOUT_STDERR:
			for (i=0; i<length/2;i++)
			{
				cerr << "-";
			}
			if (timeStampIsEnabled) cerr << timeStamp;
			for (i=0; i<length/2;i++)
			{
				cerr << "-";
			}
			cerr << endl;
			break;
	case APPOUT_LOGFILE:
			if (fileLogIsEnabled)
			{	
				for (i=0; i<length/2;i++)
				{
					appLogFile << "-";
				}
				if (timeStampIsEnabled) appLogFile << timeStamp;
				for (i=0; i<length/2;i++)
				{
					appLogFile << "-";
				}
				appLogFile << endl;
			}
			break;
	}

}



// ///////////////////////////////////////////////////////////
// function: AppOutEnableCounter()
//
// creation date:	01/09/00
// last modified:	05/09/00
// purpose: enable the ouput line counter
//
// arguments: state of the counter
//
// return value: none
// ///////////////////////////////////////////////////////////

void AppOutEnableCounter(bool enabled) 
{ 
	globalCounter = 0;
	globalCounterIsEnabled = enabled; 
}



// ///////////////////////////////////////////////////////////
// function: AppGetKey()
//
// creation date:	11/10/00
// last modified:	12/10/00
// purpose: pause until user presses a key
//
// arguments: none
//
// return value: none
// ///////////////////////////////////////////////////////////

void AppGetKey()
{
#ifdef WIN32
	_getch();
#endif
}


