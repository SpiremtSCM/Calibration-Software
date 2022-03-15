// MessageBox2Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "Calibration.h"
#include "MessageBox2Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMessageBox2Dlg dialog


CMessageBox2Dlg::CMessageBox2Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMessageBox2Dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMessageBox2Dlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CMessageBox2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMessageBox2Dlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMessageBox2Dlg, CDialog)
	//{{AFX_MSG_MAP(CMessageBox2Dlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMessageBox2Dlg message handlers

void CMessageBox2Dlg::OnOK() 
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}

void CMessageBox2Dlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

int __stdcall SetChildFont(struct HWND__ *,long);
extern CFont *g_Font;

BOOL CMessageBox2Dlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CCalibrationApp *app = (CCalibrationApp *)AfxGetApp();

	LOGFONT lf;                        // Used to create the CFont.
	memset(&lf, 0, sizeof(LOGFONT));   // Clear out structure.
	lf.lfHeight = 15;                  // Request a 20-pixel-high font
	strcpy(lf.lfFaceName, "Times New Roman");
	if (g_Font.m_hObject)
		g_Font.DeleteObject();
	g_Font.CreateFontIndirect(&lf);    // Create the font.

	if (app->language == 0)
	{
		if (app->flux.Compare("大") == 0)
		{
			GetDlgItem(IDC_STATIC_MSG)->SetWindowText("请把标准表流量调到Qmax，并等待一分钟");
		}
		else if (app->flux.Compare("中") == 0)
		{
			GetDlgItem(IDC_STATIC_MSG)->SetWindowText("请把标准表流量调到Qmid，并等待一分钟");
		}
		else if (app->flux.Compare("小") == 0)
		{
			GetDlgItem(IDC_STATIC_MSG)->SetWindowText("请把标准表流量调到Qmin，并等待一分钟");
		}
		GetDlgItem(IDOK)->SetWindowText("开始");
		GetDlgItem(IDCANCEL)->SetWindowText("取消");
	}
	else
	{
		if (app->flux.Compare("大") == 0)
		{
			GetDlgItem(IDC_STATIC_MSG)->SetWindowText("Please put the reference meter of flow rate transferred to Qmax, wait for one minute!");
		}
		else if (app->flux.Compare("中") == 0)
		{
			GetDlgItem(IDC_STATIC_MSG)->SetWindowText("Please put the reference meter of flow rate transferred to Qmid, wait for one minute!");
		}
		else if (app->flux.Compare("小") == 0)
		{
			GetDlgItem(IDC_STATIC_MSG)->SetWindowText("Please put the reference meter of flow rate transferred to Qmin, wait for one minute!");
		}
		GetDlgItem(IDOK)->SetWindowText("Start");
		GetDlgItem(IDCANCEL)->SetWindowText("Cancel");
		::EnumChildWindows(m_hWnd, ::SetChildFont, (LPARAM)&g_Font); 
	}	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
