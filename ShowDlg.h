#if !defined(AFX_SHOWDLG_H__3B9DE67D_C5AD_49D3_94B5_0CF0AA41026C__INCLUDED_)
#define AFX_SHOWDLG_H__3B9DE67D_C5AD_49D3_94B5_0CF0AA41026C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ShowDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CShowDlg dialog

class CShowDlg : public CDialog
{
// Construction
public:
	CFont g_font;
	CShowDlg(CWnd* pParent = NULL);   // standard constructor
	int m_flag;

// Dialog Data
	//{{AFX_DATA(CShowDlg)
	enum { IDD = IDD_SHOW };
	CListCtrl m_list;
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CShowDlg)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CShowDlg)
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg LRESULT OnMyMessage(WPARAM wParam, LPARAM lParam);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnClose();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SHOWDLG_H__3B9DE67D_C5AD_49D3_94B5_0CF0AA41026C__INCLUDED_)
