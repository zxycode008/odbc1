#include "odbcpool.h"

DBCPool::DBCPool(const char* configFile)
{
	pthread_mutex_init(&m_mutex,NULL);
	this->m_config = new odbcConf("config.txt");
    initDBCPool();
}

DBCPool::~DBCPool()
{
   pthread_mutex_destroy(&m_mutex);
}





void DBCPool::initDBCPool()
{
	LogUtil* log = LogUtil::getlog();
	int res = m_config->configRead();
	if (res != 0)
	{  
		log->log(LogUtil::L_ERROR,"odbcpool initial error configfile not found!",DEBUG_TRACE_FILE_LINE_INFO);
	}
	this->m_curAmount = 0;
	this->m_idleAmount = m_config->m_conn_param.idlesize;
	this->m_maxAmount = m_config->m_conn_param.maxsize;

	pthread_mutex_lock(&m_mutex);
	if (this->m_curAmount >=0 && this->m_curAmount <= m_idleAmount)
	{
		int count = m_idleAmount - m_curAmount;
		for (int i = 0; i<count; i++)
		{
			
			DBConnection* conn = createConnection();
			if (conn != NULL)
			{
                conns.push_back(conn);
				m_curAmount++;
			}			
		}
	}
	pthread_mutex_unlock(&m_mutex);

}


DBConnection* DBCPool::createConnection()
{
	LogUtil* log = LogUtil::getlog();
	DBConnection* conn = NULL;
	DBConnection::connect_option co;
	int res = 0;
	if (m_config->m_conn_param.autocommit = true)
	{
		co.connection_autocommt = SQL_AUTOCOMMIT_ON;
	}else{
		co.connection_autocommt = SQL_AUTOCOMMIT_OFF;
	}

	co.connection_timeout = m_config->m_conn_param.connectiontimeout;
	co.login_timeout = m_config->m_conn_param.logintimeout;
	DBConnection::stmt_option so;
	so.async_enable = SQL_ASYNC_ENABLE_OFF;
	so.cusor_type = SQL_CURSOR_FORWARD_ONLY;
	so.query_timeout = m_config->m_conn_param.querytimeout;
	conn  = new DBConnection(m_config->getConnStr().c_str(),so,co);
	res = conn->checkConnectionState();
	if (res != SQL_SUCCESS && res !=SQL_SUCCESS_WITH_INFO)
	{
		log->log(LogUtil::L_ERROR,"pool connect to db failed! ",DEBUG_TRACE_FILE_LINE_INFO);
	}
	return conn;
}

DBConnection*  DBCPool::getConnection()
{
	DBConnection* conn = NULL;
	pthread_mutex_lock(&m_mutex);
	if (conns.size() > 0)
	{
		
		while (conns.front()!=NULL)
		{
			conn = conns.front();
			conns.pop_front();
			m_curAmount--;
			if (conn->checkConnectionState() != SQL_SUCCESS)
			{
				if (conn != NULL)
				{
					delete(conn);
				}
			}else{
				break;
			}
			
		}
		
	}else
	{
		for (int i =0; i<m_idleAmount; i++)
		{
             conn = createConnection();
			 if (conn->checkConnectionState() == SQL_SUCCESS)
			 {
				 conns.push_back(conn);
			 }		 
		}
		conn = conns.front();
		conns.pop_front();
	}
	pthread_mutex_unlock(&m_mutex);
	return conn;
}

void DBCPool::retrieveConnection(DBConnection* conn)
{
	pthread_mutex_lock(&m_mutex);
	conns.push_back(conn);
	pthread_mutex_unlock(&m_mutex);
}

void DBCPool::TerminateConnection()
{

}

int DBCPool::DestoryConnection()
{
  return 0;
}

int DBCPool::getSize(){
	return m_curAmount;
}