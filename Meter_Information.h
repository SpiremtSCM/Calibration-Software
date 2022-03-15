/*Class Added by YC
Includes basic information of meters. Therefore, no nessary to access the database everystep*/

#ifndef METER_INFORMATION_H_
#define METER_INFORMATION_H_

#if _MSC_VER > 1000
#pragma once
#endif


class Meter_Info {
public:
	CString s_n;
	int IDN;
	float Scale_Factor;
	bool Installed;
	bool Calibrated;
	Meter_Info();//constructor
};

#endif // !METER_INFORMATION_H_