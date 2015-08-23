// /////////////////////////////////////////////////
// visualize.cpp
//
// author:			Aaron Licata
// creation date:	01/02/01
// last modified:	01/02/01
//
// Visualize the geometrical structres 
//
#ifdef WIN32
	#include <windows.h>
#endif

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "math.h"
#include "geom.h"
#include "geomutil.h"
#include "geostat.h"
#include "appio.h"
#include "STL.h"
#include "visualize.h"
#include "crust.h"

const int OGL_GRID_DLIST = 1;
const int OGL_COORDINATE_SYSTEM_DLIST = 2;



// ///////////////////////////////////////////////////////////
// function: GeometryVisualizer()
//
// creation date:	11/11/00
// last modified:	14/04/01
// purpose: constructor
//
// arguments: box is the 3-d object to be drawn
// ///////////////////////////////////////////////////////////

GeometryVisualizer::GeometryVisualizer()
{
	isVisibleMaxBox3 = false;
	isVisibleSemiArbitraryFaces = true;
	isVoronoiCenterVisible = true;
	isVisibleTetrahedra = true;
	isVisibleVoronoi = true;
	isVisibleMaxBox = false;
	isVisibleDataSet3 = true;
	isVisibleVoronoiCell = false;
	isVisibleOnlyConvexHull = false;
	isVisibleVoronoiVertex = false;
	isVisibleCircumSphere = false;
	isVisibleVertexNormal = false;
	isVisibleFaceNormal = true;

	isVisibleGrid = true;
	isVisibleBackground = true;
	isVisibleCoordinateSystem = true;

	maxSquareRadius = 100.00;
	alphaSquareRadius = 100.0;
	alphaParamDirection = 0;
	polygonMode = GV_SMOOTHSHADING;

	backgroundColor = 1;

	// overwrite defaults
	isVisibleMaxBox3 = false;
	isVisibleSemiArbitraryFaces = false;
	isVoronoiCenterVisible = true;
	isVisibleTetrahedra = true;
	isVisibleVoronoi = false;
	isVisibleMaxBox = false;
	isVisibleDataSet3 = false;
	isVisibleVoronoiCell = false;
	isVisibleOnlyConvexHull = true;
	isVisibleVoronoiVertex = false;
	isVisibleVertexNormal = false;

	isVisibleSuperTetra = false;

	isVisibleGrid = false;
	isVisibleBackgroundPlane = true;
	isVisibleLighting = false;

	normalFactor = 0.2;


	bottomOfBox = 0.0;

	// display list for 
	
}


// ///////////////////////////////////////////////////////////
// function: DrawMaxBox3()
//
// creation date:	11/11/00
// last modified:	13/02/01
// purpose: draw a 3-d box 
//
// arguments: box is the 3-d object to be drawn
// ///////////////////////////////////////////////////////////
void GeometryVisualizer::DrawMaxBox3(BoundBox3& box)
{
	if (!IsVisibleMaxBox3()) return;

	double sx = box.MaxX() - box.MinX();
	double sy = box.MaxY() - box.MinY();
	double sz = box.MaxZ() - box.MinZ();

	glPushMatrix();
		glLineWidth(0.5);


		// front face
		glBegin(GL_LINE_LOOP);
			glColor3f(0.99, 1.0, 0.99);
		    glVertex3f(box.MinX(), box.MaxY(), box.MinZ());

			glColor3f(0.72, 0.72, 0.73);
			glVertex3f(box.MaxX(), box.MaxY(), box.MinZ());

			glColor3f(0.90, 0.90, 0.90);
			glVertex3f(box.MaxX(), box.MinY(), box.MinZ());

			glColor3f(0.83, 0.82, 0.83);
			glVertex3f(box.MinX(), box.MinY(), box.MinZ());
		glEnd();

		// back face
		glBegin(GL_LINE_LOOP);
			glColor3f(0.87, 0.86, 0.86);
			glVertex3f(box.MinX(), box.MaxY(), box.MaxZ());

			glColor3f(0.99, 0.99, 0.98);
			glVertex3f(box.MaxX(), box.MaxY(), box.MaxZ());

			glColor3f(0.71, 0.71, 0.72);
			glVertex3f(box.MaxX(), box.MinY(), box.MaxZ());

			glColor3f(0.80, 0.80, 0.80);
			glVertex3f(box.MinX(), box.MinY(), box.MaxZ());
		glEnd();

		//left face
		glBegin(GL_LINE_LOOP);
		    glVertex3f(box.MinX(), box.MaxY(), box.MinZ());
			glVertex3f(box.MinX(), box.MaxY(), box.MaxZ());
			glVertex3f(box.MinX(), box.MinY(), box.MaxZ());
			glVertex3f(box.MinX(), box.MinY(), box.MinZ());
		glEnd();

	
		//right face
		glBegin(GL_LINE_LOOP);
		    glVertex3f(box.MaxX(), box.MaxY(), box.MinZ());
			glVertex3f(box.MaxX(), box.MaxY(), box.MaxZ());
			glVertex3f(box.MaxX(), box.MinY(), box.MaxZ());
			glVertex3f(box.MaxX(), box.MinY(), box.MinZ());
		glEnd();

		//top face
		glBegin(GL_LINE_LOOP);
		    glVertex3f(box.MinX(), box.MaxY(), box.MinZ());
			glVertex3f(box.MinX(), box.MaxY(), box.MaxZ());
			glVertex3f(box.MaxX(), box.MaxY(), box.MaxZ());
			glVertex3f(box.MaxX(), box.MaxY(), box.MinZ());
		glEnd();
		
	glPopMatrix();
}


// ///////////////////////////////////////////////////////////
// function: DrawTetrahedron()
//
// creation date:	15/11/00
// last modified:	10/01/01
// purpose: draw a 3-d box 
//
// arguments: tetra is the tetrahedron object to draw 
//            mode flag specifies if solid or wire drawing mode
//
// notes: flag mode is tightly coupled to OpenGL API
// ///////////////////////////////////////////////////////////
void GeometryVisualizer::DrawTetrahedron(Tetrahedron *tetra, int mode2)
{
	int mode = GetPolygonMode();

	if (mode == GV_SMOOTHSHADING || mode == GV_FLATSOLID || mode == GV_WIREANDSHADE)
	{
		DrawShadedTetrahedron(tetra);
	}

	if (mode == GV_WIRE || mode == GV_WIREANDSHADE)
	{
		DrawWireTetrahedron(tetra);
	}


}




// ///////////////////////////////////////////////////////////
// function: DrawShadedTetrahedron()
//
// creation date:	29/11/01
// last modified:	29/11/01
// purpose: draw a tetrahedron in shaded mode
//
// arguments: tetra is the tetrahedron object to draw           
//
// return value: none
// ///////////////////////////////////////////////////////////
void GeometryVisualizer::DrawShadedTetrahedron(Tetrahedron *tetra)	
{
	Face3 *f;
	float c[3] = {0.5, 0.5, 0.9 };

	// do not show tetrahedra larger than of alpha shape values
	if (alphaParamDirection)
	{
		if (tetra->SquareRadius() <  alphaSquareRadius) return;
	}
	else
	{
		if (tetra->SquareRadius() >  alphaSquareRadius) return;
	}

	// ///////////////////// opengl ////////////////////////
	glPushMatrix();


	glColor3f(1.0, 1.0, 1.0);


	glDisable(GL_CULL_FACE);
	//glDisable(GL_DEPTH_TEST);

	if (IsVisibleLighting())
	{
		glEnable(GL_LIGHTING);
	}
	else
	{
		glDisable(GL_LIGHTING);
	}


	for (int i = 0; i < 4; i++)
	{
		f = tetra->F(i);

		if (IsVisibleOnlyConvexHull())
		if (f->neigh != NO_LINK) // show only convex-hull
			continue;

		// triangle must be on the crust
		if (f->V(0)->IsPole() || (f->V(1)->IsPole()) || (f->V(2)->IsPole()))
		{
			continue;
		}

				// solid mode
		if (GetPolygonMode() == GV_FLATSOLID 
			|| GetPolygonMode() == GV_SMOOTHSHADING
			|| GetPolygonMode() == GV_WIREANDSHADE)
		{
			glPolygonMode(GL_BACK, GL_FILL);
			glPolygonMode(GL_FRONT, GL_FILL);
		}
		else
		{
			int ERROR_NONEXISTING_RENDERING = 0;
			assert(ERROR_NONEXISTING_RENDERING);
		}


		glLineWidth(1.5);


			//glEnable(GL_NORMALIZE);
			glBegin(GL_TRIANGLES);
				GLfloat c1, c2 ,c3;
				GLfloat coff = 0.08; //color offset
				if (GetPolygonMode() == GV_FLATSOLID)
				{
					c1 = c2 = c3 = 0.70;
				}
				else
				{
					if (GetPolygonMode() == GV_SMOOTHSHADING)
					{
						c1 = 0.65;
						c2 = 0.60;
						c3 = 0.55;
					}
					else // wire and shade
					{
						c1 = 0.89;
						c2 = 0.70;
						c3 = 0.56;
					}
				}


				// /////// triangle 0 //////////
				glColor3f(c1+coff, c1, c1);
				glNormal3f(f->V(0)->normal.x, f->V(0)->normal.y, f->V(0)->normal.z);
				glVertex3f(f->V(0)->x, f->V(0)->y, f->V(0)->z);
				/////////////////////////////////


				// /////// triangle 1 //////////
				glColor3f(c2, c2, c2);
				glNormal3f(f->V(1)->normal.x, f->V(1)->normal.y, f->V(1)->normal.z);			
				glVertex3f(f->V(1)->x, f->V(1)->y, f->V(1)->z);
				/////////////////////////////////


				// //////// triangle 2 /////////
				glColor3f(c3, c3, c3+coff);
				glNormal3f(f->V(2)->normal.x, f->V(2)->normal.y, f->V(2)->normal.z);
				glVertex3f(f->V(2)->x, f->V(2)->y, f->V(2)->z);
				/////////////////////////////////

			glEnd();
			
	}

	glEnable(GL_CULL_FACE);
	//glEnable(GL_DEPTH_TEST);
	
	glDisable(GL_LIGHTING);


	glPopMatrix();
	///////////////////////// end of opengl /////////////////
	
}



// ///////////////////////////////////////////////////////////
// function: :DrawSuperTetrahedron()
//
// creation date:	23/04/01
// last modified:	23/04/01
// purpose: draw a super tetrahedron in wire mode
//
// arguments: super tetra is the tetrahedron object to draw           
//
// return value: none
// ///////////////////////////////////////////////////////////
void GeometryVisualizer::DrawSuperTetrahedron(SuperTetra &superTetra)
{
	
	if (!IsVisibleSuperTetrahedron())
	{
		return;
	}
	

	Vertex3 apex = superTetra.GetApex();
	Vertex3 left = superTetra.GetBaseLeft();
	Vertex3 right = superTetra.GetBaseRight();
	Vertex3 back = superTetra.GetBaseBack();


	glPushMatrix();

	glDisable(GL_CULL_FACE);

	glPolygonMode(GL_BACK, GL_LINE);
	glPolygonMode(GL_FRONT, GL_LINE);

	glLineWidth(3.0);

	GLfloat delta = 0.1;
	GLfloat r = 0.5-delta;
	GLfloat g = 0.5-delta;
	GLfloat b = 0.9-delta;

	// /////// triangle 0: front //////////
	glBegin(GL_TRIANGLES);
		glColor3f(r+delta, g-delta, b+delta);
		glVertex3f(apex.x, apex.y, apex.z);
		glColor3f(r-delta, g-delta, b+delta);
		glVertex3f(right.x, right.y, right.z);
		glColor3f(r-delta, g-delta, b+delta);
		glVertex3f(left.x, left.y, left.z);
	glEnd();

	// /////// triangle 1: right  //////////
	glBegin(GL_TRIANGLES);
		glColor3f(r, g+delta, b+delta);
		glVertex3f(apex.x, apex.y, apex.z);
		glColor3f(r+delta, g-delta, b+delta);
		glVertex3f(back.x, back.y, back.z);
		glColor3f(r-delta, g-delta, b+delta);
		glVertex3f(right.x, right.y, right.z);
	glEnd();
	
	// /////// triangle 2: left //////////
	glBegin(GL_TRIANGLES);
		glColor3f(r-delta, g-delta, b+delta);
		glVertex3f(apex.x, apex.y, apex.z);
		glColor3f(r+delta, g-delta, b+delta);
		glVertex3f(left.x, left.y, left.z);
		glColor3f(r+delta, g+delta, b+delta);
		glVertex3f(back.x, back.y, back.z);
	glEnd();

	// /////// triangle 3: bottom //////////
	glBegin(GL_TRIANGLES);
		glColor3f(r, g, b);
		glVertex3f(back.x, back.y, back.z);
		glVertex3f(left.x, left.y, left.z);
		glVertex3f(right.x, right.y, right.z);
	glEnd();


	glEnable(GL_CULL_FACE);

	glPopMatrix();



}


// ///////////////////////////////////////////////////////////
// function: DrawWireTetrahedron()
//
// creation date:	29/11/01
// last modified:	29/11/01
// purpose: draw a tetrahedron in wire mode
//
// arguments: tetra is the tetrahedron object to draw           
//
// return value: none
// ///////////////////////////////////////////////////////////
void GeometryVisualizer::DrawWireTetrahedron(Tetrahedron *tetra)	
{
	Face3 *f;
	float c[3] = {0.5, 0.5, 0.9 };

	// do not show tetrahedra larger than of alpha shape values
	if (alphaParamDirection)
	{
		if (tetra->SquareRadius() <  alphaSquareRadius) return;
	}
	else
	{
		if (tetra->SquareRadius() >  alphaSquareRadius) return;
	}

	glColor3f(1.0, 1.0, 1.0);


	/*
	if (GetPolygonMode() == GV_POINTS)
	{
		if (!IsVisibleDataSet3()) 
		{
			SetVisibleDataSet3(true);
		}
		else
		{
			return;
		}

		return;
	}*/

	// ////////////////// opengl //////////////////
	glPushMatrix();

	glDisable(GL_CULL_FACE);
	//glDisable(GL_DEPTH_TEST);
	for (int i = 0; i < 4; i++)
	{
		f = tetra->F(i);

		if (IsVisibleOnlyConvexHull())
		if (f->neigh != NO_LINK) // show only convex-hull
			continue;

		// wire mode
		if (GetPolygonMode() == GV_WIRE || GetPolygonMode() == GV_WIREANDSHADE)
		{
			glPolygonMode(GL_BACK, GL_LINE);
			glPolygonMode(GL_FRONT, GL_LINE);
		}
		else
		{
			int ERROR_NON_ALLOWED_RENDERING = 0;
			assert(ERROR_NON_ALLOWED_RENDERING);
		}

		
		glLineWidth(1.9);


			//glEnable(GL_NORMALIZE);
			glBegin(GL_TRIANGLES);

			// /////// triangle 0 //////////
			GLfloat r = 0.9f;
			GLfloat g = 0.0f;
			GLfloat b = 0.25f;
			GLfloat off = 0.1f;
			GLfloat delta = 0.2;

				glColor3f(r-delta, g, b+off-delta);
				glVertex3f(f->V(0)->x, f->V(0)->y, f->V(0)->z);
				// /////// triangle 1 //////////
				glColor3f(r, g, b+off);
				glVertex3f(f->V(1)->x, f->V(1)->y, f->V(1)->z);
				// //////// triangle 2 /////////
				glColor3f(r, g, b+2*off);
				glVertex3f(f->V(2)->x, f->V(2)->y, f->V(2)->z);
			glEnd();
	}

	glPopMatrix();
	////////////// end of opengl ///////////////////////////
	
}

// ///////////////////////////////////////////////////////////
// function: DrawVoronoi()
//
// creation date:	07/02/01
// last modified:	09/02/01
// purpose: draw the Voronoi 3-d diagram
//
// arguments: none
// ///////////////////////////////////////////////////////////
void GeometryVisualizer::DrawVoronoi(Tetrahedron *tetra, int mode)
{
	//glDisable(GL_CULL_FACE);
	//glDisable(GL_DEPTH_TEST);

		glLineWidth(1.0);
		glPointSize(3.5);

		//ShowTetraStatistics(tetra);

       	if (IsVisibleVoronoiVertex())
		{
			if (tetra->Centre().pole)
			{
				glColor3f(0.2, 0.105, 1.0);
			}
			else
			{
				glColor3f(1.0, 0.005, 0.2);
			}
			glBegin(GL_POINTS);
					glVertex3f(
						tetra->Centre().x,
						tetra->Centre().y,
						tetra->Centre().z);
			glEnd();
		}
	
		bool infinite = 
			(tetra->F(0)->neigh!=NO_LINK) && 
			(tetra->F(1)->neigh!=NO_LINK) &&
			(tetra->F(2)->neigh!=NO_LINK) &&
			(tetra->F(3)->neigh!=NO_LINK);
		
	if (IsVisibleVoronoi())
		for (int i = 0; i < 4; i++)
		{
			Face3 *face = tetra->F(i);
			Tetrahedron *neigh = face->neigh;
			if (neigh != NO_LINK)
			{
			
				glBegin(GL_LINES);
					glColor3f(0.90, 0.71, 0.01);
					glVertex3f(tetra->Centre().x, tetra->Centre().y, tetra->Centre().z);
					glColor3f(1.00, 0.41, 0.05);
					glVertex3f(neigh->Centre().x, neigh->Centre().y, neigh->Centre().z);
				glEnd();
				
			}
			else  // voronoi edge/plane to infinity
			{
				/*
				Vertex3 *v0 = face->V(0);
				Vertex3 *v1 = face->V(1);
				Vertex3 *v2 = face->V(2);
				Vertex3 m;
				m.x = (v0->x+v2->x)/2;
				m.y = (v0->y+v2->y)/2;
				m.y = (v0->z+v2->z)/2;
				glBegin(GL_LINES);
					glColor3f(0.00, 0.87, 0.01);
					glVertex3f(tetra->Centre().x, tetra->Centre().y, tetra->Centre().z);
					glColor3f(0.00, 0.66, 0.02);
					glVertex3f(m.x, m.y, m.z);
				glEnd();
				*/
			}
		}

		if (IsVisibleVoronoiVertex())
		{
			glPushMatrix();
			glPointSize(6.0);
			glBegin(GL_POINTS);
				glColor3f(0.3, 0.0, 0.05);
				glVertex3f(tetra->Centre().x, tetra->Centre().y, tetra->Centre().z);
			glEnd();
			glPopMatrix();
		}
		
/*		
    for (int i = 0; i < 4; i++)
	{
		f = tetra->F(i);

		glLineWidth(1.0);
		glPointSize(2.0);

		// draw tetra center (voronoi vertex)
		if (isVoronoiCenterVisible)
		{
			glColor3f(1.0, 0.0, 0.0);
			glBegin(GL_POINTS);
				glVertex3f(
					tetra->Centre().x,
					tetra->Centre().y,
					tetra->Centre().z);
			glEnd();
		}

		Tetrahedron *neigh = f->neigh;


		if (neigh != NO_LINK)
		{
			glBegin(GL_LINES);
				glColor3f(1.00, 0.61, 0.01);
				glVertex3f(tetra->Centre().x, tetra->Centre().y, tetra->Centre().z);
				glColor3f(1.00, 0.21, 0.05);
				glVertex3f(neigh->Centre().x, neigh->Centre().y, neigh->Centre().z);
			glEnd();
		}
		else
		{
			//AppOutN("NO_LINK");
		}

	
		//glDisable(GL_NORMALIZE);
	
	}
	*/
	
}


void GeometryVisualizer::DrawTetraList(TetraList& tetraList, int mode)
{
	TetraList::Itr startIter;
	TetraList::Itr endIter;
	
	startIter = tetraList.Begin();
	endIter = tetraList.End();
	int size = tetraList.Size();

	for (; startIter != endIter; startIter++)
	{
		Tetrahedron *tetra = *startIter;

		if (tetra->SquareRadius() < maxSquareRadius)
		{
			if (isVisibleTetrahedra)
			{
				DrawTetrahedron(tetra, mode);
			}
			DrawVoronoi(tetra, mode);
			DrawCircumSphere(tetra);
		}
	}
}

void GeometryVisualizer::DrawCircumSphere(Tetrahedron* tetra)
{
	if (!IsVisibleCircumSphere()) return;

   GLint slices = 19;
   GLint stacks = 20;
   GLfloat alpha = 0.074;
   double maxRadius = 0.3;
   double radius = sqrt(tetra->SquareRadius());


   //if (radius > maxRadius) return;

	glPushMatrix();

	glEnable(GL_BLEND);
	glTranslatef(tetra->Centre().x, tetra->Centre().y, tetra->Centre().z);
	if (radius < maxRadius)
	{
		glColor4f(0.9, 0.0, 0.5, alpha);
	}
	else
	{
		glColor4f(0.1, 0.0, 0.9, alpha);
	}
	glutSolidSphere(radius, slices, stacks);
	
	glPopMatrix();
		

		
}

// ///////////////////////////////////////////////////////////
// function: DrawDataSet3()
//
// creation date:	12/10/00
// last modified:	06/03/01
// purpose: draw the set of vertices in a 3-d object
//
// arguments: obj is a 3-d object holding the vertices
//
// return value: none
// ///////////////////////////////////////////////////////////
void GeometryVisualizer::DrawDataSet3(Skeleton *obj)
{
	int count;

	if (IsVisibleDataSet3())
	{
	   glPushMatrix();

	   count = Vertex3::GetGlobalVertexCount();

	   glBegin(GL_POINTS);
	   for (int k2=0; k2 < count; k2++)
	   {
			
			if (obj->vert[k2].GetFlag() == GEOM_ON_CONVEX_HULL)
			{
				glPointSize(3.5);
				glColor3f(1.0, 1.0, 0.2);
			}
			else
			{
				glPointSize(2.5);
				glColor3f(0.0, 1.0, 0.9);
			}

			if (obj->vert[k2].IsPole())
			{
				glPointSize(3.0);
				glColor3f(1.0, 0.0, 1.0);
			}

			glVertex3f(obj->vert[k2].x, obj->vert[k2].y, obj->vert[k2].z);
	   }
	   glEnd();

	   glPopMatrix();

	}
}


// ///////////////////////////////////////////////////////////
// function: DrawVertexNormals()
//
// creation date:	06/03/01
// last modified:	06/03/01
// purpose: draw all vertex normals
//
// arguments: none
//
// return value: none
// ///////////////////////////////////////////////////////////
void GeometryVisualizer::DrawVertexNormals()
{
      int count = Vertex3::GetGlobalVertexCount();

	   for (int k2=0; k2 < count; k2++)
	   {
			DrawVertexNormal(k2);

	   }
	
}


// ///////////////////////////////////////////////////////////
// function: DrawVertexNormals()
//
// creation date:	24/04/01
// last modified:	24/04/01
// purpose: draw all face normals
//
// arguments: tetraList whose face normals have to be drawn
//
// return value: none
// ///////////////////////////////////////////////////////////
void GeometryVisualizer::DrawFaceNormals(TetraList& tetraList)
{

	if (!IsVisibleFaceNormal()) return;


	TetraList::Itr start = tetraList.Begin();
	TetraList::Itr end = tetraList.End();

	while (start != end)
	{
		Tetrahedron* tetra = *start++;

		DrawFaceNormal(tetra->F(0));
		DrawFaceNormal(tetra->F(1));
		DrawFaceNormal(tetra->F(2));
		DrawFaceNormal(tetra->F(3));

	}
}



// ///////////////////////////////////////////////////////////
// function: DrawVoronoiCell()
//
// creation date:	12/02/01
// last modified:	12/02/01
// purpose: draw a Voronoi cell from a Delaunay vertex (site)
//
// arguments: pointIndex is a index to the vertex list
// ///////////////////////////////////////////////////////////
void GeometryVisualizer::DrawVoronoiCell(int pointIndex)
{
#ifndef _DEBUG_STRICT
	assert (pointIndex < Vertex::GetGlobalVertexCount())
#endif
	glPushMatrix();

    DrawVertexNormal(pointIndex);

	if (!IsVisibleVoronoiCell()) return;

	Vertex3* globalList;
	globalList = Vertex3::GetGlobalVertexList();

	Vertex3 *v = &globalList[pointIndex];

	if (v->neigh->Size() > 0)
	{
		TetraList::Itr start = v->neigh->Begin();
		TetraList::Itr end   = v->neigh->End();

		// draw poles of the 3-d Voronoi cell
		Vertex3 poleMinus;
		Vertex3 polePlus;
		MedialAxisTransformer mat;
        mat.FindPolesFromDelaunayVertex(pointIndex, poleMinus, polePlus);
		// draw pole-
		glPointSize(8.0);
		glBegin(GL_POINTS);
			glColor3f(1.0, 0.0, 1.0);
			glVertex3f(poleMinus.x, poleMinus.y, poleMinus.z);
		glEnd();
		// draw pole+
		glBegin(GL_POINTS);
			glColor3f(0.1, 7.0, 0.2); // green
			glVertex3f(polePlus.x, polePlus.y, polePlus.z);
		glEnd();
		
		for (; start != end; start++)
		{
			Tetrahedron* tetra = *start;
			Vertex3 vv = tetra->Centre();
			glPointSize(3.0);
			glBegin(GL_LINES);
				glColor3f(0.9, 0.2, 1.0);
				glVertex3f(v->x, v->y, v->z);
				glColor3f(0.6, 0.0, 0.2);
				glVertex3f(vv.x, vv.y, vv.z);
			glEnd();

			glPointSize(7.0);
			glBegin(GL_POINTS);
				if (v->GetFlag() == GEOM_ON_CONVEX_HULL)
				{
					glColor3f(1.0, 1.0, 1.0);
				}
				else
				{
					glColor3f(0.6, 0.6, 1.0);
				}
				glVertex3f(v->x, v->y, v->z);
			glEnd();
		
			glPointSize(4.0);
			glBegin(GL_POINTS);
				glColor3f(1.0, 0.4, 0.345);
				glVertex3f(vv.x, vv.y, vv.z);
			glEnd();
		}
	}

	glPopMatrix();
}

// ///////////////////////////////////////////////////////////
// function: DrawVertexNormal()
//
// creation date:	07/03/01
// last modified:	07/03/01
// purpose: draw the normal vector to a vertex
//
// arguments: id of the vertex whose normal has to be draw
//
// return value: none
// ///////////////////////////////////////////////////////////
void GeometryVisualizer::DrawVertexNormal(int vertexId)
{
	if (!IsVisibleVertexNormal()) return;

	Vertex3 *vertex = Vertex3::GetVertex(vertexId);

	Vector3 vector = vertex->Normal();
	
	glPushMatrix();

	// the normal
	glLineWidth(0.05);
	double offset0 = GetNormalFactor();
	glBegin(GL_LINES);
		glColor3f(0.5, 0.9, 0.7);
		glVertex3f(vertex->x, vertex->y, vertex->z);
		glColor3f(0.5, 0.7, 0.9);
		glVertex3f(vertex->x+vector.x*offset0, vertex->y+vector.y*offset0, vertex->z+vector.z*offset0);
	glEnd();

	// tip of normal
	glPointSize(2.0);
	double offset1 = offset0+0.001*offset0;
	double offset2 = offset1+0.001*offset0;
	glBegin(GL_POINTS);
		glColor3f(1.0, 0.999, 1.0);
		glVertex3f(vertex->x+vector.x*offset1, vertex->y+vector.y*offset1, vertex->z+vector.z*offset1);
		glColor3f(1.0, 0.999, 1.0);
		glVertex3f(vertex->x+vector.x*offset2, vertex->y+vector.y*offset2, vertex->z+vector.z*offset2);
	glEnd();
	glPopMatrix();

	/*
	AppOut("vertex normal ");
	AppOut(vector.x);
	AppOut(vector.x);
	AppOut(vector.x);
	AppEndl();
	*/
}

// ///////////////////////////////////////////////////////////
// function: DrawFaceNormal()
//
// creation date:	07/03/01
// last modified:	07/03/01
// purpose: draw the normal vector to a vertex
//
// arguments: face whose normal has to be draw
//
// return value: none
// ///////////////////////////////////////////////////////////
void GeometryVisualizer::DrawFaceNormal(Face3 *face)
{
	if (!IsVisibleFaceNormal()) return;
	if (!IsFaceOnConvexHull(face)) return;

	Vertex3 tmpVertex;
	Vertex3* vertex = &tmpVertex;
	// center of face: use simple averge
	vertex->x = (face->V(0)->x + face->V(1)->x + face->V(2)->x)/3;
	vertex->y = (face->V(0)->y + face->V(1)->y + face->V(2)->y)/3;
	vertex->z = (face->V(0)->z + face->V(1)->z + face->V(2)->z)/3;

	/*
	// if no normal has been calculate before 
	// then do it now (non-procossed normal is 0,0,0)
	if (face->Normal().x == face->Normal().y 
		&& face->Normal().y == face->Normal().z 
		&& face->Normal().z == 0.0)
	{
		face->MakeNormal();
	}
	*/

	// if normal has not been normalized 
	// then create a temporary unit normal 
	Vector3 vector = face->Normal();
	if (vector.Magnitude() < 0.999 || vector.Magnitude() > 1.001)
	{
		vector.Normalize();
	}

	glPushMatrix();

	// the normal
	glLineWidth(0.05);
	double offset0 = GetNormalFactor();
	glBegin(GL_LINES);
		glColor3f(0.99, 0.8, 0.6);
		glVertex3f(vertex->x, vertex->y, vertex->z);
		glColor3f(0.88, 0.5, 0.7);
		glVertex3f(vertex->x+vector.x*offset0, vertex->y+vector.y*offset0, vertex->z+vector.z*offset0);
	glEnd();

	// tip of normal
	glPointSize(2.0);
	double offset1 = offset0+0.001*offset0;
	double offset2 = offset1+0.001*offset0;
	glBegin(GL_POINTS);
		glColor3f(0.99, 0.8, 1.0);
		glVertex3f(vertex->x+vector.x*offset1, vertex->y+vector.y*offset1, vertex->z+vector.z*offset1);
		glColor3f(0.99, 0.8, 1.0);
		glVertex3f(vertex->x+vector.x*offset2, vertex->y+vector.y*offset2, vertex->z+vector.z*offset2);
	glEnd();
	glPopMatrix();


}

// ///////////////////////////////////////////////////////////
// function: DrawGrid()
//
// creation date:	24/03/01
// last modified:	24/03/01
// purpose: draw a grid in space
//
// arguments: none
//
// return value: none
// ///////////////////////////////////////////////////////////
void GeometryVisualizer::DrawGrid()
{
	if (!IsVisibleGrid()) return;

	glPushMatrix();

	glLineWidth(1.0);

		int numLines = 5;
		float size = 0.5;
		float minx = -size;
		float maxx = +size;
		float miny = -size;
		float maxy = +size;
		float minz = -size;
		float maxz = -size;
		float step = ((maxx - minx)/2)/(float)(numLines);// + (float)(numLines%2);
		float delta;

		float off = step;
		if (numLines < 6)
		{
			off = 0.0;
		}
	
		float col =0.30;
		// grid 1: vertical lines
		for (delta = minx; delta <= (maxx+off); delta += step)
		{
			glBegin(GL_LINES);
				glColor3f(col, col, col);
				glVertex3f(delta, miny, minz);
				glColor3f(col, col, col);
				glVertex3f(delta, maxy, maxz);
			glEnd();
		}
		// grid 1: horizontal lines
		for (delta = miny; delta <= (maxy+off); delta += step)
		{	
			glBegin(GL_LINES);
				glColor3f(col, col, col);
				glVertex3f(minx, delta, minz);
				glColor3f(col, col, col);
				glVertex3f(maxx, delta, maxz);
			glEnd();
		}

		// bottom plane
		maxx = +size;
		minx = -size;
		maxy = -size;
		miny = -size;
		maxz = +size;
		minz = -size;
		// grid 2: vertical lines
		for (delta = minx; delta <= (maxx+off); delta += step)
		{
			glBegin(GL_LINES);
				glColor3f(col, col, col);
				glVertex3f(delta, miny, minz);
				glColor3f(col, col, col);
				glVertex3f(delta, maxy, maxz);
			glEnd();
		}
		// grid 2: horizontal lines
		for (delta = -size; delta <= (+size+off); delta += step)
		{	
			glBegin(GL_LINES);
				glColor3f(col, col, col);
				glVertex3f(minx, miny, delta);
				glColor3f(col, col, col);
				glVertex3f(maxx, maxy, delta);
			glEnd();
		}

		// left plane
		maxx = +size;
		minx = +size;
		maxy = +size;
		miny = -size;
		maxz = +size;
		minz = -size;
		// grid 3: vertical lines
		for (delta = -size; delta <= (+size+off); delta += step)
		{
			glBegin(GL_LINES);
				glColor3f(col, col, col);
				glVertex3f(minx, miny, delta);
				glColor3f(col, col, col);
				glVertex3f(maxx, maxy, delta);
			glEnd();
		}
		// grid 3: horizontal lines
		for (delta = -size; delta <= (+size+off); delta += step)
		{	
			glBegin(GL_LINES);
				glColor3f(col, col, col);
				glVertex3f(minx, delta, minz);
				glColor3f(col, col, col);
				glVertex3f(maxx, delta, maxx);
			glEnd();
		}
	

	glPopMatrix();
}

// ///////////////////////////////////////////////////////////
// function: DrawBackground()
//
// creation date:	24/03/01
// last modified:	24/03/01
// purpose: draw a textured background in space
//
// arguments: none
//
// return value: none
// ///////////////////////////////////////////////////////////
void GeometryVisualizer::DrawBackground()
{
	if (!IsVisibleBackground()) return;

	glPushMatrix();

	glPopMatrix();
}


// ///////////////////////////////////////////////////////////
// function: DrawFaceArray()
//
// creation date:	24/04/01
// last modified:	24/04/01
// purpose: draw an array of face indices (polygon mesh)
//
// arguments: face array
//
// return value: none
// ///////////////////////////////////////////////////////////

void GeometryVisualizer::DrawFaceArray(unsigned long *faceArray, long faceCount)
{
	if (faceCount <= 0) return;

	int mode = GetPolygonMode();

	if (mode == GV_SMOOTHSHADING || mode == GV_FLATSOLID || mode == GV_WIREANDSHADE)
	{
		DrawShadedFaceArray(faceArray, faceCount);
	}

	if (mode == GV_WIRE || mode == GV_WIREANDSHADE)
	{
		DrawWireFaceArray(faceArray, faceCount);
	}
}


// ///////////////////////////////////////////////////////////
// function: DrawShadedFaceArray()
//
// creation date:	24/04/01
// last modified:	24/04/01
// purpose: draw an array of face indices (polygon mesh)
//
// arguments: face array
//
// return value: none
// ///////////////////////////////////////////////////////////

void GeometryVisualizer::DrawShadedFaceArray(unsigned long *faceArray, long faceCount)
{
	if (faceCount <= 0) return;


	glPushMatrix();


	if (IsVisibleLighting())
	{
		glEnable(GL_LIGHTING);
	}
	else
	{
		glDisable(GL_LIGHTING);
	}

	glDisable(GL_CULL_FACE);
	glLineWidth(1.0);

	glPolygonMode(GL_BACK, GL_FILL);
	glPolygonMode(GL_FRONT, GL_FILL);


	GLfloat c1[3];
	GLfloat c2[3];
	GLfloat c3[3];
	if (GetPolygonMode() == GV_FLATSOLID)
	{
		c1[0] = c2[0] = c3[0] = 0.70;
		c1[1] = c2[1] = c3[1] = 0.70;
		c1[2] = c2[2] = c3[2] = 0.70;
		if (IsVisibleLighting())
		{
			glDisable(GL_LIGHTING);
			SetVisibleLighting(false);
		}


	}
	else
	{
		if (GetPolygonMode() == GV_SMOOTHSHADING)
		{
			c1[0] = 0.61; c2[0] = 0.60; c3[0] = 0.60;
			c1[1] = 0.71; c2[1] = 0.70; c3[1] = 0.70;
			c1[2] = 0.84; c2[2] = 0.84; c3[2] = 0.84;			c1[0] = 0.65; c2[1] = 0.60; c3[2] = 0.55;
		}
		else // wire and shade
		{
			c1[0] = 0.61; c2[0] = 0.60; c3[0] = 0.60;
			c1[1] = 0.71; c2[1] = 0.70; c3[1] = 0.70;
			c1[2] = 0.81; c2[2] = 0.80; c3[2] = 0.80;				c1[0] = 0.65; c2[1] = 0.60; c3[2] = 0.55;
		}
	}

	for (int i = 0; i < faceCount*3; i +=3)
	{
		// get triangles to draw from faceIndex array
		Vertex3 *v0 = Vertex3::GetVertex(faceArray[i+0]);
		Vertex3 *v1 = Vertex3::GetVertex(faceArray[i+1]);
		Vertex3 *v2 = Vertex3::GetVertex(faceArray[i+2]);

		glBegin(GL_TRIANGLES);

			//glColor3f(1.0f, 0.0f, 0.0f);
			glColor3f(c1[0], c2[0], c3[0]);
			glNormal3f(v0->normal.x, v0->normal.y, v0->normal.z);
			glVertex3f(v0->x, v0->y, v0->z);

			//glColor3f(1.0f, 0.5f, 0.0f);
			glColor3f(c1[1], c2[1], c3[1]);
			glNormal3f(v1->normal.x, v1->normal.y, v1->normal.z);
			glVertex3f(v1->x, v1->y, v1->z);

			//glColor3f(1.0f, 0.0f, 0.5f);
			glColor3f(c1[2], c2[2], c3[2]);
			glNormal3f(v2->normal.x, v2->normal.y, v2->normal.z);
			glVertex3f(v2->x, v2->y, v2->z);

		glEnd();
	}

	glPolygonMode(GL_BACK, GL_LINE);
	glPolygonMode(GL_FRONT, GL_LINE);

	
	glDisable(GL_LIGHTING);
	glEnable(GL_CULL_FACE);
	
	glPopMatrix();
}



// ///////////////////////////////////////////////////////////
// function: DrawWreFaceArray()
//
// creation date:	24/04/01
// last modified:	24/04/01
// purpose: draw an array of face indices (polygon mesh)
//
// arguments: face array
//
// return value: none
// ///////////////////////////////////////////////////////////

void GeometryVisualizer::DrawWireFaceArray(unsigned long *faceArray, long faceCount)
{
	if (faceCount <= 0) return;

	int mode = GetPolygonMode();

	glPushMatrix();

	glDisable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

	glPolygonMode(GL_BACK, GL_LINE);
	glPolygonMode(GL_FRONT, GL_LINE);

	GLfloat r, b, g, off, delta;

	if (mode == GV_WIRE)
	{
		
		r = 0.9f;
		g = 0.0f;
		b = 0.25f;
		off = 0.1f;
		delta = 0.2;
		/*
		r = 0.2f;
		g = 0.2f;
		b = 0.2f;
		off = 0.05f;
		delta = 0.05;
		*/
		glLineWidth(1.9);
	}
	
	else //  mode == GV_WIREANDSHADE
	{
		r = 0.5f;
		g = 0.5f;
		b = 0.5f;
		off = 0.01f;
		delta = 0.01;
		glLineWidth(2.5);
	}
	


	for (int i = 0; i < faceCount*3; i +=3)
	{
		// get triangles to draw from faceIndex array
		Vertex3 *v0 = Vertex3::GetVertex(faceArray[i+0]);
		Vertex3 *v1 = Vertex3::GetVertex(faceArray[i+1]);
		Vertex3 *v2 = Vertex3::GetVertex(faceArray[i+2]);


		glBegin(GL_TRIANGLES);
	
			glColor3f(r-delta, g, b+off-delta);
			glVertex3f(v0->x, v0->y, v0->z);

			glColor3f(r, g, b+off);
			glVertex3f(v1->x, v1->y, v1->z);

			glColor3f(r, g, b+2*off);
			glVertex3f(v2->x, v2->y, v2->z);

		glEnd();
	}

	glPolygonMode(GL_BACK, GL_LINE);
	glPolygonMode(GL_FRONT, GL_LINE);

	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	
	glPopMatrix();
}




// ///////////////////////////////////////////////////////////
// function: InitializeContext()
//
// creation date:	27/03/01
// last modified:	27/03/01
// purpose: initlization of the visual context: i
// i.e. ogl display lists
//
// arguments: none
//
// return value: none
// ///////////////////////////////////////////////////////////
void GeometryVisualizer::InitializeContext()
{
	// initalization of display lists

	// create grid display list

	// create coordinate system display list

}

// ///////////////////////////////////////////////////////////
// function: DrawCoordinateSystem()
//
// creation date:	27/03/01
// last modified:	27/03/01
// purpose: draw the three axis of the coordinate system
//
// arguments: none
//
// return value: none
// ///////////////////////////////////////////////////////////
void GeometryVisualizer::DrawCoordinateSystem()
{
	if (!IsVisibleCoordinateSystem()) return;

	glColor3f(1.0, 1.0, 1.0);
	glPointSize(3.0);
	glBegin(GL_POINTS);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(1.0, 0.0, 0.0);
		glVertex3f(0.0, 1.0, 0.0);
		glVertex3f(0.0, 0.0, 1.0);
	glEnd();
	glLineWidth(2.51);
	// x-axis red
	glBegin(GL_LINES);
		glColor3f(0.4, 0.0, 0.0);
		glVertex3f(0.0, 0.0, 0.0);
		glColor3f(0.99, 0.08, 0.23);
		glVertex3f(1.0, 0.0, 0.0);
	glEnd();
	// y-axis green
	glBegin(GL_LINES);
		glColor3f(0.0, 3.0, 0.0);
		glVertex3f(0.0, 0.0, 0.0);
		glColor3f(0.31, 0.99, 0.05);
		glVertex3f(0.0, 1.0, 0.0);
	glEnd();
	// z-axis blue
	glBegin(GL_LINES);
		glColor3f(0.0, 0.0, 0.4);
		glVertex3f(0.0, 0.0, 0.0);
		glColor3f(0.3, 0.1, 0.99);		
		glVertex3f(0.0, 0.0, 1.0);
	glEnd();
	
}


// ///////////////////////////////////////////////////////////
// function: DrawBackgroundPlane()
//
// creation date:	29/03/01
// last modified:	29/03/01
// purpose: draw a large grid representing the floor
//
// arguments: none
//
// return value: none
// ///////////////////////////////////////////////////////////
void GeometryVisualizer::DrawBackgroundPlane()
{
	if (!IsVisibleBackgroundPlane()) return;

	glPushMatrix();


		int numLines = 25;
		float size = 5.0;
		float minx = -size;
		float maxx = +size;
		float miny = -size;
		float maxy = +size;
		float minz = -size;
		float maxz = -size;
		float step = ((maxx - minx)/2)/(float)(numLines);// + (float)(numLines%2);
		float delta;

		float off = step;
		if (numLines < 6)
		{
			off = 0.0;
		}
	
		float col =0.20;
		float cd = 0.11; // color delta

		// bottom plane
		maxx = +size;
		minx = -size;
		maxy = (float)GetBottomOfBox();
		miny = (float)GetBottomOfBox();
		maxz = +size;
		minz = -size;
		// grid 2: vertical lines
		for (delta = minx; delta <= (maxx+off); delta += step)
		{
			if (delta > -0.001 && delta <= +0.001)
			{
				glLineWidth(2.0);
				col = 0.06;
			}
			else
			{
				glLineWidth(1.0);
				col = 0.20;
			}
			glBegin(GL_LINES);
				glColor3f(col+cd, col+cd, col+cd);
				glVertex3f(delta, miny, minz);
				glColor3f(col, col, col);
				glVertex3f(delta, maxy, maxz);
			glEnd();
		}
		// grid 2: horizontal lines
		cd = 0.0;
		for (delta = -size; delta <= (+size+off); delta += step)
		{	
			if (delta > -0.001 && delta <= +0.001)
			{
				glLineWidth(2.0);
				col = 0.15;
			}
			else
			{
				glLineWidth(1.0);
				col = 0.20;
			}
			cd += 0.005;
			glBegin(GL_LINES);
				glColor3f(col+cd, col+cd, col+cd);
				glVertex3f(minx, miny, delta);
				glColor3f(col+cd, col+cd, col+cd);
				glVertex3f(maxx, maxy, delta);
			glEnd();
		}

	glPopMatrix();
}



// ///////////////////////////////////////////////////////////
// function: IsSuperVertex()
//
// creation date:	11/04/01
// last modified:	12/04/01
// purpose: check if a vertex is from 
//          the super tetrahedron
//
// arguments: none
//
// return value: none
// ///////////////////////////////////////////////////////////

bool IsSuperVertex(Face3 *f)
{
Vertex3 *a[4];

	// get supertetrahedron vertices
	a[0] = Vertex3::GetGlobalVertexList() + (Vertex3::GetGlobalVertexCount()-4);
	a[1] = a[0] + 1;
	a[2] = a[0] + 2;
	a[3] = a[0] + 3;
	

		bool t0 = VERTEX3_IS_EQUALP(a[0],f->V(0))||VERTEX3_IS_EQUALP(a[1],f->V(0))||VERTEX3_IS_EQUALP(a[2],f->V(0))||VERTEX3_IS_EQUALP(a[3],f->V(0));
		bool t1 = VERTEX3_IS_EQUALP(a[0],f->V(1))||VERTEX3_IS_EQUALP(a[1],f->V(1))||VERTEX3_IS_EQUALP(a[2],f->V(1))||VERTEX3_IS_EQUALP(a[3],f->V(1));
		bool t2 = VERTEX3_IS_EQUALP(a[0],f->V(2))||VERTEX3_IS_EQUALP(a[1],f->V(2))||VERTEX3_IS_EQUALP(a[2],f->V(2))||VERTEX3_IS_EQUALP(a[3],f->V(2));

		bool superVertices = t0&&t1&&t2;
	
		return superVertices ;
}



// ///////////////////////////////////////////////////////////
// function: IsTouchingSuperVertices
//
// creation date:	11/04/01
// last modified:	12/04/01
// purpose: check if a face lies or touches a vertex of
//          the super tetrahedron
//
// arguments: none
//
// return value: none
// ///////////////////////////////////////////////////////////

bool IsTouchingSuperVertices(Face3 *f)
{

	Vertex3 *a[4];

	// get supertetrahedron vertices
	a[0] = Vertex3::GetGlobalVertexList() + (Vertex3::GetGlobalVertexCount()-4);
	a[1] = a[0] + 1;
	a[2] = a[0] + 2;
	a[3] = a[0] + 3;
	

		bool t0 = VERTEX3_IS_EQUALP(a[0],f->V(0))||VERTEX3_IS_EQUALP(a[1],f->V(0))||VERTEX3_IS_EQUALP(a[2],f->V(0))||VERTEX3_IS_EQUALP(a[3],f->V(0));
		bool t1 = VERTEX3_IS_EQUALP(a[0],f->V(1))||VERTEX3_IS_EQUALP(a[1],f->V(1))||VERTEX3_IS_EQUALP(a[2],f->V(1))||VERTEX3_IS_EQUALP(a[3],f->V(1));
		bool t2 = VERTEX3_IS_EQUALP(a[0],f->V(2))||VERTEX3_IS_EQUALP(a[1],f->V(2))||VERTEX3_IS_EQUALP(a[2],f->V(2))||VERTEX3_IS_EQUALP(a[3],f->V(2));

		bool touchingSuperVertices = t0||t1||t2; //||r3;

		return touchingSuperVertices;
}

