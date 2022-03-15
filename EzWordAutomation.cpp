// EzWordAutomation.cpp: implementation of the CEzWordAutomation class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "EzWordAutomation.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CEzWordAutomation::CEzWordAutomation()
{
	//Starts Word with bVisible = TRUE and creates empty worksheet 
	m_pWordServer = new CWordAutomation;
}

CEzWordAutomation::CEzWordAutomation(BOOL bVisible)
{
	//Starts Word with bVisible = TRUE and creates empty worksheet 
	m_pWordServer = new CWordAutomation(bVisible);
}

CEzWordAutomation::~CEzWordAutomation()
{
	if(NULL != m_pWordServer)
		delete m_pWordServer;
}



BOOL CEzWordAutomation::CreateBlankDocument()
{
	return m_pWordServer->CreateBlankDocument();
}

BOOL CEzWordAutomation::AppendText(CString szText)
{
	return m_pWordServer->AppendText(szText);
}

CString CEzWordAutomation::GetLine(int nLine)
{
	return m_pWordServer->GetLine(nLine);
}

int CEzWordAutomation::GetLineCount()
{
	return m_pWordServer->GetLinesCount();
}

BOOL CEzWordAutomation::ReleaseWord()
{
	return m_pWordServer->ReleaseWord();
}

BOOL CEzWordAutomation::PasteText(CString szText)
{
	return m_pWordServer->PasteText(szText);
}

BOOL CEzWordAutomation::CopyLinesToClipboard(int nFirstLine, int nLastLine)
{
	return m_pWordServer->CopyLinesToClipboard(nFirstLine, nLastLine);
}

BOOL CEzWordAutomation::SaveWordFileAs(CString szFileName)
{
	return m_pWordServer->SaveWordFileAs(szFileName);
}

BOOL CEzWordAutomation::OpenWordFile(CString szFileName)
{
	m_pWordServer->CloseActiveDocument(FALSE);
	return m_pWordServer->OpenWordFile(szFileName); 
}

CString CEzWordAutomation::SpellWord(CString szWord)
{
	return m_pWordServer->SpellWord(szWord);
}



BOOL CEzWordAutomation::CloseDocument(BOOL bSaveIt)
{
return m_pWordServer->CloseActiveDocument(bSaveIt);
}
