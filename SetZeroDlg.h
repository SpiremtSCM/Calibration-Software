#if !defined(AFX_SETZERODLG_H__3BE39FEE_CD8A_4D19_9449_0325FD86B85A__INCLUDED_)
#define AFX_SETZERODLG_H__3BE39FEE_CD8A_4D19_9449_0325FD86B85A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetZeroDlg.h : header file
//
#include "CollectDlg.h"
#include "ShowDlg.h"

/////////////////////////////////////////////////////////////////////////////
// CSetZeroDlg dialog

class CSetZeroDlg : public CDialog
{
// Construction
public:
	CSetZeroDlg(CWnd* pParent = NULL);   // standard constructor
	CString str;
	CFont *m_Font;
	CFont g_Font;
	CBrush m_brush;  
	_ConnectionPtr m_pAppConn;  
	_RecordsetPtr  m_recordset;
	CCollectDlg collectdlg;
	int m_flag;
	CShowDlg *showdlg;
	CWinThread* thread;
	CWinThread* pThread;
	~CSetZeroDlg();
// Dialog Data
	//{{AFX_DATA(CSetZeroDlg)
	enum { IDD = IDD_SET_ZERO };
	CTabCtrl	m_tab;
	CString	m_m41;
	CString m_wait_time, m_sample_time;
	CString v_max, v_mid, v_low;
	CString	m_show;
	int m_delay;
	float v_max_f, v_mid_f, v_low_f;
	int dlgResult;
	bool SetZeroComplete;
	bool ManualSetZero;
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSetZeroDlg)
	protected:
		int OnStart;
		virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSetZeroDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnM42();
	afx_msg void OnM41();
	afx_msg void OnM42_Cal();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnM_2();
	afx_msg void OnCollect();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnCollect2();
	afx_msg void OnCollect3();
	afx_msg void OnClose();
	afx_msg void OnDestroy();
	//afx_msg void PostNcDestroy();
	afx_msg void OnPaint();
	afx_msg void OnButtonShow();
	afx_msg void OnMove(int x, int y);
	afx_msg LRESULT OnMyMessage2(WPARAM wParam, LPARAM lParam);
	afx_msg void OnMax();
	afx_msg void OnMid();
	afx_msg void OnMin();
	afx_msg void OnCloseValve();
	afx_msg void OnCalibrate();
	afx_msg void OnCalibrate_2();
	afx_msg void OnChangeEditWaitTime();
	afx_msg void OnChangeEditSampleTime();
	afx_msg void OnChangeVCMax();
	afx_msg void OnChangeVCMid();
	afx_msg void OnChangeVCLow();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedFlush();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETZERODLG_H__3BE39FEE_CD8A_4D19_9449_0325FD86B85A__INCLUDED_)
