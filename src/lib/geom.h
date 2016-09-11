// /////////////////////////////////////////////////
// geom.h
//
// author:			Aaron Licata
// creation date:	20/08/00
// last modified:	20/08/00
//
// Header file for all general geometrical data structures
// and procedures

#ifndef GEOM_H
#define GEOM_H

#include <assert.h>
#include <list>
#include "STL.h"
#include "math.h"
#include "appio.h"

// Constants
#define NO_LINK			0

// Macros
#define COPYVERTS(v0, v1) v0.x=v1.x;v0.y=v1.y;v0.z=v1.z
#define VERTEX3_IS_EQUALP(vl,vr) ((vl->x==vr->x)&&(vl->y==vr->y)&&(vl->z==vr->z))

// forward declarations
class Edge3;
class Face3;
class Tetrahedron;
class TetraList;

#define SET_VERTEX(obj,x,y,z) {obj.x=x;obj.y=y;obj.z=z;} 

// enumeration type for geometry status of tetrahedra, faces, vertices

/*enum GeometryStatus 
{ 
	GEOM_UKNOWN_STATE,
	GEOM_ON_CONVEX_HULL,
	GEOM_NOT_ON_CONVEX_HULL

} GSInstance;
*/

// general
const unsigned char GEOM_UNKNOWN_STATE = 0;
// vertex
const unsigned char GEOM_ON_CONVEX_HULL = 1;
const unsigned char GEOM_NOT_ON_CONVEX_HULL = 2;
// face
const unsigned char GEOM_FACE_IS_CW = 1;
const unsigned char GEOM_FACE_IS_NOT_CW = 2;


// ////////////////////////////////////////////////////////////////
// class Vertex3
//
// author:		Aaron Licata
// creation date:	30/08/00
// last modified:	22/04/01
//
// purpose: class representing a vertex in 3-d space with 
//          information about its direction normal and 
//          connectivity information to the neighbour tetrahedra 
// 
// /////////////////////////////////////////////////////////////////

class Vertex3
{
public:
	Vertex3();
	Vertex3(double a, double b, double c);
	~Vertex3();
	void SetVertex(double a, double b, double c) {x=a; y=b; z=c;}
	void SetVertex(Vertex3& v) { x=v.x; y=v.y; z=v.z; }
	void Print() { AppOut(x); AppOut(y), AppOut(z); AppEndl(); }
	void DeleteNeighborList();
	void InitNeighborList();
	void SetFlag(int status) { flag = status; }
	int GetFlag() { return flag; }
	bool IsPole() { return pole; }
	void SetPole(bool state) { pole = state; }
	Vector3 & Normal() { return normal; }
	static void SetGlobalVertexList(Vertex3* vertList) 
	{ 
		globalVertexList = vertList; 
	}
	static Vertex3* GetVertex(int vertexId) { return &globalVertexList[vertexId];}
	static Vertex3* GetGlobalVertexList() { return globalVertexList; }
	static void SetGlobalVertexCount(int count) { globalVertexCount = count; }
	static int GetGlobalVertexCount() { return globalVertexCount; }

	void CopyTo(Vertex3& dest);

public:
	double x,y,z;
	TetraList *neigh;
	unsigned char flag;
	bool pole;
	Vector3 normal;

private:
	static Vertex3* globalVertexList;
	static int globalVertexCount;

};

void InitNeighborList(Vertex3& v);  
void DeleteNeighborList(Vertex3& v); 


// forward declaration of Face3
class Face3;


// ////////////////////////////////////////////////////////////////
// class Edge3
//
// author:		Aaron Licata
// creation date:	30/09/00
// last modified:	22/04/01
//
// purpose: class representing a edge in 3-d space with 
// 
// /////////////////////////////////////////////////////////////////

class Edge3
{
public:
   
    Edge3() ;                   	//  default constructor
    Edge3( Edge3& );      		//  copy constructor
    Edge3(const int v0, const int v1);
    ~Edge3() ;                   	//  destructor

	void SetLocalVertexList(Vertex3* commonPool);
	Vertex3* GetLocalVertexList() { return vertexList; }
	Vertex3 *V(int i);
	void V(int i, Vertex3& value);
	void I(int i, int indexValue);
	int I(int i);

	void Print();
	void PrintV();

      Edge3& operator=( const Edge3& ) ;  //  assignment operator
	int IsEqual(Edge3& e2);

    friend int operator==( Edge3&, Edge3& ) ; //  equality operator
    friend int operator!=( Edge3&, Edge3& ) ; //  inequality operator

    int& operator[]( int i ) ;               // access to component vertices

public:
    int vert[2]; //  store the vertices as local copies 
	Vertex3 *vertexList;

} ;

int operator==( Edge3& l, Edge3& r);
int operator!=( Edge3& l, Edge3& r);



// ////////////////////////////////////////////////////////////////
// class Face3
//
// author:		Aaron Licata
// creation date:	30/09/00
// last modified:	22/04/01
//
// purpose: class representing a face in 3-d space 
// 
// /////////////////////////////////////////////////////////////////

class Face3
{
public:
   
    Face3() ;                    //  default constructor
    Face3( const Face3& );       //  copy constructor
	Face3(Edge3& e0, Edge3& e1, Edge3& e2); //  conversion constructor
	Face3(int i0, int i1, int i2);
	Face3(int i0, int i1, int i2, Vertex3 *commonPool);

    ~Face3() ;                   //  destructor

	void SetLocalVertexList(Vertex3* commonPool);
    Face3& operator=( const Face3& ) ;  //  assignment operator

    friend int operator==( const Face3&, const Face3& ) ; //  equality operator
    friend int operator!=( const Face3&, const Face3& ) ; //  inequality operator

	Vertex3 *V(int i);
	Edge3 * E(int i) { return &edge[i]; }
	int I(int i) { return edge[i].I(0); }
	void V(int i, Vertex3& v) { edge[i].V(0, v); edge[(i+1)%3].V(1, v);}
	void Flip(); 
	Vector3& Normal() { return normal; }
	void MakeNormal();
	bool IsClockWise(); 
	void SetFlag(unsigned char state) { flag = state; };
	unsigned char GetFlag() { return flag; };


	void Print();
	void PrintV();

    Edge3& operator[]( int i ) ;               // access to component edges - wise?

	void SetEdge(int i, Edge3& e) { edge[i] = e; MakeNormal();}
    
public:
    Edge3 edge[3] ;  //  store the edges as local copies 
public:
	Tetrahedron *neigh;
	Vector3 normal;
	unsigned char flag;
} ;

int operator==(Face3&,Face3& ) ; //  equality operator
int operator!=(Face3&,Face3& ) ; //  inequality operator

class Face3List
{
public:
	typedef list<Face3*>::iterator Itr;
	typedef list<Face3*> Type;
public:
	void Add(Face3* face) { faceList.push_back(face); }
	void RemoveLast() { faceList.pop_back(); }
	Face3* First() { return faceList.front();}
	Face3* Last() { return faceList.back(); }
	Itr Begin() { return faceList.begin(); }
	Itr End() { return faceList.end(); }
	int Size() { return faceList.size(); }
	void DeleteAll();
	
private:
	Type faceList; // global list of faces

};



// ////////////////////////////////////////////////////////////////
// class Tetrahedron
//
// author:		Aaron Licata
// creation date:	30/09/00
// last modified:	22/04/01
//
// purpose: class representing a tetrahedron
// 
// /////////////////////////////////////////////////////////////////

class Tetrahedron
{
public:
    Tetrahedron() ;                    //  default constructor
    Tetrahedron( const Tetrahedron& ); //  copy constructor
	Tetrahedron(Face3& f0, Face3& f1, Face3& f2, Face3& f3);
	Tetrahedron(Face3* f0, Face3* f1, Face3* f2, Face3* f3);

    ~Tetrahedron() ;                   //  destructor
	void Print();


    Tetrahedron& operator=( const Tetrahedron& ) ;  //  assignment operator

    friend int operator==( const Tetrahedron&, const Tetrahedron& ) ; //  equality operator
    friend int operator!=( const Tetrahedron&, const Tetrahedron& ) ; //  inequality operator

    Face3*& operator[]( int i ) ;               // access to component vertices
	Face3* F(int i);
	void InitializeTetra();
	void GetAllVerticesInOrder(Vertex3 *v);
	void CalculateCentreAndRadius();
	void EnableLocalFace(bool mode) { localCopy = mode; }
	void SetLocalVertexList(Vertex3* commonPool);
	int AllocFace(int i);
	void Flagged(bool status) { flagged = status; }
	bool IsFlagged() { return flagged; }
	//void SetFace(int i, Edge3&, Edge3&, Edge3&);
	void InitNeighbours();
	void Drawn(bool state) { drawn = state; }
	bool AlreadyDrawn() { return drawn; }
	int GetID() { return id; }
	Vertex3& Centre() { return center; }
	Vertex3* GetCentre() { return &center; }
	double SquareRadius(){ return squareRadius;}
	static int GetCurrentID() { return currentId; }
private:
	static void SetCurrentID(int i) { currentId = i; }

private:
	Face3* face[4];
	bool localCopy;
	Vertex3 center;			// Voronoi vertex (tetra center)
	double squareRadius;    // square radius from center
	bool flagged;			
	int id;					// id of this tetrahedron
	static int currentId;	// global id generated by Tetrahedron class for next Tetrahedron object
	bool drawn;
	
	
};


// ////////////////////////////////////////////////////////////////
// class TetraList
//
// author:		Aaron Licata
// creation date:	30/09/00
// last modified:	22/04/01
//
// purpose: class representing a list of tetrahedron
// 
// /////////////////////////////////////////////////////////////////

class TetraList
{
public:
	typedef list<Tetrahedron*>::iterator Itr;
	typedef list<Tetrahedron*>::reverse_iterator RevItr;
    typedef list<Tetrahedron*> Type;
public:
	TetraList() {};
	~TetraList() { DeleteAll(); }    


	Type& GetList() { return tetraList; }
	void Add(Tetrahedron* t) { tetraList.push_back(t); }
	Itr Begin() { return tetraList.begin(); }
	RevItr Rbegin() { return tetraList.rbegin(); }
	RevItr Rend() { return tetraList.rend(); }
	Itr End() { return tetraList.end(); }
	Tetrahedron* Last() { return tetraList.back(); }
	void PopBack() { tetraList.pop_back(); }
	Tetrahedron* First() { return tetraList.front(); }
	int Size() { return tetraList.size(); }
	void Erase(Itr &i) {tetraList.erase(i); }
	int Empty() { return tetraList.empty(); }
	void DeleteAll();
	void Delete(Itr &i); 

// data members
private:
	Type tetraList; // global list of tetrahedra

};



// ////////////////////////////////////////////////////////////////
// class SuperTetra
//
// author:			Aaron Licata
// creation date:	30/08/00
// last modified:	22/04/01
//
// purpose: class representing a very large tetrahedron (super)
// 
// /////////////////////////////////////////////////////////////////

class SuperTetra
{
public:
	SuperTetra();
    void Set(Vertex3, Vertex3, Vertex3, Vertex3);
	Vertex3& GetApex() { return vApex; }
	Vertex3& GetBaseLeft() { return vBaseLeft; }
	Vertex3& GetBaseRight() { return vBaseRight; }
	Vertex3& GetBaseBack() { return vBaseBack; }
	void SetSuperFactor(int factor) { superFactor = factor; }
	int GetSuperFactor() { return superFactor ; }



public:
	Vertex3 vApex;
	Vertex3 vBaseLeft;
	Vertex3 vBaseRight;
	Vertex3 vBaseBack;
	int superFactor;
};



/*
class TetraListItr
{
public:

public:
	TetraList::Itr i;
};
*/



class Mesh
{
public:
	Vertex3 *vertData;
	int vertCount;
	Face3 *tri;
	int triCount;
};

class Skeleton
{
public:
	// geometry 
	Vertex3 * vert;
	int vertCount;

	// low-level topology
	Edge3 * edge;
	int edgeCount;

	Face3 * face;
	unsigned long * faceIndex;
	unsigned int faceCount;


	// non-manifold
	Tetrahedron * tetra;
	int tetraCount;

	// non-manifold
	Mesh * mesh;
	int meshCount;

public:
	Skeleton();
	~Skeleton();
};


#endif


