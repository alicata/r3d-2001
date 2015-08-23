// //////////////////////////////////////////////////////////
// file name: crust.h
//
// author:			Aaron Licata
// creation date:	14/02/01
// last modified:	16/02/01
// version number:	2
//
// description: crust algorithm related interface file
//
// //////////////////////////////////////////////////////////


#ifndef CRUST_RECONSTRUCTOR_H
#define CRUST_RECONSTRUCTOR_H


#include "interface.h"


// //////////////////////////////////////////////////////////
// file name: MedialAxisTransformer
//
// author:			Aaron Licata
// creation date:	14/02/01
// last modified:	21/04/01
// version number:	2
//
// description: class that implements the medial axis 
//
// //////////////////////////////////////////////////////////

class MedialAxisTransformer : public GeometryBuilderInterface
{
public:
	void Build(TetraList& tetraList) { DoMedialAxisTransform(tetraList); }

public:
	void DoMedialAxisTransform(TetraList& tetraList);
	int GetNumPoles();

	void FindPolesFromDelaunayVertex(int sampleId, Vertex3& pplus, Vertex3& pminus);

private:

};



// //////////////////////////////////////////////////////////
// file name: CrustExtractor
//
// author:			Aaron Licata
// creation date:	14/02/01
// last modified:	21/04/01
// version number:	2
//
// description: class that implements the crust extractor 
//
// //////////////////////////////////////////////////////////

class CrustExtractor : public GeometryBuilderInterface
{
public:
	void Build(TetraList& tetraList) { assert(0); }
	Vertex3* PerformCrustExtraction(TetraList& tetraList, int& destSize);
	void ExtractPolygonMesh(TetraList& tetraList, Skeleton* obj);
    

private:
	Vertex3* IntegratePolesIntoVertexArray(TetraList& tetraList, int totalNumPoles);
	Vertex3* CloneToLargerVertexArray(unsigned int additionalSize);

};


#endif

