// LineArray.cpp : implementation file
//

#include "stdafx.h"
#include "Calibration.h"
#include "LineArrayDlg.h"
#include "SetDlg.h"
#include "CalibrationDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLineArrayDlg dialog


CLineArrayDlg::CLineArrayDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLineArrayDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLineArrayDlg)
	m_011 = _T("");
	m_012 = _T("");
	m_021 = _T("");
	m_022 = _T("");
	m_032 = _T("");
	m_031 = _T("");
	m_041 = _T("");
	m_042 = _T("");
	m_051 = _T("");
	m_052 = _T("");
	m_061 = _T("");
	m_062 = _T("");
	m_071 = _T("");
	m_072 = _T("");
	m_081 = _T("");
	m_082 = _T("");
	m_091 = _T("");
	m_092 = _T("");
	m_101 = _T("");
	m_102 = _T("");
	m_111 = _T("");
	m_112 = _T("");
	m_121 = _T("");
	m_122 = _T("");
	//}}AFX_DATA_INIT
}


void CLineArrayDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLineArrayDlg)
	DDX_Text(pDX, IDC_EDIT_01_1, m_011);
	DDX_Text(pDX, IDC_EDIT_01_2, m_012);
	DDX_Text(pDX, IDC_EDIT_02_1, m_021);
	DDX_Text(pDX, IDC_EDIT_02_2, m_022);
	DDX_Text(pDX, IDC_EDIT_03_2, m_032);
	DDX_Text(pDX, IDC_EDIT_03_1, m_031);
	DDX_Text(pDX, IDC_EDIT_04_1, m_041);
	DDX_Text(pDX, IDC_EDIT_04_2, m_042);
	DDX_Text(pDX, IDC_EDIT_05_1, m_051);
	DDX_Text(pDX, IDC_EDIT_05_2, m_052);
	DDX_Text(pDX, IDC_EDIT_06_1, m_061);
	DDX_Text(pDX, IDC_EDIT_06_2, m_062);
	DDX_Text(pDX, IDC_EDIT_07_1, m_071);
	DDX_Text(pDX, IDC_EDIT_07_2, m_072);
	DDX_Text(pDX, IDC_EDIT_08_1, m_081);
	DDX_Text(pDX, IDC_EDIT_08_2, m_082);
	DDX_Text(pDX, IDC_EDIT_09_1, m_091);
	DDX_Text(pDX, IDC_EDIT_09_2, m_092);
	DDX_Text(pDX, IDC_EDIT_10_1, m_101);
	DDX_Text(pDX, IDC_EDIT_10_2, m_102);
	DDX_Text(pDX, IDC_EDIT_11_1, m_111);
	DDX_Text(pDX, IDC_EDIT_11_2, m_112);
	DDX_Text(pDX, IDC_EDIT_12_1, m_121);
	DDX_Text(pDX, IDC_EDIT_12_2, m_122);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLineArrayDlg, CDialog)
	//{{AFX_MSG_MAP(CLineArrayDlg)
	ON_BN_CLICKED(IDC_DATA_NUM, OnDataNum)
	ON_BN_CLICKED(IDC_BUTTON_SET, OnButtonSet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLineArrayDlg message handlers

void CLineArrayDlg::OnDataNum() 
{
	// TODO: Add your control notification handler code here
	
	CSetDlg *parent = (CSetDlg *)GetParent();
	CCalibrationApp *app = (CCalibrationApp *)AfxGetApp();
	//获取表号
	CString s;
	int iPos = ((CComboBox *)parent->GetDlgItem(IDC_COMBO_METER))->GetCurSel();
	((CComboBox *)parent->GetDlgItem(IDC_COMBO_METER))->GetLBText(iPos, s);
	s.Delete(0, 10);
	int len = s.GetLength();
	int i;
	
	//W前缀
	CString str1 = "\x57";

	for (i=0; i<len; i++)
	{
		switch(s.GetAt(i))
		{
		case '0':
			str1 += "\x30";
			break;
		case '1':
			str1 += "\x31";
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
	
	//命令
	char menu[6] = { '\x4d', '\x45', '\x4e', '\x55', '\x34', '\x38' };
	CString str2 = "";
	for (i=0; i<6; i++)
	{
		str2 += menu[i];
	}
	str2 += "\x26\x4d\x3d"; 
	str2 += "\x26\x4d\x31";
	str2 += "\x26\x4d\x31";
	str2 += "\x26\x4d\x31";
	str2 += "\x26\x4d\x31";
	str2 += "\x26\x4d\x3d";
	str2 += "\x26\x4d\x3d";

	int iPos2 = ((CComboBox *)GetDlgItem(IDC_COMBO_DATA_NUM))->GetCurSel();
	if (iPos2 >= 0 && iPos2 < 9)
	{
		//str2 += "\x26\x4d\((iPos2+1)+'0')";
		str2 += "\x26\x4d";
		CString temp;
		temp.Format("%d", (iPos2 + 1));
		temp += '0';
		str2 += temp;
	}
	else if (iPos2 == 9)
	{
		str2 += "\x26\x4d\x31";
		str2 += "\x26\x4d\x30";
	}
	else if (iPos2 == 10)
	{
		str2 += "\x26\x4d\x31";
		str2 += "\x26\x4d\x31";
	}
	else if (iPos2 == 11)
	{
		str2 += "\x26\x4d\x31";
		str2 += "\x26\x4d\x32";
	}
	str2 += "\x26\x4d\x3d\x0d";

	str = str1 + str2;
	app->g_com.Write(str);
	str = "";
}

int __stdcall SetChildFont(struct HWND__ *,long);
extern CFont *g_Font;
BOOL CLineArrayDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CCalibrationApp *app = (CCalibrationApp *)AfxGetApp();
	if (app->language == 0)
	{
		this->SetWindowText("流量修正折线数组");
		GetDlgItem(IDC_DATA_NUM)->SetWindowText("修正折线数据点数");
		GetDlgItem(IDC_STATIC_01)->SetWindowText("第01修正点数据");
		GetDlgItem(IDC_STATIC_02)->SetWindowText("第02修正点数据");
		GetDlgItem(IDC_STATIC_03)->SetWindowText("第03修正点数据");
		GetDlgItem(IDC_STATIC_04)->SetWindowText("第04修正点数据");
		GetDlgItem(IDC_STATIC_05)->SetWindowText("第05修正点数据");
		GetDlgItem(IDC_STATIC_06)->SetWindowText("第06修正点数据");
		GetDlgItem(IDC_STATIC_07)->SetWindowText("第07修正点数据");
		GetDlgItem(IDC_STATIC_08)->SetWindowText("第08修正点数据");
		GetDlgItem(IDC_STATIC_09)->SetWindowText("第09修正点数据");
		GetDlgItem(IDC_STATIC_10)->SetWindowText("第10修正点数据");
		GetDlgItem(IDC_STATIC_11)->SetWindowText("第11修正点数据");
		GetDlgItem(IDC_STATIC_12)->SetWindowText("第12修正点数据");
		GetDlgItem(IDC_BUTTON_SET)->SetWindowText("设置");
		g_Font = new CFont;       
		g_Font->CreatePointFont(90, "宋体");
		::EnumChildWindows(m_hWnd, ::SetChildFont, (LPARAM)g_Font);
	}
	else
	{
		this->SetWindowText("Calib. Data");
		GetDlgItem(IDC_DATA_NUM)->SetWindowText("Calib. Data No.");
		GetDlgItem(IDC_STATIC_01)->SetWindowText("No.01 Calib. Data");
		GetDlgItem(IDC_STATIC_02)->SetWindowText("No.02 Calib. Data");
		GetDlgItem(IDC_STATIC_03)->SetWindowText("No.03 Calib. Data");
		GetDlgItem(IDC_STATIC_04)->SetWindowText("No.04 Calib. Data");
		GetDlgItem(IDC_STATIC_05)->SetWindowText("No.05 Calib. Data");
		GetDlgItem(IDC_STATIC_06)->SetWindowText("No.06 Calib. Data");
		GetDlgItem(IDC_STATIC_07)->SetWindowText("No.07 Calib. Data");
		GetDlgItem(IDC_STATIC_08)->SetWindowText("No.08 Calib. Data");
		GetDlgItem(IDC_STATIC_09)->SetWindowText("No.09 Calib. Data");
		GetDlgItem(IDC_STATIC_10)->SetWindowText("No.10 Calib. Data");
		GetDlgItem(IDC_STATIC_11)->SetWindowText("No.11 Calib. Data");
		GetDlgItem(IDC_STATIC_12)->SetWindowText("No.12 Calib. Data");
		GetDlgItem(IDC_BUTTON_SET)->SetWindowText("Setup");
		g_Font = new CFont;       
		g_Font->CreatePointFont(90, "Times New Roman");
		::EnumChildWindows(m_hWnd, ::SetChildFont, (LPARAM)g_Font); 
	}
	((CComboBox *)GetDlgItem(IDC_COMBO_DATA_NUM))->SetCurSel(0);

	CSetDlg *parent = (CSetDlg *)GetParent();
	//获取表号
	CString s;
	int iPos = ((CComboBox *)parent->GetDlgItem(IDC_COMBO_METER))->GetCurSel();
	((CComboBox *)parent->GetDlgItem(IDC_COMBO_METER))->GetLBText(iPos, s);
	s.Delete(0, 10);
	int len = s.GetLength();
	int i;
	
	//W前缀
	//str1 = CString(0x57);
	CString temp1;
	temp1.Format("%d", 0x57);
	str1 = temp1;

	for (i=0; i<len; i++)
	{
		switch(s.GetAt(i))
		{
		case '0':
			str1 += "\x30";
			break;
		case '1':
			str1 += "\x31";
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
	//命令
	char menu[6] = { '\x4d', '\x45', '\x4e', '\x55', '\x34', '\x38' };
	CString str2 = "";
	for (i=0; i<6; i++)
	{
		str2 += menu[i];
	}
	str2 += "\x26\x4d\x3d"; 
	str2 += "\x26\x4d\x31";
	str2 += "\x26\x4d\x31";
	str2 += "\x26\x4d\x31";
	str2 += "\x26\x4d\x31";
	str2 += "\x26\x4d\x3d";
	str2 += "\x26\x4d\x3f";
	str2 += "\x26\x4c\x43\x44\x0d";

	str = str1 + str2;
	app->g_com.Write(str);
	str = "";
	str2 = "";

	char buf[56] = {0};
	app->g_com.Read(buf, 56);
	char *p = buf;
	while (*p != '\0')
	{
		if (*p == 'M' && *(p+1) == '4' && *(p+2) == '8' || *p == 'a' && *(p+1) == 't' && *(p+2) == 'a')
		{
			p += 3;
			break;
		}
		p++;
	}
	char res1[10] = {0};
	char res2[10] = {0};
	int m = 0,n = 0;
	while (*p != '\0')
	{
		if(*p == ':')
		{
			break;
		}
		if(*p <= '9' && *p >= '0' || *p == '.')
		{
			res1[m++] = *p;
		}
		p++;
	}
	res1[m] = '\0';
	while (*p != '\0')
	{
		if (*p == '\n')
		{
			break;
		}
		if(*p <= '9' && *p >= '0' || *p == '.')
		{
			res2[n++] = *p;
		}
		p++;
	}
	res2[n] = '\0';
	m_011.Format("%s", res1);
	m_012.Format("%s", res2);
	UpdateData(FALSE);
	Sleep(200);

	//命令
	for (i=0; i<6; i++)
	{
		str2 += menu[i];
	}

	str2 += "\x26\x4d\x3d";
	str2 += "\x26\x4d\x31";
	str2 += "\x26\x4d\x31";
	str2 += "\x26\x4d\x31";
	str2 += "\x26\x4d\x31";
	str2 += "\x26\x4d\x3d";
	str2 += "\x26\x4d\x3f";
	str2 += "\x26\x4d\x3f";
	str2 += "\x26\x4c\x43\x44\x0d";


	str = str1 + str2;
	app->g_com.Write(str);
	str = "";
	str2 = "";

	app->g_com.Read(buf, 56);
	p = buf;
	while (*p != '\0')
	{
		if (*p == 'M' && *(p+1) == '4' && *(p+2) == '8' || *p == 'a' && *(p+1) == 't' && *(p+2) == 'a')
		{
			p += 3;
			break;
		}
		p++;
	}
	m = 0,n = 0;
	while (*p != '\0')
	{
		if(*p == ':')
		{
			break;
		}
		if(*p <= '9' && *p >= '0' || *p == '.')
		{
			res1[m++] = *p;
		}
		p++;
	}
	res1[m] = '\0';
	while (*p != '\0')
	{
		if (*p == '\n')
		{
			break;
		}
		if(*p <= '9' && *p >= '0' || *p == '.')
		{
			res2[n++] = *p;
		}
		p++;
	}
	res2[n] = '\0';
	m_021.Format("%s", res1);
	m_022.Format("%s", res2);
	UpdateData(FALSE);
	Sleep(200);

	//命令
	for (i=0; i<6; i++)
	{
		str2 += menu[i];
	}

	str2 += "\x26\x4d\x3d";
	str2 += "\x26\x4d\x31";
	str2 += "\x26\x4d\x31";
	str2 += "\x26\x4d\x31";
	str2 += "\x26\x4d\x31";
	str2 += "\x26\x4d\x3d";
	str2 += "\x26\x4d\x3f";
	str2 += "\x26\x4d\x3f";
	str2 += "\x26\x4d\x3f";
	str2 += "\x26\x4c\x43\x44\x0d";

	

	str = str1 + str2;
	app->g_com.Write(str);
	str = "";
	str2 = "";
	
	app->g_com.Read(buf, 56);
	p = buf;
	while (*p != '\0')
	{
		if (*p == 'M' && *(p+1) == '4' && *(p+2) == '8' || *p == 'a' && *(p+1) == 't' && *(p+2) == 'a')
		{
			p += 3;
			break;
		}
		p++;
	}
	m = 0,n = 0;
	while (*p != '\0')
	{
		if(*p == ':')
		{
			break;
		}
		if(*p <= '9' && *p >= '0' || *p == '.')
		{
			res1[m++] = *p;
		}
		p++;
	}
	res1[m] = '\0';
	while (*p != '\0')
	{
		if (*p == '\n')
		{
			break;
		}
		if(*p <= '9' && *p >= '0' || *p == '.')
		{
			res2[n++] = *p;
		}
		p++;
	}
	res2[n] = '\0';
	m_031.Format("%s", res1);
	m_032.Format("%s", res2);
	UpdateData(FALSE);
	Sleep(200);

	//命令
	for (i=0; i<6; i++)
	{
		//str2 += CString(menu[i]);
		CString temp1;
		temp1.Format("%d", menu[i]);
		str2 += temp1;
	}

	str2 += "\x26\x4d\x3d";
	str2 += "\x26\x4d\x31";
	str2 += "\x26\x4d\x31";
	str2 += "\x26\x4d\x31";
	str2 += "\x26\x4d\x31";
	str2 += "\x26\x4d\x3d";
	str2 += "\x26\x4d\x3f";
	str2 += "\x26\x4d\x3f";
	str2 += "\x26\x4d\x3f";
	str2 += "\x26\x4d\x3f";
	str2 += "\x26\x4c\x43\x44\x0d";

	str = str1 + str2;
	app->g_com.Write(str);
	str = "";
	str2 = "";
	
	app->g_com.Read(buf, 56);
	p = buf;
	while (*p != '\0')
	{
		if (*p == 'M' && *(p+1) == '4' && *(p+2) == '8' || *p == 'a' && *(p+1) == 't' && *(p+2) == 'a')
		{
			p += 3;
			break;
		}
		p++;
	}
	m = 0,n = 0;
	while (*p != '\0')
	{
		if(*p == ':')
		{
			break;
		}
		if(*p <= '9' && *p >= '0' || *p == '.')
		{
			res1[m++] = *p;
		}
		p++;
	}
	res1[m] = '\0';
	while (*p != '\0')
	{
		if (*p == '\n')
		{
			break;
		}
		if(*p <= '9' && *p >= '0' || *p == '.')
		{
			res2[n++] = *p;
		}
		p++;
	}
	res2[n] = '\0';
	m_041.Format("%s", res1);
	m_042.Format("%s", res2);
	UpdateData(FALSE);
	Sleep(200);

	//命令
	for (i=0; i<6; i++)
	{
		str2 += menu[i];
	}

	str2 += "\x26\x4d\x3d";
	str2 += "\x26\x4d\x31";
	str2 += "\x26\x4d\x31";
	str2 += "\x26\x4d\x31";
	str2 += "\x26\x4d\x31";
	str2 += "\x26\x4d\x3d";
	str2 += "\x26\x4d\x3f";
	str2 += "\x26\x4d\x3f";
	str2 += "\x26\x4d\x3f";
	str2 += "\x26\x4d\x3f";
	str2 += "\x26\x4d\x3f";
	str2 += "\x26\x4c\x43\x44\x0d";

	str = str1 + str2;
	app->g_com.Write(str);
	str = "";
	str2 = "";
	
	app->g_com.Read(buf, 56);
	p = buf;
	while (*p != '\0')
	{
		if (*p == 'M' && *(p+1) == '4' && *(p+2) == '8' || *p == 'a' && *(p+1) == 't' && *(p+2) == 'a')
		{
			p += 3;
			break;
		}
		p++;
	}
	m = 0,n = 0;
	while (*p != '\0')
	{
		if(*p == ':')
		{
			break;
		}
		if(*p <= '9' && *p >= '0' || *p == '.')
		{
			res1[m++] = *p;
		}
		p++;
	}
	res1[m] = '\0';
	while (*p != '\0')
	{
		if (*p == '\n')
		{
			break;
		}
		if(*p <= '9' && *p >= '0' || *p == '.')
		{
			res2[n++] = *p;
		}
		p++;
	}
	res2[n] = '\0';
	m_051.Format("%s", res1);
	m_052.Format("%s", res2);
	UpdateData(FALSE);
	Sleep(200);

	//命令
	for (i=0; i<6; i++)
	{
		str2 += menu[i];
	}

	str2 += "\x26\x4d\x3d";
	str2 += "\x26\x4d\x31";
	str2 += "\x26\x4d\x31";
	str2 += "\x26\x4d\x31";
	str2 += "\x26\x4d\x31";
	str2 += "\x26\x4d\x3d";
	str2 += "\x26\x4d\x3f";
	str2 += "\x26\x4d\x3f";
	str2 += "\x26\x4d\x3f";
	str2 += "\x26\x4d\x3f";
	str2 += "\x26\x4d\x3f";
	str2 += "\x26\x4d\x3f";
	str2 += "\x26\x4c\x43\x44\x0d";

	str = str1 + str2;
	app->g_com.Write(str);
	str = "";
	str2 = "";
	
	app->g_com.Read(buf, 56);
	p = buf;
	while (*p != '\0')
	{
		if (*p == 'M' && *(p+1) == '4' && *(p+2) == '8' || *p == 'a' && *(p+1) == 't' && *(p+2) == 'a')
		{
			p += 3;
			break;
		}
		p++;
	}
	m = 0,n = 0;
	while (*p != '\0')
	{
		if(*p == ':')
		{
			break;
		}
		if(*p <= '9' && *p >= '0' || *p == '.')
		{
			res1[m++] = *p;
		}
		p++;
	}
	res1[m] = '\0';
	while (*p != '\0')
	{
		if (*p == '\n')
		{
			break;
		}
		if(*p <= '9' && *p >= '0' || *p == '.')
		{
			res2[n++] = *p;
		}
		p++;
	}
	res2[n] = '\0';
	m_061.Format("%s", res1);
	m_062.Format("%s", res2);
	UpdateData(FALSE);
	Sleep(200);

	//命令
	for (i=0; i<6; i++)
	{
		str2 += menu[i];
	}

	str2 += "\x26\x4d\x3d";
	str2 += "\x26\x4d\x31";
	str2 += "\x26\x4d\x31";
	str2 += "\x26\x4d\x31";
	str2 += "\x26\x4d\x31";
	str2 += "\x26\x4d\x3d";
	str2 += "\x26\x4d\x3f";
	str2 += "\x26\x4d\x3f";
	str2 += "\x26\x4d\x3f";
	str2 += "\x26\x4d\x3f";
	str2 += "\x26\x4d\x3f";
	str2 += "\x26\x4d\x3f";
	str2 += "\x26\x4d\x3f";
	str2 += "\x26\x4c\x43\x44\x0d";

	str = str1 + str2;
	app->g_com.Write(str);
	str = "";
	str2 = "";
	
	app->g_com.Read(buf, 56);
	p = buf;
	while (*p != '\0')
	{
		if (*p == 'M' && *(p+1) == '4' && *(p+2) == '8' || *p == 'a' && *(p+1) == 't' && *(p+2) == 'a')
		{
			p += 3;
			break;
		}
		p++;
	}
	m = 0,n = 0;
	while (*p != '\0')
	{
		if(*p == ':')
		{
			break;
		}
		if(*p <= '9' && *p >= '0' || *p == '.')
		{
			res1[m++] = *p;
		}
		p++;
	}
	res1[m] = '\0';
	while (*p != '\0')
	{
		if (*p == '\n')
		{
			break;
		}
		if(*p <= '9' && *p >= '0' || *p == '.')
		{
			res2[n++] = *p;
		}
		p++;
	}
	res2[n] = '\0';
	m_071.Format("%s", res1);
	m_072.Format("%s", res2);
	UpdateData(FALSE);
	Sleep(200);

	//命令
	for (i=0; i<6; i++)
	{
		str2 += menu[i];
	}

	str2 += "\x26\x4d\x3d";
	str2 += "\x26\x4d\x31";
	str2 += "\x26\x4d\x31";
	str2 += "\x26\x4d\x31";
	str2 += "\x26\x4d\x31";
	str2 += "\x26\x4d\x3d";
	str2 += "\x26\x4d\x3f";
	str2 += "\x26\x4d\x3f";
	str2 += "\x26\x4d\x3f";
	str2 += "\x26\x4d\x3f";
	str2 += "\x26\x4d\x3f";
	str2 += "\x26\x4d\x3f";
	str2 += "\x26\x4d\x3f";
	str2 += "\x26\x4d\x3f";
	str2 += "\x26\x4c\x43\x44\x0d";

	str = str1 + str2;
	app->g_com.Write(str);
	str = "";
	str2 = "";
	
	app->g_com.Read(buf, 56);
	p = buf;
	while (*p != '\0')
	{
		if (*p == 'M' && *(p+1) == '4' && *(p+2) == '8' || *p == 'a' && *(p+1) == 't' && *(p+2) == 'a')
		{
			p += 3;
			break;
		}
		p++;
	}
	m = 0,n = 0;
	while (*p != '\0')
	{
		if(*p == ':')
		{
			break;
		}
		if(*p <= '9' && *p >= '0' || *p == '.')
		{
			res1[m++] = *p;
		}
		p++;
	}
	res1[m] = '\0';
	while (*p != '\0')
	{
		if (*p == '\n')
		{
			break;
		}
		if(*p <= '9' && *p >= '0' || *p == '.')
		{
			res2[n++] = *p;
		}
		p++;
	}
	res2[n] = '\0';
	m_081.Format("%s", res1);
	m_082.Format("%s", res2);
	UpdateData(FALSE);
	Sleep(200);

	//命令
	for (i=0; i<6; i++)
	{
		str2 += menu[i];
	}

	str2 += "\x26\x4d\x3d";
	str2 += "\x26\x4d\x31";
	str2 += "\x26\x4d\x31";
	str2 += "\x26\x4d\x31";
	str2 += "\x26\x4d\x31";
	str2 += "\x26\x4d\x3d";
	str2 += "\x26\x4d\x3f";
	str2 += "\x26\x4d\x3f";
	str2 += "\x26\x4d\x3f";
	str2 += "\x26\x4d\x3f";
	str2 += "\x26\x4d\x3f";
	str2 += "\x26\x4d\x3f";
	str2 += "\x26\x4d\x3f";
	str2 += "\x26\x4d\x3f";
	str2 += "\x26\x4d\x3f";
	str2 += "\x26\x4c\x43\x44\x0d";

	str = str1 + str2;
	app->g_com.Write(str);
	str = "";
	str2 = "";
	
	app->g_com.Read(buf, 56);
	p = buf;
	while (*p != '\0')
	{
		if (*p == 'M' && *(p+1) == '4' && *(p+2) == '8' || *p == 'a' && *(p+1) == 't' && *(p+2) == 'a')
		{
			p += 3;
			break;
		}
		p++;
	}
	m = 0,n = 0;
	while (*p != '\0')
	{
		if(*p == ':')
		{
			break;
		}
		if(*p <= '9' && *p >= '0' || *p == '.')
		{
			res1[m++] = *p;
		}
		p++;
	}
	res1[m] = '\0';
	while (*p != '\0')
	{
		if (*p == '\n')
		{
			break;
		}
		if(*p <= '9' && *p >= '0' || *p == '.')
		{
			res2[n++] = *p;
		}
		p++;
	}
	res2[n] = '\0';
	m_091.Format("%s", res1);
	m_092.Format("%s", res2);
	UpdateData(FALSE);
	Sleep(200);

	//命令
	for (i=0; i<6; i++)
	{
		//str2 += CString(menu[i]);
		CString temp1;
		temp1.Format("%d", menu[i]);
		str2 += temp1;
	}

	str2 += "\x26\x4d\x3d";
	str2 += "\x26\x4d\x31";
	str2 += "\x26\x4d\x31";
	str2 += "\x26\x4d\x31";
	str2 += "\x26\x4d\x31";
	str2 += "\x26\x4d\x3d";
	str2 += "\x26\x4d\x3f";
	str2 += "\x26\x4d\x3f";
	str2 += "\x26\x4d\x3f";
	str2 += "\x26\x4d\x3f";
	str2 += "\x26\x4d\x3f";
	str2 += "\x26\x4d\x3f";
	str2 += "\x26\x4d\x3f";
	str2 += "\x26\x4d\x3f";
	str2 += "\x26\x4d\x3f";
	str2 += "\x26\x4d\x3f";
	str2 += "\x26\x4c\x43\x44\x0d";

	str = str1 + str2;
	app->g_com.Write(str);
	str = "";
	str2 = "";
	
	app->g_com.Read(buf, 56);
	p = buf;
	while (*p != '\0')
	{
		if (*p == 'M' && *(p+1) == '4' && *(p+2) == '8' || *p == 'a' && *(p+1) == 't' && *(p+2) == 'a')
		{
			p += 3;
			break;
		}
		p++;
	}
	m = 0,n = 0;
	while (*p != '\0')
	{
		if(*p == ':')
		{
			break;
		}
		if(*p <= '9' && *p >= '0' || *p == '.')
		{
			res1[m++] = *p;
		}
		p++;
	}
	res1[m] = '\0';
	while (*p != '\0')
	{
		if (*p == '\n')
		{
			break;
		}
		if(*p <= '9' && *p >= '0' || *p == '.')
		{
			res2[n++] = *p;
		}
		p++;
	}
	res2[n] = '\0';
	m_101.Format("%s", res1);
	m_102.Format("%s", res2);
	UpdateData(FALSE);
	Sleep(200);

	//命令
	for (i=0; i<6; i++)
	{
		str2 += menu[i];
	}

	str2 += "\x26\x4d\x3d";
	str2 += "\x26\x4d\x31";
	str2 += "\x26\x4d\x31";
	str2 += "\x26\x4d\x31";
	str2 += "\x26\x4d\x31";
	str2 += "\x26\x4d\x3d";
	str2 += "\x26\x4d\x3f";
	str2 += "\x26\x4d\x3f";
	str2 += "\x26\x4d\x3f";
	str2 += "\x26\x4d\x3f";
	str2 += "\x26\x4d\x3f";
	str2 += "\x26\x4d\x3f";
	str2 += "\x26\x4d\x3f";
	str2 += "\x26\x4d\x3f";
	str2 += "\x26\x4d\x3f";
	str2 += "\x26\x4d\x3f";
	str2 += "\x26\x4d\x3f";
	str2 += "\x26\x4c\x43\x44\x0d";

	str = str1 + str2;
	app->g_com.Write(str);
	str = "";
	str2 = "";
	
	app->g_com.Read(buf, 56);
	p = buf;
	while (*p != '\0')
	{
		if (*p == 'M' && *(p+1) == '4' && *(p+2) == '8' || *p == 'a' && *(p+1) == 't' && *(p+2) == 'a')
		{
			p += 3;
			break;
		}
		p++;
	}
	m = 0,n = 0;
	while (*p != '\0')
	{
		if(*p == ':')
		{
			break;
		}
		if(*p <= '9' && *p >= '0' || *p == '.')
		{
			res1[m++] = *p;
		}
		p++;
	}
	res1[m] = '\0';
	while (*p != '\0')
	{
		if (*p == '\n')
		{
			break;
		}
		if(*p <= '9' && *p >= '0' || *p == '.')
		{
			res2[n++] = *p;
		}
		p++;
	}
	res2[n] = '\0';
	m_111.Format("%s", res1);
	m_112.Format("%s", res2);
	UpdateData(FALSE);
	Sleep(200);

	//命令
	for (i=0; i<7; i++)
	{
		str2 += menu[i];

	}

	str2 += "\x26\x4d\x3d";
	str2 += "\x26\x4d\x31";
	str2 += "\x26\x4d\x31";
	str2 += "\x26\x4d\x31";
	str2 += "\x26\x4d\x31";
	str2 += "\x26\x4d\x3d";
	str2 += "\x26\x4d\x3f";
	str2 += "\x26\x4d\x3f";
	str2 += "\x26\x4d\x3f";
	str2 += "\x26\x4d\x3f";
	str2 += "\x26\x4d\x3f";
	str2 += "\x26\x4d\x3f";
	str2 += "\x26\x4d\x3f";
	str2 += "\x26\x4d\x3f";
	str2 += "\x26\x4d\x3f";
	str2 += "\x26\x4d\x3f";
	str2 += "\x26\x4d\x3f";
	str2 += "\x26\x4d\x3f";
	str2 += "\x26\x4c\x43\x44\x0d";

	str = str1 + str2;
	app->g_com.Write(str);
	str = "";
	str2 = "";
	
	app->g_com.Read(buf, 56);
	p = buf;
	while (*p != '\0')
	{
		if (*p == 'M' && *(p+1) == '4' && *(p+2) == '8' || *p == 'a' && *(p+1) == 't' && *(p+2) == 'a')
		{
			p += 3;
			break;
		}
		p++;
	}
	m = 0,n = 0;
	while (*p != '\0')
	{
		if(*p == ':')
		{
			break;
		}
		if(*p <= '9' && *p >= '0' || *p == '.')
		{
			res1[m++] = *p;
		}
		p++;
	}
	res1[m] = '\0';
	while (*p != '\0')
	{
		if (*p == '\n')
		{
			break;
		}
		if(*p <= '9' && *p >= '0' || *p == '.')
		{
			res2[n++] = *p;
		}
		p++;
	}
	res2[n] = '\0';
	m_121.Format("%s", res1);
	m_122.Format("%s", res2);
	UpdateData(FALSE);
	Sleep(200);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CLineArrayDlg::OnButtonSet() 
{
	// TODO: Add your control notification handler code here
	CSetDlg *parent = (CSetDlg *)GetParent();
	CCalibrationDlg *parent2 = (CCalibrationDlg *)parent->GetParent();
	//获取表号
	CString s;
	int iPos = ((CComboBox *)parent->GetDlgItem(IDC_COMBO_METER))->GetCurSel();
	((CComboBox *)parent->GetDlgItem(IDC_COMBO_METER))->GetLBText(iPos, s);
	s.Delete(0, 10);
	int len = s.GetLength();
	int i;
	
	//W前缀
	str1 = "\x57";

	for (i=0; i<len; i++)
	{
		switch(s.GetAt(i))
		{
		case '0':
			str1 += "\x30";
			break;
		case '1':
			str1 += "\x31";
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
	OnSet01();
	Sleep(200);
	OnSet02();
	Sleep(200);
	OnSet03();
	Sleep(200);
	OnSet04();
	Sleep(200);
	OnSet05();
	Sleep(200);
	OnSet06();
	Sleep(200);
	OnSet07();
	Sleep(200);
	OnSet08();
	Sleep(200);
	OnSet09();
	Sleep(200);
	OnSet10();
	Sleep(200);
	OnSet11();
	Sleep(200);
	OnSet12();
}
void CLineArrayDlg::OnSet01()
{	
	//命令
	char menu[6] = {'\x4d', '\x45', '\x4e', '\x55', '\x34', '\x38'};
	CString str2 = "";
	int i;
	CSetDlg *parent = (CSetDlg *)GetParent();
	CCalibrationApp *app = (CCalibrationApp *)AfxGetApp();
	for (i=0; i<6; i++)
	{
		str2 += menu[i];
	}

	str2 += "\x26\x4d\x3d";
	str2 += "\x26\x4d\x31";
	str2 += "\x26\x4d\x31";
	str2 += "\x26\x4d\x31";
	str2 += "\x26\x4d\x31";
	str2 += "\x26\x4d\x3d";
	str2 += "\x26\x4d\x3f";
	str2 += "\x26\x4c\x43\x44\x0d";

	UpdateData(TRUE);
	if (m_011 != "")
	{	
		for (i=0; i<m_011.GetLength(); i++)
		{
			switch(m_011.GetAt(i))
			{
			case '0':
				str2 += "\x26\x4d\x30";
				break;
			case '1':
				str2 += "\x26\x4d\x31";
				break;
			case '2':
				str2 += "\x26\x4d\x32";
				break;
			case '3':
				str2 += "\x26\x4d\x33";
				break;
			case '4':
				str2 += "\x26\x4d\x34";
				break;
			case '5':
				str2 += "\x26\x4d\x35";
				break;
			case '6':
				str2 += "\x26\x4d\x36";
				break;
			case '7':
				str2 += "\x26\x4d\x37";
				break;
			case '8':
				str2 +="\x26\x4d\x38";
				break;
			case '9':
				str2 +="\x26\x4d\x39";
				break;
			case '.':
				str2 += "\x26\x4d\x3a";
				break;
			default:
				if (app->language == 0)
				{
					AfxMessageBox("您的输入有误!");
				}
				else
				{
					AfxMessageBox("Your input is incorrect!");
				}
			}
		}
		str2 += "\x26\x4d\x3d";

	}
	if (m_012 != "")
	{	
		for (i=0; i<m_012.GetLength(); i++)
		{
			switch(m_012.GetAt(i))
			{
			case '0':
				str2 += "\x26\x4d\x30";
				break;
			case '1':
				str2 += "\x26\x4d\x31";
				break;
			case '2':
				str2 += "\x26\x4d\x32";
				break;
			case '3':
				str2 += "\x26\x4d\x33";
				break;
			case '4':
				str2 += "\x26\x4d\x34";
				break;
			case '5':
				str2 += "\x26\x4d\x35";
				break;
			case '6':
				str2 += "\x26\x4d\x36";
				break;
			case '7':
				str2 += "\x26\x4d\x37";
				break;
			case '8':
				str2 += "\x26\x4d\x38";
				break;
			case '9':
				str2 += "\x26\x4d\x39";
				break;
			case '.':
				str2 += "\x26\x4d\x3a";
				break;
			default:
				if (app->language == 0)
				{
					AfxMessageBox("您的输入有误!");
				}
				else
				{
					AfxMessageBox("Your input is incorrect!");
				}
			}
		}
		str2 += "\x26\x4d\x3d\x0d"; 
	}
	str = str1 + str2;
	app->g_com.Write(str);
	str = "";
}
void CLineArrayDlg::OnSet02()
{
	//命令
	char menu[6] = {'\x4d', '\x45', '\x4e','\x55', '\x34','\x38'};
	CString str2 = "";
	int i;
	CSetDlg *parent = (CSetDlg *)GetParent();
	CCalibrationApp *app = (CCalibrationApp *)AfxGetApp();
	for (i=0; i<6; i++)
	{
		str2 += menu[i];

	}

	str2 += "\x26\x4d\x3d";
	str2 += "\x26\x4d\x31";
	str2 += "\x26\x4d\x31";
	str2 += "\x26\x4d\x31";
	str2 += "\x26\x4d\x31";
	str2 += "\x26\x4d\x3d";
	str2 += "\x26\x4d\x3f";
	str2 += "\x26\x4d\x3f";
	str2 += "\x26\x4c\x43\x44\x0d";

	UpdateData(TRUE);
	if (m_021 != "")
	{	
		for (i=0; i<m_021.GetLength(); i++)
		{
			switch(m_021.GetAt(i))
			{
			case '0':
				str2 += "\x26\x4d\x30";
				break;
			case '1':
				str2 += "\x26\x4d\x31";
				break;
			case '2':
				str2 += "\x26\x4d\x32";
				break;
			case '3':
				str2 += "\x26\x4d\x33";
				break;
			case '4':
				str2 += "\x26\x4d\x34";
				break;
			case '5':
				str2 += "\x26\x4d\x35";
				break;
			case '6':
				str2 += "\x26\x4d\x36";
				break;
			case '7':
				str2 += "\x26\x4d\x37";
				break;
			case '8':
				str2 += "\x26\x4d\x38";
				break;
			case '9':
				str2 += "\x26\x4d\x39";
				break;
			case '.':
				str2 += "\x26\x4d\x3a";
				break;
			default:
				if (app->language == 0)
				{
					AfxMessageBox("您的输入有误!");
				}
				else
				{
					AfxMessageBox("Your input is incorrect!");
				}
			}
		}
		str2 += "\x26\x4d\x3d";

	}
	UpdateData(TRUE);

	if (m_022 != "")
	{	
		for (i=0; i<m_022.GetLength(); i++)
		{
			switch(m_022.GetAt(i))
			{
			case '0':
				str2 += "\x26\x4d\x30";
				break;
			case '1':
				str2 += "\x26\x4d\x31";
				break;
			case '2':
				str2 += "\x26\x4d\x32";
				break;
			case '3':
				str2 += "\x26\x4d\x33";
				break;
			case '4':
				str2 += "\x26\x4d\x34";
				break;
			case '5':
				str2 += "\x26\x4d\x35";
				break;
			case '6':
				str2 += "\x26\x4d\x36";
				break;
			case '7':
				str2 += "\x26\x4d\x37";
				break;
			case '8':
				str2 += "\x26\x4d\x38";
				break;
			case '9':
				str2 += "\x26\x4d\x39";
				break;
			case '.':
				str2 += "\x26\x4d\x3a";
				break;
			default:
				if (app->language == 0)
				{
					AfxMessageBox("您的输入有误!");
				}
				else
				{
					AfxMessageBox("Your input is incorrect!");
				}
			}
		}
		str2 += "\x26\x4d\x3d\x0d";

	}
	str = str1 + str2;
	app->g_com.Write(str);
	str = "";
}
void CLineArrayDlg::OnSet03()
{
	//命令
	char menu[6] = {'\x4d', '\x45', '\x4e', '\x55', '\x34','\x38'};
	CString str2 = "";
	int i;
	CSetDlg *parent = (CSetDlg *)GetParent();
	CCalibrationApp *app = (CCalibrationApp *)AfxGetApp();
	for (i=0; i<6; i++)
	{
		str2 += menu[i];
	}

	str2 += "\x26\x4d\x3d";
	str2 += "\x26\x4d\x31";
	str2 += "\x26\x4d\x31";
	str2 += "\x26\x4d\x31";
	str2 += "\x26\x4d\x31";
	str2 += "\x26\x4d\x3d";
	str2 += "\x26\x4d\x3f";
	str2 += "\x26\x4d\x3f";
	str2 += "\x26\x4d\x3f";
	str2 += "\x26\x4c\x43\x44\x0d";

	UpdateData(TRUE);
	if (m_031 != "")
	{	
		for (i=0; i<m_031.GetLength(); i++)
		{
			switch(m_031.GetAt(i))
			{
			case '0':
				str2 += "\x26\x4d\x30";
				break;
			case '1':
				str2 += "\x26\x4d\x31";
				break;
			case '2':
				str2 += "\x26\x4d\x32";
				break;
			case '3':
				str2 += "\x26\x4d\x33";
				break;
			case '4':
				str2 += "\x26\x4d\x34";
				break;
			case '5':
				str2 += "\x26\x4d\x35";
				break;
			case '6':
				str2 += "\x26\x4d\x36";
				break;
			case '7':
				str2 += "\x26\x4d\x37";
				break;
			case '8':
				str2 += "\x26\x4d\x38";
				break;
			case '9':
				str2 += "\x26\x4d\x39";
				break;
			case '.':
				str2 += "\x26\x4d\x3a";
				break;
			default:
				if (app->language == 0)
				{
					AfxMessageBox("您的输入有误!");
				}
				else
				{
					AfxMessageBox("Your input is incorrect!");
				}
			}
		}
		str2 += "\x26\x4d\x3d";
	}
	UpdateData(TRUE);
	
	if (m_032 != "")
	{	
		for (i=0; i<m_032.GetLength(); i++)
		{
			switch(m_032.GetAt(i))
			{
			case '0':
				str2 += "\x26\x4d\x30";
				break;
			case '1':
				str2 += "\x26\x4d\x31";
				break;
			case '2':
				str2 += "\x26\x4d\x32";
				break;
			case '3':
				str2 += "\x26\x4d\x33";
				break;
			case '4':
				str2 += "\x26\x4d\x34";
				break;
			case '5':
				str2 += "\x26\x4d\x35";
				break;
			case '6':
				str2 += "\x26\x4d\x36";
				break;
			case '7':
				str2 += "\x26\x4d\x37";
				break;
			case '8':
				str2 += "\x26\x4d\x38";
				break;
			case '9':
				str2 += "\x26\x4d\x39";
				break;
			case '.':
				str2 += "\x26\x4d\x3a";
				break;
			default:
				if (app->language == 0)
				{
					AfxMessageBox("您的输入有误!");
				}
				else
				{
					AfxMessageBox("Your input is incorrect!");
				}
			}
		}
		str2 += "\x26\x4d\x3d\x0d";

	}
	str = str1 + str2;
	app->g_com.Write(str);
	str = "";
}
void CLineArrayDlg::OnSet04()
{	
	char menu[6] = {'\x4d', '\x45','\x4e', '\x55', '\x34','\x38'};
	CString str2 = "";
	int i;
	CSetDlg *parent = (CSetDlg *)GetParent();
	CCalibrationApp *app = (CCalibrationApp *)AfxGetApp();
	//命令
	for (i=0; i<6; i++)
	{
		str2 += menu[i];
	}

	str2 += "\x26\x4d\x3d";
	str2 += "\x26\x4d\x31";
	str2 += "\x26\x4d\x31";
	str2 += "\x26\x4d\x31";
	str2 += "\x26\x4d\x31";
	str2 += "\x26\x4d\x3d";
	str2 += "\x26\x4d\x3f";
	str2 += "\x26\x4d\x3f";
	str2 += "\x26\x4d\x3f";
	str2 += "\x26\x4d\x3f";
	str2 += "\x26\x4c\x43\x44\x0d";

	UpdateData(TRUE);
	if (m_041 != "")
	{	
		for (i=0; i<m_041.GetLength(); i++)
		{
			switch(m_041.GetAt(i))
			{
			case '0':
				str2 += "\x26\x4d\x30";
				break;
			case '1':
				str2 += "\x26\x4d\x31";
				break;
			case '2':
				str2 += "\x26\x4d\x32";
				break;
			case '3':
				str2 += "\x26\x4d\x33";
				break;
			case '4':
				str2 += "\x26\x4d\x34";
				break;
			case '5':
				str2 += "\x26\x4d\x35";
				break;
			case '6':
				str2 += "\x26\x4d\x36";
				break;
			case '7':
				str2 += "\x26\x4d\x37";
				break;
			case '8':
				str2 += "\x26\x4d\x38";
				break;
			case '9':
				str2 += "\x26\x4d\x39";
				break;
			case '.':
				str2 += "\x26\x4d\x3a";
				break;
			default:
				if (app->language == 0)
				{
					AfxMessageBox("您的输入有误!");
				}
				else
				{
					AfxMessageBox("Your input is incorrect!");
				}
			}
		}
		str2 += "\x26\x4d\x3d";

	}
	UpdateData(TRUE);
	
	if (m_042 != "")
	{	
		for (i=0; i<m_042.GetLength(); i++)
		{
			switch(m_042.GetAt(i))
			{
			case '0':
				str2 += "\x26\x4d\x30";
				break;
			case '1':
				str2 += "\x26\x4d\x31";
				break;
			case '2':
				str2 += "\x26\x4d\x32";
				break;
			case '3':
				str2 += "\x26\x4d\x33";
				break;
			case '4':
				str2 += "\x26\x4d\x34";
				break;
			case '5':
				str2 += "\x26\x4d\x35";
				break;
			case '6':
				str2 += "\x26\x4d\x36";
				break;
			case '7':
				str2 += "\x26\x4d\x37";
				break;
			case '8':
				str2 += "\x26\x4d\x38";
				break;
			case '9':
				str2 += "\x26\x4d\x39";
				break;
			case '.':
				str2 += "\x26\x4d\x3a";
				break;
			default:
				if (app->language == 0)
				{
					AfxMessageBox("您的输入有误!");
				}
				else
				{
					AfxMessageBox("Your input is incorrect!");
				}
			}
		}
		str2 += "\x26\x4d\x3d\x0d";

	}
	str = str1 + str2;
	app->g_com.Write(str);
	str = "";
}
void CLineArrayDlg::OnSet05()
{
	char menu[6] = {'\x4d', '\x45','\x4e', '\x55','\x34', '\x38'};
	CString str2 = "";
	int i;
	CSetDlg *parent = (CSetDlg *)GetParent();
	CCalibrationApp *app = (CCalibrationApp *)AfxGetApp();	
	//命令
	for (i=0; i<6; i++)
	{
		str2 += menu[i];
	}

	str2 += "\x26\x4d\x3d";
	str2 += "\x26\x4d\x31";
	str2 += "\x26\x4d\x31";
	str2 += "\x26\x4d\x31";
	str2 += "\x26\x4d\x31";
	str2 += "\x26\x4d\x3d";
	str2 += "\x26\x4d\x3f";
	str2 += "\x26\x4d\x3f";
	str2 += "\x26\x4d\x3f";
	str2 += "\x26\x4d\x3f";
	str2 += "\x26\x4d\x3f";
	str2 += "\x26\x4c\x43\x44\x0d";

	UpdateData(TRUE);
	if (m_051 != "")
	{	
		for (i=0; i<m_051.GetLength(); i++)
		{
			switch(m_051.GetAt(i))
			{
			case '0':
				str2 += "\x26\x4d\x30";
				break;
			case '1':
				str2 += "\x26\x4d\x31";
				break;
			case '2':
				str2 += "\x26\x4d\x32";
				break;
			case '3':
				str2 += "\x26\x4d\x33";
				break;
			case '4':
				str2 += "\x26\x4d\x34";
				break;
			case '5':
				str2 += "\x26\x4d\x35";
				break;
			case '6':
				str2 += "\x26\x4d\x36";
				break;
			case '7':
				str2 += "\x26\x4d\x37";
				break;
			case '8':
				str2 += "\x26\x4d\x38";
				break;
			case '9':
				str2 += "\x26\x4d\x39";
				break;
			case '.':
				str2 += "\x26\x4d\x3a";
				break;
			default:
				if (app->language == 0)
				{
					AfxMessageBox("您的输入有误!");
				}
				else
				{
					AfxMessageBox("Your input is incorrect!");
				}
			}
		}
		str2 +="\x26\x4d\x3d";

	}
	UpdateData(TRUE);
	
	if (m_052 != "")
	{	
		for (i=0; i<m_052.GetLength(); i++)
		{
			switch(m_052.GetAt(i))
			{
			case '0':
				str2 += "\x26\x4d\x30";
				break;
			case '1':
				str2 += "\x26\x4d\x31";
				break;
			case '2':
				str2 += "\x26\x4d\x32";
				break;
			case '3':
				str2 += "\x26\x4d\x33";
				break;
			case '4':
				str2 += "\x26\x4d\x34";
				break;
			case '5':
				str2 += "\x26\x4d\x35";
				break;
			case '6':
				str2 += "\x26\x4d\x36";
				break;
			case '7':
				str2 += "\x26\x4d\x37";
				break;
			case '8':
				str2 += "\x26\x4d\x38";
				break;
			case '9':
				str2 += "\x26\x4d\x39";
				break;
			case '.':
				str2 += "\x26\x4d\x3a";
				break;
			default:
				if (app->language == 0)
				{
					AfxMessageBox("您的输入有误!");
				}
				else
				{
					AfxMessageBox("Your input is incorrect!");
				}
			}
		}
		str2 += "\x26\x4d\x3d\x0d";

	}
	str = str1 + str2;
	app->g_com.Write(str);
	str = "";
}
void CLineArrayDlg::OnSet06()
{
	char menu[6] = {'\x4d', '\x45','\x4e','\x55','\x34', '\x38'};
	CString str2 = "";
	int i;
	CSetDlg *parent = (CSetDlg *)GetParent();
	CCalibrationApp *app = (CCalibrationApp *)AfxGetApp();
	//命令
	for (i=0; i<6; i++)
	{
		str2 += menu[i];
	}

	str2 += "\x26\x4d\x3d";
	str2 += "\x26\x4d\x31";
	str2 += "\x26\x4d\x31";
	str2 += "\x26\x4d\x31";
	str2 += "\x26\x4d\x31";
	str2 += "\x26\x4d\x3d";
	str2 += "\x26\x4d\x3f";
	str2 += "\x26\x4d\x3f";
	str2 += "\x26\x4d\x3f";
	str2 += "\x26\x4d\x3f";
	str2 += "\x26\x4d\x3f";
	str2 += "\x26\x4d\x3f";
	str2 += "\x26\x4c\x43\x44\x0d";

	UpdateData(TRUE);
	if (m_061 != "")
	{	
		for (i=0; i<m_061.GetLength(); i++)
		{
			switch(m_061.GetAt(i))
			{
			case '0':
				str2 += "\x26\x4d\x30";
				break;
			case '1':
				str2 += "\x26\x4d\x31";
				break;
			case '2':
				str2 += "\x26\x4d\x32";
				break;
			case '3':
				str2 += "\x26\x4d\x33";
				break;
			case '4':
				str2 += "\x26\x4d\x34";
				break;
			case '5':
				str2 += "\x26\x4d\x35";
				break;
			case '6':
				str2 += "\x26\x4d\x36";
				break;
			case '7':
				str2 += "\x26\x4d\x37";
				break;
			case '8':
				str2 += "\x26\x4d\x38";
				break;
			case '9':
				str2 += "\x26\x4d\x39";
				break;
			case '.':
				str2 += "\x26\x4d\x3a";
				break;
			default:
				if (app->language == 0)
				{
					AfxMessageBox("您的输入有误!");
				}
				else
				{
					AfxMessageBox("Your input is incorrect!");
				}
			}
		}
		str2 += "\x26\x4d\x3d";
	}
	UpdateData(TRUE);
	
	if (m_062 != "")
	{	
		for (i=0; i<m_062.GetLength(); i++)
		{
			switch(m_062.GetAt(i))
			{
			case '0':
				str2 += "\x26\x4d\x30";
				break;
			case '1':
				str2 += "\x26\x4d\x31";
				break;
			case '2':
				str2 += "\x26\x4d\x32";
				break;
			case '3':
				str2 += "\x26\x4d\x33";
				break;
			case '4':
				str2 += "\x26\x4d\x34";
				break;
			case '5':
				str2 += "\x26\x4d\x35";
				break;
			case '6':
				str2 += "\x26\x4d\x36";
				break;
			case '7':
				str2 += "\x26\x4d\x37";
				break;
			case '8':
				str2 += "\x26\x4d\x38";
				break;
			case '9':
				str2 += "\x26\x4d\x39";
				break;
			case '.':
				str2 += "\x26\x4d\x3a";
				break;
			default:
				if (app->language == 0)
				{
					AfxMessageBox("您的输入有误!");
				}
				else
				{
					AfxMessageBox("Your input is incorrect!");
				}
			}
		}
		str2 += "\x26\x4d\x3d\x0d";
	}
	str = str1 + str2;
	app->g_com.Write(str);
	str = "";
}
void CLineArrayDlg::OnSet07()
{
	char menu[6] = {'\x4d', '\x45', '\x4e', '\x55', '\x34', '\x38'};
	CString str2 = "";
	int i;
	CSetDlg *parent = (CSetDlg *)GetParent();
	CCalibrationApp *app = (CCalibrationApp *)AfxGetApp();
	//命令
	for (i=0; i<76; i++)
	{
		str2 += CString(menu[i]);
	}

	str2 += "\x26\x4d\x3d";
	str2 += "\x26\x4d\x31";
	str2 += "\x26\x4d\x31";
	str2 += "\x26\x4d\x31";
	str2 += "\x26\x4d\x31";
	str2 += "\x26\x4d\x3d";
	str2 += "\x26\x4d\x3f";
	str2 += "\x26\x4d\x3f";
	str2 += "\x26\x4d\x3f";
	str2 += "\x26\x4d\x3f";
	str2 += "\x26\x4d\x3f";
	str2 += "\x26\x4d\x3f";
	str2 += "\x26\x4d\x3f";
	str2 += "\x26\x4c\x43\x44\x0d";

	UpdateData(TRUE);
	if (m_071 != "")
	{	
		for (i=0; i<m_071.GetLength(); i++)
		{
			switch(m_071.GetAt(i))
			{
			case '0':
				str2 += "\x26\x4d\x30";
				break;
			case '1':
				str2 += "\x26\x4d\x31";
				break;
			case '2':
				str2 += "\x26\x4d\x32";
				break;
			case '3':
				str2 += "\x26\x4d\x33";
				break;
			case '4':
				str2 += "\x26\x4d\x34";
				break;
			case '5':
				str2 += "\x26\x4d\x35";
				break;
			case '6':
				str2 += "\x26\x4d\x36";
				break;
			case '7':
				str2 += "\x26\x4d\x37";
				break;
			case '8':
				str2 += "\x26\x4d\x38";
				break;
			case '9':
				str2 += "\x26\x4d\x39";
				break;
			case '.':
				str2 += "\x26\x4d\x3a";
				break;
			default:
				if (app->language == 0)
				{
					AfxMessageBox("您的输入有误!");
				}
				else
				{
					AfxMessageBox("Your input is incorrect!");
				}
			}
		}
		str2 += "\x26\x4d\x3d";
	}
	UpdateData(TRUE);
	
	if (m_072 != "")
	{	
		for (i=0; i<m_072.GetLength(); i++)
		{
			switch(m_072.GetAt(i))
			{
			case '0':
				str2 += "\x26\x4d\x30";
				break;
			case '1':
				str2 += "\x26\x4d\x31";
				break;
			case '2':
				str2 += "\x26\x4d\x32";
				break;
			case '3':
				str2 += "\x26\x4d\x33";
				break;
			case '4':
				str2 += "\x26\x4d\x34";
				break;
			case '5':
				str2 += "\x26\x4d\x35";
				break;
			case '6':
				str2 += "\x26\x4d\x36";
				break;
			case '7':
				str2 += "\x26\x4d\x37";
				break;
			case '8':
				str2 += "\x26\x4d\x38";
				break;
			case '9':
				str2 += "\x26\x4d\x39";
				break;
			case '.':
				str2 += "\x26\x4d\x3a";
				break;
			default:
				if (app->language == 0)
				{
					AfxMessageBox("您的输入有误!");
				}
				else
				{
					AfxMessageBox("Your input is incorrect!");
				}
			}
		}
	    str2 += "\x26\x4d\x3d\x0d";

	}
	str = str1 + str2;
	app->g_com.Write(str);
	str = "";
}
void CLineArrayDlg::OnSet08()
{
	char menu[6] = {'\x4d', '\x45', '\x4e', '\x55', '\x34', '\x38'};
	CString str2 = "";
	int i;
	CSetDlg *parent = (CSetDlg *)GetParent();
	CCalibrationApp *app = (CCalibrationApp *)AfxGetApp();
	//命令
	for (i=0; i<6; i++)
	{
		str2 += menu[i];
	}

	str2 += "\x26\x4d\x3d";
	str2 += "\x26\x4d\x31";
	str2 += "\x26\x4d\x31";
	str2 += "\x26\x4d\x31";
	str2 += "\x26\x4d\x31";
	str2 += "\x26\x4d\x3d";
	str2 += "\x26\x4d\x3f";
	str2 += "\x26\x4d\x3f";
	str2 += "\x26\x4d\x3f";
	str2 += "\x26\x4d\x3f";
	str2 += "\x26\x4d\x3f";
	str2 += "\x26\x4d\x3f";
	str2 += "\x26\x4d\x3f";
	str2 += "\x26\x4d\x3f";
	str2 += "\x26\x4c\x43\x44\x0d";


	UpdateData(TRUE);
	if (m_081 != "")
	{	
		for (i=0; i<m_081.GetLength(); i++)
		{
			switch(m_081.GetAt(i))
			{
			case '0':
				str2 += "\x26\x4d\x30";
				break;
			case '1':
				str2 += "\x26\x4d\x31";
				break;
			case '2':
				str2 += "\x26\x4d\x32";
				break;
			case '3':
				str2 += "\x26\x4d\x33";
				break;
			case '4':
				str2 += "\x26\x4d\x34";
				break;
			case '5':
				str2 += "\x26\x4d\x35";
				break;
			case '6':
				str2 += "\x26\x4d\x36";
				break;
			case '7':
				str2 += "\x26\x4d\x37";
				break;
			case '8':
				str2 += "\x26\x4d\x38";
				break;
			case '9':
				str2 += "\x26\x4d\x39";
				break;
			case '.':
				str2 += "\x26\x4d\x3a";
				break;
			default:
				if (app->language == 0)
				{
					AfxMessageBox("您的输入有误!");
				}
				else
				{
					AfxMessageBox("Your input is incorrect!");
				}
			}
		}
		str2 += "\x26\x4d\x3d";
	}
	UpdateData(TRUE);
	
	if (m_082 != "")
	{	
		for (i=0; i<m_082.GetLength(); i++)
		{
			switch(m_082.GetAt(i))
			{
			case '0':
				str2 += "\x26\x4d\x30";
				break;
			case '1':
				str2 += "\x26\x4d\x31";
				break;
			case '2':
				str2 += "\x26\x4d\x32";
				break;
			case '3':
				str2 += "\x26\x4d\x33";
				break;
			case '4':
				str2 += "\x26\x4d\x34";
				break;
			case '5':
				str2 += "\x26\x4d\x35";
				break;
			case '6':
				str2 += "\x26\x4d\x36";
				break;
			case '7':
				str2 += "\x26\x4d\x37";
				break;
			case '8':
				str2 += "\x26\x4d\x38";
				break;
			case '9':
				str2 += "\x26\x4d\x39";
				break;
			case '.':
				str2 += "\x26\x4d\x3a";
				break;
			default:
				if (app->language == 0)
				{
					AfxMessageBox("您的输入有误!");
				}
				else
				{
					AfxMessageBox("Your input is incorrect!");
				}
			}
		}
		str2 += "\x26\x4d\x3d\x0d";
	}
	str = str1 + str2;
	app->g_com.Write(str);
	str = "";
}
void CLineArrayDlg::OnSet09()
{
	char menu[6] = {'\x4d', '\x45', '\x4e', '\x55', '\x34', '\x38'};
	CString str2 = "";
	int i;
	CSetDlg *parent = (CSetDlg *)GetParent();
	CCalibrationApp *app = (CCalibrationApp *)AfxGetApp();
	//命令
	for (i=0; i<6; i++)
	{
		str2 += menu[i];
	}

	str2 += "\x26\x4d\x3d";
	str2 += "\x26\x4d\x31";
	str2 += "\x26\x4d\x31";
	str2 += "\x26\x4d\x31";
	str2 += "\x26\x4d\x31";
	str2 += "\x26\x4d\x3d";
	str2 += "\x26\x4d\x3f";
	str2 += "\x26\x4d\x3f";
	str2 += "\x26\x4d\x3f";
	str2 += "\x26\x4d\x3f";
	str2 += "\x26\x4d\x3f";
	str2 += "\x26\x4d\x3f";
	str2 += "\x26\x4d\x3f";
	str2 += "\x26\x4d\x3f";
	str2 += "\x26\x4d\x3f";
	str2 += "\x26\x4c\x43\x44\x0d";

	UpdateData(TRUE);
	if (m_091 != "")
	{	
		for (i=0; i<m_091.GetLength(); i++)
		{
			switch(m_091.GetAt(i))
			{
			case '0':
				str2 += "\x26\x4d\x30";
				break;
			case '1':
				str2 += "\x26\x4d\x31";
				break;
			case '2':
				str2 += "\x26\x4d\x32";
				break;
			case '3':
				str2 += "\x26\x4d\x33";
				break;
			case '4':
				str2 += "\x26\x4d\x34";
				break;
			case '5':
				str2 += "\x26\x4d\x35";
				break;
			case '6':
				str2 += "\x26\x4d\x36";
				break;
			case '7':
				str2 += "\x26\x4d\x37";
				break;
			case '8':
				str2 += "\x26\x4d\x38";
				break;
			case '9':
				str2 += "\x26\x4d\x39";
				break;
			case '.':
				str2 += "\x26\x4d\x3a";
				break;
			default:
				if (app->language == 0)
				{
					AfxMessageBox("您的输入有误!");
				}
				else
				{
					AfxMessageBox("Your input is incorrect!");
				}
			}
		}
		str2 +="\x26\x4d\x3d";

	}
	UpdateData(TRUE);
	
	if (m_092 != "")
	{	
		for (i=0; i<m_092.GetLength(); i++)
		{
			switch(m_092.GetAt(i))
			{
			case '0':
				str2 += "\x26\x4d\x30";
				break;
			case '1':
				str2 += "\x26\x4d\x31";
				break;
			case '2':
				str2 += "\x26\x4d\x32";
				break;
			case '3':
				str2 += "\x26\x4d\x33";
				break;
			case '4':
				str2 += "\x26\x4d\x34";
				break;
			case '5':
				str2 += "\x26\x4d\x35";
				break;
			case '6':
				str2 += "\x26\x4d\x36";
				break;
			case '7':
				str2 += "\x26\x4d\x37";
				break;
			case '8':
				str2 += "\x26\x4d\x38";
				break;
			case '9':
				str2 += "\x26\x4d\x39";
				break;
			case '.':
				str2 += "\x26\x4d\x3a";
				break;
			default:
				if (app->language == 0)
				{
					AfxMessageBox("您的输入有误!");
				}
				else
				{
					AfxMessageBox("Your input is incorrect!");
				}
			}
		}
		str2 += "\x26\x4d\x3d\x0d";

	}
	str = str1 + str2;
	app->g_com.Write(str);
	str = "";
}
void CLineArrayDlg::OnSet10()
{
	char menu[6] = {'\x4d', '\x45', '\x4e', '\x55', '\x34', '\x38'};
	CString str2 = "";
	int i;
	CSetDlg *parent = (CSetDlg *)GetParent();
	CCalibrationApp *app = (CCalibrationApp *)AfxGetApp();
	//命令
	for (i=0; i<6; i++)
	{
		str2 += menu[i];
	}

	str2 += "\x26\x4d\x3d";
	str2 += "\x26\x4d\x31";
	str2 += "\x26\x4d\x31";
	str2 += "\x26\x4d\x31";
	str2 += "\x26\x4d\x31";
	str2 += "\x26\x4d\x3d";
	str2 += "\x26\x4d\x3f";
	str2 += "\x26\x4d\x3f";
	str2 += "\x26\x4d\x3f";
	str2 += "\x26\x4d\x3f";
	str2 += "\x26\x4d\x3f";
	str2 += "\x26\x4d\x3f";
	str2 += "\x26\x4d\x3f";
	str2 += "\x26\x4d\x3f";
	str2 += "\x26\x4d\x3f";
	str2 += "\x26\x4d\x3f";
	str2 += "\x26\x4c\x43\x44\x0d";

	UpdateData(TRUE);
	if (m_101 != "")
	{	
		for (i=0; i<m_101.GetLength(); i++)
		{
			switch(m_101.GetAt(i))
			{
			case '0':
				str2 += "\x26\x4d\x30";
				break;
			case '1':
				str2 += "\x26\x4d\x31";
				break;
			case '2':
				str2 += "\x26\x4d\x32";
				break;
			case '3':
				str2 += "\x26\x4d\x33";
				break;
			case '4':
				str2 += "\x26\x4d\x34";
				break;
			case '5':
				str2 += "\x26\x4d\x35";
				break;
			case '6':
				str2 += "\x26\x4d\x36";
				break;
			case '7':
				str2 += "\x26\x4d\x37";
				break;
			case '8':
				str2 += "\x26\x4d\x38";
				break;
			case '9':
				str2 += "\x26\x4d\x39";
				break;
			case '.':
				str2 += "\x26\x4d\x3a";
				break;
			default:
				if (app->language == 0)
				{
					AfxMessageBox("您的输入有误!");
				}
				else
				{
					AfxMessageBox("Your input is incorrect!");
				}
			}
		}
		str2 += "\x26\x4d\x3d";

	}
	UpdateData(TRUE);
	
	if (m_102 != "")
	{	
		for (i=0; i<m_102.GetLength(); i++)
		{
			switch(m_102.GetAt(i))
			{
			case '0':
				str2 += "\x26\x4d\x30";
				break;
			case '1':
				str2 += "\x26\x4d\x31";
				break;
			case '2':
				str2 += "\x26\x4d\x32";
				break;
			case '3':
				str2 += "\x26\x4d\x33";
				break;
			case '4':
				str2 += "\x26\x4d\x34";
				break;
			case '5':
				str2 += "\x26\x4d\x35";
				break;
			case '6':
				str2 += "\x26\x4d\x36";
				break;
			case '7':
				str2 += "\x26\x4d\x37";
				break;
			case '8':
				str2 += "\x26\x4d\x38";
				break;
			case '9':
				str2 += "\x26\x4d\x39";
				break;
			case '.':
				str2 += "\x26\x4d\x3a";
				break;
			default:
				if (app->language == 0)
				{
					AfxMessageBox("您的输入有误!");
				}
				else
				{
					AfxMessageBox("Your input is incorrect!");
				}
			}
		}
		str2 += "\x26\x4d\x3d\x0d";
	}
	str = str1 + str2;
	app->g_com.Write(str);
	str = "";
}
void CLineArrayDlg::OnSet11()
{
	int menu[6] = {0x4d, 0x45, 0x4e, 0x55, 0x34, 0x38};
	CString str2 = "";
	int i;
	CSetDlg *parent = (CSetDlg *)GetParent();
	CCalibrationApp *app = (CCalibrationApp *)AfxGetApp();
	//命令
	for (i=0; i<6; i++)
	{
		//str2 += CString(menu[i]);
		CString temp1;
		temp1.Format("%d", menu[i]);
		str2 += temp1;
	}

	str2 += "\x26\x4d\x3d";
	str2 += "\x26\x4d\x31";
	str2 += "\x26\x4d\x31";
	str2 += "\x26\x4d\x31";
	str2 += "\x26\x4d\x31";
	str2 += "\x26\x4d\x3d";
	str2 += "\x26\x4d\x3f";
	str2 += "\x26\x4d\x3f";
	str2 += "\x26\x4d\x3f";
	str2 += "\x26\x4d\x3f";
	str2 += "\x26\x4d\x3f";
	str2 += "\x26\x4d\x3f";
	str2 += "\x26\x4d\x3f";
	str2 += "\x26\x4d\x3f";
	str2 += "\x26\x4d\x3f";
	str2 += "\x26\x4d\x3f";
	str2 += "\x26\x4d\x3f";
	str2 += "\x26\x4c\x43\x44\x0d";

	UpdateData(TRUE);
	if (m_111 != "")
	{	
		for (i=0; i<m_111.GetLength(); i++)
		{
			switch(m_111.GetAt(i))
			{
			case '0':
				str2 += "\x26\x4d\x30";
				break;
			case '1':
				str2 += "\x26\x4d\x31";
				break;
			case '2':
				str2 += "\x26\x4d\x32";
				break;
			case '3':
				str2 += "\x26\x4d\x33";
				break;
			case '4':
				str2 += "\x26\x4d\x34";
				break;
			case '5':
				str2 += "\x26\x4d\x35";
				break;
			case '6':
				str2 += "\x26\x4d\x36";
				break;
			case '7':
				str2 += "\x26\x4d\x37";
				break;
			case '8':
				str2 += "\x26\x4d\x38";
				break;
			case '9':
				str2 += "\x26\x4d\x39";
				break;
			case '.':
				str2 += "\x26\x4d\x3a";
				break;
			default:
				if (app->language == 0)
				{
					AfxMessageBox("您的输入有误!");
				}
				else
				{
					AfxMessageBox("Your input is incorrect!");
				}
			}
		}
		str2 += "\x26\x4d\x3d";

	}
	UpdateData(TRUE);
	
	if (m_112 != "")
	{	
		for (i=0; i<m_112.GetLength(); i++)
		{
			switch(m_112.GetAt(i))
			{
			case '0':
				str2 += "\x26\x4d\x30";
				break;
			case '1':
				str2 += "\x26\x4d\x31";
				break;
			case '2':
				str2 += "\x26\x4d\x32";
				break;
			case '3':
				str2 += "\x26\x4d\x33";
				break;
			case '4':
				str2 += "\x26\x4d\x34";
				break;
			case '5':
				str2 += "\x26\x4d\x35";
				break;
			case '6':
				str2 += "\x26\x4d\x36";
				break;
			case '7':
				str2 += "\x26\x4d\x37";
				break;
			case '8':
				str2 += "\x26\x4d\x38";
				break;
			case '9':
				str2 += "\x26\x4d\x39";
				break;
			case '.':
				str2 += "\x26\x4d\x3a";
				break;
			default:
				if (app->language == 0)
				{
					AfxMessageBox("您的输入有误!");
				}
				else
				{
					AfxMessageBox("Your input is incorrect!");
				}
			}
		}
		str2 += "\x26\x4d\x3d\x0d";

	}
	str = str1 + str2;
	app->g_com.Write(str);
	str = "";
}
void CLineArrayDlg::OnSet12()
{
	int i;
	CSetDlg *parent = (CSetDlg *)GetParent();
	CCalibrationApp *app = (CCalibrationApp *)AfxGetApp();
	//命令
	char menu[6] = {'\x4d', '\x45','\x4e', '\x55', '\x34', '\x38'};
	CString str2 = "";
	for (i=0; i<6; i++)
	{
		str2 += CString(menu[i]);
	}

	str2 += "\x26\x4d\x3d";
	str2 += "\x26\x4d\x31";
	str2 += "\x26\x4d\x31";
	str2 += "\x26\x4d\x31";
	str2 += "\x26\x4d\x31";
	str2 += "\x26\x4d\x3d";
	str2 += "\x26\x4d\x3f";
	str2 += "\x26\x4d\x3f";
	str2 += "\x26\x4d\x3f";
	str2 += "\x26\x4d\x3f";
	str2 += "\x26\x4d\x3f";
	str2 += "\x26\x4d\x3f";
	str2 += "\x26\x4d\x3f";
	str2 += "\x26\x4d\x3f";
	str2 += "\x26\x4d\x3f";
	str2 += "\x26\x4d\x3f";
	str2 += "\x26\x4d\x3f";
	str2 += "\x26\x4d\x3f";
	str2 += "\x26\x4c\x43\x44\x0d";

	UpdateData(TRUE);
	if (m_121 != "")
	{	
		for (i=0; i<m_121.GetLength(); i++)
		{
			switch(m_121.GetAt(i))
			{
			case '0':
				str2 += "\x26\x4d\x30";
				break;
			case '1':
				str2 += "\x26\x4d\x31";
				break;
			case '2':
				str2 += "\x26\x4d\x32";
				break;
			case '3':
				str2 += "\x26\x4d\x33";
				break;
			case '4':
				str2 += "\x26\x4d\x34";
				break;
			case '5':
				str2 += "\x26\x4d\x35";
				break;
			case '6':
				str2 += "\x26\x4d\x36";
				break;
			case '7':
				str2 += "\x26\x4d\x37";
				break;
			case '8':
				str2 += "\x26\x4d\x38";
				break;
			case '9':
				str2 += "\x26\x4d\x39";
				break;
			case '.':
				str2 += "\x26\x4d\x3a";
				break;
			default:
				if (app->language == 0)
				{
					AfxMessageBox("您的输入有误!");
				}
				else
				{
					AfxMessageBox("Your input is incorrect!");
				}
			}
		}
		str2 += "\x26\x4d\x3d";

	}
	UpdateData(TRUE);
	
	if (m_122 != "")
	{	
		for (i=0; i<m_122.GetLength(); i++)
		{
			switch(m_122.GetAt(i))
			{
			case '0':
				str2 += "\x26\x4d\x30";
				break;
			case '1':
				str2 += "\x26\x4d\x31";
				break;
			case '2':
				str2 += "\x26\x4d\x32";
				break;
			case '3':
				str2 += "\x26\x4d\x33";
				break;
			case '4':
				str2 += "\x26\x4d\x34";
				break;
			case '5':
				str2 += "\x26\x4d\x35";
				break;
			case '6':
				str2 += "\x26\x4d\x36";
				break;
			case '7':
				str2 += "\x26\x4d\x37";
				break;
			case '8':
				str2 += "\x26\x4d\x38";
				break;
			case '9':
				str2 += "\x26\x4d\x39";
				break;
			case '.':
				str2 += "\x26\x4d\x3a";
				break;
			default:
				if (app->language == 0)
				{
					AfxMessageBox("您的输入有误!");
				}
				else
				{
					AfxMessageBox("Your input is incorrect!");
				}
			}
		}
		str2 += "\x26\x4d\x3d\x0d";
	}
	str = str1 + str2;
	app->g_com.Write(str);
	str = "";
}
