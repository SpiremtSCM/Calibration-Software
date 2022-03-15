#if !defined(AFX_SETDLG_H__03D8720A_111E_40CD_8344_5DA8359FBB17__INCLUDED_)
#define AFX_SETDLG_H__03D8720A_111E_40CD_8344_5DA8359FBB17__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetDlg.h : header file
//
#include "LineArrayDlg.h"

/////////////////////////////////////////////////////////////////////////////
// CSetDlg dialog

class CSetDlg : public CDialog
{
// Construction
public:
	CFont g_font;
	CString m_meterno;   //表号
	CString str; 
	CString str1;
	CLineArrayDlg line_array;

	_ConnectionPtr m_pAppConn; //连接对象指针 
	_RecordsetPtr  m_recordset;

	int leixing;
	CString jiaodu;
	CString shengsu;
	CString juli;
	CString shijian;
	int pinlv;
	int fangfa;
	CString xishu;

	CSetDlg(CWnd* pParent = NULL);   // standard constructor
// Dialog Data
	//{{AFX_DATA(CSetDlg)
	enum { IDD = IDD_SET };
	CString	m_m11;
	CString	m_m12;
	CString	m_m13;
	CString	m_m18;
	CString	m_m40;
	CString	m_m45;
	CString	m_m231;
	CString	m_m232;
	CString	m_m233;
	CString	m_m234;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSetDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSetDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnM11();
	afx_msg void OnM30();
	afx_msg void OnM12();
	afx_msg void OnM13();
	afx_msg void OnUpdateM14();
	afx_msg void OnM14();
	afx_msg void OnUpdateM16();
	afx_msg void OnM16();
	afx_msg void OnM18();
	afx_msg void OnUpdateM20();
	afx_msg void OnM20();
	afx_msg void OnUpdateM31();
	afx_msg void OnM31();
	afx_msg void OnUpdateM32();
	afx_msg void OnM32();
	afx_msg void OnUpdateM33();
	afx_msg void OnM33();
	afx_msg void OnM34();
	afx_msg void OnM35();
	afx_msg void OnM36();
	afx_msg void OnM37();
	afx_msg void OnOk();
	afx_msg void OnUpdateM39();
	afx_msg void OnM39();
	afx_msg void OnM40();
	afx_msg void OnUpdateM79();
	afx_msg void OnM79();
	afx_msg void OnSelchangeComboMeter();
	afx_msg void OnUpdateM24();
	afx_msg void OnUpdateM26();
	afx_msg void OnM25();
	afx_msg void OnM26();
	afx_msg void OnM45();
	afx_msg void OnM23();
	afx_msg void OnQuickSet2();
	afx_msg void OnQuickSet();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnClose();
	afx_msg void OnDestroy();
	afx_msg void OnM24();
	afx_msg void OnM48();
	afx_msg void OnM231();
	afx_msg void OnM232();
	afx_msg void OnM233();
	afx_msg void OnM234();
	afx_msg void OnCopy();
	afx_msg void OnChangeEditM11();
	afx_msg void OnChangeEditM12();
	afx_msg void OnMulset();
	afx_msg void OnPaste();
	afx_msg void OnSelchangeComboM23();
	afx_msg void OnSelchangeComboM24();
	afx_msg void OnChangeEditM231();
	afx_msg void OnChangeEditM232();
	afx_msg void OnChangeEditM233();
	afx_msg void OnChangeEditM234();
	afx_msg void OnRadio1();
	afx_msg void OnRadio2();
	afx_msg void OnSelchangeComboM16();
	afx_msg void OnRadio9();
	afx_msg void OnRadio10();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETDLG_H__03D8720A_111E_40CD_8344_5DA8359FBB17__INCLUDED_)
