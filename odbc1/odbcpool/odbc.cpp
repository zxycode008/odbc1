#include "odbc.h"

std::string wca2s(const wchar_t* src)
{
	std::wstring tmp = src;
	std::wstring& _tmp = tmp;
	std::string str = ws2s(_tmp);
	return str;

}