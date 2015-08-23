// /////////////////////////////////////////////////
// visdebug.h
//
// author:			Aaron Licata
// creation date:	08/02/01
// last modified:	08/02/01
//
// Visualize the actual geometric data structres for 
// debugging purposes
#ifdef WIN32
	#include <windows.h>
#endif
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "config.h"
#include "math.h"
#include "geom.h"
#include "geomutil.h"
#include "geostat.h"
#include "appio.h"
#include "STL.h"
#include "visdebug.h"



// ///////////////////////////////////////////////////////////
// function: VisualDebug()
//
// creation date:	08/02/01
// last modified:	08/02/01
// purpose: constructor
//
// arguments: none
//
// return value: none
// ///////////////////////////////////////////////////////////

VisualDebug::VisualDebug()
{
	debugTetraListViewScale = 3.0f;
	isVisible = false;
}



// ///////////////////////////////////////////////////////////
// function: SetTetraListViewScale()
//
// creation date:	08/02/01
// last modified:	18/03/01
// purpose: set zoom factor
//
// arguments: none
//
// return value: none
// ///////////////////////////////////////////////////////////

void VisualDebug::SetTetraListViewScale(float scale)
{
	debugTetraListViewScale = scale; 
}



// ///////////////////////////////////////////////////////////
// function: GetTetraListViewScale()
//
// creation date:	08/02/01
// last modified:	08/02/01
// purpose: get zoom factor
//
// arguments: none
//
// return value: none
// ///////////////////////////////////////////////////////////

float VisualDebug::GetTetraListViewScale()
{
	return debugTetraListViewScale;
}




// ///////////////////////////////////////////////////////////
// function: ChooseDebugColor()
//
// creation date:	03/01/01
// last modified:	03/01/01
// purpose: choose debug color
//
// arguments: none
//
// return value: none
// ///////////////////////////////////////////////////////////

void VisualDebug::ChooseDebugColor(float& r, float& g, float& b, Tetrahedron *tetra, int mode)
{
//int max = Tetrahedron::GetCurrentID();
Vertex3 center;
double dist;
		
r = g = b = 0.5;

	switch (mode) 
	{

		case VISUAL_DEBUG_CENTER:	
			center = tetra->Centre();
			dist = center.x*center.x+center.y*center.y+center.z*center.z;
			if (sqrt(dist)< 1.0)
			{
				r = center.x;
				b = center.y;
				g = center.z;
			}
			else
			{
				r = g = b = 0.5;
			}
			break;

		case VISUAL_DEBUG_TETRA_ID:
			int max = Tetrahedron::GetCurrentID();
			float shade = ((float)tetra->GetID())/((float)max);
			r = g = b = shade*shade;
			
			break;
			
		//default:
		 //  r = b = g = 0.5;
		//	break;
	}
}



// ///////////////////////////////////////////////////////////
// function: VisualizeTetraList()
//
// creation date:	03/01/01
// creation date:	03/01/01
// purpose: visualize tetralist
//
// arguments: none
//
// return value: none
// ///////////////////////////////////////////////////////////

void VisualDebug::VisualizeTetraList(TetraList& tetraList, int mode)
{
	if (!IsVisible())
	{
		return;
	}

	TetraList::Itr startIter;
	TetraList::Itr endIter;
	
	startIter = tetraList.Begin();
	endIter = tetraList.End();
	int totalTetras = tetraList.Size();

	// we might switch to a different projection martrix, etc...
	glPushMatrix();
	/*
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   glFrustum(-1.0, 1.0, -1.0, 1.0, 30.0f, 100.0f); 
   glMatrixMode(GL_MODELVIEW);
   glRotatef(0.0f, 1.0f, 0.0f, +270.0f);
   */

	// scale down each tetrahedron so that they can fit in the unit cube
	float scale = debugTetraListViewScale *(float)(1.0f/((float)totalTetras));

	int ith = 0;

	for (; startIter != endIter; startIter++)
	{
		Tetrahedron *tetra = *startIter;

		// distribute tetraheda evenly around the origin
		float param = float((float)ith++/(float)totalTetras); // param in range 0-1
		Vector3 position;
		// create a position vector from -0.5 to +0.5 range
		position.x =  debugTetraListViewScale * 10.0 *(param - 0.5f); 
		position.y = position.z = 0.0f;
#ifdef _DEBUG_STRICT
		assert(tetra != NULL);
#endif
		VisualizeTetrahedron(tetra, position, scale, mode);
	}

	glPopMatrix();
}



// ///////////////////////////////////////////////////////////
// function: VisualizeFaceNeigh()
//
// creation date:	01/09/00
// last modified:	03/10/00
// purpose: visualizer neighbours
//
// arguments: positionl, face id, tetrahedron
//
// return value: none
// ///////////////////////////////////////////////////////////

void VisualDebug::VisualizeFaceNeigh(Vector3& pos, int faceId, Tetrahedron* tetra, Vector3& color, float xmax, float xmin, float ymax, float ymin, float yTetraTop)
{

	float r = color.x;
	float g = color.y;
	float b = color.z;
	
	float midx = (xmax + xmin)/2.0f;

	glPushMatrix();
	glTranslatef(pos.x, pos.y, pos.z);
	glLineWidth(1.7f);
    glBegin(GL_QUADS);
		glColor3f(r-0.1f, g-0.1f, b-0.1f); 
		glVertex3f(xmin, ymax, 0.0f);
		glColor3f(r-0.0f, g-0.0f, b-0.0f); 
		glVertex3f(xmax, ymax, 0.0f);
		glColor3f(r+0.01f, g+0.01f, b+0.01f); 
		glVertex3f(xmax, ymin, 0.0f);
		glColor3f(r+0.1f, g+0.1f, b+0.1f); 
		glVertex3f(xmin, ymin, 0.0f);
	glEnd();
	// bottom arrow 
	glLineWidth(1.0f);
	glBegin(GL_LINES);
		glColor3f(0.9f, 0.9f, 0.9f);
		glVertex3f(midx, yTetraTop, 0.0f);
		glVertex3f(midx, ymin, 0.0f);
	glEnd();
	// top arrow towards neigh 
#ifdef _DEBUG_STRICT
	assert(tetra->F(faceId) != NULL);
#endif
	glBegin(GL_LINES);
		if (tetra->F(faceId)->neigh) // got neighbour: red and long
		{
			glLineWidth(1.3f);
			glColor3f(1.0f, 0.0f, 0.0f);
			glVertex3f(midx, ymax, 0.0f);
			glVertex3f(midx, ymax+(ymax-ymin), 0.0f);
		}
		else // no neighbour: gray and short
		{
			glLineWidth(1.0f);
			glColor3f(0.4f, 0.4f, 0.4f);
			glVertex3f(midx, ymax, 0.0f);
			glVertex3f(midx, ymax+(ymax-ymin)/2, 0.0f);
		}
	glEnd();
	// link to neibouring tetrahedron
	// draw a link from face pointer to ceter of neigh tetra
	if (tetra->F(faceId)->neigh)
	{
		glBegin(GL_LINES);
			glLineWidth(1.3f);
			glColor3f(1.0f, 0.0f, 0.0f);
			glVertex3f(midx, ymax+(ymax-ymin), 0.0f);
			float shade = (float)tetra->F(faceId)->neigh->GetID()
				/ (float)(Tetrahedron::GetCurrentID());
			glColor3f(1.0f, shade, shade);
			Vertex3 c = tetra->F(faceId)->neigh->Centre();
			glVertex3f(c.x, c.y, c.z);
		glEnd();
			glPopMatrix();
	}
	else // no link (external face?)
	{
			glPopMatrix();
		glPushMatrix();
		glPointSize(6.0);
		glBegin(GL_POINTS);
			glColor3f(0.0f, 1.0f, 0.3f);
			glVertex3f(midx, ymax+(ymax-ymin), 0.0f);
		glEnd();
		glPopMatrix();
	}	

}



// ///////////////////////////////////////////////////////////
// function: VisualizeTetraNeigh()
//
// creation date:	01/09/00
// last modified:	03/10/00
// purpose: visualize tetrahedron neighbour
//
// arguments: none
//
// return value: none
// ///////////////////////////////////////////////////////////

void VisualDebug::VisualizeTetraNeigh(Vector3& pos, Tetrahedron* tetra, Vector3& color, float scale, int mode)
{


	float xmax;
	float xmin;
	float ymax = +0.9f;
	float ymin = +0.6f;
	float yTetraTop = +0.5;
	int faceId;

	// overwrite color
	color.x = 0.6;
	color.y = 0.6;
	color.z = 0.6;


	// face 0 (left)
	xmax = -0.2f;
	xmin = -0.4f;
	faceId = 0;
	VisualizeFaceNeigh(pos, faceId, tetra, color, xmax, xmin, ymax, ymin, yTetraTop);
	// face 1 (center left)
	xmax = -0.0f;
	xmin = -0.2f;
	faceId = 1;
	VisualizeFaceNeigh(pos, faceId, tetra, color, xmax, xmin, ymax, ymin, yTetraTop);
	// face 2 (center right)
	xmax = +0.2f;
	xmin = +0.0f;
	faceId = 2;
	VisualizeFaceNeigh(pos, faceId, tetra, color, xmax, xmin, ymax, ymin, yTetraTop);
	// face 3 (right)
	xmax = +0.4f;
	xmin = +0.2f;
	faceId = 3;
	VisualizeFaceNeigh(pos, faceId, tetra, color, xmax, xmin, ymax, ymin, yTetraTop);
}



// ///////////////////////////////////////////////////////////
// function: VisualizeTetrahedron()
//
// creation date:	01/09/00
// last modified:	03/10/00
// purpose: visualize tetrahedron
//
// arguments: none
//
// return value: none
// ///////////////////////////////////////////////////////////

void VisualDebug::VisualizeTetrahedron(Tetrahedron* tetra, Vector3& pos, float tetraDim, int mode)
{
	glPushMatrix();

	glTranslatef(pos.x, pos.y, pos.z);
	glScalef(tetraDim, tetraDim, tetraDim);

	glPolygonMode(GL_FRONT,GL_FILL);
	glPolygonMode(GL_BACK,GL_FILL);
	glDisable(GL_CULL_FACE);
	glLineWidth(2.0);

	float r, g, b;

	ChooseDebugColor(r, g, b, tetra, mode);

	glBegin(GL_QUADS);
		glColor3f(r-0.1f, g-0.1f, b-0.1f); 
		glVertex3f(-0.5f, +0.5f, 0.0f);
		glColor3f(r-0.0f, g-0.0f, b-0.0f); 
		glVertex3f(+0.5f, +0.5f, 0.0f);
		glColor3f(r+0.01f, g+0.01f, b+0.01f); 
		glVertex3f(+0.5f, -0.5f, 0.0f);
		glColor3f(r+0.1f, g+0.1f, b+0.1f); 
		glVertex3f(-0.5f, -0.5f, 0.0f);
	glEnd();

	float neighScale = 1.0;
	Vector3 color;

	color.x = r;
	color.y = g;
	color.z = b; 
	glPopMatrix();
	VisualizeTetraNeigh(pos, tetra, color, neighScale, mode);

	glEnable(GL_CULL_FACE);
}


