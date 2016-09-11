// /////////////////////////////////////////////////
// visualize.h
//
// author:			Aaron Licata
// creation date:	01/02/01
// last modified:	01/02/01
//
// Visualize the geometrical structres 
//

#ifndef VISUALIZE_GEOMETRY_H
#define VISUALIZE_GEOMETRY_H

#include "config.h"
#include "math.h"
#include "geom.h"
#include "geomutil.h"

const int GV_POINTS = 0;
const int GV_WIRE = 1;
const int GV_FLATSOLID = 2;
const int GV_SMOOTHSHADING = 4;
const int GV_WIREANDSHADE = 8;


// ////////////////////////////////////////////////////////////////
// class GeometryVisualizer 
//
// author:		Aaron Licata
// creation date:	30/01/01
// last modified:	22/04/01
//
// purpose: opengl visualisation module
//
// /////////////////////////////////////////////////////////////////

class GeometryVisualizer 
{
public:
	GeometryVisualizer();
	void DrawMaxBox3(BoundBox3& box);
	void DrawTetrahedron(Tetrahedron *tetra, int mode);
	void DrawWireTetrahedron(Tetrahedron *tetra);
	void DrawShadedTetrahedron(Tetrahedron *tetra);
	void DrawSuperTetrahedron(SuperTetra &superTetra);
	void DrawVoronoi(Tetrahedron *tetra, int mode);
	void DrawVoronoiCell(int pointIndex);
	void DrawTetraList(TetraList& tetraList, int mode);
	void DrawCircumSphere(Tetrahedron* tetra);
	void DrawDataSet3(Skeleton *obj);
	void DrawVertexNormal(int vertexId);
	void DrawVertexNormals();
	void DrawFaceNormal(Face3 *face);
	void DrawFaceNormals(TetraList& tetraList);
	void DrawFaceArray(unsigned long *faceArray, long faceCount);
	void DrawWireFaceArray(unsigned long *faceArray, long faceCount);
	void DrawShadedFaceArray(unsigned long *faceArray, long faceCount);

	void DrawGrid();
	void DrawBackgroundPlane();
	void DrawCoordinateSystem();
	void DrawBackground();

	void SetMaxSquareRadius(double m) { maxSquareRadius = m; }
	void SetAlphaShapeParameter(double dRadius) { alphaSquareRadius = dRadius; }
	double GetMaxSquareRadius() { return maxSquareRadius; }

	bool IsVisibleMaxBox3() { return isVisibleMaxBox3; }
	bool IsVisibleSemiArbitraryFaces() { return isVisibleSemiArbitraryFaces;}
	bool IsVoronoiCenterVisible() { return isVoronoiCenterVisible; }
	bool IsVisibleTetrahedra() { return isVisibleTetrahedra;}
	bool IsVisibleSuperTetrahedron() { return isVisibleSuperTetra; }
	bool IsVisibleVoronoi() { return isVisibleVoronoi;}
	bool IsVisibleVoronoiVertex() {return isVisibleVoronoiVertex;}
	bool IsVisibleDataSet3() { return isVisibleDataSet3; }
	bool IsVisibleVoronoiCell() {return isVisibleVoronoiCell;}
	bool IsVisibleOnlyConvexHull() { return isVisibleOnlyConvexHull; }
	bool IsVisibleCircumSphere() { return isVisibleCircumSphere; }
	bool IsVisibleVertexNormal() { return isVisibleVertexNormal; }

	bool IsVisibleFaceNormal() { return isVisibleFaceNormal; }

	bool IsVisibleBackgroundPlane() { return isVisibleBackgroundPlane; }
	bool IsVisibleGrid() { return isVisibleGrid; }
	bool IsVisibleBackground() { return isVisibleBackground; }
	bool IsVisibleCoordinateSystem() { return isVisibleCoordinateSystem; }
	bool IsVisibleLighting() { return isVisibleLighting; }

	void SetVisibleMaxBox3(bool state) { isVisibleMaxBox3 = state; }
	void SetVisibleSemiArbitraryFaces(bool state) { isVisibleSemiArbitraryFaces = state;}
	void SetVoronoiCenterVisible(bool state) { isVoronoiCenterVisible = state; }
	void SetVisibleTetrahedra(bool state) { isVisibleTetrahedra = state;}
	void SetVisibleSuperTetrahedron(bool state) { isVisibleSuperTetra = state; }
	void SetVisibleVoronoi(bool state) { isVisibleVoronoi = state;}
	void SetVisibleVoronoiVertex(bool state) { isVisibleVoronoiVertex = state; }
	void SetVisibleDataSet3(bool state) { isVisibleDataSet3 = state; }
	void SetVisibleVoronoiCell(bool state) { isVisibleVoronoiCell = state; }
	void SetVisibleOnlyConvexHull(bool state) { isVisibleOnlyConvexHull = state; }
	void SetVisibleCircumSphere(bool state) { isVisibleCircumSphere = state ; }
	void SetVisibleVertexNormal(bool state) { isVisibleVertexNormal = state ; }
	void SetVisibleFaceNormal(bool state) { isVisibleFaceNormal = state; }

	void SetVisibleGrid(bool state) { isVisibleGrid = state; }
	void SetVisibleBackground(bool state) { isVisibleBackground = state; }
	void SetVisibleCoordinateSystem(bool state) { isVisibleCoordinateSystem = state; }
	void SetVisibleBackgroundPlane(bool state) { isVisibleBackgroundPlane = state; }
	void SetVisibleLighting(bool state) { isVisibleLighting = state; }

	void SetBackgroundColor(int selection) { backgroundColor = selection;}
	void SetPolygonMode(int mode) { polygonMode = mode; }
	void SetAlphaParamDirection(int dir) { alphaParamDirection = dir; }
	void SetBottomOfBox(double b) { bottomOfBox = b; }
	void SetNormalFactor(double factor) { normalFactor = factor; }

	int GetBackgroundColor() { return backgroundColor; }
	int GetPolygonMode() { return polygonMode; }
	int GetAlphaParamDirection() { return alphaParamDirection; }
	double GetBottomOfBox() { return bottomOfBox; }
	double GetNormalFactor() { return normalFactor; }

	void InitializeContext();

private:
	bool isVisibleMaxBox3;
	bool isVisibleSemiArbitraryFaces;
	bool isVoronoiCenterVisible;
	bool isVisibleTetrahedra;
	bool isVisibleSuperTetra;
	bool isVisibleVoronoi;
	bool isVisibleVoronoiVertex;
	bool isVisibleMaxBox;
	bool isVisibleDataSet3;
	bool isVisibleVoronoiCell;
	bool isVisibleOnlyConvexHull;
	bool isVisibleCircumSphere;
	bool isVisibleVertexNormal;
	bool isVisibleFaceNormal;

	bool isVisibleBackground;
	bool isVisibleGrid;
	bool isVisibleCoordinateSystem;
	bool isVisibleBackgroundPlane;
	bool isVisibleLighting;

	int polygonMode;

	int alphaParamDirection;
	double maxSquareRadius; 
	double alphaSquareRadius;
	double normalFactor;
	int backgroundColor;

	double bottomOfBox;
};


bool IsSuperVertex(Face3 *f);
bool IsTouchingSuperVertices(Face3 *f);

#endif

