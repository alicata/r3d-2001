// ///////////////////////////////////////////////////////////
// delaunay.cpp
//
// author:			Aaron Licata
// creation date:	30/08/00
// last modified:	30/12/00
//
// Implementation file for watson algorihm and its subroutines
//
// ///////////////////////////////////////////////////////////

#include "config.h"
#include <math.h>		// abs
#include "math.h"		// MACHINE_TOLLERANCE
#include "geom.h"		// Tetrahedron, Face3, Edge3
#include "geomutil.h"	// BoundBox3, MaxBox3
#include "apperr.h"		// AppError
#include "appio.h"		// AppOut, AppEndl
#include "delaunay.h"	// list<T>
#include <algorithm>	// count
#include <vector>		// vector<T>
#include "STL.h"		// enable native STL version 
#include <iostream>



// ///////////////////////////////////////////////////////////
// function: CreateSuperTetrahedron
//
// purpose: allocate and setup the super tetrahedron enclosing
// all data points.
//
// arguments: Tetrahedron* & super
//
// ///////////////////////////////////////////////////////////

Tetrahedron * DelaunayTetrahedralizer::CreateSuperTetrahedron(Vertex3* vert, int numVerts)
{
	BoundBox3 boundBox;
	MaxBox3(boundBox, vert, numVerts);

	boundBox.CenterAtOrigin();

	double h = boundBox.MaxX() + boundBox.MaxY() + boundBox.MaxZ();
	double densityRatio = boundBox.MaxX() * boundBox.MaxY() * boundBox.MaxZ();


	machineTollerance = CalculateMachineTollerance();

	if (fabs(h) < machineTollerance)
		AppError(APPERR_INSUFFICIENT_SAMPLE_DENSITY);
	else if (fabs(densityRatio) < MACHINE_TOLLERANCE)
	{
		AppOut("density ratio is");
		AppOut(fabs(densityRatio)) ;
		AppEndl();
		AppError(APPERR_2D_OR_1D_SAMPLES);
	}
	
	// ////////////// super tetrahedron /////////////////////////
	// possible improvement: calculate best scaling factor
	// the current implementation just overwrite scaling factor
	h = (double)superTetra.GetSuperFactor();
	// calculate coordinates of supertetra vertices	
	Vertex3 vApex    (    0.0,  4*h,  0.0);
	Vertex3 vBaseLeft( -4*h, -4*h, +4*h);
	Vertex3 vBaseRight(+4*h, -4*h, +4*h);
	Vertex3 vBaseBack(    0, -4*h, -4*h);
	superTetra.Set(vApex, vBaseLeft, vBaseRight, vBaseBack);
	// ////////////////////////////////////////////////////////////

	// indices to vertices added to vertex list
	int apex  = 0 + numVerts;
	int left  = 1 + numVerts;
	int right = 2 + numVerts;
	int back  = 3 + numVerts;

	// update vertex list
	
	COPYVERTS(  vert[apex] , vApex  );
	COPYVERTS(	vert[left] , vBaseLeft  );
	COPYVERTS(	vert[right] , vBaseRight  );
	COPYVERTS(	vert[back] , vBaseBack  );
	numVerts += 4;
	Vertex3::SetGlobalVertexCount(numVerts);

	Face3 f0(left, right, back);
	Face3 f1(left, apex, back);
	Face3 f2(right, back, apex);
	Face3 f3(left, right, apex);

	// initialize to a tetra with no neighbours
	f0.neigh = NO_LINK;
	f1.neigh = NO_LINK;
	f2.neigh = NO_LINK;
	f3.neigh = NO_LINK;

	Tetrahedron *tetra = new Tetrahedron(f0, f1, f2, f3);
	if (!tetra) AppError(APPERR_TETRA_ALLOC);
	tetra->SetLocalVertexList(vert);
	
	return tetra;
}

// ///////////////////////////////////////////////////////////
// function: RetainSinglyOccurringFaces()
//
// creation date:	09/09/00
// last modified:	11/02/00
// purpose: filter out any double face in the list
//
// note: a double face, is a face that is present twice in the list
//
// arguments: tetralist is the list of all existing tetrahedra
// ///////////////////////////////////////////////////////////

void DelaunayTetrahedralizer::RetainSinglyOccurringFaces(list<Face3*> &faces)
{
	 // NOTE: the face list must contain at least two
	 // faces

	 list<Face3*> singles;
     list<Face3*>::iterator startIter;
     list<Face3*>::iterator endIter;
	 
	 //AppOut("RetainSinglyOcc entered\n");
	 bool doubleFound = false;

	 while (faces.size() > 0)
	 {
		 startIter = faces.begin();
		 endIter = faces.end();

		 //AppOut("SinglyOccurring: Detecting a double occurrance...\n");
		 doubleFound = false;
		 list<Face3*>::iterator currentIter = startIter;
		 currentIter++;
		 for (; currentIter != endIter; currentIter++)
		 {
			//number = count(start, end, *start);
			Face3 *curFace = *currentIter;
			Face3 *startFace = *startIter;
			if (*curFace == *startFace)
			{
				doubleFound = true;
				break;
			}
		 }
	 
		 // found double faces
		 // in this case erease the two faces pointers 
		 // from the temporary list.
		 // also, the actual objects pointed to must
		 // be deleted
		 if (doubleFound)
		 {
		 //AppOut("SinglyOccurring: Removing double faces...\n");
			// get rid of face objects first
			delete *startIter;
			delete *currentIter;
			// now erase face pointers in the temprary list
			faces.erase(startIter);
			faces.erase(currentIter);
			
			// iterators are now invalid
			// they need to be assigned again
		 }
		 // current face is single
		 else
		 {
			 singles.push_back(*startIter);
			 faces.pop_front();
		 }
	 }
		
	 faces = singles;

	//AppOut(" temp list size: "); 
	//AppOut((int)faces.size());
	//AppEndl();
}



// ///////////////////////////////////////////////////////////
// function: CreateTetrahedronFrom4FacesAndPoint()
//
// creation date:	09/09/00
// last modified:	11/02/00
// purpose: create a new tetrahedron using four faces
//
// arguments: list of four faces
//            tetralist is the list of all existing tetrahedra
// ///////////////////////////////////////////////////////////

void DelaunayTetrahedralizer::CreateTetrahedronFrom4FacesAndPoint(list<Face3*> &faces, int pointIndex, TetraList& tetras)
{
	while (!faces.empty())
	{
		// create a new tetrahedron out of the single faces.
		// memory management note: each of the faces referenced
		// in the temporary list of faces is kept as it is
		// and other three faces are actually allocated.
		// So, in the end, each tetrahedron has one link to a face 
		// that already existed (allocated) and three links to 
		// newly allocated faces.
		Face3 *f0 = faces.back();
		faces.pop_back();
		Face3 *f1 = new Face3(f0->I(0), f0->I(1), pointIndex);
		Face3 *f2 = new Face3(f0->I(1), f0->I(2), pointIndex);
		Face3 *f3 = new Face3(f0->I(2), f0->I(0), pointIndex);
		tetras.Add(new Tetrahedron(f0, f1, f2, f3));
	}
	//AppOut("aftger tetra creat ");
	//AppOutN((int)faces.size());

	//cout << "after tetra creatoin: " << faces.size() << endl; 
}



// ///////////////////////////////////////////////////////////
// function: RewireNeighbouringTetrahedron()
//
// creation date:	09/11/00
// last modified:	11/12/00
// purpose: link neighbouring tetrahedron
//
// arguments: tetrahedron and face
//          
// ///////////////////////////////////////////////////////////

void DelaunayTetrahedralizer::RewireNeighbouringTetrahedron(Tetrahedron *tetra, Face3* externalFace)
{
	Tetrahedron* neighTetra = externalFace->neigh;

	// find which face is shared by the tetra and its neigbhour
	// then link the neighbouring tetrahedron to this neighbour
#ifdef _DEBUG_STRICT
	assert(neighTetra);
#endif

	//AppOut("start loop");
	//AppEndl();
	for (int i = 0; i < 4; i++)
	{
		//AppOut("for count "); 
		//AppOut(i);
		//AppEndl();
		if (neighTetra != NO_LINK)
		{
			//AppOutN("neighTetra != NO_LINK");
			Face3 *neighFace = neighTetra->F(i);
			//AppOutN("Face3 *neighFace = neighTetra->F(i)");
			assert(neighFace);
			if (*neighFace == *externalFace)
			{
				//AppOutN("if (*neighFace == *externalFace)");
				neighFace->neigh = tetra; 
				return;
			}
		}
	}
#ifdef _DEBUG_STRICT
	int NO_TETRA_FACES_FOUND = 0;
	assert(NO_TETRA_FACES_FOUND);
#endif
	
}



// ///////////////////////////////////////////////////////////
// function: WireTetrahedron()
//
// creation date:	09/12/00
// last modified:	11/12/00
// purpose: link tetrahedron to face neighbours
//
// arguments: tetraList iterators
//            
// ///////////////////////////////////////////////////////////

void DelaunayTetrahedralizer::WireTetrahedron(TetraList::RevItr startTetraItr, TetraList::RevItr stopTetraItr, TetraList::RevItr newTetraItr)
{
	Face3 *f1 = (*newTetraItr)->F(1);
	Face3 *f2 = (*newTetraItr)->F(2);
	Face3 *f3 = (*newTetraItr)->F(3);

	int numProcessedFaces = 0;
	while (startTetraItr != stopTetraItr)
	{
		Face3 *nf1 = (*startTetraItr)->F(1);
		Face3 *nf2 = (*startTetraItr)->F(2);
		Face3 *nf3 = (*startTetraItr)->F(3);

		numProcessedFaces++;
		// if this face is same as one of those in
		// an internal tetrahedron
		// face1
		if (*f1 == *nf1)
		{
			nf1->neigh = *newTetraItr;
			f1->neigh = *startTetraItr;
		}
		else if (*f1 == *nf2)
		{
			nf2->neigh = *newTetraItr;
			f1->neigh = *startTetraItr;
		}
		else if (*f1 == *nf3)
		{
			nf3->neigh = *newTetraItr;
			f1->neigh = *startTetraItr;
		}
		// face 2
		if (*f2 == *nf1)
		{
			nf1->neigh = *newTetraItr;
			f2->neigh = *startTetraItr;
		}
		else if (*f2 == *nf2)
		{
			nf2->neigh = *newTetraItr;
			f2->neigh = *startTetraItr;
		}
		else if (*f2 == *nf3)
		{
			nf3->neigh = *newTetraItr;
			f2->neigh = *startTetraItr;
		}
		// face 3
		if (*f3 == *nf1)
		{
			nf1->neigh = *newTetraItr;
			f3->neigh = *startTetraItr;
		}
		else if (*f3 == *nf2)
		{
			nf2->neigh = *newTetraItr;
			f3->neigh = *startTetraItr;
		}
		else if (*f3 == *nf3)
		{
			nf3->neigh = *newTetraItr;
			f3->neigh = *startTetraItr;
		}
#ifdef _DEBUG_STRICT
		else
		{
			int NOT_ABLE_TO_LINK_FACES_AND_TETRA = 0;
			assert(NOT_ABLE_TO_LINK_FACES_AND_TETRA);
		}
#endif

		startTetraItr--;
	}
	// end of while loop
#ifdef _DEBUG_STRICT1
	assert((numProcessedFaces % 3) == 0);
#endif

#ifdef _DEBUG_APPOUT
	AppOut("numProcessedFaces = ");
	AppOut(numProcessedFaces);
	AppEndl();
#endif
}

// ///////////////////////////////////////////////////////////
// function: WireTetrahedron2()
//
// purpose: wire internal faces to thier neighbouring tetrahedra
//
void DelaunayTetrahedralizer::WireTetrahedron2(TetraList::Itr& startTetraItr, TetraList::Itr& stopTetraItr, TetraList::Itr& newTetraItr)
{
	Face3 *f1 = (*newTetraItr)->F(1);
	Face3 *f2 = (*newTetraItr)->F(2);
	Face3 *f3 = (*newTetraItr)->F(3);

	int numProcessedFaces = 0;
	while (startTetraItr != stopTetraItr)
	{
		Face3 *nf1 = (*startTetraItr)->F(1);
		Face3 *nf2 = (*startTetraItr)->F(2);
		Face3 *nf3 = (*startTetraItr)->F(3);

		numProcessedFaces++;

		// avoid checking against the same tetrahedron'faces
		if (*newTetraItr == *startTetraItr)
		{
			//startTetraItr++;
			//continue;
		}

		// if this face is same as one of those in
		// an internal tetrahedron
		// face1
		if (*f1 == *nf1)
		{
			nf1->neigh = *newTetraItr;
			f1->neigh = *startTetraItr;
		}
		else if (*f1 == *nf2)
		{
			nf2->neigh = *newTetraItr;
			f1->neigh = *startTetraItr;
		}
		else if (*f1 == *nf3)
		{
			nf3->neigh = *newTetraItr;
			f1->neigh = *startTetraItr;
		}
		/*
#ifdef _DEBUG_STRICT
		else
		{
			int NOT_ABLE_TO_LINK_FACE1_AND_TETRA = 0;
			assert(NOT_ABLE_TO_LINK_FACE1_AND_TETRA);
		}
#endif
		*/

		// face 2
		if (*f2 == *nf1)
		{
			nf1->neigh = *newTetraItr;
			f2->neigh = *startTetraItr;
		}
		else if (*f2 == *nf2)
		{
			nf2->neigh = *newTetraItr;
			f2->neigh = *startTetraItr;
		}
		else if (*f2 == *nf3)
		{
			nf3->neigh = *newTetraItr;
			f2->neigh = *startTetraItr;
		}
		/*
#ifdef _DEBUG_STRICT
		else
		{
			int NOT_ABLE_TO_LINK_FACE2_AND_TETRA = 0;
			assert(NOT_ABLE_TO_LINK_FACE2_AND_TETRA);
		}
#endif
		*/

		// face 3
		if (*f3 == *nf1)
		{
			nf1->neigh = *newTetraItr;
			f3->neigh = *startTetraItr;
		}
		else if (*f3 == *nf2)
		{
			nf2->neigh = *newTetraItr;
			f3->neigh = *startTetraItr;
		}
		else if (*f3 == *nf3)
		{
			nf3->neigh = *newTetraItr;
			f3->neigh = *startTetraItr;
		}
#ifdef _DEBUG_STRICT
		else
		{
			int NOT_ABLE_TO_LINK_FACEs123_AND_TETRA = 0;
			assert(NOT_ABLE_TO_LINK_FACEs123_AND_TETRA);
		}
#endif

		startTetraItr++;
	}
	// end of while loop

#ifdef _DEBUG_STRICT1
	assert((numProcessedFaces % 3) == 0);
#endif

#ifdef _DEBUG_APPOUT
	AppOut("numProcessedFaces = ");
	AppOut(numProcessedFaces);
	AppEndl();
#endif
}



// ////////////////////////////////////////////////////////////////////////
// CreatedAndWireTetrahedraFromSOF
// purpuse: create one new tetrahedron for each singly-occurring face (SOF) 
// in the filtered out temporary list of faces
//
// note: it is assumed that during the creation of the supertetrahdron its 
// faces have been intilialized to NO_LINK
// 
// /////////////////////////////////////////////////////////////////////////

void DelaunayTetrahedralizer::CreatedAndWireTetrahedraFromSOF(list<Face3*> &faces, int pointIndex, TetraList& tetras)
{
#ifdef _DEBUG_STRICT
	int oldSize = (int)faces.size();
	assert( oldSize > 0);
#endif
	// current number of tetrahedra and nunber of new tetrahedra 
	int oldListSize = tetras.Size();
	int newTetraCount = 0;

	// PASS1:
	while (!faces.empty())
	{
		// create a new tetrahedron out of each of single faces.
		// memory management note: each of the faces referenced
		// in the temporary list of faces is kept as it is
		// and other three faces are actually allocated.
		// So, in the end, each tetrahedron has one link to a face 
		// that already existed (allocated) and three links to 
		// newly allocated faces.

		// +---------------+ +---------+
		// |               |-|f0  1 2 3|-> tetra T1 	(external face)
		// +               | +---------+
		// |               |-|f1  1 2 4|-> tetra T2	(internal face)
		// +  tetarhedron  | +---------+
		// |               |-|f2  1 3 4|-> tetra T3	(internal face)
		// +               | +---------+
		// |               |-|f3  2 3 4|-> tetra T4 	(internal face)
		// +---------------+ +---------+ 
	
		Face3 *f0 = faces.back();
		faces.pop_back();
		Face3 *f1 = new Face3(f0->I(0), f0->I(1), pointIndex);
		Face3 *f2 = new Face3(f0->I(1), f0->I(2), pointIndex);
		Face3 *f3 = new Face3(f0->I(0), f0->I(2), pointIndex);
		Tetrahedron *tetra = new Tetrahedron(f0, f1, f2, f3);
		tetras.Add(tetra);
		//AppOutN(newTetraCount);
		newTetraCount++;

		// external (boundary) face has a neighbouring tetrahedron
		// rewire neighbouring tetrahdron
		if (f0->neigh)
		{
			//AppOut("RewireNeighbouringTetrahedron(tetra, f0)");
			//AppEndl();
			assert(tetra);
			assert(f0);
			RewireNeighbouringTetrahedron(tetra, f0);
		}
	}

	// PASS2:
	// wire internal faces of new tetrahedra
	//TetraList::Itr lastOldItr = tetras.Begin();
	//lastOldItr = lastOldItr + (unsigned int)listSize;
	TetraList::RevItr stopTetraItr = tetras.Rend();
	TetraList::RevItr startTetraItr = tetras.Rbegin();
#ifdef _DEBUG_STRICT
	//assert( ((tetras.Last()-lastOldItr)/sizeof(TetraList::Itr)) == oldSize);
#endif
	
#ifdef _DEBUG_APPOUT1
		AppOut("********size of tetra list: ");
		AppOut(tetras.Size());
		AppEndl();
		AppOut("newTetraCount = ");
		AppOut(newTetraCount);
		AppEndl();
#endif

	int numLoops = 0;
	for (TetraList::RevItr newTetraItr = startTetraItr; (newTetraItr != stopTetraItr)&&(newTetraCount-- > 0); newTetraItr++)
	{
		WireTetrahedron(startTetraItr, stopTetraItr, newTetraItr);
#ifdef _DEBUG_APPOUT1
		numLoops++;
#endif
	}

#ifdef _DEBUG_APPOUT1
		//static int numLoops = 0;
	    AppOut("number of loops: ");
		AppOut(numLoops);
		AppEndl();
#endif 
	
	 
			

	//AppOut("aftger tetra creat ");
	//AppOutN((int)faces.size());

	//cout << "after tetra creatoin: " << faces.size() << endl; 
}



// ////////////////////////////////////////////////////////////////////////
// CreatedAndWireTetrahedraFromSOF
// purpuse: create one new tetrahedron for each singly-occurring face (SOF) 
// in the filtered out temporary list of faces
//
// note: it is assumed that during the creation of the supertetrahdron its 
// faces have been intilialized to NO_LINK
//
// ////////////////////////////////////////////////////////////////////////

void DelaunayTetrahedralizer::CreatedAndWireTetrahedraFromSOF2(list<Face3*> &faces, int pointIndex, TetraList& tetras)
{
#ifdef _DEBUG_STRICT
	int oldSize = (int)faces.size();
	assert( oldSize > 0);
#endif
	// current number of tetrahedra and nunber of new tetrahedra 
	int newTetraCount = 0;
	int oldListSize = tetras.Size();
	// the id of the first of thew new tetrahedra
	int lowestNewId = 0;

#ifdef _DEBUG_STRICT
	// if tetraList is empty (just created supertetrahedron)
	// then first tetra iterator will be == tetras.End()
	assert( oldListSize >= 0);
#endif


	// find the last tetrahedron of the tetralist
	// this is going to be the starting marker for
	// the new sublist of new tetrahedra appended to tetralist
	/*
	TetraList::Itr firstNewTetraItr = tetras.Begin();
	TetraList::Itr oneBeforeItr = firstNewTetraItr;
	TetraList::Itr end = tetras.End();
	    
		AppOut("last tetrahedron tetra id: ");
		Tetrahedron* temp = *firstNewTetraItr;
		if (oldListSize>0)
		if (temp)
		{
			AppOut("new tetra id: ");
			AppOutN(temp->GetID());
		}
		else
		{
			AppOutN("first new tetra is NULL");
		}


		
	while (firstNewTetraItr != end) 
	{
		oneBeforeItr = firstNewTetraItr;
		firstNewTetraItr++;
	}
	firstNewTetraItr = oneBeforeItr;
		*/

	// PASS1:
	while (!faces.empty())
	{
		// create a new tetrahedron out of each of single faces.
		// memory management note: each of the faces referenced
		// in the temporary list of faces is kept as it is
		// and other three faces are actually allocated.
		// So, in the end, each tetrahedron has one link to a face 
		// that already existed (allocated) and three links to 
		// newly allocated faces.

		// +---------------+ +---------+
		// |               |-|f0  1 2 3|-> tetra T1 	(external face)
		// +               | +---------+
		// |               |-|f1  1 2 4|-> tetra T2	(internal face)
		// +  tetarhedron  | +---------+
		// |               |-|f2  1 3 4|-> tetra T3	(internal face)
		// +               | +---------+
		// |               |-|f3  2 3 4|-> tetra T4 (internal face)
		// +---------------+ +---------+ 
	
		Face3 *f0 = faces.back();
		faces.pop_back();
		Face3 *f1 = new Face3(f0->I(0), f0->I(1), pointIndex);
		Face3 *f2 = new Face3(f0->I(1), f0->I(2), pointIndex);
		Face3 *f3 = new Face3(f0->I(0), f0->I(2), pointIndex);
		Tetrahedron *tetra = new Tetrahedron(f0, f1, f2, f3);
		tetras.Add(tetra);
		//AppOutN(newTetraCount);
		// save the id of the first newly created tetrahedron
	    if (newTetraCount == 0)
		{
			lowestNewId = tetra->GetID();
		}
		newTetraCount++;

		// +---------------+ +---------+
		// |               |-|f0  1 2 3|-> tetra T1 	(external face)
		// +               | +---------+
		// |               |-|f1  1 2 4|-> ?
		// +  tetarhedron  | +---------+
		// |               |-|f2  1 3 4|-> ?
		// +               | +---------+
		// |               |-|f3  2 3 4|-> ?
		// +---------------+ +---------+ 
		// external (boundary) face has a neighbouring tetrahedron
		// rewire neighbouring tetrahdron
		if (f0->neigh)
		{
			//AppOut("RewireNeighbouringTetrahedron(tetra, f0)");
			//AppEndl();
			assert(tetra);
			assert(f0);
			RewireNeighbouringTetrahedron(tetra, f0);
		}
	}

	return;
	// PASS2:
	// wire internal faces of new tetrahedra
	//TetraList::Itr lastOldItr = tetras.Begin();
	//lastOldItr = lastOldItr + (unsigned int)listSize;

	// find the iterator to the first newly created tetra
	TetraList::Itr stopTetraItr = tetras.End();
	TetraList::Itr startTetraItr = tetras.Begin();
	while ((startTetraItr != stopTetraItr)&&(oldListSize>0))
	{
		// if tetra list is empty this while loop won't execute at all
		
		Tetrahedron *firstNewTetra = *startTetraItr;
		// scan the tetra list until you find a tetra with new ID
		if (firstNewTetra->GetID() < lowestNewId)
		{
			startTetraItr++;
			AppOutN(firstNewTetra->GetID());
		}
		else
		{
			break;
		}
	}

#ifdef _DEBUG_STRICT
	//assert( ((tetras.Last()-lastOldItr)/sizeof(TetraList::Itr)) == oldSize);
#endif
	
#ifdef _DEBUG_APPOUT1
		AppOut("********size of tetra list: ");
		AppOut(tetras.Size());
		AppEndl();
		AppOut("newTetraCount = ");
		AppOut(newTetraCount);
		AppEndl();
#endif

	int numLoops = 0;
	for (TetraList::Itr newTetraItr = startTetraItr; (newTetraItr != stopTetraItr)&&(newTetraCount-- > 0); newTetraItr++)
	{
		WireTetrahedron2(startTetraItr, stopTetraItr, newTetraItr);
#ifdef _DEBUG_APPOUT1
		numLoops++;
#endif
	}

#ifdef _DEBUG_APPOUT1
		//static int numLoops = 0;
	    AppOut("number of loops: ");
		AppOut(numLoops);
		AppEndl();
#endif 
	
	 
			

	//AppOut("aftger tetra creat ");
	//AppOutN((int)faces.size());

	//cout << "after tetra creatoin: " << faces.size() << endl; 
}



// ///////////////////////////////////////////////////////////
// function: CircumsphereIsIntersected()
//
// creation date:	22/11/00
// last modified:	11/12/00
// purpose: check interection between a sphere and a vertex point
//
// arguments: sphere's tetrahedron and vertex index
//            
// ///////////////////////////////////////////////////////////

int DelaunayTetrahedralizer::CircumsphereIsIntersected(Tetrahedron *tetra, int pointIndex)
{
	// TODO: finish implementation

	// ///////////////////////////
	Vertex3* point = &(Vertex3::GetGlobalVertexList()[pointIndex]);
	Vertex3 centerObject = tetra->Centre();
	Vertex3* center = &centerObject;

	// error checking: force to initilize vertex list's neighbors
#ifdef _DEBUG_ON
	assert(center->neigh != NULL);
#endif
	//AppOutN("CircumsphereIsIntersected: ");
	//AppOut("**center**, ");
	//center->Print();
	//AppOut(" **point**, ");
	//point->Print();
	//AppEndl();

	

	double squareDistance = SQUARE_DISTANCE3P(point, center);
	
	//AppOutMode(APPOUT_LOGFILE);
	//AppOut("original center"); tetra->Centre().Print();
	//AppOut("center      : "); centre->Print();
	//AppOut("point       : "); point->Print();
	//AppOut("sq Radius   : "); AppOutN(tetra->SquareRadius());
	//AppOut("sq Distance : "); AppOutN(squareDistance);
	//int inside = (int)(squareDistance < tetra->SquareRadius());
	//AppOut("INSIDE      : "); AppOutN(inside);
	//AppOutLn(10);

	// check if the point falls inside the sphere
	// keep into account round-off error due to the
	// surface thickness
	if ( fabs(squareDistance - tetra->SquareRadius()) < (abs(machineTollerance)+0.0000000))
	{
		/*
		AppOut("**************************\n");
		AppOut("**** POINT REJECTED ****");
		AppOut(pointIndex);
		AppOut(" - sq dist: ");
		AppOut(squareDistance);
		AppOut(" - sq radius ");
		AppOut(tetra->SquareRadius());
		AppEndl();
		AppOut("**************************\n");
		AppOut("************MT*****************\n");
		AppOut(machineTollerance);
		AppOut("**************************\n");
		AppOut("**************************\n");
		AppOut("**************************\n");
		AppOut("**************************\n");
		AppOut("**************************\n");	
		*/
		return DELAUNAY_CIRCUMSPHERE_REJECTED;
	}
	// if (squareDistance < (tetra->SquareRadius() - (10.0 / tetra->SquareRadius()) * CIRCUM_DELTA) )
	else if (squareDistance < tetra->SquareRadius())
	{
		return DELAUNAY_CIRCUMSPHERE_INTERSECTED;
	}
	else
	{
		return DELAUNAY_CIRCUMSPHERE_NOT_INTERSECTED;
	}
}

// ////////////////////////////////////////////////////////////////////////
// FlagTetrahedronForDeletion
// purpuse: flag a tetrahedron for deletion.
//
// note: FlagTetrahedronForDeletion is an helping function
// for the tetrahedron flag mechanism 

void DelaunayTetrahedralizer::FlagTetrahedronForDeletion(TetraList::Itr tetraItr)
{
	//AppOut("FlagTetrahedronForDeletion");
	//AppEndl();

	 (*tetraItr)->Flagged(true);
}



// ///////////////////////////////////////////////////////////
// function: DeleteFlaggedTetrahedra()
//
// creation date:	09/12/00
// last modified:	11/12/00
// purpose: delete flagged tetrahedra
//
// arguments: tetra list
//          
// ///////////////////////////////////////////////////////////

void DelaunayTetrahedralizer::DeleteFlaggedTetrahedra(TetraList& tetraList, TetraList::Itr firstItr, TetraList::Itr lastItr, TetraList::Itr notFound)
{
	bool isFlagged = false;
	Tetrahedron* tetra;

	TetraList::Itr prev;
	// no tetrahedra were found to be deleted
	if (firstItr == notFound)
	{
		return;
	}

	do 
	{
	
	    tetra = *firstItr;
		
		if (tetra->IsFlagged())
		{
			tetra->EnableLocalFace(false);
			// deallocate teterahedron:
			delete tetra;

			// erase tetrahedron pointer from the list
			prev = firstItr;
			isFlagged = true;
			
			
		}

	    firstItr++;
		if (isFlagged)
		{
			tetraList.Erase(prev);
			isFlagged = false;
		}
	


	} while (firstItr != tetraList.End()/*lastItr*/);

    //AppOut("DELETE: ENDED.");
	//AppEndl();
}



// ///////////////////////////////////////////////////////////
// function: RestoreFlaggedTetrahedra()
//
// creation date:	09/12/00
// last modified:	11/12/00
// purpose: restore flagged tetrahedra
//
// arguments: iterators for tetraList range to check
//            
// ///////////////////////////////////////////////////////////

void DelaunayTetrahedralizer::RestoreFlaggedTetrahedra(TetraList::Itr firstItr, TetraList::Itr lastItr, TetraList::Itr notFound)
{
	Tetrahedron* tetra;

	//AppOut("RestoreFlaggedTetrahedra");
	//AppEndl();

	assert(firstItr != notFound);
	// no tetrahedra were found to be deleted/restored
	if (firstItr == notFound)
	{
		//AppOut("RESTORE: TETRA NOT FOUND");
		//AppEndl();
		return;
	}

	//AppOut("RESTORE: UNWRAPPING tetrahedron");
	//AppEndl();
	do 
	{
		tetra = *firstItr;
		assert(tetra != NULL);
		if (tetra->IsFlagged())
		{
			tetra->Flagged(false);
		}

	} while (firstItr++ != lastItr);
}




// ///////////////////////////////////////////////////////////
// function: FlagAndDeleteBallSeededTetrahedra()
//
// creation date:	09/12/00
// last modified:	11/12/00
// purpose: flag and delete seeded tetrahedra
//
// arguments: tetra list, index to insertion vertex
//            
// ///////////////////////////////////////////////////////////

void DelaunayTetrahedralizer::FlagAndDeleteBallSeededTetrahedra(TetraList &tetras, int pointIndex, list<Face3*> &temp)
{

	TetraList::Itr tetraStartItr = tetras.Begin();
	TetraList::Itr tetraStopItr = tetras.End();
	TetraList::Itr const firstFlaggedItr = tetraStartItr;
	TetraList::Itr lastFlaggedItr = tetraStartItr;

	int beforeTetraSize = (int)tetras.Size();
	int result;
	int listSize = tetras.Size();
	for (int i = 0; i < listSize; i++)
	{
		Tetrahedron *tetra = *tetraStartItr;
		result = CircumsphereIsIntersected(tetra, pointIndex);

		if (result == DELAUNAY_CIRCUMSPHERE_INTERSECTED)
		{
			temp.push_back(tetra->F(0));
			temp.push_back(tetra->F(1));
			temp.push_back(tetra->F(2));
			temp.push_back(tetra->F(3));

			// save iterator of last tetrahedron found so far 
			// and flag it
			lastFlaggedItr = tetraStartItr;
			tetra->Flagged(true);
		
			// reassign invalidated interators
		}
		else if (result == DELAUNAY_CIRCUMSPHERE_REJECTED)
		{
			while (!temp.empty())
			{
				temp.pop_back();
			}

			tetra->Flagged(false);
			RestoreFlaggedTetrahedra(firstFlaggedItr, lastFlaggedItr, tetraStopItr);
            assert( ((int)tetras.Size()+(int)temp.size()/4)==beforeTetraSize);

			return;
		}
		else
		{
			tetra->Flagged(false);
		}

		tetraStartItr++;
	}
	// end of for loop
	DeleteFlaggedTetrahedra(tetras, firstFlaggedItr, lastFlaggedItr, tetraStopItr);
	assert( ((int)tetras.Size()+(int)temp.size()/4)==beforeTetraSize);

}


// ///////////////////////////////////////////////////////////
// function: IsTetraTouchingSuperBoundary()
//
// creation date:	09/12/00
// last modified:	11/12/00
// purpose: check if tetrahedron lies outside the boundary
//          of the convex-hull
//
// arguments: tetrahedron
//            
// ///////////////////////////////////////////////////////////

bool DelaunayTetrahedralizer::IsTetraTouchingSuperBoundary(Tetrahedron *tetra, Vertex3* a[4])
{

	// check if any tetrahedron's face is between the 
	// boundary of the supertetrahedron and the boundary
	// of the actual Delaunay tetrahedrization

	bool t0, t1, t2;
	bool IsTouchingSuperVertices = false;
	Face3 *f;

	for (int i = 0; i < 4; i++)
	{
		// process  face
		f = tetra->F(i);
		t0 = VERTEX3_IS_EQUALP(a[0],f->V(0))||VERTEX3_IS_EQUALP(a[1],f->V(0))||VERTEX3_IS_EQUALP(a[2],f->V(0))||VERTEX3_IS_EQUALP(a[3],f->V(0));
		t1 = VERTEX3_IS_EQUALP(a[0],f->V(1))||VERTEX3_IS_EQUALP(a[1],f->V(1))||VERTEX3_IS_EQUALP(a[2],f->V(1))||VERTEX3_IS_EQUALP(a[3],f->V(1));
		t2 = VERTEX3_IS_EQUALP(a[0],f->V(2))||VERTEX3_IS_EQUALP(a[1],f->V(2))||VERTEX3_IS_EQUALP(a[2],f->V(2))||VERTEX3_IS_EQUALP(a[3],f->V(2));
		IsTouchingSuperVertices = t0||t1||t2;
		
		if (IsTouchingSuperVertices)
			return IsTouchingSuperVertices;
	}
	return IsTouchingSuperVertices;
}


// ///////////////////////////////////////////////////////////////
// DeleteArbitraryBoundaryFace:
//
// purpose: delete all tetrahedra and associated faces which
// lie on between the boudary of the supertetrahedron and 
// the outer boundary of the actual tetrahedrization
// 
// note: this function gives back the convex hull of the 
// original point set, by filtering out any face and simplices
// originated by the arbitrary vertices of the supertetrahedron
//

void DelaunayTetrahedralizer::DeleteArbitraryBoundaryFaces(TetraList &tetras)
{
	int arbitrary[4];		// array to hold indices to arbitrary points
	// the index to the last entry in the global vertex list is the last of 
	// the four vertices of the supertetrahedron. 
	int lastIndex = Vertex3::GetGlobalVertexCount()-1;

	Vertex3 *a[4];

	// get supertetrahedron vertices
	a[0] = Vertex3::GetGlobalVertexList() + (Vertex3::GetGlobalVertexCount()-4);
	a[1] = a[0] + 1;
	a[2] = a[0] + 2;
	a[3] = a[0] + 3;

	// save indices to supertetrahedron vertices
	for (int n = 3; n >= 0; n--)
	{
		arbitrary[n] = lastIndex--;
	}

	// scan the entire list of tetrahedra and find any 
	// that has a vertex index to the supertetrahedron
	TetraList::Itr start = tetras.Begin();
	TetraList::Itr end   = tetras.End();
	TetraList::Itr prev;

	int count = 0;
	for (; start != tetras.End(); )
	{
		// fecth the faces of the current tetrahedron
		Tetrahedron* tetra = *start;

		// if a tetrahedron is found then delete it from the 
		// global list of tetrahedra
		bool tetrahedronTouchingSuperBoundary = IsTetraTouchingSuperBoundary(tetra, &a[0]);

		if (tetrahedronTouchingSuperBoundary)
		{
			// delete actual tetrahedron first
			tetra->EnableLocalFace(true);
			delete tetra;
			prev = start;
		}
		
        start++;
		if (tetrahedronTouchingSuperBoundary)
		{
					// erease tetrahedron pointer from list second
			tetras.Erase(prev);
		}
	}
	
}



// ///////////////////////////////////////////////////////////
// function: Build()
//
// creation date:	10/02/01
// last modified:	10/02/01
// purpose: build the Delaunay tetrahedralization 
//
// arguments: tetralist is the list of all tetrahedra to be built
// ///////////////////////////////////////////////////////////

void DelaunayTetrahedralizer::Build(TetraList &tetraList)
{
	Tetrahedron *super;

	// PHASE1: build super tetrahedron
	super = CreateSuperTetrahedron(Vertex3::GetGlobalVertexList(), Vertex3::GetGlobalVertexCount());
	tetraList.Add(super);

#ifdef _DEBUG_STRICT
	int TETRALIST_SIZE_AFTER_SUPERTETRA_IS_NOT_POSITIVE = ((int)tetraList.Size()>0);
	assert(TETRALIST_SIZE_AFTER_SUPERTETRA_IS_NOT_POSITIVE);
#endif


	// PHASE2: insert all sample points into current tetrahedralization
	int maxPoints = Vertex3::GetGlobalVertexCount();

	for (int insertPoint = 0; insertPoint < maxPoints; insertPoint+=1)
	{
		// find ball-seeded tetrahedra
		list<Face3 *> tempFaceList;	
		
		FlagAndDeleteBallSeededTetrahedra(tetraList, insertPoint,  tempFaceList);	
		RetainSinglyOccurringFaces(tempFaceList);
		CreateTetrahedronFrom4FacesAndPoint(tempFaceList, insertPoint, tetraList);
    }


	// PHASE3: eliminate boundary tetrahedra and supertetrahedron
	DeleteArbitraryBoundaryFaces(tetraList);
	Vertex3::SetGlobalVertexCount( Vertex3::GetGlobalVertexCount()-4 );
}



// ///////////////////////////////////////////////////////////
// function: Build
//
// creation date:	07/02/01
// last modified:	07/02/01
// purpose: build the voronoi tessellation from the Delaunay tetrahedralization
//
// arguments: tetralist is the list of all existing tetrahedra
// 
// notes: exploit geometrical/memory coherence
// 

void VoronoiTessellator::Build(TetraList &tetraList)
{
	TetraList::Itr startIter;
	TetraList::Itr endIter;
	
	startIter = tetraList.Begin();
	endIter = tetraList.End();
	int faceCount = 4;

	for (; startIter != endIter; startIter++)
	{
		Tetrahedron *tetra = *startIter;
		FindNeighbouringFaces(tetraList, tetra);
	}	
}


// ///////////////////////////////////////////////////////////
// function: FindNeighbouringFaces()
//
// creation date:	11/02/01
// last modified:	11/02/01
// purpose: find faces that are neigbours
//
// arguments: tetralist is the list of all existing tetrahedra
// ///////////////////////////////////////////////////////////

void VoronoiTessellator::FindNeighbouringFaces(TetraList& tetraList, Tetrahedron* tetra)
{
	TetraList::Itr startIter;
	TetraList::Itr endIter;
	
	startIter = tetraList.Begin();
	endIter = tetraList.End();
	int faceCount = 4;
	int faceIndex;
	for (; (startIter != endIter) && (faceCount> 0); startIter++)
	{
		Tetrahedron *someTetra = *startIter;
		// do not wire a tetrahedron with itself!
		if (someTetra->GetID() != tetra->GetID())
		{
			faceIndex = 0;
			WireTwoNeighbouringTetrahedra(faceIndex, someTetra, tetra, faceCount);
			faceIndex = 1;
			WireTwoNeighbouringTetrahedra(faceIndex, someTetra, tetra, faceCount);
			faceIndex = 2;
			WireTwoNeighbouringTetrahedra(faceIndex, someTetra, tetra, faceCount);
			faceIndex = 3;
			WireTwoNeighbouringTetrahedra(faceIndex, someTetra, tetra, faceCount);
		}
	}
}


// ///////////////////////////////////////////////////////////
// function: WireTwoNeighbouringTetrahedra()
//
// creation date:	11/02/01
// last modified:	11/02/01
// purpose: wire two tetrahedra that share a face
//
// arguments: tetralist is the list of all existing tetrahedra
// ///////////////////////////////////////////////////////////

void VoronoiTessellator::WireTwoNeighbouringTetrahedra(int faceIndex, Tetrahedron* someTetra, Tetrahedron* tetra, int& faceCount)
{

		Face3 *someFace = someTetra->F(faceIndex);

		if (*someFace == *(tetra->F(0)))
		{
			faceCount--;
			someFace->neigh = tetra;
			tetra->F(0)->neigh = someTetra;
		}
		if (*someFace == *(tetra->F(1)))
		{
			faceCount--;
			someFace->neigh = tetra;
			tetra->F(1)->neigh = someTetra;
		}
		if (*someFace == *(tetra->F(2)))
		{
			faceCount--;
			someFace->neigh = tetra;
			tetra->F(2)->neigh = someTetra;
		}
		if (*someFace == *(tetra->F(3)))
		{
			faceCount--;
			someFace->neigh = tetra;
			tetra->F(3)->neigh = someTetra;
		}
}




// ///////////////////////////////////////////////////////////
// function: LinkVerticesToNeighTetrahedra()
//
// creation date:	11/02/01
// last modified:	11/02/01
// purpose: link each sample vertex to the tetrahedron that it touches
//
// arguments: tetralist is the list of all existing tetrahedra
// ///////////////////////////////////////////////////////////

void VoronoiTessellator::LinkVerticesToNeighTetrahedra(TetraList &tetraList)
{
	TetraList::Itr startIter;
	TetraList::Itr endIter;
	
	startIter = tetraList.Begin();
	endIter = tetraList.End();


	for (; startIter != endIter; startIter++)
	{
		// link a tetrahedron to all of its four vertices
		// follow the 0-0-0-2 convention for vertex location 
		// within a tetrahedron (see CreateTetrahedronFrom4FaceAndPoint())
		Tetrahedron *tetra = *startIter;
		Face3 *face = tetra->F(0);
		face->V(0)->neigh->Add(tetra);
		face->V(1)->neigh->Add(tetra);
		face->V(2)->neigh->Add(tetra);
		face = tetra->F(3);
		face->V(2)->neigh->Add(tetra);	

		// if a face is on the convexhull then propagate 
		// this information about boundary status from
		// tetrahedron's faces to vertices
		for (int i = 0; i < 4; i++)
		{
			face = tetra->F(i);
			if (IsFaceOnConvexHull(face))
			{
				face->V(0)->SetFlag(GEOM_ON_CONVEX_HULL);
				face->V(1)->SetFlag(GEOM_ON_CONVEX_HULL);
				face->V(2)->SetFlag(GEOM_ON_CONVEX_HULL);

				// establish if face is cw or ccw
				// note: actually by now each face should already
				// know its state, so this is a precaution
				if (face->GetFlag() == GEOM_UNKNOWN_STATE)
				{
					if (IsFaceClockWise(face, &face->normal))
					{
						face->SetFlag(GEOM_FACE_IS_CW);
					}
					else
					{
						face->SetFlag(GEOM_FACE_IS_NOT_CW);
					}
				}

				// orient faces in a clockwise way
				assert(face->GetFlag() != GEOM_UNKNOWN_STATE);
				if (face->GetFlag() == GEOM_FACE_IS_NOT_CW)
				{
					face->Flip();
					//AppOut("flipped face of thetrahedra ");
					//AppOut(tetra->GetID());
					//AppEndl();
				}
				
			}
			else
			{
				/*
				if(face->V(0)->GetFlag() != GEOM_ON_CONVEX_HULL)
				{
					face->V(0)->SetFlag(GEOM_NOT_ON_CONVEX_HULL);
				}
				if(face->V(1)->GetFlag() != GEOM_ON_CONVEX_HULL)
				{
					face->V(1)->SetFlag(GEOM_NOT_ON_CONVEX_HULL);
				}
				if(face->V(2)->GetFlag() != GEOM_ON_CONVEX_HULL)
				{
					face->V(2)->SetFlag(GEOM_NOT_ON_CONVEX_HULL);
				}
				*/
			}
		}
	}
}


