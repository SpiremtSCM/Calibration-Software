/*
Added by YC
*/

#include "stdafx.h"
#include "Calibration.h"
#include"Meter_Operation.h"

Meter_err::Meter_err(){
	err_no = 0;
	err_msg = "Unknown meter reading error";
}

Meter_Op::Meter_Op() {
	IDN = 0x00;
}

void Meter_Op::Read_S_Q(int IDN, float S_Q[]) {
	Meter_err err;
	CCalibrationApp *app = (CCalibrationApp *)AfxGetApp();

	CString str(""), strW("\x57"), strIDN(""), strEF("");
	strIDN.Format(_T("%d"), IDN);
	strEF += "\x44\x4c\x0d";//LC\r
	str = strW + strIDN + strEF;//W(IDN)LC\r

	char *p_UP(NULL), *p_DN(NULL), *p_Q(NULL);
	char buf[60] = { 0 };
	int jc(0), recvno(0);
	bool read_success(false);
	do {
		app->g_com.Write(str);
		
		recvno = app->g_com.Read(buf, 60);
		Sleep(100);
		if (recvno != 0) {
			p_UP = strstr(buf, "UP");
			p_DN = strstr(buf, "DN");
			p_Q = strstr(buf, "Q");
			if (p_UP != NULL &&  p_DN != NULL && p_Q != NULL) {
				read_success = true;
				break;
			}//recevied correct info
			else recvno = 0;//received wrong info, need to re-read
		}
		jc++;
	} while (jc < 5);//try 5 times
	str = "";

	if (!read_success) {
		if (app->language == 0)
		{
			AfxMessageBox("请保持备测表的连接!");
		}
		else
		{
			//hHook = SetWindowsHookEx(WH_CBT, (HOOKPROC)CBTHookProc, AfxGetInstanceHandle(), NULL);
			AfxMessageBox("Please keep the meter connection!");
		}
		err.err_no = 1;
		err.err_msg = "Fail in reading S, Q of meter";
		throw err;
	}//throw err code 1, meter not read
	else {
		CString UP(""), DN(""), Q("");
		UP.Format("%c%c%c%c", *(p_UP + 3), *(p_UP + 4), *(p_UP + 5), *(p_UP + 6));//format UP to CString
		sscanf(UP, "%f", &S_Q[0]);//convert to floats and store to S_Q
		
		DN.Format("%c%c%c%c", *(p_DN + 3), *(p_DN + 4), *(p_DN + 5), *(p_DN + 6));
		sscanf(DN, "%f", &S_Q[1]);
		
		Q.Format("%c%c", *(p_Q + 2), *(p_Q + 3));
		sscanf(Q, "%f", &S_Q[2]);
	}
}

void Meter_Op::Read_FlowByMin(int IDN, float &F) {
	Meter_err err;
	CCalibrationApp *app = (CCalibrationApp *)AfxGetApp();

	CString str(""), strW("\x57"), strIDN(""), strEF("");
	strIDN.Format(_T("%d"), IDN);
	strEF += "\x44\x51\x4d\x0d";//DQM\r
	str = strW + strIDN + strEF;//W(IDN)DQM\r

	char *p_F(NULL);
	char buf[60] = { 0 };
	int jc(0), recvno(0);
	bool read_success(false);
	do {
		app->g_com.Write(str);
		//str = "";
		recvno = app->g_com.Read(buf, 60);
		Sleep(100);
		if (recvno != 0) {
			p_F = strstr(buf, "E");//E is the exponent sign
			if (p_F != NULL) {
				read_success = true;
				break;
			}//recevied correct info
			else recvno = 0;//received wrong info, need to re-read
		}
		
		jc++;
	} while (jc < 5);//try 5 times max
	str = "";

	if (!read_success) {
		err.err_no = 1;
		err.err_msg = "Fail in reading flowrate of testing meter";
		throw err;
	}//throw err code 1, meter not read
	else {
		F = Meter_Op::Convert_Sci_Note_String(buf);//return the result
	}
}

void Meter_Op::Read_FluidVelocity(int IDN, float &V) {
	Meter_err err;
	CCalibrationApp *app = (CCalibrationApp *)AfxGetApp();

	CString str(""), strW("\x57"), strIDN(""), strEF("");
	strIDN.Format(_T("%d"), IDN);
	strEF += "\x44\x56\x0d";//DV\r
	str = strW + strIDN + strEF;//W(IDN)DV\r

	char *p_F(NULL);
	char buf[60] = { 0 };
	int jc(0), recvno(0);
	bool read_success(false);
	do {
		app->g_com.Write(str);
		
		recvno = app->g_com.Read(buf, 60);
		Sleep(100);
		if (recvno != 0) {
			p_F = strstr(buf, "E");//E is the exponent sign
			if (p_F != NULL) {
				read_success = true;
				break;
			}//recevied correct info
			else recvno = 0;//received wrong info, need to re-read
		}
		jc++;
	} while (jc < 5);//try 5 times max
	str = "";

	if (!read_success) {
		err.err_no = 1;
		err.err_msg = "Fail in reading fluid velocity of meter";
		throw err;
	}//throw err code 1, meter not read
	else {
		V = Meter_Op::Convert_Sci_Note_String(buf);//return the result
	}
}

void Meter_Op::Read_PosTotalizer(int IDN, float &TP) {
	CCalibrationApp *app = (CCalibrationApp *)AfxGetApp();
	CString strEF, str_F[1];
	char str_Result[60] = { 0 };//result string, should be in +/-dddddddE+/-d/cr format
	char *p_E[1] = { 0 };//the pointer of 'E' character

	strEF = "\x44\x49\x2b\x0d";//DI+\r
	str_F[0] = "E";//feature string;
	Meter_Op::Read_EFCP_Request(IDN,strEF,str_F,p_E,1,str_Result);
	TP = Meter_Op::Convert_Sci_Note_String(str_Result, 8, 2);//return the read value
}

void Meter_Op::M38_Turn_On(int IDN) {
	CCalibrationApp *app = (CCalibrationApp *)AfxGetApp();
	Meter_err err;

	CString str(""), strW("\x57"), strIDN(""), strMENU[1], strEF(""), str_F[2], strENT(""), strTemp[1];
	char *p_F[2];
	char result[60], temp[60];
	strIDN.Format(_T("%d"), IDN);
	strMENU[0] = "\x4d\x45\x4e\x55\x33\x38";//MENU38
	strEF += "\x4c\x43\x44";//LCD
	str_F[0] = "ENT";//Previously the stopwatch totalizer is off
	str_F[1] = "ON";//Previously the stopwatch totalizer is on
	strTemp[0] = "\x4d\x45\x4e\x55\x30\x31";

	Meter_Op::Read_EFCP_Request(IDN, strEF, str_F, p_F, 2, result, 0, 1, strMENU, 1);
	if (p_F[1] != NULL) {
		err.err_no = 3;
		err.err_msg = "The stopwatch totalizer has been on!";
		throw err;
	}
	else if (p_F[0] != NULL) {
		bool Stopwatch_ON(false);
		int jc(0);

		//strENT += strW + strIDN + strMENU[0] + "\x0d\x4d\x3d\x0d";//W(IDN)MENU38\rM ENT \r
		//app->g_com.Write(strENT);//deliver ENT key
		do{
			strENT += strW + strIDN + "\x4d\x3d\x0d";//W(IDN)M ENT \r
			app->g_com.Write(strENT);//deliver ENT key
			Meter_Op::Read_EFCP_Request(IDN, strEF, str_F, p_F, 2, result, 0, 1, strMENU, 1);//read the LCD only
			if (p_F[1] != NULL) {
				Stopwatch_ON = true;//succesfully initialized the stopwatch totalizer
			}
			jc++;
		} while (jc < 5 && (!Stopwatch_ON));
		if (Stopwatch_ON == false) {
			err.err_no = 4;
			err.err_msg = "Cannot turn on the stopwatch totalizer (Menu38)";
			throw err;
		}
	}
	else {
		err.err_no = 5;
		err.err_msg = "Cannot read from EFCP";
		throw err;
	}
}


void Meter_Op::M38_Turn_Off(int IDN, float &time_elapsed, float &flow_passed) {
	CCalibrationApp *app = (CCalibrationApp *)AfxGetApp();
	Meter_err err;

	CString str(""), strW("\x57"), strIDN(""), strMENU[1], strEF(""), str_F[3], strENT("");
	char *p_F[3] = { 0 };

	char result[60];
	strIDN.Format(_T("%d"), IDN);
	strMENU[0] = "\x4d\x45\x4e\x55\x33\x38";//MENU38
	strEF += "\x4c\x43\x44";//LCD
	str_F[0] = "ENT";//Previously the stopwatch totalizer is off
	str_F[1] = "ON";//Previously the stopwatch totalizer is on
	str_F[2] = "OFF";

	//strENT += strW + strIDN + strMENU[0] + "\x0d\x4d\x3d\x0d";//W(IDN)MENU38\rM ENT \r
	//app->g_com.Write(strENT);//deliver ENT key, stop the stopwatch, no error sent for failing to send this order
	//Sleep(100);

	Meter_Op::Read_EFCP_Request(IDN, strEF, str_F, p_F, 3, result);
	if (p_F[0] != NULL || p_F[2] != NULL) {
		err.err_no = 5;
		err.err_msg = "The stopwatch totalizer has NOT been on!";
		throw err;
	}
	else if (p_F[1] != NULL) {
		bool Stopwatch_ON(true);
		int jc(0);

		strENT += strW + strIDN + "\x4d\x3d\x0d";//W(IDN)M ENT \r
		app->g_com.Write(strENT);//deliver ENT key, stop the stopwatch, no error sent for failing to send this order
		Sleep(100);
		do{
			Meter_Op::Read_EFCP_Request(IDN, strEF, str_F, p_F, 3, result);//read the LCD only
			if (p_F[2] != NULL) {
				Stopwatch_ON = false;//succesfully initialized the stopwatch totalizer
			}
			jc++;
		} while (jc < 5 && Stopwatch_ON);
		if (Stopwatch_ON == true) {
			err.err_no = 6;
			err.err_msg = strIDN + ": cannot turn off the manual totalizer (Menu38)";
			throw err;
		}
		char *p_cflow, *p_ctime, cflow[8], ctime[6];
		p_cflow = strstr(result, "OFF");
		p_ctime = strstr(result, "Sec");
		for (int i(0); i < 8; i++) {
			cflow[i] = *(p_cflow + 3 + i);
		}
		for (int i(0); i < 6; i++) {
			ctime[i] = *(p_ctime - 6 + i);
		}
		sscanf(cflow, "%f", &flow_passed);
		sscanf(ctime, "%f", &time_elapsed);
	}
	else {
		err.err_no = 5;
		err.err_msg = "Cannot read from EFCP";
		throw err;
	}
}

void Meter_Op::Read_Ref_flowrate(float &rf) {
	CCalibrationApp *app = (CCalibrationApp *)AfxGetApp();
	Meter_err err;
	int jc(0), recvno(0);
	CString str("");

	//char cmd[8] = { '\x7f', '\x03', '\x02', '\x52', '\x00', '\x02', '\x6e', '\x7c' };//YC Note: read register of flow rate from ref meter
	char cmd[8] = { '\x63', '\x04', '\x10', '\x10', '\x00', '\x02', '\x7c', '\x8c' };//YC Note: read register of flow rate from ref meter
	for (int i(0); i < 8; i++)
	{
		str += cmd[i];
	}

	char s[10] = { 0 };

	while (jc < 5) {
		recvno = 0;//clear tokens
		app->g_com.Write(str, 8);
		recvno = app->g_com.Read(s, 10);
		Sleep(100);

		if (recvno == 0) {
			jc++;
			continue;//not receive any string, jump to next while(jc<5) loop
		}
		break;
	}
	if (jc == 5) {
		err.err_no = 10;
		err.err_msg = "Cannot read flowrate from the reference meter";
		throw err;
	}
	else {
		int f = ((unsigned char)s[3]) * 0x1000000 + ((unsigned char)s[4]) * 0x10000 + ((unsigned char)s[5]) * 0x100 + (unsigned char)s[6];
		char strstrstr[10] = { 0 };
		sprintf(strstrstr, "%x", f);
		sscanf_s(strstrstr, "%x", &rf);
	}
}

void Meter_Op::Read_EFCP_Request(int IDN, CString strEF, CString strFeature[], char *p[], size_t str_F_N, char str_Got[], int mode, int match_no, CString strMENU[], size_t strMENU_N){
	CCalibrationApp *app = (CCalibrationApp *)AfxGetApp();
	int jc(0), recvno(0);
	bool not_matched(false);

	CString str(""), strW("\x57"), strIDN("");
	strIDN.Format(_T("%d"), IDN);

	char buf[60] = { 0 };
	
	while(jc<5) {
		not_matched = false;
		recvno = 0;//clear tokens

		for (int i(0); i < strMENU_N; i++) {
			str = strW + strIDN + strMENU[i] + "\x0d"; //W(IDN)MENUXX\r
			app->g_com.Write(str);//request MENUXX screen on (IDN) meter;
			Sleep(100);
			str = "";
		}

		str = strW + strIDN + strEF + "\x0d";
		app->g_com.Write(str);//request EF code of (IDN) meter; e.g. W(IDN)LCD\r
		Sleep(100);
		str = "";

		recvno = app->g_com.Read(buf, 60);
		Sleep(100);

		if (recvno == 0) {
			jc++;
			continue;//not receive any string, jump to next while(jc<5) loop
		}

		for (int i(0); i < str_F_N; i++) {
			p[i] = strstr(buf, strFeature[i]);//check if the derived string matches the feature string
		}

		switch (mode) {//matching feature strings
		case 1: {//first several match
			int i(0);
			not_matched = false;
			while (i < match_no && (!not_matched)) {
				if (p[i] == NULL) {
					not_matched = true;
				}
				i++;
			}
			if (not_matched) {
				jc++;
				continue;//not all keywords are matched, continue to the next while to re-read
			}
			break;//break the case 1 switch
		}
		default: {//Any of the feature string matched, default mode=0;
			int i(0);
			bool not_matched(true);
			if (str_F_N == 0) not_matched = false;//Only a command is sent, respond is not expected;
			else{
				while (i < str_F_N && not_matched) {
					if (p[i] != NULL)not_matched = false;
					i++;
				}
			}
			if (not_matched) {
				jc++;
				continue;
			}
		}
		}//switch ends

		int j(0);
		while (buf[j]) {
			str_Got[j] = buf[j];
			j++;
		}
		break;//break the while(jc<5) loop
		
		jc++;//may not be executed at all;
	} //while loop, try 5 times

	//throw the exceptions
	if (recvno == 0) {
		Meter_err err;
		err.err_no = 1;
		err.err_msg = "Cannot read from order " + strEF;
		throw err;
	}
	else if (not_matched) {
		Meter_err err;
		err.err_no = 2;
		err.err_msg = "Read wrong information from order " + strEF;
		throw err;
	}
}

float Meter_Op::Convert_Sci_Note_String(char str[], int coefficient, int exp) {
	char c[16], e[8];
	float coef, result;
	int expo;
	for (int i(0); i < coefficient; i++) {
		c[i] = str[i];
	}
	for (int i(0); i < exp; i++) {
		e[i] = str[i + coefficient + 1];
	}
	sscanf_s(c, "%f", &coef);
	sscanf_s(e, "%d", &expo);

	result = coef*pow(10, expo);
	return result;
}


