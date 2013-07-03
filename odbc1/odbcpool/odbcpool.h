#ifndef _ODBC_POOL
#define _ODBC_POOL


#include "odbc.h"
#include "odbconnect.h"
#include <pthread.h>
#include <iostream>
#include <deque>
#include "odbcconf.h"

#ifdef WIN32
#include <Windows.h>
#endif


#pragma comment(lib, "pthreadVC2.lib")


class DBCPool
{
public:
    DBCPool(const char* configFile);
	DBConnection* getConnection();
	int LoadConfigFile(const char* configFile);
	int getSize();
    ~DBCPool();
private:

	std::deque<DBConnection*>  conns;
	int m_curAmount;
	int m_maxAmount;
	int m_idleAmount;
	odbcConf* m_config;
	pthread_mutex_t m_mutex;
	
	
	void initDBCPool();
	void TerminateConnection();
	int DestoryConnection();
	DBConnection* createConnection();
	void retrieveConnection(DBConnection* conn);
};

#endif