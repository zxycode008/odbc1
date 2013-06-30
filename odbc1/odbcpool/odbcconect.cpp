#include "odbconnect.h"
#include <iostream>
#include <string>


DBConnect::DBConnect(const char *connstr,struct stmt_option so, struct connect_option co)
{
	std::string s = connstr;
	const std::string& s2 = s;
	std::wstring ws = s2ws(s);
	wcscpy(this->m_connStr,ws.c_str());
	if (&so == NULL || &co == NULL)
	{
		optionInit();
	}else{
		this->connSet.connection_autocommt = co.connection_autocommt;
		this->connSet.connection_timeout = co.connection_timeout;
		this->connSet.login_timeout = co.login_timeout;
		this->stmtSet.async_enable = so.async_enable;
		this->stmtSet.cusor_type = so.cusor_type;
		this->stmtSet.query_timeout = so.query_timeout;
	}
    init();
}

DBConnect::~DBConnect()
{
  close();
}

void DBConnect::optionInit()
{
	this->connSet.connection_autocommt = SQL_AUTOCOMMIT_OFF;
	this->connSet.connection_timeout = 30;
	this->connSet.login_timeout = 30;
	this->stmtSet.async_enable = SQL_ASYNC_ENABLE_OFF;
	this->stmtSet.cusor_type = SQL_CURSOR_FORWARD_ONLY;
	this->stmtSet.query_timeout = 30;
}

void DBConnect::init()
{
	optionInit();
	//分配环境句柄
	result = SQLAllocHandle(SQL_HANDLE_ENV,NULL,&env);
	//设置环境句柄属性
	result = SQLSetEnvAttr(env,SQL_ATTR_ODBC_VERSION,(SQLPOINTER)SQL_OV_ODBC3,SQL_IS_INTEGER);
	//使用ODBC连接池，每个驱动一个SQL_CP_ONE_PER_DRIVER  或者每个环境一个SQL_CP_ONE_PER_HENV   SQL_CP_OFF关闭
	//result = SQLSetEnvAttr(env,SQL_ATTR_CONNECTION_POOLING,(SQLPOINTER)SQL_CP_ONE_PER_HENV,SQL_IS_INTEGER);
	//分配链接句柄
	result = SQLAllocHandle(SQL_HANDLE_DBC,env,&dbc);
	 //StringLength参数，如果参数类型是整形设置为SQL_IS_INTEGER,是字符串长度或者SQL_NTS
	result = SQLSetConnectAttr(dbc,SQL_LOGIN_TIMEOUT,(void*)this->connSet.login_timeout, SQL_IS_INTEGER);
	result = SQLSetConnectAttr(dbc,SQL_ATTR_CONNECTION_TIMEOUT,(void*)this->connSet.connection_timeout, SQL_IS_INTEGER);
	result = SQLSetConnectAttr(dbc,SQL_ATTR_AUTOCOMMIT,this->connSet.connection_autocommt, SQL_IS_INTEGER);
    SQLSMALLINT outputlength;
	result = SQLDriverConnect(dbc,NULL,m_connStr,SQL_NTS,m_connStrOut,255,&outputlength,SQL_DRIVER_NOPROMPT);
	//result = SQLConnect(dbc,L"mysql1",SQL_NTS,L"root",SQL_NTS,L"root",SQL_NTS);
	LogUtil* log = LogUtil::getlog();
	std::wstring woutput_info = m_connStrOut;
	std::wstring& _woutput_info = woutput_info;
	std::string output_info = ws2s(_woutput_info);
	log->log(LogUtil::L_INFO,output_info.c_str(),DEBUG_TRACE_FILE_LINE_INFO);
    //result = SQLAllocHandle(SQL_HANDLE_STMT,this->dbc,&stmt);
	//result = SQLExecDirect(stmt,(SQLWCHAR*)L"select * from t1",SQL_NTS);
  
	if (SQL_ERROR == result)
	{
		showDBCError(dbc);
	}
	


}

void DBConnect::showDBCError(SQLHDBC hdbc)
{
   showDBError(SQL_HANDLE_DBC,hdbc);
}

void DBConnect::showDBError(SQLSMALLINT type, SQLHANDLE sqlHandle)
{
	SQLWCHAR pstatus[10],pmsg[101];
	SQLINTEGER sqlerr;
	SQLSMALLINT sqlmsglen;
    
	long erg = SQLGetDiagRec(type,sqlHandle,1,pstatus,&sqlerr,pmsg,100,&sqlmsglen);
	LogUtil* log = LogUtil::getlog();
	std::wstring wsmsg = pmsg;
	std::wstring& _wsmsg = wsmsg;
	std::string msg = ws2s(_wsmsg);
	log->log(LogUtil::L_INFO,msg.c_str(),DEBUG_TRACE_FILE_LINE_INFO);

}

void DBConnect::showDBSError(SQLHSTMT hstmt)
{
    showDBError(SQL_HANDLE_STMT,hstmt);
}

void DBConnect::close()
{

	//SQLFreeHandle(SQL_HANDLE_STMT,stmt);
	SQLDisconnect(dbc);
	SQLFreeHandle(SQL_HANDLE_DBC,dbc);
	SQLFreeHandle(SQL_HANDLE_ENV,env);
		
}


void DBConnect::executeQuery(const char* sql, OdbcDataMap* dm)
{
	
	SQLHSTMT hstmt = NULL;
	result = SQLAllocHandle(SQL_HANDLE_STMT,this->dbc,&hstmt);
	std::string sqlstr = sql;
	std::string& sqlstr2 = sqlstr;
	std::wstring wsql =  s2ws(sqlstr2);
	//int closed;
	//SQLINTEGER length;
	//result = SQLGetConnectAttr(dbc,SQL_ATTR_CONNECTION_DEAD,(SQLPOINTER)&closed,SQL_IS_UINTEGER,&length);
	//if (result == SQL_SUCCESS)
	//{
	//	LogUtil* log = LogUtil::getlog();
	//	log->log(LogUtil::L_DEBUG,"success!",DEBUG_TRACE_FILE_LINE_INFO);
	//}
	result = SQLExecDirect(hstmt,(SQLWCHAR*)L"select * from t1",SQL_NTS);
	SQLHSTMT& _hstmt = hstmt;
	dm->init(hstmt);
}

void DBConnect::executeUpdate(const char* sql)
{

}

SQLHSTMT& DBConnect::getStatement(){
	
	SQLHSTMT& _st = this->stmt;
	return _st;
}

int DBConnect::checkConnectionState(){
	int closed;
	SQLGetConnectAttr(dbc,SQL_ATTR_CONNECTION_DEAD,(SQLPOINTER)&closed, SQL_IS_INTEGER,0);
	return closed;
}