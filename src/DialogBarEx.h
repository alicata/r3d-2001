#if !defined(AFX_DIALOGBAREX_H__D614B256_C5EC_11D2_B8C5_B41E04C10000__INCLUDED_)
#define AFX_DIALOGBAREX_H__D614B256_C5EC_11D2_B8C5_B41E04C10000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// DialogBarEx.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDialogBarEx window

/*
Class written by Sharad Kelkar drssk@ad1.vsnl.net.in
This is freeware without any kind of restriction on usage
and distribution.
*/


class CDialogBarEx : public CDialogBar 
{
// Construction
public:
	CDialogBarEx();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialogBarEx)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual void OnInitDialogBar();
	virtual ~CDialogBarEx();

	// Generated message map functions
	// Note from Sharad Kelkar
	// We have manually added entry afx_msg InitDialogBarHandler
	// as it was not done automatically by Class Wizard

protected:
	//{{AFX_MSG(CDialogBarEx)
	afx_msg void InitDialogBarHandler( WORD wParam , DWORD  lParam );
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGBAREX_H__D614B256_C5EC_11D2_B8C5_B41E04C10000__INCLUDED_)
