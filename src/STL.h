// /////////////////////////////////////////////////
// STL.h
//
// author:			Aaron Licata
// creation date:	14/09/00
// last modified:	14/09/00
//
// Header file to enable native STL in a portable way  
//
// Note: STL.h must be the last of the includes in a source file

#ifndef NATIVE_STL_H
#define NATIVE_STL_H

#include "config.h"

#ifdef WIN32
	#pragma warning(disable: 4786)
	using namespace std;
#endif

#ifdef LINUX	
// linux stl stuff
#endif

#ifdef SOLARIS	
// solaris stl stuff
#endif


#endif
