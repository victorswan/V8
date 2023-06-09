#pragma once

#include <tchar.h>
#include <string>
#include "utility\SystemHelper.h"

class CLogHelper
{
public:
	typedef enum enumLOG_LEVEL
	{
		EDL_NONE	= 0,
		EDL_TRACE	= 1,
		EDL_WARN	= 2,
		EDL_ERROR	= 3
	}ENMLOGLEVEL;

	typedef std::basic_string<TCHAR> _tstring;

	CLogHelper(LPCTSTR lpszSectionName)
	{
		m_enumOutputLevel	= EDL_TRACE;
		m_strLogInfoPrefix	= lpszSectionName;

		m_strLogFilePath = common::utility::systemhelper::Get179AppPath() + L"log.txt";
	}

	void OutputTraceInfo(LPCTSTR lpszFormat, ...)
	{
		if (m_enumOutputLevel <= EDL_TRACE && m_enumOutputLevel > EDL_NONE)
		{
			va_list pArg;
			va_start(pArg, lpszFormat);
			OutputHelper(_T("TRACE"), lpszFormat, pArg);
			va_end(pArg);
		}
	}

	void OutputWarnInfo(LPCTSTR lpszFormat, ...)
	{
		if (m_enumOutputLevel <= EDL_WARN && m_enumOutputLevel > EDL_NONE)
		{
			va_list pArg;
			va_start(pArg, lpszFormat);
			OutputHelper(_T("WARN"), lpszFormat, pArg);
			va_end(pArg);
		}
	}

	void OutputErrorInfo(LPCTSTR lpszFormat, ...)
	{
		if (m_enumOutputLevel <= EDL_ERROR && m_enumOutputLevel > EDL_NONE)
		{
			va_list pArg;
			va_start(pArg, lpszFormat);
			OutputHelper(_T("ERROR"), lpszFormat, pArg);
			va_end(pArg);
		}
	}

	void Output2FileCache(LPCTSTR lpszFormat, ...)
	{
		va_list pArg;
		va_start(pArg, lpszFormat);
		Log2FileCache(lpszFormat, pArg);
		va_end(pArg);
	}

	void FlushCache2File()
	{
		FILE* file = _wfopen(m_strLogFilePath.c_str(), L"a");
		if(file != NULL)
		{
			fwprintf(file, L"%s", m_strLogFileText.c_str());
			fclose(file);
		}
		m_strLogFileText.clear();
	}

	void ClearFileCache()
	{
		m_strLogFileText.clear();
	}

// helper
private:

	void Log(LPCTSTR lpszFormat, ...)
	{
		TCHAR szMsg[1024] = {0};
		va_list pArg;

		va_start(pArg, lpszFormat);
		_vsntprintf(szMsg, (sizeof(szMsg) / sizeof(TCHAR)) - 1, lpszFormat, pArg);
		va_end(pArg);

		//	LogHelper::OutputLog(szMsg);
		OutputDebugString(szMsg);
	}

	void OutputHelper(LPCTSTR lpszTitle, LPCTSTR lpszFormat, va_list pArgs)
	{
		TCHAR szMsg[1024] = {0};
		
		_sntprintf(
			szMsg, 
			sizeof(TCHAR) * 1024,
			TEXT("%s:%s "), lpszTitle,
			m_strLogInfoPrefix.c_str());
		
		int nPrefixLen = _tcslen(szMsg);
		TCHAR* pszContext = szMsg + nPrefixLen;
		
		_vsntprintf(
			pszContext, 
			(sizeof(szMsg) / sizeof(TCHAR)) - nPrefixLen - 1, 
			lpszFormat, 
			pArgs);
		
		Log(szMsg);
	}

	void Log2FileCache(LPCTSTR lpszFormat, va_list pArgs)
	{
		TCHAR szMsg[1024] = {0};
		_vsntprintf(szMsg, (sizeof(szMsg) / sizeof(TCHAR)) - 1, lpszFormat, pArgs);

		SYSTEMTIME st;
		GetLocalTime(&st);
		TCHAR strTime[1024] = {0};
		wsprintf(strTime, L"%4d-%02d-%02d %02d:%02d:%02d  ", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);

		std::wstring strText = strTime;
		strText += szMsg;
		strText += L"\r\n";

		m_strLogFileText += strText;
	}

// attribute member
private:
	ENMLOGLEVEL		m_enumOutputLevel;				// output level flag
	_tstring		m_strLogInfoPrefix;				// output prefix string

	std::wstring	m_strLogFileText;	//输出到log file的缓存内容
	std::wstring	m_strLogFilePath;	//log file的路径
};