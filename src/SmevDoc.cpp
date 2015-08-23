// SmevDoc.cpp : implementation of the CSmevDoc class
//

#include "stdafx.h"
#include "Smev.h"

#include "SmevDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSmevDoc

IMPLEMENT_DYNCREATE(CSmevDoc, CDocument)

BEGIN_MESSAGE_MAP(CSmevDoc, CDocument)
	//{{AFX_MSG_MAP(CSmevDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSmevDoc construction/destruction

CSmevDoc::CSmevDoc()
{
	// TODO: add one-time construction code here

}

CSmevDoc::~CSmevDoc()
{
}

BOOL CSmevDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CSmevDoc serialization

void CSmevDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CSmevDoc diagnostics

#ifdef _DEBUG
void CSmevDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSmevDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSmevDoc commands
