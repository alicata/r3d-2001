// ////////////////////////////////////////////////////////////////
// delaunay.h
//
// author:			Aaron Licata
// creation date:	30/08/00
// last modified:	30/08/00
//
// Header file for delaunay tetrahedralization 
// 
// /////////////////////////////////////////////////////////////////
#ifndef DELAUNAY_H
#define DELAUNAY_H

#include <list>
#include "STL.h"
#include "geom.h"
#include "interface.h"


// flags to distinguish between non-degenerate and degenerate intersection cases
#define DELAUNAY_CIRCUMSPHERE_NOT_INTERSECTED 0
#define DELAUNAY_CIRCUMSPHERE_INTERSECTED 1
#define DELAUNAY_CIRCUMSPHERE_REJECTED 2



// ////////////////////////////////////////////////////////////////
// class DelaunayTetrahedralizer 
//
// author:			Aaron Licata
// creation date:	30/08/00
// last modified:	21/04/01
//
// purpose: class for building a Delaunay tetrahedralization
// 
// /////////////////////////////////////////////////////////////////

class DelaunayTetrahedralizer : public GeometryBuilderInterface
{
private:

	// geometry builder interface
public:
	void Build(TetraList& tetraList);

	// other operatatoins
public:
	SuperTetra& GetSuperTetra() { return superTetra; }

private:	
	int CircumsphereIsIntersected(Tetrahedron *tetra, int pointIndex);
	Tetrahedron* CreateSuperTetrahedron(Vertex3* vert, int numVerts);
	void RetainSinglyOccurringFaces(list<Face3*> &faces);
	void CreateTetrahedronFrom4FacesAndPoint(list<Face3*> &faces, int pointIndex, TetraList &tetras);
	void CreatedAndWireTetrahedraFromSOF(list<Face3*> &faces, int pointIndex, TetraList& tetras);
	void CreatedAndWireTetrahedraFromSOF2(list<Face3*> &faces, int pointIndex, TetraList& tetras);
	void FlagAndDeleteBallSeededTetrahedra(TetraList &tetras, int pointIdex, list<Face3*> &temp);
	void DeleteArbitraryBoundaryFaces(TetraList &tetraList);

private:
	void RewireNeighbouringTetrahedron(Tetrahedron *tetra, Face3* externalFace);
    void WireTetrahedron(TetraList::RevItr startTetraItr, TetraList::RevItr stopTetraItr, TetraList::RevItr newTetraItr);
	void WireTetrahedron2(TetraList::Itr& startTetraItr, TetraList::Itr& stopTetraItr, TetraList::Itr& newTetraItr);
	void FlagTetrahedronForDeletion(TetraList::Itr tetraItr);
	void DeleteFlaggedTetrahedra(TetraList& tetraList, TetraList::Itr firstItr, TetraList::Itr lastItr, TetraList::Itr notFound);
	void RestoreFlaggedTetrahedra(TetraList::Itr firstItr, TetraList::Itr lastItr, TetraList::Itr notFound);
	bool IsTetraTouchingSuperBoundary(Tetrahedron *tetra, Vertex3* a[4]);

private:
	double machineTollerance;
	SuperTetra superTetra;
};



// ////////////////////////////////////////////////////////////////
// class VoronoiTessellator
//
// author:			Aaron Licata
// creation date:	30/08/00
// last modified:	21/04/01
//
// purpose: class for building a Voronoi Tessellation
// 
// /////////////////////////////////////////////////////////////////
class VoronoiTessellator : public GeometryBuilderInterface
{
private:

	// geometry builder interface
public:
	void Build(TetraList& tetraList);

	// other operatatoins
public:
	void LinkVerticesToNeighTetrahedra(TetraList &tetraList);

private:
	void WireTwoNeighbouringTetrahedra(int faceIndex, Tetrahedron* someTetra, Tetrahedron* tetra, int& faceCount);
	void FindNeighbouringFaces(TetraList& tetraList, Tetrahedron* tetra);

};




#endif
