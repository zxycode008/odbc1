#ifndef _ODBC_HEADER
#define _ODBC_HEADER

#ifdef _WIN32
#include <Windows.h>
#endif

#include <iostream>
#include <string>
//包含基本ODBC API的定义
#include <sql.h>
//包含扩展ODBC 的定义
#include <sqlext.h>
#include <sqltypes.h>

#include "logutil.h"



#ifndef DLL_API_EXPORT extern _declspec (dllexport)
#define DLL_API_EXPORT extern _declspec (dllexport)
#endif

#ifndef DLL_API_IMPORT extern _declspec (dllimport)
#define DLL_API_IMPORT extern _declspec (dllimport)
#endif

#pragma comment(lib,"LogUtil.lib")

#ifndef _MYUTIL
#define _MYUTIL

#pragma comment(lib,"myutil.lib")
std::string ws2s(const std::wstring& ws);
std::wstring s2ws(const std::string& s);
std::vector<std::string> splitString(const char* origin, const char* token);
std::string replaceAll(const char* src, const char* t, const char* _repstr);

#endif


std::string wca2s(const wchar_t* src);

#endif