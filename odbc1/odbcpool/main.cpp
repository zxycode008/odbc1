#include <iostream>
#include "odbconnect.h"
#include "odbcdata.h"
#include "odbc.h"

void main()
{
	odbcConf* oc = new odbcConf("config.txt");
	oc->configRead();
	DBConnect::connect_option co;
	co.connection_autocommt = SQL_AUTOCOMMIT_OFF;
	co.connection_timeout = 10000;
	co.login_timeout = 10000;
	DBConnect::stmt_option so;
	so.async_enable = SQL_ASYNC_ENABLE_OFF;
	so.cusor_type = SQL_CURSOR_FORWARD_ONLY;
	so.query_timeout = 10000;
	DBConnect* dbc = new DBConnect(oc->getConnStr().c_str(), so,co);
	//std::cout<<dbc->checkConnectionState()<<std::endl;
	OdbcDataMap* dm = new OdbcDataMap();
    dbc->executeQuery("select * from t1",dm);
	dbc->close();
	delete(oc);
	delete(dbc);
	while (dm->hasNext())
	{
		std::cout<<dm->getString("name")<<" "<<dm->getString("birthday")<<std::endl;
		dm->next();
	}
	delete(dm);
	system("pause");
}