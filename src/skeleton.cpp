// /////////////////////////////////////////////////
// geom.cpp
//
// author:			Aaron Licata
// creation date:	20/08/00
// last modified:	20/08/00
//
// Header file for all general geometrical data structures
// and procedures

#include "geom.h"



// ///////////////////////////////////////////////////////////
// function: Skeleton()
//
// creation date:	11/01/01
// last modified:	11/01/01
// purpose: constructor
// arguments: n/a
//
// return value: none
// ///////////////////////////////////////////////////////////

Skeleton::Skeleton()
{
	vert = 0;
	vertCount = 0;
	edge = 0;
	edgeCount = 0;
	face = 0;
	faceIndex = 0;
	faceCount = 0;
	tetra = 0;
	tetraCount = 0;
	mesh = 0;
	meshCount = 0;

}



// ///////////////////////////////////////////////////////////
// function: ~Skeleton()
//
// creation date:	11/01/01
// last modified:	11/01/01
// purpose: destructor
// arguments: n/a
//
// return value: none
// ///////////////////////////////////////////////////////////

Skeleton::~Skeleton()
{
	
	if (vert && vertCount > 0)
	{
	    delete [] vert;
	}

	
	if (faceIndex && faceCount > 0)
	{
		delete [] faceIndex;
	}

	if (face && faceCount > 0)
	{
		delete [] face;
	}
	
}
