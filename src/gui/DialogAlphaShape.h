#if !defined(AFX_DIALOGALPHASHAPE_H__2B8B54C1_23B2_11D5_BBDC_444553540001__INCLUDED_)
#define AFX_DIALOGALPHASHAPE_H__2B8B54C1_23B2_11D5_BBDC_444553540001__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// DialogAlphaShape.h : header file
//

#include "SmevView.h"
/////////////////////////////////////////////////////////////////////////////
// DialogAlphaShape dialog

class DialogAlphaShape : public CDialog
{
// Construction
public:
	DialogAlphaShape(CWnd* pParent = NULL);   // standard constructor
	void SetView(CSmevView* pView);
public:
	CSmevView* m_pView;
// Dialog Data
	//{{AFX_DATA(DialogAlphaShape)
	enum { IDD = IDD_DIALOG_ALPHA_SHAPE_PARAM };
	CSliderCtrl	m_alpha;
	int		m_nAlphaValue;
	BOOL	m_bDirection;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DialogAlphaShape)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(DialogAlphaShape)
	virtual void OnCancel();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnCheckInvert();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGALPHASHAPE_H__2B8B54C1_23B2_11D5_BBDC_444553540001__INCLUDED_)
