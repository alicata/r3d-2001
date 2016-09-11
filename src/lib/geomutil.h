// /////////////////////////////////////////////////
// geomutil.h
//
// author:			Aaron Licata
// creation date:	02/09/00
// last modified:	02/09/00
//
// Header file for all general geometrical utilities
//

#ifndef GEOMUTIL_H
#define GEOMUTIL_H

#include "predicates.h"
#include "math.h"
#include "geom.h"

int const MINVERTEX = 4;
int const MAXVERTEX = 2;


// //////////////////////////////////////////////////////////
// file name:BoundBox3
//
// author:			Aaron Licata
// creation date:	14/02/01
// last modified:	21/04/01
// version number:	2
//
// description: class that implements the bounding box
//
// //////////////////////////////////////////////////////////

class BoundBox3
{
public:
   
    BoundBox3() ;                    //  default constructor
    BoundBox3(Vertex3& inMin, Vertex3& inMax); //  conversion constructor

    ~BoundBox3() ;                   //  destructor

	void SetBoundingBox(Vertex3& min, Vertex3& max);
	void CenterAtOrigin();
	void Center(Vertex3 &center);
	double MaxX() { return box[MAXVERTEX].x; }
	double MaxY() { return box[MAXVERTEX].y; }
	double MaxZ() { return box[MAXVERTEX].z; }
	double MinX() { return box[MINVERTEX].x; }
	double MinY() { return box[MINVERTEX].y; }
	double MinZ() { return box[MINVERTEX].z; }


private:
    Vertex3 box[8];
} ;


void MaxBox3(BoundBox3& bbox, Vertex3* v, int numVerts);
void TetrahedronCircumCenter(const Vertex3& v0, const Vertex3& v1, const Vertex3& v2, const Vertex3& v3, Vertex3& center);

bool IsFaceClockWise(Face3* face, Vector3* normal);
bool IsFaceOnConvexHull(Face3 *f);
bool IsVertexOnConvexHull(int sampleId);

void FlipVertexNormals(Vertex3* vertexArray, int vertexCount);
void FindAverageNormalFromAdjecentFaces(int sampleId, Vector3& normal);
void RetainSampleVertexSharedFaces(Vertex3* sampleVertex, list<Face3*>& temp);


void RandomizePointSet(Vertex3* vertexArray, int percentage, double max); 


// machine precision related functions 
double CalculateMachineTollerance();
double GetMachineTollerance();


// Shewchuck's incircle and orient3d routines
// this routines are from a C-API library
#ifdef __cplusplus
extern "C" {
#endif
	double orient3dfast(double *pa, double *pb, double *pc, double *pd);
#ifdef __cplusplus
}
#endif


#endif
