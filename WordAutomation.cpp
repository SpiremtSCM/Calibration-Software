// WordAutomation.cpp: implementation of the CWordAutomation class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "WordAutomation.h"
#include <ole2ver.h>
#include <string.h>
#include <winuser.h>


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CWordAutomation::CWordAutomation()
{
	m_pdispWordApp = NULL;
	InitOLE();
	StartWord();
	CreateBlankDocument();
	SetWordVisible(TRUE);
}

CWordAutomation::CWordAutomation(BOOL bVisible)
{
	m_pdispWordApp = NULL;
	InitOLE();
	StartWord();
	CreateBlankDocument();
	SetWordVisible(bVisible);
}

CWordAutomation::~CWordAutomation()
{
	//ReleaseWord();
	ReleaseDispatch();
	OleUninitialize();
}
/*******************************************************************
 *
 *					   ARGUMENT CONSTRUCTOR FUNCTIONS
 *
 *  Each function adds a single argument of a specific type to the list
 *  of arguments for the current invoke.  If appropriate, memory may be
 *  allocated to represent the argument.  This memory will be
 *  automatically freed the next time ClearAllArgs() is called unless
 *  the NOFREEVARIANT flag is specified for a particular argument.  If
 *  NOFREEVARIANT is specified it is the responsibility of the caller
 *  to free the memory allocated for or contained within the argument.
 *
 *  Arguments may be named.  The name string must be a C-style string
 *  and it is owned by the caller.  If dynamically allocated, the caller
 *  must free the name string.
 *
 *******************************************************************/

/*
 *  Common code used by all variant types for setting up an argument.
 */

void CWordAutomation::AddArgumentCommon(LPOLESTR lpszArgName, WORD wFlags, VARTYPE vt)
{
	ClearVariant(&m_aVargs[m_iArgCount]);
	
	m_aVargs[m_iArgCount].vt = vt;
	m_awFlags[m_iArgCount] = wFlags;
	
	if (lpszArgName != NULL) 
	{
		m_alpszArgNames[m_iNamedArgCount + 1] = lpszArgName;
		m_iNamedArgCount++;
	}
}	
	

BOOL CWordAutomation::AddArgumentDispatch(LPOLESTR lpszArgName, WORD wFlags, IDispatch * pdisp)
{
	AddArgumentCommon(lpszArgName, wFlags, VT_DISPATCH);
	m_aVargs[m_iArgCount++].pdispVal = pdisp;
	return TRUE;
}


BOOL CWordAutomation::AddArgumentInt2(LPOLESTR lpszArgName, WORD wFlags, int i)
{
	AddArgumentCommon(lpszArgName, wFlags, VT_I2);
	m_aVargs[m_iArgCount++].iVal = i;
	return TRUE;
}


BOOL CWordAutomation::AddArgumentBool(LPOLESTR lpszArgName, WORD wFlags, BOOL b)
{
	AddArgumentCommon(lpszArgName, wFlags, VT_BOOL);
	// Note the variant representation of True as -1
	m_aVargs[m_iArgCount++].boolVal = b ? -1 : 0;
	return TRUE;
}

BOOL CWordAutomation::AddArgumentDouble(LPOLESTR lpszArgName, WORD wFlags, double d)
{
	AddArgumentCommon(lpszArgName, wFlags, VT_R8);
	m_aVargs[m_iArgCount++].dblVal = d;
	return TRUE;
}


BOOL CWordAutomation::ReleaseWord()
{
	if (m_pdispWordApp == NULL)
		return TRUE;
	
	// Tell Word to quit, since for automation simply releasing the IDispatch
	// object isn't enough to get the server to shut down.
	
	// Note that this code will hang if Excel tries to display any message boxes.
	// This can occur if a document is in need of saving.  The CreateChart() code
	// always clears the dirty bit on the documents it creates, avoiding this problem.
	ClearAllArgs();
	WordInvoke(m_pdispWordApp, L"Quit", NULL, DISPATCH_METHOD, 0);
	
	// Even though Word has been told to Quit, we still need to release the
	// OLE object to account for all memory.
	ReleaseDispatch();
	
	return TRUE;

}
/*
 *  ClearVariant
 *
 *  Zeros a variant structure without regard to current contents
 */
void CWordAutomation::ClearVariant(VARIANTARG *pvarg)
{
	pvarg->vt = VT_EMPTY;
	pvarg->wReserved1 = 0;
	pvarg->wReserved2 = 0;
	pvarg->wReserved3 = 0;
	pvarg->lVal = 0;

}

//Clean up: release dipatches
void CWordAutomation::ReleaseDispatch()
{
	if(NULL != m_pdispWordApp)
	{
		m_pdispWordApp->Release();
		m_pdispWordApp = NULL;
	}

}

/*
 *  ClearAllArgs
 *
 *  Clears the existing contents of the arg array in preparation for
 *  a new invocation.  Frees argument memory if so marked.
 */
void CWordAutomation::ClearAllArgs()
{
	int i;
	
	for (i = 0; i < m_iArgCount; i++) 
	{
		if (m_awFlags[i] & DISPARG_NOFREEVARIANT)
			// free the variant's contents based on type
			ClearVariant(&m_aVargs[i]);
		else
			ReleaseVariant(&m_aVargs[i]);
	}

	m_iArgCount = 0;
	m_iNamedArgCount = 0;

}

/*
 *  ReleaseVariant
 *
 *  Clears a particular variant structure and releases any external objects
 *  or memory contained in the variant.  Supports the data types listed above.
 */
void CWordAutomation::ReleaseVariant(VARIANTARG *pvarg)
{
	VARTYPE vt;
	VARIANTARG *pvargArray;
	long lLBound, lUBound, l;
	
	vt = pvarg->vt & 0xfff;		// mask off flags
	
	// check if an array.  If so, free its contents, then the array itself.
	if (V_ISARRAY(pvarg)) 
	{
		// variant arrays are all this routine currently knows about.  Since a
		// variant can contain anything (even other arrays), call ourselves
		// recursively.
		if (vt == VT_VARIANT) 
		{
			SafeArrayGetLBound(pvarg->parray, 1, &lLBound);
			SafeArrayGetUBound(pvarg->parray, 1, &lUBound);
			
			if (lUBound > lLBound) 
			{
				lUBound -= lLBound;
				
				SafeArrayAccessData(pvarg->parray, (void**)&pvargArray);
				
				for (l = 0; l < lUBound; l++) 
				{
					ReleaseVariant(pvargArray);
					pvargArray++;
				}
				
				SafeArrayUnaccessData(pvarg->parray);
			}
		}
		else 
		{
			MessageBox(NULL, _T("ReleaseVariant: Array contains non-variant type"), "Failed", MB_OK | MB_ICONSTOP);
		}
		
		// Free the array itself.
		SafeArrayDestroy(pvarg->parray);
	}
	else 
	{
		switch (vt) 
		{
			case VT_DISPATCH:
				//(*(pvarg->pdispVal->lpVtbl->Release))(pvarg->pdispVal);
				pvarg->pdispVal->Release();
				break;
				
			case VT_BSTR:
				SysFreeString(pvarg->bstrVal);
				break;
				
			case VT_I2:
			case VT_BOOL:
			case VT_R8:
			case VT_ERROR:		// to avoid erroring on an error return from Excel
				// no work for these types
				break;
				
			default:
				MessageBox(NULL, _T("ReleaseVariant: Unknown type"), "Failed", MB_OK | MB_ICONSTOP);
				break;
		}
	}
	
	ClearVariant(pvarg);

}
/*******************************************************************
 *
 *								INVOKE
 *
 *******************************************************************/

/*
 *  INVOKE
 *
 *  Invokes a method or property.  Takes the IDispatch object on which to invoke,
 *  and the name of the method or property as a String.  Arguments, if any,
 *  must have been previously setup using the AddArgumentXxx() functions.
 *
 *  Returns TRUE if the call succeeded.  Returns FALSE if an error occurred.
 *  A messagebox will be displayed explaining the error unless the DISP_NOSHOWEXCEPTIONS
 *  flag is specified.  Errors can be a result of unrecognized method or property
 *  names, bad argument names, invalid types, or runtime-exceptions defined
 *  by the recipient of the Invoke.
 *
 *  The argument list is reset via ClearAllArgs() if the DISP_FREEARGS flag is
 *  specified.  If not specified, it is up to the caller to call ClearAllArgs().
 *
 *  The return value is placed in pvargReturn, which is allocated by the caller.
 *  If no return value is required, pass NULL.  It is up to the caller to free
 *  the return value (ReleaseVariant()).
 *
 *  This function calls IDispatch::GetIDsOfNames for every invoke.  This is not
 *  very efficient if the same method or property is invoked multiple times, since
 *  the DISPIDs for a particular method or property will remain the same during
 *  the lifetime of an IDispatch object.  Modifications could be made to this code
 *  to cache DISPIDs.  If the target application is always the same, a similar
 *  modification is to statically browse and store the DISPIDs at compile-time, since
 *  a given application will return the same DISPIDs in different sessions.
 *  Eliminating the extra cross-process GetIDsOfNames call can result in a
 *  signficant time savings.
 */


BOOL CWordAutomation::WordInvoke(IDispatch *pdisp, LPOLESTR szMember, VARIANTARG * pvargReturn,
			WORD wInvokeAction, WORD wFlags)
{
	HRESULT hr;
	DISPPARAMS dispparams;
	unsigned int uiArgErr;
	EXCEPINFO excep;
	
	// Get the IDs for the member and its arguments.  GetIDsOfNames expects the
	// member name as the first name, followed by argument names (if any).
	m_alpszArgNames[0] = szMember;
	hr = pdisp->GetIDsOfNames( IID_NULL, m_alpszArgNames,
								1 + m_iNamedArgCount, LOCALE_SYSTEM_DEFAULT, m_aDispIds);
	if (FAILED(hr)) 
	{
		if (!(wFlags & DISP_NOSHOWEXCEPTIONS))
			ShowException(szMember, hr, NULL, 0);
		return FALSE;
	}
	
	if (pvargReturn != NULL)
		ClearVariant(pvargReturn);
	
	// if doing a property put(ref), we need to adjust the first argument to have a
	// named arg of DISPID_PROPERTYPUT.
	if (wInvokeAction & (DISPATCH_PROPERTYPUT | DISPATCH_PROPERTYPUTREF)) 
	{
		m_iNamedArgCount = 1;
		m_aDispIds[1] = DISPID_PROPERTYPUT;
		pvargReturn = NULL;
	}
	
	dispparams.rgdispidNamedArgs = m_aDispIds + 1;
	dispparams.rgvarg = m_aVargs;
	dispparams.cArgs = m_iArgCount;
	dispparams.cNamedArgs = m_iNamedArgCount;
	
	excep.pfnDeferredFillIn = NULL;
	
	hr = pdisp->Invoke(m_aDispIds[0], IID_NULL, LOCALE_SYSTEM_DEFAULT,
								wInvokeAction, &dispparams, pvargReturn, &excep, &uiArgErr);
	
	if (wFlags & DISP_FREEARGS)
		ClearAllArgs();
	
	if (FAILED(hr)) 
	{
		// display the exception information if appropriate:
		if (!(wFlags & DISP_NOSHOWEXCEPTIONS))
			ShowException(szMember, hr, &excep, uiArgErr);
	
		// free exception structure information
		SysFreeString(excep.bstrSource);
		SysFreeString(excep.bstrDescription);
		SysFreeString(excep.bstrHelpFile);
	
		return FALSE;
	}
	return TRUE;
}

//Error handling
void CWordAutomation::ShowException(LPOLESTR szMember, HRESULT hr, EXCEPINFO *pexcep, unsigned int uiArgErr)
{
	TCHAR szBuf[512];
	
	switch (GetScode(hr)) 
	{
		case DISP_E_UNKNOWNNAME:
			wsprintf(szBuf, "%s: Unknown name or named argument.", szMember);
			break;
	
		case DISP_E_BADPARAMCOUNT:
			wsprintf(szBuf, "%s: Incorrect number of arguments.", szMember);
			break;
			
		case DISP_E_EXCEPTION:
			wsprintf(szBuf, "%s: Error %d: ", szMember, pexcep->wCode);
			if (pexcep->bstrDescription != NULL)
				lstrcat(szBuf, (char*)pexcep->bstrDescription);
			else
				lstrcat(szBuf, "<<No Description>>");
			break;
			
		case DISP_E_MEMBERNOTFOUND:
			wsprintf(szBuf, "%s: method or property not found.", szMember);
			break;
		
		case DISP_E_OVERFLOW:
			wsprintf(szBuf, "%s: Overflow while coercing argument values.", szMember);
			break;
		
		case DISP_E_NONAMEDARGS:
			wsprintf(szBuf, "%s: Object implementation does not support named arguments.",
						szMember);
		    break;
		    
		case DISP_E_UNKNOWNLCID:
			wsprintf(szBuf, "%s: The locale ID is unknown.", szMember);
			break;
		
		case DISP_E_PARAMNOTOPTIONAL:
			wsprintf(szBuf, "%s: Missing a required parameter.", szMember);
			break;
		
		case DISP_E_PARAMNOTFOUND:
			wsprintf(szBuf, "%s: Argument not found, argument %d.", szMember, uiArgErr);
			break;
			
		case DISP_E_TYPEMISMATCH:
			wsprintf(szBuf, "%s: Type mismatch, argument %d.", szMember, uiArgErr);
			break;

		default:
			wsprintf(szBuf, "%s: Unknown error occured.", szMember);
			break;
	}
	
	MessageBox(NULL, szBuf, "OLE Error", MB_OK | MB_ICONSTOP);

}

BOOL CWordAutomation::StartWord()
{
	CLSID clsWordApp;

	// if Excel is already running, return with current instance
	if (m_pdispWordApp != NULL)
		return TRUE;

	/* Obtain the CLSID that identifies EXCEL.APPLICATION
	 * This value is universally unique to Excel versions 5 and up, and
	 * is used by OLE to identify which server to start.  We are obtaining
	 * the CLSID from the ProgID.
	 */
	if (FAILED(CLSIDFromProgID(L"Word.Application", &clsWordApp))) 
	{
		MessageBox(NULL, _T("Cannot obtain CLSID from ProgID"), "Failed", MB_OK | MB_ICONSTOP);
		return FALSE;
	}

	// start a new copy of Excel, grab the IDispatch interface
	if (FAILED(CoCreateInstance(clsWordApp, NULL, CLSCTX_LOCAL_SERVER, IID_IDispatch, (void**)&m_pdispWordApp))) 
	{
		MessageBox(NULL, _T("Cannot start an instance of Excel for Automation."), "Failed", MB_OK | MB_ICONSTOP);
		return FALSE;
	}

	return TRUE;

}

BOOL CWordAutomation::SetWordVisible(BOOL bVisible)
{
	if (m_pdispWordApp == NULL)
		return FALSE;
	
	ClearAllArgs();
	AddArgumentBool(NULL, 0, bVisible);
	return WordInvoke(m_pdispWordApp, L"Visible", NULL, DISPATCH_PROPERTYPUT, DISP_FREEARGS);

}

BOOL CWordAutomation::InitOLE()
{
	DWORD dwOleVer;
	
	dwOleVer = CoBuildVersion();
	
	// check the OLE library version
	if (rmm != HIWORD(dwOleVer)) 
	{
		MessageBox(NULL, _T("Incorrect version of OLE libraries."), "Failed", MB_OK | MB_ICONSTOP);
		return FALSE;
	}
	
	// could also check for minor version, but this application is
	// not sensitive to the minor version of OLE
	
	// initialize OLE, fail application if we can't get OLE to init.
	if (FAILED(OleInitialize(NULL))) 
	{
		MessageBox(NULL, _T("Cannot initialize OLE."), "Failed", MB_OK | MB_ICONSTOP);
		return FALSE;
	}
	
		
	return TRUE;

}

//Create empty Word document by executing
//Documents.Add 
BOOL CWordAutomation::CreateBlankDocument()
{
	if(NULL  == m_pdispWordApp)
		return FALSE;

	VARIANTARG varg1, varg2;
	
	//Documents.Add
	ClearAllArgs();
	if (!WordInvoke(m_pdispWordApp, L"Documents", &varg1, DISPATCH_PROPERTYGET, 0))
		return FALSE;
	ClearAllArgs();
	if (!WordInvoke(varg1.pdispVal, L"Add", &varg2, DISPATCH_METHOD, 0))
		return FALSE;

	return TRUE;
}

//Move to the last line and 
//add text to the Word document by executing
//Selection.TypeText Text:="Enter my text szText"
BOOL CWordAutomation::AppendText(CString szText)
{
	if(NULL  == m_pdispWordApp)
		return FALSE;

	VARIANTARG varg1, varg2;
	int wdGoToLine = 3;		//MsWord constant
	int wdGoToLast = -1;	//MsWord constant
	
	//Got to first line
	ClearAllArgs();
	if (!WordInvoke(m_pdispWordApp, L"Selection", &varg1, DISPATCH_PROPERTYGET, 0))
		return FALSE;
	GoToEndOfDocument();

	//Documents.Add
	ClearAllArgs();
	AddArgumentCString(L"Text", 0, szText);
	if (!WordInvoke(varg1.pdispVal, L"TypeText", &varg2, DISPATCH_METHOD, 0))
		return FALSE;

	return TRUE;
}

BOOL CWordAutomation::AddArgumentCString(LPOLESTR lpszArgName, WORD wFlags, CString szStr)
{
	BSTR b;
	
	b = szStr.AllocSysString();
	if (!b)
		return FALSE;
	AddArgumentCommon(lpszArgName, wFlags, VT_BSTR);
	m_aVargs[m_iArgCount++].bstrVal = b;
	
	return TRUE;
}
//Copy line:
//	  Selection.HomeKey Unit:=wdLine
//    Selection.EndKey Unit:=wdLine, Extend:=wdExtend
//    Selection.Copy
//Move up/down
//Selection.MoveUp Unit:=wdLine, Count:=2
//Selection.MoveDown Unit:=wdLine, Count:=1

CString CWordAutomation::GetLine(int nLine)
{
	CString szLine = _T("");
	if(NULL  == m_pdispWordApp)
		return szLine;

	VARIANTARG varg1, varg2;
	int wdGoToLine = 3;		//MsWord constant
	int wdGoToAbsolute = 1;	//MsWord constant
	int wdLine = 5;			//MsWord constant
	int wdExtend = 1;		//MsWord constant
	
	//Got to line
	ClearAllArgs();
	if (!WordInvoke(m_pdispWordApp, L"Selection", &varg1, DISPATCH_PROPERTYGET, 0))
		return szLine;
	ClearAllArgs();
	AddArgumentInt2(L"What", 0, wdGoToLine);
	AddArgumentInt2(L"Which", 0, wdGoToAbsolute);
	AddArgumentInt2(L"Count", 0, nLine);
	if (!WordInvoke(varg1.pdispVal, L"GoTo", NULL, DISPATCH_METHOD, 0))
		return szLine;
	
	//Selection.HomeKey Unit:=wdLine
	ClearAllArgs();
	AddArgumentInt2(L"Unit", 0, wdLine);
	if (!WordInvoke(varg1.pdispVal, L"HomeKey", NULL, DISPATCH_METHOD, 0))
		return szLine;
	//Selection.EndKey Unit:=wdLine, Extend:=wdExtend
	ClearAllArgs();
	AddArgumentInt2(L"Unit", 0, wdLine);
	AddArgumentInt2(L"Extend", 0, wdExtend);
	if (!WordInvoke(varg1.pdispVal, L"EndKey", &varg2, DISPATCH_METHOD, 0))
		return szLine;
	ClearAllArgs();
	if (!WordInvoke(varg1.pdispVal, L"Text", &varg2, DISPATCH_PROPERTYGET, 0))
		return szLine;

	//Get text from varg2
	VARTYPE Type = varg2.vt;
	switch (Type) 
		{
			case VT_UI1:
				{
					unsigned char nChr = varg2.bVal;
					//szLine = nChr;
				}
				break;
			case VT_I4:
				{
					long nVal = varg2.lVal;
					szLine.Format("%i", nVal);
				}
				break;
			case VT_R4:
				{
					float fVal = varg2.fltVal;
					szLine.Format("%f", fVal);
				}
				break;
			case VT_R8:
				{
					double dVal = varg2.dblVal;
					szLine.Format("%f", dVal);
				}
				break;
			case VT_BSTR:
				{
					BSTR b = varg2.bstrVal;
					szLine = b;
				}
				break;
			case VT_BYREF|VT_UI1:
				{
					//Not tested
					unsigned char* pChr = varg2.pbVal;
					//szLine = *pChr;
				}
				break;
			case VT_BYREF|VT_BSTR:
				{
					//Not tested
					BSTR* pb = varg2.pbstrVal;
					szLine = *pb;
				}
			case 0:
				{
					//Empty
					szLine = _T("");
				}
			}

	
	return szLine;

}
//Find the number of lines in this document by executing macro:
//n = ActiveDocument.ComputeStatistics(Statistic:=wdStatisticLines)
int CWordAutomation::GetLinesCount()
{
	int nLineCount = -1;
	if(NULL  == m_pdispWordApp)
		return nLineCount;

	VARIANTARG varg1, varg2;
	int wdStatisticLines = 1;		//MsWord constant

	//Get ActiveDocument object
	ClearAllArgs();
	if (!WordInvoke(m_pdispWordApp, L"ActiveDocument", &varg1, DISPATCH_PROPERTYGET, 0))
		return nLineCount;
	//Get statistics
	ClearAllArgs();
	AddArgumentInt2(L"Statistic", 0, wdStatisticLines);
	if (!WordInvoke(varg1.pdispVal, L"ComputeStatistics", &varg2, DISPATCH_METHOD, 0))
		return nLineCount;

	//Find how many lines there
		VARTYPE Type = varg2.vt;
		if(Type != VT_I4)
			return -1;
		nLineCount = varg2.lVal; //We did reach the end - get the number of lines
			
	return nLineCount;

}
//Paste text from clipboard. Append it at the end of the document
BOOL CWordAutomation::PasteText(CString szText)
{
	if(NULL  == m_pdispWordApp)
		return FALSE;

	if(szText.IsEmpty())
		return FALSE;
	//Place text to clipboard
	long nBuffSize = szText.GetLength(); 
	//Nothing to copy
	if(0 == nBuffSize)
		return FALSE;

	HANDLE hMem = GlobalAlloc(GMEM_MOVEABLE|GMEM_DDESHARE, 24);
  
	  if (OpenClipboard(NULL) )
	  {
		HGLOBAL hClipMem;
		char* buffer;
		BOOL bResult = TRUE;
		
		EmptyClipboard();
		hClipMem = GlobalAlloc(GMEM_DDESHARE, nBuffSize);
		buffer = (char*)GlobalLock(hClipMem);
		memcpy(buffer, szText, nBuffSize);
		GlobalUnlock(hClipMem);
		SetClipboardData(CF_TEXT, hClipMem);
		CloseClipboard();
	  }
	

	VARIANTARG varg1;
	int wdGoToLine = 3;		//MsWord constant
	int wdGoToLast = -1;	//MsWord constant
	int wdLine =  5;		//MsWord constant

	//Got to Last line
	ClearAllArgs();
	if (!WordInvoke(m_pdispWordApp, L"Selection", &varg1, DISPATCH_PROPERTYGET, 0))
		return FALSE;
	GoToEndOfDocument();
	ClearAllArgs();
	if (!WordInvoke(varg1.pdispVal, L"Paste", NULL, DISPATCH_METHOD, 0))
		return FALSE;

	return TRUE;
}

BOOL CWordAutomation::CopyLinesToClipboard(int nFirstLine, int nLastLine)
{
	
	if(NULL  == m_pdispWordApp)
		return FALSE;

	VARIANTARG varg1, varg2;
	int wdGoToLine = 3;		//MsWord constant
	int wdGoToAbsolute = 1;	//MsWord constant
	int wdLine = 5;			//MsWord constant
	int wdExtend = 1;		//MsWord constant
	
	//Got to first line
	ClearAllArgs();
	if (!WordInvoke(m_pdispWordApp, L"Selection", &varg1, DISPATCH_PROPERTYGET, 0))
		return FALSE;
	ClearAllArgs();
	AddArgumentInt2(L"What", 0, wdGoToLine);
	AddArgumentInt2(L"Which", 0, wdGoToAbsolute);
	AddArgumentInt2(L"Count", 0, nFirstLine);
	if (!WordInvoke(varg1.pdispVal, L"GoTo", &varg2, DISPATCH_METHOD, 0))
		return FALSE;
	
	//Select lines
	//Selection.MoveDown Unit:=wdLine, Count:=nLastLine-nFirstLine, Extend:=wdExtend
	ClearAllArgs();
	AddArgumentInt2(L"Unit", 0, wdLine);
	AddArgumentInt2(L"Count", 0, nLastLine-nFirstLine);
	AddArgumentInt2(L"Extend", 0, wdExtend);
	if (!WordInvoke(varg1.pdispVal, L"MoveDown", NULL, DISPATCH_METHOD, 0))
		return FALSE;
	
	ClearAllArgs();
	if (!WordInvoke(varg1.pdispVal, L"Copy", NULL, DISPATCH_METHOD, 0))
		return FALSE;
	return TRUE;
}

BOOL CWordAutomation::SaveWordFileAs(CString szFileName)
{
	//ActiveDocument.SaveAs FileName:="Text.rtf", FileFormat:= wdFormatText
	if(NULL  == m_pdispWordApp)
		return FALSE;

	VARIANTARG varg1;	
	int wdFormatText = 2;
	ClearAllArgs();
	if (!WordInvoke(m_pdispWordApp, L"ActiveDocument", &varg1, DISPATCH_PROPERTYGET, 0))
		return FALSE;
	
	ClearAllArgs();
	AddArgumentCString(L"FileName", 0, szFileName);
	if (!WordInvoke(varg1.pdispVal, L"SaveAs", NULL, DISPATCH_METHOD, 0))
		return FALSE;

	return TRUE;
}

BOOL CWordAutomation::OpenWordFile(CString szFileName)
{
	//Documents.Open FileName:="C:\MyFiles\MyDoc.doc", ReadOnly:=True
	if(NULL  == m_pdispWordApp)
		return FALSE;

	VARIANTARG varg1;
	ClearAllArgs();
	if (!WordInvoke(m_pdispWordApp, L"Documents", &varg1, DISPATCH_PROPERTYGET, 0))
		return FALSE;
	
	ClearAllArgs();
	AddArgumentCString(L"FileName", 0, szFileName);
	if (!WordInvoke(varg1.pdispVal, L"Open", NULL, DISPATCH_METHOD, 0))
		return FALSE;
	
	return TRUE;
}
//Check spelling by executing this macro
//s = Application.GetSpellingSuggestions(Word:="styd").Item(Index:=1).Name
CString CWordAutomation::SpellWord(CString szWord)
{
	CString szSpelling;
	szSpelling = _T("No spelling");

	if(NULL  == m_pdispWordApp)
		return szSpelling;

	VARIANTARG varg1, varg2, varg3, varg4;
	int wdSpellword = 0;
	
	//Application.GetSpellingSuggestions Word:=szWord)
	ClearAllArgs();
	AddArgumentCString(L"Word", 0, szWord);
	if (!WordInvoke(m_pdispWordApp, L"GetSpellingSuggestions", &varg1, DISPATCH_METHOD, 0))
		return szSpelling;

	//Check if there Word  has any suggested spelling for this word
	//nCount = GetSpellingSuggestions(Word:="styd", SuggestionMode:=wdSpellword).Count
	ClearAllArgs();
	if (!WordInvoke(varg1.pdispVal, L"Count", &varg2, DISPATCH_PROPERTYGET, 0))
		return szSpelling;

	if(varg2.vt != VT_I4)
		return szSpelling;
	int nCount = varg2.lVal;
	if(nCount == 0)
	{
		//No suggestion. Leave with the original spelling.
		szSpelling = szWord;
		return szSpelling;
	}
	//Get first suggested spelling from the Word list
	//s = Application.GetSpellingSuggestions(Word:="styd", SuggestionMode:=wdSpellword).Item(Index:=1).Name
	ClearAllArgs();
	AddArgumentInt2(L"Index", 0, 1);
	if (!WordInvoke(varg1.pdispVal, L"Item", &varg3, DISPATCH_METHOD, 0))
		return szSpelling;
	ClearAllArgs();
	if (!WordInvoke(varg3.pdispVal, L"Name", &varg4, DISPATCH_PROPERTYGET, 0))
		return szSpelling;
		
	//Check what speller tell us
	VARTYPE Type = varg4.vt;
	if(varg4.vt != VT_BSTR)
		return szSpelling;

	BSTR b = varg4.bstrVal;
	szSpelling = b;
	return szSpelling;

}
//Close active docyment by:
//ActiveDocument.Close
BOOL CWordAutomation::CloseActiveDocument(BOOL bSaveIt)
{
	if(NULL  == m_pdispWordApp)
		return FALSE;
	int wdDoNotSaveChanges = 0;
	int wdPromptToSaveChanges = -2;
	int wdSaveOption = wdDoNotSaveChanges;
	if(bSaveIt)
		wdSaveOption = wdPromptToSaveChanges;

	VARIANTARG varg1;	
	ClearAllArgs();
	if (!WordInvoke(m_pdispWordApp, L"ActiveDocument", &varg1, DISPATCH_PROPERTYGET, 0))
		return FALSE;
	ClearAllArgs();
	AddArgumentInt2(L"SaveChanges", 0, wdSaveOption);
	if (!WordInvoke(varg1.pdispVal, L"Close", NULL, DISPATCH_METHOD, 0))
		return FALSE;

	return TRUE;

}

BOOL CWordAutomation::GoToEndOfDocument()
{
	if(NULL  == m_pdispWordApp)
		return FALSE;

	VARIANTARG varg1;
	int wdGoToLine = 3;		//MsWord constant
	int wdGoToLast = -1;	//MsWord constant
	int wdLine =  5;		//MsWord constant

	//Got to line
	ClearAllArgs();
	if (!WordInvoke(m_pdispWordApp, L"Selection", &varg1, DISPATCH_PROPERTYGET, 0))
		return FALSE;
	ClearAllArgs();
	AddArgumentInt2(L"What", 0, wdGoToLine);
	AddArgumentInt2(L"Which", 0, wdGoToLast);
	if (!WordInvoke(varg1.pdispVal, L"GoTo", NULL, DISPATCH_METHOD, 0))
		return FALSE;

	//Selection.EndKey Unit:=wdLine
	ClearAllArgs();
	AddArgumentInt2(L"Unit", 0, wdLine);
	if (!WordInvoke(varg1.pdispVal, L"EndKey", NULL, DISPATCH_METHOD, 0))
		return FALSE;

	return TRUE;
}
