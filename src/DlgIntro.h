#if !defined(AFX_DLGINTRO_H__40395B20_3A90_11D5_BBDC_444553540001__INCLUDED_)
#define AFX_DLGINTRO_H__40395B20_3A90_11D5_BBDC_444553540001__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// DlgIntro.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgIntro dialog

class CDlgIntro : public CDialog
{
// Construction
public:
	CDlgIntro(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgIntro)
	enum { IDD = IDD_DIALOG_INTRODUCTION };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgIntro)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgIntro)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGINTRO_H__40395B20_3A90_11D5_BBDC_444553540001__INCLUDED_)
