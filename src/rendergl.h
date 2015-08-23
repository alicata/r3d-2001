// ///////////////////////////////////////////////////////////
// file name: rendergl.h//
// author:			Aaron Licata
// creation date:	28/02/01
// last modified:	28/02/01
// version number:	1
//
// description: opengl redering interface
//
// ///////////////////////////////////////////////////////////

#ifndef OPENGL_RENDERER_H
#define OPENGL_RENDERER_H

#include <GL/gl.h>

#include "geom.h"
#include "visualize.h"
#include "visdebug.h"



// ////////////////////////////////////////////////////////////////
// class Viewport
//
// author:		Aaron Licata
// creation date:	30/10/00
// last modified:	22/04/01
//
// purpose: class representing the viewport
//
// /////////////////////////////////////////////////////////////////
struct Viewport
{
	GLfloat width;
	GLfloat height;
};

// ////////////////////////////////////////////////////////////////
// class Viewvolume
//
// author:		Aaron Licata
// creation date:	30/10/00
// last modified:	22/04/01
//
// purpose: class representing the viewport
//
// /////////////////////////////////////////////////////////////////class ViewingVolume
class ViewingVolume
{
public:
	ViewingVolume() { zNear = zFar = fov = aspect = left = right = bottom = top = 0.0; }

public:
	GLdouble zNear;
	GLdouble zFar;
	
	// mothod1
	GLdouble fov;
	GLdouble aspect;

	// method2
	GLdouble left;		
	GLdouble right;	
	GLdouble bottom;
	GLdouble top;	

};



// ////////////////////////////////////////////////////////////////
// class Camera
//
// author:		Aaron Licata
// creation date:	30/10/00
// last modified:	22/04/01
//
// purpose: class representing the OpenGL camera
//
// /////////////////////////////////////////////////////////////////

struct Camera
{
	Vector3 pos;	// eye position
	Vector3 at;		// reference point (target)
	Vector3 up;		// up vector
	Vector3 rot;	// added rotation angle

};



// ////////////////////////////////////////////////////////////////
// class VisualContext 
//
// author:		Aaron Licata
// creation date:	30/10/00
// last modified:	22/04/01
//
// purpose: class representing the OpenGL VisualContext 
//
// /////////////////////////////////////////////////////////////////

class VisualContext 
{
public:
	VisualContext() { sampleId = 0; obj = NULL; }
	~VisualContext() {  tetraList.DeleteAll(); }
	void Clear() { tetraList.DeleteAll(); }
public:
	Camera camera;
	ViewingVolume viewVolume;
	Viewport viewport;

	BoundBox3 box;
	SuperTetra superTetra;
	VisualDebug visualDebugger;

	GeometryVisualizer visualizer;
	int sampleId;
	TetraList tetraList;
	Skeleton *obj;
};


void GLInitialize(VisualContext& vc);
void GLRender(VisualContext& vc);
void GLIdle(VisualContext& vc);
void GLResize(VisualContext& vc, int width, int height);
void ToggleGLIdlePause();

#endif

