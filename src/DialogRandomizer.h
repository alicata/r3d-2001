#if !defined(AFX_DIALOGRANDOMIZER_H__F3314131_1C95_11D5_A8B1_1470F8000000__INCLUDED_)
#define AFX_DIALOGRANDOMIZER_H__F3314131_1C95_11D5_A8B1_1470F8000000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DialogRandomizer.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDialogRandomizer dialog

class CDialogRandomizer : public CDialog
{
// Construction
public:
	CDialogRandomizer(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDialogRandomizer)
	enum { IDD = IDD_DIALOG_RANDOMIZER };
	UINT	m_nRandomPercentage;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialogRandomizer)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDialogRandomizer)
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	static UINT ScrollBarValue(CScrollBar* pScrollBar, UINT nSBCode, UINT nSBPos);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGRANDOMIZER_H__F3314131_1C95_11D5_A8B1_1470F8000000__INCLUDED_)
