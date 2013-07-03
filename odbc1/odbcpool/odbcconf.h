#ifndef _ODBC_CONF
#define _ODBC_CONF

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "odbc.h"


static const int NOT_FOUND_CONFIGFILE = 1;
static const int NO_PROLEM = 0;
static const int CONFIG_PARSE_ERROR = 2;
static const int PARSE_CONFIG_ERROR = 3;
static const int MAXBUFFLE = 255;

class odbcConf
{
public:
	typedef struct conn_param
	{
		std::string driver;
		std::string dsn;
		std::string filedsn;
		std::string uid;
		std::string pwd;
		std::string savefile;
		std::string server;
		std::string database;
		std::string _charset;
		int maxsize;
		int idlesize;
		bool autocommit;
		double logintimeout;
		double connectiontimeout;
		double querytimeout;
	};

    conn_param m_conn_param;

	odbcConf(const char* fileName);
	~odbcConf();
	int configRead();
	//void showError();
	std::wstring getConnStr_W();
	std::string getConnStr();
	

private:
	

	std::wstring generateConnStr();

	void deleteCofigInfo();

	int parseConfig();

	typedef struct configNode
	{
		std::string key;
		std::string value;
		configNode* next;
	};


	const char* m_onfig_file;
	configNode* m_config_head;
	std::wstring m_conn_str;

};

#endif