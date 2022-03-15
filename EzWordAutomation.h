// EzWordAutomation.h: interface for the CEzWordAutomation class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EZWORDAUTOMATION_H__4BAE37DA_1A96_42D0_99E5_74E58F5D733F__INCLUDED_)
#define AFX_EZWORDAUTOMATION_H__4BAE37DA_1A96_42D0_99E5_74E58F5D733F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "WordAutomation.h"

class CEzWordAutomation  
{
public:
	BOOL CloseDocument(BOOL bSaveIt);
	CString SpellWord(CString szWord);
	BOOL OpenWordFile(CString szFileName);
	BOOL SaveWordFileAs(CString szFileName);
	BOOL CopyLinesToClipboard(int nFirstLine, int nLastLine);
	BOOL PasteText(CString szText);
	BOOL ReleaseWord();
	int GetLineCount();
	CString GetLine(int nLine);
	BOOL AppendText(CString szText);
	BOOL CreateBlankDocument();
	CEzWordAutomation();
	CEzWordAutomation(BOOL bVisible);
	virtual ~CEzWordAutomation();

protected:
	CWordAutomation* m_pWordServer;
};

#endif // !defined(AFX_EZWORDAUTOMATION_H__4BAE37DA_1A96_42D0_99E5_74E58F5D733F__INCLUDED_)
