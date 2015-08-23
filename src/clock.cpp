// ///////////////////////////////////////////////////////////
// clock.cpp
//
// author:		Aaron Licata
//
// creation date:	02/09/00
// last modified:	02/09/00
//
// Implementation file for time and clock related functions
//
// ///////////////////////////////////////////////////////////

#include <string.h>
#include "clock.h"
#include "appio.h"

#include <time.h>
#ifdef WIN32	
   #include <windows.h>
   #include <mmsystem.h>
#endif



// ///////////////////////////////////////////////////////////
// function:  GetTimeStamp()
//
// creation date:	03/09/00
// last modified:	09/10/00
// purpose: get a timestap of current time
//
// arguments: destination string
//
// return value: none
// ///////////////////////////////////////////////////////////

void GetTimeStamp(char *timeStamp)
{
#ifdef WIN32
	clock_t time;
    time = timeGetTime();
#endif
	strcpy(timeStamp, "01/09/00 11:05:33 Saturday");
}



// ///////////////////////////////////////////////////////////
// function:  ShowTimeDelta()
//
// creation date:	02/09/00
// last modified:	04/09/00
// purpose: show time elapsed between current call to this
//          function and the previous one
//
// arguments: void
//
// return value: none
// ///////////////////////////////////////////////////////////

void ShowTimeDelta()
{
#ifdef WIN32
	static clock_t past = 0;

	clock_t time = timeGetTime();

    AppOut("elapsed time: "); 
	AppOut(time - past);
	AppEndl();

	past = time;
#endif
}



