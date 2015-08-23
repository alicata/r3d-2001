// /////////////////////////////////////////////////
// geomutil.cpp
//
// author:			Aaron Licata
// creation date:	02/09/00
// last modified:	05/03/01
//
// Implementaion file for all general geometrical utilities
//
// /////////////////////////////////////////////////////////

#include "config.h"
#include "ccenter.h"
#include "geom.h"		// Vertex3
#include "geomutil.h"	


// tollerated thickness of the surface of a circusphere
double machineTollerance = 0.000001;



// ////////////////////////////////////////////////////////////
// function: BoundBox3()
//
// creation date:	17/10/00
// last modified:	17/10/00
// purpose: constructor
//
// arguments: none
//
// return value: none
// ////////////////////////////////////////////////////////////

BoundBox3::BoundBox3()
{
	box[0].x =  box[0].y = box[0].z = 0.0;
	box[1].x =  box[1].y = box[1].z = 0.0;
	box[2].x =  box[2].y = box[2].z = 0.0;
	box[3].x =  box[3].y = box[3].z = 0.0;
	box[4].x =  box[4].y = box[4].z = 0.0;
	box[5].x =  box[5].y = box[5].z = 0.0;
	box[6].x =  box[6].y = box[6].z = 0.0;
	box[7].x =  box[7].y = box[7].z = 0.0;

}   



// ////////////////////////////////////////////////////////////
// function: BoundBox3()
//
// creation date:	17/10/00
// last modified:	17/10/00
// purpose: constructor
//
// arguments: min, max vertices
//
// return value: none
// ////////////////////////////////////////////////////////////

BoundBox3::BoundBox3(Vertex3& min, Vertex3& max)
{
	box[0].x = min.x; box[0].y = min.y; box[0].z = max.z;
	box[1].x = max.x; box[1].y = min.y; box[1].z = max.z;
	box[2].x = max.x; box[2].y = max.y; box[2].z = max.z;
	box[3].x = min.x; box[3].y = max.y; box[3].z = max.z;
	box[4].x = min.x; box[4].y = min.y; box[4].z = min.z;
	box[5].x = max.x; box[5].y = min.y; box[5].z = min.z;
	box[6].x = max.x; box[6].y = max.y; box[6].z = min.z;
	box[7].x = min.x; box[7].y = max.y; box[7].z = min.z;
}



// ////////////////////////////////////////////////////////////
// function: ~BoundBox3()
//
// creation date:	17/10/00
// last modified:	17/10/00
// purpose: destructor
//
// arguments: none
//
// return value: none
// ////////////////////////////////////////////////////////////

BoundBox3::~BoundBox3()
{
	
}




// ////////////////////////////////////////////////////////////
// function: SetBoundingBox()
//
// creation date:	17/10/00
// last modified:	17/10/00
// purpose: destructor
//
// arguments: min and max vertices
//
// return value: none
// ////////////////////////////////////////////////////////////

void BoundBox3::SetBoundingBox(Vertex3& min, Vertex3& max)
{
	box[0].x = min.x; box[0].y = min.y; box[0].z = max.z;
	box[1].x = max.x; box[1].y = min.y; box[1].z = max.z;
	box[2].x = max.x; box[2].y = max.y; box[2].z = max.z;
	box[3].x = min.x; box[3].y = max.y; box[3].z = max.z;
	box[4].x = min.x; box[4].y = min.y; box[4].z = min.z;
	box[5].x = max.x; box[5].y = min.y; box[5].z = min.z;
	box[6].x = max.x; box[6].y = max.y; box[6].z = min.z;
	box[7].x = min.x; box[7].y = max.y; box[7].z = min.z;
}



// ////////////////////////////////////////////////////////////
// function: Center()
//
// creation date:	19/10/00
// last modified:	19/10/00
// purpose: destructor
//
// arguments: vertex 
//
// return value: none
// ////////////////////////////////////////////////////////////

void BoundBox3::Center(Vertex3 &center)
{
	center.x = MinX() + (MaxX() - MinX())/2;
	center.y = MinX() + (MaxY() - MinY())/2;
	center.z = MinX() + (MaxZ() - MinZ())/2;
}



// ////////////////////////////////////////////////////////////
// function: CenterAtOrigin()
//
// creation date:	19/10/00
// last modified:	19/10/00
// purpose: move center of box to the origin
//
// arguments: none
//
// return value: none
// ////////////////////////////////////////////////////////////

void BoundBox3::CenterAtOrigin()
{
	// TODO
	double xOffset = (MaxX() - MinX())/2;
	double yOffset = (MaxY() - MinY())/2;
	double zOffset = (MaxZ() - MinZ())/2;

	// first
	box[0].x = -xOffset;
	box[0].y = +yOffset;
	box[0].z = -zOffset;
	
	// second
	box[1].x = +xOffset;
	box[1].y = +yOffset;
	box[1].z = -zOffset;

	// MAX
	box[MAXVERTEX].x = +xOffset;
	box[MAXVERTEX].y = +yOffset;
	box[MAXVERTEX].z = +zOffset;

	// 3
	box[3].x = -xOffset;
	box[3].y = +yOffset;
	box[3].z = +zOffset;

	// MIN
	box[MINVERTEX].x = -xOffset;
	box[MINVERTEX].y = -yOffset;
	box[MINVERTEX].z = -zOffset;

	//
	box[5].x = -xOffset;
	box[5].y = -yOffset;
	box[5].z = +zOffset;

	//
	box[6].x = +xOffset;
	box[6].y = -yOffset;
	box[6].z = -zOffset;

	box[7].x = +xOffset;
	box[7].y = -yOffset;
	box[7].z = +zOffset;


}



// ////////////////////////////////////////////////////////////////////////
// general and global functions
//



// ////////////////////////////////////////////////////////////
// function: MaxBox3()
//
// creation date:	19/10/00
// last modified:	19/10/00
// purpose: set max bounding box of a point cloud
//
// arguments: vertex list and number of vertices
//
// return value: none
// ////////////////////////////////////////////////////////////

void MaxBox3(BoundBox3& box, Vertex3* v, int numVerts)
{
	int i;
	Vertex3 min, max;

	max.x = min.x = v[0].x;
	max.y = min.y = v[0].y;
	max.z = min.z = v[0].z;
	for (i = 0; i < numVerts; i++)
	{
		if (v[i].x > max.x) { max.x = v[i].x; }
		if (v[i].x < min.x) { min.x = v[i].x; }
		if (v[i].y > max.y) { max.y = v[i].y; }
		if (v[i].y < min.y) { min.y = v[i].y; }
		if (v[i].z > max.z) { max.z = v[i].z; }
		if (v[i].z < min.z) { min.z = v[i].z; }
	}
	box.SetBoundingBox(min, max);
}


// ///////////////////////////////////////////////////////////
// function: TetrahedronCircumCenter()
//
// creation date:	05/11/00
// last modified:	05/11/00
// purpose: find circumcenter of a tetrahedron
//
// arguments: vertices
//
// return value: none
// ///////////////////////////////////////////////////////////

void TetrahedronCircumCenter(const Vertex3& p0, const Vertex3& p1, const Vertex3& p2, const Vertex3& p3, Vertex3& center)
{
	double a[3];
	double b[3];
	double c[3];
	double d[3];

	a[0] = p0.x; a[1] = p0.y; a[2] = p0.z;
	b[0] = p1.x; b[1] = p1.y; b[2] = p1.z;
	c[0] = p2.x; c[1] = p2.y; c[2] = p2.z;
	d[0] = p3.x; d[1] = p3.y; d[2] = p3.z;

	double* xi = NULL;
	double cc[3];

	TetraCircumCenter(a, b, c, d, cc, xi, xi, xi);

	center.x = cc[0] + a[0];
	center.y = cc[1] + a[1];
	center.z = cc[2] + a[2];
}

// ///////////////////////////////////////////////////////////
// function: IsFaceClockWise()
//
// creation date:	05/03/01
// last modified:	05/03/01
// purpose: establish whether a face in 3-d is clockwise or 
//          counterclockwise (see predicates.c for details)
//
// arguments: face is a pointer to a known face (triangle)
//            normal is a normal to the face 
//
// return value: boolean true if cw, false if ccw
// ///////////////////////////////////////////////////////////

bool IsFaceClockWise(Face3 *face, Vector3 *normal)
{
	double pa[3]; // face vertex a (1) 
	double pb[3]; // face vertex b (2)
	double pc[3]; // face vertex c (3)
	double pd[3]; // point d is either above or below face

	  assert(normal);

      // convert application native vertex and vector format
	  // into format used by Shewchuck's routines in predicates.c

	  // vertex 0
	  pa[0] = face->V(0)->x;
	  pa[1] = face->V(0)->y;
	  pa[2] = face->V(0)->z;

	  // vertex 1
	  pb[0] = face->V(1)->x;
	  pb[1] = face->V(1)->y;
	  pb[2] = face->V(1)->z;
 
	  // vertex 2
	  pc[0] = face->V(2)->x;
	  pc[1] = face->V(2)->y;
	  pc[2] = face->V(2)->z;

	  // point d 
	  pd[0] = pa[0] + normal->x;
	  pd[0] = pa[1] + normal->y;
	  pd[0] = pa[2] + normal->z;

   
    // check if point d lies below or above the face
    if (orient3dfast(pa, pb, pc, pd) < 0)
        return true; // d lies below, clockwise 
     else
        return false; // d lies above, counterclockwise

  return false;
}


// ///////////////////////////////////////////////////////////
// function: RandomizePointSet()
//
// creation date:	27/03/01
// last modified:	27/03/01
// purpose: add random displacement to each vertex 
//          of the vertex array
//
// arguments: the vertex array to randomize
//           
// return value: none 
// ///////////////////////////////////////////////////////////

void RandomizePointSet(Vertex3* vertexArray, int percentage, double max)
{

	max = max / 10.0;
	for (int vertexId = 0; vertexId < Vertex3::GetGlobalVertexCount(); vertexId++)
	{
		Vertex3* v = Vertex3::GetVertex(vertexId);
		v->x += ((double)(rand()%percentage)/2000.0)*v->x;
		v->y += ((double)(rand()%percentage)/2000.0)*v->y;
		v->z += ((double)(rand()%percentage)/2000.0)*v->z;
	}
}



// ///////////////////////////////////////////////////////////
// function: IsFaceOnConvexHull()
//
// creation date:	13/02/01
// last modified:	13/02/01
// purpose: tell if a face belongs to the 3-d convex-hull
// of the Delaunay tetrahedralization
//
// arguments: face that might belong to the convex-hull
// ///////////////////////////////////////////////////////////
bool IsFaceOnConvexHull(Face3 *f)
{
	return (f->neigh == NO_LINK);
}



// ///////////////////////////////////////////////////////////
// function: IsVertexOnConvexHull()
//
// creation date:	18/02/01
// last modified:	18/02/01
// purpose: tell if a vertex belongs to the 3-d convex-hull
// of the Delaunay tetrahedralization
//
// arguments: vertex id that might belong to the convex-hull
// ///////////////////////////////////////////////////////////
bool IsVertexOnConvexHull(int vertexId)
{
	Vertex3 *v = Vertex3::GetVertex(vertexId);
	return (v->flag == GEOM_ON_CONVEX_HULL);
}



// ///////////////////////////////////////////////////////////
// function: CalculateMachineTollerance()
//
// creation date:	10/12/00
// last modified:	18/02/01
//
// purpose: find the smallest positive real number representable 
// by the machine running this code
//
// arguments: none
// ///////////////////////////////////////////////////////////

double CalculateMachineTollerance()
{
	double num1 = 0.0;
	double num2 = 0.1;
	double tollerance;

	while (fabs(num1 - num2) > 0)
	{
		tollerance = num2;
		num2 /= 2;
	}
	return machineTollerance = tollerance;
}




// ///////////////////////////////////////////////////////////
// function:GetMachineTollerance()
//
// creation date:	10/12/00
// last modified:	18/02/01
//
// purpose: return  smallest positive real number representable 
// by the machine running this code
//
// arguments: none
// ///////////////////////////////////////////////////////////

double GetMachineTollerance()
{
	return machineTollerance;
}



// ///////////////////////////////////////////////////////////
// function:FlipVertexNormals()
//
// creation date:	26/12/00
// last modified:	26/02/01
//
// purpose: flip the direction of the vertex normals of vertex array   
//
// arguments: vertex array and its size
// ///////////////////////////////////////////////////////////

void FlipVertexNormals(Vertex3* vertexArray, int vertexCount)
{
	for (int i = 0 ; i < vertexCount ; i++)
	{
		Vertex3* vertex = Vertex3::GetVertex(i);

		vertex->normal.x = -vertex->normal.x;
		vertex->normal.y = -vertex->normal.y;
		vertex->normal.z = -vertex->normal.z;

	}
}



// ///////////////////////////////////////////////////////////
// function: FindAverageNormalFromAdjecentFaces()
//
// creation date:	14/02/01
// last modified:	17/02/01
// purpose: calculate the average normal vector to the surface 
// around the neighbouring faces (triangles) 
//
// arguments: sampleId is an index to the vertex list
//            normal is a reference to the normal to be computed 
//
// return value: none
// ///////////////////////////////////////////////////////////
void FindAverageNormalFromAdjecentFaces(int sampleId, Vector3& averageFaceNormal)
{
 	// grab a pointer to the Delaunay vertex
	Vertex3 *sampleVertex = Vertex3::GetVertex(sampleId);

	// iterators to neighbouring tetrahedra
	TetraList::Itr startItr = sampleVertex->neigh->Begin();
	TetraList::Itr endItr = sampleVertex->neigh->End();

	if (startItr == endItr)
	{
     // this Delaunay vertex has not neighbouring Voronoi vertices
		return;
	}

	// loop through neighbouring Tetrahedra
	// and isolate the surface faces
	list<Face3*> temp;
	for (; startItr != endItr; startItr++)
	{
		Tetrahedron *tetra = *startItr;
		temp.push_back(tetra->F(0));
		temp.push_back(tetra->F(1));
		temp.push_back(tetra->F(2));
		temp.push_back(tetra->F(3));
	}
	// find faces contributing to the average normal to the sample vertex
	RetainSampleVertexSharedFaces(sampleVertex, temp);
	
	// calculate avarage out of each face's normal vector
	int numTotalVectors = (int)temp.size();
	averageFaceNormal.Set(0.0, 0.0, 0.0);
	for (int i = 0; i < numTotalVectors; i++)
	{
		// make a normal vector out of each face
		Face3 *face = temp.back();
		temp.pop_back();

		// note: face normal are calculated during face creation
		// also, faces are assumed to be already clockwise (see LinkVerticesToNeighTetrahedra())
		Vector3 tempNormal = face->Normal(); 

		// add this normal vector to the total average
		averageFaceNormal.x += tempNormal.x;
		averageFaceNormal.y += tempNormal.y;
		averageFaceNormal.z += tempNormal.z;
	}
	averageFaceNormal.x /= -numTotalVectors;
	averageFaceNormal.y /= -numTotalVectors;
	averageFaceNormal.z /= -numTotalVectors;
}

// ////////////////////////////////////////////////////////////
// function: RetainSampleVertexSharedFaces()
//
// creation date:	17/02/01
// last modified:	17/02/01
// purpose: filter out from teporary list those external faces 
// that do not share the sample vertex 
//
// arguments: sampleVertex is the Delaunay vertex
//            temp is a list of Face3 pointers
//
// return value: none
// ////////////////////////////////////////////////////////////
void RetainSampleVertexSharedFaces(Vertex3* sampleVertex, list<Face3*>& temp)
{
	list<Face3*>::iterator startItr = temp.begin();
	list<Face3*>::iterator endItr   = temp.end();
	list<Face3*>::iterator disposibleItr;

	while ( startItr != endItr)
	{
		Face3 *face = *startItr;
		assert(face != NO_LINK);
		if (!IsFaceOnConvexHull(face))
		{
			disposibleItr = startItr++;
			temp.erase(disposibleItr);
		}
		else
		{
			startItr++;
		}
	}
}
