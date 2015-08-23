// ////////////////////////////////////////////////////////////////
// geom.cpp
//
// author:			Aaron Licata
// creation date:	20/08/00
// last modified:	01/09/00
//
// Implementation file for all general geometrical data structures
// and procedures
// ////////////////////////////////////////////////////////////////

#include <assert.h>
#include "apperr.h"
#include "appio.h"
#include "math.h"
#include "ccenter.h"
#include "geomutil.h"
#include "geom.h"




Vertex3* Vertex3::globalVertexList = NO_LINK;
int Tetrahedron::currentId = 0;




// ///////////////////////////////////////////////////////////
// function: Vertex3 defualt constructor
//
// creation date:	20/08/00
// last modified:	10/10/00
// purpose: constructor
//
// // ///////////////////////////////////////////////////////////

Vertex3::Vertex3() 
{ 
	x = y = z = 0.0;
	neigh = new TetraList; 
	flag = GEOM_UNKNOWN_STATE;
	pole = false;
}


// ///////////////////////////////////////////////////////////
// function: Vertex3  constructor
//
// creation date:	20/08/00
// last modified:	10/10/00
// purpose: constructor
//
// // ///////////////////////////////////////////////////////////

Vertex3::Vertex3(double a, double b, double c) 
{ 
	x=a; y=b; z=c; 
	neigh = new TetraList;
	flag = GEOM_UNKNOWN_STATE;
	pole = false;
}



// ///////////////////////////////////////////////////////////
// function: ~Vertex3 destructor
//
// creation date:	20/08/00
// last modified:	10/10/00
//
// purpose: destructor
//
// // ///////////////////////////////////////////////////////////

Vertex3::~Vertex3() 
{
	
	if (neigh->Size() > 0) 
	{
		while (neigh->Size() > 0)
		{
			neigh->PopBack();
		}
		delete neigh;
	}
}



// ///////////////////////////////////////////////////////////
// function: CopyTo()
//
// creation date:	17/04/01
// last modified:	17/04/01
// purpose: copy the contents of one vertex into another
//
// arguments: reference to the destination vertex
// ///////////////////////////////////////////////////////////

void Vertex3::CopyTo(Vertex3& dest)
{
	double x,y,z;

	dest.x = x;
	dest.y = y;
	dest.z = z;

	dest.neigh = neigh;
	dest.flag = flag;
	dest.pole = pole;
	dest.normal.Set(normal);
}


int Vertex3::globalVertexCount = 0;


void Vertex3::InitNeighborList()
{ 

}

void Vertex3::DeleteNeighborList() 
{  
//	if (neigh) delete neigh;
}




// ////////////////////////////////////////////////////////////////////////
// Edge3 member functions

// ///////////////////////////////////////////////////////////
// function: Edge3()
//
// creation date:	11/09/00
// last modified:	11/09/00
// purpose: default constructor
//
// ///////////////////////////////////////////////////////////
Edge3::Edge3()
{
	SetLocalVertexList(Vertex3::GetGlobalVertexList());
	vert[0] = NO_LINK;
	vert[1] = NO_LINK;
}


// ///////////////////////////////////////////////////////////
// function: Edge3()
//
// creation date:	11/09/00
// last modified:	11/09/00
// purpose: copy  constructor
//
// arguments: edge to be copied
// ///////////////////////////////////////////////////////////

Edge3::Edge3( Edge3& edge)
{
	// copy the pointer to the vertex list of the source
	// edge as well
	SetLocalVertexList(edge.GetLocalVertexList());
	vert[0] = edge.vert[0];
	vert[1] = edge.vert[1];
}



// ///////////////////////////////////////////////////////////
// function: Edge3()
//
// creation date:	11/09/00
// last modified:	11/09/00
// purpose: copy  constructor
//
// arguments: edge to be copied
// ///////////////////////////////////////////////////////////

Edge3::Edge3(const int i0, const int i1) 
{ 
	SetLocalVertexList(Vertex3::GetGlobalVertexList());
	vert[0]=i0; 
	vert[1]=i1; 
}



// ///////////////////////////////////////////////////////////
// function: ~Edge3()
//
// creation date:	11/09/00
// last modified:	11/09/00
// purpose: destructor
//
// ///////////////////////////////////////////////////////////

Edge3::~Edge3()                
{
	
}  



// ///////////////////////////////////////////////////////////
// function: V()
//
// creation date:	11/09/00
// last modified:	11/09/00
// purpose: return pointer to an edge vertex
//
// arguments: index of vertex
// ///////////////////////////////////////////////////////////

Vertex3 *Edge3::V(int i) 
{ 
	assert(i<2&&i>=0);
	return &vertexList[vert[i]]; 
}



// ///////////////////////////////////////////////////////////
// function: V()
//
// creation date:	11/09/00
// last modified:	11/09/00
// purpose: return pointer to an edge vertex
//
// arguments: index of vertex
//
// return value: none
// ///////////////////////////////////////////////////////////

void Edge3::V(int i, Vertex3& value) 
{ 
	assert(i<2&&i>=0);
	vertexList[vert[i]].x = value.x;
	vertexList[vert[i]].y = value.y;
	vertexList[vert[i]].z = value.z;
}




// ///////////////////////////////////////////////////////////
// function: I()
//
// creation date:	11/09/00
// last modified:	11/09/00
// purpose: return index to an edge vertex
//
// arguments: edge's end vertex
//
// return value: none
// ///////////////////////////////////////////////////////////

void Edge3::I(int i, int indexValue) 
{
	assert(i<2&&i>=0); 
	vert[i] = indexValue; 
}



// ///////////////////////////////////////////////////////////
// function: I()
//
// creation date:	11/09/00
// last modified:	11/09/00
// purpose: return index to an edge vertex
//
// arguments: edge's end vertex
//
// return value: none
// ///////////////////////////////////////////////////////////

int Edge3::I(int i) 
{
	assert((i<2)&&(i>=0)); 
	return vert[i]; 
}




// ///////////////////////////////////////////////////////////
// function: Print()
//
// creation date:	11/09/00
// last modified:	11/09/00
// purpose: print value of an edge
//
// arguments: none
//
// return value: none
// ///////////////////////////////////////////////////////////

void Edge3::Print()
{
	AppOut("-EDGE- ");
	AppOut("I0:"); AppOut(I(0)); AppOut(" I1:"); AppOut(I(1));
	AppEndl();
}


// ///////////////////////////////////////////////////////////
// function: PrintV()
//
// creation date:	11/09/00
// last modified:	11/09/00
// purpose: print value of an edge
//
// arguments: none
//
// return value: none
// ///////////////////////////////////////////////////////////

void Edge3::PrintV()
{
	AppOutN("- EDGE-:");
	AppOut("I0 "); AppOutN(I(0));
	AppOut("I1 "); AppOutN(I(1));
	Vertex3 *v;
	v = V(0);
	AppOut("V0 "); AppOut(v->x); AppOut(v->y); AppOutN(v->z);
	v = V(1);
	AppOut("V1 "); AppOut(v->x); AppOut(v->y); AppOutN(v->z);
}



// ///////////////////////////////////////////////////////////
// function: operator=
//
// creation date:	11/09/00
// last modified:	11/09/00
// purpose: overload operator =
//
// arguments: edge to be copied
//
// return value: edge reference
// ///////////////////////////////////////////////////////////

Edge3& Edge3::operator=( const Edge3& edge)       //  assignment operator
{
	if (this == &edge)
		return *this;
	vert[0] = edge.vert[0];
	vert[1] = edge.vert[1];

	return *this;
}



// ///////////////////////////////////////////////////////////
// function: operator=
//
// creation date:	11/09/00
// last modified:	11/09/00
// purpose: set pointer to vertex list
//
// arguments: vertex list
//
// return value: none
// ///////////////////////////////////////////////////////////

void Edge3::SetLocalVertexList(Vertex3* commonPool)
{
	vertexList = commonPool;
}



// ///////////////////////////////////////////////////////////
// function: operator[]
//
// creation date:	11/09/00
// last modified:	11/09/00
// purpose: overload operator[]
// arguments: vertex index
//
// return value: none
// ///////////////////////////////////////////////////////////

int& Edge3::operator[]( int i )                // access to component character - wise?
{
	assert(i >= 0 && i < 2);
	return vert[i];
}



// ///////////////////////////////////////////////////////////
// function: IsEqual()
//
// creation date:	11/01/01
// last modified:	11/01/01
// purpose: compare two edges
// arguments: edge to be compared
//
// return value: result of comparison
// ///////////////////////////////////////////////////////////

int Edge3::IsEqual(Edge3& r)
{
	Edge3& l = (*this);

	return (((l.vert[0]==r.vert[0]) && (l.vert[1]==r.vert[1]))) ||
		(((l.vert[0]==r.vert[1]) && (l.vert[1]==r.vert[0])));
}



// ////////////////////////////////////////////////////////////////////////
// global functions related to class Edge3
//

int operator==(Edge3& l, Edge3& r)  //  equality operator
{
	return (((l.vert[0]==r.vert[0]) && (l.vert[1]==r.vert[1]))) ||
		(((l.vert[0]==r.vert[1]) && (l.vert[1]==r.vert[0])));
}

int operator!=( Edge3& l, Edge3& r)  //  inequality operator
{
	return ((l.vert[0]!=r.vert[0]) || (l.vert[0]!=r.vert[1])) ;
}




// ///////////////////////////////////////////////////////////
// function: default constructor
//
// creation date:	11/09/00
// last modified:	11/09/00
// purpose: default constructor
// arguments: none
//
// return value: none
// ///////////////////////////////////////////////////////////

Face3::Face3()
{
	// Edge3 defult constructor called automatically
	neigh = NO_LINK;
	flag = GEOM_UNKNOWN_STATE;
}




// ///////////////////////////////////////////////////////////
// function: copyt constructor
//
// creation date:	11/09/00
// last modified:	11/09/00
// purpose: copy constructor
// arguments: face to be copied
//
// return value: none
// ///////////////////////////////////////////////////////////

Face3::Face3( const Face3& face)
{
	edge[0] = face.edge[0];
	edge[1] = face.edge[1];
	edge[2] = face.edge[2];
	neigh = NO_LINK;
	MakeNormal();
	flag = GEOM_UNKNOWN_STATE;
}

// ///////////////////////////////////////////////////////////
// function: Face3()
//
// creation date:	11/09/00
// last modified:	11/09/00
// purpose: constructor
// arguments: none
//
// return value: none
// ///////////////////////////////////////////////////////////

Face3::Face3(Edge3& e0, Edge3& e1, Edge3& e2)
{
	edge[0] = e0;
	edge[1] = e1;
	edge[2] = e2;
	neigh = NO_LINK;
	MakeNormal();
	flag = GEOM_UNKNOWN_STATE;
}




// ///////////////////////////////////////////////////////////
// function: Face3()
//
// creation date:	11/09/00
// last modified:	11/09/00
// purpose: conversion constructor
// arguments: none
//
// return value: none
// ///////////////////////////////////////////////////////////

Face3::Face3(int i0, int i1, int i2)
{
	edge[0] = Edge3(i0, i1);
	edge[1] = Edge3(i1, i2);
	edge[2] = Edge3(i2, i0);
	neigh = NO_LINK;
	MakeNormal();
	flag = GEOM_UNKNOWN_STATE;
}



// ///////////////////////////////////////////////////////////
// function: Face3()
//
// creation date:	11/09/00
// last modified:	11/09/00
// purpose: conversion constructor
// arguments: none
//
// return value: none
// ///////////////////////////////////////////////////////////

Face3::Face3(int i0, int i1, int i2, Vertex3 *commonPool)
{
	edge[0] = Edge3(i0, i1);
	edge[1] = Edge3(i1, i2);
	edge[2] = Edge3(i2, i0);

	edge[0].SetLocalVertexList(commonPool);
	edge[1].SetLocalVertexList(commonPool);
	edge[2].SetLocalVertexList(commonPool);
	neigh = NO_LINK;
	MakeNormal();
	flag = GEOM_UNKNOWN_STATE;
}




// ///////////////////////////////////////////////////////////
// function: SetLocalVertexList()
//
// creation date:	11/09/00
// last modified:	11/09/00
// purpose: specify the vertex list
// arguments: vertex list
//
// return value: none
// ///////////////////////////////////////////////////////////

void Face3::SetLocalVertexList(Vertex3* commonPool)
{
	edge[0].SetLocalVertexList(commonPool);
	edge[1].SetLocalVertexList(commonPool);
	edge[2].SetLocalVertexList(commonPool);
}



// ///////////////////////////////////////////////////////////
// function: destructor
//
// creation date:	11/09/00
// last modified:	11/09/00
// purpose: destructor
// arguments: none
//
// return value: none
// ///////////////////////////////////////////////////////////

Face3::~Face3()                
{
	
}  




// ///////////////////////////////////////////////////////////
// function: Flip()
//
// creation date:	06/03/01
// last modified:	06/03/01
// purpose: flip last two edges of a face; the effect is to 
//			convert a face from ccw to cw or viceversa
//
// arguments: none
//
// return value: none
// ///////////////////////////////////////////////////////////

void Face3::Flip() 
{ 
	Edge3 tmp = edge[1]; 
	edge[1] = edge[2]; 
	edge[2] = tmp; 
	MakeNormal();
}



// ///////////////////////////////////////////////////////////
// function: MakeNormal()
//
// creation date:	17/02/01
// last modified:	06/03/01
// purpose: calculate the normal (perpendiacular) vector to this face
//
// arguments: none
//
// return value: none
// ///////////////////////////////////////////////////////////

void Face3::MakeNormal()
{
	// prepare the components of two vectors from three vertices of face
	double x1 = this->V(0)->x - this->V(1)->x;
	double y1 = this->V(0)->y - this->V(1)->y;
	double z1 = this->V(0)->z - this->V(1)->z;

	double x2 = this->V(0)->x - this->V(2)->x;
	double y2 = this->V(0)->y - this->V(2)->y;
	double z2 = this->V(0)->z - this->V(2)->z;

	// vector product of two vectors is the normal to the face
	Vector3 v1(x1, y1, z1);
	Vector3 v2(x2, y2, z2);
	CrossProduct3(v1, v2, normal);
}



// ///////////////////////////////////////////////////////////
// function: IsClockWise()
//
// creation date:	06/03/01
// last modified:	06/03/01
// purpose: wrapper function to establish whether a face in 3-d 
//          is clockwise or counterclockwise. 
//
// arguments: none
//
// return value: boolean true if cw, false if ccw
// ///////////////////////////////////////////////////////////

bool Face3::IsClockWise()
{
	if (GetFlag() == GEOM_UNKNOWN_STATE)
	{

		if (IsFaceClockWise(this, &normal))
		{
			SetFlag(GEOM_FACE_IS_CW);
		}
		else
		{
			SetFlag(GEOM_FACE_IS_NOT_CW);
		}
	}
	
	return (GetFlag() == GEOM_FACE_IS_CW);
	
}

	

// ///////////////////////////////////////////////////////////
// function: operator=
//
// creation date:	06/03/01
// last modified:	06/03/01
// purpose: assigment operator
//      
// arguments: face to be copied
//
// return value: face reference
// ///////////////////////////////////////////////////////////

Face3& Face3::operator=( const Face3& f)       //  assignment operator
{
	if (this == &f)
		return *this;
	edge[0] = f.edge[0];
	edge[1] = f.edge[1];
	edge[2] = f.edge[2];

	normal.Set(f.normal.x, f.normal.y, f.normal.z);
	return *this;
}
 


// ///////////////////////////////////////////////////////////
// function: Print()
//
// creation date:	30/09/00
// last modified:	30/09/00
// purpose: print content of face
//      
// arguments: none
//
// return value: none
// ///////////////////////////////////////////////////////////

void Face3::Print()
{
	AppOut("*FACE*:");
    AppEndl();
	AppOut("  E0 ");  edge[0].Print();
	AppOut("  E1 ");  edge[1].Print();
	AppOut("  E2 ");  edge[2].Print();
}



// ///////////////////////////////////////////////////////////
// function: Print()
//
// creation date:	30/09/00
// last modified:	30/09/00
// purpose: print content of face
//      
// arguments: none
//
// return value: none
// ///////////////////////////////////////////////////////////

void Face3::PrintV()
{
	AppOutN("-FACE-:");
	AppOut("E0 ");  edge[0].PrintV();
	AppOut("E1 "); edge[1].PrintV();
	AppOut("E2 ");  edge[2].PrintV();
}



// ///////////////////////////////////////////////////////////
// function: operator[]
//
// creation date:	30/09/00
// last modified:	30/09/00
// purpose: access operator
//      
// arguments: edge index 
//
// return value: edge reference
// ///////////////////////////////////////////////////////////

Edge3& Face3::operator[]( int i )                // access to component character - wise?
{
	assert(i >= 0 && i < 3);
	return edge[i];
}



// ///////////////////////////////////////////////////////////
// function: V()
//
// creation date:	02/09/00
// last modified:	11/02/01
// purpose: returns a pointer to a face vertex
//
// arguments: index of the required vertex
// ///////////////////////////////////////////////////////////

Vertex3 *Face3::V(int i) 
{
////////////////////////ASSERTIONS///////////////////////
#ifndef _DEBUG_STRICT
	assert(i >= 0 && i <= 2);
#endif
//////////////////////////////////////////////////////////

	return edge[i].V(0); 
}



// ////////////////////////////////////////////////////////////////////////
// global functions related to class Face3
//

// ///////////////////////////////////////////////////////////
// function: equality operator
//
// creation date:	30/09/00
// last modified:	30/09/00
// purpose: compare faces
//      
// arguments: faces to compare
//
// return value: result of comparison
// ///////////////////////////////////////////////////////////

int operator==(Face3& l, Face3& r)  //  equality operator
{
	// Case 1
	//     L0==R0
        //     |    |     
	// L1==R1  L1==R2
	//    |      |
	// L2==R2  L2==R1
	if ( l.edge[0].IsEqual(r.edge[0]) )
	{
		if (l.edge[1].IsEqual(r.edge[1]))
		{
			if (l.edge[2].IsEqual(r.edge[2]))
			{
				return 1;
			}
		}
		else if (l.edge[1].IsEqual(r.edge[2]))
		{
			if (l.edge[2].IsEqual(r.edge[1]))
			{
				return 1;
			}
		}
	}

	// Case 2
	//     L0==R1
	//     |    |
	// L1==R0  L1==R2
	//    |      |
	// L2==R2  L2==R0
	if (l.edge[0].IsEqual(r.edge[1]))
	{
		if (l.edge[1].IsEqual(r.edge[0]))
		{
			if (l.edge[2].IsEqual(r.edge[2]))
			{
				return 1;
			}
		}
		else if (l.edge[1].IsEqual(r.edge[2]))
		{
				if (l.edge[2].IsEqual(r.edge[0]))
				{
					return 1;
				}
		}
	}

	// Case 3
	//     L0==R2
	//     |    |
	// L1==R0  L1==R0
	//    |      |
	// L2==R1  L2==R0
	if (l.edge[0].IsEqual(r.edge[2]))
	{
		if (l.edge[1].IsEqual(r.edge[0]))
		{
			if (l.edge[2].IsEqual(r.edge[1]))
			{
				return 1;
			}
		}
		else if (l.edge[1].IsEqual(r.edge[0]))
		{
				if (l.edge[2].IsEqual(r.edge[0]))
				{
					return 1;
				}
		}
	}

	return 0;
}


// ///////////////////////////////////////////////////////////
// function: disequality operator
//
// creation date:	30/09/00
// last modified:	30/09/00
// purpose: compare faces
//      
// arguments: faces to compare
//
// return value: result of comparison
// ///////////////////////////////////////////////////////////

int operator!=(Face3& l, Face3& r)  //  inequality operator
{
	return !(l == r);
}



// ///////////////////////////////////////////////////////////
// function: Tetrahedron()
//
// creation date:	30/09/00
// last modified:	30/09/00
// purpose: default constructor
//      
// arguments: none
//
// return value: none
// ///////////////////////////////////////////////////////////

Tetrahedron::Tetrahedron()
{	
	face[0] = NO_LINK;
	face[1] = NO_LINK;
	face[2] = NO_LINK;
	face[3] = NO_LINK;
	InitializeTetra();
}



// ///////////////////////////////////////////////////////////
// function: Tetrahedron()
//
// creation date:	30/09/00
// last modified:	30/09/00
// purpose: copy constructor
//      
// arguments: tetrahedron
//
// return value: none
// ///////////////////////////////////////////////////////////

Tetrahedron::Tetrahedron( const Tetrahedron& tetra)
{
	// allocate new identical faces for this Tetrahedron
	face[0] = new Face3(*(tetra.face[0]));
	face[1] = new Face3(*(tetra.face[1]));
	face[2] = new Face3(*(tetra.face[2]));
	face[3] = new Face3(*(tetra.face[3]));
	face[0]->neigh = tetra.face[0]->neigh;
	face[1]->neigh = tetra.face[1]->neigh;
	face[2]->neigh = tetra.face[2]->neigh;
	face[3]->neigh = tetra.face[3]->neigh;

	// are these pointers to a global face list?
	// or are they local to this object
	localCopy = true;
	InitializeTetra();

	COPYVERTS(center, tetra.center);
	squareRadius = tetra.squareRadius;
	CalculateCentreAndRadius();

}



// ///////////////////////////////////////////////////////////
// function: Tetrahedron()
//
// creation date:	30/09/00
// last modified:	30/09/00
// purpose: conversion constructor
//      
// arguments: faces
//
// return value: none
// ///////////////////////////////////////////////////////////

Tetrahedron::Tetrahedron(Face3& f0, Face3& f1, Face3& f2, Face3& f3)
{
	// save face pointers in the private face list
	face[0] = new Face3(f0);
	face[1] = new Face3(f1);
	face[2] = new Face3(f2);
	face[3] = new Face3(f3);
    //InitNeighbours();

	// are these pointers to a global face list?
	// or are they local to this object
	localCopy = true;
	InitializeTetra();
	CalculateCentreAndRadius();
}



// ///////////////////////////////////////////////////////////
// function: Tetrahedron()
//
// creation date:	30/09/00
// last modified:	30/09/00
// purpose: conversion constructor
//      
// arguments: faces
//
// return value: none
// ///////////////////////////////////////////////////////////

Tetrahedron::Tetrahedron(Face3* f0, Face3* f1, Face3* f2, Face3* f3)
{
	// just copy the links to the already allocated Face3 object
	face[0] = f0;
	face[1] = f1;
	face[2] = f2;
	face[3] = f3;
    //InitNeighbours();

	// are these pointers to a global face list?
	// or are they local to this object
	localCopy = true;
	InitializeTetra();
	CalculateCentreAndRadius();
}



// ///////////////////////////////////////////////////////////
// function: ~Tetrahedron()
//
// creation date:	30/09/00
// last modified:	30/09/00
// purpose: destructor
//      
// arguments: none
//
// return value: none
// ///////////////////////////////////////////////////////////

Tetrahedron::~Tetrahedron()                
{
	assert(face[0] && face[1] && face[2] && face[3]);

	if (localCopy)
	{
		delete face[0];
		delete face[1];
		delete face[2];
		delete face[3];
	}
}  



// ///////////////////////////////////////////////////////////
// function: InitializeTetra()
//
// creation date:	30/09/00
// last modified:	30/09/00
// purpose: initialize a tetrahedron
//      
// arguments: none
//
// return value: none
// ///////////////////////////////////////////////////////////

void Tetrahedron::InitializeTetra()
{
	id = Tetrahedron::GetCurrentID();
	Tetrahedron::SetCurrentID(id+1);

	SetLocalVertexList(Vertex3::GetGlobalVertexList());
	flagged = false;
	drawn = false;
}




// ///////////////////////////////////////////////////////////
// function: CalculateCentreAndRadius()
//
// creation date:	30/09/00
// last modified:	30/09/00
// purpose: calcualate center and radius of a tetrahedron
//      
// arguments: none
//
// return value: none
// ///////////////////////////////////////////////////////////

void Tetrahedron::CalculateCentreAndRadius()
{
	double a[3];
	double b[3];
	double c[3];
	double d[3];

	Vertex3 p0, p1, p2, p3;

	SetLocalVertexList(Vertex3::GetGlobalVertexList());
	// TODO: change code to use GetAllVerticesInOrder()
	// like
	// Vertex3 p[4];
	// GetAllVerticesInOrder(p)
	COPYVERTS(p0,(*(F(0)->V(0))));
	COPYVERTS(p1,(*(F(0)->V(1))));
	COPYVERTS(p2,(*(F(0)->V(2))));
	COPYVERTS(p3,(*(F(3)->V(2))));

	a[0] = p0.x; a[1] = p0.y; a[2] = p0.z;
    b[0] = p1.x; b[1] = p1.y; b[2] = p1.z;
	c[0] = p2.x; c[1] = p2.y; c[2] = p2.z;
	d[0] = p3.x; d[1] = p3.y; d[2] = p3.z;

	double xi1[3];
	double xi2[3];
	double xi3[3];
	double cc[3];

	TetraCircumCenter(a, b, c, d, cc, xi1, xi2, xi3);

	center.x = cc[0] + a[0];
	center.y = cc[1] + a[1];
	center.z = cc[2] + a[2];

	squareRadius = SQUARE_DISTANCE3(center, p0);
}


// ///////////////////////////////////////////////////////////
// function: InitNeighbours()
//
// creation date:	30/09/00
// last modified:	30/09/00
// purpose: initialize neighbour
//      
// arguments: none
//
// return value: none
// ///////////////////////////////////////////////////////////

void Tetrahedron::InitNeighbours()
{
	face[0] = NO_LINK;
	face[1] = NO_LINK;
	face[2] = NO_LINK;
	face[3] = NO_LINK;

}



// ///////////////////////////////////////////////////////////
// function: Print()
//
// creation date:	10/10/00
// last modified:	10/10/00
// purpose: print content of tetrahedron
//      
// arguments: none
//
// return value: none
// ///////////////////////////////////////////////////////////

void Tetrahedron::Print()
{
	AppOut(".TETRAHEDON............................................."); 
	AppEndl();
	AppOut(" F0 "); face[0]->Print();
	AppOut(" F1 "); face[1]->Print();
	AppOut(" F2 "); face[2]->Print();
	AppOut(" F3 "); face[3]->Print();

}



// ///////////////////////////////////////////////////////////
// function: operator=
//
// creation date:	10/10/00
// last modified:	10/10/00
// purpose: operator=
//      
// arguments: tetrahedron
//
// return value: tetrahedron reference
// ///////////////////////////////////////////////////////////

Tetrahedron& Tetrahedron::operator=( const Tetrahedron& tetra)       //  assignment operator
{
	if (this == &tetra)
		return *this;

	// delete current four faces
	assert(face[0] && face[1] && face[2] && face[3]);
		delete face[0];
		delete face[1];
		delete face[2];
		delete face[3];

	// copy four faces from some tetrahedron to this one
	// use pointers to faces of source tetrahedron as 
	// source of information
	face[0] = new Face3(*tetra.face[0]);
	face[1] = new Face3(*tetra.face[1]);
	face[2] = new Face3(*tetra.face[2]);
	face[3] = new Face3(*tetra.face[3]);

	return *this;
}


// ///////////////////////////////////////////////////////////
// function: operator[]
//
// creation date:	10/10/00
// last modified:	10/10/00
// purpose: operator[]
//      
// arguments: index to faces
//
// return value: face pointer reference
// ///////////////////////////////////////////////////////////

Face3*& Tetrahedron::operator[]( int i )                // access to component character - wise?
{
	assert(i >= 0 && i < 4);
	return face[i];
}



// ///////////////////////////////////////////////////////////
// function: face index
//
// creation date:	10/10/00
// last modified:	10/10/00
// purpose: face index
//      
// arguments: index to faces
//
// return value: face pointer reference
// ///////////////////////////////////////////////////////////

Face3* Tetrahedron::F( int i )                // access to component character - wise?
{
	assert(i >= 0 && i < 4);
	return face[i];
}



// ///////////////////////////////////////////////////////////
// function: GetAllVerticesInOrder()
//
// creation date:	10/10/00
// last modified:	10/10/00
// purpose: get all vertices in order
//      
// arguments: pointer to vertex
//
// return value: none
// ///////////////////////////////////////////////////////////

void Tetrahedron::GetAllVerticesInOrder(Vertex3 *v)
{
	// get the four vertices of tetra in right order
	// so, to avoid confusion and bugs
	// TODO: implement

}



// ///////////////////////////////////////////////////////////
// function: SetLocalVertexList()
//
// creation date:	10/10/00
// last modified:	10/10/00
// purpose: specify vertex list
//      
// arguments: pointer to vertex list
//
// return value: none
// ///////////////////////////////////////////////////////////

void Tetrahedron::SetLocalVertexList(Vertex3* commonPool)
{
	face[0]->SetLocalVertexList(commonPool);
	face[1]->SetLocalVertexList(commonPool);
	face[2]->SetLocalVertexList(commonPool);
	face[3]->SetLocalVertexList(commonPool);
}



// ///////////////////////////////////////////////////////////
// function: AllocFacet()
//
// creation date:	10/10/00
// last modified:	10/10/00
// purpose: allocate face
//      
// arguments: index 
//
// return value: allocation result
// ///////////////////////////////////////////////////////////

int Tetrahedron::AllocFace(int i)
{
	face[i] = new Face3;
	if (!face[i])
	{
		AppError(APPERR_FACE_ALLOC);
		return 0;
	}

	return 1;
}

/*
void Tetrahedron::SetFace(int i, Edge3& e1, Edge3& e2, Edge3& e3)
{
	face[i]->SetEdge(0, e1);
	face[i]->SetEdge(1, e2);
	face[i]->SetEdge(2, e3);
}
*/
// ////////////////////////////////////////////////////////////////////////
// global functions related to class Tetrahedron
 //


// ///////////////////////////////////////////////////////////
// function: operator==
//
// creation date:	10/10/00
// last modified:	10/10/00
// purpose: operator==
//      
// arguments: tetrahedra
//
// return value: none
// ///////////////////////////////////////////////////////////

int operator==( const Tetrahedron& l, const Tetrahedron& r)  //  equality operator
{
	// TODO
	return 1;
}



// ///////////////////////////////////////////////////////////
// function: inequality operator
//
// creation date:	10/10/00
// last modified:	10/10/00
// purpose: inequality operator
//      
// arguments: tetrahedra
//
// return value: none
// ///////////////////////////////////////////////////////////

int operator!=( const Tetrahedron& l, const Tetrahedron& r)  //  inequality operator
{
	return 0;
}




// ///////////////////////////////////////////////////////
// FaceList
//
// ///////////////////////////////////////////////////////
// FaceListDeleteAll()
// purpose: delete all objects pointed to by and 
// the nodes of the list
void Face3List::DeleteAll()
{
	Itr start = faceList.begin();
	Itr end   = faceList.end();
    Itr tmp;

	while (start != end)
	{
		tmp = start;
		assert(start != end);
		start++;
		
		static int count = 0;
		AppOut("count: "); 
		AppOut(count++);
		AppEndl();
		// delete object and then its node
		assert(*tmp != NULL);
		delete *tmp;
		assert(tmp != NULL);
		faceList.erase(tmp);
	}
}


// ////////////////////////////////////////////////////////
// TetraList
//




// ///////////////////////////////////////////////////////////
// function: DeleteAll()
//
// creation date:	10/10/00
// last modified:	10/10/00
// purpose: delete all tetrahedra in list
//      
// arguments: none
//
// return value: none
// ///////////////////////////////////////////////////////////

void TetraList::DeleteAll()
{
	Itr start = tetraList.begin();
	Itr end   = tetraList.end();
    Itr tmp;

	while (start != end)
	{
		tmp = start;
		assert(start != end);
		start++;

		// delete object and then its node
		delete *tmp;
		tetraList.erase(tmp);
	}
}




// ///////////////////////////////////////////////////////////
// function: Delete()
//
// creation date:	10/10/00
// last modified:	10/10/00
// purpose: delete tetrahedra in list
//      
// arguments: iterator to tetrahedron
//
// return value: none
// ///////////////////////////////////////////////////////////

void TetraList::Delete(Itr &i) 
{
	assert(*i != NULL);

	delete *i;
	tetraList.erase(i);
}




// ///////////////////////////////////////////////////////////
// function: SuperTetra()
//
// creation date:	10/10/00
// last modified:	10/10/00
// purpose: constructor
//      
// arguments: none
//
// return value: none
// ///////////////////////////////////////////////////////////

SuperTetra::SuperTetra()
{
	vApex.SetVertex(0.0, 0.0, 0.0);
	vBaseLeft.SetVertex(0.0, 0.0, 0.0);
	vBaseRight.SetVertex(0.0, 0.0, 0.0);
	vBaseBack.SetVertex(0.0, 0.0, 0.0);

	superFactor = 2;
}




// ///////////////////////////////////////////////////////////
// function: Set()
//
// creation date:	10/02/01
// last modified:	10/02/01
// purpose: delete tetrahedra in list
//      
// arguments: vertices of the super pyramid
//
// return value: none
// ///////////////////////////////////////////////////////////

void SuperTetra::Set(Vertex3 apex, Vertex3 bLeft, Vertex3 bRight, Vertex3 bBack)
{
	vApex.SetVertex(apex);
	vBaseLeft.SetVertex(bLeft);
	vBaseRight.SetVertex(bRight);
	vBaseBack.SetVertex(bBack);
}