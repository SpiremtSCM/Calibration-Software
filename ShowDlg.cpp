// ShowDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Calibration.h"
#include "ShowDlg.h"
#include "CnComm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CShowDlg dialog


CShowDlg::CShowDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CShowDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CShowDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CShowDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CShowDlg)
	DDX_Control(pDX, IDC_LIST_SHOW, m_list);
	//}}AFX_DATA_MAP
	
}


BEGIN_MESSAGE_MAP(CShowDlg, CDialog)
	//{{AFX_MSG_MAP(CShowDlg)
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_MESSAGE(WM_MYMESSAGE, OnMyMessage)
	ON_WM_SIZE()
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CShowDlg message handlers

void CShowDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	CCalibrationApp *app = (CCalibrationApp *)AfxGetApp();
	CRect rc;
	rc.top = app->g_rc.top;
	rc.left = app->g_rc.right+2;
	rc.bottom = app->g_rc.bottom;
	rc.right = app->g_rc.right+415;
	MoveWindow(&rc);
	
	// Do not call CDialog::OnPaint() for painting messages
}
LRESULT   __stdcall   CBTHookProc(   long   nCode,WPARAM   wParam,LPARAM   lParam) ;
extern HHOOK   hHook; 

int __stdcall SetChildFont(struct HWND__ *,long);
//extern CFont *g_Font;
BOOL CShowDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	LOGFONT lf;                        // Used to create the CFont.
	memset(&lf, 0, sizeof(LOGFONT));   // Clear out structure.
	lf.lfHeight = 15;                  // Request a 20-pixel-high font
	strcpy(lf.lfFaceName, "Times New Roman");    
	if (g_font.m_hObject)
		g_font.DeleteObject();
	g_font.CreateFontIndirect(&lf);    // Create the font.

	// TODO: Add extra initialization here
	CCalibrationApp *app = (CCalibrationApp *)AfxGetApp();
	if (!app->g_com.IsOpen())
	{
		app->g_com.Open(app->commm,9600,NOPARITY,8,TWOSTOPBITS);
	}
	if (app->language == 0)
	{
		this->SetWindowText("显示");
		m_list.InsertColumn(0, "表号", LVCFMT_LEFT, 40);
		m_list.InsertColumn(1, "流量", LVCFMT_LEFT, 84);
		m_list.InsertColumn(2, "流速", LVCFMT_LEFT, 84);
		m_list.InsertColumn(3, "S", LVCFMT_LEFT, 103);
		m_list.InsertColumn(4, "Q", LVCFMT_LEFT, 25);
		m_list.InsertColumn(5, "R", LVCFMT_LEFT, 70);

		::EnumChildWindows(m_hWnd, ::SetChildFont, (LPARAM)&g_font);
	}
	else
	{
		this->SetWindowText("Show");
		m_list.InsertColumn(0, "IDN", LVCFMT_LEFT, 40);
		m_list.InsertColumn(1, "Flow", LVCFMT_LEFT, 84);
		m_list.InsertColumn(2, "Vel", LVCFMT_LEFT, 84);
		m_list.InsertColumn(3, "S_UP", LVCFMT_LEFT, 35);
		m_list.InsertColumn(4, "S_DN", LVCFMT_LEFT, 35);
		m_list.InsertColumn(5, "Q", LVCFMT_LEFT, 25);
//		m_list.InsertColumn(6, "R", LVCFMT_LEFT, 30);
//		m_list.InsertColumn(7, "Total", LVCFMT_LEFT, 35);

		::EnumChildWindows(m_hWnd, ::SetChildFont, (LPARAM)&g_font); 
	}	
	m_flag = 0;
	CRect rc;
	rc.top = app->g_rc.top;
	rc.left = app->g_rc.right+1;
	rc.bottom = app->g_rc.bottom;
	rc.right = app->g_rc.right+415;
	MoveWindow(&rc);
	SetTimer(3, 500, NULL);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CShowDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	CCalibrationApp *app = (CCalibrationApp *)AfxGetApp();
	if (nIDEvent == 3){
		m_list.DeleteAllItems();
		for (int i=0; i<app->no; i++)
		{
			m_list.InsertItem(i, app->liuliang[i].mmeter);
			CString cc,cd;
			if (app->liuliang[i].mflux == -1)
			{
				cc.Format("ERROR");
			}
			else
			{
				cc.Format("%.4f %s", app->liuliang[i].mflux, app->liuliang[i].unflux);
			}
			m_list.SetItemText(i, 1, cc);

			if (app->liuliang[i].mspeed == -1)
			{
				cd.Format("ERROR");
			}
			else
			{
				cd.Format("%.4f %s", app->liuliang[i].mspeed, app->liuliang[i].unspeed);
			}
			m_list.SetItemText(i, 2, cd);

			CString cS_UP(""), cS_DN(""), cQ(""), cR(""), cpos_Total("");
			cS_UP.Format(_T("%.1f"), app->liuliang[i].S_UPf);
			m_list.SetItemText(i, 3, cS_UP);

			cS_DN.Format(_T("%.1f"), app->liuliang[i].S_DNf);
			m_list.SetItemText(i, 4, cS_DN);

			cQ.Format(_T("%.0f"), app->liuliang[i].Qf);
			m_list.SetItemText(i, 5, cQ);

	//		cR.Format(_T("%.2f"), app->liuliang[i].Rf);
	//		m_list.SetItemText(i, 6, cR);

	//		cpos_Total.Format(_T("%.2f"), app->liuliang[i].posTotalf);
	//		m_list.SetItemText(i, 7, cpos_Total);
		}
	}
	CDialog::OnTimer(nIDEvent);
}

LRESULT CShowDlg::OnMyMessage(WPARAM wParam, LPARAM lParam)
{
	Invalidate();
	return 0;
}

void CShowDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	CWnd  *pList=GetDlgItem(IDC_LIST_SHOW); 
	if(pList) 
	{ 
		CRect  rect; 
		GetWindowRect(&rect);  //获取窗口rect，
		ScreenToClient(rect);  //从窗口尺寸转换到用户区rect
		pList->MoveWindow(0, 0, rect.right-rect.left, rect.bottom-rect.top, true); 
	} 
	// TODO: Add your message handler code here
}

void CShowDlg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	CCalibrationApp *app = (CCalibrationApp *)AfxGetApp();
	HWND hwnd;
	if (app->language == 0)
	{
		hwnd = ::FindWindow(NULL, "置零及调流速");
	}
	else
	{
		hwnd = ::FindWindow(NULL, "Zero Setting and Flow Rate Debugging");
	}
	::SetWindowText(::GetDlgItem(hwnd, IDC_BUTTON_SHOW), ">>");
	::SendMessage(hwnd, WM_MYMESSAGE2, 0, 0);

	CDialog::OnClose();
}

void CShowDlg::OnDestroy()
{
	CDialog::OnDestroy();
	::PostQuitMessage(0);
}
