#if !defined(AFX_INSTALLDLG_H__4EA9C07B_603A_45F3_826A_A6B99B8178FF__INCLUDED_)
#define AFX_INSTALLDLG_H__4EA9C07B_603A_45F3_826A_A6B99B8178FF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// InstallDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CInstallDlg dialog

class CInstallDlg : public CDialog
{
// Construction
	CFont g_font;

public:
	void GetM25();
	BOOL CheckR(int i);
	BOOL CheckQ(int i);
	BOOL CheckS(int i);
	BOOL CheckM45(CString meter_no);
	BOOL CheckM25(CString meter_no);
	BOOL CheckM24(CString meter_no);
	BOOL CheckM23(CString meter_no);
	BOOL CheckM79();
	BOOL CheckM40();
	BOOL CheckM39();
	BOOL CheckM36();
	BOOL CheckM35();
	BOOL CheckM34();
	BOOL CheckM33();
	BOOL CheckM32();
	BOOL CheckM31();
	BOOL CheckM20();
	BOOL CheckM18();
	BOOL CheckM16();
	BOOL CheckM14();
	BOOL CheckM13();
	BOOL CheckM12();
	BOOL CheckM11();
	void GetR();
	void GetS_Q();
	CInstallDlg(CWnd* pParent = NULL);   // standard constructor
	CString str;                         //发送到表的消息	
	CString str1;                        //str1 = W前缀 + 表号
	_ConnectionPtr m_pAppConn; //连接对象指针 
	_RecordsetPtr  m_recordset;
	CString strBeg;
	int line;
	int biaoleixing;
	int gyz;

// Dialog Data
	//{{AFX_DATA(CInstallDlg)
	enum { IDD = IDD_INSTALL };
	CListCtrl	m_list;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInstallDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CInstallDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnCheckout();
	afx_msg void OnUpdate();
	afx_msg void OnClose();
	afx_msg void OnDestroy();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INSTALLDLG_H__4EA9C07B_603A_45F3_826A_A6B99B8178FF__INCLUDED_)
