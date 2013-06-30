#ifndef _MYUTIL
#define _MYUTIL
#define  DLL_API_EXPORT extern _declspec (dllexport)
	
#include <string>
#include <vector>

DLL_API_EXPORT  std::string ws2s(const std::wstring& ws);
DLL_API_EXPORT  std::wstring s2ws(const std::string& s);
DLL_API_EXPORT  std::vector<std::string> splitString(const char* origin, const char* token);
DLL_API_EXPORT  std::string replaceAll(const char* src, const char* t, const char* _repstr);

#endif