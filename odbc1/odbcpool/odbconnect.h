#ifndef _ODBC_CONNECT
#define _ODBC_CONNECT

#include "odbc.h"
//包含基本ODBC API的定义
#include <sql.h>
//包含扩展ODBC 的定义
#include <sqlext.h>
#include <sqltypes.h>
#include "odbcconf.h"
#include "logutil.h"
#include "odbcdata.h"




//检查错误
#define CHECKSTMTERROR(result,stmt) if (SQL_ERROR==result){showDBSError(stmt);}

class DBConnection
{
	

public:

	typedef struct {
		//连接属性
		//SQL_AUTOCOMMIT_OFF SQL_AUTOCOMMIT_ON
		unsigned long connection_autocommt;
		int login_timeout;
		int connection_timeout;
	}connect_option;

	typedef struct{

		//SQL_ASYNC_ENABLE_OFF ON
		int async_enable;
		int query_timeout;
		//SQL_CURSOR_DYNAMIC SQL_CURSOR_FORWARD_ONLY SQL_CURSOR_STATIC SQL_CURSOR_KEYSET_DRIVEN
		int cusor_type;


	}stmt_option;

	DBConnection(const char* connstr, struct stmt_option so, struct connect_option co);
	~DBConnection();

	SQLHENV env;
	//数据库连接句柄
	SQLHDBC dbc;
	//语句句柄
	SQLHSTMT stmt;
	//返回值
	SQLRETURN result;


    
    int checkConnectionState();
	void showDBError(SQLSMALLINT type,SQLHANDLE sqlHandle);
	void showDBCError(SQLHDBC hdbc);
	void showDBSError(SQLHSTMT hstmt);
	void executeQuery(const char* sql, OdbcDataMap* dm);
	void executeUpdate(const char* sql);
	void endTransction();
	SQLHSTMT& getStatement();
	void close();
	bool isIdle();
	void free();
	bool canbeUsed();

private:


	SQLWCHAR m_connStr[255];
	SQLWCHAR m_connStrOut[255];
	stmt_option stmtSet;
	connect_option connSet;
	bool _idle;
	bool enable;




	void optionInit();
	void init();

};

#endif