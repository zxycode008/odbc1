#ifndef _MYUTIL
#define _MYUTIL
#ifdef _MYUTIL_EXPORTS
#define  DLL_API _declspec(dllexport)
#else
#define  DLL_API _declspec(dllimport)
#endif


#include <iostream>
#include <string>

DLL_API std::string ws2s(const std::wstring& ws);
DLL_API std::wstring s2ws(const std::string& s);
#endif