#if !defined(AFX_LEFTPANE_H__FD108CC0_219D_11D5_BBDC_444553540001__INCLUDED_)
#define AFX_LEFTPANE_H__FD108CC0_219D_11D5_BBDC_444553540001__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// LeftPane.h : header file
//
#include "DialogBarEx.h"

/////////////////////////////////////////////////////////////////////////////
// CGeomTreeCtrl window

class CGeomTreeCtrl : public CTreeCtrl
{
// Construction
public:
	CGeomTreeCtrl();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGeomTreeCtrl)
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	void Initialize();
	void ResetTree();
	HTREEITEM m_TreeRoot;

	BOOL		m_bDragging;
	HTREEITEM	m_hitemDrag;
	HTREEITEM	m_hitemDrop;
	CImageList	*m_pimagelist;

	virtual ~CGeomTreeCtrl();

	// Generated message map functions
protected:
	//{{AFX_MSG(CGeomTreeCtrl)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CLeftPane dialog

class CLeftPane : public CDialogBarEx
{
public:
	HTREEITEM	m_rghItem[12];
	HTREEITEM	m_hitemDrag;
	HTREEITEM	m_hitemDrop;

// Construction
public:
	virtual void OnInitDialogBar();
	CLeftPane(); //(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CLeftPane)
	enum { IDD = IDD_DIALOGBAR };
	CGeomTreeCtrl	m_ctrlGeometryTree;
	BOOL	m_bConvexHull;
	BOOL	m_bCrustEdges;
	BOOL	m_bDelaunay;
	BOOL	m_bMedialAxis;
	BOOL	m_bPointCloud;
	BOOL	m_bVertexNormals;
	BOOL	m_bMedialBalls;
	BOOL	m_bVoronoiCell;
	BOOL	m_bVoronoiDiagram;
	BOOL	m_bVoronoiVertices;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLeftPane)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CLeftPane)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LEFTPANE_H__FD108CC0_219D_11D5_BBDC_444553540001__INCLUDED_)
