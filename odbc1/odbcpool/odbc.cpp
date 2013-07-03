#include "odbc.h"

std::string wca2s(const wchar_t* src)
{
	std::wstring tmp = src;
	std::wstring& _tmp = tmp;
	std::string str = ws2s(_tmp);
	return str;

}

int convert_string_to_time_t(const std::string & time_string, time_t* time)
{
	struct tm tm1;
	int i = sscanf(time_string.c_str(), "%d-%d-%d %d:%d:%d" ,     
		&(tm1.tm_year), 
		&(tm1.tm_mon), 
		&(tm1.tm_mday),
		&(tm1.tm_hour),
		&(tm1.tm_min),
		&(tm1.tm_sec),
		&(tm1.tm_wday),
		&(tm1.tm_yday));

//	tm1.tm_year -= 1900;
//	tm1.tm_mon --;
	tm1.tm_isdst=-1;
	*time = mktime(&tm1);

	return i;
}


int covert_string_to_tm(const std::string & time_string, tm* timestamp)
{
	int i = sscanf(time_string.c_str(), "%d-%d-%d %d:%d:%d" ,     
		&(timestamp->tm_year), 
		&(timestamp->tm_mon), 
		&(timestamp->tm_mday),
		&(timestamp->tm_hour),
		&(timestamp->tm_min),
		&(timestamp->tm_sec),
		&(timestamp->tm_wday),
		&(timestamp->tm_yday));

//	timestamp->tm_year -= 1900;
//	timestamp->tm_mon --;
	timestamp->tm_isdst=-1;

	return i;
}