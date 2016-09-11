// DlgReconProcess.cpp : implementation file
//

#include "stdafx.h"
#include "smev.h"
#include "DlgReconProcess.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgReconProcess dialog


CDlgReconProcess::CDlgReconProcess(CWnd* pParent /*=NULL*/)
	: CDialog()
{
	Create(CDlgReconProcess::IDD, pParent);
	//{{AFX_DATA_INIT(CDlgReconProcess)
	//}}AFX_DATA_INIT
	m_uiRangeFrom = 1;
	m_uiRangeTo = 100;
	m_uiPos = 10;
}


void CDlgReconProcess::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgReconProcess)
	DDX_Control(pDX, IDC_PROGRESS1, m_Progress);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgReconProcess, CDialog)
	//{{AFX_MSG_MAP(CDlgReconProcess)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgReconProcess message handlers

BOOL CDlgReconProcess::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_Progress.SetRange( m_uiRangeFrom, m_uiRangeTo );
	m_Progress.SetPos(m_uiPos);

	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgReconProcess::SetRange(UINT uiRangeFrom, UINT uiRangeTo)
{
	UpdateData();
	m_uiRangeFrom = uiRangeFrom;
	m_uiRangeTo = uiRangeTo;
	m_Progress.SetRange( uiRangeFrom, uiRangeTo );
}

void CDlgReconProcess::SetPos(UINT uiPos)
{
	UpdateData();
	m_uiPos = uiPos;
	m_Progress.SetPos(uiPos );
}

void CDlgReconProcess::StepIt()
{
	m_Progress.StepIt();
}

BOOL CDlgReconProcess::DestroyWindow() 
{

	return	CDialog::DestroyWindow();

}

void CDlgReconProcess::OnOK() 
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
	DestroyWindow();
}
