#ifndef _ODBC_POOL
#define _ODBC_POOL


#include <Windows.h>
#include <pthread.h>
#include <iostream>
//��������ODBC API�Ķ���
#include <sql.h>
//������չODBC �Ķ���
#include <sqlext.h>
#include <sqltypes.h>
#include "odbcconf.h"

#ifndef DLL_API_EXPORT extern _declspec (dllexport)
#define DLL_API_EXPORT extern _declspec (dllexport)
#endif

#ifndef MUTEX
#define MUTEX pthread_mutex_t;
#endif

class DBCPool
{
private:
	static DBCPool* connPool;
	int m_curAmount;
	int m_maxAmount;
	int m_idleAmount;
	odbcConf m_config;
	MUTEX m_mutex;
	DBCPool();
	~DBCPool();
	void TerminateConnection();
};

#endif