// /////////////////////////////////////////////////
// visdebug.h
//
// author:			Aaron Licata
// creation date:	08/02/01
// last modified:	08/02/01
//
// Visualize the actual geometric data structres for 
// debugging purposes

#ifndef VISUAL_DEBUG_H
#define VISUAL_DEBUG_H

#define VISUAL_DEBUG_CENTER 1
#define VISUAL_DEBUG_TETRA_ID 2

#include "geom.h"
#include "geomutil.h"


// ////////////////////////////////////////////////////////////////
// class VisualDebug
//
// author:		Aaron Licata
// creation date:	30/08/00
// last modified:	22/04/01
//
// purpose: class to visualized the internals of geometrical
// data structure MTIN (Minimal Tetrahedralisation Network)
//
// /////////////////////////////////////////////////////////////////
class VisualDebug
{
public:
	// Visual Debugging
	VisualDebug();
	void VisualizeTetraList(TetraList& tetraList, int mode);
	void SetTetraListViewScale(float scale);
	float GetTetraListViewScale();
	bool IsVisible() { return isVisible; }
	void SetVisualizer(bool state) { isVisible = state; }

private:
	void VisualizeFaceNeigh(Vector3& pos, int faceId, Tetrahedron* tetra, Vector3& color, float xmax, float xmin, float ymax, float ymin, float yTetraTop);
	void VisualizeTetraNeigh(Vector3& pos, Tetrahedron* tetra, Vector3& color, float scale, int mode);
	void VisualizeTetrahedron(Tetrahedron* tetra, Vector3& pos, float tetraDim, int mode);
	void ChooseDebugColor(float& r, float& g, float& b, Tetrahedron *tetra, int mode);

private:
	float debugTetraListViewScale;
	bool isVisible;
};

#endif
