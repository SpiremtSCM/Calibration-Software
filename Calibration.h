// Calibration.h : main header file for the CALIBRATION application
//

#if !defined(AFX_CALIBRATION_H__AAE3103C_76FA_489D_AA50_797C06CE0516__INCLUDED_)
#define AFX_CALIBRATION_H__AAE3103C_76FA_489D_AA50_797C06CE0516__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols
#include "CnComm.h"
#include "Afxmt.h"
#include"Meter_Information.h"

#include <fstream> 

/////////////////////////////////////////////////////////////////////////////
// CCalibrationApp:
// See Calibration.cpp for the implementation of this class
//

typedef struct NOWFLUX 
{
	CString mmeter;
	float mflux;
	float mspeed;
	float S_UPf;
	float S_DNf;
	float Qf;
	float Rf;
	float posTotalf;
	CString unflux;          //流量单位, unit of flow rate;
	CString unspeed;         //流速单位, unit of flow speed;
	CString S;
	CString Q;
	CString R;
}nowflux;

class CCalibrationApp : public CWinApp
{
public:
	CCalibrationApp();
	CString biaohao;         //表号
	CString xs;              //系数
	CString yxs;             //原系数
	CString flux;            //流量
	CRect g_rc;              //
	nowflux liuliang[20];    //瞬时流量
	int no;                  //Number of meters that could be calibrated
	CnComm g_com;            //串口
	CEvent g_event;          //状态
	int p;                   //
	int commm;               //commm号串口
	int language;            //语言
	int unit_volume;		//unit of volume of meter current meter
	int unit_time;			//time of the meters;
	int biaoleixing;          //表类型：0    1M表； 1   2M表
	Meter_Info Meters[20];	 //The meters that are currently connected
	int Global_Sampling_Total; //For each sampling, how many times it polls the reference meter at 1s gap
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCalibrationApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CCalibrationApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CALIBRATION_H__AAE3103C_76FA_489D_AA50_797C06CE0516__INCLUDED_)
