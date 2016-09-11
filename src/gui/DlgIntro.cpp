// DlgIntro.cpp : implementation file
//

#include "stdafx.h"
#include "smev.h"
#include "DlgIntro.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgIntro dialog


CDlgIntro::CDlgIntro(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgIntro::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgIntro)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgIntro::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgIntro)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgIntro, CDialog)
	//{{AFX_MSG_MAP(CDlgIntro)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgIntro message handlers
