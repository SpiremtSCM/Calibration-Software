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
	CString unflux;          //������λ, unit of flow rate;
	CString unspeed;         //���ٵ�λ, unit of flow speed;
	CString S;
	CString Q;
	CString R;
}nowflux;

class CCalibrationApp : public CWinApp
{
public:
	CCalibrationApp();
	CString biaohao;         //���
	CString xs;              //ϵ��
	CString yxs;             //ԭϵ��
	CString flux;            //����
	CRect g_rc;              //
	nowflux liuliang[20];    //˲ʱ����
	int no;                  //Number of meters that could be calibrated
	CnComm g_com;            //����
	CEvent g_event;          //״̬
	int p;                   //
	int commm;               //commm�Ŵ���
	int language;            //����
	int unit_volume;		//unit of volume of meter current meter
	int unit_time;			//time of the meters;
	int biaoleixing;          //�����ͣ�0    1M�� 1   2M��
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
