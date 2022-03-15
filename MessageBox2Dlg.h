#if !defined(AFX_MESSAGEBOX2DLG_H__0C9B8F5C_D1BF_4B2A_9588_9B6339E6506B__INCLUDED_)
#define AFX_MESSAGEBOX2DLG_H__0C9B8F5C_D1BF_4B2A_9588_9B6339E6506B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MessageBox2Dlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMessageBox2Dlg dialog

class CMessageBox2Dlg : public CDialog
{
// Construction
public:
	CMessageBox2Dlg(CWnd* pParent = NULL);   // standard constructor
	CFont g_Font;

// Dialog Data
	//{{AFX_DATA(CMessageBox2Dlg)
	enum { IDD = IDD_MESSAGEBOX2 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMessageBox2Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMessageBox2Dlg)
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MESSAGEBOX2DLG_H__0C9B8F5C_D1BF_4B2A_9588_9B6339E6506B__INCLUDED_)
