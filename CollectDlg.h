#if !defined(AFX_COLLECTDLG_H__C9EEE88C_3EA4_476C_B5C7_CEFA1E84E372__INCLUDED_)
#define AFX_COLLECTDLG_H__C9EEE88C_3EA4_476C_B5C7_CEFA1E84E372__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CollectDlg.h : header file
//
/////////////////////////////////////////////////////////////////////////////
// CCollectDlg dialog


class CCollectDlg : public CDialog
{
// Construction
	void db_Setup(CCalibrationApp *app);//YC added temp function, Set up the database and find the meter that can be calibrated;

public:
	CCollectDlg(CWnd* pParent = NULL);   // standard constructor
	_ConnectionPtr m_pAppConn; //连接对象指针 
	_RecordsetPtr  m_recordset;
	int flag;
	int err_ref_count;//For how many times the ref meter has not read successfully
	float collect[20][2000];
	float collect2[2000];
	CString str;
	CFont g_font;
	int Count;

	int Sampling_Gap;//YC Added: gap between each sampling, in msec
	int Sampling_Total;//YC Added: total number of sampling for taking each average. That is, for a flow rate, the total sample should be 3 x Sampling_Total 
	bool To_file;//YC Added: if you want to print all collected data to a txt file?
// Dialog Data
	//{{AFX_DATA(CCollectDlg)
	enum { IDD = IDD_COLLECT };
	CProgressCtrl	m_pro;
	CListCtrl	m_list;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCollectDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCollectDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnClose();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COLLECTDLG_H__C9EEE88C_3EA4_476C_B5C7_CEFA1E84E372__INCLUDED_)
