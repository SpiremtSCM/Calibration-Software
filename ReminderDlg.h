#pragma once


// CReminderDlg dialog

class CReminderDlg : public CDialog
{
	DECLARE_DYNAMIC(CReminderDlg)

public:
	CReminderDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CReminderDlg();
	CFont g_Font;
	CString	transType;
	CString	tranSpace;
	CString mountType;

	CString str;                         //发送到表的消息	
	CString str1;                        //str1 = W前缀 + 表号
	_ConnectionPtr m_pAppConn; 
	_RecordsetPtr  m_recordset;
	CString strBeg;
	int line;
	int biaoleixing;
	int gyz;

// Dialog Data
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

protected:

	// Generated message map functions
	//{{AFX_MSG(CMessageBoxDlg)
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	void getM23(CString meter_no);
	void calculateSpacing();
	void getM24(CString meter_no);
	DECLARE_MESSAGE_MAP()
};
#pragma once


// ReminderDlg dialog

class ReminderDlg : public CDialog
{
	DECLARE_DYNAMIC(ReminderDlg)

public:
	ReminderDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~ReminderDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
