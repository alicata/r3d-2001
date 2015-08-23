// /////////////////////////////////////////////////
// apperr.cpp
//
// author:			Aaron Licata
// creation date:	01/09/00
// last modified:	01/09/00
//
// Implementation file for application error handling

#include "config.h"		// HALT_ON_ERROR
#include "clock.h"		// GetTimeStamp
#include "appio.h"		// AppOut
#include "apperr.h"		// AppError, APPERR_EXIT_NO
#include <stdlib.h>		// exit

// ///////////////////////////////////////////////////////////
// function: AppError()
//
// creation date:	01/09/00
// last modified:	01/09/00
// purpose: OS independent error message 
//
// arguments: error message to print

// return value: none
// ///////////////////////////////////////////////////////////
void AppError(char *msg)
{
	AppOut(msg);

	if (ERROR_MODE_VERBOSE)
	{
		char timeStamp[80];
		GetTimeStamp(timeStamp);
		AppOut(timeStamp);
	}

	AppEndl();
	

	if (HALT_ON_ERROR)
	{
		exit(APPERR_EXIT_ERROR_NO);
	}
}
