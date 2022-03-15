#if !defined(AFX_ERRORDLG_H__AB2FAE5F_A668_4BE1_AB57_D26BAC6FF4A8__INCLUDED_)
#define AFX_ERRORDLG_H__AB2FAE5F_A668_4BE1_AB57_D26BAC6FF4A8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ErrorDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CErrorDlg dialog

class CErrorDlg : public CDialog
{
// Construction
public:
	CErrorDlg(CWnd* pParent = NULL);   // standard constructor
	_RecordsetPtr  m_recordset;
	_ConnectionPtr m_pAppConn; //连接对象指针
	CString str;
	CFont g_Font;
	CString Q, R, S;

// Dialog Data
	//{{AFX_DATA(CErrorDlg)
	enum { IDD = IDD_ERROR };
	CListCtrl	m_listerror;
	CString	m_xishu;
	CString	c_xishu;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CErrorDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CErrorDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();
	afx_msg void SetQS();
	afx_msg void SetR();
	afx_msg void OnSetm45();
	afx_msg void OnReport();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ERRORDLG_H__AB2FAE5F_A668_4BE1_AB57_D26BAC6FF4A8__INCLUDED_)
