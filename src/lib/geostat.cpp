#include "geom.h"
#include "appio.h"
#include "geostat.h"



// ////////////////////////////////////////////////////////////
// function: ShowTetraListStatistics(()
//
// creation date:	19/10/00
// last modified:	19/10/00
// purpose: show statistics
//
// arguments: tetralist to inspect and stat mode
//
// return value: none
// ////////////////////////////////////////////////////////////

void ShowTetraListStatistics(TetraList& tetraList, int mode)
{
	if (mode & TETRALIST_STATS)
	{
		AppOutN("=====TETRAHEDRA STATISTICS=====");
		AppOut("number of tetrahedra      : ");
		AppOutN((int)tetraList.Size());
		AppOut("number of faces           : ");
		AppOutN(4*(int)tetraList.Size());
		AppOut("size of tetrahedron       : ");
		AppOutN((int)sizeof(Tetrahedron));
		AppOut("memory used for tetrahedra: ");
		AppOut((((int)tetraList.Size())*(int)sizeof(Tetrahedron))/1024);
		AppOut(" Kb");
		AppEndl();
        AppOutN("...............................................");

		AppOut("number of total points  : ");
		AppOutN((int)Vertex3::GetGlobalVertexCount());
		AppOut("size of a vertex        : ");
		AppOutN((int)(sizeof(Vertex3)));
        AppOut("memory used for vertices: ");
		AppOut(((int)Vertex3::GetGlobalVertexCount()*(int)sizeof(Vertex3))/1024);
		AppOut(" Kb ");
		AppEndl();

	}

	if (mode & mode)
	{
		
	}

	if (mode & TETRA_STATS)
	{
		TetraList::Itr startIter;
		TetraList::Itr endIter;
		
		startIter = tetraList.Begin();
		endIter = tetraList.End();
		int size = tetraList.Size();

		for (; startIter != endIter; startIter++)
		{
			Tetrahedron *tetra = *startIter;
			ShowTetraStatistics(tetra);
		}
	}
}



// ////////////////////////////////////////////////////////////
// function: ShowTetraStatistics()
//
// creation date:	19/10/00
// last modified:	19/10/00
// purpose: show statistics
//
// arguments: tetrahedron to inspect
//
// return value: none
// ////////////////////////////////////////////////////////////

void ShowTetraStatistics(Tetrahedron* tetra)
{
	AppOutN("=====TETRA STATS=====");
	AppOutN("N0 N1 N2 N3 : ");
	AppOut((int)tetra->F(0)); 
	AppOut(" ");
	AppOut((int)tetra->F(1)); 
	AppOut(" ");
	AppOut((int)tetra->F(2)); 
	AppOut(" ");
	AppOut((int)tetra->F(0)); 
	AppEndl();
}
