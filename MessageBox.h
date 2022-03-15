#pragma once


// MessageBox dialog

class MessageBox : public CDialog
{
	DECLARE_DYNAMIC(MessageBox)

public:
	MessageBox(CWnd* pParent = NULL);   // standard constructor
	virtual ~MessageBox();
	CFont g_Font;
	CString	transType;
	CString	tranSpace;
	CString MountType;

	// Dialog Data
	//{{AFX_DATA(CMessageBox2Dlg)
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
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.
