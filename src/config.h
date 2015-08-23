// /////////////////////////////////////////////////
// config.h
//
// author:		Aaron Licata
// creation date:	11/08/00
// last modified:	11/08/00
//
// purpose:
// system configuration and hardware dependecies

#ifndef CONFIG_H
#define CONFIG_H

#define PROJECT_PROGRAM_NAME		"Voronoi"
#define PROJECT_PROGRAM_NUMBER		"2"
#define APPLICATION_RELEASE			"2"
#define APPLICATION_VERSION 		"0"



#ifndef LINUX
#define LINUX
#endif

// Complilation settings
#define _DEBUG_STRICT	// assert
#define _DEBUG_APPOUT	// AppOut()

// System enabling options
#define ENABLE_OPTIMIZE_SPEED		0
#define ENABLE_OPTIMIZE_MEMORY		0
#define ENABLE_DEBUGGING			0
#define ENABLE_ERROR_CHECKING		0
#define ENABLE_ROBUST				0
#define ENABLE_EXACT_ARITHMETIC		0
#define ENABLE_NETWORKING           0

// General configuration settings
#define HALT_ON_ERROR				1	// exit application on error
#define ERROR_MODE_VERBOSE          0   // more detail in error messages


#endif
