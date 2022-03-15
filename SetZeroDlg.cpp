// SetZeroDlg.cpp : implementation file
//

#include "stdafx.h"
#include <iostream>
#include <afxwin.h>
#include <stdio.h>
#include "Calibration.h"
#include "CalibrationDlg.h"
#include "SetZeroDlg.h"
#include "MessageBoxDlg.h"
#include "MessageBox2Dlg.h"
#include "Meter_Operation.h"
#include "VC_Update.h"
#include <cstdio> 

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace std;

/////////////////////////////////////////////////////////////////////////////
// CSetZeroDlg dialog

CSetZeroDlg::CSetZeroDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSetZeroDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSetZeroDlg)
	m_m41 = _T("");
	m_show = _T("");
	//m_delay = _T("");
	//}}AFX_DATA_INIT
}

CSetZeroDlg::~CSetZeroDlg()
{
	// Deallocate the memory that was previously reserved
	if (showdlg)
		delete[] showdlg;
}

void CSetZeroDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSetZeroDlg)
	CCalibrationApp *app = (CCalibrationApp *)AfxGetApp();
	m_m41 = "0.0984252";
	DDX_Text(pDX, IDC_EDIT_M41, m_m41);//the input cut_flow rate text
	DDX_Text(pDX, IDC_EDIT_WAIT_TIME, m_wait_time);
	DDX_Text(pDX, IDC_EDIT_SAMPLE_TIME, m_sample_time);
	DDX_Text(pDX, IDC_EDIT_SHOW, m_show);
	DDX_Text(pDX, IDC_EDIT_VC_MAX, v_max);
	DDX_Text(pDX, IDC_EDIT_VC_MID, v_mid);
	DDX_Text(pDX, IDC_EDIT_VC_LOW, v_low);
	m_delay = atoi(m_wait_time);
	app->Global_Sampling_Total = atoi(m_sample_time) / 3;
	//DDX_Text(pDX, IDC_EDIT_DELAY, m_delay); 
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSetZeroDlg, CDialog)
	//{{AFX_MSG_MAP(CSetZeroDlg)
	ON_BN_CLICKED(IDC_M42, OnM42)//Set zero
	ON_BN_CLICKED(IDC_M41, OnM41)//Set low flow cutoff
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_M_2, OnM_2)//Store zero point value 
	ON_BN_CLICKED(IDC_COLLECT, OnCollect)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_COLLECT2, OnCollect2)
	ON_BN_CLICKED(IDC_COLLECT3, OnCollect3)
	ON_WM_CLOSE()
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON_SHOW, OnButtonShow)
	ON_WM_MOVE()
	ON_MESSAGE(WM_MYMESSAGE2, OnMyMessage2)
	ON_BN_CLICKED(IDC_BUTTON3, OnMax)
	ON_BN_CLICKED(IDC_BUTTON4, OnMid)
	ON_BN_CLICKED(IDC_BUTTON5, OnMin)
	ON_BN_CLICKED(IDC_BUTTON6, OnCalibrate)
	ON_BN_CLICKED(IDC_BUTTON7, OnCloseValve)
	ON_EN_CHANGE(IDC_EDIT_WAIT_TIME, OnChangeEditWaitTime)
	ON_EN_CHANGE(IDC_EDIT_SAMPLE_TIME, OnChangeEditSampleTime)
	ON_EN_CHANGE(IDC_EDIT_VC_MAX,OnChangeVCMax)
	ON_EN_CHANGE(IDC_EDIT_VC_MID,OnChangeVCMid)
	ON_EN_CHANGE(IDC_EDIT_VC_LOW,OnChangeVCLow)
	//}}AFX_MSG_MAP
	//ON_BN_CLICKED(IDC_FLUSH, OnBnClickedFlush)
	ON_BN_CLICKED(IDC_FLUSH, OnCalibrate_2)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSetZeroDlg message handlers
int __stdcall SetChildFont(struct HWND__ *,long);
//extern CFont *g_Font;

LRESULT   __stdcall   CBTHookProc(   long   nCode,WPARAM   wParam,LPARAM   lParam) ;
extern HHOOK   hHook; 

HANDLE m_hExit;
DWORD dwResult = 0;
unsigned threadID = 0;

int sp;         
int count = 0;
int End_pThread;   

//HANDLE hEventFinish = CreateEvent(NULL,TRUE,FALSE,NULL);
UINT __cdecl MyThreadProc(LPVOID pParam)
{ 
	CCalibrationApp *app = (CCalibrationApp *)AfxGetApp();

	_ConnectionPtr m_pAppConn; //连接对象指针 
	_RecordsetPtr  m_recordset, m_recordset2, m_recordset3;
	CString str, str1, str2;

	if (!app->g_com.IsOpen())
	{
		app->g_com.Open(app->commm, 9600, NOPARITY, 8, TWOSTOPBITS);
	}
	m_pAppConn.CreateInstance(__uuidof(Connection));
	m_pAppConn->Open("File Name=MyData.udl", "", "", adConnectUnspecified);

	CString sql;
	sql.Format("USE settings");
	m_pAppConn->Execute((_bstr_t)sql, NULL, adCmdText);

	sql.Format("select netword_IDN from Independent_settings");
	try
	{
		m_recordset = m_pAppConn->Execute((_bstr_t)sql, NULL, adCmdText);
		if (!m_recordset->adoEOF)
		{
			m_recordset->MoveFirst();
		}
		else
		{
			if (app->language == 0)
			{
				AfxMessageBox("没有发现表!");
			}
			else
			{
				hHook = SetWindowsHookEx(WH_CBT, (HOOKPROC)CBTHookProc, AfxGetInstanceHandle(), NULL);
				AfxMessageBox("Found No meter!");
			}
			sp = 0;
			return 0;
		}
	}
	catch (_com_error e)
	{
		AfxMessageBox(e.ErrorMessage());
	}
	sp = 1;

	//Repetitively read flow rate, sound speed, S, Q and R
	while (0)
	{
		int m = 0;
		m_recordset->MoveFirst();

		while (!m_recordset->adoEOF)
		{
			if (sp == 0)
			{
				sp = 1;
				do
				{
					Sleep(50);
				} while (sp == 1);
				sp = 1;
			}

			if (End_pThread == 1)
			{
				return 0;
			}
			sql.Format("select count(netword_IDN) idncount from Independent_settings");
			try
			{
				m_recordset2 = m_pAppConn->Execute((_bstr_t)sql, NULL, adCmdText);
				_variant_t var = m_recordset2->GetCollect("idncount");
				CString cstr = (char *)_bstr_t(var);
				int a;
				sscanf(cstr, "%d", &a);
				app->no = a;
			}
			catch (_com_error e)
			{
				AfxMessageBox(e.ErrorMessage());
			}
			//count = 0;

			_variant_t var = m_recordset->GetCollect("netword_IDN");
			CString meter = (char *)_bstr_t(var);

			int i;
			int len = meter.GetLength();
			str1 = "";
			str1 += "\x57";//YC Note: W

			for (i = 0; i < len; i++)
			{
				switch (meter.GetAt(i))
				{
				case '0':
					str1 += "\x30";
					break;
				case '1':
					str1 += "\x31";;
					break;
				case '2':
					str1 += "\x32";
					break;
				case '3':
					str1 += "\x33";
					break;
				case '4':
					str1 += "\x34";
					break;
				case '5':
					str1 += "\x35";
					break;
				case '6':
					str1 += "\x36";
					break;
				case '7':
					str1 += "\x37";
					break;
				case '8':
					str1 += "\x38";
					break;
				case '9':
					str1 += "\x39";
					break;
				}
			}

			int pi = 0;
			char buf[60] = { 0 };
			int xnm = 0;

			CString temp1, temp2, temp3, temp4;
			do
			{
				char menu[6] = { '\x4d', '\x45', '\x4e', '\x55', '\x30', '\x31' };//YC Note: MENU01
				for (i = 0; i < 6; i++)
				{
					str2 += CString(menu[i]);
				}
				str2 += "\x0d";//YC Note: /r - Return

				str = str1 + str2;
				app->g_com.Write(str);
				str = "";
				str2 = "";

				str2 += "\x4c\x43\x44\x0d";//YC Note: LCD/r

				str = str1 + str2;
				pi = 0;
				app->g_com.Write(str);
				str = "";
				str2 = "";
				app->g_com.Read(buf, 60);
				Sleep(100);
				if (strstr(buf, "Flow") != NULL && strstr(buf, "Cutoff") == NULL || strstr(buf, "流量") != NULL)
				{
					pi = 1;
				}
				xnm++;
				if (xnm == 5)
				{
					break;
				}
			} while (!pi);//While pi==0, repeat inquiring MENU01 flow rate and LCD/r un less "flow" and "cutoff" received, max 5 requesting
			str = "";
			str2 = "";

			app->liuliang[m].mmeter = meter;
			if (xnm == 5)
			{
				app->liuliang[m].mflux = -1;
				app->liuliang[m].mspeed = -1;
				app->liuliang[m].unflux = " ";
				app->liuliang[m].unspeed = " ";
			}
			else
			{

				CString xx;
				CString us;
				CString xc;
				CString uf;

				char *p = NULL;

				if ((strstr(buf, "流量")) != NULL)
				{
					if ((p = strstr(buf, "流速")) != NULL)
					{
						xx.Format("%c%c%c%c%c%c%c", *(p + 5), *(p + 6), *(p + 7), *(p + 8), *(p + 9), *(p + 10), *(p + 11));
						us.Format("%c%c%c%c", *(p + 13), *(p + 14), *(p + 15), *(p + 16));
					}
				}
				else if (strstr(buf, "Flow") != NULL)
				{
					//p = strstr(buf, "Vel");
					if ((p = strstr(buf, "Vel")) != NULL)
					{

						xx.Format("%c%c%c%c%c%c%c", *(p + 5), *(p + 6), *(p + 7), *(p + 8), *(p + 9), *(p + 10), *(p + 11));

						us.Format("%c%c%c%c", *(p + 13), *(p + 14), *(p + 15), *(p + 16));
					}

				}
				float speed;
				sscanf(xx, "%f", &speed);
				us.TrimLeft();
				us.TrimRight();


				if ((p = strstr(buf, "流量")) != NULL)
				{
					xc.Format("%c%c%c%c%c%c%c", *(p + 5), *(p + 6), *(p + 7), *(p + 8), *(p + 9), *(p + 10), *(p + 11));
					uf.Format("%c%c%c%c", *(p + 13), *(p + 14), *(p + 15), *(p + 16));
				}
				else if ((p = strstr(buf, "Flow")) != NULL)
				{
					xc.Format("%c%c%c%c%c%c%c", *(p + 5), *(p + 6), *(p + 7), *(p + 8), *(p + 9), *(p + 10), *(p + 11));
					uf.Format("%c%c%c%c", *(p + 13), *(p + 14), *(p + 15), *(p + 16));
				}
				float fflow;
				sscanf(xc, "%f", &fflow);
				uf.TrimLeft();
				uf.TrimRight();

				app->liuliang[m].mflux = fflow;
				app->liuliang[m].mspeed = speed;
				app->liuliang[m].unflux = uf;
				app->liuliang[m].unspeed = us;
				p = NULL;
			}

			CCalibrationApp *app = (CCalibrationApp *)AfxGetApp();

			str2 += "\x44\x4c\x0d";//YC Note: DL\r

			//发送消息
			char buf2[60] = { 0 };
			str = str1 + str2;
			int fl = 1;
			xnm = 0;

			Sleep(100);
			do
			{
				app->g_com.Write(str);
				app->g_com.Read(buf2, 60);
				Sleep(100);
				if (strstr(buf2, "UP") != NULL && strstr(buf2, "DN") != NULL)
				{
					fl = 0;
				}
				xnm++;
				if (xnm == 5)
				{
					break;
				}
			} while (fl);//While fl==1, repeat inquiring MENU01 flow rate and LCD/r unless "up" and "dn" received, max 5 requesting
			str = "";
			str2 = "";

			//接收消息, write up, down and Q in liuliang[m].S
			if (xnm == 5)
			{
				//app->liuliang[m].S.Format("UP:ERROR,DN:ERROR");
				//app->liuliang[m].Q.Format("ERROR");
			}
			else
			{
				CString value_s;
				CString value_q;
				CString up;
				CString dn;
				char *p2 = strstr(buf2, "UP");

				if ((p2 = strstr(buf2, "UP")) != NULL)
				{
					up.Format("%c%c%c%c", *(p2 + 3), *(p2 + 4), *(p2 + 5), *(p2 + 6));
				}
				if ((p2 = strstr(buf2, "DN")) != NULL)
				{
					dn.Format("%c%c%c%c", *(p2 + 3), *(p2 + 4), *(p2 + 5), *(p2 + 6));
				}
				if ((p2 = strstr(buf2, "Q=")) != NULL)
				{
					app->liuliang[m].Q.Format("%c%c", *(p2 + 2), *(p2 + 3));
				}
				p2 = NULL;
				app->liuliang[m].S.Format("UP:%s,DN:%s", up, dn);

			}

			//发送消息

			char buf4[60] = { 0 };
			int bj = 0;
			xnm = 0;

			Sleep(100);
			do
			{
				char menu2[6] = { '\x4d', '\x45', '\x4e', '\x55', '\x39', '\x31' };//YC Note: MENU91
				for (i = 0; i < 6; i++)
				{
					str2 += CString(menu2[i]);
				}
				str2 += "\x0d";//YC Note: /r

				str = str1 + str2;
				app->g_com.Write(str);
				str2 = "";
				str = "";
				str2 += "\x4c\x43\x44\x0d";//YC Note: LCD/r

				str = str1 + str2;
				app->g_com.Write(str);
				str2 = "";
				str = "";
				app->g_com.Read(buf4, 60);
				Sleep(100);
				if (strstr(buf4, "时间比") != NULL || strstr(buf4, "[91") != NULL)
				{
					bj = 1;
				}
				xnm++;
				if (xnm == 5)
				{
					break;
				}
			} while (!bj);//YC Note: keep requesting menu 91 information, max 5 requests
			str = "";
			str2 = "";
			if (xnm == 5)
			{
				app->liuliang[m].R.Format("ERROR");
			}//YC Note: ERROR report 5 requests have been reached, 
			else
			{
				char temp[20] = { 0 };
				char *p5 = NULL;
				if ((p5 = strstr(buf4, "时间比")) != NULL)
				{
					p5 += 9;
					strncpy(temp, p5, 16);
				}
				else if ((p5 = strstr(buf4, "[91")) != NULL)
				{
					p5 += 6;
					strncpy(temp, p5, 16);
				}
				CString strtemp;
				strtemp.Format("%s", temp);
				strtemp.TrimLeft();

				app->liuliang[m].R.Format("%s", strtemp);
				p5 = NULL;
			}//YC Note: report R value
		
			str1 = "";
			str2 = "";
			str = "";

			m++;
			m_recordset->MoveNext();
		}
	}//while(1) loop//
	m_pAppConn->Close();

	if (m_recordset)
		if (m_recordset->State == adStateOpen)
			m_recordset->Close();

	if (m_recordset2)
		if (m_recordset2->State == adStateOpen)
			m_recordset2->Close();

	if (m_recordset3)
		if (m_recordset3->State == adStateOpen)
			m_recordset3->Close();

	// Terminate the thread
	::AfxEndThread(0, FALSE);
	return 0;
}

BOOL CSetZeroDlg::OnInitDialog() 
{

	CDialog::OnInitDialog();
	OnStart = 0;
	// TODO: Add extra initialization here
	int cx = GetSystemMetrics(SM_CXFULLSCREEN);
	int cy = GetSystemMetrics(SM_CYFULLSCREEN);

	MoveWindow((cx-490)/2-190, (cy-470)/2, 490, 470);
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
		this->SetWindowText("置零及调流速");
		GetDlgItem(IDC_M41)->SetWindowText("低流速切除值");
		GetDlgItem(IDC_M42)->SetWindowText("静态置零");
		GetDlgItem(IDC_M_2)->SetWindowText("储存当前零点延迟");
		GetDlgItem(IDC_STATIC_SZ)->SetWindowText("置零");
		GetDlgItem(IDC_STATIC_DB)->SetWindowText("调流速");
		GetDlgItem(IDC_COLLECT)->SetWindowText("大流速采集");
		GetDlgItem(IDC_STATIC_TEXT)->SetWindowText("取值3次值，用时60s");
		GetDlgItem(IDC_COLLECT2)->SetWindowText("中流速采集");
		GetDlgItem(IDC_STATIC_TEXT2)->SetWindowText("取值3次值，用时60s");
		GetDlgItem(IDC_COLLECT3)->SetWindowText("低流速采集");
		GetDlgItem(IDC_STATIC_TEXT3)->SetWindowText("取值3次值，用时120s");
		::EnumChildWindows(m_hWnd, ::SetChildFont, (LPARAM)&g_Font);
	}
	else
	{
		this->SetWindowText("Zero Setting and Flow Rate Debugging");
		GetDlgItem(IDC_M41)->SetFont(&g_Font);
		GetDlgItem(IDC_M41)->SetWindowText("Low Flow Cutoff Value");

		GetDlgItem(IDC_M42)->SetFont(&g_Font);
		GetDlgItem(IDC_M42)->SetWindowText("Set Zero");

		GetDlgItem(IDC_M_2)->SetFont(&g_Font);
		GetDlgItem(IDC_M_2)->SetWindowText("Store Zero-Point");

		GetDlgItem(IDC_STATIC_SZ)->SetFont(&g_Font);
		GetDlgItem(IDC_STATIC_SZ)->SetWindowText("Set Zero");

		GetDlgItem(IDC_STATIC_DB)->SetFont(&g_Font);
		GetDlgItem(IDC_STATIC_DB)->SetWindowText("Flow Rate Debugging");

		GetDlgItem(IDC_COLLECT)->SetFont(&g_Font);
		GetDlgItem(IDC_COLLECT)->SetWindowText("Collect(Qmax)");

		GetDlgItem(IDC_STATIC_TEXT)->SetFont(&g_Font);
		GetDlgItem(IDC_STATIC_TEXT)->SetWindowText("Collect high flow rate");

		GetDlgItem(IDC_COLLECT2)->SetFont(&g_Font);
		GetDlgItem(IDC_COLLECT2)->SetWindowText("Collect(Qmid)");

		GetDlgItem(IDC_STATIC_TEXT2)->SetFont(&g_Font);
		GetDlgItem(IDC_STATIC_TEXT2)->SetWindowText("Collect medium flow rate");

		GetDlgItem(IDC_COLLECT3)->SetFont(&g_Font);
		GetDlgItem(IDC_COLLECT3)->SetWindowText("Collect(Qmin)");

		GetDlgItem(IDC_STATIC_TEXT3)->SetFont(&g_Font);
		GetDlgItem(IDC_STATIC_TEXT3)->SetWindowText("Collect low flow rate");

		GetDlgItem(IDC_BUTTON6)->SetFont(&g_Font);
		GetDlgItem(IDC_BUTTON6)->SetWindowText("Auto Calibrate");

		GetDlgItem(IDC_FLUSH)->SetFont(&g_Font);
		GetDlgItem(IDC_FLUSH)->SetWindowText("Auto Cali w/o Zero");
	}
	app->p = 1;
	m_flag = 0;

	UpdateData(FALSE);

	showdlg = new CShowDlg;
	showdlg->Create(IDD_SHOW);
	showdlg->ShowWindow(SW_HIDE);

	HWND hwnd;
	if (app->language == 0)
	{
		hwnd = ::FindWindow(NULL, _T("显示"));
	}
	else
	{
		hwnd = ::FindWindow(NULL, _T("Show"));
	}
	::SendMessage(hwnd, WM_MYMESSAGE, 0, 0);//向指定窗口中发送消息
	m_Font = new CFont;
	m_Font->CreateFont(-18,0,0,0,100,FALSE,FALSE,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,FF_SWISS,"Arial");

	delete m_Font;
	m_Font = NULL;

	try
	{
		HRESULT hr = m_pAppConn.CreateInstance(__uuidof(Connection));
		if (FAILED(hr))
			AfxMessageBox("Can't create an intance of ADO.Connection");

		if (FAILED(m_pAppConn->Open(_bstr_t("File Name=MyData.udl"), _bstr_t(""), _bstr_t(""), adModeUnknown)))
			::AfxMessageBox(TEXT("Can't open datasource"));

	}
	catch (_com_error &e)
	{
		::AfxMessageBox(TEXT("I am in catch block 6"));
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

	CString sql;
	sql.Format("USE settings");
	m_pAppConn->Execute((_bstr_t)sql,NULL,adCmdText);
	
	SYSTEMTIME st;
	CString strtime;
	GetLocalTime(&st);
	strtime.Format("%04d%02d%02d", st.wYear, st.wMonth, st.wDay);

	sql.Format("SELECT RIGHT(name,11) no FROM sysobjects WHERE name LIKE \'Data%c\'", '%');
	try
	{
		m_recordset = m_pAppConn->Execute((_bstr_t)sql,NULL,adCmdText);
		if (!m_recordset->adoEOF)
		{
			m_recordset->MoveFirst();
		}
		int fl = 1;
		CString no;
		while(!m_recordset->adoEOF)
		{
			_variant_t var = m_recordset->GetCollect("no");
			no = (char *)_bstr_t(var);
			CString date = no.Left(8);
			if (date.Compare(strtime)==0)
			{
				fl = 0;
				break;
			}
			m_recordset->MoveNext();
		}

		if (1 == fl)
		{
			sql.Format("CREATE TABLE Data%s001(netword_IDN int,s_n varchar(50),flow varchar(50),flow_1  varchar(50),flow_2 varchar(50),flow_3 varchar(50),Rflow_1 varchar(50),Rflow_2 varchar(50),Rflow_3 varchar(50),error_1 varchar(50),error_2 varchar(50),error_3 varchar(50))", strtime);
			try
			{
				m_pAppConn->Execute((_bstr_t)sql,NULL,adCmdText);	
			}
			catch (_com_error e)
			{
				AfxMessageBox(e.ErrorMessage());
			}
		}
		else if (0 == fl)
		{
			int temp, max = 0;
			sql.Format("SELECT RIGHT(name,3) bh FROM sysobjects WHERE name LIKE \'Data%s%c\'", strtime, '%');
			try
			{
				m_recordset = m_pAppConn->Execute((_bstr_t)sql,NULL,adCmdText);
				if (!m_recordset->adoEOF)
				{
					m_recordset->MoveFirst();
				}
				while(!m_recordset->adoEOF)
				{
					_variant_t var = m_recordset->GetCollect("bh");
					CString bh = (char *)_bstr_t(var);
					sscanf(bh, "%d", &temp);
					if (max < temp)
					{
						max = temp;
					}
					m_recordset->MoveNext();
				}
			}
			catch (_com_error e)
			{
				AfxMessageBox(e.ErrorMessage());
			}

			sql.Format("CREATE TABLE Data%s%03d(netword_IDN int,s_n varchar(50),flow varchar(50),flow_1  varchar(50),flow_2 varchar(50),flow_3 varchar(50),Rflow_1 varchar(50),Rflow_2 varchar(50),Rflow_3 varchar(50),error_1 varchar(50),error_2 varchar(50),error_3 varchar(50))", strtime, max+1);
			try
			{
				m_pAppConn->Execute((_bstr_t)sql,NULL,adCmdText);	
			}
			catch (_com_error e)
			{
				AfxMessageBox(e.ErrorMessage());
			}
		}
	}
	catch (_com_error e)
	{
		AfxMessageBox(e.ErrorMessage());
	}

	GetDlgItem(IDC_BUTTON_SHOW)->EnableWindow(TRUE);

	sp = 1;
	SetZeroComplete = false;
	ManualSetZero = false;
	if(m_m41!="")
		OnM41();

	m_wait_time = "240";
	m_sample_time = "360";
	v_max = "0";
	v_mid = "5";
	v_low = "7";
	v_max_f = .0f;
	v_mid_f = 5.0f;
	v_low_f = 7.0f;
	m_delay = 240;

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

int t; //用于记录OnTimer函数运行次数

void CSetZeroDlg::OnChangeEditWaitTime()
{
	UpdateData(true);
	m_delay = atoi(m_wait_time);
	UpdateData(FALSE);
}

void CSetZeroDlg::OnChangeEditSampleTime()
{
	CCalibrationApp *app = (CCalibrationApp *)AfxGetApp();

	UpdateData(true);
	app->Global_Sampling_Total = atoi(m_sample_time) / 3;
	UpdateData(FALSE);
}

void CSetZeroDlg::OnChangeVCMax() {
	UpdateData(true);
	v_max_f = float(atof(v_max));
	UpdateData(FALSE);
}

void CSetZeroDlg::OnChangeVCMid() {
	UpdateData(true);
	v_mid_f = float(atof(v_mid));
	UpdateData(FALSE);
}

void CSetZeroDlg::OnChangeVCLow() {
	UpdateData(true);
	v_low_f = float(atof(v_low));
	UpdateData(FALSE);
}

//YC Note: Set Zero button clicked
void CSetZeroDlg::OnM42() 
{
	//CMessageBoxDlg mbd;
	//int result = mbd.DoModal();
	//if (result == IDOK)
	//{
		sp = 0;
		//do{
		//	Sleep(50);
		//}
		//while (sp == 0);
		
		//GetDlgItem(IDC_STATIC_SHOW)->ShowWindow(FALSE);
		CCalibrationApp *app = (CCalibrationApp *)AfxGetApp();
		if (!app->g_com.IsOpen())
		{
			app->g_com.Open(app->commm,9600,NOPARITY,8,TWOSTOPBITS);
		}
		UpdateData(TRUE);
		
		CString sql;
		int count = 0;
		int res = 0;
		CString str1, str2;
		sql.Format("select netword_IDN from Independent_settings where state=1");
		try
		{
			m_recordset = m_pAppConn->Execute((_bstr_t)sql, NULL, adCmdText);
			if (!m_recordset->adoEOF)
			{
				m_recordset->MoveFirst();
				res = 0;
			}
			else
			{
				if (app->language == 0)
				{
					AfxMessageBox("没有发现可置零的表!");
				}
				else
				{
					hHook=SetWindowsHookEx(WH_CBT,(HOOKPROC)CBTHookProc,AfxGetInstanceHandle(),NULL); 
					AfxMessageBox("Did not find the meter may be set zero!");

					//gl test
					//m_show = "Failure";
					//UpdateData(FALSE);
					//res = 1;
					//return;
					//gl test end
				}
			}	
			while (!m_recordset->adoEOF)
			{
				_variant_t var = m_recordset->GetCollect("netword_IDN");
				CString cstr = (char *)_bstr_t(var);
				str1 += "\x57";
				int len = cstr.GetLength();
				int i;
				for (i=0; i<len; i++)
				{
					switch(cstr.GetAt(i))
					{
					case '0':
						str1 += "\x30";
						break;
					case '1':
						str1 += "\x31";;
						break;
					case '2':
						str1 += "\x32";
						break;
					case '3':
						str1 += "\x33";
						break;
					case '4':
						str1 += "\x34";
						break;
					case '5':
						str1 += "\x35";
						break;
					case '6':
						str1 += "\x36";
						break;
					case '7':
						str1 += "\x37";
						break;
					case '8':
						str1 += "\x38";
						break;
					case '9':
						str1 += "\x39";
						break;
					}
				}
				char menu[6] = {'\x4d', '\x45', '\x4e', '\x55', '\x34', '\x32'};
				for (i=0; i<6; i++)
				{
					str2 += CString(menu[i]);//MENU42
				}
				str2 += "\x26\x4d\x3d\x0d";//&M (ENT)\r

				str = str1 + str2;
				app->g_com.Write(str);
				Sleep(100);
				str = "";
				str2 = "";

				str2 = "\x4c\x43\x44\x0d";//LCD\r

				str = str1 + str2;//LCD\r
				app->g_com.Write(str);
				Sleep(100);
				str = "";
				str2 = "";
				char buf[60] = {0};
				
				app->g_com.Read(buf, 60);
				if (strstr(buf, "流体没有静止") != NULL || strstr(buf, "No stop Flow") != NULL)
				{
					int result2 = AfxMessageBox("Flow is not stopped, Please close the valve");
					if (result2 == IDOK)
					{
						str2 = "\x4d\x3d\x0d";//M(ENT)\r

						str = str1 + str2;
						app->g_com.Write(str);
						Sleep(100);
						str = "";
						str2 = "";
					}
				}
				str1 = "";
				m_recordset->MoveNext();
			}			
		}
		catch(_com_error e)
		{
			AfxMessageBox("I am in M42 catch block!");
			AfxMessageBox(e.ErrorMessage());
		}
		t = 0;
		m_show = "";
		if (res == 0)//Set zero not fail;
		{
			UpdateData(FALSE);
			GetDlgItem(IDC_M42)->EnableWindow(FALSE);
			SetTimer(1, 500, NULL);
			OnStart = 2;
		}
	//}	
}

//YC Note: for set zero on automatic calibration
void CSetZeroDlg::OnM42_Cal()
{
	CCalibrationApp *app = (CCalibrationApp *)AfxGetApp();
	sp = 0;
	//GetDlgItem(IDC_STATIC_SHOW)->ShowWindow(FALSE);
	
	if (!app->g_com.IsOpen())
	{
		app->g_com.Open(app->commm, 9600, NOPARITY, 8, TWOSTOPBITS);
	}
	UpdateData(TRUE);

	CString sql;
	int count = 0;
	int res = 0;
	CString str1, str2;
	Meter_err err;
	sql.Format("select netword_IDN from Independent_settings where state=1");
	try
	{
		m_recordset = m_pAppConn->Execute((_bstr_t)sql, NULL, adCmdText);
		if (!m_recordset->adoEOF)
		{
			m_recordset->MoveFirst();
			res = 0;
		}
		else
		{
			if (app->language == 0)
			{
				AfxMessageBox("没有发现可置零的表!");
			}
			else
			{
				hHook = SetWindowsHookEx(WH_CBT, (HOOKPROC)CBTHookProc, AfxGetInstanceHandle(), NULL);
				AfxMessageBox("Did not find the meter may be set zero!");

				//gl test
				//m_show = "Failure";
				//UpdateData(FALSE);
				//res = 1;
				//return;
				//gl test end

			}
		}
		while (!m_recordset->adoEOF)
		{
			_variant_t var = m_recordset->GetCollect("netword_IDN");
			CString cstr = (char *)_bstr_t(var);
			str1 += "\x57";
			int len = cstr.GetLength();
			int i;
			for (i = 0; i<len; i++)
			{
				switch (cstr.GetAt(i))
				{
				case '0':
					str1 += "\x30";
					break;
				case '1':
					str1 += "\x31";;
					break;
				case '2':
					str1 += "\x32";
					break;
				case '3':
					str1 += "\x33";
					break;
				case '4':
					str1 += "\x34";
					break;
				case '5':
					str1 += "\x35";
					break;
				case '6':
					str1 += "\x36";
					break;
				case '7':
					str1 += "\x37";
					break;
				case '8':
					str1 += "\x38";
					break;
				case '9':
					str1 += "\x39";
					break;
				}
			}
			char menu[6] = { '\x4d', '\x45', '\x4e', '\x55', '\x34', '\x32' };
			for (i = 0; i<6; i++)
			{
				str2 += CString(menu[i]);
			}
			str2 += "\x26\x4d\x3d\x0d";

			str = str1 + str2;
			app->g_com.Write(str);
			Sleep(100);
			str = "";
			str2 = "";

			str2 = "\x4c\x43\x44\x0d";

			str = str1 + str2;
			app->g_com.Write(str);
			Sleep(100);
			str = "";
			str2 = "";
			char buf[60] = { 0 };

			app->g_com.Read(buf, 60);
			if (strstr(buf, "流体没有静止") != NULL || strstr(buf, "No stop Flow") != NULL)
			{
				/*int result2 = AfxMessageBox("Flow is not stopped, Please close the valve");
				if (result2 == IDOK)
				{
					str2 = "\x4d\x3d\x0d";//M=(CR)

					str = str1 + str2;
					app->g_com.Write(str);
					Sleep(100);
					str = "";
					str2 = "";
				}*/
				err.err_no = 9;//YC Note on Nov 23, 2016: looks like it is useless at this moment
				err.err_msg = "Flow is not stopped, Please close the valve";
				throw err;
			}
			str1 = "";
			m_recordset->MoveNext();
		}
	}
	catch (_com_error e)
	{
		AfxMessageBox("I am in M42 catch block!");
		AfxMessageBox(e.ErrorMessage());
	}

	t = 0;
	m_show = "";
	if (res == 0)
	{
		UpdateData(FALSE);
		GetDlgItem(IDC_M42)->EnableWindow(FALSE);
		//SetTimer(1, 500, NULL);
		Sleep(45000);//Wait 45s to let count down complete
		m_show = "Set zero success!";
		OnStart = 2;
	}
}

//YC Note: low flow cut off value
void CSetZeroDlg::OnM41() 
{
	CCalibrationApp *app = (CCalibrationApp *)AfxGetApp();

	sp = 0;

	//do{
	//	Sleep(50);
	//}
	//while (sp == 0);
	
	UpdateData(TRUE);

	CString temp1;
	int i;
	char menu[6] = { '\x4d', '\x45', '\x4e', '\x55', '\x34', '\x31' };
	for (i=0; i<6; i++)
	{
		str += CString(menu[i]);
	}
	if (m_m41 != "")
	{	
		str += "\x26\x4d\x3d";

		for (i=0; i<m_m41.GetLength(); i++)
		{
			switch(m_m41.GetAt(i))
			{
			case '0':
				str += "\x26\x4d\x30";
				break;
			case '1':
				str += "\x26\x4d\x31";
				break;
			case '2':
				str += "\x26\x4d\x32";
				break;
			case '3':
				str += "\x26\x4d\x33";;
				break;
			case '4':
				str += "\x26\x4d\x34";
				break;
			case '5':
				str += "\x26\x4d\x35";
				break;
			case '6':
				str += "\x26\x4d\x36";
				break;
			case '7':
				str += "\x26\x4d\x37";
				break;
			case '8':
				str += "\x26\x4d\x38";
				break;
			case '9':
				str += "\x26\x4d\x39";
				break;
			case '.':
				str += "\x26\x4d\x3a";
				break;
			default:
				if (app->language == 0)
				{
					AfxMessageBox("您的输入有误!");
				}
				else
				{
					hHook=SetWindowsHookEx(WH_CBT,(HOOKPROC)CBTHookProc,AfxGetInstanceHandle(),NULL); 
					AfxMessageBox("Your input is incorrect!");
				}
			}
		}
		str += "\x26\x4d\x3d\x0d"; 

		app->g_com.Write(str);
		Sleep(100);
		str = "";
		m_show = "";
		if (app->language == 0)
		{
			m_show = "低流速切除值设置成功";	
		}
		else
		{
			m_show = "Low flow cutoff value set success.";	
			OnStart = 1;
		}	
		UpdateData(FALSE);
	}
	else
	{
		m_show = "";
		if (app->language == 0)
		{
			m_show = "低流速切除值设置失败\r\n请确认输入了低流速切除值";
		}
		else
		{
			m_show = "Low flow cutoff value set failure.\r\nPlease make sure to enter the low flow cutoff value.";
		}
		UpdateData(FALSE);
	}

	CString str1;
	CString sql;
	sql.Format("SELECT netword_IDN,table_type FROM Independent_settings where table_type = 0");
	try
	{
		m_recordset = m_pAppConn->Execute((_bstr_t)sql,NULL,adCmdText);
		while (!m_recordset->adoEOF)
		{
			_variant_t var = m_recordset->GetCollect("netword_IDN");
			CString cstr = (char *)_bstr_t(var);
			str1 = "\x57";

			int len = cstr.GetLength();
			for (i=0; i<len; i++)
			{
				switch(cstr.GetAt(i))
				{
				case '0':
					str1 += "\x30";
					break;
				case '1':
					str1 += "\x31";;
					break;
				case '2':
					str1 += "\x32";
					break;
				case '3':
					str1 += "\x33";
					break;
				case '4':
					str1 += "\x34";
					break;
				case '5':
					str1 += "\x35";
					break;
				case '6':
					str1 += "\x36";
					break;
				case '7':
					str1 += "\x37";
					break;
				case '8':
					str1 += "\x38";
					break;
				case '9':
					str1 += "\x39";
					break;
				}
			}
			CString str2;
			char menu[7] = { '\x4d', '\x45', '\x4e', '\x55', '\x32', '\x36', '\x0d' };
			for (i=0; i<7; i++)
			{
				str2 += CString(menu[i]);
			}
			str = str1+ str2;
			app->g_com.Write(str);
			str2 = "";
			str = "";
			//Sleep(100);

			str2 = "\x4d\0x3d\x0d";

			str = str1+ str2;
			app->g_com.Write(str);
			str2 = "";
			str = "";
			//Sleep(100);
			
			str2 = "\x4d\x31\x0d";

			str = str1+ str2;
			app->g_com.Write(str);
			str2 = "";
			str = "";
			//Sleep(100);
			
			str2 = "\x4d\x3d\x0d";

			str = str1+ str2;
			app->g_com.Write(str);
			str2 = "";
			str = "";
			
			Sleep(100);
			str1 = "";
			m_recordset->MoveNext();
		}
		
	}
	catch (_com_error e)
	{
		AfxMessageBox(e.ErrorMessage());
	}

	Sleep(1000);
	sp = 0;
}

int flag;

float collect[60] = {0};
void CSetZeroDlg::OnTimer(UINT nIDEvent)//Set zero count down 
{
	// TODO: Add your message handler code here and/or call default
	CCalibrationApp *app = (CCalibrationApp *)AfxGetApp();
	CString sql;

	switch(nIDEvent)
	{
		case 1:                                  
		{	
			CString show;
			if (app->language == 0)
			{
				show.Format("置零中。。。%d\r\n--------------------\r\n", 38-t);
			}
			else
			{
				show.Format("Set zero...%d\r\n--------------------\r\n", 38-t);
			}	
			m_show = show;
			UpdateData(FALSE);
			if (t == 38)
			{
				if (app->language == 0)
				{
					show.Format("置零完成!\r\n--------------------\r\n");
				}
				else
				{
					show.Format("Set zero is complete!\r\n--------------------\r\n");
				}
				m_show = show;
				UpdateData(FALSE);
				sql.Format("select netword_IDN from Independent_settings where state=0");
				m_recordset = m_pAppConn->Execute((_bstr_t)sql, NULL, adCmdText);
				if (!m_recordset->adoEOF)
				{
					m_recordset->MoveFirst();
				}
				while (!m_recordset->adoEOF)
				{
					_variant_t var = m_recordset->GetCollect("netword_IDN");
					CString cstr = (char *)_bstr_t(var);
					CString ge;
					ge = m_show;
					CString show;
					if (app->language == 0)
					{
						show.Format("%s号表置零失败\r\n--------------------\r\n", cstr);
					}
					else
					{
						show.Format("IDN %s set zero failure\r\n--------------------\r\n", cstr);
					}
					show = ge+show;
					m_show = show;
					UpdateData(FALSE);
					m_recordset->MoveNext();
				}
				sql.Format("select netword_IDN from Independent_settings where state=1");
				try
				{
					_RecordsetPtr m_recordset2 = m_pAppConn->Execute((_bstr_t)sql, NULL, adCmdText);
					if (!m_recordset2->adoEOF)
					{
						m_recordset2->MoveFirst();
					}
					while (!m_recordset2->adoEOF)
					{
						_variant_t var = m_recordset2->GetCollect("netword_IDN");
						CString cstr = (char *)_bstr_t(var);
						str += "\x57";

						int len = cstr.GetLength();
						int i;
						for (i=0; i<len; i++)
						{
							switch(cstr.GetAt(i))
							{
							case '0':
								str += "\x30";
								break;
							case '1':
								str += "\x31";;
								break;
							case '2':
								str += "\x32";
								break;
							case '3':
								str += "\x33";
								break;
							case '4':
								str += "\x34";
								break;
							case '5':
								str += "\x35";
								break;
							case '6':
								str += "\x36";
								break;
							case '7':
								str += "\x37";
								break;
							case '8':
								str += "\x38";
								break;
							case '9':
								str += "\x39";
								break;
							}
						}
						char menu[6] = { '\x4d', '\x45', '\x4e', '\x55', '\x30', '\x31' };
						for (i=0; i<6; i++)
						{
							str += CString(menu[i]);
						}
						str += "\x26\x4c\x43\x44\x0d";

						int pi = 0;
						char buf[60] = {0};
						int xnm = 0;
						do
						{
							pi = 0;
							app->g_com.Write(str);
							Sleep(100);
							app->g_com.Read(buf, 60);
							Sleep(100);
							if (strstr(buf, "Flow") != NULL && strstr(buf, "Cutoff") == NULL || strstr(buf, "流量") != NULL)
							{
								pi = 1;
							}
							xnm++;
							if (xnm == 5)
							{
								break;
							}
						}
						while(!pi);
						str = "";
						
						CString xx, us;
						if (xnm == 5)
						{
							xx.Format("ERROR");
						}
						else
						{		
							char *p = NULL;
							if ((strstr(buf, "流量")) != NULL)
							{
								p = strstr(buf, "流速");
								xx.Format("%c%c%c%c%c%c%c", *(p+5), *(p+6), *(p+7), *(p+8), *(p+9), *(p+10), *(p+11));
								us.Format("%c%c%c%c", *(p+13), *(p+14), *(p+15), *(p+16));
							}
							else if (strstr(buf, "Flow") != NULL)
							{
								p = strstr(buf, "Vel");
								xx.Format("%c%c%c%c%c%c%c", *(p+5), *(p+6), *(p+7), *(p+8), *(p+9), *(p+10), *(p+11));
								us.Format("%c%c%c%c", *(p+13), *(p+14), *(p+15), *(p+16));
							}
							us.TrimLeft();
							us.TrimRight();
						}
						float vel;
						sscanf(xx, "%f", &vel);
						
						if (vel < 0.005 && strstr(us, "m/s")!=NULL || vel < 0.0164 && strstr(us, "ft/s")!=NULL)
						{
							CString ge;
							ge = m_show;
							CString show;
							if (app->language == 0)
							{
								show.Format("%s号表置零成功\r\n流速%s%s\r\n--------------------\r\n", cstr, xx, us);
							}
							else
							{
								show.Format("IDN %s set zero success\r\nflow rate%s%s\r\n--------------------\r\n", cstr, xx, us);
							}
							show = ge+show;
							m_show = show;
							UpdateData(FALSE);
						}
						else
						{
							CString ge;
							ge = m_show;
							CString show;
							if (app->language == 0)
							{
								show.Format("%s号表置零失败\r\n--------------------\r\n", cstr);
							}
							else
							{
								show.Format("IDN %s set zero failure\r\n--------------------\r\n", cstr);
							}
							show = ge+show;
							m_show = show;
							UpdateData(FALSE);
						}
						m_recordset2->MoveNext();
					}	
				}
				catch(_com_error e)
				{
					AfxMessageBox(e.ErrorMessage());
				}
				GetDlgItem(IDC_M42)->EnableWindow(TRUE);
				KillTimer(1);
				SetZeroComplete = true;
				sp = 0;
				//AfxBeginThread((AFX_THREADPROC)MyThreadProc, NULL);
			}
			t++;

			break;
		}
	}
	CDialog::OnTimer(nIDEvent);
}

//get flow rate and positive totalizer
void CSetZeroDlg::OnM_2() 
{
	// TODO: Add your control notification handler code here
	sp = 0;
	//do{
	//	Sleep(50);
	//}
	//while (sp == 0);
	
	m_show = "";
	UpdateData(FALSE);
	CCalibrationApp *app = (CCalibrationApp *)AfxGetApp();
	app->p = 0;
	if (!app->g_com.IsOpen())
	{
		app->g_com.Open(app->commm,9600,NOPARITY,8,TWOSTOPBITS);
	}
	int i;
	CString cstr;
	CString sql;
	sql.Format("select netword_IDN from Independent_settings");
	try
	{
		m_recordset = m_pAppConn->Execute((_bstr_t)sql, NULL, adCmdText);
		if (!m_recordset->adoEOF)
		{
			m_recordset->MoveFirst();
		}
		else
		{
			if (app->language == 0)
			{
				AfxMessageBox("没有发现表!");
			}
			else
			{
				hHook=SetWindowsHookEx(WH_CBT,(HOOKPROC)CBTHookProc,AfxGetInstanceHandle(),NULL); 
				AfxMessageBox("Found no meter!");
			}
		}
		while (!m_recordset->adoEOF)
		{
			_variant_t var = m_recordset->GetCollect("netword_IDN");
			cstr = (char *)_bstr_t(var);
			int len = cstr.GetLength();
			CString strbeg;
			strbeg += "\x57";

			for (i=0; i<len; i++)
			{
				switch(cstr.GetAt(i))
				{
				case '0':
					strbeg += "\x30";
					break;
				case '1':
					strbeg += "\x31";
					break;
				case '2':
					strbeg += "\x32";
					break;
				case '3':
					strbeg += "\x33";
					break;
				case '4':
					strbeg += "\x34";
					break;
				case '5':
					strbeg += "\x35";
					break;
				case '6':
					strbeg += "\x36";
					break;
				case '7':
					strbeg += "\x37";
					break;
				case '8':
					strbeg += "\x38";
					break;
				case '9':
					strbeg += "\x39";
					break;
				}
			}
			CString strend;
			char menu[6] = { '\x4d', '\x45', '\x4e', '\x55', '\x30', '\x31' };
			for (i=0; i<6; i++)
			{
				strend += CString(menu[i]); 
			}

			strend += "\x0d";

			str = strbeg + strend;
			app->g_com.Write(str);
			str = "";
			str += strbeg +"\x4c\x43\x44\x0d";

			app->g_com.Write(str);
			str = "";
			char buf[60] = {0};
			app->g_com.Read(buf, 60);
			Sleep(100);

			CString xx;
			xx.Format("%c%c%c%c%c%c", buf[37], buf[38], buf[39], buf[40], buf[41], buf[42]);
			float flow;
			sscanf(xx, "%f", &flow);

			if (flow < 0.01)
			{	
				CString ge;
				ge = m_show;
				CString show;
				if (app->language == 0)
				{
					show.Format("%s储存当前零点延迟成功\r\n---------------------\r\n", cstr);
				}
				else
				{
					show.Format("Meter%s stored zero-point successfully!\r\n---------------------\r\n", cstr);
					OnStart = 3;
				}
				show = ge+show;
				m_show = show;
				UpdateData(FALSE);
				str += "\x57";

				for (i=0; i<len; i++)
				{
					switch(cstr.GetAt(i))
					{
					case '0':
						str += "\x30";
						break;
					case '1':
						str += "\x31";;
						break;
					case '2':
						str += "\x32";
						break;
					case '3':
						str += "\x33";
						break;
					case '4':
						str += "\x34";
						break;
					case '5':
						str += "\x35";
						break;
					case '6':
						str += "\x36";
						break;
					case '7':
						str += "\x37";
						break;
					case '8':
						str += "\x38";
						break;
					case '9':
						str += "\x39";
						break;
					}
				}
				
				str += "\x4d\x3c";//M<
				str += "\x26\x4d\x3a";//-M:
				str += "\x26\x4d\x32";//-M2
				str += "\x26\x4d\x3d";//-M
				str += "\x26\x4d\x3d";
				str += "\x26\x4d\x3d\x0d";

				
				Sleep(1000);
				app->g_com.Write(str);
				str = "";
			}
			else
			{
				CString ge;
				ge = m_show;
				CString show;
				if (app->language == 0)
				{
					show.Format("%s号表储存当前零点延迟失败\r\n---------------------\r\n", cstr);
				}
				else
				{
					show.Format("IDN %s Store zero-point failure!\r\n---------------------\r\n", cstr);
				}
				show = ge + show;
				m_show = show;
				UpdateData(FALSE);
			}
			Sleep(500);
			m_recordset->MoveNext();
		}
	}
	catch(_com_error e)
	{
		AfxMessageBox(e.ErrorMessage());
	}
	GetDlgItem(IDC_BUTTON_SHOW)->EnableWindow(TRUE);
	app->p = 1;
	sp = 0;

	if (OnStart >= 3)
	{
		// Create the CEvent object that will be passed to the thread routine
		CEvent* pEvent = new CEvent(FALSE, FALSE);

		// Create a thread that will wait on the event
		//CWinThread* pThread;
		pThread = ::AfxBeginThread(&MyThreadProc, pEvent, 0, 0, CREATE_SUSPENDED, NULL);
		pThread->m_bAutoDelete = FALSE;
		pThread->ResumeThread();

		dwResult = WaitForSingleObject(pThread->m_hThread, 0);
		if (dwResult == WAIT_TIMEOUT)
		{
			printf("The thread is still running...\n");
		}
		else
		{
			printf("The thread is no longer running...\n");
		}
		Sleep(100);
		dwResult = WaitForSingleObject(pThread->m_hThread, 0);
		if (dwResult == WAIT_TIMEOUT)
		{
			printf("The thread is still running...\n");
		}
		else
		{
			printf("The thread is no longer running...\n");
		}

		delete pEvent;

		End_pThread = 0;
		OnStart = 4;
		m_flag = 0;
		OnButtonShow();		
	}
	else
		AfxMessageBox("Please try again!");
	
}

HBRUSH CSetZeroDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here
	if(pWnd->GetDlgCtrlID()== IDC_STATIC_SHOW)   
	{              
		pDC->SetTextColor(RGB(255,0,0));
	}       
	// TODO: Return a different brush if the default is not desired
	return hbr;
}

void CSetZeroDlg::OnCollect() 
{
	dlgResult = 0;

	if (OnStart == 4)
	{
		CCalibrationApp *app = (CCalibrationApp *)AfxGetApp();
		app->flux.Format("max");


		//CMessageBox2Dlg msgb2dlg;
		//int result = msgb2dlg.DoModal();
		//if (result == IDOK)
		//{
		/*Modified by YC
			sp = 0;
			do{
				Sleep(50);
			} while (sp == 0);*/
		//Sleep(500);
		if (!app->g_com.IsOpen()){
			app->g_com.Open(app->commm, 9600, NOPARITY, 8, TWOSTOPBITS);
		}
		app->Global_Sampling_Total = atoi(m_sample_time) / 3;
		UpdateData(TRUE);
		flag = 0;
		CCalibrationDlg *parent = (CCalibrationDlg *)GetParent();

			//modified by YC if (sp == 1)
		dlgResult = collectdlg.DoModal();//YC Note: open pop up window of CollectDlg

			//modified by YC sp = 0;
		//}
	}
	else
	{
		// Create the CEvent object that will be passed to the thread routine
		CEvent* pEvent = new CEvent(FALSE, FALSE);

		// Create a thread that will wait on the event
		//CWinThread* pThread;
		pThread = ::AfxBeginThread(&MyThreadProc, pEvent, 0, 0, CREATE_SUSPENDED, NULL);
		pThread->m_bAutoDelete = FALSE;
		pThread->ResumeThread();

		dwResult = WaitForSingleObject(pThread->m_hThread, 0);
		if (dwResult == WAIT_TIMEOUT)
		{
			printf("The thread is still running...\n");
		}
		else
		{
			printf("The thread is no longer running...\n");
		}

		delete pEvent;

		End_pThread = 0;
		OnStart = 4;
		OnCollect();
	}
}

void CSetZeroDlg::OnCollect2() 
{
	dlgResult = 0;

	if (OnStart == 4)
	{
		CCalibrationApp *app = (CCalibrationApp *)AfxGetApp();

		app->flux.Format("mid");
		//CMessageBox2Dlg msgb2dlg;
		//int result = msgb2dlg.DoModal();
		//if (result == IDOK)
		//{
		/*	sp = 0;
			do{
				Sleep(50);
			} while (sp == 0);*/
		if (!app->g_com.IsOpen()){
			app->g_com.Open(app->commm, 9600, NOPARITY, 8, TWOSTOPBITS);
		}
		app->Global_Sampling_Total = atoi(m_sample_time) / 3;
		UpdateData(TRUE);
		flag = 0;
		CCalibrationDlg *parent = (CCalibrationDlg *)GetParent();

		//	if (sp == 1)
			
		dlgResult = collectdlg.DoModal();
		//			sp = 0;
		//}
	}
	else
	{
		// Create the CEvent object that will be passed to the thread routine
		CEvent* pEvent = new CEvent(FALSE, FALSE);

		// Create a thread that will wait on the event
		//CWinThread* pThread;
		pThread = ::AfxBeginThread(&MyThreadProc, pEvent, 0, 0, CREATE_SUSPENDED, NULL);
		pThread->m_bAutoDelete = FALSE;
		pThread->ResumeThread();

		dwResult = WaitForSingleObject(pThread->m_hThread, 0);
		if (dwResult == WAIT_TIMEOUT)
		{
			printf("The thread is still running...\n");
		}
		else
		{
			printf("The thread is no longer running...\n");
		}


		delete pEvent;

		End_pThread = 0;
		OnStart = 4;
		OnCollect2();
	}
}

void CSetZeroDlg::OnCollect3() 
{
	dlgResult = 0;
	if (OnStart == 4)
	{
		CCalibrationApp *app = (CCalibrationApp *)AfxGetApp();
		//SetEvent(hEventFinish);
		app->flux.Format("min");
		//CMessageBox2Dlg msgb2dlg;
		//int result = msgb2dlg.DoModal();
		//if (result == IDOK)
		//{
			//sp = 0;
			//dwResult = WaitForSingleObject(pThread->m_hThread, 0);

			/*do{
				Sleep(50);
			} while (sp == 0);*/
			if (!app->g_com.IsOpen())
			{
				app->g_com.Open(app->commm, 9600, NOPARITY, 8, TWOSTOPBITS);
			}
			app->Global_Sampling_Total = atoi(m_sample_time) / 3;
			UpdateData(TRUE);
			CCalibrationDlg *parent = (CCalibrationDlg *)GetParent();

			flag = 0;
			//if (sp == 1)
			//{
			
		dlgResult = collectdlg.DoModal();
			//}

		//	sp = 0;
		//}
	}
	else
	{
		// Create the CEvent object that will be passed to the thread routine
		CEvent* pEvent = new CEvent(FALSE, FALSE);

		// Create a thread that will wait on the event
		//CWinThread* pThread;
		pThread = ::AfxBeginThread(&MyThreadProc, pEvent, 0, 0, CREATE_SUSPENDED, NULL);
		pThread->m_bAutoDelete = FALSE;
		pThread->ResumeThread();

		dwResult = WaitForSingleObject(pThread->m_hThread, 0);
		if (dwResult == WAIT_TIMEOUT)
		{
			printf("The thread is still running...\n");
		}
		else
		{
			printf("The thread is no longer running...\n");
		}
		/*Sleep(100);
		dwResult = WaitForSingleObject(pThread->m_hThread, 0);
		if (dwResult == WAIT_TIMEOUT)
		{
			printf("The thread is still running...\n");
		}
		else
		{
			printf("The thread is no longer running...\n");
		}*/

		delete pEvent;

		End_pThread = 0;
		OnStart = 4;
		OnCollect3();
	}
}

void CSetZeroDlg::OnClose() 
{
	//_CrtDumpMemoryLeaks();

	End_pThread = 1;
	CCalibrationApp *app = (CCalibrationApp *)AfxGetApp(); 
	app->p = 0;
	if (!app->g_com.IsOpen())
	{
		app->g_com.Open(app->commm,9600,NOPARITY,8,TWOSTOPBITS);
	}

	SYSTEMTIME st;
	CString strtime;
	GetLocalTime(&st);
	strtime.Format("%04d%02d%02d", st.wYear, st.wMonth, st.wDay);
	CString sql;
	int temp, max = 0;
	sql.Format("SELECT RIGHT(name,3) bh FROM sysobjects WHERE name LIKE \'Data%s%c\'", strtime, '%');
	try
	{
		m_recordset = m_pAppConn->Execute((_bstr_t)sql,NULL,adCmdText);
		if (!m_recordset->adoEOF)
		{
			m_recordset->MoveFirst();
		}
		while(!m_recordset->adoEOF)
		{
			_variant_t var = m_recordset->GetCollect("bh");
			CString bh = (char *)_bstr_t(var);
			sscanf(bh, "%d", &temp);
			if (max < temp)
			{
				max = temp;
			}
			m_recordset->MoveNext();
		}
	}
	catch (_com_error e)
	{
		AfxMessageBox(e.ErrorMessage());
	}
	sql.Format("USE settings SELECT * INTO #temp FROM Data%s%03d ORDER BY netword_IDN, CASE flow WHEN '大' THEN 1 WHEN '中' THEN 2 WHEN '小' THEN 3 END DELETE FROM Data%s%03d INSERT Data%s%03d SELECT * FROM #temp DROP TABLE #temp", strtime, max, strtime, max, strtime, max);
	try
	{
		m_pAppConn->Execute((_bstr_t)sql, NULL, adCmdText);
	}
	catch(_com_error e)
	{
		AfxMessageBox(e.ErrorMessage());
	}

	//kill the thread, when ShowDlg is closed, the window is also closed
	if (OnStart == 4)
	{
		dwResult = WaitForSingleObject(pThread->m_hThread, 0);
		if (dwResult == WAIT_TIMEOUT)
		{
			printf("The thread is still running...\n");
		}
		else
		{
			printf("The thread is no longer running...\n");
		}
		::TerminateThread(pThread->m_hThread, 0);

		showdlg->DestroyWindow();
		delete showdlg;
		showdlg = NULL;
	}
	else
	{
		showdlg->DestroyWindow();
		delete showdlg;
		showdlg = NULL;
	}

	//showdlg->DestroyWindow();
	//showdlg = NULL;
	OnStart = 0;

	//m_pAppConn->Close();
	//m_pAppConn = NULL;

	if (m_recordset)
		if (m_recordset->State == adStateOpen)
			m_recordset->Close();
	if (m_pAppConn)
		if (m_pAppConn->State == adStateOpen)
			m_pAppConn->Close();

	m_pAppConn.Release();
	CDialog::OnClose();
}

void CSetZeroDlg::OnDestroy()
{
	showdlg->DestroyWindow();
	::PostQuitMessage(0);
	CDialog::OnDestroy();
}

void CSetZeroDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	CRect rc;
	GetWindowRect(&rc);

	CCalibrationApp *app = (CCalibrationApp *)AfxGetApp();
	app->g_rc = rc;

	HWND hwnd;
	if (app->language == 0)
	{
		hwnd = ::FindWindow(NULL, _T("显示"));
	}
	else
	{
		hwnd = ::FindWindow(NULL, _T("Show"));
	}
	::SendMessage(hwnd, WM_MYMESSAGE, 0, 0);
	// Do not call CDialog::OnPaint() for painting messages
}

void CSetZeroDlg::OnButtonShow() 
{
	// TODO: Add your control notification handler code here
	CCalibrationApp *app = (CCalibrationApp *)AfxGetApp();

	if (m_flag == 0)
	{
		showdlg->ShowWindow(SW_SHOW);
		HWND hwnd;
		if (app->language == 0)
		{
			hwnd = ::FindWindow(NULL, _T("显示"));
		}
		else
		{
			hwnd = ::FindWindow(NULL, _T("Show"));
		}
		::SendMessage(hwnd, WM_MYMESSAGE, 0, 0);
		GetDlgItem(IDC_BUTTON_SHOW)->SetWindowText("<<");
		m_flag = 1;
		sp = 0;
	}
	else if (m_flag == 1)
	{
		if (!app->g_com.IsOpen())
		{
			app->g_com.Open(app->commm,9600,NOPARITY,8,TWOSTOPBITS);
		}
		GetDlgItem(IDC_BUTTON_SHOW)->SetWindowText(">>");
		showdlg->ShowWindow(SW_HIDE);
		m_flag = 0;

		//sp = 0;
		//do{
		//	Sleep(50);
		//}
		//while(sp == 0);
	}
}

void CSetZeroDlg::OnMove(int x, int y) 
{
	CDialog::OnMove(x, y);
	CRect rc;
	GetWindowRect(&rc);
	//	ClientToScreen(&rc); //把屏幕坐标系下的RECT坐标转换为客户区坐标系下的RECT坐标。
	CCalibrationApp *app = (CCalibrationApp *)AfxGetApp();
	app->g_rc = rc;
	HWND hwnd;
	if (app->language == 0)
	{
		hwnd = ::FindWindow(NULL, _T("显示"));
	}
	else
	{
		hwnd = ::FindWindow(NULL, _T("Show"));
	}
	::SendMessage(hwnd, WM_MYMESSAGE, 0, 0);//向指定窗口中发送消息

	// TODO: Add your message handler code here
	
}

LRESULT CSetZeroDlg::OnMyMessage2(WPARAM wParam, LPARAM lParam)
{
	sp = 0;
	m_flag = 0;
	return 0;	
}

void CSetZeroDlg::OnMax()
{
	//Open Valve for MAX

	STARTUPINFO siStartupInfo;
	PROCESS_INFORMATION piProcessInfo;

	memset(&siStartupInfo, 0, sizeof(siStartupInfo));
	memset(&piProcessInfo, 0, sizeof(piProcessInfo));

	siStartupInfo.cb = sizeof(siStartupInfo);

	//if (CreateProcess("C:\\Program Files (x86)\\Default Company Name\\Qmax\\VC_VoltUpdate.exe", NULL, NULL, NULL, FALSE, CREATE_NO_WINDOW | CREATE_DEFAULT_ERROR_MODE,
		//NULL, NULL, &siStartupInfo, &piProcessInfo) == FALSE)
	//LPCTSTR Max_direct("ValveControl\\VC_Max.exe");
	//if (CreateProcess(Max_direct, NULL, NULL, NULL, FALSE, CREATE_NO_WINDOW | CREATE_DEFAULT_ERROR_MODE,NULL, NULL, &siStartupInfo, &piProcessInfo) == FALSE)
	if(VC_Update::DAQ_Update(v_max_f)==1)//YC Note on Nov 23, 2016: Update DAQ
	{
		// Could not start application
		AfxMessageBox("Can't contact NI DAQ, STOP");
		return;
	}

		// Wait until application has terminated
	WaitForSingleObject(piProcessInfo.hProcess, INFINITE);

	// Close process and thread handlesDialogBox
	::CloseHandle(piProcessInfo.hThread);
	::CloseHandle(piProcessInfo.hProcess);

	m_show = "Valve is open for 100%";
	UpdateData(FALSE);
}

void CSetZeroDlg::OnMid()
{
	//Open Valve for Mid
	STARTUPINFO siStartupInfo;
	PROCESS_INFORMATION piProcessInfo;

	memset(&siStartupInfo, 0, sizeof(siStartupInfo));
	memset(&piProcessInfo, 0, sizeof(piProcessInfo));

	siStartupInfo.cb = sizeof(siStartupInfo);

	//if (CreateProcess("C:\\Program Files (x86)\\Default Company Name\\Qmid\\VC_VoltUpdate.exe", NULL, NULL, NULL, FALSE, CREATE_NO_WINDOW | CREATE_DEFAULT_ERROR_MODE,
		//NULL, NULL, &siStartupInfo, &piProcessInfo) == FALSE)
	//if (CreateProcess("ValveControl\\VC_Mid.exe", NULL, NULL, NULL, FALSE, CREATE_NO_WINDOW | CREATE_DEFAULT_ERROR_MODE,NULL, NULL, &siStartupInfo, &piProcessInfo) == FALSE)
	if (VC_Update::DAQ_Update(v_mid_f) == 1)//YC Note on Nov 23, 2016: Update DAQ
	{
		// Could not start application
		AfxMessageBox("Can't contact NI DAQ, STOP");
		return;
	}

	// Wait until application has terminated
	WaitForSingleObject(piProcessInfo.hProcess, INFINITE);

	// Close process and thread handles
	::CloseHandle(piProcessInfo.hThread);
	::CloseHandle(piProcessInfo.hProcess);

	m_show = "Valve is open for 70%";
	UpdateData(FALSE);
}

void CSetZeroDlg::OnMin()
{
	//Open Valve for Min
	STARTUPINFO siStartupInfo;
	PROCESS_INFORMATION piProcessInfo;

	memset(&siStartupInfo, 0, sizeof(siStartupInfo));
	memset(&piProcessInfo, 0, sizeof(piProcessInfo));

	siStartupInfo.cb = sizeof(siStartupInfo);

	//if (CreateProcess("C:\\Program Files (x86)\\Default Company Name\\Qmin\\VC_VoltUpdate.exe", NULL, NULL, NULL, FALSE, CREATE_NO_WINDOW | CREATE_DEFAULT_ERROR_MODE,
		//NULL, NULL, &siStartupInfo, &piProcessInfo) == FALSE)
	//if (CreateProcess("ValveControl\\VC_Min.exe", NULL, NULL, NULL, FALSE, CREATE_NO_WINDOW | CREATE_DEFAULT_ERROR_MODE,NULL, NULL, &siStartupInfo, &piProcessInfo) == FALSE)
	if (VC_Update::DAQ_Update(v_low_f) == 1)//YC Note on Nov 23, 2016: Update DAQ
	{
		// Could not start application
		AfxMessageBox("Can't contact NI DAQ, STOP");
		return;
	}

	// Wait until application has terminated
	WaitForSingleObject(piProcessInfo.hProcess, INFINITE);

	// Close process and thread handles
	::CloseHandle(piProcessInfo.hThread);
	::CloseHandle(piProcessInfo.hProcess);
	
	m_show = "Valve is open for 30%";
	UpdateData(FALSE);
}

void CSetZeroDlg::OnCloseValve()
{
	//Close Valve for set sero

	STARTUPINFO siStartupInfo;
	PROCESS_INFORMATION piProcessInfo;

	memset(&siStartupInfo, 0, sizeof(siStartupInfo));
	memset(&piProcessInfo, 0, sizeof(piProcessInfo));

	siStartupInfo.cb = sizeof(siStartupInfo);

	//if (CreateProcess("C:\\Program Files (x86)\\Default Company Name\\CloseValve\\VC_VoltUpdate.exe", NULL, NULL, NULL, FALSE, CREATE_NO_WINDOW | CREATE_DEFAULT_ERROR_MODE,
		//NULL, NULL, &siStartupInfo, &piProcessInfo) == FALSE)
	//if (CreateProcess("ValveControl\\VC_CloseValve.exe", NULL, NULL, NULL, FALSE, CREATE_NO_WINDOW | CREATE_DEFAULT_ERROR_MODE,NULL, NULL, &siStartupInfo, &piProcessInfo) == FALSE)
	if (VC_Update::DAQ_Update(10.0f) == 1)//YC Note on Nov 23, 2016: Update DAQ
	{
		// Could not start application
		AfxMessageBox("Can't contact NI DAQ, STOP");
		return;
	}
	// Wait until application has terminated
	WaitForSingleObject(piProcessInfo.hProcess, INFINITE);

	// Close process and thread handles
	::CloseHandle(piProcessInfo.hThread);
	::CloseHandle(piProcessInfo.hProcess);

	m_show = "Valve is closed";
	UpdateData(FALSE);
}

void CSetZeroDlg::OnCalibrate()
{
	AfxMessageBox("You are about to start the calibration process.\n Press OK to continue");
	CCalibrationApp *app = (CCalibrationApp *)AfxGetApp();

	CEdit *m_edit_a;
	m_edit_a = reinterpret_cast<CEdit *>(GetDlgItem(IDC_EDIT_SHOW));

	//m_delay = atoi(m_wait_time);
	//app->Global_Sampling_Total = atoi(m_sample_time) / 3;

	//Automatic set zero
	if (!ManualSetZero) {
		Invalidate();
		//flush
		//OnBnClickedFlush();

		OnCloseValve();
		//Invalidate();
		UpdateWindow();

		Sleep(1000);

		m_edit_a->SetWindowText("Close valve, please wait for "+m_wait_time+" seconds!");
		UpdateWindow();

		//AfxMessageBox("Delay time");
		//wait for valve to be closed;
		Sleep(m_delay * 1000);

		//Set Zero
		m_edit_a->SetWindowText("Set zero start, please wait for 45s");
		UpdateWindow();
		try{
			OnM42_Cal();
		}
		catch (Meter_err err) {
			AfxMessageBox(err.err_msg);
			return;
		}
		//OnM42();

		int tempIndex = 0;

		//Sleep(2000);
		//wait for the count down
		/*do{
			Sleep(1000);
		} while (SetZeroComplete == false);*/

		//save zero
		OnM_2();
		UpdateWindow();

		m_edit_a->SetWindowText("Store Zero!");
		UpdateWindow();

		Sleep(1000);

		tempIndex = m_show.Find("Failure");
		int count = 0;
		//check if set zero were success
		if (tempIndex != -1)
		{
			AfxMessageBox("Calibration Failure! Stop!");
			return;
		}
	}//Jump the set zero part;

	//open valve for 30%
	//AfxMessageBox("open valve for 30%.");
	m_edit_a->SetWindowText("open valve 30%");
	UpdateWindow();

	OnMin();
	UpdateWindow();

	Sleep(1000);

	//AfxMessageBox("2 min.");
	m_edit_a->SetWindowText("Open valve to 30%, please wait for "+m_wait_time+" seconds!");
	UpdateWindow();

	//wait for 3.5 minuts
	Sleep(m_delay * 1000);

	//AfxMessageBox("Qmin.");
	m_edit_a->SetWindowText("Qmin!");
	UpdateWindow();
	//collect Q min
	OnCollect3();

	if (dlgResult == 5)
		return;

	//open valve for 70%
	//AfxMessageBox("open valve for 70%.");
	m_edit_a->SetWindowText("open valve 70%");
	UpdateWindow();

	Sleep(1000);

	OnMid();
	UpdateWindow();

	Sleep(1000);

	//AfxMessageBox("2 min.");
	m_edit_a->SetWindowText("Open valve to 70%, please wait for "+ m_wait_time+" seconds!");
	UpdateWindow();
	//wait for 3.5 minuts
	Sleep(m_delay * 1000);

	//AfxMessageBox("Qmid.");
	m_edit_a->SetWindowText("Qmid!");
	UpdateWindow();
	Sleep(1000);
	//collect Q mid
	OnCollect2();

	if (dlgResult == 5)
		return;

	//open valve for 100%
	//AfxMessageBox("open valve 100%.");
	m_edit_a->SetWindowText("open valve 100%");
	UpdateWindow();

	OnMax();
	UpdateWindow();

	Sleep(1000);

	//AfxMessageBox("4 min.");
	m_edit_a->SetWindowText("Open valve to 100%, please wait for "+ m_wait_time+" seconds!");
	UpdateWindow();
	//wait for 3.5 minuts
	Sleep(m_delay * 1000);

	//AfxMessageBox("Qmax");
	m_edit_a->SetWindowText("Qmax!");
	UpdateWindow();
	//collect Q max
	OnCollect();

	if (dlgResult == 5)
		return;

	Sleep(1000);

	AfxMessageBox("Data collect finished!");
	m_show = "Data collect finished!";
	UpdateData(FALSE);
}


void CSetZeroDlg::OnCalibrate_2() {
	ManualSetZero = true;
	OnCalibrate();
}

void CSetZeroDlg::OnBnClickedFlush()
{
	// TODO: Add your control notification handler code here
	AfxMessageBox("You are about to start Flushing process. This may take 3 minutes. Please press Ok to continue.");

	Invalidate();
	UpdateWindow();

	Sleep(1000);

	CEdit *m_edit_a;
	m_edit_a = reinterpret_cast<CEdit *>(GetDlgItem(IDC_EDIT_SHOW));
	m_edit_a->SetWindowText("Please wait 3.5 minutes!");
	UpdateWindow();

	//open valve for 100%
	//AfxMessageBox("open valve 100%.");
	m_edit_a->SetWindowText("Now flushing(open valve 100%)");
	UpdateWindow();

	OnMax();
	UpdateWindow();

	//wait for 3.5 minuts
	Sleep(210000);
	m_edit_a->SetWindowText("flushing finished!");
}
