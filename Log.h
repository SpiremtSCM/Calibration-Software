#pragma once
#include <fstream>

using namespace std;

class Log {
public:
	Log(char* filename);
	~Log();
	void Write(char* logline);
	//void Close();

	CString static getCurrentDateTime(CString s);
	void static Logger(CString logMsg);

private:
	ofstream m_stream;
};
