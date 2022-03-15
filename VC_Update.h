/*Class Added by YC on Nov 23, 2016
Includes static functions to modify Voltage from NI_DAQ*/

#ifndef VC_UPDATE_H_
#define VC_UPDATE_H_


#if _MSC_VER > 1000
#pragma once
#endif

#include"StdAfx.h"
#include"Calibration.h"

#include <NIDAQmx.h>

#define DAQmxErrChk(functionCall) if( DAQmxFailed(error=(functionCall)) ) goto Error; else

class VC_Update {
public:
	VC_Update();
	static int DAQ_Update(float voltage);
};

#endif