// WordAutomation.h: interface for the CWordAutomation class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WORDAUTOMATION_H__95A76A0B_B338_4EE1_8BD5_7D113F0B5282__INCLUDED_)
#define AFX_WORDAUTOMATION_H__95A76A0B_B338_4EE1_8BD5_7D113F0B5282__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CWordAutomation  
{

#define MAX_DISP_ARGS 10
#define DISPARG_NOFREEVARIANT 0x01
#define DISP_FREEARGS 0x02
#define DISP_NOSHOWEXCEPTIONS 0x03

public:
	BOOL DisplayAlerts(BOOL bPostAlerts);
	BOOL GoToEndOfDocument();
	BOOL CloseActiveDocument(BOOL bSaveIt);
	CString SpellWord(CString szWord);
	BOOL OpenWordFile(CString szFileName);
	BOOL SaveWordFileAs(CString szFileName);
	BOOL CopyLinesToClipboard(int nFirstLine, int nLastLine);
	BOOL PasteText(CString szText);
	int GetLinesCount();
	CString GetLine(int nLine);
	BOOL AppendText(CString szText);
	BOOL CreateBlankDocument();
	CWordAutomation();
	CWordAutomation(BOOL bVisible);
	virtual ~CWordAutomation();
	BOOL ReleaseWord();
	BOOL AddArgumentCStringArray(LPOLESTR lpszArgName,WORD wFlags, LPOLESTR *paszStrings, int iCount);
	BOOL AddArgumentOLEString(LPOLESTR lpszArgName, WORD wFlags, LPOLESTR lpsz);
	BOOL AddArgumentCString(LPOLESTR lpszArgName, WORD wFlags, CString szStr);
	BOOL AddArgumentDouble(LPOLESTR lpszArgName, WORD wFlags, double d);
	BOOL AddArgumentBool(LPOLESTR lpszArgName, WORD wFlags, BOOL b);
	BOOL AddArgumentInt2(LPOLESTR lpszArgName, WORD wFlags, int i);
	BOOL AddArgumentDispatch(LPOLESTR lpszArgName, WORD wFlags, IDispatch * pdisp);
	void AddArgumentCommon(LPOLESTR lpszArgName, WORD wFlags, VARTYPE vt);
	BOOL InitOLE();


protected:
	void ShowException(LPOLESTR szMember, HRESULT hr, EXCEPINFO *pexcep, unsigned int uiArgErr);
	void ReleaseDispatch();
	BOOL SetWordVisible(BOOL bVisible);
	void ReleaseVariant(VARIANTARG *pvarg);
	void ClearAllArgs();
	void ClearVariant(VARIANTARG *pvarg);
	BOOL StartWord();
	 
	int			m_iArgCount;
	int			m_iNamedArgCount;
	VARIANTARG	m_aVargs[MAX_DISP_ARGS];
	DISPID		m_aDispIds[MAX_DISP_ARGS + 1];		// one extra for the member name
	LPOLESTR	m_alpszArgNames[MAX_DISP_ARGS + 1];	// used to hold the argnames for GetIDs
	WORD		m_awFlags[MAX_DISP_ARGS];



	BOOL WordInvoke(IDispatch *pdisp, LPOLESTR szMember, VARIANTARG * pvargReturn,
			WORD wInvokeAction, WORD wFlags);
	IDispatch* m_pdispWordApp;
	BOOL StartExcel();
};

#endif // !defined(AFX_WORDAUTOMATION_H__95A76A0B_B338_4EE1_8BD5_7D113F0B5282__INCLUDED_)
