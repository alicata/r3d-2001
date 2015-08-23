#if !defined(AFX_DLGRECONPROCESS_H__40395B21_3A90_11D5_BBDC_444553540001__INCLUDED_)
#define AFX_DLGRECONPROCESS_H__40395B21_3A90_11D5_BBDC_444553540001__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// DlgReconProcess.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgReconProcess dialog

class CDlgReconProcess : public CDialog
{
// Construction
public:
	UINT m_uiPos;
	UINT m_uiRangeTo;
	UINT m_uiRangeFrom;
	void StepIt();
	void SetPos(UINT uiPos);
	void SetRange(UINT uiRangeFrom, UINT uiRangeTo);
	
	CDlgReconProcess(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgReconProcess)
	enum { IDD = IDD_DIALOG_RECON_PROGRESS };
	CProgressCtrl	m_Progress;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgReconProcess)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgReconProcess)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGRECONPROCESS_H__40395B21_3A90_11D5_BBDC_444553540001__INCLUDED_)
