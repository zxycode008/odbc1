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
	//临时变量,字符串真实长度应+1，终止符隐式存在
	char* _s = (char*)malloc(strlen(origin)+1);
	//将字符串拷贝到临时变量中
	strcpy(_s,origin);
	char* p  =strtok(_s,token);	
	std::vector<std::string> v1;
	while (p)
	{
		std::string tmp(p);		
		v1.push_back(tmp);
		p=strtok(NULL,token);
	}
	//回收内存
	free(_s);
    return v1;
	
}

//字符串替换
std::string replaceAll(const char* src, const char* t, const char* _repstr)
{
	int _findpos = 0;
	int _size = strlen(t);
	char* _t = (char*)malloc(strlen(t)+1);
	strcpy(_t, t);
	char* repstr = (char*)malloc(strlen(_repstr)+1);
	strcpy(repstr,_repstr);

	std::string _str(src);
	std::string& _str2 = _str;
	_findpos = _str.find(t,_findpos);
	while (_findpos != std::string::npos)
	{
		_str.replace(_findpos,_size,repstr);
		_findpos = _str.find(t,_findpos);
	}

	free(_t);
	free(repstr);
	return _str;
	
}