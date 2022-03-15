/*Class Added by YC
Includes static functions to read testing meters and reference meters*/

#ifndef METER_OPERATION_H_
#define METER_OPERATION_H_


#if _MSC_VER > 1000
#pragma once
#endif

struct Meter_err {
	int err_no;
	CString err_msg;

	Meter_err();
};

class Meter_Op {
public:
	int IDN;
	Meter_Op();
	static void Read_S_Q(int IDN, float S_Q[]);//Read S & Q value, S_Q[0]: S_UP, S_Q[1]: S_DN, S_Q[2]: Q 
	static void Read_FlowByMin(int IDN, float &F);//Read flow rate and sound velocity, F Flow rate to be read
	static void Read_FluidVelocity(int IDN, float &V);//Read fluid velocity
	static void Read_PosTotalizer(int IDN, float &TP);//Read positive totalizer
	
	static void Read_Ref_flowrate(float &rf);//Read flowrate of the reference meter;
	
	static void M38_Turn_On(int IDN);//Turn on MENU 38, start totalizer by seconds;
	static void M38_Turn_Off(int IDN, float &time_elapsed, float &flow_passed);//Stop the stopwatch and read M38 totalizer;

	static float Convert_Sci_Note_String(char str[], int coefficient = 9, int exp = 3);//Read Scientific notation string, default +d.ddddddE+dd(cr), coefficient includes dot and sign, exponent includes sign, return a float value
	static void Read_EFCP_Request(int IDN, CString strEF, CString strFeature[], char *p[], size_t str_F_N, char str_Got[], int mode = 0, int match_no = 1, CString strMENU[] = NULL, size_t strMENU_N = 0);
};


#endif // !METER_OPERATION