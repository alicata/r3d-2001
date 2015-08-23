// DialogOptions.cpp : implementation file
//

#include "stdafx.h"
#include "smev.h"
#include "DialogOptions.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialogOptions dialog


CDialogOptions::CDialogOptions(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogOptions::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialogOptions)
	m_radioBackgroundColor = -1;
	m_maxRadiusFactor = 0.0;
	m_normalFactor = 0.0;
	m_superFactor = 0;
	//}}AFX_DATA_INIT

	m_radioBackgroundColor = 1;
	m_maxRadiusFactor = 999.99;
	m_normalFactor = 1.0;
	m_superFactor = 2;
}


void CDialogOptions::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogOptions)
	DDX_Radio(pDX, IDC_RADIO1, m_radioBackgroundColor);
	DDX_Text(pDX, IDC_EDIT_MAXRADIUS_FACTOR, m_maxRadiusFactor);
	DDV_MinMaxDouble(pDX, m_maxRadiusFactor, 0., 99999.99);
	DDX_Text(pDX, IDC_EDIT_NORMAL_FACTOR, m_normalFactor);
	DDV_MinMaxDouble(pDX, m_normalFactor, 1.e-002, 9.99);
	DDX_Text(pDX, IDC_EDIT_SUPER_FACTOR, m_superFactor);
	DDV_MinMaxUInt(pDX, m_superFactor, 1, 9);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialogOptions, CDialog)
	//{{AFX_MSG_MAP(CDialogOptions)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialogOptions message handlers
