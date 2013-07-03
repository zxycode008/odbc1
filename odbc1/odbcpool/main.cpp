#include <iostream>
#include "odbconnect.h"
#include "odbcdata.h"
#include "odbc.h"
#include <Psapi.h>
#include "odbcpool.h"

void main()
{
	odbcConf* oc = new odbcConf("config.txt");
	oc->configRead();
	DBConnection::connect_option co;
	co.connection_autocommt = SQL_AUTOCOMMIT_OFF;
	co.connection_timeout = 10000;
	co.login_timeout = 10000;
	DBConnection::stmt_option so;
	so.async_enable = SQL_ASYNC_ENABLE_OFF;
	so.cusor_type = SQL_CURSOR_FORWARD_ONLY;
	so.query_timeout = 10000;
	DBConnection* dbc = new DBConnection(oc->getConnStr().c_str(), so,co);
	//std::cout<<dbc->checkConnectionState()<<std::endl;
	OdbcDataMap* dm = new OdbcDataMap();
    dbc->executeQuery("select * from t1",dm);
	dbc->close();
	delete(oc);
	delete(dbc);
	while (dm->hasNext())
	{
		std::cout<<dm->getString("name")<<" "<<dm->getString("birthday")<<std::endl;
		TIME_STRUCT time = dm->getTime("birthday");
		DATE_STRUCT date = dm->getDate("birthday");
        int age = dm->getInt("age");
		std::string name = dm->getString("name");
		dm->next();
	}
	delete(dm);
	DBCPool* pool = new DBCPool("config.txt");
	DBConnection* c = pool->getConnection();
	OdbcDataMap* dm2 = new OdbcDataMap();
	c->executeQuery("select * from t2",dm2);
	c->close();
	while (dm2->hasNext())
	{
		std::cout<<dm2->getString("name")<<" "<<dm2->getString("tdate")<<std::endl;
		dm2->next();
	}
	
	system("pause");
}
