#ifndef _ODBC_DATAMAP
#define _ODBC_DATAMAP


#include "odbc.h"
#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <vector>
#include <time.h>



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

