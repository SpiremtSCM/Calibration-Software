#if !defined(AFX_LINEARRAY_H__C8ED1878_19B6_421C_A885_54EC67C36DF8__INCLUDED_)
#define AFX_LINEARRAY_H__C8ED1878_19B6_421C_A885_54EC67C36DF8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LineArray.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLineArrayDlg dialog

class CLineArrayDlg : public CDialog
{
// Construction
public:
	CString str;
	CString str1;
	CLineArrayDlg(CWnd* pParent = NULL);   // standard constructor
	void OnSet01();
	void OnSet02();
	void OnSet03();
	void OnSet04();
	void OnSet05();
	void OnSet06();
	void OnSet07();
	void OnSet08();
	void OnSet09();
	void OnSet10();
	void OnSet11();
	void OnSet12();
// Dialog Data
	//{{AFX_DATA(CLineArrayDlg)
	enum { IDD = IDD_LINE_ARRAY };
	CString	m_011;
	CString	m_012;
	CString	m_021;
	CString	m_022;
	CString	m_032;
	CString	m_031;
	CString	m_041;
	CString	m_042;
	CString	m_051;
	CString	m_052;
	CString	m_061;
	CString	m_062;
	CString	m_071;
	CString	m_072;
	CString	m_081;
	CString	m_082;
	CString	m_091;
	CString	m_092;
	CString	m_101;
	CString	m_102;
	CString	m_111;
	CString	m_112;
	CString	m_121;
	CString	m_122;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLineArrayDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CLineArrayDlg)
	afx_msg void OnDataNum();
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonSet();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LINEARRAY_H__C8ED1878_19B6_421C_A885_54EC67C36DF8__INCLUDED_)
