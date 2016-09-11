// DlgLocation.cpp : implementation file
//

#include "stdafx.h"
#include "smev.h"
#include "DlgLocation.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgLocation dialog


CDlgLocation::CDlgLocation(CWnd* pParent /*=NULL*/)
	: CDialog()
{
	Create(CDlgLocation::IDD, pParent);
	//{{AFX_DATA_INIT(CDlgLocation)
	m_radioLocation = -1;
	//}}AFX_DATA_INIT
}


void CDlgLocation::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgLocation)
	DDX_Radio(pDX, IDC_RADIO_FRONT, m_radioLocation);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgLocation, CDialog)
	//{{AFX_MSG_MAP(CDlgLocation)
	ON_BN_CLICKED(IDC_RADIO_FRONT, OnRadioFront)
	ON_BN_CLICKED(IDC_RADIO_INSIDE, OnRadioInside)
	ON_BN_CLICKED(IDC_RADIO_NEAR, OnRadioNear)
	ON_BN_CLICKED(IDC_RADIO_SIDE, OnRadioSide)
	ON_BN_CLICKED(IDC_RADIO_TOP, OnRadioTop)
	ON_BN_CLICKED(IDC_RADIO_FOLLOW_POLE, OnRadioFollowPole)
	ON_BN_CLICKED(IDC_RADIO_FAR, OnRadioFar)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgLocation message handlers

void CDlgLocation::PostNcDestroy() 
{
	CDialog::PostNcDestroy();
	delete this;
}

void CDlgLocation::OnOK() 
{
	CDialog::OnOK();
	DestroyWindow();
}

BOOL CDlgLocation::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_radioLocation = 0;
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgLocation::SetView(CSmevView* pView)
{
	m_pView = pView;
}


void CDlgLocation::OnRadioFront() 
{
	m_pView->m_cameraLocation = m_radioLocation;
	m_pView->UpdateCameraLocation(LOCATION_FRONT);
}

void CDlgLocation::OnRadioTop() 
{
	m_pView->UpdateCameraLocation(LOCATION_TOP);
}

void CDlgLocation::OnRadioSide() 
{
	m_pView->UpdateCameraLocation(LOCATION_SIDE);
}

void CDlgLocation::OnRadioNear() 
{
	m_pView->UpdateCameraLocation(LOCATION_NEAR);
}

void CDlgLocation::OnRadioInside() 
{
	m_pView->UpdateCameraLocation(LOCATION_INSIDE);
}

void CDlgLocation::OnRadioFollowPole() 
{
	m_pView->UpdateCameraLocation(LOCATION_FOLLOWPOLES);	
}

void CDlgLocation::OnRadioFar() 
{
	m_pView->UpdateCameraLocation(LOCATION_FAR);		
}
