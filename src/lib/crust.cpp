// ///////////////////////////////////////////////////////////
// file name: crust.cpp
//
// author:			Aaron Licata
// creation date:	14/02/01
// last modified:	18/02/01
// version number:	3
//
// description: crust algorithm related implementation module
//
// ///////////////////////////////////////////////////////////

#include "config.h"		
#include "math.h"		// DotProduct3
#include "geom.h"		// Vertex3
#include "geomutil.h"	// IsFaceClockWise
#include "delaunay.h"	// IsFaceOnConvexHull
#include "crust.h"		

int numPoles = 0;


// ///////////////////////////////////////////////////////////
// function: FindPolesFromDelaunayVertex()
//
// creation date:	14/02/01
// last modified:	06/04/01
// purpose: find the two poles from a Delaunay vertex (site)
//
// note: sample point and Delaunay vertex is the same
//
// arguments: sampleId is an index to the vertex list
//            poleMinus is one of the two poles
//			  polePlus is the other pole
//
// return value: none
// ///////////////////////////////////////////////////////////
void MedialAxisTransformer::FindPolesFromDelaunayVertex(int sampleId, Vertex3& poleMinus, Vertex3& polePlus)
{
	Vector3 normal;						// surface normal to sample point
	Vector3 spPlus;						// vector from pole+ to sample point
	Vertex3 *samplePoint;				// sample point (Delaunay vertex)
	Vertex3 *pPlus;						// reference to p+
	Vertex3 *pMinus;					// reference to p-
	double maxExternalMagnitude = 0.0;	// initialize longest external vector
	double maxInternalMagnitude = 0.0;	// initialize longest internal vector
	Tetrahedron *plusTetra = NO_LINK;	// tetra for pole+
	Tetrahedron *minusTetra = NO_LINK;	// tetra for pole-
	
	// find star and end of Voronoi 3-d cell VC(s) of sample point
	samplePoint = Vertex3::GetVertex(sampleId);
	TetraList::Itr startItr = samplePoint->neigh->Begin();
	TetraList::Itr endItr = samplePoint->neigh->End();
	if (startItr == endItr)
	{
     // this Delaunay vertex (sample point) has not neighbouring Voronoi vertices
		return;
	}

    // sample point does not lie on convex-hull
	if (!IsVertexOnConvexHull(sampleId))
	{
		// pole+ is furthest Voronoi vertex of VC(s) from sample point
		while (startItr != endItr)
		{
			// get Voronoi vertex
			Tetrahedron *tetra = *startItr++;
			Vertex3* pVoronoiVertex = tetra->GetCentre();

			// find distance from this Voronoi vertex to the one sample point
			Vector3 temp(pVoronoiVertex->x-samplePoint->x, pVoronoiVertex->y-samplePoint->y, pVoronoiVertex->z-samplePoint->z);
			double spPlusMagnitude = temp.Magnitude();

			// find the largest vector so far
			if (spPlusMagnitude > maxExternalMagnitude)
			{
				maxExternalMagnitude = spPlusMagnitude; // save largest distance

				spPlus.Set(temp.x, temp.y, temp.z);		// save largest vector
				
				// update destination pole to passed to this function
				polePlus.x = pVoronoiVertex->x; 
				polePlus.y = pVoronoiVertex->y;
				polePlus.z = pVoronoiVertex->z;


				pPlus = pVoronoiVertex; // save best vv candidate to be pole
				plusTetra = tetra;
			}
		}
		// normal is vector sp+ from pole+ to sample point
		normal.Set(spPlus.x, spPlus.y, spPlus.z);

		// flagg tetrahedron and its vv as pole 
		plusTetra->Flagged(true);
		if (!plusTetra->GetCentre()->IsPole())
		{
			plusTetra->GetCentre()->SetPole(true);
			numPoles++;
		}

	}
	else // sample point lies on convex-hull
	{
		// ignore pole+ (i.e. pole+ is at infinity)
		polePlus.x = INFINITY;
		polePlus.y = INFINITY;
		polePlus.z = INFINITY;

		// normal is  average of outer normals of adjecent faces
		FindAverageNormalFromAdjecentFaces(sampleId, normal);
		normal.Normalize();

		// save normal for later stages
		Vertex3* vertex = Vertex3::GetVertex(sampleId);
		vertex->normal.Set(normal);
	}    
	
    //  for each Voronoi vertex in the 3-D Voronoi cell
	for (startItr = samplePoint->neigh->Begin(); startItr != endItr; startItr++)
	{
		// determine vector from Voronoi vertex to sample point
		Tetrahedron *tetra = *startItr;
		Vertex3 voronoiVertex = tetra->Centre(); 

		// SP- = vector from Voronoi vertex to sample point 
		Vector3 spMinus(voronoiVertex.x-samplePoint->x, voronoiVertex.y-samplePoint->y, voronoiVertex.z-samplePoint->z);

		// determine whether a vector is internal or external to surface
		// inner pole: dot product between vector SP- and normal is negative
		if (DotProduct3(&spMinus, &normal) < 0)
		{
			// If SP- Is Longest Internal Vector
			double spMinusMagnitude = spMinus.Magnitude();

			// enstablish longest internal vector
			if (spMinusMagnitude > maxInternalMagnitude)
			{
				maxInternalMagnitude = spMinusMagnitude;

				// pole- = current Voronoi vertex
				poleMinus.x = voronoiVertex.x;
				poleMinus.y = voronoiVertex.y;
				poleMinus.z = voronoiVertex.z;
				// store reference to current farthest
				pMinus = &voronoiVertex;
				minusTetra = tetra;
			}
		}
	}
    if (minusTetra != NO_LINK)
	{
		minusTetra->Flagged(true);
		if (!minusTetra->GetCentre()->IsPole())
		{
			minusTetra->GetCentre()->SetPole(true);
			numPoles++;
		}

	}
	// end of for Voronoi cell loop
}



// ///////////////////////////////////////////////////////////
// function: GetNumPoles()
//
// creation date:	19/04/01
// last modified:	19/04/01
// purpose: returns the number of poles computed by MedialAxis
//
// arguments: none

// return value: number of poles
// ///////////////////////////////////////////////////////////

int MedialAxisTransformer::GetNumPoles()
{
	return numPoles;
}



// ///////////////////////////////////////////////////////////
// function: DoMedialAxisTransform()
//
// creation date:	18/02/01
// last modified:	18/02/01
// purpose: find Voronoi vertices of Medial Axis 
//
// arguments: tetraList is the list of current tetrahedra
//
// return value: none
// ///////////////////////////////////////////////////////////

void MedialAxisTransformer::DoMedialAxisTransform(TetraList& tetraList)
{
	Vertex3 polePlus;
	Vertex3 poleMinus;

	numPoles = 0;
	


	for (int vertexId = 0; vertexId < Vertex3::GetGlobalVertexCount(); vertexId++)
	{
		poleMinus.SetVertex(0.0, 0.0, 0.0);
		polePlus.SetVertex(0.0, 0.0, 0.0);
		FindPolesFromDelaunayVertex(vertexId, poleMinus, polePlus);	
	}
}



// ///////////////////////////////////////////////////////////
// function: CloneToLargerVertexArray()
//
// creation date:	18/04/01
// last modified:	18/04/01
// purpose: resize vertex array by allocating a new larger array
//          and copy the contents of the old array to the new one
//
// arguments: the new additional size (how much should the array
// be expanded).
//
// return value: new vertex array
// ///////////////////////////////////////////////////////////

Vertex3* CrustExtractor::CloneToLargerVertexArray(unsigned int additionalSize)
{
	unsigned int oldSize = Vertex3::GetGlobalVertexCount();

	// allocate new vertex array
	unsigned int newSize = oldSize + additionalSize;
	Vertex3* newArray = new Vertex3[newSize+4]; // add four extra vertices of supertetra 
	if (!newArray)
	{
		return NULL;
	}

	// copy contents of old array into new array
	for (int i = 0; i < oldSize; i++)
	{
		Vertex3* oldVertex = Vertex3::GetVertex(i);

		//oldVertex->CopyTo(newArray[i]); // this function is not working
		newArray[i].x = oldVertex->x;
		newArray[i].y = oldVertex->y;
		newArray[i].z = oldVertex->z;

		newArray[i].normal.x = oldVertex->normal.x;
		newArray[i].normal.y = oldVertex->normal.y;
		newArray[i].normal.z = oldVertex->normal.z;

	}

	return newArray;
}



// ///////////////////////////////////////////////////////////
// function: IntegratePolesIntoVertexArray()
//
// creation date:	18/04/01
// last modified:	18/04/01
// purpose: add the poles to the global vertex array
//
// arguments: tetrahedron list where the poles are stored
//			  total number of poles to add to the global vertex array 
//
// return value: new vertex array
// ///////////////////////////////////////////////////////////

Vertex3* CrustExtractor::IntegratePolesIntoVertexArray(TetraList& tetraList, int totalNumPoles)
{
	int oldSize = Vertex3::GetGlobalVertexCount();
	int newSize;

	// resize the global vertex array
	Vertex3* newArray = CloneToLargerVertexArray(totalNumPoles);
	if (!newArray)
	{
		// not enough primary memory available
		return false;
	}
	newSize = oldSize + totalNumPoles;


	TetraList::Itr start = tetraList.Begin();
	TetraList::Itr end = tetraList.End();

	int newVertexId = oldSize;
        int count = 0;
	
	while (start != end)
	{
		Tetrahedron *tetra = *start++;
		
		// copy pole coordinates to a vertex in the new  
		// vertex array
		if (tetra->GetCentre()->IsPole())
		{
			Vertex3* currentVertex = &newArray[newVertexId];
			newVertexId++;
			count++;
			currentVertex->SetVertex(*(tetra->GetCentre()));
			currentVertex->pole = true;
		}
	}
	

	assert(totalNumPoles == count);
	assert(newVertexId <= newSize);

	return newArray;
}




// ///////////////////////////////////////////////////////////
// function: Build()
//
// creation date:	18/04/01
// last modified:	18/04/01
// purpose: extract the crust from the point set and its poles
//
// arguments: none
//
// return value: true successful allocation, false not successful
// ///////////////////////////////////////////////////////////

Vertex3* CrustExtractor::PerformCrustExtraction(TetraList& tetraList, int& destArraySize)
{

	int oldSize = Vertex3::GetGlobalVertexCount();

	assert(numPoles > 0 );

	// assume the Medial Axis has already been calculated
	Vertex3* destinationArray = IntegratePolesIntoVertexArray(tetraList, numPoles);
        if (!destinationArray)
	{
		// not enough memory
		return NULL;
	}

	destArraySize = oldSize + numPoles;
    
	return destinationArray;
}



// ///////////////////////////////////////////////////////////
// function: ExtractPolygonMesh()
//
// creation date:	23/04/01
// last modified:	23/04/01
// purpose: extract the polygon mesh from the union of vertices and poles
//
// arguments: the list of tetrahedra and the destination mesh object

// return value: none
// ///////////////////////////////////////////////////////////

void CrustExtractor::ExtractPolygonMesh(TetraList& tetraList, Skeleton* obj)
{

	TetraList::Itr start = tetraList.Begin();
	TetraList::Itr end = tetraList.End();
	

	/////////////////////////////////////////////////
	// find how many crust faces (triangles) there are and 
	// allocate a corresponding face array
	
	obj->faceCount = 0;
	obj->faceIndex = NULL;

	while (start != end)
	{
		Tetrahedron *tetra = *start++;
		
		for (int i = 0; i < 4; i++)
		{
			Face3 *face = tetra->F(i);
			
			// ignore faces with pole vertices and process 
			//  only faces with vertices from original samples
			// because they represent the reconstructed surface

			Vertex3* v0 = face->V(0);
			Vertex3* v1 = face->V(1);
			Vertex3* v2 = face->V(2);

			if (!v0->IsPole() && !v1->IsPole() && !v2->IsPole())
			{
				obj->faceCount++;
			}
		}
	}
	obj->faceIndex = new unsigned long [obj->faceCount*3];
	// note: vertexCount = faceCount*3
	/// //////////////////////////////////////////////////


	// now extract crust faces from Delaunay simplicial complex
	// and place crust faces into the new face array as indices
	start = tetraList.Begin();
	end = tetraList.End();
	int vertexCount = 0;

        while (start != end)
	{
		Tetrahedron *tetra = *start++;
		
		for (int i = 0; i < 4; i++)
		{
			Face3 *face = tetra->F(i);
			
			// ignore faces with pole vertices and process 
			//  only faces with vertices from original samples
			// because they represent the reconstructed surface

			Vertex3* v0 = face->V(0);
			Vertex3* v1 = face->V(1);
			Vertex3* v2 = face->V(2);

			if (!v0->IsPole() && !v1->IsPole() && !v2->IsPole())
			{
				obj->faceIndex[vertexCount+0] = face->I(0);
				obj->faceIndex[vertexCount+1] = face->I(1);
				obj->faceIndex[vertexCount+2] = face->I(2);

				vertexCount += 3;

				// calculate normal if not aleardy done so
				// use vertex index as source of information
				// and place result direclty into v->normal
				if (v0->normal.Magnitude() == 0.0)
				{
					FindAverageNormalFromAdjecentFaces(face->I(0), v0->normal);
				}
				if (v1->normal.Magnitude() == 0.0)
				{
					FindAverageNormalFromAdjecentFaces(face->I(1), v1->normal);
				}
				if (v2->normal.Magnitude() == 0.0)
				{
					FindAverageNormalFromAdjecentFaces(face->I(2), v2->normal);
				}
			}
		}
	}
	assert((vertexCount) == (obj->faceCount*3));
    tetraList.DeleteAll();
}

