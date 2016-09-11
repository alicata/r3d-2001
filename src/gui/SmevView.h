// SmevView.h : interface of the CSmevView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SMEVVIEW_H__5FDFFB6F_5F81_11D2_935C_88E504C10000__INCLUDED_)
#define AFX_SMEVVIEW_H__5FDFFB6F_5F81_11D2_935C_88E504C10000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "math.h"
#include "delaunay.h"
#include "crust.h"
#include "rendergl.h"


#include "SmevDoc.h"


const int LOCATION_FRONT = 0;
const int LOCATION_TOP = 1;
const int LOCATION_SIDE = 2;
const int LOCATION_NEAR = 3;
const int LOCATION_FAR = 4;
const int LOCATION_INSIDE = 5;
const int LOCATION_FOLLOWPOLES = 6;


extern enum RenderSpecsEnumType
{
	APP_PERSPECTIVE,
	APP_ORTHO,
	APP_VERTEXONLY,
	APP_WIREFRAME, 
	APP_SOLID,
	APP_FLAT, 
	APP_GOURAUD, 
	APP_PHONG, 
	APP_TEXTURE,

	// reconstruction state
	APP_EMPTY,
	APP_POINTSET,
	APP_DELAUNAY,
	APP_VORONOI,
	APP_NEIGH_LINKS,
	APP_MEDIAL_AXIS,
	APP_CRUST,
	APP_2D_MANIFOLD

} RenderSpecs_123456;


class CViewSpecs
{
public:
	float nearPlane;
	float farPlane;
	Vector3 pos;		// input position
	Vector3 angle;		// input rotation angle
	Vector3 axis;		// input rotation axis
	Vector3 scale;		// input scale
	GLdouble ratio;

	int projectionType;

	bool useBoundingBox;
	bool useGrid;
	int renderingType;
	int reconState;

	CRect orgRect;
	
	CViewSpecs() 
	{
		nearPlane = 1.0f;
		farPlane = 100.0f;
		pos.Set(0.0,0.0,0.0);
		angle.Set(0.0,0.0,0.0);
		axis.Set(0.0,0.0,0.0);
		scale.Set(0.0,0.0,0.0);
		ratio = 1.0;
		projectionType = 0;

		useBoundingBox = false;
		useGrid = true;
		renderingType = GV_POINTS;
		reconState = APP_EMPTY; 
	}
};

class CSmevView : public CView
{
protected: // create from serialization only
	CSmevView();
	DECLARE_DYNCREATE(CSmevView)

// Attributes
public:
	CSmevDoc* GetDocument();

	CPalette    m_cPalette;
    CPalette    *m_pOldPalette;
	CRect		m_oldRect;
	CClientDC	*m_pDC;

	// mouse control
	CPoint m_MousePos;
	CPoint m_DragPos;
	int m_nActiveChoice;	// which mouse choice is still active
	BOOL m_Dragging;		// still dragging moud

	GLfloat m_Grab_Rot_X;
	GLfloat m_Grab_Rot_Y;
	GLfloat m_Grab_Rot_Z;

	GLfloat m_Grab_Trans_X;
	GLfloat m_Grab_Trans_Y;
	GLfloat m_Grab_Trans_Z;

	// camera control
	int m_cameraLocation;

	// rendering
	CViewSpecs m_vs;
	VisualContext m_vc;

	// geometry
	DelaunayTetrahedralizer m_tetrahedralizer;
	VoronoiTessellator m_tessellator;
	MedialAxisTransformer m_medialAxisTransformer;
	CrustExtractor m_crustExtractor;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSmevView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	
	void IntroductionMessage();
	void UpdateCameraLocation(int nLocation);

	void UpdateVisualContext();
	BOOL m_bRButtonDown;
	int m_nBackgroundColor;
	void SetAlphaShapeParameter(double dRadius);
	int m_nAlphaShapeValue;
	void DeleteAll();
	BOOL _SetPixelFormat(void);
	void _CreateRGBPalette(void);
	void _DrawScene();
	void _InitializeGL();
	virtual ~CSmevView();
	void InitVertexArray();

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CSmevView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnCheckdelaunay();
	afx_msg void OnDoubleclickedCheckdelaunay();
	afx_msg void OnCheckconvexhull();
	afx_msg void OnCheckPointCloud();
	afx_msg void OnCheckVoroCell();
	afx_msg void OnCheckVoronoiBall();
	afx_msg void OnCheckvorodiagram();
	afx_msg void OnCheckvoronoivertices();
	afx_msg void OnAnalysisStatistics();
	afx_msg void OnButtonCameraRotateXCcw();
	afx_msg void OnButtonCameraRotateXCw();
	afx_msg void OnButtonCameraRotateYCcw();
	afx_msg void OnButtonCameraRotateYCw();
	afx_msg void OnButtonCameraTback();
	afx_msg void OnButtonCameraTfront();
	afx_msg void OnButtonCameraTleft();
	afx_msg void OnButtonCameraTright();
	afx_msg void OnButtonVoronoiCell();
	afx_msg void OnButtonVoronoiNextSample();
	afx_msg void OnButtonVoronoiPrevSample();
	afx_msg void OnButtonVoronoiVertices();
	afx_msg void OnCheckVertexNormal();
	afx_msg void OnToolsRandomize();
	afx_msg void OnViewGrid();
	afx_msg void OnViewPointcloud();
	afx_msg void OnViewSmootShading();
	afx_msg void OnViewWireframe();
	afx_msg void OnViewWireShading();
	afx_msg void OnViewFlatSolid();
	afx_msg void OnViewBoundingBox();
	afx_msg void OnUpdateViewPointcloud(CCmdUI* pCmdUI);
	afx_msg void OnUpdateViewWireframe(CCmdUI* pCmdUI);
	afx_msg void OnUpdateViewFlatsolid(CCmdUI* pCmdUI);
	afx_msg void OnUpdateViewSmootShading(CCmdUI* pCmdUI);
	afx_msg void OnUpdateViewWireShading(CCmdUI* pCmdUI);
	afx_msg void OnUpdateViewGrid(CCmdUI* pCmdUI);
	afx_msg void OnUpdateViewBoundingBox(CCmdUI* pCmdUI);
	afx_msg void OnReconstruction3Dsr();
	afx_msg void OnReconDelaunay();
	afx_msg void OnReconVoronoi();
	afx_msg void OnFileImportNative();
	afx_msg void OnFileImportPt2File();
	afx_msg void OnVisualDebugger();
	afx_msg void OnUpdateVisualDebugger(CCmdUI* pCmdUI);
	afx_msg void OnAlphaShape();
	afx_msg void OnLocation();
	afx_msg void OnViewGroundPlane();
	afx_msg void OnUpdateViewGroundPlane(CCmdUI* pCmdUI);
	afx_msg void OnViewCoordinateSystem();
	afx_msg void OnUpdateViewCoordinateSystem(CCmdUI* pCmdUI);
	afx_msg void OnToolsOption();
	afx_msg void OnToolsFlaggedTetra();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnReconMedialAxis();
	afx_msg void OnReconCalculateVertexNormals();
	afx_msg void OnViewSuperTetrahedron();
	afx_msg void OnUpdateViewSuperTetrahedron(CCmdUI* pCmdUI);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnViewLightToggle();
	afx_msg void OnUpdateViewLightToggle(CCmdUI* pCmdUI);
	afx_msg void OnFileNew();
	afx_msg void OnToolsFlipVertexNormals();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in SmevView.cpp
inline CSmevDoc* CSmevView::GetDocument()
   { return (CSmevDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SMEVVIEW_H__5FDFFB6F_5F81_11D2_935C_88E504C10000__INCLUDED_)
