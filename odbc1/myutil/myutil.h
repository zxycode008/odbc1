#ifndef _MYUTIL
#define _MYUTIL
#define  DLL_API extern _declspec (dllexport)
	
#include <string>
#include <vector>

DLL_API  std::string ws2s(const std::wstring& ws);
DLL_API  std::wstring s2ws(const std::string& s);
DLL_API  std::vector<std::string> splitString(const char* origin, const char* token);

#endif