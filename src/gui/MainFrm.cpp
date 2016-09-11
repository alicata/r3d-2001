// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "Smev.h"
#include "SmevDoc.h"
#include "SmevView.h"

#include "MainFrm.h"
#include "LeftPane.h"
 
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_PALETTECHANGED()
	ON_WM_QUERYNEWPALETTE()
	//}}AFX_MSG_MAP
	// Global help commands
	ON_COMMAND(ID_HELP_FINDER, CFrameWnd::OnHelpFinder)
	ON_COMMAND(ID_HELP, CFrameWnd::OnHelp)
	ON_COMMAND(ID_CONTEXT_HELP, CFrameWnd::OnContextHelp)
	ON_COMMAND(ID_DEFAULT_HELP, CFrameWnd::OnHelpFinder)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	
	if ( ! m_mainPanel.Create(this, IDD_DIALOGBAR, 
		CBRS_LEFT , IDD_DIALOGBAR))
	{
		TRACE0("Failed to create dialog bar from CLeftPanel class\n");
		return -1;      // fail to create
	}
	
	//m_mainPanel.SetWindowText("This is docking dialog bar");
 	//m_mainPanel.EnableDocking(CBRS_ALIGN_LEFT);
	//DockControlBar(&m_mainPanel);
	

	/*
	if (!m_mainPanel.Create(this, IDD_DIALOGBAR,
		CBRS_LEFT|CBRS_TOOLTIPS|CBRS_FLYBY, IDD_DIALOGBAR))
	{
		TRACE0("Failed to create DlgBar\n");
		return -1;      // fail to create
	}
	*/
	

	if (!m_wndToolBar.Create(this) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}


	if (!m_wndCameraToolBar.Create(this) ||
		!m_wndCameraToolBar.LoadToolBar(IDR_TOOLBAR_CAMERA))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndVoronoiToolBar.Create(this) ||
		!m_wndVoronoiToolBar.LoadToolBar(IDR_TOOLBAR_VORONOI))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

		if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}


	// TODO: Remove this if you don't want tool tips or a resizeable toolbar
	m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);


	// camera toolbar
	// TODO: Remove this if you don't want tool tips or a resizeable toolbar
	m_wndCameraToolBar.SetBarStyle(m_wndCameraToolBar.GetBarStyle() |
		CBRS_TOP | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndCameraToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndCameraToolBar);

	// camera toolbar
	// TODO: Remove this if you don't want tool tips or a resizeable toolbar
	m_wndVoronoiToolBar.SetBarStyle(m_wndVoronoiToolBar.GetBarStyle() |
		CBRS_TOP | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndVoronoiToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndVoronoiToolBar);





	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// remove this flag to remove " - Untitled" from the frame's caption
    cs.style &= ~ FWS_ADDTOTITLE;
	//cs.style |= WS_MAXIMIZE;

	return CFrameWnd::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

void CMainFrame::OnPaletteChanged(CWnd* pFocusWnd) 
{
	// Indicates focus-window (some window) has realized its palette
	CFrameWnd::OnPaletteChanged(pFocusWnd);
	
	if (pFocusWnd != this)
	{
		OnQueryNewPalette();
	}
	
}

BOOL CMainFrame::OnQueryNewPalette() 
{
	// Allows a window to realize it logical palette	
	WORD i;
	CPalette	*pOldPal;
	CSmevView	*pView = (CSmevView *)GetActiveView();
	CClientDC	dc(pView);

	pOldPal = dc.SelectPalette(&pView->m_cPalette, FALSE);
	i = dc.RealizePalette();
	dc.SelectPalette(pOldPal, FALSE);

	if(i > 0)
	{
		InvalidateRect(NULL);
	}
	
	return CFrameWnd::OnQueryNewPalette();
}


