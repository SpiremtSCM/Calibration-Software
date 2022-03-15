#if !defined(AFX_ANALYSISDLG_H__A2D01BE2_9FFB_47E5_991E_7003490AB631__INCLUDED_)
#define AFX_ANALYSISDLG_H__A2D01BE2_9FFB_47E5_991E_7003490AB631__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AnalysisDlg.h : header file
#include "ErrorDlg.h"
//

/////////////////////////////////////////////////////////////////////////////
// CAnalysisDlg dialog

class CAnalysisDlg : public CDialog
{
// Construction
public:
	CAnalysisDlg(CWnd* pParent = NULL);   // standard constructor
	_ConnectionPtr m_pAppConn; //连接对象指针 
	_RecordsetPtr  m_recordset;
	CString m_str;
	CFont g_font;
	CErrorDlg errordlg;
	float fdata[3][6];
	float wucha[3][3];
	float xzwucha[3][3];
	float xishu[20];
	float xzxishu[20];
	int check[20];


// Dialog Data
	//{{AFX_DATA(CAnalysisDlg)
	enum { IDD = IDD_ANALYSIS };
	CListCtrl	m_list;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAnalysisDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAnalysisDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnCheckout();
	afx_msg void OnClose();
	afx_msg void OnDblclkListAnalysis(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ANALYSISDLG_H__A2D01BE2_9FFB_47E5_991E_7003490AB631__INCLUDED_)
