// Smev.h : main header file for the SMEV application
//

#if !defined(AFX_SMEV_H__5FDFFB67_5F81_11D2_935C_88E504C10000__INCLUDED_)
#define AFX_SMEV_H__5FDFFB67_5F81_11D2_935C_88E504C10000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CSmevApp:
// See Smev.cpp for the implementation of this class
//

class CSmevApp : public CWinApp
{
public:
	CSmevApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSmevApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CSmevApp)
	afx_msg void OnHelpAboutR3d();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SMEV_H__5FDFFB67_5F81_11D2_935C_88E504C10000__INCLUDED_)
