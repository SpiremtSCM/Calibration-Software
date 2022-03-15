#include "stdafx.h"

#include "log.h"

Log::Log(char* filename) {
	m_stream.open(filename);
}

void Log::Write(char* logline) {
	m_stream << logline << endl;
}

Log::~Log() {
	m_stream.close();
}

CString Log::getCurrentDateTime(CString s) {
	time_t now = time(0);
	struct tm  tstruct;
	char  buf[80];
	tstruct = *localtime(&now);
	if (s == "now")
		strftime(buf, sizeof(buf), "%Y-%m-%d %X", &tstruct);
	else if (s == "date")
		strftime(buf, sizeof(buf), "%Y-%m-%d", &tstruct);
	return CString(buf);
};


void Log::Logger(CString logMsg) {

	std::string filePath = "c:/LogDir/log_" + getCurrentDateTime("date") + ".txt";
	CString f1(filePath.c_str());

	CString str;
	CFile file;
	CFileException e;
	BOOL bFileExists = (GetFileAttributes(f1) != INVALID_FILE_ATTRIBUTES);
	if (bFileExists)
	{
		file.Open(f1, CFile::modeWrite, &e);
		try
		{
			file.SeekToEnd();
		}
		catch (CFileException* e)
		{
			AfxMessageBox(_T("Make sure result file not open in another application!."));
			e->Delete();
			return;
		}
	}
	else
	{
		file.Open(f1, CFile::modeCreate | CFile::modeWrite, &e);
	}
	logMsg += " \r\n";

	file.Write(logMsg, logMsg.GetLength());
	file.Close();

}
