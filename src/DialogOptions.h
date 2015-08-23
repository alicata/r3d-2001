#if !defined(AFX_DIALOGOPTIONS_H__54F3BD20_2867_11D5_BBDC_444553540001__INCLUDED_)
#define AFX_DIALOGOPTIONS_H__54F3BD20_2867_11D5_BBDC_444553540001__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// DialogOptions.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDialogOptions dialog

class CDialogOptions : public CDialog
{
// Construction
public:
	CDialogOptions(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDialogOptions)
	enum { IDD = IDD_DIALOG_OPTIONS };
	int		m_radioBackgroundColor;
	double	m_maxRadiusFactor;
	double	m_normalFactor;
	UINT	m_superFactor;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialogOptions)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDialogOptions)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGOPTIONS_H__54F3BD20_2867_11D5_BBDC_444553540001__INCLUDED_)
