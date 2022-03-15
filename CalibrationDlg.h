// CalibrationDlg.h : header file
//

#if !defined(AFX_CALIBRATIONDLG_H__81E1239B_4B66_4E4F_ADF4_6558B2026620__INCLUDED_)
#define AFX_CALIBRATIONDLG_H__81E1239B_4B66_4E4F_ADF4_6558B2026620__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CnComm.h"
#include "SetDlg.h"
#include "InstallDlg.h"
#include "SetZeroDlg.h"
#include "AnalysisDlg.h"
#include "ShowDlg.h"
#include "ReminderDlg.h"

/////////////////////////////////////////////////////////////////////////////
// CCalibrationDlg dialog

class CCalibrationDlg : public CDialog
{
// Construction

public:
	CString str;
	CFont g_Font;
	int res;
	CCalibrationDlg(CWnd* pParent = NULL);	// standard constructor
	CSetDlg setdlg;
	CInstallDlg installdlg;
	CSetZeroDlg setzerodlg;
	CAnalysisDlg analysisdlg;
	CReminderDlg reminderDlg;

	_ConnectionPtr m_pAppConn;
	_RecordsetPtr  m_recordset;


// Dialog Data
	//{{AFX_DATA(CCalibrationDlg)
	enum { IDD = IDD_CALIBRATION_DIALOG };
	CString	m_meterrange;
	//}}AFX_DATA
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCalibrationDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CCalibrationDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnOpenComm();
	afx_msg void OnSet();
	afx_msg void OnInstall();
	afx_msg void OnBaudAuto();
	afx_msg void CloseBaudAuto();
	afx_msg void OnSearchMeter();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnSetZero();
	afx_msg void OnAnalysis();
	afx_msg void OnClose();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnDestroy();
	afx_msg void OnSelchangeLanguage();
	afx_msg void OnCheck();
	afx_msg void OnSelchangeComboComm();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CALIBRATIONDLG_H__81E1239B_4B66_4E4F_ADF4_6558B2026620__INCLUDED_)
