// ///////////////////////////////////////////////////////////
// file name: rendergl.cpp
//
// author:			Aaron Licata
// creation date:	28/02/01
// last modified:	28/02/01
// version number:	1
//
// description: opengl redering implementation module
//
// ///////////////////////////////////////////////////////////

#include "config.h"
#ifdef WIN32
	#include <windows.h>
#endif

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <stdio.h>
#include <stdlib.h>
#include "math.h"
#include "geom.h"
#include "geomutil.h"
#include "delaunay.h"
#include "visualize.h"
#include "visdebug.h"
#include "STL.h"

#include "rendergl.h"


int pause;

// ///////////////////////////////////////////////////////////
// function: GLInitialize()
//
// creation date:	11/01/01
// last modified:	11/01/01
// purpose: initialize openGL state machine using a visual context
// arguments: visual context object
//
// return value: none
// ///////////////////////////////////////////////////////////

void GLInitialize(VisualContext& vc)
{

	GLfloat ambient[] = { 0.4f, 0.4f, 0.3f, 1.0f };
	GLfloat diffuse[] = { 0.7, 0.7, 0.5, 1.0 };
	GLfloat specular[] = { 0.3, 0.4, 0.4, 1.0 };
	GLfloat lightpos[] = { 0.5, 0.4, 1.0, 0.0 };
///////////////////////////////////////////////////////////////////////////////



    glClearDepth(1.0);
    glDepthFunc(GL_LESS);
    glShadeModel(GL_SMOOTH);

    glEnable(GL_DEPTH_TEST);

    
	//////////////Establish viewing volume: method1 ///////////
	/*
	assert(vc.viewport.width != 0 && vc.viewport.height != 0);

	vc.viewVolume.fov = 60.0;
	vc.viewVolume.aspect = vc.viewport.width / vc.viewport.height;
	vc.viewVolume.zNear = 1;
	vc.viewVolume.zFar = 2000;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(
		vc.viewport.fov, 
		vc.viewport.aspect,
		vc.viewport.zNear, 
		vc.viewport.zFar); 
		*/
	// ////////////////////////////////////////////////////////

	// /////////// Establish viewing volume: method2 //////////
	vc.viewVolume.left		= -2.0;
	vc.viewVolume.right		= +2.0;
	vc.viewVolume.bottom	= -2.0;
	vc.viewVolume.top		= +2.0;
	vc.viewVolume.zNear		= +0.5;		// must be positive
	vc.viewVolume.zFar		= +100.0;	// must be positive
	
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	glFrustum(
		vc.viewVolume.left,			
		vc.viewVolume.right,
		vc.viewVolume.bottom,	
		vc.viewVolume.top,		
		vc.viewVolume.zNear	,	
		vc.viewVolume.zFar);		
	// ////////////////////////////////////////////////////////
	
    

	// SET SOME OGL INITIAL STATES SO THEY ARE NOT DONE IN THE DRAW LOOP
	glMatrixMode(GL_MODELVIEW);
//	glPolygonMode(GL_FRONT,GL_FILL);
	glPolygonMode(GL_FRONT,GL_LINE);
	glDepthFunc(GL_LESS);
    glEnable(GL_CULL_FACE);
	glHint(GL_LINE_SMOOTH_HINT,GL_FASTEST);
	glDisable(GL_TEXTURE_2D);


	// lighting 	
	glMaterialfv(GL_FRONT,GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT,GL_SPECULAR, specular);
	glMaterialf(GL_FRONT,GL_SHININESS, 12.0f);
	glLightfv(GL_LIGHT0,GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_POSITION, lightpos);
	glDisable(GL_LIGHTING);
	glEnable(GL_LIGHT0);


   glClearColor (0.0, 0.0, 0.0, 0.0);
   glShadeModel (GL_SMOOTH);
   glEnable(GL_DEPTH_TEST); 
   glFrontFace(GL_CCW);

	vc.camera.pos.Set(0.0, 0.0, -3.0);
	vc.camera.rot.Set(340.0, 250.0, 0.0);
	vc.camera.at.Set(0.0, 0.0, 0.0);
	vc.camera.up.Set(0.0, 1.0, 0.0);
	vc.sampleId = 0;

	pause = 0;
}



// ///////////////////////////////////////////////////////////
// function: GLRender()
//
// creation date:	11/01/01
// last modified:	11/01/01
// purpose: render openGL scene
// arguments: visual context object
//
// return value: none
// ///////////////////////////////////////////////////////////

void GLRender(VisualContext& vc)
{
	if (vc.visualizer.GetBackgroundColor() == 0)
	{
		glClearColor (1.0, 1.0, 1.0, 0.0);
	}
	else if (vc.visualizer.GetBackgroundColor() == 1)
	{
		glClearColor (0.55, 0.55, 0.55, 0.0);
	}
	else if (vc.visualizer.GetBackgroundColor() == 2)
	{
		glClearColor (0.4, 0.4, 0.99, 0.0);
	}
	else 
	{
		glClearColor (0.0, 0.0, 0.0, 0.0);
	}

    glDisable(GL_DEPTH_TEST);	// TURN OFF DEPTH TEST FOR CLEAR

    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);

    glColor3f (1.0, 0.0, 0.0);  
    //glEnable(GL_COLOR_MATERIAL);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glLoadIdentity();
	gluLookAt(vc.camera.pos.x, vc.camera.pos.y, vc.camera.pos.z, 
				vc.camera.at.x, vc.camera.at.y, vc.camera.at.z, 
				vc.camera.up.x, vc.camera.up.y, vc.camera.up.z);

    glRotatef(vc.camera.rot.x, 1, 0, 0);
    glRotatef(vc.camera.rot.y, 0, 1, 0);
    glRotatef(vc.camera.rot.z, 0, 0, 1);

	glPushMatrix();

	if (Vertex3::GetGlobalVertexCount() > 0)
	{
 	vc.visualizer.DrawMaxBox3(vc.box);
	vc.visualizer.DrawVoronoiCell(vc.sampleId);
	vc.visualizer.DrawDataSet3(vc.obj);
	vc.visualizer.DrawTetraList(vc.tetraList, 0);
	vc.visualizer.DrawSuperTetrahedron(vc.superTetra);
	vc.visualizer.DrawVertexNormals();
	vc.visualizer.DrawFaceNormals(vc.tetraList);

	vc.visualizer.DrawFaceArray((unsigned long *)vc.obj->faceIndex, (unsigned long)vc.obj->faceCount);

	vc.visualDebugger.VisualizeTetraList(vc.tetraList,  VISUAL_DEBUG_TETRA_ID); // VISUAL_DEBUG_TETRA_ID;
	}
	vc.visualizer.DrawGrid();
	vc.visualizer.DrawBackgroundPlane();  
	vc.visualizer.DrawCoordinateSystem();
	


	glPopMatrix();
}



// ///////////////////////////////////////////////////////////
// function: GLIdle()
//
// creation date:	11/01/01
// last modified:	11/01/01
// purpose: work to be done by OpenGL when the application loop
//          is idle: good for real-time graphics 
// arguments: visual context object
//
// return value: none
// ///////////////////////////////////////////////////////////

void GLIdle(VisualContext& vc)
{

	if (pause) { return; }
     
	/*
	if (!interactive) { return; }

	if (insertPoint > Vertex3::GetGlobalVertexCount()) return;

	if (insertPoint == 0)
	{
		// PHASE1: build super tetrahedron
		Tetrahedron *super;
		super = CreateSuperTetrahedron(Vertex3::GetGlobalVertexList(), Vertex3::GetGlobalVertexCount());
		tetraList.Add(super);
	#ifdef _DEBUG_STRICT
		int TETRALIST_SIZE_AFTER_SUPERTETRA_IS_NOT_POSITIVE = ((int)tetraList.Size()>0);
		assert(TETRALIST_SIZE_AFTER_SUPERTETRA_IS_NOT_POSITIVE);
	#endif
	}

	if (insertPoint < Vertex3::GetGlobalVertexCount())
	{
		// PHASE2: build Delaunay terahedralization
		// find ball-seeded tetrahedra
		list<Face3 *> tempFaceList;	
		FlagAndDeleteBallSeededTetrahedra(tetraList, insertPoint,  tempFaceList);	
		RetainSinglyOccurringFaces(tempFaceList);
		CreateTetrahedronFrom4FacesAndPoint(tempFaceList, insertPoint, tetraList);
	}

	if (insertPoint == Vertex3::GetGlobalVertexCount())
	{
		// PHASE3: eliminate boundary tetrahedra
		DeleteArbitraryBoundaryFaces(tetraList);

		// PHASE4: Voronoi tessellation
		BuildVoronoiTessellation(tetraList);
	}

	// advance to next reconstruction frame
	insertPoint++;

	display();
	*/
}



// ///////////////////////////////////////////////////////////
// function: GLResize()
//
// creation date:	11/01/01
// last modified:	11/01/01
// purpose: resize 
//          is idle: good for real-time graphics 
// arguments: visual context object
//
// return value: none
// ///////////////////////////////////////////////////////////

void GLResize(VisualContext& vc)
{
	glViewport (0, 0, vc.viewport.width, vc.viewport.height);
	
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	glFrustum(
		vc.viewVolume.left,			
		vc.viewVolume.right,
		vc.viewVolume.bottom,	
		vc.viewVolume.top,		
		vc.viewVolume.zNear	,	
		vc.viewVolume.zFar);	
	glMatrixMode(GL_MODELVIEW);
}




// ///////////////////////////////////////////////////////////
// function: ToggleGLIdlePause()
//
// creation date:	11/01/01
// last modified:	11/01/01
// purpose: pause/unpause the idle loop
//        
// arguments: visual context object
//
// return value: none
// ///////////////////////////////////////////////////////////

void ToggleGLIdlePause()
{
	pause = !pause;
}
