#include "odbcdata.h"
#include "odbc.h"


OdbcDataMap::OdbcDataMap()
{

}


OdbcDataMap::~OdbcDataMap()
{

}

void OdbcDataMap::init(SQLHSTMT &hstmt)
{
	short count = 0;
	int rec = 0;
	rec = SQLNumResultCols(hstmt,(SQLSMALLINT*)&count);
	rec = SQLRowCount(hstmt,&this->rowCount);
	if (rec == SQL_ERROR)
	{
		this->isERROR = true;
		return;
	}else{
		this->isERROR = false;
		this->columnCount = count;
	}
	for (short i=0; i<=count; i++)
	{
		//int columnNum;
		SQLWCHAR columnName[255];
		short columnNameLength;
		memset(columnName,'\0',sizeof(columnName));
		short datatype;
		unsigned long columnSize;
		short decimalDigits;
		short nullable;
		rec = SQLDescribeCol(hstmt,i,columnName,255,&columnNameLength, &datatype, &columnSize,&decimalDigits,&nullable);
		if (rec == SQL_ERROR)
		{
			continue;
		}
		OdbcDataMap::ColumnMetaInfo mi;
		mi.columnLen = (int)columnSize;
		mi.columnNum = i;
		mi.columnName = wca2s(columnName);
		mi.datatype = datatype;
		mi.decimalDigits =decimalDigits;
		mi.nullable = nullable;
		this->colmeta.push_back(mi);




	}
	while (SQLFetch(hstmt) != SQL_NO_DATA_FOUND)
	{

		std::map<std::string,std::string> record;
		for (int i = 0; i<this->columnCount; i++)
		{
			SQLWCHAR* v = (SQLWCHAR*) malloc(sizeof(SQLWCHAR)*(colmeta[i].columnLen + 1));
//			std::cout<<wcslen(v)<<std::endl;
			SQLINTEGER len;
			int buffsize = (colmeta[i].columnLen+1)*2;
			rec = SQLGetData(hstmt,colmeta[i].columnNum,SQL_C_WCHAR,v,buffsize,&len);	
			std::string tmp = wca2s(v);
			record.insert(std::map<std::string,std::string>::value_type(colmeta[i].columnName,tmp));   
			free(v);
		}
		rs.push_back(record);
	}
	this->it = this->rs.begin();
}


bool OdbcDataMap::first()
{
    this->it = rs.begin();
	return true;

}

bool OdbcDataMap::next()
{
     if (it == this->rs.end())
     {
		 return false;
     }
	 it++;
	 return true;

}

bool OdbcDataMap::hasNext()
{
	std::vector<std::map<std::string,std::string>>::iterator it2;
	it2 = it;
	if (it2 == this->rs.end())
	{
		return false;
	}
	return true;
}

int OdbcDataMap::getColumnCount()
{
	return this->columnCount;
}

long OdbcDataMap::getRowCount()
{
	return this->rowCount;
}


bool OdbcDataMap::valid()
{
	return this->isERROR;
}


std::string OdbcDataMap::getString(const char *columnName)
{
	std::map<std::string,std::string> record = *it;
	std::string cn = columnName;
	std::map<std::string,std::string>::iterator m_it;
	m_it = record.find(cn);
	if (m_it == record.end())
	{
		return NULL;
	}
	return m_it->second;
}

int OdbcDataMap::getInt(const char *columnName)
{
	std::map<std::string,std::string> record = *it;
	std::string cn = columnName;
	std::map<std::string,std::string>::iterator m_it;
	m_it = record.find(cn);
	if (m_it == record.end())
	{
		return 0;
	}
	return 1;
}

long OdbcDataMap::getLong(const char* columnName)
{
	return 0;
}


double OdbcDataMap::getDouble(const char *columnName)
{
	return 0.0;
}

tm OdbcDataMap::getTimestamp(const char* columnName)
{
  tm t;
   return t;
}

TIME_STRUCT OdbcDataMap::getTime(const char *columnName)
{

	TIME_STRUCT time;
	return time;

}

DATE_STRUCT OdbcDataMap::getDate(const char *columnName)
{
	DATE_STRUCT date;
	return date;
}
