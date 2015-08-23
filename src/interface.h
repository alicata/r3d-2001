// //////////////////////////////////////////////////////////
// file name: interface.h
//
// author:			Aaron Licata
// creation date:	21/04/01
// last modified:	21/04/01
// version number:	1
//
// description: file for abstract interfaces
//
// //////////////////////////////////////////////////////////


#ifndef GEOMETRY_BUILDER_INTERFACE_H
#define GEOMETRY_BUILDER_INTERFACE_H

#include "geom.h"
// //////////////////////////////////////////////////////////
// class name: GeometryBuilderInterfac
//
// author:			Aaron Licata
// creation date:	21/04/01
// last modified:	21/04/01
// version number:	1
//
// description: abstract interface for a geometry builder
//
// //////////////////////////////////////////////////////////

class GeometryBuilderInterface 
{

public:
	GeometryBuilderInterface() {}

	virtual void Build (TetraList&) = 0;

};


#endif

