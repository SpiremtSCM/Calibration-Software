// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__F8E1DD13_DA2D_4889_9CC3_B4252263E92C__INCLUDED_)
#define AFX_STDAFX_H__F8E1DD13_DA2D_4889_9CC3_B4252263E92C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#import "C:\Program Files (x86)\Common Files\System\ado\msado15.dll" no_namespace rename("EOF","adoEOF")
#define WM_MYMESSAGE (WM_USER+100)
#define WM_MYMESSAGE2 (WM_USER+101)

#include <atlbase.h>
#include <afxcontrolbars.h>

// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__F8E1DD13_DA2D_4889_9CC3_B4252263E92C__INCLUDED_)
