// SetDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Calibration.h"
#include "CalibrationDlg.h"
#include "SetDlg.h"
#include "Log.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSetDlg dialog


CSetDlg::CSetDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSetDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSetDlg)
	m_m11 = _T("");
	m_m12 = _T("");
	m_m13 = _T("");
	m_m18 = _T("");
	m_m40 = _T("");
	m_m45 = _T("");
	m_m231 = _T("");
	m_m232 = _T("");
	m_m233 = _T("");
	m_m234 = _T("");
	//}}AFX_DATA_INIT
}


void CSetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSetDlg)
	DDX_Text(pDX, IDC_EDIT_M11, m_m11);
	DDX_Text(pDX, IDC_EDIT_M12, m_m12);
	DDX_Text(pDX, IDC_EDIT_M13, m_m13);
	DDX_Text(pDX, IDC_EDIT_M18, m_m18);
	DDX_Text(pDX, IDC_EDIT_M40, m_m40);
	DDV_MaxChars(pDX, m_m40, 3);
	DDX_Text(pDX, IDC_EDIT_M45, m_m45);
	DDX_Text(pDX, IDC_EDIT_M23_1, m_m231);
	DDX_Text(pDX, IDC_EDIT_M23_2, m_m232);
	DDX_Text(pDX, IDC_EDIT_M23_3, m_m233);
	DDX_Text(pDX, IDC_EDIT_M23_4, m_m234);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSetDlg, CDialog)
	//{{AFX_MSG_MAP(CSetDlg)
	ON_BN_CLICKED(IDC_M11, OnM11)
	ON_BN_CLICKED(IDC_M30, OnM30)
	ON_BN_CLICKED(IDC_M12, OnM12)
	ON_BN_CLICKED(IDC_M13, OnM13)
	ON_BN_CLICKED(IDC_UPDATE_M14, OnUpdateM14)
	ON_BN_CLICKED(IDC_M14, OnM14)
	ON_BN_CLICKED(IDC_UPDATE_M16, OnUpdateM16)
	ON_BN_CLICKED(IDC_M16, OnM16)
	ON_BN_CLICKED(IDC_M18, OnM18)
	ON_BN_CLICKED(IDC_UPDATE_M20, OnUpdateM20)
	ON_BN_CLICKED(IDC_M20, OnM20)
	ON_BN_CLICKED(IDC_UPDATE_M31, OnUpdateM31)
	ON_BN_CLICKED(IDC_M31, OnM31)
	ON_BN_CLICKED(IDC_UPDATE_M32, OnUpdateM32)
	ON_BN_CLICKED(IDC_M32, OnM32)
	ON_BN_CLICKED(IDC_UPDATE_M33, OnUpdateM33)
	ON_BN_CLICKED(IDC_M33, OnM33)
	ON_BN_CLICKED(IDC_M34, OnM34)
	ON_BN_CLICKED(IDC_M35, OnM35)
	ON_BN_CLICKED(IDC_M36, OnM36)
	ON_BN_CLICKED(IDC_M37, OnM37)
	ON_BN_CLICKED(IDC_OK, OnOk)
	ON_BN_CLICKED(IDC_UPDATE_M39, OnUpdateM39)
	ON_BN_CLICKED(IDC_M39, OnM39)
	ON_BN_CLICKED(IDC_M40, OnM40)
	ON_BN_CLICKED(IDC_UPDATE_M79, OnUpdateM79)
	ON_BN_CLICKED(IDC_M79, OnM79)
	ON_CBN_SELCHANGE(IDC_COMBO_METER, OnSelchangeComboMeter)
	ON_BN_CLICKED(IDC_UPDATE_M24, OnUpdateM24)
	ON_BN_CLICKED(IDC_UPDATE_M26, OnUpdateM26)
	ON_BN_CLICKED(IDC_M25, OnM25)
	ON_BN_CLICKED(IDC_M45, OnM45)
	ON_BN_CLICKED(IDC_M23, OnM23)
	ON_BN_CLICKED(IDC_QUICK_SET2, OnQuickSet2)
	ON_BN_CLICKED(IDC_QUICK_SET, OnQuickSet)
	ON_WM_CTLCOLOR()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_M24, OnM24)
	ON_BN_CLICKED(IDC_M48, OnM48)
	ON_BN_CLICKED(IDC_M23_1, OnM231)
	ON_BN_CLICKED(IDC_M23_2, OnM232)
	ON_BN_CLICKED(IDC_M23_3, OnM233)
	ON_BN_CLICKED(IDC_M23_4, OnM234)
	ON_BN_CLICKED(IDC_COPY, OnCopy)
	ON_EN_CHANGE(IDC_EDIT_M11, OnChangeEditM11)
	ON_EN_CHANGE(IDC_EDIT_M12, OnChangeEditM12)
	ON_BN_CLICKED(IDC_MULSET, OnMulset)
	ON_BN_CLICKED(IDC_PASTE, OnPaste)
	ON_CBN_SELCHANGE(IDC_COMBO_M23, OnSelchangeComboM23)
	ON_CBN_SELCHANGE(IDC_COMBO_M24, OnSelchangeComboM24)
	ON_EN_CHANGE(IDC_EDIT_M23_1, OnChangeEditM231)
	ON_EN_CHANGE(IDC_EDIT_M23_2, OnChangeEditM232)
	ON_EN_CHANGE(IDC_EDIT_M23_3, OnChangeEditM233)
	ON_EN_CHANGE(IDC_EDIT_M23_4, OnChangeEditM234)
	ON_BN_CLICKED(IDC_RADIO1, OnRadio1)
	ON_BN_CLICKED(IDC_RADIO2, OnRadio2)
	ON_CBN_SELCHANGE(IDC_COMBO_M16, OnSelchangeComboM16)
	ON_BN_CLICKED(IDC_RADIO9, OnRadio9)
	ON_BN_CLICKED(IDC_RADIO10, OnRadio10)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSetDlg message handlers
int __stdcall SetChildFont(struct HWND__ *,long);
//extern CFont *g_Font;

LRESULT   __stdcall   CBTHookProc(   long   nCode,WPARAM   wParam,LPARAM   lParam) ;
extern HHOOK   hHook; 

BOOL CSetDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CCalibrationApp *app = (CCalibrationApp *)AfxGetApp();

	LOGFONT lf;                        // Used to create the CFont.
	memset(&lf, 0, sizeof(LOGFONT));   // Clear out structure.
	lf.lfHeight = 15;                  // Request a 20-pixel-high font
	strcpy(lf.lfFaceName, "Times New Roman");    
	if (g_font.m_hObject)
		g_font.DeleteObject();
	g_font.CreateFontIndirect(&lf);    // Create the font.

	if (app->language == 0)
	{
		this->SetWindowText("设置");
		GetDlgItem(IDC_STATIC_COMSET)->SetWindowText("公用设置");
		GetDlgItem(IDC_STATIC_INDSET)->SetWindowText("独立设置");
		GetDlgItem(IDC_M11)->SetWindowText("管道外直径");
		GetDlgItem(IDC_M12)->SetWindowText("管道管壁厚度");
		GetDlgItem(IDC_M13)->SetWindowText("管道内直径");
		GetDlgItem(IDC_M14)->SetWindowText("管道材质类型");
		CComboBox *m_Combo = (CComboBox *)GetDlgItem(IDC_COMBO_M14);
		int nItem = m_Combo->GetCount();
		while(nItem)
		{
			m_Combo->DeleteString(--nItem);
		}
		m_Combo->AddString("0. 碳钢");
		m_Combo->AddString("1. 不锈钢");
		m_Combo->AddString("2. 铸铁");
		m_Combo->AddString("3. 球墨铸铁");
		m_Combo->AddString("4. 铜");
		m_Combo->AddString("5. PVC,塑料");
		m_Combo->AddString("6. 铝");
		m_Combo->AddString("7. 石棉");
		m_Combo->AddString("8. 玻璃钢");
		m_Combo->AddString("9. 其它");
		GetDlgItem(IDC_M16)->SetWindowText("衬里材质类型");
		m_Combo = (CComboBox *)GetDlgItem(IDC_COMBO_M16);
		nItem = m_Combo->GetCount();
		while(nItem)
		{
			m_Combo->DeleteString(--nItem);
		}
		m_Combo->AddString("0. 无衬里");
		m_Combo->AddString("1. 环氧沥青");
		m_Combo->AddString("2. 橡胶");
		m_Combo->AddString("3. 灰浆");
		m_Combo->AddString("4. 聚丙烯");
		m_Combo->AddString("5. 聚苯乙烯");
		m_Combo->AddString("6. 聚苯乙烯");
		m_Combo->AddString("7. 聚酯");
		m_Combo->AddString("8. 聚乙烯");
		m_Combo->AddString("9. 硬质橡胶,胶木");
		m_Combo->AddString("10. 聚四氟乙烯");
		m_Combo->AddString("11. 其他");
		GetDlgItem(IDC_M18)->SetWindowText("衬里厚度");
		GetDlgItem(IDC_M20)->SetWindowText("流体类型");		
		m_Combo = (CComboBox *)GetDlgItem(IDC_COMBO_M20);
		nItem = m_Combo->GetCount();
		while(nItem)
		{
			m_Combo->DeleteString(--nItem);
		}
		m_Combo->AddString("0. 水");
		m_Combo->AddString("1. 海水");
		m_Combo->AddString("2. 煤油");
		m_Combo->AddString("3. 汽油");
		m_Combo->AddString("4. 燃料油");
		m_Combo->AddString("5. 原油");
		m_Combo->AddString("6. 丙烷（-45度）");
		m_Combo->AddString("7. 0度丁烷");
		m_Combo->AddString("8. 其他");
		m_Combo->AddString("9. 柴油");
		m_Combo->AddString("10. 蓖麻油");
		m_Combo->AddString("11. 花生油");
		m_Combo->AddString("12. 90号汽油");
		m_Combo->AddString("13. 93号汽油");
		m_Combo->AddString("14. 酒精");
		m_Combo->AddString("15. 125度高温水");
		GetDlgItem(IDC_M30)->SetWindowText("公英制测量单位");
		GetDlgItem(IDC_RADIO1)->SetWindowText("公制");
		GetDlgItem(IDC_RADIO2)->SetWindowText("英制");
		GetDlgItem(IDC_M31)->SetWindowText("瞬时流量单位");
		m_Combo = (CComboBox *)GetDlgItem(IDC_COMBO_M31_1);
		nItem = m_Combo->GetCount();
		while(nItem)
		{
			m_Combo->DeleteString(--nItem);
		}
		m_Combo->AddString("立方米（m3）");
		m_Combo->AddString("公升（L）");
		m_Combo->AddString("美制加仑（GAL）");
		m_Combo->AddString("英制加仑（IGL）");
		m_Combo->AddString("美制兆加仑（MGL）");
		m_Combo->AddString("立方英尺（CF）");
		m_Combo->AddString("美制石油桶[42]（OB）");
		m_Combo->AddString("英制石油桶（IB）");
		m_Combo = (CComboBox *)GetDlgItem(IDC_COMBO_M31_2);
		nItem = m_Combo->GetCount();
		while(nItem)
		{
			m_Combo->DeleteString(--nItem);
		}
		m_Combo->AddString("每秒（s）");
		m_Combo->AddString("每分（m）");
		m_Combo->AddString("每时（h）");
		m_Combo->AddString("每天（d）");
		GetDlgItem(IDC_M32)->SetWindowText("累积流量单位");
		m_Combo = (CComboBox *)GetDlgItem(IDC_COMBO_M32);
		nItem = m_Combo->GetCount();
		while(nItem)
		{
			m_Combo->DeleteString(--nItem);
		}
		m_Combo->AddString("立方米（m3）");
		m_Combo->AddString("公升（L）");
		m_Combo->AddString("美制加仑（GAL）");
		m_Combo->AddString("英制加仑（IGL）");
		m_Combo->AddString("美制兆加仑（MGL）");
		m_Combo->AddString("立方英尺（CF）");
		m_Combo->AddString("美制石油桶[42]（OB）");
		m_Combo->AddString("英制石油桶（IB）");
		GetDlgItem(IDC_M33)->SetWindowText("累积倍乘因子");
		m_Combo = (CComboBox *)GetDlgItem(IDC_COMBO_M33);
		nItem = m_Combo->GetCount();
		while(nItem)
		{
			m_Combo->DeleteString(--nItem);
		}
		m_Combo->AddString("0. x0.001(1E-3)");
		m_Combo->AddString("1. x0.01");
		m_Combo->AddString("2. x0.1");
		m_Combo->AddString("3. x1");
		m_Combo->AddString("4. x10");
		m_Combo->AddString("5. x100");
		m_Combo->AddString("6. x1000");
		m_Combo->AddString("7. x10000(1E+4)");
		GetDlgItem(IDC_M34)->SetWindowText("净累积器开关");
		GetDlgItem(IDC_RADIO3)->SetWindowText("开(ON)");
		GetDlgItem(IDC_RADIO4)->SetWindowText("关(OFF)");
		GetDlgItem(IDC_M35)->SetWindowText("正累积器开关");
		GetDlgItem(IDC_RADIO5)->SetWindowText("开(ON)");
		GetDlgItem(IDC_RADIO6)->SetWindowText("关(OFF)");
		GetDlgItem(IDC_M36)->SetWindowText("负累积器开关");
		GetDlgItem(IDC_RADIO7)->SetWindowText("开(ON)");
		GetDlgItem(IDC_RADIO8)->SetWindowText("关(OFF)");
		GetDlgItem(IDC_M37)->SetWindowText("累积器清零");
		GetDlgItem(IDC_RADIO9)->SetWindowText("不(NO)");
		GetDlgItem(IDC_RADIO10)->SetWindowText("是(YES)");
		GetDlgItem(IDC_OK)->SetWindowText("确认");
		GetDlgItem(IDC_STATIC5)->SetWindowText("欲清零的累积器");
		m_Combo = (CComboBox *)GetDlgItem(IDC_COMBO_M37);
		nItem = m_Combo->GetCount();
		while(nItem)
		{
			m_Combo->DeleteString(--nItem);
		}
		m_Combo->AddString("=====不清除=====");
		m_Combo->AddString(" 所有累积器清零");
		m_Combo->AddString("   净累积器");
		m_Combo->AddString("   正累积器");
		m_Combo->AddString("   负累积器");
		m_Combo->AddString("  热量净累积器");
		GetDlgItem(IDC_M40)->SetWindowText("阻尼系数");
		GetDlgItem(IDC_M79)->SetWindowText("继电器输出");
		m_Combo = (CComboBox *)GetDlgItem(IDC_COMBO_M79);
		nItem = m_Combo->GetCount();
		while(nItem)
		{
			m_Combo->DeleteString(--nItem);
		}
		m_Combo->AddString("0. 无信号时报警");
		m_Combo->AddString("1. 信号变差时报警");
		m_Combo->AddString("2. 测量状态不正常");
		m_Combo->AddString("3. 反向流动时报警");
		m_Combo->AddString("4. 模拟输出越限100%");
		m_Combo->AddString("5. 频率输出越限120%");
		m_Combo->AddString("6. #1报警器超上下限");
		m_Combo->AddString("7. #2报警器未超限");
		m_Combo->AddString("8. 作为定量器输出");
		m_Combo->AddString("9. 正累积脉冲输出");
		m_Combo->AddString("10. 负累积脉冲输出");
		m_Combo->AddString("11. 净累积脉冲输出");
		m_Combo->AddString("12. 正热量累积脉冲");
		m_Combo->AddString("13. 负热量累积脉冲");
		m_Combo->AddString("14. 净热量累积脉冲");
		m_Combo->AddString("15. 流体声速=>阈值");
		m_Combo->AddString("16. 流体声速<阈值");
		m_Combo->AddString("17. 串口控制通断");
		m_Combo->AddString("18. 每天一次M51定时");
		m_Combo->AddString("19. 定时的#1报警器");
		m_Combo->AddString("20. 定时的#2报警器");
		m_Combo->AddString("21. 定量控制器积满");
		m_Combo->AddString("22. M51定时周期输出");
		m_Combo->AddString("23. 定量器90%已满");
		m_Combo->AddString("24. 关闭继电器输出");
		GetDlgItem(IDC_QUICK_SET)->SetWindowText("一键设置");
		GetDlgItem(IDC_STATIC_CHOSE)->SetWindowText("选择表");
		GetDlgItem(IDC_M23)->SetWindowText("传感器类型");
		m_Combo = (CComboBox *)GetDlgItem(IDC_COMBO_M23);
		nItem = m_Combo->GetCount();
		while(nItem)
		{
			m_Combo->DeleteString(--nItem);
		}	
		m_Combo->AddString("0. 标准中性探头-M");
		m_Combo->AddString("1. 插入探头-C型");
		m_Combo->AddString("2. 标准小型探头-S");
		m_Combo->AddString("3. 用户自备探头");
		m_Combo->AddString("4. 标准 B型探头");
		m_Combo->AddString("5. 插入探头-B型");
		m_Combo->AddString("6. 标准大型探头-L");
		m_Combo->AddString("7. 宝利声标准探头");
		m_Combo->AddString("8. 标准HS小支架探头");
		m_Combo->AddString("9. 标准HM中支架探头");
		m_Combo->AddString("10. 标准M1型中探头");
		m_Combo->AddString("11. 标准S1型小探头");
		m_Combo->AddString("12. 标准L1型大探头");
		m_Combo->AddString("13. PI型管水表探头");
		m_Combo->AddString("14. FS410（中型）");
		m_Combo->AddString("15. FS510（大型）");
		m_Combo->AddString("16. 夹装中探头TM-1");
		m_Combo->AddString("17. 插入探头TC-1");
		m_Combo->AddString("18. 夹装小探头TS-1");
		m_Combo->AddString("19. 夹装小探头TS-2");
		m_Combo->AddString("20. 夹装大探头TL-1");
		m_Combo->AddString("21. 插入探头TLC-2");
		m_Combo->AddString("22. 外夹装中探头M2");
		m_Combo->AddString("23. 外夹装大探头L2");
		GetDlgItem(IDC_M23_1)->SetWindowText("探头声楔角度 ");
		GetDlgItem(IDC_M23_2)->SetWindowText("探头声楔声速");
		GetDlgItem(IDC_M23_3)->SetWindowText("探头声楔总距离");
		GetDlgItem(IDC_M23_4)->SetWindowText("探头声楔延迟时间");
		GetDlgItem(IDC_M24)->SetWindowText("传感器工作频率");
		GetDlgItem(IDC_M25)->SetWindowText("传感器安装方法");	
		m_Combo = (CComboBox *)GetDlgItem(IDC_COMBO_M25);
		nItem = m_Combo->GetCount();
		while(nItem)
		{
			m_Combo->DeleteString(--nItem);
		}	
		m_Combo->AddString("V法安装");
		m_Combo->AddString("Z法安装");
		m_Combo->AddString("N法小管道安装");
		m_Combo->AddString("W法小管道安装");
		GetDlgItem(IDC_M45)->SetWindowText("标尺因子，仪表系数");
		GetDlgItem(IDC_M48)->SetWindowText("流量修正折线数组");
		GetDlgItem(IDC_COPY)->SetWindowText("拷贝");
		GetDlgItem(IDC_QUICK_SET2)->SetWindowText("一键设置");
		GetDlgItem(IDC_PASTE)->SetWindowText("粘贴");
		GetDlgItem(IDC_MULSET)->SetWindowText("多表设置");
		//g_Font = new CFont;       
		//g_Font->CreatePointFont(90, "宋体");
		//::EnumChildWindows(m_hWnd, ::SetChildFont, (LPARAM)g_Font);	
	}
	else
	{
		lf.lfHeight = 20;                 
		strcpy(lf.lfFaceName, "Times New Roman");
		if (g_font.m_hObject)
			g_font.DeleteObject();
		g_font.CreateFontIndirect(&lf);

		GetDlgItem(IDC_STATIC_COMSET)->SetFont(&g_font);
		GetDlgItem(IDC_STATIC_COMSET)->SetWindowText("Common Settings for All connected meters");

		GetDlgItem(IDC_STATIC_INDSET)->SetFont(&g_font);
		GetDlgItem(IDC_STATIC_INDSET)->SetWindowText("Individual Settings");

		lf.lfHeight = 15;
		strcpy(lf.lfFaceName, "Times New Roman");
		if (g_font.m_hObject)
			g_font.DeleteObject();
		g_font.CreateFontIndirect(&lf);

		GetDlgItem(IDC_PASTE)->SetFont(&g_font);
		GetDlgItem(IDC_PASTE)->SetWindowText("Paste");

		GetDlgItem(IDC_MULSET)->SetFont(&g_font);
		GetDlgItem(IDC_MULSET)->SetWindowText("Multi settings");
		this->SetWindowText("Setup");

		GetDlgItem(IDC_M11)->SetFont(&g_font);
		GetDlgItem(IDC_M11)->SetWindowText("Pipe Outer Diameter");

		GetDlgItem(IDC_M12)->SetFont(&g_font);
		GetDlgItem(IDC_M12)->SetWindowText("Pipe Wall Thickness");

		GetDlgItem(IDC_M13)->SetFont(&g_font);
		GetDlgItem(IDC_M13)->SetWindowText("Pipe Inner Diameter");

		GetDlgItem(IDC_M14)->SetFont(&g_font);
		GetDlgItem(IDC_M14)->SetWindowText("Pipe Material");

		GetDlgItem(IDC_COMBO_M14)->SetFont(&g_font);
		CComboBox *m_Combo = (CComboBox *)GetDlgItem(IDC_COMBO_M14);
		int nItem = m_Combo->GetCount();
		while(nItem)
		{
			m_Combo->DeleteString(--nItem);
		}
		m_Combo->AddString("0. Carbon Stee1");
		m_Combo->AddString("1. Stainless Stee1");
		m_Combo->AddString("2. Cast Iron");
		m_Combo->AddString("3. Ductile Iron");
		m_Combo->AddString("4. Copper");
		m_Combo->AddString("5. PVC");
		m_Combo->AddString("6. Aluminium");
		m_Combo->AddString("7. Asbestos");
		m_Combo->AddString("8. FiberGlass-Epoxy");
		m_Combo->AddString("9. Other");

		GetDlgItem(IDC_M16)->SetFont(&g_font);
		GetDlgItem(IDC_M16)->SetWindowText("Liner Material");

		GetDlgItem(IDC_COMBO_M16)->SetFont(&g_font);
		m_Combo = (CComboBox *)GetDlgItem(IDC_COMBO_M16);
		nItem = m_Combo->GetCount();
		while(nItem)
		{
			m_Combo->DeleteString(--nItem);
		}
		m_Combo->AddString("0. None,No Liner");
		m_Combo->AddString("1. Tar Epoxy");
		m_Combo->AddString("2. Rubber");
		m_Combo->AddString("3. Mortar");
		m_Combo->AddString("4. Polyropylene");
		m_Combo->AddString("5. Polystyrol");
		m_Combo->AddString("6. Polystyrene");
		m_Combo->AddString("7. Polyester");
		m_Combo->AddString("8. Polyethylene");
		m_Combo->AddString("9. Ebonite");
		m_Combo->AddString("10. Teflon");
		m_Combo->AddString("11. Other");
		GetDlgItem(IDC_M18)->SetFont(&g_font);
		GetDlgItem(IDC_M18)->SetWindowText("Liner Thickness");

		GetDlgItem(IDC_M20)->SetFont(&g_font);
		GetDlgItem(IDC_M20)->SetWindowText("Fluid Type");

		GetDlgItem(IDC_COMBO_M20)->SetFont(&g_font);
		m_Combo = (CComboBox *)GetDlgItem(IDC_COMBO_M20);
		nItem = m_Combo->GetCount();
		while(nItem)
		{
			m_Combo->DeleteString(--nItem);
		}
		m_Combo->AddString("0. Water(General)");
		m_Combo->AddString("1. Sea Water");
		m_Combo->AddString("2. Kerosene");
		m_Combo->AddString("3. Gasoline");
		m_Combo->AddString("4. Fuel Oil");
		m_Combo->AddString("5. Crude Oil");
		m_Combo->AddString("6. Propane(-45C)");
		m_Combo->AddString("7. Butane(0C)");
		m_Combo->AddString("8. Other Liquid");
		m_Combo->AddString("9. Diesel Oil");
		m_Combo->AddString("10. Castor Oil");
		m_Combo->AddString("11. Peanut Oil");
		m_Combo->AddString("12. Gasoline #90");
		m_Combo->AddString("13. Gasoline #93");
		m_Combo->AddString("14. Alcohol");
		m_Combo->AddString("15. Water(125C)");

		GetDlgItem(IDC_M30)->SetFont(&g_font);
		GetDlgItem(IDC_M30)->SetWindowText("Measurement Units");

		GetDlgItem(IDC_RADIO1)->SetFont(&g_font);
		GetDlgItem(IDC_RADIO1)->SetWindowText("Metric");

		GetDlgItem(IDC_RADIO2)->SetFont(&g_font);
		GetDlgItem(IDC_RADIO2)->SetWindowText("English");

		GetDlgItem(IDC_M31)->SetFont(&g_font);
		GetDlgItem(IDC_M31)->SetWindowText("Flow Rate Unit");

		GetDlgItem(IDC_COMBO_M31_1)->SetFont(&g_font);
		m_Combo = (CComboBox *)GetDlgItem(IDC_COMBO_M31_1);
		nItem = m_Combo->GetCount();
		while(nItem)
		{
			m_Combo->DeleteString(--nItem);
		}
		m_Combo->AddString("Cubic Meter  (m3)");
		m_Combo->AddString("Liter        (l)");
		m_Combo->AddString("US Gallon    (Gal)");
		m_Combo->AddString("UK Gallon    (IGL)");
		m_Combo->AddString("Million US Gallon");
		m_Combo->AddString("Cubic Feet   (CF)");
		m_Combo->AddString("US Oil Barrel(OB)");
		m_Combo->AddString("UK Oil Barrel(IB)");

		GetDlgItem(IDC_COMBO_M31_2)->SetFont(&g_font);
		m_Combo = (CComboBox *)GetDlgItem(IDC_COMBO_M31_2);
		nItem = m_Combo->GetCount();
		while(nItem)
		{
			m_Combo->DeleteString(--nItem);
		}
		m_Combo->AddString("sec");
		m_Combo->AddString("min");
		m_Combo->AddString("hour");
		m_Combo->AddString("day");
		GetDlgItem(IDC_M32)->SetFont(&g_font);
		GetDlgItem(IDC_M32)->SetWindowText("Totalizer Units");
		GetDlgItem(IDC_COMBO_M32)->SetFont(&g_font);
		m_Combo = (CComboBox *)GetDlgItem(IDC_COMBO_M32);
		nItem = m_Combo->GetCount();
		while(nItem)
		{
			m_Combo->DeleteString(--nItem);
		}
		m_Combo->AddString("Cubic Meter  (m3)");
		m_Combo->AddString("Liter        (l)");
		m_Combo->AddString("US Gallon    (Gal)");
		m_Combo->AddString("UK Gallon    (IGL)");
		m_Combo->AddString("Million US Gallon");
		m_Combo->AddString("Cubic Feet   (CF)");
		m_Combo->AddString("US Oil Barrel(OB)");
		m_Combo->AddString("UK Oil Barrel(IB)");
		GetDlgItem(IDC_M33)->SetFont(&g_font);
		GetDlgItem(IDC_M33)->SetWindowText("Totalizer Multiplier");
		GetDlgItem(IDC_COMBO_M33)->SetFont(&g_font);
		m_Combo = (CComboBox *)GetDlgItem(IDC_COMBO_M33);
		nItem = m_Combo->GetCount();
		while(nItem)
		{
			m_Combo->DeleteString(--nItem);
		}
		m_Combo->AddString("0. x0.001(1E-3)");
		m_Combo->AddString("1. x0.01");
		m_Combo->AddString("2. x0.1");
		m_Combo->AddString("3. x1");
		m_Combo->AddString("4. x10");
		m_Combo->AddString("5. x100");
		m_Combo->AddString("6. x1000");
		m_Combo->AddString("7. x10000(1E+4)");
		GetDlgItem(IDC_M34)->SetFont(&g_font);
		GetDlgItem(IDC_M34)->SetWindowText("NET Totalizer");

		GetDlgItem(IDC_RADIO3)->SetFont(&g_font);
		GetDlgItem(IDC_RADIO3)->SetWindowText("ON");

		GetDlgItem(IDC_RADIO4)->SetFont(&g_font);
		GetDlgItem(IDC_RADIO4)->SetWindowText("OFF");

		GetDlgItem(IDC_M35)->SetFont(&g_font);
		GetDlgItem(IDC_M35)->SetWindowText("POS Totalizer");

		GetDlgItem(IDC_RADIO5)->SetFont(&g_font);
		GetDlgItem(IDC_RADIO5)->SetWindowText("ON");

		GetDlgItem(IDC_RADIO6)->SetFont(&g_font);
		GetDlgItem(IDC_RADIO6)->SetWindowText("OFF");

		GetDlgItem(IDC_M36)->SetFont(&g_font);
		GetDlgItem(IDC_M36)->SetWindowText("NEG Totalizer");

		GetDlgItem(IDC_RADIO7)->SetFont(&g_font);
		GetDlgItem(IDC_RADIO7)->SetWindowText("ON");

		GetDlgItem(IDC_RADIO8)->SetFont(&g_font);
		GetDlgItem(IDC_RADIO8)->SetWindowText("OFF");

		GetDlgItem(IDC_M37)->SetFont(&g_font);
		GetDlgItem(IDC_M37)->SetWindowText("Totalizer Reset");

		GetDlgItem(IDC_RADIO9)->SetFont(&g_font);
		GetDlgItem(IDC_RADIO9)->SetWindowText("NO");

		GetDlgItem(IDC_RADIO10)->SetFont(&g_font);
		GetDlgItem(IDC_RADIO10)->SetWindowText("YES");

		GetDlgItem(IDC_OK)->SetFont(&g_font);
		GetDlgItem(IDC_OK)->SetWindowText("OK");

		GetDlgItem(IDC_COMBO_M37)->SetFont(&g_font);
		m_Combo = (CComboBox *)GetDlgItem(IDC_COMBO_M37);
		nItem = m_Combo->GetCount();
		while(nItem)
		{
			m_Combo->DeleteString(--nItem);
		}
		m_Combo->AddString("None");
		m_Combo->AddString("All");
		m_Combo->AddString("NET Totalizer");
		m_Combo->AddString("POS Totalizer");
		m_Combo->AddString("NEG Totalizer");
		m_Combo->AddString("Energy NET Totalizer");

		GetDlgItem(IDC_STATIC5)->SetFont(&g_font);
		GetDlgItem(IDC_STATIC5)->SetWindowText("Select Totalizer");

		GetDlgItem(IDC_M40)->SetFont(&g_font);
		GetDlgItem(IDC_M40)->SetWindowText("Damping Factor");

		GetDlgItem(IDC_M79)->SetFont(&g_font);
		GetDlgItem(IDC_M79)->SetWindowText("RELAY Output Setup");

		GetDlgItem(IDC_COMBO_M79)->SetFont(&g_font);
		m_Combo = (CComboBox *)GetDlgItem(IDC_COMBO_M79);
		nItem = m_Combo->GetCount();
		while(nItem)
		{
			m_Combo->DeleteString(--nItem);
		}
		m_Combo->AddString("0. No Signal");
		m_Combo->AddString("1. Poor Signal");
		m_Combo->AddString("2. Not Ready(No *R)");
		m_Combo->AddString("3. Reverse Flow");
		m_Combo->AddString("4. AO Over 100%");
		m_Combo->AddString("5. FO Over 120%");
		m_Combo->AddString("6. Alarm #1");
		m_Combo->AddString("7. Reverse Alarm #2");
		m_Combo->AddString("8. Batch Controller");
		m_Combo->AddString("9. POS Int Pulse");
		m_Combo->AddString("10. NEG Int Pulse");
		m_Combo->AddString("11. NET Int Pulse");
		m_Combo->AddString("12. Energy POS Pulse");
		m_Combo->AddString("13. Energy NEG Pulse");
		m_Combo->AddString("14. Energy NET Pulse");
		m_Combo->AddString("15. MediaVel=>Thresh");
		m_Combo->AddString("16. MediaVelo<Thresh");
		m_Combo->AddString("17. ON/OFF via RS485");
		m_Combo->AddString("18. Timer(M51 Daily)");
		m_Combo->AddString("19. Timed Alarm #1");
		m_Combo->AddString("20. Timed Alarm #2");
		m_Combo->AddString("21. Batch total Full");
		m_Combo->AddString("22. Timer by M51");
		m_Combo->AddString("23. Batch 90% Full");
		m_Combo->AddString("24. Disable Relay");
		GetDlgItem(IDC_QUICK_SET)->SetFont(&g_font);
		GetDlgItem(IDC_QUICK_SET)->SetWindowText("Hotkey Setup");

		GetDlgItem(IDC_STATIC_CHOSE)->SetFont(&g_font);
		GetDlgItem(IDC_STATIC_CHOSE)->SetWindowText("S/N + IDN");

		GetDlgItem(IDC_M23)->SetFont(&g_font);
		GetDlgItem(IDC_M23)->SetWindowText("Transducer Type");

		GetDlgItem(IDC_COMBO_M23)->SetFont(&g_font);
		m_Combo = (CComboBox *)GetDlgItem(IDC_COMBO_M23);
		nItem = m_Combo->GetCount();
		while(nItem)
		{
			m_Combo->DeleteString(--nItem);
		}	
		m_Combo->AddString("0. Standard-M");
		m_Combo->AddString("1. Insertion Type");
		m_Combo->AddString("2. Standard-S");
		m_Combo->AddString("3. User Type");
		m_Combo->AddString("4. Standard-B");
		m_Combo->AddString("5. Insertion B(45)");
		m_Combo->AddString("6. Standard-L");
		m_Combo->AddString("7. JH-Polysonics");
		m_Combo->AddString("8. Standard-HS");
		m_Combo->AddString("9. Standard-HM");
		m_Combo->AddString("10. Standard-M1");
		m_Combo->AddString("11. Standard-S1");
		m_Combo->AddString("12. Standard-L1");
		m_Combo->AddString("13. PI-Type");
		m_Combo->AddString("14. FS410(FUJI)");
		m_Combo->AddString("15. FS510(FUJI)");
		m_Combo->AddString("16. Clamp-on TM-1");
		m_Combo->AddString("17. Insertion TC-1");
		m_Combo->AddString("18. Clamp-On TS-1");
		m_Combo->AddString("19. Clamp-On TS-2");
		m_Combo->AddString("20. Clamp-On TL-1");
		m_Combo->AddString("21. Insertion TLC-2");
		m_Combo->AddString("22. Clamp-On M2");
		m_Combo->AddString("23. Clamp-On L2");
		//user define type please look at the Trancducer Configuration
		m_Combo->AddString("24. TWC-HF0"); 
		m_Combo->AddString("25. TWC-HF1");
		m_Combo->AddString("26. TWC-HF2");
		m_Combo->AddString("27. TWC-HF3");
		m_Combo->AddString("28. TWC-HF4");
		m_Combo->AddString("29. TWC-HF5");
		m_Combo->AddString("30. TWC-HF6");
		m_Combo->AddString("31. TWC-RS2");
		m_Combo->AddString("32. TWC-RM");
		m_Combo->AddString("33. TWC-LF");
		m_Combo->AddString("34. TWC-HF0HT");


		GetDlgItem(IDC_M23_1)->SetFont(&g_font);
		GetDlgItem(IDC_M23_1)->SetWindowText("Wedge Degree");

		GetDlgItem(IDC_M23_2)->SetFont(&g_font);
		GetDlgItem(IDC_M23_2)->SetWindowText("Wedge Sound Velocity");

		GetDlgItem(IDC_M23_3)->SetFont(&g_font);
		GetDlgItem(IDC_M23_3)->SetWindowText("Wedge Distance");

		GetDlgItem(IDC_M23_4)->SetFont(&g_font);
		GetDlgItem(IDC_M23_4)->SetWindowText("Wedge Time Delay");

		GetDlgItem(IDC_M24)->SetFont(&g_font);
		GetDlgItem(IDC_M24)->SetWindowText("Transducer Frequency");
		GetDlgItem(IDC_EDIT_M45)->SetFont(&g_font);

		GetDlgItem(IDC_M25)->SetFont(&g_font);
		GetDlgItem(IDC_M25)->SetWindowText("Transducer Mounting");

		GetDlgItem(IDC_STATIC)->SetFont(&g_font);

		GetDlgItem(IDC_COMBO_M25)->SetFont(&g_font);
		m_Combo = (CComboBox *)GetDlgItem(IDC_COMBO_M25);
		nItem = m_Combo->GetCount();
		while(nItem)
		{
			m_Combo->DeleteString(--nItem);
		}	
		m_Combo->AddString("V Method");
		m_Combo->AddString("Z Method");
		m_Combo->AddString("N (small pipe)");
		m_Combo->AddString("W (small pipe)");

		GetDlgItem(IDC_M45)->SetFont(&g_font);
		GetDlgItem(IDC_M45)->SetWindowText("Scale Factor");

		GetDlgItem(IDC_M48)->SetFont(&g_font);
		GetDlgItem(IDC_M48)->SetWindowText("Entry to Calib,Data");

		GetDlgItem(IDC_COPY)->SetFont(&g_font);
		GetDlgItem(IDC_COPY)->SetWindowText("Copy");

		GetDlgItem(IDC_QUICK_SET2)->SetFont(&g_font);
		GetDlgItem(IDC_QUICK_SET2)->SetWindowText("Hotkey Setup");

	}
	//连接数据库
	
	//m_pAppConn.CreateInstance(__uuidof(Connection));
	//m_pAppConn->Open("File Name=MyData.udl", "", "", adConnectUnspecified);

	try
	{
		HRESULT hr = m_pAppConn.CreateInstance(__uuidof(Connection));
		if (FAILED(hr))
			AfxMessageBox("Can't create an intance of ADO.Connection");

		if (FAILED(m_pAppConn->Open(_bstr_t("File Name=MyData.udl"), _bstr_t(""), _bstr_t(""), adModeUnknown)))
			::AfxMessageBox(TEXT("Can't open datasource"));
		//m_pAppConn->Close();
	}
	catch (_com_error &e)
	{
		::AfxMessageBox(TEXT("I am in catch block 5"));
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
	Log::Logger("CSetDlg::OnInitDialog() the adCmdText is " + adCmdText);

	//公共设置初始化
	((CComboBox *)GetDlgItem(IDC_COMBO_M37))->SetCurSel(0);
	((CButton *)GetDlgItem(IDC_RADIO9))->SetCheck(TRUE);
	
	sql.Format("select * from Common_settings");
	try 
	{	
		m_recordset = m_pAppConn->Execute((_bstr_t)sql,NULL,adCmdText);
		_variant_t var = m_recordset->GetCollect ("pipe_outer_diameter");
		CString cstr =(char *)_bstr_t(var);	 
		cstr.TrimRight();
		float fm11;
		sscanf(cstr, "%f", &fm11);
		m_m11.Format("%g", fm11);
		var = m_recordset->GetCollect ("pipe_wall_thickness");
		cstr =(char *)_bstr_t(var);
		float fm12;
		sscanf(cstr, "%f", &fm12);
		m_m12.Format("%g", fm12);
		var = m_recordset->GetCollect ("pipe_inner_diameter");
		cstr =(char *)_bstr_t(var);
		float fm13;
		sscanf(cstr, "%f", &fm13);
		m_m13.Format("%g", fm13);
		var = m_recordset->GetCollect ("pipe_material");
		cstr =(char *)_bstr_t(var);
		int len = cstr.GetLength();
		if (len == 1)
		{
			int x = cstr.GetAt(0) - '0';
			((CComboBox *)GetDlgItem(IDC_COMBO_M14))->SetCurSel(x);
		}
		else
		{
			int x = (cstr.GetAt(0) - '0') * 10 + (cstr.GetAt(1) - '0');
			((CComboBox *)GetDlgItem(IDC_COMBO_M14))->SetCurSel(x);
		}
		var = m_recordset->GetCollect ("liner_material");
		cstr =(char *)_bstr_t(var);
		len = cstr.GetLength();
		if (len == 1)
		{
			int x = cstr.GetAt(0) - '0';
			((CComboBox *)GetDlgItem(IDC_COMBO_M16))->SetCurSel(x);
		}
		else
		{
			int x = (cstr.GetAt(0) - '0') * 10 + (cstr.GetAt(1) - '0');
			((CComboBox *)GetDlgItem(IDC_COMBO_M16))->SetCurSel(x);
		}
		int iPos;
		sscanf(cstr, "%d", &iPos);
		if (iPos == 0)
		{
			GetDlgItem(IDC_M18)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDIT_M18)->EnableWindow(FALSE);
			m_m18 = "0";
			UpdateData(FALSE);
		}
		else
		{
			GetDlgItem(IDC_M18)->EnableWindow(TRUE);
			GetDlgItem(IDC_EDIT_M18)->EnableWindow(TRUE);
		}
		var = m_recordset->GetCollect ("liner_thickness");
		cstr =(char *)_bstr_t(var);
		float fm18;
		sscanf(cstr, "%f", &fm18);
		m_m18.Format("%g", fm18);
		var = m_recordset->GetCollect ("fluid_type");
		cstr =(char *)_bstr_t(var);
		len = cstr.GetLength();
		if (len == 1)
		{
			int x = cstr.GetAt(0) - '0';
			((CComboBox *)GetDlgItem(IDC_COMBO_M20))->SetCurSel(x);
		}
		else
		{
			int x = (cstr.GetAt(0) - '0') * 10 + (cstr.GetAt(1) - '0');
			((CComboBox *)GetDlgItem(IDC_COMBO_M20))->SetCurSel(x);
		}
		var = m_recordset->GetCollect ("measurement_units");
		cstr =(char *)_bstr_t(var);
		if (cstr == "0")
		{
			((CButton *)GetDlgItem(IDC_RADIO1))->SetCheck(TRUE);
		}
		else
		{
			((CButton *)GetDlgItem(IDC_RADIO2))->SetCheck(TRUE);
		}
		
		var = m_recordset->GetCollect ("flow_rate_unit");
		cstr =(char *)_bstr_t(var);
		((CComboBox *)GetDlgItem(IDC_COMBO_M31_1))->SetCurSel(cstr.GetAt(0) - '0');
		((CComboBox *)GetDlgItem(IDC_COMBO_M31_2))->SetCurSel(cstr.GetAt(2) - '0');
		var = m_recordset->GetCollect ("totalizer_units");
		cstr =(char *)_bstr_t(var);
		len = cstr.GetLength();
		if (len == 1)
		{
			int x = cstr.GetAt(0) - '0';
			((CComboBox *)GetDlgItem(IDC_COMBO_M32))->SetCurSel(x);
		}
		else
		{
			int x = (cstr.GetAt(0) - '0') * 10 + (cstr.GetAt(1) - '0');
			((CComboBox *)GetDlgItem(IDC_COMBO_M32))->SetCurSel(x);
		}
		var = m_recordset->GetCollect ("totalizer_multiplier");
		cstr =(char *)_bstr_t(var);
		len = cstr.GetLength();
		if (len == 1)
		{
			int x = cstr.GetAt(0) - '0';
			((CComboBox *)GetDlgItem(IDC_COMBO_M33))->SetCurSel(x);
		}
		else
		{
			int x = (cstr.GetAt(0) - '0') * 10 + (cstr.GetAt(1) - '0');
			((CComboBox *)GetDlgItem(IDC_COMBO_M33))->SetCurSel(x);
		}
		var = m_recordset->GetCollect ("net_toalizer");
		cstr =(char *)_bstr_t(var);
		if (cstr == "0")
		{
			((CButton *)GetDlgItem(IDC_RADIO4))->SetCheck(TRUE);
		}
		else
		{
			((CButton *)GetDlgItem(IDC_RADIO3))->SetCheck(TRUE);
		}
		var = m_recordset->GetCollect ("pos_totalizer");
		cstr =(char *)_bstr_t(var);
		if (cstr == "0")
		{
			((CButton *)GetDlgItem(IDC_RADIO6))->SetCheck(TRUE);
		}
		else
		{
			((CButton *)GetDlgItem(IDC_RADIO5))->SetCheck(TRUE);
		}
		var = m_recordset->GetCollect ("neg_totalizer");
		cstr =(char *)_bstr_t(var);
		if (cstr == "0")
		{
			((CButton *)GetDlgItem(IDC_RADIO8))->SetCheck(TRUE);
		}
		else
		{
			((CButton *)GetDlgItem(IDC_RADIO7))->SetCheck(TRUE);
		}
		var = m_recordset->GetCollect ("Language_LINGUA");
		cstr =(char *)_bstr_t(var);
		len = cstr.GetLength();
		if (len == 1)
		{
			int x = cstr.GetAt(0) - '0';
			((CComboBox *)GetDlgItem(IDC_COMBO_M39))->SetCurSel(x);
		}
		else
		{
			int x = (cstr.GetAt(0) - '0') * 10 + (cstr.GetAt(1) - '0');
			((CComboBox *)GetDlgItem(IDC_COMBO_M39))->SetCurSel(x);
		}
		var = m_recordset->GetCollect ("damping_factor");
		cstr =(char *)_bstr_t(var);
		m_m40 = cstr;
		var = m_recordset->GetCollect ("relay_output_setup");
		cstr =(char *)_bstr_t(var);
		len = cstr.GetLength();
		if (len == 1)
		{
			int x = cstr.GetAt(0) - '0';
			((CComboBox *)GetDlgItem(IDC_COMBO_M79))->SetCurSel(x);
		}
		else
		{
			int x = (cstr.GetAt(0) - '0') * 10 + (cstr.GetAt(1) - '0');
			((CComboBox *)GetDlgItem(IDC_COMBO_M79))->SetCurSel(x);
		}
		UpdateData(FALSE);
	}
	catch(_com_error e)
	{
		AfxMessageBox(e.ErrorMessage());
	}
	if(IsDlgButtonChecked(IDC_RADIO1))
	{
		GetDlgItem(IDC_STATIC1)->SetWindowText("mm");
		GetDlgItem(IDC_STATIC2)->SetWindowText("mm");
		GetDlgItem(IDC_STATIC3)->SetWindowText("mm");
		GetDlgItem(IDC_STATIC4)->SetWindowText("mm");
		GetDlgItem(IDC_STATIC00)->SetWindowText("m/s");
		GetDlgItem(IDC_STATIC01)->SetWindowText("mm");
	}
	else if(IsDlgButtonChecked(IDC_RADIO2))
	{
		GetDlgItem(IDC_STATIC1)->SetWindowText("in");
		GetDlgItem(IDC_STATIC2)->SetWindowText("in");
		GetDlgItem(IDC_STATIC3)->SetWindowText("in");
		GetDlgItem(IDC_STATIC4)->SetWindowText("in");
		GetDlgItem(IDC_STATIC00)->SetWindowText("f/s");
		GetDlgItem(IDC_STATIC01)->SetWindowText("in");
	}

	//独立设置初始化
	sql.Format("select * from Independent_settings");
	try
	{
		m_recordset = m_pAppConn->Execute((_bstr_t)sql,NULL,adCmdText);
		_variant_t var;
		CString cstr1;    //得到netword_IDN
		CString cstr2;    //得到s_n
		CString cstr3;    //str1 + str2 
		if (!m_recordset->adoEOF)
		{
			m_recordset->MoveFirst();
		}
		else
		{
			if (app->language == 0)
			{
				AfxMessageBox("没有搜索到表!");
			}
			else
			{
				hHook=SetWindowsHookEx(WH_CBT,(HOOKPROC)CBTHookProc,AfxGetInstanceHandle(),NULL); 
				AfxMessageBox("No search to the meter!");

			}
		}
		while(!m_recordset->adoEOF)
		{
			var = m_recordset->GetCollect("netword_IDN");
			if (var.vt != VT_NULL)
			{
				cstr1 =(char *)_bstr_t(var);
			}
			var = m_recordset->GetCollect("s_n");
			if (var.vt != VT_NULL)
			{
				cstr2 =(char *)_bstr_t(var);
			}
			cstr3 = cstr2 + "  " +cstr1;
			((CComboBox *)GetDlgItem(IDC_COMBO_METER))->AddString(cstr3);
			m_recordset->MoveNext();
		}
	}
	catch(_com_error e)
	{
		AfxMessageBox(e.ErrorMessage());
	}
	sql.Format("SELECT * from Logo");
	try
	{
		m_recordset = m_pAppConn->Execute((_bstr_t)sql,NULL,adCmdText);
		_variant_t var = m_recordset->GetCollect("l1");
		CString str = (char *)_bstr_t(var);
		int l1=_ttoi(str);
		((CComboBox *)GetDlgItem(IDC_COMBO_M23))->SetCurSel(l1);
		UpdateData(FALSE);
		if (l1 == 3)
		{
			var = m_recordset->GetCollect("l2");
			str = (char *)_bstr_t(var);
			m_m231 = str;
			var = m_recordset->GetCollect("l3");
			str = (char *)_bstr_t(var);
			m_m232 = str;
			var = m_recordset->GetCollect("l4");
			str = (char *)_bstr_t(var);
			m_m233 = str;
			var = m_recordset->GetCollect("l5");
			str = (char *)_bstr_t(var);
			m_m234 = str;
			UpdateData(FALSE);
			GetDlgItem(IDC_M23_1)->EnableWindow(TRUE);
			GetDlgItem(IDC_M23_2)->EnableWindow(TRUE);
			GetDlgItem(IDC_M23_3)->EnableWindow(TRUE);
			GetDlgItem(IDC_M23_4)->EnableWindow(TRUE);
			GetDlgItem(IDC_EDIT_M23_1)->EnableWindow(TRUE);
			GetDlgItem(IDC_EDIT_M23_1)->SetWindowText("");
			GetDlgItem(IDC_EDIT_M23_2)->EnableWindow(TRUE);
			GetDlgItem(IDC_EDIT_M23_2)->SetWindowText("");
			GetDlgItem(IDC_EDIT_M23_3)->EnableWindow(TRUE);
			GetDlgItem(IDC_EDIT_M23_3)->SetWindowText("");
			GetDlgItem(IDC_EDIT_M23_4)->EnableWindow(TRUE);
			GetDlgItem(IDC_EDIT_M23_4)->SetWindowText("");
			GetDlgItem(IDC_STATIC00)->EnableWindow(TRUE);
			GetDlgItem(IDC_STATIC01)->EnableWindow(TRUE);
			GetDlgItem(IDC_STATIC02)->EnableWindow(TRUE);
			GetDlgItem(IDC_STATIC03)->EnableWindow(TRUE);
		}
		else if (l1 == 26)
		{
			m_m231 = "37";
			m_m232 = "8061.024";
			m_m233 = "0.314961";
			m_m234 = "0.215";

			GetDlgItem(IDC_M23_1)->EnableWindow(FALSE);
			GetDlgItem(IDC_M23_2)->EnableWindow(FALSE);
			GetDlgItem(IDC_M23_3)->EnableWindow(FALSE);
			GetDlgItem(IDC_M23_4)->EnableWindow(FALSE);

			GetDlgItem(IDC_EDIT_M23_1)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDIT_M23_1)->SetWindowText(m_m231);

			GetDlgItem(IDC_EDIT_M23_2)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDIT_M23_2)->SetWindowTextA("8061.024");

			GetDlgItem(IDC_EDIT_M23_3)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDIT_M23_3)->SetWindowText("0.314961");

			GetDlgItem(IDC_EDIT_M23_4)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDIT_M23_4)->SetWindowText("0.215");

			GetDlgItem(IDC_STATIC00)->EnableWindow(FALSE);
			GetDlgItem(IDC_STATIC01)->EnableWindow(FALSE);
			GetDlgItem(IDC_STATIC02)->EnableWindow(FALSE);
			GetDlgItem(IDC_STATIC03)->EnableWindow(FALSE);
		}
		else if (l1 == 27)
		{
			m_m231 = "37";
			m_m232 = "8061.024";
			m_m233 = "0.275591";
			m_m234 = "0.21";

			GetDlgItem(IDC_M23_1)->EnableWindow(FALSE);
			GetDlgItem(IDC_M23_2)->EnableWindow(FALSE);
			GetDlgItem(IDC_M23_3)->EnableWindow(FALSE);
			GetDlgItem(IDC_M23_4)->EnableWindow(FALSE);

			GetDlgItem(IDC_EDIT_M23_1)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDIT_M23_1)->SetWindowText(m_m231);

			GetDlgItem(IDC_EDIT_M23_2)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDIT_M23_2)->SetWindowTextA("8061.024");

			GetDlgItem(IDC_EDIT_M23_3)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDIT_M23_3)->SetWindowText("0.275591");

			GetDlgItem(IDC_EDIT_M23_4)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDIT_M23_4)->SetWindowText("0.21");


			GetDlgItem(IDC_STATIC00)->EnableWindow(FALSE);
			GetDlgItem(IDC_STATIC01)->EnableWindow(FALSE);
			GetDlgItem(IDC_STATIC02)->EnableWindow(FALSE);
			GetDlgItem(IDC_STATIC03)->EnableWindow(FALSE);
		}
		else if (l1 == 28)
		{
			m_m231 = "37";
			m_m232 = "8061.024";
			m_m233 = "0.551181";
			m_m234 = "0.21";

			GetDlgItem(IDC_M23_1)->EnableWindow(FALSE);
			GetDlgItem(IDC_M23_2)->EnableWindow(FALSE);
			GetDlgItem(IDC_M23_3)->EnableWindow(FALSE);
			GetDlgItem(IDC_M23_4)->EnableWindow(FALSE);

			GetDlgItem(IDC_EDIT_M23_1)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDIT_M23_1)->SetWindowText(m_m231);

			GetDlgItem(IDC_EDIT_M23_2)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDIT_M23_2)->SetWindowTextA("8061.024");

			GetDlgItem(IDC_EDIT_M23_3)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDIT_M23_3)->SetWindowText("0.551181");

			GetDlgItem(IDC_EDIT_M23_4)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDIT_M23_4)->SetWindowText("0.21");

			GetDlgItem(IDC_STATIC00)->EnableWindow(FALSE);
			GetDlgItem(IDC_STATIC01)->EnableWindow(FALSE);
			GetDlgItem(IDC_STATIC02)->EnableWindow(FALSE);
			GetDlgItem(IDC_STATIC03)->EnableWindow(FALSE);
		}
		else if (l1 == 29)
		{
			m_m231 = "37";
			m_m232 = "8061.024";
			m_m233 = "0.314961";
			m_m234 = "0.214";

			GetDlgItem(IDC_M23_1)->EnableWindow(FALSE);
			GetDlgItem(IDC_M23_2)->EnableWindow(FALSE);
			GetDlgItem(IDC_M23_3)->EnableWindow(FALSE);
			GetDlgItem(IDC_M23_4)->EnableWindow(FALSE);

			GetDlgItem(IDC_EDIT_M23_1)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDIT_M23_1)->SetWindowText(m_m231);

			GetDlgItem(IDC_EDIT_M23_2)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDIT_M23_2)->SetWindowTextA("8061.024");

			GetDlgItem(IDC_EDIT_M23_3)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDIT_M23_3)->SetWindowText("0.314961");

			GetDlgItem(IDC_EDIT_M23_4)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDIT_M23_4)->SetWindowText("0.214");

			GetDlgItem(IDC_STATIC00)->EnableWindow(FALSE);
			GetDlgItem(IDC_STATIC01)->EnableWindow(FALSE);
			GetDlgItem(IDC_STATIC02)->EnableWindow(FALSE);
			GetDlgItem(IDC_STATIC03)->EnableWindow(FALSE);
		}
		else if (l1 == 30)
		{
			m_m231 = "38";
			m_m232 = "7765.75";
			m_m233 = "0.866142";
			m_m234 = "0.18";

			GetDlgItem(IDC_M23_1)->EnableWindow(FALSE);
			GetDlgItem(IDC_M23_2)->EnableWindow(FALSE);
			GetDlgItem(IDC_M23_3)->EnableWindow(FALSE);
			GetDlgItem(IDC_M23_4)->EnableWindow(FALSE);


			GetDlgItem(IDC_EDIT_M23_1)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDIT_M23_1)->SetWindowText(m_m231);

			GetDlgItem(IDC_EDIT_M23_2)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDIT_M23_2)->SetWindowTextA("7765.75");

			GetDlgItem(IDC_EDIT_M23_3)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDIT_M23_3)->SetWindowText("0.866142");

			GetDlgItem(IDC_EDIT_M23_4)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDIT_M23_4)->SetWindowText("0.18");

			GetDlgItem(IDC_STATIC00)->EnableWindow(FALSE);
			GetDlgItem(IDC_STATIC01)->EnableWindow(FALSE);
			GetDlgItem(IDC_STATIC02)->EnableWindow(FALSE);
			GetDlgItem(IDC_STATIC03)->EnableWindow(FALSE);
		}
		else if (l1 == 31)
		{
			m_m231 = "38";
			m_m232 = "7447.51";
			m_m233 = "0.842520";
			m_m234 = "0.164";

			GetDlgItem(IDC_M23_1)->EnableWindow(FALSE);
			GetDlgItem(IDC_M23_2)->EnableWindow(FALSE);
			GetDlgItem(IDC_M23_3)->EnableWindow(FALSE);
			GetDlgItem(IDC_M23_4)->EnableWindow(FALSE);

			GetDlgItem(IDC_EDIT_M23_1)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDIT_M23_1)->SetWindowText(m_m231);

			GetDlgItem(IDC_EDIT_M23_2)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDIT_M23_2)->SetWindowTextA("7447.51");

			GetDlgItem(IDC_EDIT_M23_3)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDIT_M23_3)->SetWindowText("0.842520");

			GetDlgItem(IDC_EDIT_M23_4)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDIT_M23_4)->SetWindowText("0.164");

			GetDlgItem(IDC_STATIC00)->EnableWindow(FALSE);
			GetDlgItem(IDC_STATIC01)->EnableWindow(FALSE);
			GetDlgItem(IDC_STATIC02)->EnableWindow(FALSE);
			GetDlgItem(IDC_STATIC03)->EnableWindow(FALSE);
		}
		else if (l1 == 32)
		{
			m_m231 = "38";
			m_m232 = "7447.51";
			m_m233 = "1.348819";
			m_m234 = "0.276";

			GetDlgItem(IDC_M23_1)->EnableWindow(FALSE);
			GetDlgItem(IDC_M23_2)->EnableWindow(FALSE);
			GetDlgItem(IDC_M23_3)->EnableWindow(FALSE);
			GetDlgItem(IDC_M23_4)->EnableWindow(FALSE);

			GetDlgItem(IDC_EDIT_M23_1)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDIT_M23_1)->SetWindowText(m_m231);

			GetDlgItem(IDC_EDIT_M23_2)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDIT_M23_2)->SetWindowTextA("7447.51");

			GetDlgItem(IDC_EDIT_M23_3)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDIT_M23_3)->SetWindowText("1.348819");

			GetDlgItem(IDC_EDIT_M23_4)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDIT_M23_4)->SetWindowText("0.276");

			GetDlgItem(IDC_STATIC00)->EnableWindow(FALSE);
			GetDlgItem(IDC_STATIC01)->EnableWindow(FALSE);
			GetDlgItem(IDC_STATIC02)->EnableWindow(FALSE);
			GetDlgItem(IDC_STATIC03)->EnableWindow(FALSE);
		}
		else if (l1 == 33)
		{
			m_m231 = "38";
			m_m232 = "7447.51";
			m_m233 = "2.077165";
			m_m234 = "0.197";

			GetDlgItem(IDC_M23_1)->EnableWindow(FALSE);
			GetDlgItem(IDC_M23_2)->EnableWindow(FALSE);
			GetDlgItem(IDC_M23_3)->EnableWindow(FALSE);
			GetDlgItem(IDC_M23_4)->EnableWindow(FALSE);

			GetDlgItem(IDC_EDIT_M23_1)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDIT_M23_1)->SetWindowText(m_m231);

			GetDlgItem(IDC_EDIT_M23_2)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDIT_M23_2)->SetWindowTextA("7447.51");

			GetDlgItem(IDC_EDIT_M23_3)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDIT_M23_3)->SetWindowText("2.077165");

			GetDlgItem(IDC_EDIT_M23_4)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDIT_M23_4)->SetWindowText("0.197");

			GetDlgItem(IDC_STATIC00)->EnableWindow(FALSE);
			GetDlgItem(IDC_STATIC01)->EnableWindow(FALSE);
			GetDlgItem(IDC_STATIC02)->EnableWindow(FALSE);
			GetDlgItem(IDC_STATIC03)->EnableWindow(FALSE);
		}
		else if (l1 == 34)
		{
			m_m231 = "38";
			m_m232 = "7765.75";
			m_m233 = "0.866142";
			m_m234 = "0.101";

			GetDlgItem(IDC_M23_1)->EnableWindow(FALSE);
			GetDlgItem(IDC_M23_2)->EnableWindow(FALSE);
			GetDlgItem(IDC_M23_3)->EnableWindow(FALSE);
			GetDlgItem(IDC_M23_4)->EnableWindow(FALSE);


			GetDlgItem(IDC_EDIT_M23_1)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDIT_M23_1)->SetWindowText(m_m231);

			GetDlgItem(IDC_EDIT_M23_2)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDIT_M23_2)->SetWindowTextA("7765.75");

			GetDlgItem(IDC_EDIT_M23_3)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDIT_M23_3)->SetWindowText("0.866142");

			GetDlgItem(IDC_EDIT_M23_4)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDIT_M23_4)->SetWindowText("0.101");

			GetDlgItem(IDC_STATIC00)->EnableWindow(FALSE);
			GetDlgItem(IDC_STATIC01)->EnableWindow(FALSE);
			GetDlgItem(IDC_STATIC02)->EnableWindow(FALSE);
			GetDlgItem(IDC_STATIC03)->EnableWindow(FALSE);
		}
		else
		{
			m_m231 = "";
			m_m232 = "";
			m_m233 = "";
			m_m234 = "";
			GetDlgItem(IDC_M23_1)->EnableWindow(FALSE);
			GetDlgItem(IDC_M23_2)->EnableWindow(FALSE);
			GetDlgItem(IDC_M23_3)->EnableWindow(FALSE);
			GetDlgItem(IDC_M23_4)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDIT_M23_1)->SetWindowText("");
			GetDlgItem(IDC_EDIT_M23_1)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDIT_M23_2)->SetWindowText("");
			GetDlgItem(IDC_EDIT_M23_2)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDIT_M23_3)->SetWindowText("");
			GetDlgItem(IDC_EDIT_M23_3)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDIT_M23_4)->SetWindowText("");
			GetDlgItem(IDC_EDIT_M23_4)->EnableWindow(FALSE);
			GetDlgItem(IDC_STATIC00)->EnableWindow(FALSE);
			GetDlgItem(IDC_STATIC01)->EnableWindow(FALSE);
			GetDlgItem(IDC_STATIC02)->EnableWindow(FALSE);
			GetDlgItem(IDC_STATIC03)->EnableWindow(FALSE);
		}
		/*else
		{
			m_m231 = "";
			m_m232 = "";
			m_m233 = "";
			m_m234 = "";

			GetDlgItem(IDC_M23_1)->EnableWindow(FALSE);
			GetDlgItem(IDC_M23_2)->EnableWindow(FALSE);
			GetDlgItem(IDC_M23_3)->EnableWindow(FALSE);
			GetDlgItem(IDC_M23_4)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDIT_M23_1)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDIT_M23_2)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDIT_M23_3)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDIT_M23_4)->EnableWindow(FALSE);
			GetDlgItem(IDC_STATIC00)->EnableWindow(FALSE);
			GetDlgItem(IDC_STATIC01)->EnableWindow(FALSE);
			GetDlgItem(IDC_STATIC02)->EnableWindow(FALSE);
			GetDlgItem(IDC_STATIC03)->EnableWindow(FALSE);
		}*/
		
		var = m_recordset->GetCollect("l6");
		str = (char *)_bstr_t(var);
		int l6=_ttoi(str);
		((CComboBox *)GetDlgItem(IDC_COMBO_M24))->SetCurSel(l6);
		UpdateData(FALSE);
		var = m_recordset->GetCollect("l7");
		str = (char *)_bstr_t(var);
		int l7=_ttoi(str);
		((CComboBox *)GetDlgItem(IDC_COMBO_M25))->SetCurSel(l7);
		UpdateData(FALSE);
		var = m_recordset->GetCollect("l8");
		str = (char *)_bstr_t(var);
		float fm45;
		sscanf(str, "%f", &fm45);
		m_m45.Format("%g", fm45);
		UpdateData(FALSE);
	}
	catch (_com_error e)
	{
		AfxMessageBox(e.ErrorMessage());
	}
	((CComboBox *)GetDlgItem(IDC_COMBO_METER))->SetCurSel(0);
	m_recordset->Close();
	m_recordset.Release();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSetDlg::OnM11() 
{
	// TODO: Add your control notification handler code here
	
	CCalibrationApp *app = (CCalibrationApp *)AfxGetApp();
	int i;
	char menu[7] = {'\x4d', '\x45', '\x4e', '\x55', '\x31', '\x31', '\x0d'};
	for (i=0; i<7; i++)
	{
		str += menu[i];
	}
	UpdateData(TRUE);
	if (m_m11 != "")
	{	
		float fm11;
		sscanf(m_m11, "%f", &fm11);
		if(IsDlgButtonChecked(IDC_RADIO1) && fm11>18000)
		{
			if (app->language == 0)
			{
				AfxMessageBox("管道外直径不能大于18000 mm!");
			}
			else
			{
				hHook=SetWindowsHookEx(WH_CBT,(HOOKPROC)CBTHookProc,AfxGetInstanceHandle(),NULL); 
				AfxMessageBox("The pipe outside diameter can not be greater than 18000 mm! ");
			}
		}
		else if(IsDlgButtonChecked(IDC_RADIO2) && fm11>708.661)
		{
			if (app->language == 0)
			{
				AfxMessageBox("管道外直径不能大于708.661 in!");
			}
			else
			{
				hHook=SetWindowsHookEx(WH_CBT,(HOOKPROC)CBTHookProc,AfxGetInstanceHandle(),NULL); 
				AfxMessageBox("The pipe outside diameter can not be greater than 708.661 in! ");
			}
		}
		else
		{
			str += "\x4d\x3d\x0d";

			for (i=0; i<m_m11.GetLength(); i++)
			{
				switch(m_m11.GetAt(i))
				{
				case '0':
					str += "\x4d\x30\x0d";
					break;
				case '1':
					str += "\x4d\x31\x0d";
					break;
				case '2':
					str += "\x4d\x32\x0d";
					break;
				case '3':
					str += "\x4d\x33\x0d";
					break;
				case '4':
					str += "\x4d\x34\x0d";
					break;
				case '5':
					str += "\x4d\x35\x0d";
					break;
				case '6':
					str += "\x4d\x36\x0d";
					break;
				case '7':
					str += "\x4d\x37\x0d";
					break;
				case '8':
					str += "\x4d\x38\x0d";
					break;
				case '9':
					str += "\x4d\x39\x0d";
					break;
				case '.':
					str += "\x4d\x3a\x0d";;
					break;
				default:
					if (app->language == 0)
					{
						AfxMessageBox("您的输入有误!");
						return;
					}
					else
					{
						hHook=SetWindowsHookEx(WH_CBT,(HOOKPROC)CBTHookProc,AfxGetInstanceHandle(),NULL); 
						AfxMessageBox("Your input is incorrect!");
						return;
					}
				}
			}
			str += "\x4d\x3d\x0d";

			app->g_com.Write(str);
			app->g_com.Write(str);
			Sleep(100);
			str = "";
			CString sql;
			sql.Format("update Common_settings set pipe_outer_diameter = %s", m_m11);
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
}

void CSetDlg::OnM30() {
	// TODO: Add your control notification handler code here
	CCalibrationApp *app = (CCalibrationApp *)AfxGetApp();
	int i;
	char menu[7] = {'\x4d', '\x45', '\x4e', '\x55', '\x33', '\x30', '\x0d'};
	for (i=0; i<7; i++){
		str += CString(menu[i]);
	}
	int gyz;     //公英制单位   0  公制  1 英制
	if(IsDlgButtonChecked(IDC_RADIO1)){
		GetDlgItem(IDC_STATIC1)->SetWindowText("mm");
		GetDlgItem(IDC_STATIC2)->SetWindowText("mm");
		GetDlgItem(IDC_STATIC3)->SetWindowText("mm");
		GetDlgItem(IDC_STATIC4)->SetWindowText("mm");
		GetDlgItem(IDC_STATIC00)->SetWindowText("m/s");
		GetDlgItem(IDC_STATIC01)->SetWindowText("mm");
		
		str += "\x4d\x3d\x0d";
		str += "\x4d\x30\x0d";
		str += "\x4d\x3d\x0d";

		gyz = 0;
	}
	if(IsDlgButtonChecked(IDC_RADIO2)){
		GetDlgItem(IDC_STATIC1)->SetWindowText("in");
		GetDlgItem(IDC_STATIC2)->SetWindowText("in");
		GetDlgItem(IDC_STATIC3)->SetWindowText("in");
		GetDlgItem(IDC_STATIC4)->SetWindowText("in");
		GetDlgItem(IDC_STATIC00)->SetWindowText("f/s");
		GetDlgItem(IDC_STATIC01)->SetWindowText("in");
		
		str += "\x4d\x3d\x0d";
		str += "\x4d\x31\x0d";
		str += "\x4d\x3d\x0d";

		gyz = 1;
	}
	app->g_com.Write(str);
	str = "";
	CString sql;
	sql.Format("update Common_settings set measurement_units = %d", gyz);
	try{
		m_pAppConn->Execute((_bstr_t)sql,NULL,adCmdText);
	}
	catch (_com_error e){
		AfxMessageBox(e.ErrorMessage());
	}
}

void CSetDlg::OnM12() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	CCalibrationApp *app = (CCalibrationApp *)AfxGetApp();
	int i;
	CString temp;
	char menu[7] = { '\x4d', '\x45', '\x4e', '\x55', '\x31', '\x32', '\x0d' };
	for (i=0; i<7; i++)
	{
		str += CString(menu[i]);
	}
	if (m_m12 != "")
	{	
		float fm11, fm12;
		sscanf(m_m12, "%f", &fm12);
		sscanf(m_m11, "%f", &fm11);
		if(IsDlgButtonChecked(IDC_RADIO1) && fm12>(fm11/2))
		{
			if (app->language == 0)
			{
				CString temp;
				temp.Format("管道管壁厚度不能大于%f mm!", fm11/2);
				AfxMessageBox(temp);
			}
			else
			{
				hHook=SetWindowsHookEx(WH_CBT,(HOOKPROC)CBTHookProc,AfxGetInstanceHandle(),NULL); 
				CString temp;
				temp.Format("The pipe wall thickness can not be greater than %f mm!", fm11/2);
				AfxMessageBox(temp);
			}
		}
		else if(IsDlgButtonChecked(IDC_RADIO2) && fm12>(fm11/2))
		{
			if (app->language == 0)
			{
				CString temp;
				temp.Format("管道管壁厚度不能大于%f in!", fm11/2);
				AfxMessageBox(temp);
			}
			else
			{
				hHook=SetWindowsHookEx(WH_CBT,(HOOKPROC)CBTHookProc,AfxGetInstanceHandle(),NULL); 
				CString temp;
				temp.Format("The pipe wall thickness can not be greater than %f in!", fm11/2);
				AfxMessageBox(temp);
			}
		}
		else
		{
			str += "\x4d\x3d\x0d";

			for (i=0; i<m_m12.GetLength(); i++)
			{
				switch(m_m12.GetAt(i))
				{
				case '0':
					str += "\x4d\x30\x0d";
					break;
				case '1':
					str += "\x4d\x31\x0d";
					break;
				case '2':
					str += "\x4d\x32\x0d";
					break;
				case '3':
					str += "\x4d\x33\x0d";
					break;
				case '4':
					str += "\x4d\x34\x0d";
					break;
				case '5':
					str += "\x4d\x35\x0d";
					break;
				case '6':
					str += "\x4d\x36\x0d";
					break;
				case '7':
					str += "\x4d\x37\x0d";
					break;
				case '8':
					str += "\x4d\x38\x0d";
					break;
				case '9':
					str += "\x4d\x39\x0d";
					break;
				case '.':
					str += "\x4d\x3a\x0d";;
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
			str += "\x4d\x3d\x0d";

			app->g_com.Write(str);
			app->g_com.Write(str);
			Sleep(100);
			str = "";
			CString sql;
			sql.Format("update Common_settings set pipe_wall_thickness = %s", m_m12);
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
}

void CSetDlg::OnM13() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	/*
	CCalibrationApp *app = (CCalibrationApp *)AfxGetApp();
	int i;
	int menu[7] = {0x4d, 0x45, 0x4e, 0x55, 0x31, 0x33, 0x0d};
	for (i=0; i<7; i++)
	{
		str += CString(menu[i]);
	}
	if (m_m13 != "")
	{
		for (i=0; i<m_m13.GetLength(); i++)
		{
			switch(m_m13.GetAt(i))
			{
			case '0':
				str += CString(0x4d) + CString(0x30) + CString(0x0d);
				break;
			case '1':
				str += CString(0x4d) + CString(0x31) + CString(0x0d);
				break;
			case '2':
				str += CString(0x4d) + CString(0x32) + CString(0x0d);
				break;
			case '3':
				str += CString(0x4d) + CString(0x33) + CString(0x0d);
				break;
			case '4':
				str += CString(0x4d) + CString(0x34) + CString(0x0d);
				break;
			case '5':
				str += CString(0x4d) + CString(0x35) + CString(0x0d);
				break;
			case '6':
				str += CString(0x4d) + CString(0x36) + CString(0x0d);
				break;
			case '7':
				str += CString(0x4d) + CString(0x37) + CString(0x0d);
				break;
			case '8':
				str += CString(0x4d) + CString(0x38) + CString(0x0d);
				break;
			case '9':
				str += CString(0x4d) + CString(0x39) + CString(0x0d);
				break;
			case '.':
				str += CString(0x4d) + CString(0x3a) + CString(0x0d);
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
		str += CString(0x4d) + CString(0x3d) + CString(0x0d);
		
	}
	app->g_com.Write(str);
	str = "";
	*/
	CString sql;
	sql.Format("update Common_settings set pipe_inner_diameter = %s", m_m13);
	try
	{
		m_pAppConn->Execute((_bstr_t)sql,NULL,adCmdText);
	}
	catch (_com_error e)
	{
		AfxMessageBox(e.ErrorMessage());
	}
}

void CSetDlg::OnUpdateM14() 
{
	// TODO: Add your control notification handler code here
	CCalibrationApp *app = (CCalibrationApp *)AfxGetApp();
	int i;
	char menu[7] = { '\x4d', '\x45', '\x4e', '\x55', '\x31', '\x32', '\x0d' };
	for (i=0; i<7; i++)
	{
		str += CString(menu[i]);
	}
	str += "\x4c\x43\x44\x0d";

	app->g_com.Write(str);
	char buf[50];
	app->g_com.Read(buf, 50);
	Sleep(100);
	char *p = buf;
	char num[2];
	while (p != NULL)
	{
		p++;
		if (*p == '.')
		{
			num[0] = *(p-2);
			num[1] = *(p-1);
			break;
		}
		
	}
	int x;
	if (num[0] == ' ')
	{
		x = num[1] - '0';
	}
	else
	{
		x = (num[0] - '0') * 10 + (num[1] - '0');
	}
	((CComboBox *)GetDlgItem(IDC_COMBO_M14))->SetCurSel(x);
	str = "";
}

void CSetDlg::OnM14() 
{
	// TODO: Add your control notification handler code here
	CCalibrationApp *app = (CCalibrationApp *)AfxGetApp();
	int i;
	CString temp;
	char menu[7] = { '\x4d', '\x45', '\x4e', '\x55', '\x31', '\x34', '\x0d' };
	for (i=0; i<7; i++)
	{
		str += CString(menu[i]);
	}
	int iPos = ((CComboBox *)GetDlgItem(IDC_COMBO_M14))->GetCurSel();

	if (iPos <= 9 && iPos >= 0)
	{
		str += "\x4d\x3d\x0d"; 	
		//str += "\x4d\(iPos + '0')\x0d";
		str += "\x4d";
		CString temp;
		temp.Format("%d", iPos);
		temp += '0';
		str += temp;
		str += "\x0d";
		str += "\x4d\x3d\x0d";
	}
	else
	{
		str += "\x4d\x3d\x0d";
		str += "\x4d\x39\x0d";

		for (int i=0; i<(iPos-9); i++)
		{
			str += "\x4d\x3f\x0d";
		}
		str += "\x4d\x3d\x0d";
	}
	app->g_com.Write(str);
	Sleep(100);
	str = "";
	CString sql;
	sql.Format("update Common_settings set pipe_material = %d", iPos);
	try
	{
		m_pAppConn->Execute((_bstr_t)sql,NULL,adCmdText);
	}
	catch (_com_error e)
	{
		AfxMessageBox(e.ErrorMessage());
	}
}

void CSetDlg::OnUpdateM16() 
{
	// TODO: Add your control notification handler code here
	CCalibrationApp *app = (CCalibrationApp *)AfxGetApp();
	int i;
	CString temp;
	char menu[7] = { '\x4d', '\x45', '\x4e', '\x55', '\x31', '\x36', '\x0d' };
	for (i=0; i<7; i++)
	{
		str += CString(menu[i]);
	}
	str += "\x4c\x43\x44\x0d";

	app->g_com.Write(str);
	char buf[50];
	app->g_com.Read(buf, 50);
	Sleep(100);
	char *p = buf;
	char num[2];
	while (p != NULL)
	{
		p++;
		if (*p == '.')
		{
			num[0] = *(p-2);
			num[1] = *(p-1);
			break;
		}
		
	}
	int x;
	if (num[0] == ' ')
	{
		x = num[1] - '0';
	}
	else
	{
		x = (num[0] - '0') * 10 + (num[1] - '0');
	}
	((CComboBox *)GetDlgItem(IDC_COMBO_M16))->SetCurSel(x);
	str = "";
}

void CSetDlg::OnM16() 
{
	// TODO: Add your control notification handler code here
	CCalibrationApp *app = (CCalibrationApp *)AfxGetApp();
	int i;
	char menu[7] = { '\x4d', '\x45', '\x4e', '\x55', '\x31', '\x36', '\x0d' };
	for (i=0; i<7; i++)
	{
		str += CString(menu[i]);
	}
	int iPos = ((CComboBox *)GetDlgItem(IDC_COMBO_M16))->GetCurSel();

	if (iPos <= 9 && iPos >= 0)
	{
		str += "\x4d\x3d\x0d"; 	
		//str += "\x4d\(iPos + '0')\x0d";
		str += "\x4d";
		CString temp;
		temp.Format("%d", iPos);
		temp += '0';
		str += temp;
		str += "\x0d";
		str += "\x4d\x3d\x0d";
	}
	else
	{
		str += "\x4d\x3d\x0d";
		str += "\x4d\x39\x0d";

		for (int i=0; i<(iPos-9); i++)
		{
			str += "\x4d\x3f\x0d";
		}
		str += "\x4d\x3d\x0d"; 
	}
	app->g_com.Write(str);
	Sleep(100);
	str = "";
	CString sql;
	if (iPos != 0)
	{
		sql.Format("update Common_settings set liner_material = %d", iPos);
	}
	else
	{
		sql.Format("update Common_settings set liner_material = %d,liner_thickness = 0", iPos);
	}
	try
	{
		m_pAppConn->Execute((_bstr_t)sql,NULL,adCmdText);
	}
	catch (_com_error e)
	{
		AfxMessageBox(e.ErrorMessage());
	}
	if (iPos == 0)
	{
		GetDlgItem(IDC_M18)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_M18)->EnableWindow(FALSE);
		m_m18 = "0";
		UpdateData(FALSE);
	}
	else
	{
		GetDlgItem(IDC_M18)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_M18)->EnableWindow(TRUE);
	}
}

void CSetDlg::OnM18() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	CCalibrationApp *app = (CCalibrationApp *)AfxGetApp();
	int i;
	CString temp;
	char menu[7] = { '\x4d', '\x45', '\x4e', '\x55', '\x31', '\x38', '\x0d' };
	for (i=0; i<7; i++)
	{
		str += CString(menu[i]);
	}
	if (m_m18 != "")
	{	

		for (i=0; i<m_m18.GetLength(); i++)
		{
			switch(m_m18.GetAt(i))
			{
			case '0':
				str += "\x4d\x30\x0d";
				break;
			case '1':
				str += "\x4d\x31\x0d";
				break;
			case '2':
				str += "\x4d\x32\x0d";
				break;
			case '3':
				str += "\x4d\x33\x0d";
				break;
			case '4':
				str += "\x4d\x34\x0d";
				break;
			case '5':
				str += "\x4d\x35\x0d";
				break;
			case '6':
				str += "\x4d\x36\x0d";
				break;
			case '7':
				str += "\x4d\x37\x0d";
				break;
			case '8':
				str += "\x4d\x38\x0d";
				break;
			case '9':
				str += "\x4d\x39\x0d";
				break;
			case '.':
				str += "\x4d\x3a\x0d";;
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
		str += "\x4d\x3d\x0d";

		CString sql;
		sql.Format("update Common_settings set liner_thickness = %s", m_m18);
		try
		{
			m_pAppConn->Execute((_bstr_t)sql,NULL,adCmdText);
		}
		catch (_com_error e)
		{
			AfxMessageBox(e.ErrorMessage());
		}
	}
	app->g_com.Write(str);
	Sleep(100);
	str = "";
}

void CSetDlg::OnUpdateM20() 
{
	// TODO: Add your control notification handler code here
	CCalibrationApp *app = (CCalibrationApp *)AfxGetApp();
	int i;
	CString temp;
	char menu[7] = { '\x4d', '\x45', '\x4e', '\x55', '\x32', '\x30', '\x0d' };
	for (i=0; i<7; i++)
	{
		str += CString(menu[i]);
	}
	str += "\x4c\x43\x44\x0d";

	app->g_com.Write(str);
	char buf[50];
	app->g_com.Read(buf, 50);
	Sleep(100);
	char *p = buf;
	char num[2];
	while (p != NULL)
	{
		p++;
		if (*p == '.')
		{
			num[0] = *(p-2);
			num[1] = *(p-1);
			break;
		}
		
	}
	int x;
	if (num[0] == ' ')
	{
		x = num[1] - '0';
	}
	else
	{
		x = (num[0] - '0') * 10 + (num[1] - '0');
	}
	((CComboBox *)GetDlgItem(IDC_COMBO_M20))->SetCurSel(x);
	str = "";
}

void CSetDlg::OnM20() 
{
	// TODO: Add your control notification handler code here
	CCalibrationApp *app = (CCalibrationApp *)AfxGetApp();
	int i;
	CString temp;
	char menu[7] = { '\x4d', '\x45', '\x4e', '\x55', '\x32', '\x30', '\x0d' };
	for (i=0; i<7; i++)
	{
		str += CString(menu[i]);
	}
	int iPos = ((CComboBox *)GetDlgItem(IDC_COMBO_M20))->GetCurSel();

	if (iPos <= 9 && iPos >= 0)
	{
		str += "\x4d\x3d\x0d"; 	
		//str += "\x4d\(iPos + '0')\x0d";
		str += "\x4d";
		temp.Format("%d", iPos);
		temp += '0';
		str += temp;
		str += "\x0d";
		str += "\x4d\x3d\x0d";

	}
	else
	{
		str += "\x4d\x3d\x0d";
		str += "\x4d\x39\x0d";

		for (int i=0; i<(iPos-9); i++)
		{
			str += "\x4d\x3f\x0d";
		}
		str += "\x4d\x3d\x0d";
	}
	app->g_com.Write(str);
	Sleep(100);
	str = "";

	CString sql;
	sql.Format("update Common_settings set fluid_type = %d", iPos);
	try
	{
		m_pAppConn->Execute((_bstr_t)sql,NULL,adCmdText);
	}
	catch (_com_error e)
	{
		AfxMessageBox(e.ErrorMessage());
	}
}

void CSetDlg::OnUpdateM31() 
{
	// TODO: Add your control notification handler code here
	CCalibrationApp *app = (CCalibrationApp *)AfxGetApp();
	int i;
	char menu[7] = { '\x4d', '\x45', '\x4e', '\x55', '\x33', '\x31', '\x0d' };
	for (i=0; i<7; i++)
	{
		str += CString(menu[i]);
	}
	str += "\x4c\x43\x44\x0d";

	app->g_com.Write(str);
	str = "";
	char buf[60];
	app->g_com.Read(buf, 60);
	Sleep(100);
	char *p = buf;
	char unit[3] = {0};
	while (*p != '\0')
	{
		if (*p == '/')
		{
			unit[0] = *(p-2);
			unit[1] = *(p-1);
			unit[2] = *(p+1);
			break;
		}
 		p++;
	}
	if (unit[0] == 'm' && unit[1] == '3')
	{
		((CComboBox *)GetDlgItem(IDC_COMBO_M31_1))->SetCurSel(0);
	}
	else if(unit[0] == ' ' && unit[1] == 'l')
	{
		((CComboBox *)GetDlgItem(IDC_COMBO_M31_1))->SetCurSel(1);
	}
	else if(unit[0] == ' ' && unit[1] == 'g')
	{
		((CComboBox *)GetDlgItem(IDC_COMBO_M31_1))->SetCurSel(2);
	}
	else if(unit[0] == 'i' && unit[1] == 'g')
	{
		((CComboBox *)GetDlgItem(IDC_COMBO_M31_1))->SetCurSel(3);
	}
	else if(unit[0] == 'M' && unit[1] == 'g')
	{
		((CComboBox *)GetDlgItem(IDC_COMBO_M31_1))->SetCurSel(4);
	}
	else if(unit[0] == 'c' && unit[1] == 'f')
	{
		((CComboBox *)GetDlgItem(IDC_COMBO_M31_1))->SetCurSel(5);
	}
	else if(unit[0] == 'o' && unit[1] == 'b')
	{
		((CComboBox *)GetDlgItem(IDC_COMBO_M31_1))->SetCurSel(6);
	}
	else
	{
		((CComboBox *)GetDlgItem(IDC_COMBO_M31_1))->SetCurSel(7);
	}
	switch (unit[2])
	{
	case 's':
		((CComboBox *)GetDlgItem(IDC_COMBO_M31_2))->SetCurSel(0);
		break;
	case 'm':
		((CComboBox *)GetDlgItem(IDC_COMBO_M31_2))->SetCurSel(1);
		break;
	case 'h':
		((CComboBox *)GetDlgItem(IDC_COMBO_M31_2))->SetCurSel(2);
		break;
	case 'd':
		((CComboBox *)GetDlgItem(IDC_COMBO_M31_2))->SetCurSel(3);
		break;
	}	
}

void CSetDlg::OnM31() 
{
	// TODO: Add your control notification handler code here
	CCalibrationApp *app = (CCalibrationApp *)AfxGetApp();
	int i;
	CString temp;
	char menu[7] = { '\x4d', '\x45', '\x4e', '\x55', '\x33', '\x31', '\x0d' };
	for (i=0; i<7; i++)
	{
		str += CString(menu[i]);
	}
	int iPos1 = ((CComboBox *)GetDlgItem(IDC_COMBO_M31_1))->GetCurSel();
	int iPos2 = ((CComboBox *)GetDlgItem(IDC_COMBO_M31_2))->GetCurSel();
	
	str += "\x4d\x3d\x0d"; 	
	//str += "\x4d\(iPos1 + '0')\x0d";
	str += "\x4d";
	temp.Format("%d", iPos1);
	temp += '0';
	str += temp;
	str += "\x0d";
	str += "\x4d\x3d\x0d";
	//str += "\x4d\(iPos1 + '0')\x0d";
	str += "\x4d";
	temp.Format("%d", iPos2);
	temp += '0';
	str += temp;
	str += "\x0d";
	str += "\x4d\x3d\x0d";

	app->g_com.Write(str);
	str = "";
	CString sql;
	sql.Format("update Common_settings set flow_rate_unit = \'%d/%d\'", iPos1, iPos2);
	try
	{
		m_pAppConn->Execute((_bstr_t)sql,NULL,adCmdText);
	}
	catch (_com_error e)
	{
		AfxMessageBox(e.ErrorMessage());
	}
}

void CSetDlg::OnUpdateM32() 
{
	// TODO: Add your control notification handler code here
	CCalibrationApp *app = (CCalibrationApp *)AfxGetApp();
	int i;
	char menu[7] = { '\x4d', '\x45', '\x4e', '\x55', '\x33', '\x32', '\x0d' };
	for (i=0; i<7; i++)
	{
		str += CString(menu[i]);
	}
	str += "\0x4c\x43\x44\x0d";

	app->g_com.Write(str);
	str = "";
	char buf[50];
	app->g_com.Read(buf, 50);
	Sleep(100);
	char *p = buf;
	char *p2 = new char;
	while (*p != ')')
	{
		if (*p == '(')
		{
			p2 = p+1;
			break;
		}
		p++;
	}
	char *p3 = p2;
	while (*p3 != '\0')
	{
		if (*p3 == ')')
		{
			break;
		}
		p3++;
	}
	char unit[3] = {0};
	for (i=0; i<(p3-p2); i++)
	{
		unit[i] = *(p2+i);
	}
	if (unit[0] == 'm' && unit[1] == '3')
	{
		((CComboBox *)GetDlgItem(IDC_COMBO_M32))->SetCurSel(0);
	}
	else if(unit[0] == 'L')
	{
		((CComboBox *)GetDlgItem(IDC_COMBO_M32))->SetCurSel(1);
	}
	else if(unit[0] == 'G' && unit[1] == 'A' && unit[2] == 'L')
	{
		((CComboBox *)GetDlgItem(IDC_COMBO_M32))->SetCurSel(2);
	}
	else if(unit[0] == 'I' && unit[1] == 'G' && unit[2] == 'L')
	{
		((CComboBox *)GetDlgItem(IDC_COMBO_M32))->SetCurSel(3);
	}
	else if(unit[0] == 'M' && unit[1] == 'G' && unit[2] == 'L')
	{
		((CComboBox *)GetDlgItem(IDC_COMBO_M32))->SetCurSel(4);
	}
	else if(unit[0] == 'C' && unit[1] == 'F')
	{
		((CComboBox *)GetDlgItem(IDC_COMBO_M32))->SetCurSel(5);
	}
	else if(unit[0] == 'O' && unit[1] == 'B')
	{
		((CComboBox *)GetDlgItem(IDC_COMBO_M32))->SetCurSel(6);
	}
	else if(unit[0] == 'I' && unit[1] == 'B')
	{
		((CComboBox *)GetDlgItem(IDC_COMBO_M32))->SetCurSel(7);
	}
	delete p2;
	p2 = NULL;
}

void CSetDlg::OnM32() 
{
	// TODO: Add your control notification handler code here
	CCalibrationApp *app = (CCalibrationApp *)AfxGetApp();
	int i;
	char menu[7] = { '\x4d', '\x45', '\x4e', '\x55', '\x33', '\x32', '\x0d' };
	for (i=0; i<7; i++)
	{
		str += CString(menu[i]);
	}
	int iPos = ((CComboBox *)GetDlgItem(IDC_COMBO_M32))->GetCurSel();
	
	str += "\x4d\x3d\x0d"; 	
	//str += "\x4d\(iPos + '0')\x0d";
	str += "\x4d";
	CString temp;
	temp.Format("%d", iPos);
	temp += '0';
	str += temp;
	str += "\x0d";
	str += "\x4d\x3d\x0d";

	app->g_com.Write(str);
	str = "";
	CString sql;
	sql.Format("update Common_settings set totalizer_units = %d", iPos);
	try
	{
		m_pAppConn->Execute((_bstr_t)sql,NULL,adCmdText);
	}
	catch (_com_error e)
	{
		AfxMessageBox(e.ErrorMessage());
	}
}

void CSetDlg::OnUpdateM33() 
{
	// TODO: Add your control notification handler code here
	CCalibrationApp *app = (CCalibrationApp *)AfxGetApp();
	int i;
	char menu[7] = { '\x4d', '\x45', '\x4e', '\x55', '\x33', '\x33', '\x0d' };
	for (i=0; i<7; i++)
	{
		str += CString(menu[i]);
	}
	str += "\x4c\x43\x44\x0d";

	app->g_com.Write(str);
	char buf[40];
	app->g_com.Read(buf, 40);
	Sleep(100);
	char *p = buf;
	char num[2];
	while (p != NULL)
	{
		p++;
		if (*p == '.')
		{
			num[0] = *(p-2);
			num[1] = *(p-1);
			break;
		}	
	}
	int x;
	if (num[0] == ' ')
	{
		x = num[1] - '0';
	}
	else
	{
		x = (num[0] - '0') * 10 + (num[1] - '0');
	}
	((CComboBox *)GetDlgItem(IDC_COMBO_M33))->SetCurSel(x);
	str = "";
}

void CSetDlg::OnM33() 
{
	// TODO: Add your control notification handler code here
	CCalibrationApp *app = (CCalibrationApp *)AfxGetApp();
	int i;
	char menu[7] = { '\x4d', '\x45', '\x4e', '\x55', '\x33', '\x33', '\x0d' };
	for (i=0; i<7; i++)
	{
		str += CString(menu[i]);
	}
	int iPos = ((CComboBox *)GetDlgItem(IDC_COMBO_M33))->GetCurSel();
	
	str += "\x4d\x3d\x0d";
	//str += "\x4d\(iPos + '0')\x0d";
	str += "\x4d";
	CString temp;
	temp.Format("%d", iPos);
	temp += '0';
	str += temp;
	str += "\x0d";
	str += "\x4d\x3d\x0d";

	app->g_com.Write(str);
	str = "";
	CString sql;
	sql.Format("update Common_settings set totalizer_multiplier = %d", iPos);
	try
	{
		m_pAppConn->Execute((_bstr_t)sql,NULL,adCmdText);
	}
	catch (_com_error e)
	{
		AfxMessageBox(e.ErrorMessage());
	}
}

void CSetDlg::OnM34() 
{
	// TODO: Add your control notification handler code here
	CCalibrationApp *app = (CCalibrationApp *)AfxGetApp();
	int i;
	char menu[7] = { '\x4d', '\x45', '\x4e', '\x55', '\x33', '\x34', '\x0d' };
	for (i=0; i<7; i++)
	{
		str += CString(menu[i]);
	}
	int flag = 0;

	if(IsDlgButtonChecked(IDC_RADIO3))
	{
		str += "\x4d\x3d\x0d";
		str += "\x4d\x31\x0d";
		str += "\x4d\x3d\x0d";

		flag = 1;
	}
	if(IsDlgButtonChecked(IDC_RADIO4))
	{
		str += "\x4d\x3d\x0d";
		str += "\x4d\x30\x0d";
		str += "\x4d\x3d\x0d";

		flag = 0;
	}
	app->g_com.Write(str);
	str = "";
	CString sql;
	sql.Format("update Common_settings set net_toalizer = %d", flag);
	try
	{
		m_pAppConn->Execute((_bstr_t)sql,NULL,adCmdText);
	}
	catch (_com_error e)
	{
		AfxMessageBox(e.ErrorMessage());
	}
}

void CSetDlg::OnM35() 
{
	// TODO: Add your control notification handler code here
	CCalibrationApp *app = (CCalibrationApp *)AfxGetApp();
	int i;
	char menu[7] = { '\x4d', '\x45', '\x4e', '\x55', '\x33', '\x35', '\x0d' };
	for (i=0; i<7; i++)
	{
		str += CString(menu[i]);
	}
	int flag = 0;

	if(IsDlgButtonChecked(IDC_RADIO5))
	{
		str += "\x4d\x3d\x0d";
		str += "\x4d\x31\x0d";
		str += "\x4d\x3d\x0d";

		flag = 1;
	}
	if(IsDlgButtonChecked(IDC_RADIO6))
	{
		str += "\x4d\x3d\x0d";
		str += "\x4d\x30\x0d";
		str += "\x4d\x3d\x0d";

		flag = 0;
	}
	app->g_com.Write(str);
	str = "";
	CString sql;
	sql.Format("update Common_settings set pos_totalizer = %d", flag);
	try
	{
		m_pAppConn->Execute((_bstr_t)sql,NULL,adCmdText);
	}
	catch (_com_error e)
	{
		AfxMessageBox(e.ErrorMessage());
	}
}

void CSetDlg::OnM36() 
{
	// TODO: Add your control notification handler code here
	CCalibrationApp *app = (CCalibrationApp *)AfxGetApp();
	int i;
	char menu[7] = { '\x4d', '\x45', '\x4e', '\x55', '\x33', '\x36', '\x0d' };
	for (i=0; i<7; i++)
	{
		str += CString(menu[i]);
	}
	int flag = 0;

	if(IsDlgButtonChecked(IDC_RADIO7))
	{
		str += "\x4d\x3d\x0d";
		str += "\x4d\x31\x0d";
		str += "\x4d\x3d\x0d";

		flag = 1;
	}
	if(IsDlgButtonChecked(IDC_RADIO8))
	{
		str += "\x4d\x3d\x0d";
		str += "\x4d\x30\x0d";
		str += "\x4d\x3d\x0d";

		flag = 0;
	}
	app->g_com.Write(str);
	str = "";
	CString sql;
	sql.Format("update Common_settings set neg_totalizer = %d", flag);
	try
	{
		m_pAppConn->Execute((_bstr_t)sql,NULL,adCmdText);
	}
	catch (_com_error e)
	{
		AfxMessageBox(e.ErrorMessage());
	}
}

void CSetDlg::OnM37() 
{
	// TODO: Add your control notification handler code here
	CCalibrationApp *app = (CCalibrationApp *)AfxGetApp();
	int i;
	char menu[7] = { '\x4d', '\x45', '\x4e', '\x55', '\x33', '\x37', '\x0d'};
	for (i=0; i<7; i++)
	{
		str += CString(menu[i]);
	}

	str += "\x4d\x3d\x0d";
	str += "\x4d\x3d\x0d";

	if(IsDlgButtonChecked(IDC_RADIO9))
	{
		GetDlgItem(IDC_STATIC5)->EnableWindow(FALSE);
		GetDlgItem(IDC_OK)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_M37)->EnableWindow(FALSE);

		str += "\x4d\x3d\x0d";
		str += "\x4d\x30\x0d";
		str += "\x4d\x3d\x0d";

	}
	if(IsDlgButtonChecked(IDC_RADIO10))
	{
		GetDlgItem(IDC_STATIC5)->EnableWindow(TRUE);
		GetDlgItem(IDC_OK)->EnableWindow(TRUE);
		GetDlgItem(IDC_COMBO_M37)->EnableWindow(TRUE);

		str += "\x4d\x3d\x0d";
		str += "\x4d\x31\x0d";
		str += "\x4d\x3d\x0d";

	}
	app->g_com.Write(str);
	str = "";
}

void CSetDlg::OnOk() 
{
	// TODO: Add your control notification handler code here
	GetDlgItem(IDC_STATIC5)->EnableWindow(FALSE);
	GetDlgItem(IDC_OK)->EnableWindow(FALSE);
	GetDlgItem(IDC_COMBO_M37)->EnableWindow(FALSE);
	CCalibrationApp *app = (CCalibrationApp *)AfxGetApp();
	int i;
	char menu[7] = { '\x4d', '\x45', '\x4e', '\x55', '\x33', '\x37', '\x0d' };
	for (i=0; i<7; i++)
	{
		str += CString(menu[i]);
	}

	str += "\x4d\x3d\x0d";
	str += "\x4d\x3d\x0d";
	str += "\x4d\x3d\x0d";
	str += "\x4d\x31\x0d";
	str += "\x4d\x3d\x0d";

	int iPos = ((CComboBox *)GetDlgItem(IDC_COMBO_M37))->GetCurSel();

	//str += "\x4d\(iPos + '0')\x0d";
	str += "\x4d";
	CString temp;
	temp.Format("%d", iPos);
	temp += '0';
	str += temp;
	str += "\x0d";
	str += "\x4d\x3d\x0d";

	app->g_com.Write(str);
	str = "";
	if (app->language == 0)
	{
		AfxMessageBox("所选累积器已清零。");
	}
	else
	{
		hHook=SetWindowsHookEx(WH_CBT,(HOOKPROC)CBTHookProc,AfxGetInstanceHandle(),NULL); 
		AfxMessageBox("The selected cumulative device has been reset.");
	}
}

void CSetDlg::OnUpdateM39() 
{
	// TODO: Add your control notification handler code here
	CCalibrationApp *app = (CCalibrationApp *)AfxGetApp();
	int i;
	char menu[7] = { '\x4d', '\x45', '\x4e', '\x55', '\x33', '\x39', '\x0d' };
	for (i=0; i<7; i++)
	{
		str += CString(menu[i]);
	}
	str += "\x4c\x43\x44\x0d";


	app->g_com.Write(str);
	char buf[50];
	app->g_com.Read(buf, 50);
	Sleep(100);
	char *p = buf;
	int x;
	while (*p != '\0')
	{
		p++;
		if(*p == 'E' && *(p+1) == 'n')
		{
			x = 0; 
		}
		else if(*p == 'Z' && *(p+1) == 'h')
		{
			x = 1;
		}
		else if(*p == 'I' && *(p+1) == 't')
		{
			x = 2;
		}	
	}
	((CComboBox *)GetDlgItem(IDC_COMBO_M39))->SetCurSel(x);
	str = "";
}

void CSetDlg::OnM39() 
{
	// TODO: Add your control notification handler code here
	CCalibrationApp *app = (CCalibrationApp *)AfxGetApp();
	int i;
	char menu[7] = { '\x4d', '\x45', '\x4e', '\x55', '\x33', '\x39', '\x0d' };
	for (i=0; i<7; i++)
	{
		str += CString(menu[i]);
	}
	int iPos = ((CComboBox *)GetDlgItem(IDC_COMBO_M39))->GetCurSel();
	
	str += "\x4d\x3d\x0d";
	//str += "\x4d\(iPos + '0')\x0d";
	str += "\x4d";
	CString temp;
	temp.Format("%d", iPos);
	temp += '0';
	str += temp;
	str += "\x0d";
	str += "\x4d\x3d\x0d";

	app->g_com.Write(str);
	str = "";
	CString sql;
	sql.Format("update Common_settings set Language_LINGUA = %d", iPos);
	try
	{
		m_pAppConn->Execute((_bstr_t)sql,NULL,adCmdText);
	}
	catch (_com_error e)
	{
		AfxMessageBox(e.ErrorMessage());
	}
}

void CSetDlg::OnM40() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	CCalibrationApp *app = (CCalibrationApp *)AfxGetApp();
	int i;
	char menu[7] = { '\x4d', '\x45', '\x4e', '\x55', '\x34', '\x30', '\x0d' };
	for (i=0; i<7; i++)
	{
		str += CString(menu[i]);
	}
	if (m_m40 != "")
	{
		str += "\x4d\x3d\x0d";

		for (i=0; i<m_m40.GetLength(); i++)
		{
			switch(m_m40.GetAt(i))
			{
			case '0':
				str += "\x4d\x30\x0d";
				break;
			case '1':
				str += "\x4d\x31\x0d";
				break;
			case '2':
				str += "\x4d\x32\x0d";
				break;
			case '3':
				str += "\x4d\x33\x0d";
				break;
			case '4':
				str += "\x4d\x34\x0d";
				break;
			case '5':
				str += "\x4d\x35\x0d";
				break;
			case '6':
				str += "\x4d\x36\x0d";
				break;
			case '7':
				str += "\x4d\x37\x0d";
				break;
			case '8':
				str += "\x4d\x38\x0d";
				break;
			case '9':
				str += "\x4d\x39\x0d";
				break;
			case '.':
				str += "\x4d\x3a\x0d";;
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
		str += "\x4d\x3d\x0d";

		CString sql;
		sql.Format("update Common_settings set damping_factor = %s", m_m40);
		try
		{
			m_pAppConn->Execute((_bstr_t)sql,NULL,adCmdText);
		}
		catch (_com_error e)
		{
			AfxMessageBox(e.ErrorMessage());
		}
	}
	app->g_com.Write(str);
	str = "";
}

void CSetDlg::OnUpdateM79() 
{
	// TODO: Add your control notification handler code here
	CCalibrationApp *app = (CCalibrationApp *)AfxGetApp();
	int i;
	char menu[7] = { '\x4d', '\x45', '\x4e', '\x55', '\x37', '\x39', '\x0d' };
	for (i=0; i<7; i++)
	{
		str += CString(menu[i]);
	}
	str += "\x4c\x43\x44\x0d";

	app->g_com.Write(str);
	char buf[60];
	app->g_com.Read(buf, 60);
	Sleep(100);
	char *p = buf;
	char num[2];
	int x;
	while (p != NULL)
	{
		p++;
		if (*p == '.')
		{
			num[0] = *(p-2);
			num[1] = *(p-1);
			break;
		}
		
	}
	if (num[0] == ' ')
	{
		x = num[1] - '0';
	}
	else
	{
		x = (num[0] - '0') * 10 + (num[1] - '0');
	}
	((CComboBox *)GetDlgItem(IDC_COMBO_M79))->SetCurSel(x);
	str = "";
}

void CSetDlg::OnM79() 
{
	// TODO: Add your control notification handler code here
	CCalibrationApp *app = (CCalibrationApp *)AfxGetApp();
	int i;
	char menu[7] = { '\x4d', '\x45', '\x4e', '\x55', '\x37', '\x39', '\x0d' };
	for (i=0; i<7; i++)
	{
		str += CString(menu[i]);
	}
	int iPos = ((CComboBox *)GetDlgItem(IDC_COMBO_M79))->GetCurSel();

	if (iPos <= 9 && iPos >= 0)
	{
		str += "\x4d\x3d\x0d";
		str += "\x4d";
		CString temp;
		temp.Format("%d", iPos);
		temp += '0';
		str += temp;
		str+="\x0d";
		str += "\x4d\x3d\x0d";
	}
	else
	{
		str += "\x4d\x3d\x0d";
		str += "\x4d\x39\x0d";

		for (int i=0; i<(iPos-9); i++)
		{
			str += "\x4d\x3f\x0d";
		}
		str += "\x4d\x3d\x0d";
	}
	app->g_com.Write(str);
	str = "";
	CString sql;
	sql.Format("update Common_settings set relay_output_setup = %d", iPos);
	try
	{
		m_pAppConn->Execute((_bstr_t)sql,NULL,adCmdText);
	}
	catch (_com_error e)
	{
		AfxMessageBox(e.ErrorMessage());
	}
}

void CSetDlg::OnSelchangeComboMeter() 
{
	// TODO: Add your control notification handler code here
	CCalibrationApp *app = (CCalibrationApp *)AfxGetApp();
	GetDlgItem(IDC_STATIC_AUTO2)->ShowWindow(FALSE);
	int i;
	//获取netword_IDN
	CString s;
	int iPos = ((CComboBox *)GetDlgItem(IDC_COMBO_METER))->GetCurSel();
	((CComboBox *)GetDlgItem(IDC_COMBO_METER))->GetLBText(iPos, s);
	s.Delete(0, 10);
	int len = s.GetLength();

	CString sql;
	sql.Format("select * from Independent_settings where netword_IDN = %s", s);
	
	try
	{
		m_recordset = m_pAppConn->Execute((_bstr_t)sql,NULL,adCmdText);
		_variant_t var = m_recordset->GetCollect("table_type");	
		CString cstr =(char *)_bstr_t(var);
		iPos = atoi(cstr);
		if (iPos == 0)
		{
			((CComboBox *)GetDlgItem(IDC_COMBO_M24))->SetCurSel(0);
			((CComboBox *)GetDlgItem(IDC_COMBO_M24))->EnableWindow(FALSE);
			((CButton *)GetDlgItem(IDC_M24))->EnableWindow(FALSE);
		}
	}
	catch (_com_error e)
	{
		AfxMessageBox(e.ErrorMessage());
	}

	//W前缀
	str1 = "\x57";

	for (i=0; i<len; i++)
	{
		switch(s.GetAt(i))
		{
		case '0':
			str1 +="\x30";
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

	char menu[6] = { '\x4d', '\x45', '\x4e', '\x55', '\x32', '\x33' };
	CString str2 = "";
	for (i=0; i<6; i++)
	{
		str2 += CString(menu[i]);
	}
	str2 += "\x26\x4c\x43\x44\x0d";

	//发送消息
	str = str1 + str2;
	app->g_com.Write(str);
	str = "";
	str2 = "";
	
	//接收消息
	char buf[60] = {0};
	app->g_com.Read(buf, 60);
	Sleep(100);
	char *p = buf;
	char num[2] = {0};
	while (p != NULL)
	{
		p++;
		if (*p == '.')
		{
			num[0] = *(p-2);
			num[1] = *(p-1);
			break;
		}
	}
	int x;
	if (num[0] == ' ')
	{
		x = num[1] - '0';
	}
	else
	{
		x = (num[0] - '0') * 10 + (num[1] - '0');
	}
	UpdateData(FALSE);
	((CComboBox *)GetDlgItem(IDC_COMBO_M23))->SetCurSel(x);

	CString t, t1;
	t.Format("%d", 0x4d);
	t1.Format("%d", 0x3d);

	if (x == 3)
	{
		str2 ="\x4d\x3d\x0d";

		str = str1 + str2;
		app->g_com.Write(str);
		Sleep(100);
		str = "";
		str2 = "";
		str2 = "\0x4d\x3d\x26\x4c\x43\x44\x0d";
		
		str = str1 + str2;
		app->g_com.Write(str);
		Sleep(100);
		str = "";
		str2 = "";
		char buf[60] = {0};
		app->g_com.Read(buf, 60);
		Sleep(100);
		CString readstr;
		readstr.Format("%s", buf);
		readstr = readstr.Left(45);
		readstr = readstr.Right(10);
		readstr.TrimLeft();
		readstr.TrimRight();
		m_m231 = readstr;

		str2 = "\x4d\x3f\x26\x4c\x43\x44\x0d";
		str = str1 + str2;
		app->g_com.Write(str);
		str = "";
		str2 = "";
		char buf2[60] = {0};
		app->g_com.Read(buf2, 60);
		Sleep(100);
		CString readstr2;
		readstr2.Format("%s", buf2);
		readstr2 = readstr2.Left(45);
		readstr2 = readstr2.Right(10);
		readstr2.TrimLeft();
		readstr2.TrimRight();
		m_m232 = readstr2;

		str2 = "\x4d\x3f\x26\x4c\x43\x44\x0d";

		str = str1 + str2;
		app->g_com.Write(str);
		str = "";
		str2 = "";
		char buf3[60] = {0};
		app->g_com.Read(buf3, 60);
		Sleep(100);
		CString readstr3;
		readstr3.Format("%s", buf3);
		readstr3 = readstr3.Left(45);
		readstr3 = readstr3.Right(10);
		readstr3.TrimLeft();
		readstr3.TrimRight();
		m_m233 = readstr3;

		str2 = "\x4d\x3f\x26\x4c\x43\x44\x0d";

		str = str1 + str2;
		app->g_com.Write(str);
		str = "";
		str2 = "";
		char buf4[60] = {0};
		app->g_com.Read(buf4, 60);
		Sleep(100);
		CString readstr4;
		readstr4.Format("%s", buf4);
		readstr4 = readstr4.Left(45);
		readstr4 = readstr4.Right(10);
		readstr4.TrimLeft();
		readstr4.TrimRight();
		m_m234 = readstr4;
		GetDlgItem(IDC_M23_1)->EnableWindow(TRUE);
		GetDlgItem(IDC_M23_2)->EnableWindow(TRUE);
		GetDlgItem(IDC_M23_3)->EnableWindow(TRUE);
		GetDlgItem(IDC_M23_4)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_M23_1)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_M23_2)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_M23_3)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_M23_4)->EnableWindow(TRUE);
		GetDlgItem(IDC_STATIC00)->EnableWindow(TRUE);
		GetDlgItem(IDC_STATIC01)->EnableWindow(TRUE);
		GetDlgItem(IDC_STATIC02)->EnableWindow(TRUE);
		GetDlgItem(IDC_STATIC03)->EnableWindow(TRUE);
	}
	else
	{
		m_m231 = "";
		m_m232 = "";
		m_m233 = "";
		m_m234 = "";
		GetDlgItem(IDC_M23_1)->EnableWindow(FALSE);
		GetDlgItem(IDC_M23_2)->EnableWindow(FALSE);
		GetDlgItem(IDC_M23_3)->EnableWindow(FALSE);
		GetDlgItem(IDC_M23_4)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_M23_1)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_M23_2)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_M23_3)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_M23_4)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC00)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC01)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC02)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC03)->EnableWindow(FALSE);
	}

	if (iPos == 1)
	{
		CString str2 = "";
		char menu[6] = { '\x4d', '\x45', '\x4e', '\x55', '\x32', '\x34' };
		for (i=0; i<6; i++)
		{
			str2 += CString(menu[i]);
		}
		str2 += "\x26\x4c\x43\x44\x0d";
		
		//发送消息
		str = str1 + str2;
		app->g_com.Write(str);
		str = "";
		str2 = "";
		
		//接收消息
		char buf[60] = {0};
		app->g_com.Read(buf, 60);
		Sleep(100);
		char *p = buf;
		char num[2] = {0};
		while (p != NULL)
		{
			p++;
			if (*p == '.')
			{
				num[0] = *(p-2);
				num[1] = *(p-1);
				break;
			}
			
		}
		int x;
		if (num[0] == ' ')
		{
			x = num[1] - '0';
		}
		else
		{
			x = (num[0] - '0') * 10 + (num[1] - '0');
		}
		UpdateData(FALSE);
		((CComboBox *)GetDlgItem(IDC_COMBO_M24))->SetCurSel(x);
		((CComboBox *)GetDlgItem(IDC_COMBO_M24))->EnableWindow(TRUE);
		((CButton *)GetDlgItem(IDC_M24))->EnableWindow(TRUE);
	}

	if (iPos == 0)
	{
		char temp[6] = { '\x4d', '\x45', '\x4e', '\x55', '\x32', '\x34' };
		for (i=0; i<6; i++)
		{
			menu[i] = temp[i];
		}
	}
	else
	{
		char temp[6] = { '\x4d', '\x45', '\x4e', '\x55', '\x32', '\x35' };
		for (i=0; i<6; i++)
		{
			menu[i] = temp[i];
		}
	}
	for (i=0; i<6; i++)
	{
		str2 += CString(menu[i]);
	}
	str2 += "\x26\x4c\x43\x44\x0d";
	
	//发送消息
	str = str1 + str2;
	app->g_com.Write(str);
	str = "";
	str2 = "";
	
	//接收消息
	char buf2[60] = {0};
	app->g_com.Read(buf2, 60);
	Sleep(100);
	char *p2 = buf2;
	char num2[2] = {0};
	while (p2 != NULL)
	{
		p2++;
		if (*p2 == '.')
		{
			num2[0] = *(p2-2);
			num2[1] = *(p2-1);
			break;
		}		
	}
	if (num2[0] == ' ')
	{
		x = num2[1] - '0';
	}
	else
	{
		x = (num2[0] - '0') * 10 + (num2[1] - '0');
	}
	UpdateData(FALSE);
	((CComboBox *)GetDlgItem(IDC_COMBO_M25))->SetCurSel(x);
	
	char temp[6] = { '\x4d', '\x45', '\x4e', '\x55', '\x34', '\x35' };
	for (i=0; i<6; i++)
	{
		str2 += CString(temp[i]);
	}
	str2 += "\x26\x4c\x43\x44\x0d";

	//发送消息
	str = str1 + str2;
	app->g_com.Write(str);
	str = "";
	str2 = "";
	
	//接收消息
	char buf3[100] = {0};
	app->g_com.Read(buf3, 100);
	Sleep(100);
	CString readstr;
	readstr.Format("%s", buf3);
	readstr = readstr.Left(50);
	readstr = readstr.Right(19);
	readstr.TrimLeft();
	readstr.TrimRight();
	m_m45 = readstr;
	
	UpdateData(FALSE);
	m_recordset->Close();
	m_recordset.Release();
}

void CSetDlg::OnUpdateM24() 
{
	// TODO: Add your control notification handler code here
	//命令
	CCalibrationApp *app = (CCalibrationApp *)AfxGetApp();
	int i;
	CString str2 = "";
	char menu[6] = { '\x4d', '\x45', '\x4e', '\x55', '\x32', '\x34' };
	for (i=0; i<6; i++)
	{
		str2 += CString(menu[i]);
	}
	str2 += "\x26\x4c\x43\x44\x0d";
	
	//发送消息
	str = str1 + str2;
	app->g_com.Write(str);
	str = "";
	
	//接收消息
	char buf[50];
	app->g_com.Read(buf, 50);
	Sleep(100);
	char *p = buf;
	char num[2];
	while (p != NULL)
	{
		p++;
		if (*p == '.')
		{
			num[0] = *(p-2);
			num[1] = *(p-1);
			break;
		}
		
	}
	int x;
	if (num[0] == ' ')
	{
		x = num[1] - '0';
	}
	else
	{
		x = (num[0] - '0') * 10 + (num[1] - '0');
	}
	UpdateData(FALSE);
	((CComboBox *)GetDlgItem(IDC_COMBO_M24))->SetCurSel(x);
	
}

void CSetDlg::OnUpdateM26() 
{
	// TODO: Add your control notification handler code here
	//命令
	CCalibrationApp *app = (CCalibrationApp *)AfxGetApp();
	int i;
	CString str2 = "";
	char menu[6] = { '\x4d', '\x45', '\x4e', '\x55', '\x32', '\x36' };
	for (i=0; i<6; i++)
	{
		str2 += CString(menu[i]);
	}
	str2 += "\x26\x4c\x43\x44\x0d";
	
	//发送消息
	str = str1 + str2;
	app->g_com.Write(str);
	str = "";
	
	//接收消息
	char buf[50];
	app->g_com.Read(buf, 50);
	Sleep(100);
	char *p = buf;
	char num[2];
	while (p != NULL)
	{
		p++;
		if (*p == '.')
		{
			num[0] = *(p-2);
			num[1] = *(p-1);
			break;
		}
		
	}
	int x;
	if (num[0] == ' ')
	{
		x = num[1] - '0';
	}
	else
	{
		x = (num[0] - '0') * 10 + (num[1] - '0');
	}
	UpdateData(FALSE);
	((CComboBox *)GetDlgItem(IDC_COMBO_M26))->SetCurSel(x);
}

void CSetDlg::OnM45() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	//获取netword_IDN
	CString s;
	int iPos = ((CComboBox *)GetDlgItem(IDC_COMBO_METER))->GetCurSel();
	((CComboBox *)GetDlgItem(IDC_COMBO_METER))->GetLBText(iPos, s);
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

	//命令
	CCalibrationApp *app = (CCalibrationApp *)AfxGetApp();
	char menu[6] = { '\x4d', '\x45', '\x4e', '\x55', '\x34', '\x35' };
	CString str2 = "";
	for (i=0; i<6; i++)
	{
		str2 += CString(menu[i]);
	}
	if (m_m45 != "")
	{
		float fm45;
		sscanf(m_m45, "%f", &fm45);
		if (fm45 > 1.5 || fm45 < 0.5)
		{
			if (app->language == 0)
			{
				AfxMessageBox("仪表系数必须在0.5~1.5之间!");
			}
			else
			{
				hHook=SetWindowsHookEx(WH_CBT,(HOOKPROC)CBTHookProc,AfxGetInstanceHandle(),NULL); 
				AfxMessageBox("Scale factor must be between 0.5 to 1.5! ");
			}
		}
		else
		{
			str += "\x26\x4d\x3d";

			for (i=0; i<m_m45.GetLength(); i++)
			{
				switch(m_m45.GetAt(i))
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
						hHook=SetWindowsHookEx(WH_CBT,(HOOKPROC)CBTHookProc,AfxGetInstanceHandle(),NULL); 
						AfxMessageBox("Your input is incorrect!");
					}
				}
			}
			str2 += "\x26\x4d\x3d\x0d";

			str = str1 + str2;
			app->g_com.Write(str);
			str = "";
			//修改数据库
			CString sql;
			sql.Format("update Independent_settings set scale_factor = %s where netword_IDN = %s", m_m45, s);
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
}

void CSetDlg::OnM48() 
{
	// TODO: Add your control notification handler code here
	line_array.DoModal();
}
void CSetDlg::OnM23() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	//获取netword_IDN
	CString s;
	int iPos = ((CComboBox *)GetDlgItem(IDC_COMBO_METER))->GetCurSel();
	((CComboBox *)GetDlgItem(IDC_COMBO_METER))->GetLBText(iPos, s);
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
	
	//命令
	CCalibrationApp *app = (CCalibrationApp *)AfxGetApp();
	char menu[6] = { '\x4d', '\x45', '\x4e', '\x55', '\x32', '\x33' };
	CString str2 = "";
	for (i=0; i<6; i++)
	{
		str2 += CString(menu[i]);
	}
	int iPos2 = ((CComboBox *)GetDlgItem(IDC_COMBO_M23))->GetCurSel();
	if (iPos2 == 3)
	{
		if (m_m231.IsEmpty() || m_m232.IsEmpty() || m_m233.IsEmpty() || m_m234.IsEmpty())
		{
			AfxMessageBox("Please check Wedge Degree, Sound Velocity, Distance or Time Delay cannot be empty.");
			return;
		}
		GetDlgItem(IDC_M23_1)->EnableWindow(TRUE);
		GetDlgItem(IDC_M23_2)->EnableWindow(TRUE);
		GetDlgItem(IDC_M23_3)->EnableWindow(TRUE);
		GetDlgItem(IDC_M23_4)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_M23_1)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_M23_2)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_M23_3)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_M23_4)->EnableWindow(TRUE);
		GetDlgItem(IDC_STATIC00)->EnableWindow(TRUE);
		GetDlgItem(IDC_STATIC01)->EnableWindow(TRUE);
		GetDlgItem(IDC_STATIC02)->EnableWindow(TRUE);
		GetDlgItem(IDC_STATIC03)->EnableWindow(TRUE);
		OnM231();
		Sleep(100);
		OnM232();
		Sleep(100);
		OnM233();
		Sleep(100);
		OnM234();
		Sleep(100);
	}
	else if (iPos2 == 24)
	{
		m_m231 = "38";
		m_m232 = "7447.51";
		m_m233 = "0.72441";
		m_m234 = "0.197";

		GetDlgItem(IDC_M23_1)->EnableWindow(FALSE);
		GetDlgItem(IDC_M23_2)->EnableWindow(FALSE);
		GetDlgItem(IDC_M23_3)->EnableWindow(FALSE);
		GetDlgItem(IDC_M23_4)->EnableWindow(FALSE);

		GetDlgItem(IDC_EDIT_M23_1)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_M23_1)->SetWindowTextA(m_m231);
		GetDlgItem(IDC_EDIT_M23_2)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_M23_1)->SetWindowTextA(m_m232);
		GetDlgItem(IDC_EDIT_M23_3)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_M23_1)->SetWindowTextA(m_m233);
		GetDlgItem(IDC_EDIT_M23_4)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_M23_1)->SetWindowTextA(m_m234);

		GetDlgItem(IDC_STATIC00)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC01)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC02)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC03)->EnableWindow(FALSE);

		OnM231();
		Sleep(100);
		OnM232();
		Sleep(100);
		OnM233();
		Sleep(100);
		OnM234();
		Sleep(100);
	}
	else if (iPos2 == 25)
	{
		m_m231 = "37";
		m_m232 = "7447.51";
		m_m233 = "0.23622";
		m_m234 = "0.215";

		GetDlgItem(IDC_M23_1)->EnableWindow(FALSE);
		GetDlgItem(IDC_M23_2)->EnableWindow(FALSE);
		GetDlgItem(IDC_M23_3)->EnableWindow(FALSE);
		GetDlgItem(IDC_M23_4)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_M23_1)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_M23_2)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_M23_3)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_M23_4)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC00)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC01)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC02)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC03)->EnableWindow(FALSE);

		OnM231();
		Sleep(100);
		OnM232();
		Sleep(100);
		OnM233();
		Sleep(100);
		OnM234();
		Sleep(100);
	}
	else if (iPos2 == 26)
	{
		m_m231 = "38";
		m_m232 = "8061.024";
		m_m233 = "0.314961";
		m_m234 = "0.215";

		GetDlgItem(IDC_M23_1)->EnableWindow(FALSE);
		GetDlgItem(IDC_M23_2)->EnableWindow(FALSE);
		GetDlgItem(IDC_M23_3)->EnableWindow(FALSE);
		GetDlgItem(IDC_M23_4)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_M23_1)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_M23_2)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_M23_3)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_M23_4)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC00)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC01)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC02)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC03)->EnableWindow(FALSE);

		OnM231();
		Sleep(100);
		OnM232();
		Sleep(100);
		OnM233();
		Sleep(100);
		OnM234();
		Sleep(100);
	}
	else if (iPos2 == 27)
	{
		m_m231 = "37";
		m_m232 = "8061.024";
		m_m233 = "0.275591";
		m_m234 = "0.21";

		GetDlgItem(IDC_M23_1)->EnableWindow(FALSE);
		GetDlgItem(IDC_M23_2)->EnableWindow(FALSE);
		GetDlgItem(IDC_M23_3)->EnableWindow(FALSE);
		GetDlgItem(IDC_M23_4)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_M23_1)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_M23_2)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_M23_3)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_M23_4)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC00)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC01)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC02)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC03)->EnableWindow(FALSE);

		OnM231();
		Sleep(100);
		OnM232();
		Sleep(100);
		OnM233();
		Sleep(100);
		OnM234();
		Sleep(100);
	}
	else if (iPos2 == 28)
	{
		m_m231 = "37";
		m_m232 = "8061.024";
		m_m233 = "0.551181";
		m_m234 = "0.21";

		GetDlgItem(IDC_M23_1)->EnableWindow(FALSE);
		GetDlgItem(IDC_M23_2)->EnableWindow(FALSE);
		GetDlgItem(IDC_M23_3)->EnableWindow(FALSE);
		GetDlgItem(IDC_M23_4)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_M23_1)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_M23_2)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_M23_3)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_M23_4)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC00)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC01)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC02)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC03)->EnableWindow(FALSE);

		OnM231();
		Sleep(100);
		OnM232();
		Sleep(100);
		OnM233();
		Sleep(100);
		OnM234();
		Sleep(100);
	}
	else if (iPos2 == 29)
	{
		m_m231 = "38";
		m_m232 = "8061.024";
		m_m233 = "0.314961";
		m_m234 = "0.214";

		GetDlgItem(IDC_M23_1)->EnableWindow(FALSE);
		GetDlgItem(IDC_M23_2)->EnableWindow(FALSE);
		GetDlgItem(IDC_M23_3)->EnableWindow(FALSE);
		GetDlgItem(IDC_M23_4)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_M23_1)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_M23_2)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_M23_3)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_M23_4)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC00)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC01)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC02)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC03)->EnableWindow(FALSE);

		OnM231();
		Sleep(100);
		OnM232();
		Sleep(100);
		OnM233();
		Sleep(100);
		OnM234();
		Sleep(100);
	}
	else if (iPos2 == 30)
	{
		m_m231 = "38";
		m_m232 = "7765.75";
		m_m233 = "0.866142";
		m_m234 = "0.18";

		GetDlgItem(IDC_M23_1)->EnableWindow(FALSE);
		GetDlgItem(IDC_M23_2)->EnableWindow(FALSE);
		GetDlgItem(IDC_M23_3)->EnableWindow(FALSE);
		GetDlgItem(IDC_M23_4)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_M23_1)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_M23_2)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_M23_3)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_M23_4)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC00)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC01)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC02)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC03)->EnableWindow(FALSE);

		OnM231();
		Sleep(100);
		OnM232();
		Sleep(100);
		OnM233();
		Sleep(100);
		OnM234();
		Sleep(100);
	}
	else if (iPos2 == 31)
	{
		m_m231 = "38";
		m_m232 = "7447.51";
		m_m233 = "0.842520";
		m_m234 = "0.164";

		GetDlgItem(IDC_M23_1)->EnableWindow(FALSE);
		GetDlgItem(IDC_M23_2)->EnableWindow(FALSE);
		GetDlgItem(IDC_M23_3)->EnableWindow(FALSE);
		GetDlgItem(IDC_M23_4)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_M23_1)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_M23_2)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_M23_3)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_M23_4)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC00)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC01)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC02)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC03)->EnableWindow(FALSE);

		OnM231();
		Sleep(100);
		OnM232();
		Sleep(100);
		OnM233();
		Sleep(100);
		OnM234();
		Sleep(100);
	}
	else if (iPos2 == 32)
	{
		m_m231 = "38";
		m_m232 = "7447.51";
		m_m233 = "1.348819";
		m_m234 = "0.27";

		GetDlgItem(IDC_M23_1)->EnableWindow(FALSE);
		GetDlgItem(IDC_M23_2)->EnableWindow(FALSE);
		GetDlgItem(IDC_M23_3)->EnableWindow(FALSE);
		GetDlgItem(IDC_M23_4)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_M23_1)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_M23_2)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_M23_3)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_M23_4)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC00)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC01)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC02)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC03)->EnableWindow(FALSE);

		OnM231();
		Sleep(100);
		OnM232();
		Sleep(100);
		OnM233();
		Sleep(100);
		OnM234();
		Sleep(100);
	}
	else if (iPos2 == 33)
	{
		m_m231 = "38";
		m_m232 = "7447.51";
		m_m233 = "2.077165";
		m_m234 = "0.197";

		GetDlgItem(IDC_M23_1)->EnableWindow(FALSE);
		GetDlgItem(IDC_M23_2)->EnableWindow(FALSE);
		GetDlgItem(IDC_M23_3)->EnableWindow(FALSE);
		GetDlgItem(IDC_M23_4)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_M23_1)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_M23_2)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_M23_3)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_M23_4)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC00)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC01)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC02)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC03)->EnableWindow(FALSE);

		OnM231();
		Sleep(100);
		OnM232();
		Sleep(100);
		OnM233();
		Sleep(100);
		OnM234();
		Sleep(100);
	}
	else if (iPos2 == 34)
	{
		m_m231 = "38";
		m_m232 = "7765.75";
		m_m233 = "0.866142";
		m_m234 = "0.101";

		GetDlgItem(IDC_M23_1)->EnableWindow(FALSE);
		GetDlgItem(IDC_M23_2)->EnableWindow(FALSE);
		GetDlgItem(IDC_M23_3)->EnableWindow(FALSE);
		GetDlgItem(IDC_M23_4)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_M23_1)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_M23_2)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_M23_3)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_M23_4)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC00)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC01)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC02)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC03)->EnableWindow(FALSE);

		OnM231();
		Sleep(100);
		OnM232();
		Sleep(100);
		OnM233();
		Sleep(100);
		OnM234();
		Sleep(100);
	}
	else
	{
		m_m231 = "";
		m_m232 = "";
		m_m233 = "";
		m_m234 = "";
		GetDlgItem(IDC_M23_1)->EnableWindow(FALSE);
		GetDlgItem(IDC_M23_2)->EnableWindow(FALSE);
		GetDlgItem(IDC_M23_3)->EnableWindow(FALSE);
		GetDlgItem(IDC_M23_4)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_M23_1)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_M23_2)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_M23_3)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_M23_4)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC00)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC01)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC02)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC03)->EnableWindow(FALSE);
	}
	
	//else
	//{
	//	m_m231 = "";
	//	m_m232 = "";
	//	m_m233 = "";
	//	m_m234 = "";
	//	GetDlgItem(IDC_M23_1)->EnableWindow(FALSE);
	//	GetDlgItem(IDC_M23_2)->EnableWindow(FALSE);
	//	GetDlgItem(IDC_M23_3)->EnableWindow(FALSE);
	//	GetDlgItem(IDC_M23_4)->EnableWindow(FALSE);
	//	GetDlgItem(IDC_EDIT_M23_1)->EnableWindow(FALSE);
	//	GetDlgItem(IDC_EDIT_M23_2)->EnableWindow(FALSE);
	//	GetDlgItem(IDC_EDIT_M23_3)->EnableWindow(FALSE);
	//	GetDlgItem(IDC_EDIT_M23_4)->EnableWindow(FALSE);
	//	GetDlgItem(IDC_STATIC00)->EnableWindow(FALSE);
	//	GetDlgItem(IDC_STATIC01)->EnableWindow(FALSE);
	//	GetDlgItem(IDC_STATIC02)->EnableWindow(FALSE);
	//	GetDlgItem(IDC_STATIC03)->EnableWindow(FALSE);
	//}

	if (iPos2 <= 9 && iPos2 >= 0)
	{
		str2 += "\x26\x4d\x3d"; 	
		//str2 += "\x26\x4d\(iPos2 + '0')";
		str2 += "\x26\x4d";
		CString temp;
		temp.Format("%d", iPos2);
		temp += '0';
		str2 += temp;
		str2 += "\x26\x4d\x3d\x0d";
	}
	else if (iPos2 <= 34 && iPos2 >= 24)
	{
		str2 += "\x26\x4d\x3d";
		iPos2 = 3;
		str2 += "\x26\x4d";
		CString temp;
		temp.Format("%d", iPos2);
		temp += '0';
		str2 += temp;
		str2 += "\x26\x4d\x3d\x0d";
	}
	else
	{
		str2 += "\x26\x4d\x3d"; 
		str2 += "\x26\x4d\x39";

		for (i=0; i<(iPos2-9); i++)
		{
			str2 += "\x26\x4d\x3f";
		}
		str2 += "\x26\x4d\x3d\x0d"; 
	}
	str = str1 + str2;
	app->g_com.Write(str);
	str = "";
	
	//修改数据库
	CString sql;
	sql.Format("update Independent_settings set transducer_type = %d where netword_IDN = %s", iPos2, s);
	try
	{
		m_pAppConn->Execute((_bstr_t)sql,NULL,adCmdText);
	}
	catch (_com_error e)
	{
		AfxMessageBox(e.ErrorMessage());
	}
}

void CSetDlg::OnM231() 
{
	// TODO: Add your control notification handler code here
	CString s;
	int iPos = ((CComboBox *)GetDlgItem(IDC_COMBO_METER))->GetCurSel();
	((CComboBox *)GetDlgItem(IDC_COMBO_METER))->GetLBText(iPos, s);
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
	//命令
	CCalibrationApp *app = (CCalibrationApp *)AfxGetApp();
	char menu[6] = {0x4d, 0x45, 0x4e, 0x55, 0x32, 0x33};
	CString str2 = "";
	for (i=0; i<6; i++)
	{
		str2 += CString(menu[i]);
	}
	str = str1 + str2 + "\x0d";

	app->g_com.Write(str);
	str = "";
	str2 = "";

	str2 += "\x4d\x3d";

	str = str1 + str2 + "\x0d";

	app->g_com.Write(str);
	str = "";
	str2 = "";

	str2 += "\x4d\x33";

	str = str1 + str2 + "\x0d";

	app->g_com.Write(str);
	str = "";
	str2 = "";

	str2 += "\x4d\x3d"; 

	str = str1 + str2 + "\x0d";

	app->g_com.Write(str);
	str = "";
	str2 = "";

	str2 += "\x4d\x3d";

	str = str1 + str2 + "\x0d";

	app->g_com.Write(str);
	str = "";
	str2 = "";
	UpdateData(TRUE);
	if (m_m231 != "")
	{	
		for (i=0; i<m_m231.GetLength(); i++)
		{
			switch(m_m231.GetAt(i))
			{
			case '0':
				str2 += "\x4d\x30\x0d";
				break;
			case '1':
				str2 += "\x4d\x31\x0d";
				break;
			case '2':
				str2 += "\x4d\x32\x0d";
				break;
			case '3':
				str2 += "\x4d\x33\x0d";
				break;
			case '4':
				str2 += "\x4d\x34\x0d";
				break;
			case '5':
				str2 += "\x4d\x35\x0d";
				break;
			case '6':
				str2 += "\x4d\x36\x0d";
				break;
			case '7':
				str2 += "\x4d\x37\x0d";
				break;
			case '8':
				str2 += "\x4d\x38\x0d";
				break;
			case '9':
				str2 += "\x4d\x39\x0d";
				break;
			case '.':
				str2 += "\x4d\x3a\x0d";
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
			str = str1 + str2;
			app->g_com.Write(str);
			str = "";
			str2 = "";
		}
	}

	str2 +="\x4d\x3d\x0d";

	str = str1 + str2;
	app->g_com.Write(str);
	str = "";
	str2 = "";

	CString sql;
	sql.Format("update Probe set wedge_degree = %s", m_m231, s);
	try
	{
		m_pAppConn->Execute((_bstr_t)sql,NULL,adCmdText);
	}
	catch (_com_error e)
	{
		AfxMessageBox(e.ErrorMessage());
	}
}

void CSetDlg::OnM232() 
{
	// TODO: Add your control notification handler code here
	CString s;
	int iPos = ((CComboBox *)GetDlgItem(IDC_COMBO_METER))->GetCurSel();
	((CComboBox *)GetDlgItem(IDC_COMBO_METER))->GetLBText(iPos, s);
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
	//命令
	CCalibrationApp *app = (CCalibrationApp *)AfxGetApp();
	char menu[6] = { '\x4d', '\x45', '\x4e', '\x55', '\x32', '\x33' };
	CString str2 = "";
	for (i=0; i<6; i++)
	{
		str2 += CString(menu[i]);
	}

	str = str1 + str2 + "\x0d";

	app->g_com.Write(str);
	str = "";
	str2 = "";

	str2 += "\x4d\x3d"; 

	str = str1 + str2 + "\x0d";

	app->g_com.Write(str);
	str = "";
	str2 = "";

	str2 += "\x4d\x33";

	str = str1 + str2 + "\x0d";

	app->g_com.Write(str);
	str = "";
	str2 = "";

	str2 += "\x4d\x3d"; 

	str = str1 + str2 + "\x0d";
	app->g_com.Write(str);
	str = "";
	str2 = "";

	str2 += "\x4d\x3f";

	str = str1 + str2 + "\x0d";

	app->g_com.Write(str);
	str = "";
	str2 = "";

	str2 += "\x4d\x3d";

	str = str1 + str2 + "\x0d";

	app->g_com.Write(str);
	str = "";
	str2 = "";

	UpdateData(TRUE);
	if (m_m232 != "")
	{	
		for (i=0; i<m_m232.GetLength(); i++)
		{
			switch(m_m232.GetAt(i))
			{
			case '0':
				str2 += "\x4d\x30\x0d";
				break;
			case '1':
				str2 += "\x4d\x31\x0d";
				break;
			case '2':
				str2 += "\x4d\x32\x0d";
				break;
			case '3':
				str2 += "\x4d\x33\x0d";
				break;
			case '4':
				str2 += "\x4d\x34\x0d";
				break;
			case '5':
				str2 += "\x4d\x35\x0d";
				break;
			case '6':
				str2 += "\x4d\x36\x0d";
				break;
			case '7':
				str2 += "\x4d\x37\x0d";
				break;
			case '8':
				str2 += "\x4d\x38\x0d";
				break;
			case '9':
				str2 += "\x4d\x39\x0d";
				break;
			case '.':
				str2 += "\x4d\x3a\x0d";
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
			str = str1 + str2;
			app->g_com.Write(str);
			str = "";
			str2 = "";
		}
	}

	str2 += "\x26\x4d\x3d\x0d";

	str = str1 + str2;
	app->g_com.Write(str);
	str = "";
	str2 = "";

	CString sql;
	sql.Format("update Probe set wedge_sound_velocity = %s", m_m232, s);
	try
	{
		m_pAppConn->Execute((_bstr_t)sql,NULL,adCmdText);
	}
	catch (_com_error e)
	{
		AfxMessageBox(e.ErrorMessage());
	}
}

void CSetDlg::OnM233() 
{
	// TODO: Add your control notification handler code here
	CString s;
	int iPos = ((CComboBox *)GetDlgItem(IDC_COMBO_METER))->GetCurSel();
	((CComboBox *)GetDlgItem(IDC_COMBO_METER))->GetLBText(iPos, s);
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
	//命令
	CCalibrationApp *app = (CCalibrationApp *)AfxGetApp();
	char menu[6] = { '\x4d', '\x45', '\x4e', '\x55', '\x32', '\x33' };
	CString str2 = "";
	for (i=0; i<6; i++)
	{
		str2 += CString(menu[i]);
	}

	str = str1 + str2 + "\x0d";

	app->g_com.Write(str);
	str = "";
	str2 = "";

	str2 += "\x4d\x3d"; 

	str = str1 + str2 + "\x0d";

	app->g_com.Write(str);
	str = "";
	str2 = "";

	str2 += "\x4d\x33";

	str = str1 + str2 + "\x0d";

	app->g_com.Write(str);
	str = "";
	str2 = "";

	str2 += "\x4d\x3d"; 

	str = str1 + str2 + "\x0d";

	app->g_com.Write(str);
	str = "";
	str2 = "";

	str2 += "\x4d\x3f";

	str = str1 + str2 +"\x0d";

	app->g_com.Write(str);
	str = "";
	str2 = "";

	str2 += "\x4d\x3f";

	str = str1 + str2 + "\x0d";

	app->g_com.Write(str);
	str = "";
	str2 = "";

	str2 += "\x4d\x3d";

	str = str1 + str2 + "\x0d";

	app->g_com.Write(str);
	str = "";
	str2 = "";
	UpdateData(TRUE);
	if (m_m233 != "")
	{	
		for (i=0; i<m_m233.GetLength(); i++)
		{
			switch(m_m233.GetAt(i))
			{
			case '0':
				str2 += "\x4d\x30\x0d";
				break;
			case '1':
				str2 += "\x4d\x31\x0d";
				break;
			case '2':
				str2 += "\x4d\x32\x0d";
				break;
			case '3':
				str2 += "\x4d\x33\x0d";
				break;
			case '4':
				str2 += "\x4d\x34\x0d";
				break;
			case '5':
				str2 += "\x4d\x35\x0d";
				break;
			case '6':
				str2 += "\x4d\x36\x0d";
				break;
			case '7':
				str2 += "\x4d\x37\x0d";
				break;
			case '8':
				str2 += "\x4d\x38\x0d";
				break;
			case '9':
				str2 += "\x4d\x39\x0d";
				break;
			case '.':
				str2 += "\x4d\x3a\x0d";
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
			str = str1 + str2;
			app->g_com.Write(str);
			str = "";
			str2 = "";
		}
	}

	str2 += "\x26\x4d\x3d\x0d";

	str = str1 + str2;
	app->g_com.Write(str);
	str = "";
	str2 = "";

	CString sql;
	sql.Format("update Probe set wedge_distance = %s", m_m233, s);
	try
	{
		m_pAppConn->Execute((_bstr_t)sql,NULL,adCmdText);
	}
	catch (_com_error e)
	{
		AfxMessageBox(e.ErrorMessage());
	}
}

void CSetDlg::OnM234() 
{
	// TODO: Add your control notification handler code here
	CString s;
	int iPos = ((CComboBox *)GetDlgItem(IDC_COMBO_METER))->GetCurSel();
	((CComboBox *)GetDlgItem(IDC_COMBO_METER))->GetLBText(iPos, s);
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
	//命令
	CCalibrationApp *app = (CCalibrationApp *)AfxGetApp();
	char menu[6] = { '\x4d', '\x45', '\x4e', '\x55', '\x32', '\x33' };
	CString str2 = "";
	for (i=0; i<6; i++)
	{
		str2 += CString(menu[i]);
	}

	str = str1 + str2 + "\x0d";

	app->g_com.Write(str);
	str = "";
	str2 = "";

	str2 += "\x4d\x3d";

	str = str1 + str2 + "\x0d";

	app->g_com.Write(str);
	str = "";
	str2 = "";

	str2 += "\x4d\x3d";

	str = str1 + str2 + "\x0d";

	app->g_com.Write(str);
	//str = "";
	//str2 = "";

	//str2 += "\x4d\x3d";

	//str = str1 + str2 + "\x0d";

	//app->g_com.Write(str);
	str = "";
	str2 = "";

	str2 += "\x4d\x3f";

	str = str1 + str2 + "\x0d";

	app->g_com.Write(str);
	str = "";
	str2 = "";

	str2 += "\x4d\x3f";

	str = str1 + str2 + "\x0d";

	app->g_com.Write(str);
	str = "";
	str2 = "";

	str2 += "\x4d\x3f";

	str = str1 + str2 + "\x0d";

	app->g_com.Write(str);
	str = "";
	str2 = "";

	str2 += "\x4d\x3d";

	str = str1 + str2 + "\x0d";

	app->g_com.Write(str);
	str = "";
	str2 = "";
	UpdateData(TRUE);
	if (m_m234 != "")
	{	
		for (i=0; i<m_m234.GetLength(); i++)
		{
			switch(m_m234.GetAt(i))
			{
			case '0':
				str2 += "\x4d\x30\x0d";
				break;
			case '1':
				str2 += "\x4d\x31\x0d";
				break;
			case '2':
				str2 += "\x4d\x32\x0d";
				break;
			case '3':
				str2 += "\x4d\x33\x0d";
				break;
			case '4':
				str2 += "\x4d\x34\x0d";
				break;
			case '5':
				str2 += "\x4d\x35\x0d";
				break;
			case '6':
				str2 += "\x4d\x36\x0d";
				break;
			case '7':
				str2 += "\x4d\x37\x0d";
				break;
			case '8':
				str2 += "\x4d\x38\x0d";
				break;
			case '9':
				str2 += "\x4d\x39\x0d";
				break;
			case '.':
				str2 += "\x4d\x3a\x0d";
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
			str = str1 + str2;
			app->g_com.Write(str);
			str = "";
			str2 = "";
		}
	}

	str2 += "\x4d\x3d\x0d";

	str = str1 + str2;
	app->g_com.Write(str);
	str = "";
	str2 = "";

	CString sql;
	sql.Format("update Probe set wedge_time_delay = %s", m_m234, s);
	try
	{
		m_pAppConn->Execute((_bstr_t)sql,NULL,adCmdText);
	}
	catch (_com_error e)
	{
		AfxMessageBox(e.ErrorMessage());
	}
}

void CSetDlg::OnM24() 
{
	// TODO: Add your control notification handler code here
	
	//获取netword_IDN
	CString s;
	int iPos = ((CComboBox *)GetDlgItem(IDC_COMBO_METER))->GetCurSel();
	
	((CComboBox *)GetDlgItem(IDC_COMBO_METER))->GetLBText(iPos, s);
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
	
	//命令
	CCalibrationApp *app = (CCalibrationApp *)AfxGetApp();
	char menu[6] = { '\x4d', '\x45', '\x4e', '\x55', '\x32', '\x34' };
	CString str2 = "";
	for (i=0; i<6; i++)
	{
		str2 += CString(menu[i]);
	}
	int iPos2 = ((CComboBox *)GetDlgItem(IDC_COMBO_M24))->GetCurSel();
	CString sql;
	int biaoleixing;
	sql.Format("SELECT table_type FROM Independent_settings where netword_IDN = %s", s);
	try
	{
		m_recordset = m_pAppConn->Execute((_bstr_t)sql,NULL,adCmdText);
		_variant_t var = m_recordset->GetCollect("table_type");
		CString str = (char *)_bstr_t(var);
		sscanf(str, "%d", &biaoleixing);
	}
	catch (_com_error e)
	{
		AfxMessageBox(e.ErrorMessage());
	}
	if (biaoleixing == 1)
	{
		str2 += "\x26\x4d\x3d";
		//str2 += "\x26\x4d\(iPos2 + '0')";
		str2 += "\x26\x4d";
		CString temp;
		temp.Format("%d", iPos2);
		temp += '0';
		str2 += temp;
		str2 += "\x26\x4d\x3d";
		str2 += "\x26\x4d\x32";
		str2 += "\x26\x4d\x32";
		str2 += "\x26\x4d\x32";
		str2 += "\x26\x4d\x32";
		str2 += "\x26\x4d\x3d\x0d";

		str = str1 + str2;
		app->g_com.Write(str);
		str = ""; 
		//修改数据库
		CString sql;
		sql.Format("update Independent_settings set transducer_frequency = %d where netword_IDN = %s", iPos2, s);
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

void CSetDlg::OnM25() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	//获取netword_IDN
	CString s;
	int iPos = ((CComboBox *)GetDlgItem(IDC_COMBO_METER))->GetCurSel();
	((CComboBox *)GetDlgItem(IDC_COMBO_METER))->GetLBText(iPos, s);
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
	CString sql;
	int biaoleixing;
	sql.Format("SELECT table_type FROM Independent_settings where netword_IDN = %s", s);
	try
	{
		m_recordset = m_pAppConn->Execute((_bstr_t)sql,NULL,adCmdText);
		_variant_t var = m_recordset->GetCollect("table_type");
		CString str = (char *)_bstr_t(var);
		sscanf(str, "%d", &biaoleixing);
	}
	catch (_com_error e)
	{
		AfxMessageBox(e.ErrorMessage());
	}
	//命令
	CCalibrationApp *app = (CCalibrationApp *)AfxGetApp();
	char menu[6] = {0};
	if(biaoleixing == 0)
	{
		char temp[6] = { '\x4d', '\x45', '\x4e', '\x55', '\x32', '\x34' };
		for (i=0; i<6; i++)
		{
			menu[i] = temp[i];
		}
	}
	else
	{
		char temp[6] = { '\x4d', '\x45', '\x4e', '\x55', '\x32', '\x35' };
		for (i=0; i<6; i++)
		{
			menu[i] = temp[i];
		}
	}
	CString str2 = "";
	for (i=0; i<6; i++)
	{
		str2 += menu[i];
	}
	int iPos2 = ((CComboBox *)GetDlgItem(IDC_COMBO_M25))->GetCurSel();

	str2 += "\x26\x4d\x3d"; 	
	//str2 += "\x26\x4d\(iPos2 + '0')";
	str2 += "\x26\x4d";
	CString temp;
	temp.Format("%d", iPos2);
	temp += '0';
	str2 += temp;
	str2 += "\x26\x4d\x3d\x0d";

	str = str1 + str2;
	app->g_com.Write(str);
	str = "";

	//修改数据库
	sql.Format("update Independent_settings set transducer_mounting = %d where netword_IDN = %s", iPos2, s);
	try
	{
		m_pAppConn->Execute((_bstr_t)sql,NULL,adCmdText);
	}
	catch (_com_error e)
	{
		AfxMessageBox(e.ErrorMessage());
	}
	//OnM26();
}

void CSetDlg::OnM26() 
{
/*	// TODO: Add your control notification handler code here
	//获取netword_IDN
	CString s;
	int iPos = ((CComboBox *)GetDlgItem(IDC_COMBO_METER))->GetCurSel();
	((CComboBox *)GetDlgItem(IDC_COMBO_METER))->GetLBText(iPos, s);
	s.Delete(0, 10);
	int len = s.GetLength();
	int i;
	
	//W前缀
	str1 = CString(0x57);
	for (i=0; i<len; i++)
	{
		switch(s.GetAt(i))
		{
		case '0':
			str1 += CString(0x30);
			break;
		case '1':
			str1 += CString(0x31);
			break;
		case '2':
			str1 += CString(0x32);
			break;
		case '3':
			str1 += CString(0x33);
			break;
		case '4':
			str1 += CString(0x34);
			break;
		case '5':
			str1 += CString(0x35);
			break;
		case '6':
			str1 += CString(0x36);
			break;
		case '7':
			str1 += CString(0x37);
			break;
		case '8':
			str1 += CString(0x38);
			break;
		case '9':
			str1 += CString(0x39);
			break;
		}
	}
	CString sql;
	int biaoleixing;
	sql.Format("SELECT table_type FROM Independent_settings where netword_IDN = %s", s);
	try
	{
		m_recordset = m_pAppConn->Execute((_bstr_t)sql,NULL,adCmdText);
		_variant_t var = m_recordset->GetCollect("table_type");
		CString str = (char *)_bstr_t(var);
		sscanf(str, "%d", &biaoleixing);
	}
	catch (_com_error e)
	{
		AfxMessageBox(e.ErrorMessage());
	}
	//命令
	CCalibrationApp *app = (CCalibrationApp *)AfxGetApp();
	int menu[6] = {0};
	if(biaoleixing == 0)
	{
		int temp[6] = {0x4d, 0x45, 0x4e, 0x55, 0x32, 0x35};
		for (i=0; i<6; i++)
		{
			menu[i] = temp[i];
		}
	}
	else
	{
		int temp[6] = {0x4d, 0x45, 0x4e, 0x55, 0x32, 0x36};	
		for (i=0; i<6; i++)
		{
			menu[i] = temp[i];
		}
	}
	CString str2 = "";
	for (i=0; i<6; i++)
	{
		str2 += CString(menu[i]);
	}
	str2 += CString(0x26) + CString(0x4c) + CString(0x43) + CString(0x44) + CString(0x0d);
	str = str1 + str2;
	app->g_com.Write(str);
	
	str = "";

	char buf[100] = {0};
	app->g_com.Read(buf, 100);
	Sleep(100);                
	char *p = buf;

	while (*p != '\0')
	{
		p++;
		if (biaoleixing == 0)
		{
			if (*p == 'M'&& *(p+1) == '2' && *(p+2) == '5' || *p == 'i' && *(p+1) == 'n' && *(p+2) == 'g')
			{
				p += 3;
				break;
			}
		}
		else
		{
			if (*p == 'M'&& *(p+1) == '2' && *(p+2) == '6' || *p == 'i' && *(p+1) == 'n' && *(p+2) == 'g')
			{
				p += 3;
				break;
			}
		}	
	}
	char res[10] = {0};
	int n = 0;
	while (*p != '\0')
	{
		if (*p <= '9' && *p >= '0' || *p == '.' || *p == '-' || *p == 'E')
		{
			res[n++] = *p;
		}
		p++;
	}
	res[n] = '\0';

	//修改数据库
	sql.Format("update Independent_settings set 传感器安装距离 = %s where netword_IDN = %s", res, s);
	try
	{
		m_pAppConn->Execute((_bstr_t)sql,NULL,adCmdText);
	}
	catch (_com_error e)
	{
		AfxMessageBox(e.ErrorMessage());
	}*/
}

void delay_ms(unsigned int x)
{
	unsigned int i;
	while (x--)
	{
		for (i=0; i<125000; i++)
		{
			;
		}
	}
}

void CSetDlg::OnQuickSet2() 
{
	// TODO: Add your control notification handler code here
	CCalibrationApp *app = (CCalibrationApp *)AfxGetApp();
	GetDlgItem(IDC_STATIC_AUTO2)->ShowWindow(SW_SHOW);
	CString show;
	if (app->language == 0)
	{
		show.Format("设置中。。。%.2f%c", (float)0/5*100, '%');
	}
	else
	{
		show.Format("Settings...%.2f%c", (float)0/5*100, '%');
	}
	GetDlgItem(IDC_STATIC_AUTO2)->SetWindowText(show);

	int transId = ((CComboBox *)GetDlgItem(IDC_COMBO_M23))->GetCurSel();
	if (transId == 3)
	{
		if (m_m231.IsEmpty() || m_m232.IsEmpty() || m_m233.IsEmpty() || m_m234.IsEmpty())
		{
			AfxMessageBox("Please check Wedge Degree, Sound Velocity, Distance or Time Delay cannot be empty.");
			return;
		}
	}
	OnM23();
	delay_ms(500);
	if (app->language == 0)
	{
		show.Format("设置中。。。%.2f%c", (float)1/5*100, '%');
	}
	else
	{
		show.Format("Settings...%.2f%c", (float)1/5*100, '%');
	}
	GetDlgItem(IDC_STATIC_AUTO2)->SetWindowText(show);

	OnM24();
	delay_ms(500);
	if (app->language == 0)
	{
		show.Format("设置中。。。%.2f%c", (float)2/5*100, '%');
	}
	else
	{
		show.Format("Settings...%.2f%c", (float)2/5*100, '%');
	}
	GetDlgItem(IDC_STATIC_AUTO2)->SetWindowText(show);

	//OnM26();
	delay_ms(500);
	if (app->language == 0)
	{
		show.Format("设置中。。。%.2f%c", (float)3/5*100, '%');
	}
	else
	{
		show.Format("Settings...%.2f%c", (float)3/5*100, '%');
	}
	GetDlgItem(IDC_STATIC_AUTO2)->SetWindowText(show);

	OnM45();
	delay_ms(500);
	if (app->language == 0)
	{
		show.Format("设置中。。。%.2f%c", (float)4/5*100, '%');
	}
	else
	{
		show.Format("Settings...%.2f%c", (float)4/5*100, '%');
	}
	GetDlgItem(IDC_STATIC_AUTO2)->SetWindowText(show);

	OnM25();
	if (app->language == 0)
	{
		show.Format("设置中。。。%.2f%c", (float)5/5*100, '%');
	}
	else
	{
		show.Format("Settings...%.2f%c", (float)5/5*100, '%');
	}
	GetDlgItem(IDC_STATIC_AUTO2)->SetWindowText(show);

	delay_ms(500);
	if (app->language == 0)
	{
		GetDlgItem(IDC_STATIC_AUTO2)->SetWindowText("设置成功");
	}
	else
	{
		GetDlgItem(IDC_STATIC_AUTO2)->SetWindowText("Set success");
	}	
}

void CSetDlg::OnQuickSet() 
{
	// TODO: Add your control notification handler code here
	CCalibrationApp *app = (CCalibrationApp *)AfxGetApp();
	GetDlgItem(IDC_STATIC_AUTO)->ShowWindow(SW_SHOW);
	CString show;
	if (app->language == 0)
	{
		show.Format("设置中。。。%.2f%c", (float)0/18*100, '%');
	}
	else
	{
		show.Format("Settings...%.2f%c", (float)0/18*100, '%');
	}
	GetDlgItem(IDC_STATIC_AUTO)->SetWindowText(show);

	OnM30();
	delay_ms(500);
	if (app->language == 0)
	{
		show.Format("设置中。。。%.2f%c", (float)1/18*100, '%');
	}
	else
	{
		show.Format("Settings...%.2f%c", (float)1/18*100, '%');
	}
	GetDlgItem(IDC_STATIC_AUTO)->SetWindowText(show);
	OnM11();
	delay_ms(500);
	if (app->language == 0)
	{
		show.Format("设置中。。。%.2f%c", (float)2/18*100, '%');
	}
	else
	{
		show.Format("Settings...%.2f%c", (float)2/18*100, '%');
	}
	GetDlgItem(IDC_STATIC_AUTO)->SetWindowText(show);

	OnM12();
	delay_ms(500);
	if (app->language == 0)
	{
		show.Format("设置中。。。%.2f%c", (float)3/18*100, '%');
	}
	else
	{
		show.Format("Settings...%.2f%c", (float)3/18*100, '%');
	}
	GetDlgItem(IDC_STATIC_AUTO)->SetWindowText(show);

	OnM13();
	delay_ms(500);
	if (app->language == 0)
	{
		show.Format("设置中。。。%.2f%c", (float)4/18*100, '%');
	}
	else
	{
		show.Format("Settings...%.2f%c", (float)4/18*100, '%');
	}
	GetDlgItem(IDC_STATIC_AUTO)->SetWindowText(show);
	OnM14();
	delay_ms(500);
	if (app->language == 0)
	{
		show.Format("设置中。。。%.2f%c", (float)5/18*100, '%');
	}
	else
	{
		show.Format("Settings...%.2f%c", (float)5/18*100, '%');
	}
	GetDlgItem(IDC_STATIC_AUTO)->SetWindowText(show);

	OnM16();
	delay_ms(500);
	if (app->language == 0)
	{
		show.Format("设置中。。。%.2f%c", (float)6/18*100, '%');
	}
	else
	{
		show.Format("Settings...%.2f%c", (float)6/18*100, '%');
	}
	GetDlgItem(IDC_STATIC_AUTO)->SetWindowText(show);

	OnM18();
	delay_ms(500);
	if (app->language == 0)
	{
		show.Format("设置中。。。%.2f%c", (float)7/18*100, '%');
	}
	else
	{
		show.Format("Settings...%.2f%c", (float)7/18*100, '%');
	}
	GetDlgItem(IDC_STATIC_AUTO)->SetWindowText(show);

	OnM20();
	delay_ms(500);
	if (app->language == 0)
	{
		show.Format("设置中。。。%.2f%c", (float)8/18*100, '%');
	}
	else
	{
		show.Format("Settings...%.2f%c", (float)8/18*100, '%');
	}
	GetDlgItem(IDC_STATIC_AUTO)->SetWindowText(show);

	OnM31();
	delay_ms(500);
	if (app->language == 0)
	{
		show.Format("设置中。。。%.2f%c", (float)9/18*100, '%');
	}
	else
	{
		show.Format("Settings...%.2f%c", (float)9/18*100, '%');
	}
	GetDlgItem(IDC_STATIC_AUTO)->SetWindowText(show);

	OnM32();
	delay_ms(500);
	if (app->language == 0)
	{
		show.Format("设置中。。。%.2f%c", (float)10/18*100, '%');
	}
	else
	{
		show.Format("Settings...%.2f%c", (float)10/18*100, '%');
	}
	GetDlgItem(IDC_STATIC_AUTO)->SetWindowText(show);

	OnM33();
	delay_ms(500);
	if (app->language == 0)
	{
		show.Format("设置中。。。%.2f%c", (float)11/18*100, '%');
	}
	else
	{
		show.Format("Settings...%.2f%c", (float)11/18*100, '%');
	}
	GetDlgItem(IDC_STATIC_AUTO)->SetWindowText(show);

	OnM34();
	delay_ms(500);
	if (app->language == 0)
	{
		show.Format("设置中。。。%.2f%c", (float)12/18*100, '%');
	}
	else
	{
		show.Format("Settings...%.2f%c", (float)12/18*100, '%');
	}
	GetDlgItem(IDC_STATIC_AUTO)->SetWindowText(show);

	OnM35();
	delay_ms(500);
	if (app->language == 0)
	{
		show.Format("设置中。。。%.2f%c", (float)13/18*100, '%');
	}
	else
	{
		show.Format("Settings...%.2f%c", (float)13/18*100, '%');
	}
	GetDlgItem(IDC_STATIC_AUTO)->SetWindowText(show);

	OnM36();
	delay_ms(500);
	if (app->language == 0)
	{
		show.Format("设置中。。。%.2f%c", (float)14/18*100, '%');
	}
	else
	{
		show.Format("Settings...%.2f%c", (float)14/18*100, '%');
	}
	GetDlgItem(IDC_STATIC_AUTO)->SetWindowText(show);

	OnM37();
	delay_ms(500);
	if (app->language == 0)
	{
		show.Format("设置中。。。%.2f%c", (float)15/18*100, '%');
	}
	else
	{
		show.Format("Settings...%.2f%c", (float)15/18*100, '%');
	}
	GetDlgItem(IDC_STATIC_AUTO)->SetWindowText(show);

	OnM39();
	delay_ms(500);
	if (app->language == 0)
	{
		show.Format("设置中。。。%.2f%c", (float)16/18*100, '%');
	}
	else
	{
		show.Format("Settings...%.2f%c", (float)16/18*100, '%');
	}
	GetDlgItem(IDC_STATIC_AUTO)->SetWindowText(show);

	OnM40();
	delay_ms(500);
	if (app->language == 0)
	{
		show.Format("设置中。。。%.2f%c", (float)17/18*100, '%');
	}
	else
	{
		show.Format("Settings...%.2f%c", (float)17/18*100, '%');
	}
	GetDlgItem(IDC_STATIC_AUTO)->SetWindowText(show);

	OnM79();
	delay_ms(500);
	if (app->language == 0)
	{
		show.Format("设置中。。。%.2f%c", (float)18/18*100, '%');
	}
	else
	{
		show.Format("Settings...%.2f%c", (float)18/18*100, '%');
	}
	GetDlgItem(IDC_STATIC_AUTO)->SetWindowText(show);
	delay_ms(500);
	if (app->language == 0)
	{
		GetDlgItem(IDC_STATIC_AUTO)->SetWindowText("设置成功");
	}
	else
	{
		GetDlgItem(IDC_STATIC_AUTO)->SetWindowText("Set success");
	}
}

HBRUSH CSetDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here
	if( pWnd->GetDlgCtrlID() == IDC_STATIC_AUTO )
	{
		pDC->SetTextColor(RGB(255,0,0)); //字体颜色
    }
	if( pWnd->GetDlgCtrlID() == IDC_STATIC_AUTO2 )
	{
		pDC->SetTextColor(RGB(255,0,0)); //字体颜色
    }
	if (pWnd->GetDlgCtrlID() == IDC_STATIC)
	{
		pDC->SetTextColor(RGB(255, 0, 0)); //字体颜色
	}
	// TODO: Return a different brush if the default is not desired
	return hbr;
}

void CSetDlg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	CCalibrationApp *app = (CCalibrationApp *)AfxGetApp();
	CString sql;
	UpdateData(TRUE);
	int l1 = ((CComboBox *)GetDlgItem(IDC_COMBO_M23))->GetCurSel();
	int l6 = ((CComboBox *)GetDlgItem(IDC_COMBO_M24))->GetCurSel();
	int l7 = ((CComboBox *)GetDlgItem(IDC_COMBO_M25))->GetCurSel();
	CString l8; 
	l8 = m_m45;
	if (m_m45 == "")
	{
		l8.Format("0");
	}
	
	CString l2, l3, l4, l5;
	if (l1 == 3)
	{	
		l2 = m_m231;
		l3 = m_m232;
		l4 = m_m233;
		l5 = m_m234;
		if (m_m231 == "")
		{
			l2.Format("0");
		}
		if (m_m232 == "")
		{
			l3.Format("0");
		}
		if (m_m233 == "")
		{
			l4.Format("0");
		}
		if (m_m234 == "")
		{
			l5.Format("0");
		}	
		sql.Format("UPDATE Logo SET l1=%d,l2=%s,l3=%s,l4=%s,l5=%s,l6=%d,l7=%d,l8=%s", l1, l2, l3, l4, l5, l6, l7, l8);
	}
	else
	{
		sql.Format("UPDATE Logo SET l1=%d,l2=%s,l3=%s,l4=%s,l5=%s,l6=%d,l7=%d,l8=%s", l1, NULL, NULL, NULL, NULL, l6, l7, l8);
	}
	try
	{
		m_pAppConn->Execute((_bstr_t)sql,NULL,adCmdText);
	}
	catch (_com_error e)
	{
		AfxMessageBox(e.ErrorMessage());
	}
	
	int i;
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

			str2 = "\x4d\x3d\x0d";

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
	//m_pAppConn->Close();
	//m_pAppConn.Release();

	if (m_recordset)
		if (m_recordset->State == adStateOpen)
			m_recordset->Close();
	if (m_pAppConn)
		if (m_pAppConn->State == adStateOpen)
			m_pAppConn->Close();

	m_pAppConn.Release();
	Sleep(3000);
	CDialog::OnClose();

}

void CSetDlg::OnDestroy()
{
	CDialog::OnDestroy();
	this->DestroyWindow();
	::PostQuitMessage(0);
}

void CSetDlg::OnCopy() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	leixing = ((CComboBox *)GetDlgItem(IDC_COMBO_M23))->GetCurSel();
	jiaodu = m_m231;
	shengsu	 = m_m232;
	juli = m_m233;
	shijian = m_m234;
	pinlv = ((CComboBox *)GetDlgItem(IDC_COMBO_M24))->GetCurSel();
	fangfa = ((CComboBox *)GetDlgItem(IDC_COMBO_M25))->GetCurSel();
	xishu = m_m45;
	UpdateData(FALSE);
}

void CSetDlg::OnChangeEditM11() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	UpdateData(true);
	float w, h, n;
	sscanf(m_m11, "%f", &w);
	sscanf(m_m12, "%f", &h);
	n = w - 2*h;
	m_m13.Format("%.3f", n);
	UpdateData(FALSE);
	// TODO: Add your control notification handler code here
	
}

void CSetDlg::OnChangeEditM12() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	UpdateData(true);
	float w, h, n;
	sscanf(m_m11, "%f", &w);
	sscanf(m_m12, "%f", &h);
	n = w - 2*h;
	m_m13.Format("%.3f", n);
	UpdateData(FALSE);
	// TODO: Add your control notification handler code here
	
}

void CSetDlg::OnMulset() 
{
	// TODO: Add your control notification handler code here
	//transducer_type
	CCalibrationApp *app = (CCalibrationApp *)AfxGetApp();
	int i;
	char menu[6] = { '\x4d', '\x45', '\x4e', '\x55', '\x32', '\x33' };
	CString str2 = "";
	for (i=0; i<6; i++)
	{
		str2 += CString(menu[i]);
	}
	int iPos = ((CComboBox *)GetDlgItem(IDC_COMBO_M23))->GetCurSel();

	if (iPos <= 9 && iPos >= 0)
	{
		str2 += "\x26\x4d\x3d";
		//str2 += "\x26\x4d\(iPos + '0')";
		str2 += "\x26\x4d";
		CString temp;
		temp.Format("%d", iPos);
		temp += '0';
		str2 += temp;
		str2 += "\x26\x4d\x3d\x0d";
	}
	else
	{
		str2 += "\x26\x4d\x3d";
		str2 += "\x26\x4d\x39";

		for (i=0; i<(iPos-9); i++)
		{
			str2 += "\x26\x4d\x3f";
		}
		str2 += "\x26\x4d\x3d\x0d";
	}
	app->g_com.Write(str2);
	Sleep(100);
	str2 = "";

	CString sql;
	sql.Format("update Independent_settings set transducer_type = %d", iPos);
	try
	{
		m_pAppConn->Execute((_bstr_t)sql,NULL,adCmdText);
	}
	catch (_com_error e)
	{
		AfxMessageBox(e.ErrorMessage());
	}
	if (iPos == 3)
	{
		str2 = "\x4d\x3d\x0d"; 

		app->g_com.Write(str2);
		str2 = "";
		UpdateData(TRUE);
		for (i=0; i<m_m231.GetLength(); i++)
		{
			switch(m_m231.GetAt(i))
			{
			case '0':
				str2 += "\x4d\x30\x0d";
				break;
			case '1':
				str2 += "\x4d\x31\x0d";
				break;
			case '2':
				str2 += "\x4d\x32\x0d";
				break;
			case '3':
				str2 += "\x4d\x33\x0d";
				break;
			case '4':
				str2 += "\x4d\x34\x0d";
				break;
			case '5':
				str2 += "\x4d\x35\x0d";
				break;
			case '6':
				str2 += "\x4d\x36\x0d";
				break;
			case '7':
				str2 += "\x4d\x37\x0d";
				break;
			case '8':
				str2 += "\x4d\x38\x0d";
				break;
			case '9':
				str2 += "\x4d\x39\x0d";
				break;
			case '.':
				str2 += "\x4d\x3a\x0d";
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
			app->g_com.Write(str2);
			str2 = "";
		}

		str2 += "\x4d\x3d\x0d";

		app->g_com.Write(str2);
		Sleep(100);
		str2 = "";

		str2 += str2 += "\x4d\x3f";

		str2 += "\x0d";

		app->g_com.Write(str2);
		str2 = "";

		str2 += "\x4d\x3d";

		str2 +="\x0d";

		app->g_com.Write(str2);
		str2 = "";
		for (i=0; i<m_m232.GetLength(); i++)
		{
			switch(m_m232.GetAt(i))
			{
			case '0':
				str2 += "\x4d\x30\x0d";
				break;
			case '1':
				str2 += "\x4d\x31\x0d";
				break;
			case '2':
				str2 += "\x4d\x32\x0d";
				break;
			case '3':
				str2 += "\x4d\x33\x0d";
				break;
			case '4':
				str2 += "\x4d\x34\x0d";
				break;
			case '5':
				str2 += "\x4d\x35\x0d";
				break;
			case '6':
				str2 += "\x4d\x36\x0d";
				break;
			case '7':
				str2 += "\x4d\x37\x0d";
				break;
			case '8':
				str2 += "\x4d\x38\x0d";
				break;
			case '9':
				str2 += "\x4d\x39\x0d";
				break;
			case '.':
				str2 += "\x4d\x3a\x0d";
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
			app->g_com.Write(str2);
			str2 = "";
		}

		str2 += "\x4d\x3d\x0d";

		app->g_com.Write(str2);
		Sleep(100);
		str2 = "";

		str2 += "\x4d\x3f";

		str2 += "\x0d";

		app->g_com.Write(str2);
		str2 = "";
		str2 += "\x4d\x3d";

		str2 += "\x0d";

		app->g_com.Write(str2);
		str2 = "";
		for (i=0; i<m_m233.GetLength(); i++)
		{
			switch(m_m233.GetAt(i))
			{
			case '0':
				str2 += "\x4d\x30\x0d";
				break;
			case '1':
				str2 += "\x4d\x31\x0d";
				break;
			case '2':
				str2 += "\x4d\x32\x0d";
				break;
			case '3':
				str2 += "\x4d\x33\x0d";
				break;
			case '4':
				str2 += "\x4d\x34\x0d";
				break;
			case '5':
				str2 += "\x4d\x35\x0d";
				break;
			case '6':
				str2 += "\x4d\x36\x0d";
				break;
			case '7':
				str2 += "\x4d\x37\x0d";
				break;
			case '8':
				str2 += "\x4d\x38\x0d";
				break;
			case '9':
				str2 += "\x4d\x39\x0d";
				break;
			case '.':
				str2 += "\x4d\x3a\x0d";
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
			app->g_com.Write(str2);
			str2 = "";
		}

		str2 += "\x4d\x3a\x0d";

		app->g_com.Write(str2);
		Sleep(100);
		str2 = "";

		str2 += "\x4d\x3f";

		str2 += "\x0d";

		app->g_com.Write(str2);
		str2 = "";
		str2 += "\x4d\x3d";

		str2 += "x0d";

		app->g_com.Write(str2);
		str2 = "";
		for (i=0; i<m_m234.GetLength(); i++)
		{
			switch(m_m234.GetAt(i))
			{
			case '0':
				str2 += "\x4d\x30\x0d";
				break;
			case '1':
				str2 += "\x4d\x31\x0d";
				break;
			case '2':
				str2 += "\x4d\x32\x0d";
				break;
			case '3':
				str2 += "\x4d\x33\x0d";
				break;
			case '4':
				str2 += "\x4d\x34\x0d";
				break;
			case '5':
				str2 += "\x4d\x35\x0d";
				break;
			case '6':
				str2 += "\x4d\x36\x0d";
				break;
			case '7':
				str2 += "\x4d\x37\x0d";
				break;
			case '8':
				str2 += "\x4d\x38\x0d";
				break;
			case '9':
				str2 += "\x4d\x39\x0d";
				break;
			case '.':
				str2 += "\x4d\x3a\x0d";
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
			app->g_com.Write(str2);
			str2 = "";
		}

		str2 += "\x4d\x3a\x0d";

		app->g_com.Write(str2);
		Sleep(100);
		str2 = "";
		sql.Format("update Probe set wedge_degree=%s,wedge_sound_velocity=%s,wedge_distance=%s,wedge_time_delay=%s", m_m231, m_m232, m_m233, m_m234);
		try
		{
			m_pAppConn->Execute((_bstr_t)sql,NULL,adCmdText);
		}
		catch (_com_error e)
		{
			AfxMessageBox(e.ErrorMessage());
		}
	}
	int iPos2 = ((CComboBox *)GetDlgItem(IDC_COMBO_M24))->GetCurSel();
	int count = 0;
	CString biaohao[10];
	sql.Format("SELECT netword_IDN FROM Independent_settings WHERE table_type=0");
	try
	{
		m_recordset = m_pAppConn->Execute((_bstr_t)sql,NULL,adCmdText);
		while(!m_recordset->adoEOF)
		{
			_variant_t var = m_recordset->GetCollect("netword_IDN");
			CString str = (char *)_bstr_t(var);
			biaohao[count] = str;
			count++;
			m_recordset->MoveNext();
		}	
	}
	catch (_com_error e)
	{
		AfxMessageBox(e.ErrorMessage());
	}
	if (iPos2 != 0 && count != 0)
	{
		CString show;
		for (i=0; i<count; i++)
		{
			CString temp;
			temp.Format("%s号表不可以频率设置！\r\n", biaohao[i]);
			show += temp;	
		}
		//CString temp2;
		//temp2.Format("请设置为1MHz,然后单独设置！");
		//show += temp2;
		AfxMessageBox(show);
	}

	int count2 = 0;
	CString biaohao2[10];
	sql.Format("SELECT netword_IDN FROM Independent_settings WHERE table_type=1");
	try
	{
		m_recordset = m_pAppConn->Execute((_bstr_t)sql,NULL,adCmdText);
		while(!m_recordset->adoEOF)
		{
			_variant_t var = m_recordset->GetCollect("netword_IDN");
			CString str = (char *)_bstr_t(var);
			biaohao2[count2] = str;
			count2++;
			m_recordset->MoveNext();
		}	
	}
	catch (_com_error e)
	{
		AfxMessageBox(e.ErrorMessage());
	}

	int j,k;
	for (i=0; i<count2; i++)
	{
		str1 = "\x57";

		for (j=0; j<biaohao2[i].GetLength(); j++)
		{
			switch(biaohao2[i].GetAt(j))
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

		char menu2[6] = { '\x4d', '\x45', '\x4e', '\x55', '\x32', '\x34' };
		for (k=0; k<6; k++)
		{
			str2 += CString(menu2[k]);
		}
		
		str2 += "\x26\x4d\x3d"; 	
		//str2 += "\x26\x4d\(iPos2 + '0')";
		str2 += "\x26\x4d";
		CString temp;
		temp.Format("%d", iPos2);
		temp += '0';
		str2 += temp;
		str2 += "\x26\x4d\x3d";
		str2 += "\x26\x4d\x32";
		str2 += "\x26\x4d\x32";
		str2 += "\x26\x4d\x32";
		str2 += "\x26\x4d\x32";
		str2 += "\x26\x4d\x3d\x0d"; 

		str = str1 + str2;
		app->g_com.Write(str);
		Sleep(100);
		str = ""; 
		str2 = "";

		sql.Format("UPDATE Independent_settings SET transducer_frequency=%d WHERE netword_IDN=%s", iPos2, biaohao2[i]);
		try
		{
			m_pAppConn->Execute((_bstr_t)sql,NULL,adCmdText);
		}
		catch (_com_error e)
		{
			AfxMessageBox(e.ErrorMessage());
		}

		char menu3[6] = { '\x4d', '\x45', '\x4e', '\x55', '\x32', '\x35' };
		for (k=0; k<6; k++)
		{
			str2 += CString(menu3[k]);
		}
		int iPos3 = ((CComboBox *)GetDlgItem(IDC_COMBO_M25))->GetCurSel();
		
		str2 += "\x26\x4d\x3d";
		//str2 += "\x26\x4d\(iPos2 + '0')";
		str2 += "\x26\x4d";
		temp.Format("%d", iPos2);
		temp += '0';
		str2 += temp;
		str2 += "\x26\x4d\x3d\x0d";

		str = str1 + str2;
		app->g_com.Write(str);
		str = "";
		str2 = "";
		sql.Format("UPDATE Independent_settings SET transducer_mounting=%d WHERE netword_IDN=%s", iPos3, biaohao2[i]);
		try
		{
			m_pAppConn->Execute((_bstr_t)sql,NULL,adCmdText);
		}
		catch (_com_error e)
		{
			AfxMessageBox(e.ErrorMessage());
		}

		char menu4[6] = { '\x4d', '\x45', '\x4e', '\x55', '\x34', '\x35' };
		for (k=0; k<6; k++)
		{
			str2 += CString(menu4[k]);
		}
		UpdateData(TRUE);
		if (m_m45 != "")
		{
			float fm45;
			sscanf(m_m45, "%f", &fm45);
			if (fm45 > 1.5 || fm45 < 0.5)
			{
				if (app->language == 0)
				{
					AfxMessageBox("仪表系数必须在0.5~1.5之间!");
				}
				else
				{
					hHook=SetWindowsHookEx(WH_CBT,(HOOKPROC)CBTHookProc,AfxGetInstanceHandle(),NULL); 
					AfxMessageBox("Scale factor must be between 0.5 to 1.5! ");
				}
			}
			else
			{
				for (j=0; j<m_m45.GetLength(); j++)
				{
					switch(m_m45.GetAt(j))
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
							hHook=SetWindowsHookEx(WH_CBT,(HOOKPROC)CBTHookProc,AfxGetInstanceHandle(),NULL); 
							AfxMessageBox("Your input is incorrect!");
						}
					}
				}
				str2 +="\x26\x4d\x3d\x0d";

				str = str1 + str2;
				app->g_com.Write(str);
				str = "";
				str2 = "";
			}
			sql.Format("update Independent_settings set scale_factor = %s where netword_IDN = %s", m_m45, biaohao2[i]);
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
	
	for (i=0; i<count; i++)
	{
		str1 = "\x57";

		for (j=0; j<biaohao[i].GetLength(); j++)
		{
			switch(biaohao[i].GetAt(j))
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

		sql.Format("UPDATE Independent_settings SET transducer_frequency=0 WHERE netword_IDN=%s", biaohao[i]);
		try
		{
			m_pAppConn->Execute((_bstr_t)sql,NULL,adCmdText);
		}
		catch (_com_error e)
		{
			AfxMessageBox(e.ErrorMessage());
		}

		char menu3[6] = { '\x4d', '\x45', '\x4e', '\x55', '\x32', '\x34' };
		for (k=0; k<6; k++)
		{
			str2 += CString(menu3[k]);
		}
		int iPos3 = ((CComboBox *)GetDlgItem(IDC_COMBO_M25))->GetCurSel();
		
		str2 += "\x26\x4d\x3d";
		//str2 += "\x26\x4d\(iPos3 + '0')";
		str2 += "\x26\x4d";
		CString temp;
		temp.Format("%d", iPos3);
		temp += '0';
		str2 += temp;
		str2 += "\x26\x4d\x3d\x0d";

		str = str1 + str2;
		app->g_com.Write(str);
		Sleep(100);
		str = "";
		str2 = "";
		sql.Format("UPDATE Independent_settings SET transducer_mounting=%d WHERE netword_IDN=%s", iPos3, biaohao[i]);
		try
		{
			m_pAppConn->Execute((_bstr_t)sql,NULL,adCmdText);
		}
		catch (_com_error e)
		{
			AfxMessageBox(e.ErrorMessage());
		}

		char menu4[6] = { '\x4d', '\x45', '\x4e', '\x55', '\x34', '\x35' };
		for (k=0; k<6; k++)
		{
			str2 += CString(menu4[k]);
		}
		UpdateData(TRUE);
		if (m_m45 != "")
		{
			float fm45;
			sscanf(m_m45, "%f", &fm45);
			if (fm45 > 1.5 || fm45 < 0.5)
			{
				if (app->language == 0)
				{
					AfxMessageBox("仪表系数必须在0.5~1.5之间!");
				}
				else
				{
					hHook=SetWindowsHookEx(WH_CBT,(HOOKPROC)CBTHookProc,AfxGetInstanceHandle(),NULL); 
					AfxMessageBox("Scale factor must be between 0.5 to 1.5! ");
				}
			}
			else
			{
				for (j=0; j<m_m45.GetLength(); j++)
				{
					switch(m_m45.GetAt(j))
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
							hHook=SetWindowsHookEx(WH_CBT,(HOOKPROC)CBTHookProc,AfxGetInstanceHandle(),NULL); 
							AfxMessageBox("Your input is incorrect!");
						}
					}
				}
				str2 += "\x26\x4d\x3d\x0d";

				str = str1 + str2;
				app->g_com.Write(str);
				Sleep(100);
				str = "";
				str2 = "";
			}
			sql.Format("update Independent_settings set scale_factor = %s where netword_IDN = %s", m_m45, biaohao[i]);
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
	
	if (app->language == 0)
	{
		GetDlgItem(IDC_STATIC_AUTO2)->SetWindowText("设置成功");
	}
	else
	{
		GetDlgItem(IDC_STATIC_AUTO2)->SetWindowText("Set success");
	}	
	GetDlgItem(IDC_STATIC_AUTO2)->ShowWindow(SW_SHOW);
}

void CSetDlg::OnPaste() 
{
	// TODO: Add your control notification handler code here
	((CComboBox *)GetDlgItem(IDC_COMBO_M23))->SetCurSel(leixing);
	m_m231 = jiaodu;
	m_m232 = shengsu;
	m_m233 = juli;
	m_m234 = shijian;
	((CComboBox *)GetDlgItem(IDC_COMBO_M24))->SetCurSel(pinlv);
	((CComboBox *)GetDlgItem(IDC_COMBO_M25))->SetCurSel(fangfa);
	m_m45 = xishu;
	UpdateData(FALSE);
}


void CSetDlg::OnSelchangeComboM23() 
{
	// TODO: Add your control notification handler code here
	int iPos = ((CComboBox *)GetDlgItem(IDC_COMBO_M23))->GetCurSel();
	if (iPos == 3)
	{
		GetDlgItem(IDC_M23_1)->EnableWindow(TRUE);
		GetDlgItem(IDC_M23_2)->EnableWindow(TRUE);
		GetDlgItem(IDC_M23_3)->EnableWindow(TRUE);
		GetDlgItem(IDC_M23_4)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_M23_1)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_M23_1)->SetWindowText("");
		GetDlgItem(IDC_EDIT_M23_2)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_M23_2)->SetWindowText("");
		GetDlgItem(IDC_EDIT_M23_3)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_M23_3)->SetWindowText("");
		GetDlgItem(IDC_EDIT_M23_4)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_M23_4)->SetWindowText("");
		GetDlgItem(IDC_STATIC00)->EnableWindow(TRUE);
		GetDlgItem(IDC_STATIC01)->EnableWindow(TRUE);
		GetDlgItem(IDC_STATIC02)->EnableWindow(TRUE);
		GetDlgItem(IDC_STATIC03)->EnableWindow(TRUE);
	}
	else if (iPos == 24)
	{
		m_m231 = "38";
		m_m232 = "7447.51";
		m_m233 = "0.72441";
		m_m234 = "0.197";

		GetDlgItem(IDC_M23_1)->EnableWindow(FALSE);
		GetDlgItem(IDC_M23_2)->EnableWindow(FALSE);
		GetDlgItem(IDC_M23_3)->EnableWindow(FALSE);
		GetDlgItem(IDC_M23_4)->EnableWindow(FALSE);

		GetDlgItem(IDC_EDIT_M23_1)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_M23_1)->SetWindowText(m_m231);

		GetDlgItem(IDC_EDIT_M23_2)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_M23_2)->SetWindowTextA("7447.51");

		GetDlgItem(IDC_EDIT_M23_3)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_M23_3)->SetWindowText("0.72441");

		GetDlgItem(IDC_EDIT_M23_4)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_M23_4)->SetWindowText("0.197");

		GetDlgItem(IDC_STATIC00)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC01)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC02)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC03)->EnableWindow(FALSE);
	}
	else if (iPos == 25)
	{
		m_m231 = "37";
		m_m232 = "7447.51";
		m_m233 = "0.23622";
		m_m234 = "0.215";

		GetDlgItem(IDC_M23_1)->EnableWindow(FALSE);
		GetDlgItem(IDC_M23_2)->EnableWindow(FALSE);
		GetDlgItem(IDC_M23_3)->EnableWindow(FALSE);
		GetDlgItem(IDC_M23_4)->EnableWindow(FALSE);

		GetDlgItem(IDC_EDIT_M23_1)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_M23_1)->SetWindowText(m_m231);

		GetDlgItem(IDC_EDIT_M23_2)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_M23_2)->SetWindowTextA("7447.51");

		GetDlgItem(IDC_EDIT_M23_3)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_M23_3)->SetWindowText("0.23622");

		GetDlgItem(IDC_EDIT_M23_4)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_M23_4)->SetWindowText("0.215");

		GetDlgItem(IDC_STATIC00)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC01)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC02)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC03)->EnableWindow(FALSE);
	}
	else if (iPos == 26)
	{
		m_m231 = "37";
		m_m232 = "8061.024";
		m_m233 = "0.314961";
		m_m234 = "0.215";

		GetDlgItem(IDC_M23_1)->EnableWindow(FALSE);
		GetDlgItem(IDC_M23_2)->EnableWindow(FALSE);
		GetDlgItem(IDC_M23_3)->EnableWindow(FALSE);
		GetDlgItem(IDC_M23_4)->EnableWindow(FALSE);

		GetDlgItem(IDC_EDIT_M23_1)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_M23_1)->SetWindowText(m_m231);

		GetDlgItem(IDC_EDIT_M23_2)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_M23_2)->SetWindowTextA("8061.024");

		GetDlgItem(IDC_EDIT_M23_3)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_M23_3)->SetWindowText("0.314961");

		GetDlgItem(IDC_EDIT_M23_4)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_M23_4)->SetWindowText("0.215");

		GetDlgItem(IDC_STATIC00)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC01)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC02)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC03)->EnableWindow(FALSE);
	}
	else if (iPos == 27)
	{
		m_m231 = "37";
		m_m232 = "8061.024";
		m_m233 = "0.275591";
		m_m234 = "0.21";

		GetDlgItem(IDC_M23_1)->EnableWindow(FALSE);
		GetDlgItem(IDC_M23_2)->EnableWindow(FALSE);
		GetDlgItem(IDC_M23_3)->EnableWindow(FALSE);
		GetDlgItem(IDC_M23_4)->EnableWindow(FALSE);

		GetDlgItem(IDC_EDIT_M23_1)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_M23_1)->SetWindowText(m_m231);

		GetDlgItem(IDC_EDIT_M23_2)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_M23_2)->SetWindowTextA("8061.024");

		GetDlgItem(IDC_EDIT_M23_3)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_M23_3)->SetWindowText("0.275591");

		GetDlgItem(IDC_EDIT_M23_4)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_M23_4)->SetWindowText("0.21");


		GetDlgItem(IDC_STATIC00)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC01)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC02)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC03)->EnableWindow(FALSE);
	}
	else if (iPos == 28)
	{
		m_m231 = "37";
		m_m232 = "8061.024";
		m_m233 = "0.551181";
		m_m234 = "0.21";

		GetDlgItem(IDC_M23_1)->EnableWindow(FALSE);
		GetDlgItem(IDC_M23_2)->EnableWindow(FALSE);
		GetDlgItem(IDC_M23_3)->EnableWindow(FALSE);
		GetDlgItem(IDC_M23_4)->EnableWindow(FALSE);

		GetDlgItem(IDC_EDIT_M23_1)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_M23_1)->SetWindowText(m_m231);

		GetDlgItem(IDC_EDIT_M23_2)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_M23_2)->SetWindowTextA("8061.024");

		GetDlgItem(IDC_EDIT_M23_3)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_M23_3)->SetWindowText("0.551181");

		GetDlgItem(IDC_EDIT_M23_4)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_M23_4)->SetWindowText("0.21");

		GetDlgItem(IDC_STATIC00)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC01)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC02)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC03)->EnableWindow(FALSE);
	}
	else if (iPos == 29)
	{
		m_m231 = "37";
		m_m232 = "8061.024";
		m_m233 = "0.314961";
		m_m234 = "0.214";

		GetDlgItem(IDC_M23_1)->EnableWindow(FALSE);
		GetDlgItem(IDC_M23_2)->EnableWindow(FALSE);
		GetDlgItem(IDC_M23_3)->EnableWindow(FALSE);
		GetDlgItem(IDC_M23_4)->EnableWindow(FALSE);

		GetDlgItem(IDC_EDIT_M23_1)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_M23_1)->SetWindowText(m_m231);

		GetDlgItem(IDC_EDIT_M23_2)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_M23_2)->SetWindowTextA("8061.024");

		GetDlgItem(IDC_EDIT_M23_3)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_M23_3)->SetWindowText("0.314961");

		GetDlgItem(IDC_EDIT_M23_4)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_M23_4)->SetWindowText("0.214");

		GetDlgItem(IDC_STATIC00)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC01)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC02)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC03)->EnableWindow(FALSE);
	}
	else if (iPos == 30)
	{
		m_m231 = "38";
		m_m232 = "7765.75";
		m_m233 = "0.866142";
		m_m234 = "0.18";

		GetDlgItem(IDC_M23_1)->EnableWindow(FALSE);
		GetDlgItem(IDC_M23_2)->EnableWindow(FALSE);
		GetDlgItem(IDC_M23_3)->EnableWindow(FALSE);
		GetDlgItem(IDC_M23_4)->EnableWindow(FALSE);


		GetDlgItem(IDC_EDIT_M23_1)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_M23_1)->SetWindowText(m_m231);

		GetDlgItem(IDC_EDIT_M23_2)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_M23_2)->SetWindowTextA("7765.75");

		GetDlgItem(IDC_EDIT_M23_3)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_M23_3)->SetWindowText("0.866142");

		GetDlgItem(IDC_EDIT_M23_4)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_M23_4)->SetWindowText("0.18");

		GetDlgItem(IDC_STATIC00)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC01)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC02)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC03)->EnableWindow(FALSE);
	}
	else if (iPos == 31)
	{
		m_m231 = "38";
		m_m232 = "7447.51";
		m_m233 = "0.842520";
		m_m234 = "0.164";

		GetDlgItem(IDC_M23_1)->EnableWindow(FALSE);
		GetDlgItem(IDC_M23_2)->EnableWindow(FALSE);
		GetDlgItem(IDC_M23_3)->EnableWindow(FALSE);
		GetDlgItem(IDC_M23_4)->EnableWindow(FALSE);

		GetDlgItem(IDC_EDIT_M23_1)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_M23_1)->SetWindowText(m_m231);

		GetDlgItem(IDC_EDIT_M23_2)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_M23_2)->SetWindowTextA("7447.51");

		GetDlgItem(IDC_EDIT_M23_3)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_M23_3)->SetWindowText("0.842520");

		GetDlgItem(IDC_EDIT_M23_4)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_M23_4)->SetWindowText("0.164");

		GetDlgItem(IDC_STATIC00)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC01)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC02)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC03)->EnableWindow(FALSE);
	}
	else if (iPos == 32)
	{
		m_m231 = "38";
		m_m232 = "7447.51";
		m_m233 = "1.348819";
		m_m234 = "0.276";

		GetDlgItem(IDC_M23_1)->EnableWindow(FALSE);
		GetDlgItem(IDC_M23_2)->EnableWindow(FALSE);
		GetDlgItem(IDC_M23_3)->EnableWindow(FALSE);
		GetDlgItem(IDC_M23_4)->EnableWindow(FALSE);

		GetDlgItem(IDC_EDIT_M23_1)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_M23_1)->SetWindowText(m_m231);

		GetDlgItem(IDC_EDIT_M23_2)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_M23_2)->SetWindowTextA("7447.51");

		GetDlgItem(IDC_EDIT_M23_3)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_M23_3)->SetWindowText("1.348819");

		GetDlgItem(IDC_EDIT_M23_4)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_M23_4)->SetWindowText("0.276");

		GetDlgItem(IDC_STATIC00)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC01)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC02)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC03)->EnableWindow(FALSE); 
	}
	else if (iPos == 33)
	{
		m_m231 = "38";
		m_m232 = "7447.51";
		m_m233 = "2.077165";
		m_m234 = "0.197";

		GetDlgItem(IDC_M23_1)->EnableWindow(FALSE);
		GetDlgItem(IDC_M23_2)->EnableWindow(FALSE);
		GetDlgItem(IDC_M23_3)->EnableWindow(FALSE);
		GetDlgItem(IDC_M23_4)->EnableWindow(FALSE);

		GetDlgItem(IDC_EDIT_M23_1)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_M23_1)->SetWindowText(m_m231);

		GetDlgItem(IDC_EDIT_M23_2)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_M23_2)->SetWindowTextA("7447.51");

		GetDlgItem(IDC_EDIT_M23_3)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_M23_3)->SetWindowText("2.077165");

		GetDlgItem(IDC_EDIT_M23_4)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_M23_4)->SetWindowText("0.197");

		GetDlgItem(IDC_STATIC00)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC01)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC02)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC03)->EnableWindow(FALSE);
	}
	else if (iPos == 34)
	{
		m_m231 = "38";
		m_m232 = "7765.75";
		m_m233 = "0.866142";
		m_m234 = "0.101";

		GetDlgItem(IDC_M23_1)->EnableWindow(FALSE);
		GetDlgItem(IDC_M23_2)->EnableWindow(FALSE);
		GetDlgItem(IDC_M23_3)->EnableWindow(FALSE);
		GetDlgItem(IDC_M23_4)->EnableWindow(FALSE);


		GetDlgItem(IDC_EDIT_M23_1)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_M23_1)->SetWindowText(m_m231);

		GetDlgItem(IDC_EDIT_M23_2)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_M23_2)->SetWindowTextA("7765.75");

		GetDlgItem(IDC_EDIT_M23_3)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_M23_3)->SetWindowText("0.866142");

		GetDlgItem(IDC_EDIT_M23_4)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_M23_4)->SetWindowText("0.101");

		GetDlgItem(IDC_STATIC00)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC01)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC02)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC03)->EnableWindow(FALSE);
	}
	else
	{
		m_m231 = "";
		m_m232 = "";
		m_m233 = "";
		m_m234 = "";
		GetDlgItem(IDC_M23_1)->EnableWindow(FALSE);
		GetDlgItem(IDC_M23_2)->EnableWindow(FALSE);
		GetDlgItem(IDC_M23_3)->EnableWindow(FALSE);
		GetDlgItem(IDC_M23_4)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_M23_1)->SetWindowText("");
		GetDlgItem(IDC_EDIT_M23_1)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_M23_2)->SetWindowText("");
		GetDlgItem(IDC_EDIT_M23_2)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_M23_3)->SetWindowText("");
		GetDlgItem(IDC_EDIT_M23_3)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_M23_4)->SetWindowText("");
		GetDlgItem(IDC_EDIT_M23_4)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC00)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC01)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC02)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC03)->EnableWindow(FALSE);
	}

}

void CSetDlg::OnSelchangeComboM24() 
{
	// TODO: Add your control notification handler code here
	/*
	int iPos = ((CComboBox *)GetDlgItem(IDC_COMBO_M24))->GetCurSel();
	int count = 0;
	CString biaohao[10];
	CString sql;
	int i;
	sql.Format("SELECT netword_IDN FROM Independent_settings WHERE table_type=0");
	try
	{
		m_recordset = m_pAppConn->Execute((_bstr_t)sql,NULL,adCmdText);
		while(!m_recordset->adoEOF)
		{
			_variant_t var = m_recordset->GetCollect("netword_IDN");
			CString str = (char *)_bstr_t(var);
			biaohao[count] = str;
			count++;
			m_recordset->MoveNext();
		}	
	}
	catch (_com_error e)
	{
		AfxMessageBox(e.ErrorMessage());
	}
	if (iPos != 0 && count != 0)
	{
		CString show;
		for (i=0; i<count; i++)
		{
			CString temp;
			temp.Format("%s号表不可以频率设置！\r\n", biaohao[i]);
			show += temp;	
		}
		CString temp2;
		temp2.Format("请设置为1MHz,然后单独设置！");
		show += temp2;
		AfxMessageBox(show);
	}
	*/
}

void CSetDlg::OnChangeEditM231() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
}

void CSetDlg::OnChangeEditM232() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
}

void CSetDlg::OnChangeEditM233() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
}

void CSetDlg::OnChangeEditM234() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
}

void CSetDlg::OnRadio1() 
{
	// TODO: Add your control notification handler code here
	GetDlgItem(IDC_STATIC1)->SetWindowText("mm");
	GetDlgItem(IDC_STATIC2)->SetWindowText("mm");
	GetDlgItem(IDC_STATIC3)->SetWindowText("mm");
	GetDlgItem(IDC_STATIC4)->SetWindowText("mm");
	GetDlgItem(IDC_STATIC00)->SetWindowText("m/s");
	GetDlgItem(IDC_STATIC01)->SetWindowText("mm");
}

void CSetDlg::OnRadio2() 
{
	// TODO: Add your control notification handler code here
	GetDlgItem(IDC_STATIC1)->SetWindowText("in");
	GetDlgItem(IDC_STATIC2)->SetWindowText("in");
	GetDlgItem(IDC_STATIC3)->SetWindowText("in");
	GetDlgItem(IDC_STATIC4)->SetWindowText("in");
	GetDlgItem(IDC_STATIC00)->SetWindowText("f/s");
	GetDlgItem(IDC_STATIC01)->SetWindowText("in");
}


void CSetDlg::OnSelchangeComboM16() 
{
	// TODO: Add your control notification handler code here
	int iPos = ((CComboBox *)GetDlgItem(IDC_COMBO_M16))->GetCurSel();
	if (iPos == 0)
	{
		GetDlgItem(IDC_M18)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_M18)->EnableWindow(FALSE);
		m_m18 = "0";
		UpdateData(FALSE);
	}
	else
	{
		GetDlgItem(IDC_M18)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_M18)->EnableWindow(TRUE);
	}
}

void CSetDlg::OnRadio9() 
{
	// TODO: Add your control notification handler code here
	GetDlgItem(IDC_STATIC5)->EnableWindow(FALSE);
	GetDlgItem(IDC_OK)->EnableWindow(FALSE);
	GetDlgItem(IDC_COMBO_M37)->EnableWindow(FALSE);
}

void CSetDlg::OnRadio10() 
{
	// TODO: Add your control notification handler code here
	GetDlgItem(IDC_STATIC5)->EnableWindow(TRUE);
	GetDlgItem(IDC_OK)->EnableWindow(TRUE);
	GetDlgItem(IDC_COMBO_M37)->EnableWindow(TRUE);
}
