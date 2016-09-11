// DialogRandomizer.cpp : implementation file
//

#include "stdafx.h"
#include "Smev.h"
#include "DialogRandomizer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialogRandomizer dialog


CDialogRandomizer::CDialogRandomizer(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogRandomizer::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialogRandomizer)
	m_nRandomPercentage = 0;
	//}}AFX_DATA_INIT

	m_nRandomPercentage = 50;
}


void CDialogRandomizer::DoDataExchange(CDataExchange* pDX)
{
	// from object to dialog box
	if (!pDX->m_bSaveAndValidate)
	{
		// set range for scroll bar
		CScrollBar *psbControl;

		psbControl = (CScrollBar*)GetDlgItem(IDC_SCROLLBAR_RANDOMIZER);
		ASSERT_VALID(psbControl);
		psbControl->SetScrollRange(0, 99, FALSE);
		psbControl->SetScrollPos(m_nRandomPercentage);
	}

	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogRandomizer)
	DDX_Text(pDX, IDC_EDIT_RANDOMIZER, m_nRandomPercentage);
	DDV_MinMaxUInt(pDX, m_nRandomPercentage, 0, 100);
	//}}AFX_DATA_MAP

	// from dialog box to object
	if (pDX->m_bSaveAndValidate)
	{
		
	}
}


BEGIN_MESSAGE_MAP(CDialogRandomizer, CDialog)
	//{{AFX_MSG_MAP(CDialogRandomizer)
	ON_WM_HSCROLL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialogRandomizer message handlers

void CDialogRandomizer::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	nPos = ScrollBarValue(pScrollBar, nSBCode, nPos);

	// update corresponding edit box
	int nSourceID = pScrollBar->GetDlgCtrlID();

	switch (nSourceID)
	{
	case IDC_SCROLLBAR_RANDOMIZER:
		SetDlgItemInt(IDC_EDIT_RANDOMIZER, nPos);
		break;

	default:
		TRACE("Unreconized dialog control id receiver\n");
	}
}

UINT CDialogRandomizer::ScrollBarValue(CScrollBar * pScrollBar, UINT nSBCode, UINT nSBPos)
{
	// current scrollbar position
	int nPos = pScrollBar->GetScrollPos();

	// current range
	int nMinPos, nMaxPos;
	pScrollBar->GetScrollRange(&nMinPos, &nMaxPos);

	// the sbcode tells you what to do
	switch (nSBCode)
	{
	case SB_LEFT:
		nPos = nMinPos;
		break;

	case SB_RIGHT:
		nPos = nMaxPos;
		break;

	case SB_LINELEFT:
		nPos = max(nPos - 1, nMinPos);
		break;

	case SB_LINERIGHT:
		nPos = min(nPos + 1, nMaxPos);
		break;

	case SB_PAGERIGHT:
		nPos = min(nPos + 10, nMaxPos);
		break;

	case SB_PAGELEFT:
		nPos = max(nPos - 10, nMinPos);

	case SB_THUMBPOSITION:
	case SB_THUMBTRACK:
		nSBPos = min((int)nSBPos, nMaxPos);
		nSBPos = max((int)nSBPos, nMinPos);
		nPos = nSBPos;
		break;

	case SB_ENDSCROLL:
		break;

	default:
		TRACE("Uknown SBCode\n");
	}

	// update scroll bar
	pScrollBar->SetScrollPos(nPos);

	return nPos;
}
