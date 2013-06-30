#ifndef _ODBC_DATAMAP
#define _ODBC_DATAMAP


#ifdef _WIN32
#include <Windows.h>
#endif
#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <vector>
#include <time.h>
//包含基本ODBC API的定义
#include <sql.h>
//包含扩展ODBC 的定义
#include <sqlext.h>
#include <sqltypes.h>
#include "logutil.h"


#ifndef _MYUTIL
#define _MYUTIL

#pragma comment(lib,"myutil.lib")
std::string ws2s(const std::wstring& ws);
std::wstring s2ws(const std::string& s);
std::vector<std::string> splitString(const char* origin, const char* token);
std::string replaceAll(const char* src, const char* t, const char* _repstr);

#endif


class OdbcDataMap 
{
public:
   
	typedef struct{
		std::string columnName;
		short columnNum;
		short datatype;
		int columnLen;
		short decimalDigits;
		short nullable;
	}ColumnMetaInfo;

	OdbcDataMap();
	~OdbcDataMap();

	std::string getString(const char* columnName);
	int getInt(const char* columnName);
	double getDouble(const char* columnName);
	tm getTimestamp(const char* columnName);
	long getLong(const char* columnName);
	TIME_STRUCT getTime(const char* columnName);
	DATE_STRUCT getDate(const char* columnName);
	bool next();
	bool hasNext();
	bool first();
	int getColumnCount();
	long getRowCount();
	bool valid();
	void init(SQLHSTMT& hstmt);

private:
	std::vector<std::map<std::string,std::string>> rs;
	std::vector<std::map<std::string,std::string>>::iterator it;
	std::vector<ColumnMetaInfo>   colmeta;
	long rowCount;
	int columnCount;
	int isERROR;

	


};

#endif

