#ifndef _ODBC_CONF
#define _ODBC_CONF

#include <iostream>
#include <fstream>
#include <string>

#pragma comment(lib,"myutil.lib")

extern _declspec (dllimport) std::string ws2s(const std::wstring& ws);
extern _declspec (dllimport) std::wstring s2ws(const std::string& s);

static const int NOT_FOUND_CONFIGFILE = 1;
static const int CONFIG_NO_ERROR = 0;
static const int CONFIG_PARSE_ERROR = 2;
static const int MAXBUFFLE = 255;

class odbcConf
{
public:

	odbcConf(const char* fileName);
	~odbcConf();
	int configRead();
	void showError();

private:
	char* m_onfig_file;

	std::wstring generateConnStr();

	typedef struct configNode
	{
         char* key;
		 char* value;
		 configNode* next;
	};
	
	typedef struct conn_param
	{
		std::wstring driver;
		std::wstring dsn;
		std::wstring filedsn;
		std::wstring uid;
		std::wstring pwd;
		std::wstring savefile;
		std::wstring server;
		std::wstring database;
		std::wstring _charset;
	};
	conn_param m_conn_param;
	configNode* m_config_head;

};

#endif