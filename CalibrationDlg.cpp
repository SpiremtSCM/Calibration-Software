// CalibrationDlg.cpp : implementation file
//

#include "stdafx.h"
#include <windows.h>
#include <strsafe.h>
#include "Calibration.h"
#include "CalibrationDlg.h"
#include "CnComm.h"
#include "atlbase.h"
#include <math.h> 
#include "atlutil.h"

#pragma once
#include <afx.h>
#include <afxinet.h>
#include <afxwin.h>

#import "C:\Program Files\Common Files\System\ado\msado15.dll" \
no_namespace \
rename( "EOF", "adoEOF" )

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


#define CN_COMM_MFC_EXCEPTION



/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About
void FindCommPort( CComboBox *pComboBox )  
{  
	HKEY hKey;
	#ifdef _DEBUG  
		ASSERT( pComboBox != NULL );
		pComboBox->AssertValid();
		pComboBox->ResetContent(); 
	#endif
	#ifdef SNK_STH
		::AfxMessageBox( TEXT("I am in #ifdef SNK_STH!") );
		VERIFY(pComboBox != NULL);
		pComboBox->AssertValid();
		pComboBox->ResetContent();
	#endif


	if( ::RegOpenKeyEx( HKEY_LOCAL_MACHINE,TEXT("Hardware\\DeviceMap\\SerialComm"), NULL, KEY_READ, &hKey) == ERROR_SUCCESS)  
	{  
		int i=0;
		TCHAR portName[256],commName[256];
		DWORD dwLong,dwSize;
		while(1)
		{
			dwLong = dwSize = sizeof(portName)/sizeof(TCHAR);

			if( ::RegEnumValue( hKey, i, portName, &dwLong, NULL, NULL, (PUCHAR)commName, &dwSize ) == ERROR_NO_MORE_ITEMS )
				break;
			pComboBox->AddString( commName );// commName
			i++;
		}

		if( pComboBox->GetCount() == 0 )
		{
			::AfxMessageBox( TEXT("Cannot Find any available COM port!") );
		}

		RegCloseKey(hKey);
	}

} 

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCalibrationDlg dialog

CCalibrationDlg::CCalibrationDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCalibrationDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCalibrationDlg)
	m_meterrange = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCalibrationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCalibrationDlg)
	DDX_Text(pDX, IDC_METER_RANGE, m_meterrange);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CCalibrationDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_OPEN_COMM, OnOpenComm)
	ON_COMMAND(IDM_SET, OnSet)
	ON_COMMAND(IDM_INSTALL, OnInstall)
	ON_BN_CLICKED(IDC_BAUD_AUTO, OnBaudAuto)
	ON_BN_CLICKED(IDC_SEARCH_METER, OnSearchMeter)
	ON_WM_TIMER()
	ON_COMMAND(IDM_SET_ZERO, OnSetZero)
	ON_COMMAND(IDM_ANALYSIS, OnAnalysis)
	ON_WM_CLOSE()
	ON_WM_CTLCOLOR()
	ON_WM_DESTROY()
	ON_CBN_SELCHANGE(IDC_LANGUAGE, OnSelchangeLanguage)
	ON_BN_CLICKED(IDC_CHECK, OnCheck)
	ON_CBN_SELCHANGE(IDC_COMBO_COMM, OnSelchangeComboComm)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCalibrationDlg message handlers

HHOOK   hHook;  
LRESULT   __stdcall   CBTHookProc(   long   nCode,WPARAM   wParam,LPARAM   lParam)  
{  
	if   (nCode==HCBT_ACTIVATE)  
	{  
		SetDlgItemText((HWND)wParam,IDYES,"&Yes");  
		SetDlgItemText((HWND)wParam,IDNO   ,"&No");  
		SetDlgItemText((HWND)wParam,IDOK,"&OK");  
		SetDlgItemText((HWND)wParam,IDCANCEL,"&Cancel");  
		UnhookWindowsHookEx(hHook);  
	}  
	return   0;  
 }  

BOOL __stdcall SetChildFont(HWND hwnd, LPARAM lparam)
{   
	CFont *pFont = (CFont*)lparam;   
	CWnd *pWnd = CWnd::FromHandle(hwnd);   
	pWnd->SetFont(pFont);   
	return TRUE;
}
CFont *g_Font;


BOOL CCalibrationDlg::OnInitDialog()
{

	_CrtSetDbgFlag(_CrtSetDbgFlag(_CRTDBG_REPORT_FLAG) | _CRTDBG_LEAK_CHECK_DF);

	CDialog::OnInitDialog();

	LOGFONT lf;                        // Used to create the CFont.
	memset(&lf, 0, sizeof(LOGFONT));   // Clear out structure.
	lf.lfHeight = 15;                  // Request a 20-pixel-high font
	strcpy(lf.lfFaceName, "Times New Roman");    //    with face name "Arial".
	g_Font.CreateFontIndirect(&lf);    // Create the font.

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here

	CCalibrationApp *app = (CCalibrationApp *)AfxGetApp();
	app->language = 0;
	//显示菜单栏
	CMenu* menu = new CMenu;
	menu->LoadMenu(MAKEINTRESOURCE(IDR_MENU));    
	this->SetMenu(menu);
	//导入串口组合框的内容，并初始化

	CComboBox *combox;
	GetDlgItem(IDC_COMBO_COMM)->SetFont(&g_Font);
	GetDlgItem(IDC_COMBO_COMM)->SetFont(&g_Font);
	combox = (CComboBox *)GetDlgItem(IDC_COMBO_COMM);

	try
	{
		FindCommPort(combox);
	}
	catch (...)
	{
		AfxMessageBox("Com port call fail!");
	}


	combox->SetCurSel(1);
	//语言选择初始化
	((CComboBox *)GetDlgItem(IDC_LANGUAGE))->SetCurSel(1);
	OnSelchangeLanguage();
	//范围对话框初始化
	GetDlgItem(IDC_METER_RANGE)->SetFont(&g_Font);
	GetDlgItem(IDC_METER_RANGE)->SetWindowText("");
	((CEdit *)GetDlgItem(IDC_METER_RANGE))->SetSel(0,-1); 
	((CEdit *)GetDlgItem(IDC_METER_RANGE))->SetFocus(); 
	GetDlgItem(IDC_LOADING)->ShowWindow(FALSE);

	UpdateData(FALSE);
	GetDlgItem(IDC_WAIT234)->ShowWindow(FALSE);

	try
	{
		//m_pAppConn.CreateInstance(__uuidof(Connection));
		//m_pAppConn->Open("File Name=MyData.udl", "", "", adConnectUnspecified);
		HRESULT hr = m_pAppConn.CreateInstance(__uuidof(Connection));
		if (FAILED(hr))
			AfxMessageBox("Can't create an intance of ADO.Connection");

		if (FAILED(m_pAppConn->Open(_bstr_t("File Name=MyData.udl"), _bstr_t( "" ), _bstr_t( "" ), adModeUnknown)))
			::AfxMessageBox(TEXT("Can't open datasource"));
		//m_pAppConn->Close();
	}
	catch (_com_error &e)
	{
		::AfxMessageBox(TEXT("Connection with database fail! Please close application and check MyData.udl file"));
		_bstr_t bstrSource(e.Source());
		_bstr_t bstrDescription(e.Description());
		TRACE("Exception thrown for classes generated by #import");
		TRACE("\tCode = %08lx\n", e.Error());
		TRACE("\tCode meaning = %s\n", e.ErrorMessage());
		TRACE("\tSource = %s\n", (LPCTSTR)bstrSource);
		TRACE("\tDescription = %s\n", (LPCTSTR)bstrDescription);

	}
	catch (...)
	{
		TRACE("*** Unhandled Exception ***");
	}
	CString path;
	CString sql;
	sql.Format("SELECT CONVERT(CHAR(100),filename) AS f_name FROM master.dbo.sysdatabases WHERE filename LIKE \'%cMASTER.MDF%c\'", '%', '%');
	try
	{
		m_recordset = m_pAppConn->Execute((_bstr_t)sql, NULL, adCmdText);
		_variant_t var = m_recordset->GetCollect("f_name");
		path = (char *)_bstr_t(var);
	}
	catch (_com_error e)
	{
		AfxMessageBox(e.ErrorMessage());
	}
	CString path2 = path;
	path2.MakeUpper();
	int index = path2.Find("DATA");
	index += 4;
	path = path.Left(index);
	path.Replace(_T("\\"),_T("\\\\"));
	sql.Format("use master");
	try
	{
		m_pAppConn->Execute((_bstr_t)sql, NULL, adCmdText);
	}
	catch (_com_error e)
	{
		AfxMessageBox(e.ErrorMessage());
	}
	sql.Format("IF NOT EXISTS(SELECT * FROM dbo.sysdatabases WHERE name = \'settings\')CREATE DATABASE settings ON(name=settings,filename=\'%s/settings_data.mdf\')LOG ON(name=settings_log,filename=\'%s/settings_log.ldf\')", path, path);
	try
	{

		m_pAppConn->Execute((_bstr_t)sql, NULL, adCmdText);

	}
	catch (_com_error e)
	{
		AfxMessageBox(e.ErrorMessage());
	}
	_bstr_t SQL("use settings");
	try
	{

		m_pAppConn->Execute(SQL, NULL, adCmdText);

	}
	catch (_com_error e)
	{
		AfxMessageBox(e.ErrorMessage());
	}
	_bstr_t strSQL1("IF NOT EXISTS(SELECT name FROM sysobjects WHERE xtype=\'U\' AND name=\'Common_settings\') BEGIN CREATE TABLE settings.dbo.Common_settings(pipe_outer_diameter float not null,pipe_wall_thickness float,pipe_inner_diameter float,pipe_material int,liner_material int,liner_thickness float,fluid_type int,measurement_units int,flow_rate_unit varchar(50),totalizer_units int,totalizer_multiplier int,net_toalizer bit,pos_totalizer bit,neg_totalizer bit,Language_LINGUA int,damping_factor float,relay_output_setup int) INSERT INTO Common_settings VALUES(0,0,0,0,0,0,0,0,\'0/0\',0,0,0,0,0,0,0,0) END");
	try
	{

		m_pAppConn->Execute(strSQL1, NULL, adCmdText);

	}
	catch (_com_error e)
	{
		AfxMessageBox(e.ErrorMessage());
	}
	_bstr_t strSQL2("IF NOT EXISTS(SELECT name FROM sysobjects WHERE xtype=\'U\' AND name=\'Independent_settings\') CREATE TABLE Independent_settings(netword_IDN int not null primary key,s_n varchar(8),table_type int,transducer_type int,transducer_frequency int,transducer_mounting int,scale_factor float,state int)");
	try
	{

		m_pAppConn->Execute(strSQL2, NULL, adCmdText);

	}
	catch (_com_error e)
	{
		AfxMessageBox(e.ErrorMessage());
	}
	_bstr_t strSQL3("IF NOT EXISTS(SELECT name FROM sysobjects WHERE xtype=\'U\' AND name=\'Probe\')BEGIN CREATE TABLE Probe(wedge_degree float,wedge_sound_velocity float,wedge_distance float,wedge_time_delay float) INSERT INTO Probe VALUES(0,0,0,0) END");
	try
	{

		m_pAppConn->Execute(strSQL3, NULL, adCmdText);

	}
	catch (_com_error e)
	{
		AfxMessageBox(e.ErrorMessage());
	}
	_bstr_t strSQL4("IF NOT EXISTS(SELECT name FROM sysobjects WHERE xtype='U' AND name='Logo')BEGIN CREATE TABLE Logo(l1 int,l2 float,l3 float,l4 float,l5 float,l6 int,l7 int,l8 float) INSERT INTO Logo VALUES(0,0,0,0,0,0,0,0) END");
	try
	{

		m_pAppConn->Execute(strSQL4, NULL, adCmdText);

	}
	catch (_com_error e)
	{
		AfxMessageBox(e.ErrorMessage());
	}
	//m_pAppConn->Close();

	delete menu;
	menu = NULL;

	return FALSE;  // return TRUE  unless you set the focus to a control
}


void CCalibrationDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CCalibrationDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CCalibrationDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CCalibrationDlg::OnOpenComm() 
{	
	CCalibrationApp *app = (CCalibrationApp *)AfxGetApp();
	int iPos = ((CComboBox *)GetDlgItem(IDC_COMBO_COMM))->GetCurSel();
	CString chose; 
	((CComboBox *)GetDlgItem(IDC_COMBO_COMM))->GetLBText(iPos, chose);
	
	sscanf(chose, "COM%d", &app->commm);
	if(app->g_com.IsOpen())
    {
		app->g_com.Close();
		if (app->language == 0)
		{
			GetDlgItem(IDC_OPEN_COMM)->SetWindowText("打开串口");
		}
		else
		{
			//hHook=SetWindowsHookEx(WH_CBT,(HOOKPROC)CBTHookProc,AfxGetInstanceHandle(),NULL); 
			GetDlgItem(IDC_OPEN_COMM)->SetWindowText("Open Serial Port");
		}
    } 
	else
	{	
		if(!app->g_com.Open(app->commm,9600,NOPARITY,8,TWOSTOPBITS))//打开串口
		{	
			if (app->language == 0)
			{
				AfxMessageBox("串口被占用，请使用其他串口!");
			}
			else
			{
				hHook=SetWindowsHookEx(WH_CBT,(HOOKPROC)CBTHookProc,AfxGetInstanceHandle(),NULL); 
				AfxMessageBox("Serial occupied, please use the other serial port!");
			}		
		}
		else
		{
			if (app->language == 0)
			{
				GetDlgItem(IDC_OPEN_COMM)->SetWindowText("关闭串口");
			}
			else
			{ 
				GetDlgItem(IDC_OPEN_COMM)->SetWindowText("Close Serial Port");
			}
		}
	}
	OnBaudAuto(); //set Baud rate to Calibration mode 9600;none;8;2
}                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               

void CCalibrationDlg::OnSet() 
{
	// TODO: Add your command handler code here
	CCalibrationApp *app = (CCalibrationApp *)AfxGetApp();
	if (app->g_com.IsOpen())
	{
		setdlg.DoModal();
	}
	else
	{
		if (app->language == 0)
		{
			AfxMessageBox("请打开串口并完成波特率设置和表搜索!");
		}
		else
		{
			hHook=SetWindowsHookEx(WH_CBT,(HOOKPROC)CBTHookProc,AfxGetInstanceHandle(),NULL); 
			AfxMessageBox("Please open the serial port , complete the baud rate setting and search meter!");
		}		
	}
}

void CCalibrationDlg::OnInstall() 
{
	// TODO: Add your command handler code here
	CCalibrationApp *app = (CCalibrationApp *)AfxGetApp();
	if (app->g_com.IsOpen())
	{
		reminderDlg.DoModal();
		installdlg.DoModal();
	}
	else
	{
		if (app->language == 0)
		{
			AfxMessageBox("请打开串口!");
		}
		else
		{
			hHook=SetWindowsHookEx(WH_CBT,(HOOKPROC)CBTHookProc,AfxGetInstanceHandle(),NULL); 
			AfxMessageBox("Please open the serial port!");
		}	
	}
	
}
void DelayNS(int t);

void CCalibrationDlg::OnBaudAuto() 
{
	// TODO: Add your control notification handler code here

	CCalibrationApp *app = (CCalibrationApp *)AfxGetApp();

	if (app->g_com.IsOpen())
	{
		int iPos = ((CComboBox *)GetDlgItem(IDC_COMBO_COMM))->GetCurSel();
		CString chose;
		((CComboBox *)GetDlgItem(IDC_COMBO_COMM))->GetLBText(iPos, chose);
		int commm;
		sscanf(chose, "COM%d", &commm);

		GetDlgItem(IDC_BAUD_AUTO)->EnableWindow(FALSE);

		UpdateData(FALSE);
		int baud[8] = { 300, 600, 1200, 2400, 4800, 9600, 14400, 19200 };
		app->g_com.Close(commm);
		for (int i = 0; i < 8; i++)
		{
			if (app->language == 0)
			{
				GetDlgItem(IDC_WAIT234)->SetWindowText("请等待。。。");
			}
			else
			{
				GetDlgItem(IDC_WAIT234)->SetFont(&g_Font);
				GetDlgItem(IDC_WAIT234)->SetWindowText("Please wait...");
			}
			GetDlgItem(IDC_WAIT234)->ShowWindow(TRUE);
			int temp = baud[i];
			if (app->g_com.Open(commm, temp, NOPARITY, 8, TWOSTOPBITS))
			{
				//str += "\x4d\x3c\x0d\x4d\x36\x0d\x4d\x32\x0d";

				app->g_com.Write("\x4d\x3c\x0d\x4d\x36\x0d\x4d\x32\x0d");
				Sleep(100);
				app->g_com.Write("\x4d\x3c\x0d\x4d\x36\x0d\x4d\x32\x0d");
				str = "";
				Sleep(100);
				str += "\x4d\x3d\x0d";

				app->g_com.Write(str);
				str = "";
				Sleep(100);
				str += "\x4d\x32\x0d";

				app->g_com.Write(str);
				str = "";
				Sleep(100);
				str += "\x4d\x3d\x0d";

				app->g_com.Write(str);
				str = "";
				Sleep(100);
				str += "\x4d\x30\x0d";

				app->g_com.Write(str);
				str = "";
				Sleep(100);
				str += "\x4d\x3d\x0d";

				app->g_com.Write(str);
				str = "";
				Sleep(100);
				str += "\x4d\x30\x0d";

				app->g_com.Write(str);
				str = "";
				Sleep(100);
				str += "\x4d\x3d\x0d";

				app->g_com.Write(str);
				str = "";
				Sleep(100);
				str += "\x4d\x31\x0d";

				app->g_com.Write(str);
				str = "";
				Sleep(100);
				str += "\x4d\x3d\x0d";

				app->g_com.Write(str);
				str = "";
				Sleep(100);
			}
			app->g_com.Close(commm);
		}
		app->g_com.Open(commm, 9600, NOPARITY, 8, TWOSTOPBITS);
		GetDlgItem(IDC_BAUD_AUTO)->EnableWindow(TRUE);
		GetDlgItem(IDC_WAIT234)->ShowWindow(FALSE);
	}
	else
	{
		if (app->language == 0)
		{
			AfxMessageBox("请打开串口并完成波特率设置和表搜索!");
		}
		else
		{
			hHook = SetWindowsHookEx(WH_CBT, (HOOKPROC)CBTHookProc, AfxGetInstanceHandle(), NULL);
			AfxMessageBox("Please open the serial port , complete the baud rate setting and search meter!");
		}
	}
}

void CCalibrationDlg::OnSearchMeter() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	CCalibrationApp *app = (CCalibrationApp *)AfxGetApp();
	if (app->g_com.IsOpen())
	{
		SYSTEMTIME st;
		CString strtime;
		GetLocalTime(&st);
		strtime.Format("%04d%02d%02d", st.wYear, st.wMonth, st.wDay);

		CString sql;
		sql.Format("delete from Independent_settings");
		try
		{
			m_pAppConn->Execute((_bstr_t)sql, NULL, adCmdText);
		}
		catch (_com_error e)
		{
			AfxMessageBox(e.ErrorMessage());
		}
		int num = 0;
		int len = m_meterrange.GetLength();
		int range = 0;
		int i, j;
		for (i = 0; i < len; i++)
		{
			range += (int)((m_meterrange.GetAt(i) - '0') * pow(10.0, (len - i - 1)));
		}
		char str2[3] = { 0 };

		for (i = 1; i <= range; i++)
		{
			char buf[20] = { 0 };
			//str = CString(0x57);
			str = "\x57";

			sprintf(str2, "%d", i);
			len = strlen(str2);
			int s = i;
			for (j = 1; j <= len; j++)
			{
				int x = (int)( i / pow(10.0, len - j));
				switch (x)
				{
				case 0:
					str += "\x30";
					break;
				case 1:
					str += "\x31";
					break;
				case 2:
					str += "\x32";
					break;
				case 3:
					str += "\x33";
					break;
				case 4:
					str += "\x34";
					break;
				case 5:
					str += "\x35";
					break;
				case 6:
					str += "\x36";
					break;
				case 7:
					str += "\x37";
					break;
				case 8:
					str += "\x38";
					break;
				case 9:
					str += "\x39";
					break;
				default:
					if (app->language == 0)
					{
						AfxMessageBox("请输入一个整数!");
					}
					else
					{
						hHook = SetWindowsHookEx(WH_CBT, (HOOKPROC)CBTHookProc, AfxGetInstanceHandle(), NULL);
						AfxMessageBox("Please enter an integer!");
					}
					break;
				}
				i %= (int)pow(10.0, len - j);
			}
			//str += CString(0x45) + CString(0x53) + CString(0x4e) + CString(0x0d);
			str += "\x45\x53\x4e\x0d";//ESN\r

			app->g_com.Write(str);
			str = "";
			Sleep(100);
			int len = 0;
			len = app->g_com.Read(buf, 11);
			Sleep(100);
			if (len > 0)
			{
				if (len == 11)
				{
					buf[8] = '\0';
					if (buf[0] == '1' && buf[1] == '8')
					{
						app->biaoleixing = 0;
					}
					else
					{
						app->biaoleixing = 1;
					}
					CString sql;
					sql.Format("INSERT INTO Independent_settings(netword_IDN,s_n,table_type,transducer_type,transducer_frequency,transducer_mounting,scale_factor,state) VALUES(%d,\'%s\',%d,0,0,0,0,0)", s, buf, app->biaoleixing);
					try
					{
						m_pAppConn->Execute((_bstr_t)sql, NULL, adCmdText);
					}
					catch (_com_error e)
					{
						AfxMessageBox(e.ErrorMessage());
					}
					num++;
				}
				else
				{
					if (app->language == 0)
					{
						AfxMessageBox("请设置独立的表号!");
					}
					else
					{
						hHook = SetWindowsHookEx(WH_CBT, (HOOKPROC)CBTHookProc, AfxGetInstanceHandle(), NULL);
						AfxMessageBox("Please set up independent netword_IDN!");
					}
				}
			}
			i = s;
			CString show;
			if (app->language == 0)
			{
				show.Format("搜索中。。。%.2f%c", (float)i / range * 100, '%');
			}
			else
			{
				show.Format("Searching...%.2f%c", (float)i / range * 100, '%');
			}
			GetDlgItem(IDC_LOADING)->SetFont(&g_Font);
			GetDlgItem(IDC_LOADING)->SetWindowText(show);
			GetDlgItem(IDC_LOADING)->ShowWindow(TRUE);
			UpdateData(FALSE);
		}
		//char *meter_num = new char;
		//sprintf(meter_num, "%d", num);
		CString meter_num;
		meter_num.Format("%d", num);
		GetDlgItem(IDC_METER_NUM)->SetFont(&g_Font);
		GetDlgItem(IDC_METER_NUM)->SetWindowText(meter_num);

		Sleep(500);
		CString show;
		if (app->language == 0)
		{
			show.Format("搜索完成");
		}
		else
		{
			show.Format("Search complete");
		}
		GetDlgItem(IDC_LOADING)->SetWindowText(show);
	}
	else
	{
		if (app->language == 0)
		{
			AfxMessageBox("请打开串口并完成波特率设置和表搜索!");
		}
		else
		{
			hHook = SetWindowsHookEx(WH_CBT, (HOOKPROC)CBTHookProc, AfxGetInstanceHandle(), NULL);
			AfxMessageBox("Please open the serial port , complete the baud rate setting and search meter!");
		}
	}

}

void CCalibrationDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnTimer(nIDEvent);
}

void CCalibrationDlg::OnSetZero() 
{
	// TODO: Add your command handler code here
	CCalibrationApp *app = (CCalibrationApp *)AfxGetApp();
	if (app->g_com.IsOpen())
	{
		setzerodlg.DoModal();
	}
	else
	{
		if (app->language == 0)
		{
			AfxMessageBox("请打开串口!");
		}
		else
		{
			hHook=SetWindowsHookEx(WH_CBT,(HOOKPROC)CBTHookProc,AfxGetInstanceHandle(),NULL); 
			AfxMessageBox("Please open the serial port!");
		}	
	}
}

void CCalibrationDlg::OnAnalysis() 
{
	// TODO: Add your command handler code here
	CCalibrationApp *app = (CCalibrationApp *)AfxGetApp();
	if (app->g_com.IsOpen())
	{
		analysisdlg.DoModal();
	}
	else
	{
		if (app->language == 0)
		{
			AfxMessageBox("请打开串口!");
		}
		else
		{
			hHook=SetWindowsHookEx(WH_CBT,(HOOKPROC)CBTHookProc,AfxGetInstanceHandle(),NULL); 
			AfxMessageBox("Please open the serial port!");
		}	
	}
}

void CCalibrationDlg::OnClose() 
{
	if (m_recordset)
		if (m_recordset->State == adStateOpen)
			m_recordset->Close();
	if (m_pAppConn)
		if (m_pAppConn->State == adStateOpen)
			m_pAppConn->Close();

	//set Baud rate to Normal mode 9600;None;8;1
	CloseBaudAuto();

	CCalibrationApp *app = (CCalibrationApp *)AfxGetApp();
	if (app->g_com.IsOpen())
		app->g_com.Close();

	CDialog::OnClose();
	exit(0);
}

void CCalibrationDlg::CloseBaudAuto()
{
	// TODO: Add your control notification handler code here

	CCalibrationApp *app = (CCalibrationApp *)AfxGetApp();

	if (app->g_com.IsOpen())
	{
		int iPos = ((CComboBox *)GetDlgItem(IDC_COMBO_COMM))->GetCurSel();
		CString chose;
		((CComboBox *)GetDlgItem(IDC_COMBO_COMM))->GetLBText(iPos, chose);
		int commm;
		sscanf(chose, "COM%d", &commm);

		GetDlgItem(IDC_WAIT234)->ShowWindow(TRUE);
		GetDlgItem(IDC_BAUD_AUTO)->EnableWindow(FALSE);

		UpdateData(FALSE);
		app->g_com.Close(commm);

		if (app->language == 0)
		{
			GetDlgItem(IDC_WAIT234)->SetWindowText("请等待。。。");
		}
		else
		{
			GetDlgItem(IDC_WAIT234)->SetFont(&g_Font);
			GetDlgItem(IDC_WAIT234)->SetWindowText("Please wait...");
		}
		GetDlgItem(IDC_WAIT234)->ShowWindow(TRUE);

		if (app->g_com.Open(commm, 9600, NOPARITY, 8, TWOSTOPBITS))
		{
			app->g_com.Write("\x4d\x3c\x0d\x4d\x36\x0d\x4d\x32\x0d");
			Sleep(100);
			app->g_com.Write("\x4d\x3c\x0d\x4d\x36\x0d\x4d\x32\x0d");
			str = "";
			Sleep(100);
			str += "\x4d\x3d\x0d";
			app->g_com.Write(str);

			str = "";
			Sleep(100);
			str += "\x4d\x32\x0d";
			app->g_com.Write(str);

			str = "";
			Sleep(100);
			str += "\x4d\x3d\x0d";
			app->g_com.Write(str);

			str = "";
			Sleep(100);
			str += "\x4d\x30\x0d";
			app->g_com.Write(str);

			str = "";
			Sleep(100);
			str += "\x4d\x3d\x0d";
			app->g_com.Write(str);

			str = "";
			Sleep(100);
			str += "\x4d\x30\x0d";
			app->g_com.Write(str);

			str = "";
			Sleep(100);
			str += "\x4d\x3d\x0d";
			app->g_com.Write(str);

			str = "";
			Sleep(100);
			str += "\x4d\x31\x0d";
			app->g_com.Write(str);

			//scrol down to 1

			str = "";
			Sleep(100);
			str += "\x4d\x3f\x0d";
			app->g_com.Write(str);
				
			str = "";
			Sleep(100);
			str += "\x4d\x3d\x0d";
			app->g_com.Write(str);

			str = "";
			Sleep(100);
		}
		app->g_com.Close(commm);
	
	}

}

HBRUSH CCalibrationDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here
	if( pWnd->GetDlgCtrlID() == IDC_LOADING )
	{
		pDC->SetTextColor(RGB(255,0,0)); //字体颜色
    }
	if( pWnd->GetDlgCtrlID() == IDC_WAIT234 )
	{
		pDC->SetTextColor(RGB(255,0,0)); //字体颜色
    }
	// TODO: Return a different brush if the default is not desired
	return hbr;
}

void CCalibrationDlg::OnDestroy() 
{
	
	m_pAppConn->Close();
	m_pAppConn = NULL;
	this->DestroyWindow();
	::PostQuitMessage(0);
	CDialog::OnDestroy();

}

void CCalibrationDlg::OnSelchangeLanguage() 
{
	// TODO: Add your control notification handler code here
	CMenu *pmenu = AfxGetApp()->GetMainWnd()->GetMenu();
	CWnd* pMain = AfxGetMainWnd();
	CCalibrationApp *app = (CCalibrationApp *)AfxGetApp();

	int iPos = ((CComboBox *)GetDlgItem(IDC_LANGUAGE))->GetCurSel();
	if (iPos == 0)
	{		
		app->language = 0;	
		if(app->g_com.IsOpen())
		{
			GetDlgItem(IDC_OPEN_COMM)->SetWindowText("关闭串口");
		}
		else
		{
			GetDlgItem(IDC_OPEN_COMM)->SetWindowText("打开串口");
		}
		GetDlgItem(IDC_BAUD_AUTO)->SetWindowText("自动设置波特率");
		GetDlgItem(IDC_SEARCH_METER)->SetWindowText("搜索表");
		GetDlgItem(IDC_STATIC_METERNO)->SetWindowText("表的数量");
		GetDlgItem(IDC_STATIC_LANGUAGE)->SetWindowText("Language");
		GetDlgItem(IDC_CHECK)->SetWindowText("检查标准表是否连接");

		CMenu* menu = new CMenu;
		BOOL success = menu->LoadMenu(MAKEINTRESOURCE(IDR_MENU));
		if (success == TRUE)
			this->SetMenu(menu);

		DrawMenuBar();
		::EnumChildWindows(m_hWnd, ::SetChildFont, (LPARAM)&g_Font); 

	}
	else
	{
		app->language = 1;
		if(app->g_com.IsOpen())
		{
			GetDlgItem(IDC_OPEN_COMM)->SetFont(&g_Font);
			GetDlgItem(IDC_OPEN_COMM)->SetWindowText("Close Serial Port");
		}
		else
		{
			GetDlgItem(IDC_OPEN_COMM)->SetFont(&g_Font);
			GetDlgItem(IDC_OPEN_COMM)->SetWindowText("Open Serial Port");
		}
		GetDlgItem(IDC_BAUD_AUTO)->SetFont(&g_Font);
		GetDlgItem(IDC_BAUD_AUTO)->SetWindowText("Set up Baud Rate Automatically");

		GetDlgItem(IDC_SEARCH_METER)->SetFont(&g_Font);
		GetDlgItem(IDC_SEARCH_METER)->SetWindowText("Search");

		GetDlgItem(IDC_STATIC_METERNO)->SetFont(&g_Font);
		GetDlgItem(IDC_STATIC_METERNO)->SetWindowText("Quantity");

		GetDlgItem(IDC_STATIC_LANGUAGE)->SetFont(&g_Font);
		GetDlgItem(IDC_STATIC_LANGUAGE)->SetWindowText("语言");

		GetDlgItem(IDC_CHECK)->SetFont(&g_Font);
		GetDlgItem(IDC_CHECK)->SetWindowText("Check the reference meter");

		CMenu* menu = new CMenu;
		// Create a new menu for the application window.
		BOOL success = menu->CreateMenu();
		if (success == TRUE)
		{
			menu->AppendMenuA(MF_POPUP, (UINT_PTR)IDM_SET, _T("&Setup"));
			menu->AppendMenuA(MF_POPUP, (UINT_PTR)IDM_INSTALL, _T("&Install"));
			menu->AppendMenuA(MF_POPUP, (UINT_PTR)IDM_SET_ZERO, _T("&Zero Setting and Flow Rate Debugging"));
			menu->AppendMenuA(MF_POPUP, (UINT_PTR)IDM_ANALYSIS, _T("&Analysis"));
			// Remove and destroy old menu
			SetMenu(NULL);
			pmenu->DestroyMenu();

			// Add new menu.
			SetMenu(menu);
		}

		DrawMenuBar();
		
		delete menu;
		menu = NULL;
	}
}

void CCalibrationDlg::OnCheck() 
{
	// TODO: Add your control notification handler code here
	CCalibrationApp *app = (CCalibrationApp *)AfxGetApp();

	if (app->g_com.IsOpen())
	{
		char cmd[8] = { '\x63', '\x04', '\x10', '\x10', '\x00', '\x02', '\x7c', '\x8c' };//YC Note: read register of flow rate from ref meter
		str = "";
		for (int i(0); i < 8; i++)
		{
			str += cmd[i];
		}
		app->g_com.Write(str, 8);
		char buf[60] = { 0 };
		int recvno = app->g_com.Read(buf, 10);
		Sleep(100);
		if (recvno == 0)
		{
			if (app->language == 0)
			{
				AfxMessageBox("请连接参考表!");
			}
			else
			{
				hHook = SetWindowsHookEx(WH_CBT, (HOOKPROC)CBTHookProc, AfxGetInstanceHandle(), NULL);
				AfxMessageBox("Please connect the reference meter!");
			}
		}
		else
		{
			if (app->language == 0)
			{
				AfxMessageBox("已连接参考表!");
			}
			else
			{
				hHook = SetWindowsHookEx(WH_CBT, (HOOKPROC)CBTHookProc, AfxGetInstanceHandle(), NULL);
				AfxMessageBox("Have been connected to the reference meter!");
			}
		}
	}
	else
	{
		hHook = SetWindowsHookEx(WH_CBT, (HOOKPROC)CBTHookProc, AfxGetInstanceHandle(), NULL);
		AfxMessageBox("Please open the serial port!");
	}
}

void CCalibrationDlg::OnSelchangeComboComm() 
{
	// TODO: Add your control notification handler code here
	CCalibrationApp *app = (CCalibrationApp *)AfxGetApp();
	int iPos = ((CComboBox *)GetDlgItem(IDC_COMBO_COMM))->GetCurSel();
	CString chose; 
	((CComboBox *)GetDlgItem(IDC_COMBO_COMM))->GetLBText(iPos, chose);
	sscanf(chose, "COM%d", &app->commm);

	if (app->g_com.IsOpen())
	{
		app->g_com.Close();
		app->g_com.Open(app->commm,9600,NOPARITY,8,TWOSTOPBITS);
	}
}

