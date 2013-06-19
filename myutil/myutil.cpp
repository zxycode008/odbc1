#include "myutil.h"
#include <iostream>
#include <string>
#include <stdio.h>
#include <string.h>
#include <vector>

 std::string ws2s(const std::wstring& ws)
{
	std::string curLocale = setlocale(LC_ALL, NULL);        // curLocale = "C";
	setlocale(LC_ALL, "chs");
	const wchar_t* _Source = ws.c_str();
	size_t _Dsize = 2 * ws.size() + 1;
	char *_Dest = new char[_Dsize];
	memset(_Dest,0,_Dsize);
	wcstombs(_Dest,_Source,_Dsize);
	std::string result = _Dest;
	delete []_Dest;
	setlocale(LC_ALL, curLocale.c_str());
	return result;
}

std::wstring s2ws(const std::string& s)
{
	setlocale(LC_ALL, "chs"); 
	const char* _Source = s.c_str();
	size_t _Dsize = s.size() + 1;
	wchar_t *_Dest = new wchar_t[_Dsize];
	wmemset(_Dest, 0, _Dsize);
	mbstowcs(_Dest,_Source,_Dsize);
	std::wstring result = _Dest;
	delete []_Dest;
	setlocale(LC_ALL, "C");
	return result;
}

std::vector<std::string> splitString(const char* origin, const char* token){
	char* _s = (char*)malloc(sizeof(origin));
	strcpy(_s,origin);
	char* p  =strtok(_s,token);	
	int i = 0;
	std::vector<std::string> v1;
	while (p)
	{
		std::string tmp(p);		
		v1.push_back(tmp);
		p=strtok(NULL,token);
	}
    return v1;
	
}