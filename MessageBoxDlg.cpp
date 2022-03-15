// MessageBoxDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Calibration.h"
#include "MessageBoxDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMessageBoxDlg dialog


CMessageBoxDlg::CMessageBoxDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMessageBoxDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMessageBoxDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CMessageBoxDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMessageBoxDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMessageBoxDlg, CDialog)
	//{{AFX_MSG_MAP(CMessageBoxDlg)
	ON_BN_CLICKED(IDSTART, OnStart)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMessageBoxDlg message handlers


void CMessageBoxDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

void CMessageBoxDlg::OnStart() 
{
	// TODO: Add your control notification handler code here
	CDialog::OnOK();
}

int __stdcall SetChildFont(struct HWND__ *,long);
extern CFont *g_Font;

BOOL CMessageBoxDlg::OnInitDialog() 
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
		GetDlgItem(IDC_STATIC_MSG)->SetWindowText("请关闭阀门，等待水完全停止（2分钟）。准备好了，请按“开始”键。");
		GetDlgItem(IDSTART)->SetWindowText("开始");
		GetDlgItem(IDCANCEL)->SetWindowText("取消");
	}
	else
	{
		GetDlgItem(IDC_STATIC_MSG)->SetWindowText("Please close the valve, and wait for the water to completely stop (2 min). Ready, press the 'Start' button.");
		GetDlgItem(IDSTART)->SetWindowText("Start");
		GetDlgItem(IDCANCEL)->SetWindowText("Cancel");
		//g_Font = new CFont;       
		//g_Font->CreatePointFont(90, "Times New Roman");
		::EnumChildWindows(m_hWnd, ::SetChildFont, (LPARAM)&g_Font); 
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

