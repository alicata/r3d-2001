#if !defined(AFX_DLGLOCATION_H__BD0F0800_386C_11D5_BBDC_444553540001__INCLUDED_)
#define AFX_DLGLOCATION_H__BD0F0800_386C_11D5_BBDC_444553540001__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// DlgLocation.h : header file
//
#include "SmevView.h"
/////////////////////////////////////////////////////////////////////////////
// CDlgLocation dialog

class CDlgLocation : public CDialog
{
// Construction
public:
	CDlgLocation(CWnd* pParent = NULL);   // standard constructor
	void SetView(CSmevView* pView);
public:
	CSmevView* m_pView;

// Dialog Data
	//{{AFX_DATA(CDlgLocation)
	enum { IDD = IDD_DIALOG_LOCATION };
	int		m_radioLocation;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgLocation)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgLocation)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnRadioFront();
	afx_msg void OnRadioInside();
	afx_msg void OnRadioNear();
	afx_msg void OnRadioSide();
	afx_msg void OnRadioTop();
	afx_msg void OnRadioFollowPole();
	afx_msg void OnRadioFar();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGLOCATION_H__BD0F0800_386C_11D5_BBDC_444553540001__INCLUDED_)
