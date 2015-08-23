// LeftPane.cpp : implementation file
//

#include "stdafx.h"
#include "smev.h"
#include "DialogBarEx.h"
#include "LeftPane.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define CELEMS(rgFoo) (sizeof(rgFoo) / sizeof(rgFoo[0]))
/////////////////////////////////////////////////////////////////////////////
// CLeftPane dialog


CLeftPane::CLeftPane()//CWnd* pParent /*=NULL*/)
	//: CDialogBarEx(CLeftPane::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLeftPane)
	m_bConvexHull = FALSE;
	m_bCrustEdges = FALSE;
	m_bDelaunay = FALSE;
	m_bMedialAxis = FALSE;
	m_bPointCloud = FALSE;
	m_bVertexNormals = FALSE;
	m_bMedialBalls = FALSE;
	m_bVoronoiCell = FALSE;
	m_bVoronoiDiagram = FALSE;
	m_bVoronoiVertices = FALSE;
	//}}AFX_DATA_INIT
	OnInitDialogBar();
}


void CLeftPane::DoDataExchange(CDataExchange* pDX)
{
	CDialogBarEx::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLeftPane)
	DDX_Check(pDX, IDC_CHECKCONVEXHULL, m_bConvexHull);
	DDX_Check(pDX, IDC_CHECKCRUSTEDGES, m_bCrustEdges);
	DDX_Check(pDX, IDC_CHECKDELAUNAY, m_bDelaunay);
	DDX_Check(pDX, IDC_CHECKMEDIALAXIS, m_bMedialAxis);
	DDX_Check(pDX, IDC_CHECKPOINTCLOUD, m_bPointCloud);
	DDX_Check(pDX, IDC_CHECKVERTNORMAL, m_bVertexNormals);
	DDX_Check(pDX, IDC_CHECKMedialBall, m_bMedialBalls);
	DDX_Check(pDX, IDC_CHECKVOROCELL, m_bVoronoiCell);
	DDX_Check(pDX, IDC_CHECKVORODIAGRAM, m_bVoronoiDiagram);
	DDX_Check(pDX, IDC_CHECKVORONOIVERTICES, m_bVoronoiVertices);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLeftPane, CDialogBarEx)
	//{{AFX_MSG_MAP(CLeftPane)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLeftPane message handlers

void CLeftPane::OnInitDialogBar()
{
	m_bConvexHull = FALSE;
	m_bCrustEdges = FALSE;
	m_bDelaunay = FALSE;
	m_bMedialAxis = FALSE;
	m_bPointCloud = TRUE;
	m_bVertexNormals = FALSE;
	m_bMedialBalls = FALSE;
	m_bVoronoiCell = FALSE;
	m_bVoronoiDiagram = FALSE;
	m_bVoronoiVertices = FALSE;

	/*
	CImageList			*pimagelist;
	CBitmap				bitmap;
	CSmevApp			*pApp;
	int					iItem;
	UINT				nID;
	TV_INSERTSTRUCT		tvstruct;
	TCHAR				rgszItems[][18] = {_T("Dogs"), _T("German Shepherd"), _T("Dalmatian"), _T("Great Dane"),
								_T("Birds"), _T("Hummingbird"), _T("Pigeon"), _T("Eagle"),
								_T("Fish"), _T("Snapper"), _T("Sole"), _T("Salmon")};

	pApp = (CSmevApp *)AfxGetApp();
	//::OnInitDialog();  // let the base class do the default work
	pimagelist = new CImageList();
	

	pimagelist->Create(32, 16, TRUE, 6, 4);

	
	for (nID = IDB_BMTREE_FACE; nID <= IDB_BMTREE_VERTEX_SELECTED; nID++)  // load bitmaps for dog, bird and fish
	{
		bitmap.LoadBitmap(nID);
		pimagelist->Add(&bitmap, (COLORREF)0xFFFFFF);
		bitmap.DeleteObject();
	}

	m_ctrlGeometryTree.SetImageList(pimagelist, TVSIL_NORMAL);
	for (iItem = 0; iItem < CELEMS(rgszItems); iItem ++)
	{
		tvstruct.hParent = (iItem % 4 == 0)? NULL : m_rghItem[iItem / 4 * 4];
		tvstruct.hInsertAfter = TVI_SORT;
		tvstruct.item.iImage = iItem / 4 * 2;
		tvstruct.item.iSelectedImage = tvstruct.item.iImage + 1;
		tvstruct.item.pszText = rgszItems[iItem];
		tvstruct.item.mask = TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_TEXT;
		m_rghItem[iItem] = m_ctrlGeometryTree.InsertItem(&tvstruct);
	}*/

	return;
}
/////////////////////////////////////////////////////////////////////////////
// CGeomTreeCtrl

CGeomTreeCtrl::CGeomTreeCtrl()
{
	m_bDragging = FALSE;
	m_pimagelist = NULL;
}

CGeomTreeCtrl::~CGeomTreeCtrl()
{
}


BEGIN_MESSAGE_MAP(CGeomTreeCtrl, CTreeCtrl)
	//{{AFX_MSG_MAP(CGeomTreeCtrl)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGeomTreeCtrl message handlers


void CGeomTreeCtrl::ResetTree()
{
	DeleteAllItems();	// CLEAR THE CONTROL
	m_TreeRoot = InsertItem( "Point Cloud", TVI_ROOT, TVI_LAST );
	// SET THE ROOT DATA TO NULL
	SetItemData( m_TreeRoot, NULL );
}

int CGeomTreeCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CTreeCtrl::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	
	return 0;
}

BOOL CGeomTreeCtrl::PreCreateWindow(CREATESTRUCT& cs) 
{
	CString className;
	HCURSOR arrow;
	
	// TODO: do you need this line???
	arrow = AfxGetApp()->LoadStandardCursor(IDC_ARROW);	

	return CTreeCtrl::PreCreateWindow(cs);
}

void CGeomTreeCtrl::Initialize()
{
	/*	
	PSTR pszTreeRoots[] = 
	{	
		_T("Point Cloud 1"), 
		_T("Point Cloud 2") 
	};

	int numItems = 1;
	//HTREEITEM rootItems[2];

	for (int i = 0; i < numItems; i++)
	{
		m_ctrlGeometryTree.m_TreeRoot = m_ctrlGeometryTree.InsertItem(
			TVIF_PARAM | TVIF_TEXT,
			pszTreeRoots[i], i, i, 0, 0, 
			-1, TVI_ROOT, TVI_LAST);
	}

	*/

	/*
	m_TreeRoot = InsertItem( "Point Cloud", TVI_ROOT, TVI_LAST );
	// SET THE ROOT DATA TO NULL
	//SetItemData( m_TreeRoot, NULL );
		SetItemData( m_TreeRoot, (DWORD)NULL );
		*/
}

