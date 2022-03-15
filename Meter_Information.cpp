
#include "stdafx.h"
#include "Calibration.h"
#include"Meter_Information.h"

Meter_Info::Meter_Info() {
	s_n = "S\\N";
	IDN = 0;
	Scale_Factor = 1;
	Installed = false;//for testing purpose
	Calibrated = false;
}