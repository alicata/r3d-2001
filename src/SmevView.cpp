// SmevView.cpp : implementation of the CSmevView class
//

#include "stdafx.h"


#include <gl\gl.h>
#include <gl\glu.h>
//#include <gl\glaux.h>


#include "rabdata.h"
#include "rendergl.h"
#include "filept2.h"
#include "geom.h"
#include "geomutil.h"
#include "delaunay.h"
#include "crust.h"

#include "Smev.h"
#include "SmevDoc.h"

#include "SmevView.h"
#include "DlgIntro.h"

#include "DialogRandomizer.h"
#include "DialogAlphaShape.h"
#include "DialogOptions.h"
#include "DlgLocation.h"
#include "DlgReconProcess.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define ROTATE_SPEED		0.2f		// SPEED OF ROTATION
#define TRANSLATE_SPEED		0.05f	// speed of translation

const int MC_NONE = 0;
const int MC_ROT_Y_AXIS = 1;
const int MC_ROT_X_AXIS = 2;
const int MC_TRANS_X_AXIS = 3;
const int MC_TRANS_Y_AXIS = 4;
const int MC_TRANS_Z_AXIS = 5;

UINT WorkerThreadTetrahedralizer(LPVOID pParam);

/////////////////////////////////////////////////////////////////////////////
// CSmevView

IMPLEMENT_DYNCREATE(CSmevView, CView)

BEGIN_MESSAGE_MAP(CSmevView, CView)
	//{{AFX_MSG_MAP(CSmevView)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
	ON_WM_TIMER()
	ON_WM_KEYDOWN()
	ON_BN_CLICKED(IDC_CHECKDELAUNAY, OnCheckdelaunay)
	ON_BN_DOUBLECLICKED(IDC_CHECKDELAUNAY, OnDoubleclickedCheckdelaunay)
	ON_BN_CLICKED(IDC_CHECKCONVEXHULL, OnCheckconvexhull)
	ON_BN_CLICKED(IDC_CHECKPOINTCLOUD, OnCheckPointCloud)
	ON_BN_CLICKED(IDC_CHECKVOROCELL, OnCheckVoroCell)
	ON_BN_CLICKED(IDC_CHECKVORONOIBALL, OnCheckVoronoiBall)
	ON_BN_CLICKED(IDC_CHECKVORODIAGRAM, OnCheckvorodiagram)
	ON_BN_CLICKED(IDC_CHECKVORONOIVERTICES, OnCheckvoronoivertices)
	ON_COMMAND(ID_ANALYSIS_STATISTICS, OnAnalysisStatistics)
	ON_COMMAND(ID_BUTTON_CAMERA_ROTATE_X_CCW, OnButtonCameraRotateXCcw)
	ON_COMMAND(ID_BUTTON_CAMERA_ROTATE_X_CW, OnButtonCameraRotateXCw)
	ON_COMMAND(ID_BUTTON_CAMERA_ROTATE_Y_CCW, OnButtonCameraRotateYCcw)
	ON_COMMAND(ID_BUTTON_CAMERA_ROTATE_Y_CW, OnButtonCameraRotateYCw)
	ON_COMMAND(ID_BUTTON_CAMERA_TBACK, OnButtonCameraTback)
	ON_COMMAND(ID_BUTTON_CAMERA_TFRONT, OnButtonCameraTfront)
	ON_COMMAND(ID_BUTTON_CAMERA_TLEFT, OnButtonCameraTleft)
	ON_COMMAND(ID_BUTTON_CAMERA_TRIGHT, OnButtonCameraTright)
	ON_COMMAND(ID_BUTTON_VORONOI_CELL, OnButtonVoronoiCell)
	ON_COMMAND(ID_BUTTON_VORONOI_NEXT_SAMPLE, OnButtonVoronoiNextSample)
	ON_COMMAND(ID_BUTTON_VORONOI_PREV_SAMPLE, OnButtonVoronoiPrevSample)
	ON_COMMAND(ID_BUTTON_VORONOI_VERTICES, OnButtonVoronoiVertices)
	ON_BN_CLICKED(IDC_CHECKVERTNORMAL, OnCheckVertexNormal)
	ON_COMMAND(ID_TOOLS_RANDOMIZE, OnToolsRandomize)
	ON_COMMAND(ID_VIEW_GRID, OnViewGrid)
	ON_COMMAND(ID_VIEW_POINTCLOUD, OnViewPointcloud)
	ON_COMMAND(ID_VIEW_SMOOTSHADING, OnViewSmootShading)
	ON_COMMAND(ID_VIEW_WIREFRAME, OnViewWireframe)
	ON_COMMAND(ID_VIEW_WIRESHADING, OnViewWireShading)
	ON_COMMAND(ID_VIEW_FLATSOLID, OnViewFlatSolid)
	ON_COMMAND(ID_VIEW_BOUNDING_BOX, OnViewBoundingBox)
	ON_UPDATE_COMMAND_UI(ID_VIEW_POINTCLOUD, OnUpdateViewPointcloud)
	ON_UPDATE_COMMAND_UI(ID_VIEW_WIREFRAME, OnUpdateViewWireframe)
	ON_UPDATE_COMMAND_UI(ID_VIEW_FLATSOLID, OnUpdateViewFlatsolid)
	ON_UPDATE_COMMAND_UI(ID_VIEW_SMOOTSHADING, OnUpdateViewSmootShading)
	ON_UPDATE_COMMAND_UI(ID_VIEW_WIRESHADING, OnUpdateViewWireShading)
	ON_UPDATE_COMMAND_UI(ID_VIEW_GRID, OnUpdateViewGrid)
	ON_UPDATE_COMMAND_UI(ID_VIEW_BOUNDING_BOX, OnUpdateViewBoundingBox)
	ON_COMMAND(ID_RECONSTRUCTION_3DSR, OnReconstruction3Dsr)
	ON_COMMAND(ID_RECON_DELAUNAY, OnReconDelaunay)
	ON_COMMAND(ID_RECON_VORONOI, OnReconVoronoi)
	ON_COMMAND(ID_FILE_IMPORT_NATIVE, OnFileImportNative)
	ON_COMMAND(ID_FILE_IMPORT_PT2FILE, OnFileImportPt2File)
	ON_COMMAND(ID_VISUALIZATION_VISDEBUG, OnVisualDebugger)
	ON_UPDATE_COMMAND_UI(ID_VISUALIZATION_VISDEBUG, OnUpdateVisualDebugger)
	ON_COMMAND(IDC_BUTTON_ALPHA_SHAPE, OnAlphaShape)
	ON_COMMAND(IDC_BUTTON_LOCATION, OnLocation)
	ON_COMMAND(ID_VIEW_3DPLANE, OnViewGroundPlane)
	ON_UPDATE_COMMAND_UI(ID_VIEW_3DPLANE, OnUpdateViewGroundPlane)
	ON_COMMAND(ID_VIEW_COORDINATE_SYSTEM, OnViewCoordinateSystem)
	ON_UPDATE_COMMAND_UI(ID_VIEW_COORDINATE_SYSTEM, OnUpdateViewCoordinateSystem)
	ON_COMMAND(ID_TOOLS_OPTION, OnToolsOption)
	ON_COMMAND(ID_TOOLS_FLAGGED_TETRA, OnToolsFlaggedTetra)
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_RECON_MEDIAL_AXIS, OnReconMedialAxis)
	ON_COMMAND(ID_RECON_VERTEX_NORMALS, OnReconCalculateVertexNormals)
	ON_COMMAND(ID_VIEW_SUPER_TETRA, OnViewSuperTetrahedron)
	ON_UPDATE_COMMAND_UI(ID_VIEW_SUPER_TETRA, OnUpdateViewSuperTetrahedron)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_VIEW_LIGHT_TOGGLE, OnViewLightToggle)
	ON_UPDATE_COMMAND_UI(ID_VIEW_LIGHT_TOGGLE, OnUpdateViewLightToggle)
	ON_COMMAND(ID_FILE_NEW, OnFileNew)
	ON_COMMAND(ID_TOOLS_FLIP_VNORMALS, OnToolsFlipVertexNormals)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSmevView construction/destruction

CSmevView::CSmevView()
{
	m_pDC = NULL;
	m_pOldPalette = NULL;
	m_nAlphaShapeValue = 0;
	m_nBackgroundColor  = 1;

	m_Dragging = FALSE;
	m_nActiveChoice = MC_NONE;


}

CSmevView::~CSmevView()
{
	DeleteAll();
}

BOOL CSmevView::PreCreateWindow(CREATESTRUCT& cs)
{
    // An OpenGL window must be created with the following flags and must not
    // include CS_PARENTDC for the class style. Refer to SetPixelFormat
    // documentation in the "Comments" section for further information.
    cs.style |= WS_CLIPSIBLINGS | WS_CLIPCHILDREN;

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CSmevView drawing

void CSmevView::OnDraw(CDC* pDC)
{
	CSmevDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	_DrawScene();
}

/////////////////////////////////////////////////////////////////////////////
// CSmevView printing

BOOL CSmevView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CSmevView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CSmevView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CSmevView diagnostics

#ifdef _DEBUG
void CSmevView::AssertValid() const
{
	CView::AssertValid();
}
 
void CSmevView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSmevDoc* CSmevView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSmevDoc)));
	return (CSmevDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSmevView message handlers

void CSmevView::_InitializeGL()
{
    PIXELFORMATDESCRIPTOR pfd;
	HGLRC		hrc;
    int         n;

    m_pDC = new CClientDC(this);
    ASSERT(m_pDC != NULL);

	// Set GL Pixel Format
    if (!_SetPixelFormat())
	{
        return;
	}
    n = ::GetPixelFormat(m_pDC->GetSafeHdc());
    ::DescribePixelFormat(m_pDC->GetSafeHdc(), n, sizeof(pfd), &pfd);

	// Logical Palette
    _CreateRGBPalette();

	// OpenGL Window Context
    hrc = wglCreateContext(m_pDC->GetSafeHdc());
    wglMakeCurrent(m_pDC->GetSafeHdc(), hrc);

    GetClientRect(&m_oldRect);
	GetClientRect(&m_vs.orgRect);

	InitVertexArray();
	//char buffer[200];
	//sprintf(buffer, "number of vertices: %d", m_vc.obj->vertCount);
	//MessageBox(buffer, MB_OK);

	// current sample for pole finding
	m_vc.sampleId = 0;

	// set up supertetrahedron to be draw
	Vertex3 apex(m_tetrahedralizer.GetSuperTetra().GetApex());
	Vertex3 left(m_tetrahedralizer.GetSuperTetra().GetBaseLeft());
	Vertex3 right(m_tetrahedralizer.GetSuperTetra().GetBaseRight());
	Vertex3 back(m_tetrahedralizer.GetSuperTetra().GetBaseBack());
	m_vc.superTetra.Set(apex, left, right, back);

	// initilize opengl with current visual context
	GLInitialize(m_vc);

	
	/*
	glClearDepth(1.0f);
    glDepthFunc(GL_LEQUAL);
	glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
	*/

	
	if (m_oldRect.bottom)
	{
		m_vs.ratio = (GLdouble)m_oldRect.right/m_oldRect.bottom;
	}
	else	// don't divide by zero, not that we should ever run into that...
	{
		m_vs.ratio = 1.0f;
	}
	
	m_vs.nearPlane = 0.1f;
	m_vs.farPlane = 100.0f;

	if (m_vs.projectionType == APP_PERSPECTIVE)
	{
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(45.0f, m_vs.ratio, m_vs.nearPlane, m_vs.farPlane);
		glMatrixMode(GL_MODELVIEW);
	}
	else // GL_ORTHO
	{
		glLoadIdentity();
		glOrtho(0.0f, m_vs.orgRect.right*m_vs.ratio, 0.0f, m_vs.orgRect.right*m_vs.ratio, 1.0f, -1.0f);
	}


   
	m_vs.pos.z = -5.0f;	
}


void CSmevView::_DrawScene()
{
    static BOOL     bBusy = FALSE;
	static int count = 0;
 
    if(bBusy)
	{
		return;
	}
    bBusy = TRUE;


	if (m_vc.camera.rot.x  > 360.0f) m_vc.camera.rot.x  = 0.0f;
	if (m_vc.camera.rot.y  > 360.0f) m_vc.camera.rot.y  = 0.0f;
	if (m_vc.camera.rot.z  > 360.0f) m_vc.camera.rot.z  = 0.0f;

	/*
	glPushMatrix();
	glTranslatef(m_vs.pos.x, m_vs.pos.y, m_vs.pos.z);
	glRotatef(m_vs.angle.x, 1.0f, 0.0f, 0.0f);
	glRotatef(m_vs.angle.y, 0.0f, 1.0f, 0.0f);
	glRotatef(m_vs.angle.z, 0.0f, 0.0f, 1.0f);

	
	switch(m_vs.fillType)
	{
	case APP_SOLID:
			for (i = 0; i < m_pO->nNumTris; i++)
			{
				glBegin(GL_TRIANGLES);

				t = &m_pO->t[i];
				v[0] = &m_pO->v[t->vid[0]];
				v[1] = &m_pO->v[t->vid[1]];
				v[2] = &m_pO->v[t->vid[2]];
				glColor3f(1.0f, 0.0f, 1.0f);
				glVertex3f(v[0]->lx, v[0]->ly, v[0]->lz);
				glColor3f(0.8f, 0.0f, 0.8f);
				glVertex3f(v[1]->lx, v[1]->ly, v[1]->lz);
				glColor3f(0.6f, 0.0f, 0.6f);
				glVertex3f(v[2]->lx, v[2]->ly, v[2]->lz);
				
				glEnd();
			}
		break;

	case APP_WIREFRAME:
			for (i = 0; i < m_pO->nNumTris; i++)
			{
				glBegin(GL_LINE_LOOP);

				t = &m_pO->t[i];
				v[0] = &m_pO->v[t->vid[0]];
				v[1] = &m_pO->v[t->vid[1]];
				v[2] = &m_pO->v[t->vid[2]];
				glColor3f(1.0f, 0.0f, 1.0f);
				glVertex3f(v[0]->lx, v[0]->ly, v[0]->lz);
				glColor3f(0.8f, 0.0f, 0.8f);
				glVertex3f(v[1]->lx, v[1]->ly, v[1]->lz);
				glColor3f(0.6f, 0.0f, 0.6f);
				glVertex3f(v[2]->lx, v[2]->ly, v[2]->lz);
				
				glEnd();
			}
		break;
		
	case APP_VERTEXONLY:
			
			for (i = 0; i < m_pO->nNumTris; i++)
			{
				glColor3f(1.0f, 1.0f, 1.0f);
				glPointSize(3.0);
				glBegin(GL_POINTS);

				t = &m_pO->t[i];
				v[0] = &m_pO->v[t->vid[0]];
				v[1] = &m_pO->v[t->vid[1]];
				v[2] = &m_pO->v[t->vid[2]];
				glVertex3f(v[0]->lx, v[0]->ly, v[0]->lz);
				glVertex3f(v[1]->lx, v[1]->ly, v[1]->lz);
				glVertex3f(v[2]->lx, v[2]->ly, v[2]->lz);
				
				glEnd();
			}
		break;

	//default:
		

	}

	glPopMatrix();
    */

	GLRender(m_vc);
    glFlush();
    SwapBuffers(wglGetCurrentDC());

    bBusy = FALSE;

	if (count < 5)
	{
		count++;
		
		if (count == 2)
		{

			IntroductionMessage();
		}
	}
}

void CSmevView::_CreateRGBPalette()
{
    PIXELFORMATDESCRIPTOR pfd;
    LOGPALETTE *pPal;
    int n;
 
    n = ::GetPixelFormat(m_pDC->GetSafeHdc());
    ::DescribePixelFormat(m_pDC->GetSafeHdc(), n, sizeof(pfd), &pfd);


	if (pfd.dwFlags & PFD_NEED_PALETTE)
    {
        n = 1 << pfd.cColorBits;
        pPal = (PLOGPALETTE) new char[sizeof(LOGPALETTE) + n * sizeof(PALETTEENTRY)];

        ASSERT(pPal != NULL);

        pPal->palVersion = 0x300;
        pPal->palNumEntries = n;
		/*
        for (i=0; i<n; i++)
        {
            pPal->palPalEntry[i].peRed =
                    ComponentFromIndex(i, pfd.cRedBits, pfd.cRedShift);
            pPal->palPalEntry[i].peGreen =
                    ComponentFromIndex(i, pfd.cGreenBits, pfd.cGreenShift);
            pPal->palPalEntry[i].peBlue =
                    ComponentFromIndex(i, pfd.cBlueBits, pfd.cBlueShift);
            pPal->palPalEntry[i].peFlags = 0;
        }
		*/
	

        // fix up the palette to include the default GDI palette 
        if ((pfd.cColorBits == 8)                           &&
            (pfd.cRedBits   == 3) && (pfd.cRedShift   == 0) &&
            (pfd.cGreenBits == 3) && (pfd.cGreenShift == 3) &&
            (pfd.cBlueBits  == 2) && (pfd.cBlueShift  == 6)
           )
        {
			//for (i = 1 ; i <= 12 ; i++)
            //    pPal->palPalEntry[defaultOverride[i]] = defaultPalEntry[i];
        }


        m_cPalette.CreatePalette(pPal);
        delete pPal;

        m_pOldPalette = m_pDC->SelectPalette(&m_cPalette, FALSE);
        m_pDC->RealizePalette();
    }

}

BOOL CSmevView::_SetPixelFormat()
{
    static PIXELFORMATDESCRIPTOR pfd = 
	{
        sizeof(PIXELFORMATDESCRIPTOR),  // size of this pfd
        1,                              // version number
        PFD_DRAW_TO_WINDOW |            // support window
          PFD_SUPPORT_OPENGL |          // support OpenGL
          PFD_DOUBLEBUFFER,             // double buffered
        PFD_TYPE_RGBA,                  // RGBA type
        24,                             // 24-bit color depth
        0, 0, 0, 0, 0, 0,               // color bits ignored
        0,                              // no alpha buffer
        0,                              // shift bit ignored
        0,                              // no accumulation buffer
        0, 0, 0, 0,                     // accum bits ignored
        32,                             // 32-bit z-buffer
        0,                              // no stencil buffer
        0,                              // no auxiliary buffer
        PFD_MAIN_PLANE,                 // main layer
        0,                              // reserved
        0, 0, 0                         // layer masks ignored
    };
    int pixelformat;

    if ( (pixelformat = ChoosePixelFormat(m_pDC->GetSafeHdc(), &pfd)) == 0 )
    {
        MessageBox("ChoosePixelFormat failed");
        return FALSE;
    }

    if (SetPixelFormat(m_pDC->GetSafeHdc(), pixelformat, &pfd) == FALSE)
    {
        MessageBox("SetPixelFormat failed");
        return FALSE;
    }

    return TRUE;
}

int CSmevView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// Initialize OpenGL 
	_InitializeGL();
	
	return 0;
}

void CSmevView::OnDestroy() 
{	
	HGLRC	hrc;

	//DeleteAll();

	KillTimer(1);

	hrc = ::wglGetCurrentContext();
    ::wglMakeCurrent(NULL,  NULL);
    if (hrc)
	{
        ::wglDeleteContext(hrc);
	}

    if (m_pOldPalette)
	{
        m_pDC->SelectPalette(m_pOldPalette, FALSE);
	}

    if (m_pDC)
	{
        delete m_pDC;
	}

	CView::OnDestroy();	
}

BOOL CSmevView::OnEraseBkgnd(CDC* pDC) 
{	
	return TRUE;	
}

void CSmevView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	
	if (m_vs.projectionType == APP_PERSPECTIVE)
	{
		if(cy > 0)
		{    
			// Rescale the viewport
			glViewport(0, 0, cx, cy);

			if((m_oldRect.right > cx) || (m_oldRect.bottom > cy))
			{
				RedrawWindow();
			}

			m_oldRect.right = cx;
			m_oldRect.bottom = cy;

			// Keep right x/y proportion of the window/clipping volume mapping:
			(cy > cx) ? m_vs.ratio = (GLdouble)cy/cx : m_vs.ratio = (GLdouble)cx/cy;


			// Reset Perspective View Volume
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			gluPerspective(45.0f, m_vs.ratio, m_vs.nearPlane, m_vs.farPlane);
			glMatrixMode(GL_MODELVIEW);
		}
	}
	else // GL_ORTHO
	{
		// Prevent divide by zero
		if (cy == 0)
		{
			cy = 1;
		}

		// Set the viewport to be the entire window
		glViewport(0, 0, cx, cy);

		// Reset the coordinate system before modifying 
		glLoadIdentity();

		m_oldRect.right = cx;
		m_oldRect.bottom = cy; 
		// Keep ratio like a square
		if (cx <= cy)
		{
			m_vs.ratio = (GLdouble)(cy/cx);
		}
		else
		{
			m_vs.ratio = (GLdouble)(cx/cy);
		}
		// Set Clipping Volume
		glOrtho(0.0f, m_vs.orgRect.right*m_vs.ratio, 0.0f, m_vs.orgRect.right*m_vs.ratio, 1.0f, -1.0f);
	}
	
	// m_vc.viewport.width = cx;
	// m_vc.viewport.height = cy;
	// GLResize(m_vc);

}

void CSmevView::OnTimer(UINT nIDEvent) 
{
	_DrawScene();
	
	CView::OnTimer(nIDEvent);

	// Eat spurious WM_TIMER messages
	MSG msg;
	while(::PeekMessage(&msg, m_hWnd, WM_TIMER, WM_TIMER, PM_REMOVE));
}


void CSmevView::InitVertexArray()
{
	//char filename[] = "hotdogs.pt2";
	//char filename[] = "test1.pt2";
	char filename[] = "woman3.pt2";
	//char filename[] = "bernard.pt2";
	//char filename[] = "default.pt2";

    
    m_vc.obj = new Skeleton;
	/*
	if (1)
	{
		convertToNativeDataFormat(m_vc.obj);
		
		// overwrite number of verts
		//m_vc.obj->vertCount = 55;

	}
	else 
	{
	   if (!PT2ReadFile(filename, m_vc.obj))
	   {
		   MessageBox("file not found", MB_OK);
		   AppOutN("i/o error: file not found ");
		   exit(0);
	   }
		//m_vc.obj->vertCount = 500;
    }
   

    // initialize global vertex array
	MaxBox3(m_vc.box, &m_vc.obj->vert[0], m_vc.obj->vertCount);
	Vertex3::SetGlobalVertexList(&m_vc.obj->vert[0]);
	*/
	m_vc.obj->vertCount = 0;
	Vertex3::SetGlobalVertexCount(m_vc.obj->vertCount);

	m_vs.reconState = APP_EMPTY;
}

void CSmevView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	switch(nChar)
	{
	case VK_RIGHT:
		m_vc.camera.rot.y += 5.0f;
		TRACE("camera y %f", m_vc.camera.rot.y ); 
		Invalidate(FALSE);
		break;
	case VK_LEFT:
		m_vc.camera.rot.y -= 5.0f;
		Invalidate(FALSE);
		break;
	case VK_UP:
		m_vc.camera.rot.x += 5.0f;
		Invalidate(FALSE);
		break;
	case VK_DOWN:
		m_vc.camera.rot.x -= 5.0f;
		Invalidate(FALSE);
		break;
	}

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CSmevView::OnCheckdelaunay() 
{
	m_vc.visualizer.SetVisibleTetrahedra(!m_vc.visualizer.IsVisibleTetrahedra());
	Invalidate(FALSE);
}

void CSmevView::OnDoubleclickedCheckdelaunay() 
{
	m_vc.visualizer.SetVisibleTetrahedra(false);
	Invalidate(FALSE);
}

void CSmevView::OnCheckconvexhull() 
{
	m_vc.visualizer.SetVisibleOnlyConvexHull(!m_vc.visualizer.IsVisibleOnlyConvexHull());
	Invalidate(FALSE);	
}

void CSmevView::OnCheckPointCloud() 
{
	m_vc.visualizer.SetVisibleDataSet3(!m_vc.visualizer.IsVisibleDataSet3());
	Invalidate(FALSE);	
}

void CSmevView::OnCheckVoroCell() 
{
	m_vc.visualizer.SetVisibleVoronoiCell(!m_vc.visualizer.IsVisibleVoronoiCell());
	Invalidate(FALSE);	
}

void CSmevView::OnCheckVoronoiBall() 
{
	m_vc.visualizer.SetVisibleCircumSphere(!m_vc.visualizer.IsVisibleCircumSphere());
	Invalidate(FALSE);	
}

void CSmevView::OnCheckvorodiagram() 
{
	m_vc.visualizer.SetVisibleVoronoi(!m_vc.visualizer.IsVisibleVoronoi());
	Invalidate(FALSE);	
}

void CSmevView::OnCheckvoronoivertices() 
{
	m_vc.visualizer.SetVisibleVoronoiVertex(!m_vc.visualizer.IsVisibleVoronoiVertex());
	Invalidate(FALSE);	
}



void CSmevView::OnAnalysisStatistics() 
{
	char sBuffer[1023-255] = "";
	char temp[255];

	// gemetry title
	sprintf(temp, "Geometry:\n\n");
	strcat(sBuffer, temp);

		// vertex
	sprintf(temp, "Number of object vertices: \t\t%d\n", m_vc.obj->vertCount);
	strcat(sBuffer, temp);
	sprintf(temp, "Number of global vertices: \t\t%d\n", Vertex3::GetGlobalVertexCount());
	strcat(sBuffer, temp);

	sprintf(temp, "Size of a vertex: \t\t%d bytes\n", (int)sizeof(Vertex3));
	strcat(sBuffer, temp);

	// simplicial complex title
	sprintf(temp, "\n\nSimplicial Complex:\n\n");
	strcat(sBuffer, temp);

	// edge
	sprintf(temp, "Number of undirected edges: \t%d\n", (int)m_vc.tetraList.Size()*4*3);
	strcat(sBuffer, temp);
	sprintf(temp, "Size of an edge: \t\t%d bytes\n", (int)sizeof(Edge3));
	strcat(sBuffer, temp);

	// face
	sprintf(temp, "Number of total faces: \t%d\n", (int)m_vc.tetraList.Size()*4);
	strcat(sBuffer, temp);
	sprintf(temp, "Size of a face: \t\t%d bytes\n", (int)sizeof(Face3));
	strcat(sBuffer, temp);

	// tetrahedron
	sprintf(temp, "Number of tetrahedra: \t%d\n", (int)m_vc.tetraList.Size());
	strcat(sBuffer, temp);
	sprintf(temp, "Size of a tetrahedron: \t%d bytes\n", (int)sizeof(Tetrahedron));
	strcat(sBuffer, temp);

	// total used memory
	int totalBytes = 
		m_vc.obj->vertCount * (int)sizeof(Vertex3) +
		m_vc.tetraList.Size()*4*3 * (int)sizeof(Edge3) +
		m_vc.tetraList.Size()*4 * (int)sizeof(Face3) +
		m_vc.tetraList.Size() * (int)sizeof(Tetrahedron);

	sprintf(temp, "\n\nTotal Memory For Used Data Structures:\n\n");
	strcat(sBuffer, temp);
	sprintf(temp, "Memory in bytes: \t%d bytes\n", totalBytes);
	strcat(sBuffer, temp);
	sprintf(temp, "Memory in kilobytes: \t%d kb\n\n", (int)(totalBytes/1024));
	strcat(sBuffer, temp);

	// poles and medial-axis
	sprintf(temp, "\n\nNumber of Poles computed by MAT: %d\n\n", m_medialAxisTransformer.GetNumPoles());
	strcat(sBuffer, temp);


	char sState[80];
	switch(m_vs.reconState)
	{
	case APP_EMPTY:
		strcpy(sState, "Empty, no point cloud");
		break;

	case APP_POINTSET:
		strcpy(sState, "PointSet, point cloud loaded in memory");
		break;

	case APP_DELAUNAY:
		strcpy(sState, "Delaunay, tetrahedralization in memory");
		break;

	case APP_VORONOI:
		strcpy(sState, "Voronoi, diagram computed");
		break;

	case APP_NEIGH_LINKS:
		strcpy(sState, "Vertices Linked to neighbouring tetrahedra");
		break;

	case APP_MEDIAL_AXIS:
		strcpy(sState, "Medial Axis, all poles computed");
		break;

	case APP_CRUST:
		strcpy(sState, "Crust computed");
		break;

	case APP_2D_MANIFOLD:
		strcpy(sState, "2D Manifold: surface reconstruction computed");
		break;

	default:
		strcpy(sState, "Unknown state");


	}
	sprintf(temp, "Reconstruction state: %s\n", sState);
	strcat(sBuffer, temp);
	
	MessageBox(sBuffer, "Geometrical Statistics", MB_OK);
	
	
}

void CSmevView::OnButtonCameraRotateXCcw() 
{
	m_vc.camera.rot.x -= 1.0f;	
	Invalidate(FALSE);	
}

void CSmevView::OnButtonCameraRotateXCw() 
{
	m_vc.camera.rot.x += 1.0f;	
	Invalidate(FALSE);		
}

void CSmevView::OnButtonCameraRotateYCcw() 
{
	m_vc.camera.rot.y -= 1.0f;
	Invalidate(FALSE);	
}

void CSmevView::OnButtonCameraRotateYCw() 
{
	m_vc.camera.rot.y += 1.0f;	
	Invalidate(FALSE);	
}

void CSmevView::OnButtonCameraTback() 
{
	m_vc.camera.pos.z += 0.3f;
	Invalidate(FALSE);	
}

void CSmevView::OnButtonCameraTfront() 
{
	m_vc.camera.pos.z -= 0.3f;
	Invalidate(FALSE);	
}

void CSmevView::OnButtonCameraTleft() 
{
	m_vc.camera.pos.x -= 0.2f;	
	m_vc.camera.at.x -= 0.2f;
	Invalidate(FALSE);
}

void CSmevView::OnButtonCameraTright() 
{
	m_vc.camera.pos.x += 0.2f;	
	m_vc.camera.at.x += 0.2f;
	Invalidate(FALSE);
}

void CSmevView::OnButtonVoronoiCell() 
{
	m_vc.visualizer.SetVisibleVoronoiCell(!m_vc.visualizer.IsVisibleVoronoiCell());
	Invalidate(FALSE);
}

void CSmevView::OnButtonVoronoiNextSample() 
{
	m_vc.sampleId++;	
	Invalidate(FALSE);
}

void CSmevView::OnButtonVoronoiPrevSample() 
{
	m_vc.sampleId--;
	Invalidate(FALSE);
}

void CSmevView::OnButtonVoronoiVertices() 
{
	m_vc.visualizer.SetVisibleVoronoiVertex(!m_vc.visualizer.IsVisibleVoronoiVertex());
	Invalidate(FALSE);
}	


void CSmevView::OnCheckVertexNormal() 
{
	m_vc.visualizer.SetVisibleVertexNormal(!m_vc.visualizer.IsVisibleVertexNormal());
	Invalidate(FALSE);	
}

void CSmevView::OnToolsRandomize() 
{
	CDialogRandomizer dlg;

	if (dlg.DoModal() == TRUE)
	{
		RandomizePointSet(Vertex3::GetGlobalVertexList(), dlg.m_nRandomPercentage, 1.0);
		Invalidate(FALSE);	
	}
}


void CSmevView::OnViewGrid() 
{
	m_vc.visualizer.SetVisibleGrid(!m_vc.visualizer.IsVisibleGrid());
	m_vs.useGrid = !m_vs.useGrid;
	Invalidate(FALSE);	

}

void CSmevView::OnViewPointcloud() 
{
	m_vc.visualizer.SetPolygonMode(GV_POINTS);
	m_vc.visualizer.SetVisibleLighting(false);

	m_vs.renderingType = GV_POINTS;

	Invalidate(FALSE);
}

void CSmevView::OnViewWireframe() 
{
	m_vc.visualizer.SetPolygonMode(GV_WIRE);
	m_vc.visualizer.SetVisibleLighting(false);

	m_vs.renderingType = GV_WIRE;

	Invalidate(FALSE);
}

void CSmevView::OnViewFlatSolid() 
{
	m_vc.visualizer.SetPolygonMode(GV_FLATSOLID);	
	m_vc.visualizer.SetVisibleLighting(false);

	m_vs.renderingType = GV_FLATSOLID;

	Invalidate(FALSE);
}

void CSmevView::OnViewSmootShading() 
{
	m_vc.visualizer.SetPolygonMode(GV_SMOOTHSHADING);
	m_vc.visualizer.SetVisibleLighting(true);

	m_vs.renderingType = GV_SMOOTHSHADING;

	Invalidate(FALSE);
}

void CSmevView::OnViewWireShading() 
{
	m_vc.visualizer.SetPolygonMode(GV_WIREANDSHADE);	
	m_vc.visualizer.SetVisibleLighting(false);

	m_vs.renderingType = GV_WIREANDSHADE;
	Invalidate(FALSE);
}


void CSmevView::OnViewBoundingBox() 
{
	m_vc.visualizer.SetVisibleMaxBox3(!m_vc.visualizer.IsVisibleMaxBox3());
	m_vs.useBoundingBox = !m_vs.useBoundingBox;
	Invalidate(FALSE);	
}

void CSmevView::OnUpdateViewPointcloud(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_vs.renderingType == GV_POINTS);
}

void CSmevView::OnUpdateViewWireframe(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_vs.renderingType == GV_WIRE);
	
}

void CSmevView::OnUpdateViewFlatsolid(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_vs.renderingType == GV_FLATSOLID);
	
}

void CSmevView::OnUpdateViewSmootShading(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_vs.renderingType == GV_SMOOTHSHADING);
	
}

void CSmevView::OnUpdateViewWireShading(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_vs.renderingType == GV_WIREANDSHADE);
	
}

void CSmevView::OnUpdateViewGrid(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_vs.useGrid == true);

}

void CSmevView::OnUpdateViewBoundingBox(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_vs.useBoundingBox == true);
	
}

void CSmevView::OnReconstruction3Dsr() 
{

	if (m_vs.reconState == APP_EMPTY)
	{
		MessageBox("Cannot start surface reconstruction: data set is empty", MB_OK);
		return;
	}



	CDlgReconProcess* dlg = new CDlgReconProcess;

	dlg->UpdateData(FALSE);
	dlg->ShowWindow(SW_SHOW);


	dlg->SetRange(1,100);
	dlg->SetPos(10);
	dlg->UpdateData(TRUE);

	

	if (m_vs.reconState == APP_POINTSET)
	{
		m_tetrahedralizer.Build(m_vc.tetraList);
		m_vs.reconState = APP_DELAUNAY;
		_DrawScene();
	}

	dlg->SetPos(20);
	dlg->UpdateData(TRUE);
	if (m_vs.reconState == APP_DELAUNAY)
	{
		m_tessellator.Build(m_vc.tetraList);
		m_vs.reconState = APP_VORONOI;
		_DrawScene();

	}

	dlg->SetPos(30);
	dlg->UpdateData(TRUE);

	if (m_vs.reconState == APP_VORONOI)
	{
		m_tessellator.LinkVerticesToNeighTetrahedra(m_vc.tetraList);
		m_vs.reconState = APP_NEIGH_LINKS;
		_DrawScene();
	}

	dlg->SetPos(60);
	dlg->UpdateData(TRUE);

	if (m_vs.reconState == APP_NEIGH_LINKS)
	{
		m_medialAxisTransformer.Build(m_vc.tetraList);	
		m_vs.reconState = APP_MEDIAL_AXIS;
		_DrawScene();
	}

	dlg->SetPos(70);
	dlg->UpdateData(TRUE);

	Vertex3* newArray = NULL;
	int newArraySize = 0;
	if (m_vs.reconState == APP_MEDIAL_AXIS)
	{


		newArray = m_crustExtractor.PerformCrustExtraction(m_vc.tetraList, newArraySize);
		if (!newArray)
		{
			MessageBox("Not enough memory for entire surface reconstruction", MB_OK);	
			Invalidate(FALSE);	
			return;
		}	
		_DrawScene();

	
	// delete old array
	DeleteAll();
     
	// register new array with a 3d object
	m_vc.obj = new Skeleton;
    m_vc.obj->vert = newArray;
	m_vc.obj->vertCount = newArraySize;

    MaxBox3(m_vc.box, &m_vc.obj->vert[0], m_vc.obj->vertCount);

	// register the new array as the global vertex array
	Vertex3::SetGlobalVertexList(&m_vc.obj->vert[0]);
	Vertex3::SetGlobalVertexCount(m_vc.obj->vertCount);

	dlg->SetPos(80);
	dlg->UpdateData(TRUE);

	// re-triagulate s U p again
	m_tetrahedralizer.GetSuperTetra().SetSuperFactor(4);
	m_tetrahedralizer.Build(m_vc.tetraList);
	m_tetrahedralizer.GetSuperTetra().SetSuperFactor(2);
	m_vs.reconState = APP_CRUST;    

	dlg->SetPos(90);
	dlg->UpdateData(TRUE);

	// extract polygon mesh
	m_crustExtractor.ExtractPolygonMesh(m_vc.tetraList, m_vc.obj);
	_DrawScene();
	dlg->SetPos(100);


	}
	
    // re-initialize object reference to global vertex array
	//m_vc.obj->vert = Vertex3::GetGlobalVertexList();
	//m_vc.obj->vertCount = Vertex3::GetGlobalVertexCount();

	// recalculate max box
	//MaxBox3(m_vc.box, &m_vc.obj->vert[0], m_vc.obj->vertCount);

   
	MessageBox("Poles Integration Completed!", MB_OK);
	//m_vs.reconState = APP_POINTSET;

	UpdateVisualContext();
	Invalidate(FALSE);		
}

void CSmevView::OnReconDelaunay() 
{
	if (m_vs.reconState == APP_POINTSET)
	{
		CWinThread* pThread = AfxBeginThread(WorkerThreadTetrahedralizer, (LPVOID)this);
	}
	else if (m_vs.reconState == APP_EMPTY)
	{
		MessageBox("Cannot build Delaunay tetrahedralization: data set is empty", MB_OK);
	}
	else 
	{
		MessageBox("Delaunay tetrahedralization already exist!", MB_OK);		
	}
	UpdateVisualContext();
	Invalidate(FALSE);	
}

void CSmevView::OnReconVoronoi() 
{
	if (m_vs.reconState == APP_POINTSET)
	{
		m_tetrahedralizer.Build(m_vc.tetraList);
		m_vs.reconState = APP_DELAUNAY;
	}

	if (m_vs.reconState == APP_DELAUNAY)
	{
		m_tessellator.Build(m_vc.tetraList);
		m_vs.reconState = APP_VORONOI;
	}
	else if (m_vs.reconState == APP_EMPTY)
	{
		MessageBox("Cannot build Voronoi diagram: data set is empty!", MB_OK);
	}
	else
	{
		MessageBox("Voronoi diagram already exist!", MB_OK);
	}
	UpdateVisualContext();
	Invalidate(FALSE);	
}

void CSmevView::OnFileImportNative() 
{
	if (m_vs.reconState != APP_EMPTY)
	{
		MessageBox("Deleting current point cloud", MB_OK);
		DeleteAll();
	}


    m_vc.obj = new Skeleton;

	convertToNativeDataFormat(m_vc.obj); 

    // initialize global vertex array
	MaxBox3(m_vc.box, &m_vc.obj->vert[0], m_vc.obj->vertCount);
	Vertex3::SetGlobalVertexList(&m_vc.obj->vert[0]);
	Vertex3::SetGlobalVertexCount(m_vc.obj->vertCount);

	m_vs.reconState = APP_POINTSET;
	
	m_vc.visualizer.SetVisibleDataSet3(true);

	UpdateVisualContext();
	Invalidate(FALSE);	
}

void CSmevView::OnFileImportPt2File() 
{
	//char filename[] = "hotdogs.pt2";
	//char filename[] = "test1.pt2";
	//char filename[] = "woman3.pt2";
	//char filename[] = "bernard.pt2";
	//char filename[] = "default.pt2";

	if (m_vs.reconState != APP_EMPTY)
	{
		MessageBox("Deleting current point cloud", MB_OK);
		DeleteAll();
	}

    m_vc.obj = new Skeleton;
	   
	CFileDialog dlg(TRUE); //TRUE);
	CString dir = "c:/dev";
	dlg.m_ofn.lpstrInitialDir = dir;

	if (dlg.DoModal() == IDOK)
	{
		CString temp = dlg.GetPathName();
		

		if (!PT2ReadFile((LPCTSTR)temp, m_vc.obj))
		{
			   MessageBox("file not found", MB_OK);
			   AppOutN("i/o error: file not found ");
			   return;
		}
      
		// initialize global vertex array
		MaxBox3(m_vc.box, &m_vc.obj->vert[0], m_vc.obj->vertCount);
		Vertex3::SetGlobalVertexList(&m_vc.obj->vert[0]);
		Vertex3::SetGlobalVertexCount(m_vc.obj->vertCount);

		m_vs.reconState = APP_POINTSET;	
		m_vc.visualizer.SetVisibleDataSet3(true);
	}
	UpdateVisualContext();
	Invalidate(FALSE);	
}

void CSmevView::DeleteAll()
{
	assert(m_vc.obj != NULL);

	// Smev is the memory manager for obj
	// Skeleton deconstructor deletes also the vertex array
	if (m_vc.obj) delete m_vc.obj;

	// tetrahedra are deleted automatically by VisualContext destructor
	m_vc.Clear();
	
}

void CSmevView::OnVisualDebugger() 
{
	MessageBox("This feature is still experimental", MB_OK);
	m_vc.visualizer.SetPolygonMode(GV_POINTS);
	m_vc.visualizer.SetVisibleDataSet3(false);
	
	m_vc.visualDebugger.SetVisualizer(!m_vc.visualDebugger.IsVisible());	

	Invalidate(FALSE);

	UpdateCameraLocation(LOCATION_FAR);
}

void CSmevView::OnUpdateVisualDebugger(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_vc.visualDebugger.IsVisible() == true);
}

void CSmevView::OnAlphaShape() 
{
	if (m_vs.reconState == APP_EMPTY || m_vs.reconState == APP_POINTSET)
	{
		MessageBox("Cannot use alpha parameters withou Delaunay tetrahedralization", MB_OK);
		return;
	}

	DialogAlphaShape *pDialog;
	pDialog = new DialogAlphaShape;
	pDialog->SetView(this);

	//pDialog->m_alpha.SetValue();
	pDialog->UpdateData(FALSE);
	pDialog->ShowWindow(SW_SHOW);
	
	Invalidate(FALSE);	
}

void CSmevView::SetAlphaShapeParameter(double dRadius)
{
	m_vc.visualizer.SetAlphaShapeParameter(dRadius);
	Invalidate(FALSE);
}

void CSmevView::OnViewGroundPlane() 
{
	m_vc.visualizer.SetVisibleBackgroundPlane(!m_vc.visualizer.IsVisibleBackgroundPlane());
	Invalidate(FALSE);
}

void CSmevView::OnUpdateViewGroundPlane(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_vc.visualizer.IsVisibleBackgroundPlane() == true);
}

void CSmevView::OnViewCoordinateSystem() 
{
	m_vc.visualizer.SetVisibleCoordinateSystem(!m_vc.visualizer.IsVisibleCoordinateSystem());
	Invalidate(FALSE);	
}

void CSmevView::OnUpdateViewCoordinateSystem(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_vc.visualizer.IsVisibleCoordinateSystem() == true);	
}



void CSmevView::OnToolsOption() 
{
	CDialogOptions dlg;
	
	dlg.m_radioBackgroundColor = m_vc.visualizer.GetBackgroundColor();
	dlg.m_normalFactor = m_vc.visualizer.GetNormalFactor();
	dlg.m_superFactor = m_tetrahedralizer.GetSuperTetra().GetSuperFactor();

	if (dlg.DoModal() == IDOK)
	{
		m_vc.visualizer.SetBackgroundColor(dlg.m_radioBackgroundColor);
		m_vc.visualizer.SetNormalFactor(dlg.m_normalFactor);
		m_tetrahedralizer.GetSuperTetra().SetSuperFactor(dlg.m_superFactor);

		UpdateVisualContext();
		Invalidate(FALSE);
	}
}

void CSmevView::OnToolsFlaggedTetra() 
{
	char sBuffer[1023-255] = "";
	char temp[255];

	// title
	//sprintf(temp, "Number of Flagged Tetrehedra:\n\n");
	//strcat(sBuffer, temp);

	int numFlagged = 0;
    
	TetraList::Itr start = m_vc.tetraList.Begin();
	TetraList::Itr end = m_vc.tetraList.End();

	while (start != end)
	{
		Tetrahedron *tetra = *start++;
		if (tetra->IsFlagged())
		{
			numFlagged++;
		}
	}

		// vertex
	sprintf(temp, "Number of Flagged Tetrahedra: \t\t%d\n", numFlagged);
	strcat(sBuffer, temp);

	
	MessageBox(sBuffer, "Flagged Tetrehedra", MB_OK);
	
		
}

void CSmevView::OnPrint(CDC* pDC, CPrintInfo* pInfo) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CView::OnPrint(pDC, pInfo);
}

void CSmevView::OnRButtonDown(UINT nFlags, CPoint point) 
{
    m_bRButtonDown = TRUE;
	//Invalidate(FALSE);
	CView::OnRButtonDown(nFlags, point);
}

void CSmevView::OnRButtonUp(UINT nFlags, CPoint point) 
{
	m_bRButtonDown = FALSE;
	//Invalidate(FALSE);
	CView::OnRButtonUp(nFlags, point);
}

void CSmevView::OnMouseMove(UINT nFlags, CPoint point) 
{
	if (!m_Dragging) return;
	m_DragPos = point;

	if (nFlags & MK_RBUTTON > 0)
	{
 		if ( m_bRButtonDown)
		{
			m_vc.camera.rot.y += 1.0;
		}
	}

	if ((nFlags & MK_LBUTTON) > 0 )
	{
		//UpdateStatusBar(2);

		if ((point.x - m_MousePos.x) != 0)	// Rotate Camera in Y
		{
			m_vc.camera.rot.y = m_Grab_Rot_Y + ((float)ROTATE_SPEED * (point.x - m_MousePos.x));
			_DrawScene();
		}
		else
		if ((point.y - m_MousePos.y) != 0)
		{
			m_vc.camera.pos.z = m_Grab_Trans_Z + ((float)TRANSLATE_SPEED * (point.y - m_MousePos.y));
			_DrawScene();
		}

		


	}


	Invalidate(FALSE);
	CView::OnMouseMove(nFlags, point);
}

void CSmevView::OnReconMedialAxis() 
{
	if (m_vs.reconState == APP_EMPTY)
	{
		MessageBox("Cannot start medial axis tranform: data set is empty", MB_OK);
		return;
	}

	if (m_vs.reconState == APP_POINTSET)
	{
		m_tetrahedralizer.Build(m_vc.tetraList);
		m_vs.reconState = APP_DELAUNAY;
	}

	if (m_vs.reconState == APP_DELAUNAY)
	{
		m_tessellator.Build(m_vc.tetraList);
		m_vs.reconState = APP_VORONOI;
	}

	if (m_vs.reconState == APP_VORONOI)
	{
		m_tessellator.LinkVerticesToNeighTetrahedra(m_vc.tetraList);
		m_vs.reconState = APP_NEIGH_LINKS;
	}
	if (m_vs.reconState == APP_NEIGH_LINKS)
	{
		m_medialAxisTransformer.Build(m_vc.tetraList);	
		m_vs.reconState = APP_MEDIAL_AXIS;
	}
	else
	{
		MessageBox("Medial Axis Tranform already exists", MB_OK);
		return;
	}

	UpdateVisualContext();
	Invalidate(FALSE);	

}

void CSmevView::OnReconCalculateVertexNormals() 
{
	MessageBox("Sorry, this feature is not available in this version", MB_OK);
	return;

	if (m_vs.reconState == APP_EMPTY)
	{
		MessageBox("Cannot calculate vertex normals: data set is empty", MB_OK);
		return;
	}

	if (m_vs.reconState == APP_POINTSET)
	{
		m_tetrahedralizer.Build(m_vc.tetraList);
		m_vs.reconState = APP_DELAUNAY;
	}

	if (m_vs.reconState == APP_DELAUNAY)
	{
		m_tessellator.LinkVerticesToNeighTetrahedra(m_vc.tetraList);
		m_vs.reconState = APP_NEIGH_LINKS;
	}
	else
	{
		MessageBox("Vertex normals already calculated", MB_OK);
		return;
	}

	UpdateVisualContext();
	Invalidate(FALSE);	
	
}

void CSmevView::UpdateVisualContext()
{
	// set up supertetrahedron to be draw
	Vertex3 a(m_tetrahedralizer.GetSuperTetra().GetApex());
	Vertex3 l(m_tetrahedralizer.GetSuperTetra().GetBaseLeft());
	Vertex3 r(m_tetrahedralizer.GetSuperTetra().GetBaseRight());
	Vertex3 b(m_tetrahedralizer.GetSuperTetra().GetBaseBack());

	int sf = m_tetrahedralizer.GetSuperTetra().GetSuperFactor();

	a.SetVertex(a.x*sf, a.y*sf, a.z*sf);
	l.SetVertex(l.x*sf, l.y*sf, l.z*sf);
	r.SetVertex(r.x*sf, r.y*sf, r.z*sf);
	b.SetVertex(b.x*sf, b.y*sf, b.z*sf);

	m_vc.superTetra.Set(a, l, r, b);

	m_vc.visualizer.SetBottomOfBox(m_vc.box.MinY());
}

void CSmevView::OnViewSuperTetrahedron() 
{
	m_vc.visualizer.SetVisibleSuperTetrahedron(!m_vc.visualizer.IsVisibleSuperTetrahedron());	
	Invalidate(FALSE);
}


void CSmevView::OnUpdateViewSuperTetrahedron(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_vc.visualizer.IsVisibleSuperTetrahedron() == true);
	
}

void CSmevView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// STORE OFF THE HIT POINT AND SETTINGS FOR THE MOVEMENT LATER
	m_MousePos = point;
	m_Dragging = TRUE;

	m_Grab_Rot_X = 		m_vc.camera.rot.x;
	m_Grab_Rot_Y = 		m_vc.camera.rot.y;
	m_Grab_Rot_Z = 		m_vc.camera.rot.z;

	m_Grab_Trans_X = 	m_vc.camera.pos.x;
	m_Grab_Trans_Y = 	m_vc.camera.pos.y;
	m_Grab_Trans_Z = 	m_vc.camera.pos.z;

	CWnd::OnLButtonDown(nFlags, point);

}

void CSmevView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// STORE OFF THE HIT POINT AND SETTINGS FOR THE MOVEMENT LATER
	m_Dragging = FALSE;



	CWnd::OnLButtonUp(nFlags, point);
}

void CSmevView::OnLocation()
{
	CDlgLocation *pDialog;
	pDialog = new CDlgLocation;
	pDialog->SetView(this);

	pDialog->UpdateData(FALSE);
	pDialog->ShowWindow(SW_SHOW);
	
	Invalidate(FALSE);	
}

void CSmevView::UpdateCameraLocation(int nLocation)
{
	Vector3 pos; 
	Vertex3 * v;

	switch(nLocation)
	{
	case LOCATION_FRONT: // front
		m_vc.camera.pos.Set(0.0, 0.0, 2.0);
		m_vc.camera.at.Set(0.0, 0.0, 0.0);
		m_vc.camera.up.Set(0.0, 1.0, 0.0);
		m_vc.camera.rot.Set(0.0, 0.0, 0.0);
		break;

	case LOCATION_TOP: // top
		m_vc.camera.pos.Set(0.0, 3.0, 0.0);
		m_vc.camera.at.Set(0.0, 0.0, 0.0);
		m_vc.camera.up.Set(0.0, 0.0, 1.0);
		m_vc.camera.rot.Set(0.0, 0.0, 0.0);
		break;

	case LOCATION_SIDE: // (left) side
		m_vc.camera.pos.Set(0.0, 0.0, 2.0);
		m_vc.camera.at.Set(0.0, 0.0, 0.0);
		m_vc.camera.up.Set(0.0, 1.0, 0.0);
		m_vc.camera.rot.Set(0.0, 90.0, 0.0);
		break;

	case LOCATION_NEAR: // near
		m_vc.camera.pos.Set(0.0, 0.0, 1.0);
		m_vc.camera.at.Set(0.0, 0.0, 0.0);
		m_vc.camera.up.Set(0.0, 1.0, 0.0);
		m_vc.camera.rot.Set(0.0, 0.0, 0.0);
		break;

	case LOCATION_FAR: // far
		m_vc.camera.pos.Set(0.0, 0.0, 9.0);
		m_vc.camera.at.Set(0.0, 0.0, 0.0);
		m_vc.camera.up.Set(0.0, 1.0, 0.0);
		m_vc.camera.rot.Set(0.0, 0.0, 0.0);
		break;

	case LOCATION_INSIDE: // inside
		m_vc.camera.pos.Set(0.0, 0.0, 0.0);
		m_vc.camera.at.Set(0.0, 0.0, 1.0);
		m_vc.camera.up.Set(0.0, 1.0, 0.0);
		m_vc.camera.rot.Set(0.0, 0.0, 0.0);
		break;

	case LOCATION_FOLLOWPOLES:
	if (m_vs.reconState < 	APP_MEDIAL_AXIS)
	{
		MessageBox("Cannot follow pole: poles must be computed first!", MB_OK);
		return;
	}

		v = Vertex3::GetVertex(m_vc.sampleId);
		pos.Set(v->normal);

		m_vc.camera.pos.Set(pos.x, pos.y, pos.z);
		m_vc.camera.at.Set(v->x, v->y, v->z);
		m_vc.camera.up.Set(0.0, 1.0, 0.0);
		m_vc.camera.rot.Set(0.0, 0.0, 0.0);
		break;

	default:
        break;
	}

	Invalidate(FALSE);	
}

void CSmevView::OnContextMenu(CWnd* pWnd, CPoint point) 
{
	CPoint pos = point;
	ScreenToClient(&pos);

	CRect rect;
	GetClientRect(&rect);
	// rect.bottom /= 2; // use only half client view

	if (rect.PtInRect(pos))
	{
		CMenu menu;
		menu.LoadMenu(IDR_CONTEXTMENU_CONTROL);

		CMenu * pContextMenu = menu.GetSubMenu(0); 

		int nCmd = (int)pContextMenu->TrackPopupMenu(TPM_LEFTALIGN |
			TPM_LEFTBUTTON | TPM_RIGHTBUTTON,
			point.x, point.y, AfxGetMainWnd());

		switch(nCmd)
		{
		case ID_CONTEXT_CTRL_TRANSLATE_XY:
			break;

		case ID_CONTEXT_CTRL_ROTATE_XY:
			break;

		case ID_CONTEXT_CTRL_ROTRANS_Z:
			break;

		case ID_CONTEXT_CTRL_PICK_VERTEX:
			break;

		case ID_CONTEXT_CTRL_PICK_TRIANGLE:
			break;

		case ID_CONTEXT_CTRL_PICK_TETRAHEDRON:
			break;
		}

		return;
	}
	CWnd::OnContextMenu(pWnd, point);
	
}

void CSmevView::OnViewLightToggle() 
{
	m_vc.visualizer.SetVisibleLighting(!m_vc.visualizer.IsVisibleLighting());
	Invalidate(FALSE);
}

void CSmevView::OnUpdateViewLightToggle(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_vc.visualizer.IsVisibleLighting() == true);
	
}

void CSmevView::OnFileNew() 
{
	MessageBox("All current data will be deleted", MB_OK);
	DeleteAll();

	// vertex count and face count is initialized 
	// to zero by the object constructor
    m_vc.obj = new Skeleton; 

	Vertex3::SetGlobalVertexCount(m_vc.obj->vertCount);
	m_vc.visualizer.SetVisibleDataSet3(false);


	Vertex3 origin(0.0, 0.0, 0.0);
	m_vc.box.SetBoundingBox(origin, origin);


	m_vs.reconState = APP_EMPTY;

	Invalidate(FALSE);
}

void CSmevView::IntroductionMessage()
{

	CDlgIntro dlg;
	dlg.DoModal();	
}

UINT WorkerThreadTetrahedralizer(LPVOID pParam)
{
	CSmevView* pView = (CSmevView*)pParam;

	pView->m_vs.reconState = APP_DELAUNAY;	
	pView->m_tetrahedralizer.Build(pView->m_vc.tetraList);

	return 0;
}

void CSmevView::OnToolsFlipVertexNormals() 
{
	FlipVertexNormals(Vertex3::GetGlobalVertexList(), Vertex3::GetGlobalVertexCount());	
	Invalidate(FALSE);
}
