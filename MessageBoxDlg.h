#if !defined(AFX_MESSAGEBOXDLG_H__2BCD1A76_196E_4520_A11F_F070919D2D53__INCLUDED_)
#define AFX_MESSAGEBOXDLG_H__2BCD1A76_196E_4520_A11F_F070919D2D53__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MessageBoxDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMessageBoxDlg dialog

class CMessageBoxDlg : public CDialog
{
// Construction
public:
	CMessageBoxDlg(CWnd* pParent = NULL);   // standard constructor
	CFont g_Font;
// Dialog Data
	//{{AFX_DATA(CMessageBoxDlg)
	enum { IDD = IDD_MESSAGEBOX };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMessageBoxDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMessageBoxDlg)
	virtual void OnCancel();
	afx_msg void OnStart();
	virtual BOOL OnInitDialog();

	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MESSAGEBOXDLG_H__2BCD1A76_196E_4520_A11F_F070919D2D53__INCLUDED_)
