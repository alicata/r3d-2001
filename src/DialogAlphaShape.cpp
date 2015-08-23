// DialogAlphaShape.cpp : implementation file
//

#include "stdafx.h"
#include "smev.h"
#include "SmevView.h"
#include "DialogAlphaShape.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DialogAlphaShape dialog


DialogAlphaShape::DialogAlphaShape(CWnd* pParent /*=NULL*/)
	: CDialog()
{
	Create(DialogAlphaShape::IDD, pParent);
	//{{AFX_DATA_INIT(DialogAlphaShape)
	m_nAlphaValue = 0;
	m_bDirection = FALSE;
	//}}AFX_DATA_INIT
}


void DialogAlphaShape::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DialogAlphaShape)
	DDX_Control(pDX, IDC_SLIDER_ALPHA_SHAPE, m_alpha);
	DDX_Text(pDX, IDC_EDIT_ALPHA_VALUE, m_nAlphaValue);
	DDV_MinMaxInt(pDX, m_nAlphaValue, 0, 999);
	DDX_Check(pDX, IDC_CHECK_INVERT, m_bDirection);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DialogAlphaShape, CDialog)
	//{{AFX_MSG_MAP(DialogAlphaShape)
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_CHECK_INVERT, OnCheckInvert)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DialogAlphaShape message handlers

void DialogAlphaShape::PostNcDestroy() 
{

	CDialog::PostNcDestroy();
	delete this;
}

void DialogAlphaShape::OnCancel() 
{

	CDialog::OnCancel();
	DestroyWindow();
}

void DialogAlphaShape::OnOK() 
{

	CDialog::OnOK();
	DestroyWindow();
}

BOOL DialogAlphaShape::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// set radius-filter range 
	m_alpha.SetRange(0, 999);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void DialogAlphaShape::SetView(CSmevView* pView)
{
	// stoore current view
	m_pView = pView;
}

void DialogAlphaShape::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	if ((CSliderCtrl *)pScrollBar == &m_alpha)
	{
		m_pView->m_nAlphaShapeValue = m_alpha.GetPos();
		m_nAlphaValue = m_alpha.GetPos();
		UpdateData(FALSE);

		double dRadius = ((double)m_nAlphaValue)/200.0;  
		m_pView->SetAlphaShapeParameter(dRadius);
		m_pView->Invalidate(FALSE);	
	}
	else
	{
		CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
	}
}

void DialogAlphaShape::OnCheckInvert() 
{
		m_pView->m_vc.visualizer.SetAlphaParamDirection(!m_pView->m_vc.visualizer.GetAlphaParamDirection());
		m_pView->Invalidate(FALSE);		
}
