#include "odbcconf.h"
#include <Windows.h>
#include <iostream>
#include <string>
#include <vector>



odbcConf::odbcConf(const char* fileName)
{
	m_onfig_file = fileName;
	m_config_head = NULL;
	m_conn_param._charset="";
	m_conn_param.database="";
	m_conn_param.driver="";
	m_conn_param.dsn="";
	m_conn_param.filedsn="";
	m_conn_param.pwd="";
	m_conn_param.savefile="";
	m_conn_param.server="";
	m_conn_param.uid="";
	m_conn_str = L"";


}

odbcConf::~odbcConf()
{
	deleteCofigInfo();
}

void odbcConf::deleteCofigInfo(){
	//释放配置文件结构
	if (NULL != m_config_head)
	{

		while (NULL != m_config_head->next)
		{
			configNode* _tmpNode = m_config_head;
			m_config_head = m_config_head->next;
			free(_tmpNode);

		}
		free(m_config_head);
	}
}



int odbcConf::configRead()
{

	int rec = 0;
	FILE* file = fopen(m_onfig_file,"r+");
	if (!file)
	{
		rec = NOT_FOUND_CONFIGFILE;
		return rec;
	}

	std::ifstream fs(this->m_onfig_file);
	//释放配置文件结构
	deleteCofigInfo();
	//是否到达文件尾部
	std::string str_tmp;
	while (!fs.eof())
	{ 
		std::getline(fs,str_tmp);
		if (str_tmp.find("=",0)==std::string::npos)
		{
			continue;
		}
		char* token = "=";
		const char* source = str_tmp.data();
		std::vector<std::string> v = splitString(source,token);
		if (m_config_head)
		{
			configNode* _node = new configNode();
			_node->key = v[0];
			_node->value = v[1];
			_node->next = m_config_head;
			m_config_head = _node;


		}else
		{  
			m_config_head = new configNode();
			m_config_head->key = v[0];
			m_config_head->value = v[1];
			m_config_head->next = NULL;
		}



	}
	fclose(file);
	fs.close();
	rec = parseConfig();
	if (rec==0)
	{
		m_conn_str = generateConnStr();
	}
	return rec;
}

//void odbcConf::showError()

std::wstring odbcConf::generateConnStr()
{
	std::string connStr("");
	connStr += m_conn_param.dsn;
	connStr += m_conn_param.driver;
	connStr += m_conn_param.server;
	connStr += m_conn_param.uid;
	connStr += m_conn_param.pwd;
	connStr += m_conn_param.database;
	connStr += m_conn_param._charset;
	const std::string &conStr2 = connStr;
	std::wstring wconn_Str = s2ws(conStr2);
	return wconn_Str;
}

int odbcConf::parseConfig(){
	if (!m_config_head)
	{
		return CONFIG_PARSE_ERROR;
	}
	configNode* node = m_config_head;
	if (node->key == "DRIVER")
	{
		m_conn_param.driver = "DRIVER={" + node->value + "};";
	}
	else if (node->key == "DSN")
	{
		m_conn_param.dsn = "DSN=" + node->value + ";";
	}
	else if (node->key == "SERVER")
	{
		m_conn_param.server = "SERVER=" + node->value + ";";
	}
	else if (node->key == "UID")
	{
		m_conn_param.uid = "UID="+node->value+";";
	}
	else if (node->key == "PWD")
	{
		m_conn_param.pwd = "PWD=" +node->value + ";";
	}
	else if (node->key == "DATABASE")
	{
		m_conn_param.database = "DATABASE="+node->value+";";
	}
	else if (node->key == "CharSet")
	{
		m_conn_param._charset = "CharSet="+node->value+";";
	}
	else if (node->key == "FILEDSN")
	{
		m_conn_param.filedsn = "FILEDSN={"+node->value+"};";
	}
	else if (node->key == "SAVEFILE")
	{
		m_conn_param.savefile = "SAVEFILE="+node->value+";";
	}else if (node->key == "MAXSIZE")
	{
		sscanf(node->value.c_str(),"%d",&m_conn_param.maxsize);
	}else if (node->key == "IDLESIZE")
	{
		sscanf(node->value.c_str(),"%d",&m_conn_param.idlesize);
	}else if (node->key == "AUTOCMMIT")
	{
		if (node->key == "TRUE" || node->key == "true")
		{
			m_conn_param.autocommit = true;
		}else if(node->key == "FALSE" || node->key == "false"){
			m_conn_param.autocommit = false; 
		} 
	}else if (node->key == "LOGINTIMEOUT")
	{
		sscanf(node->value.c_str(),"%lf",&m_conn_param.logintimeout);
	}else if (node->key == "CONNECTIONTIMEOUT")
	{
		sscanf(node->value.c_str(),"%lf",&m_conn_param.connectiontimeout);
	}else if (node->key == "QUERYTIMEOUT")
	{
		sscanf(node->value.c_str(),"%lf",&m_conn_param.querytimeout);
	}

	while (NULL != node->next)
	{
		node = node->next;
		if (node->key == "DRIVER")
		{
			m_conn_param.driver = "DRIVER={" + node->value + "};";
		}
		else if (node->key == "DSN")
		{
			m_conn_param.dsn = "DSN=" + node->value + ";";
		}
		else if (node->key == "SERVER")
		{
			m_conn_param.server = "SERVER=" + node->value + ";";
		}
		else if (node->key == "UID")
		{
			m_conn_param.uid = "UID="+node->value+";";
		}
		else if (node->key == "PWD")
		{
			m_conn_param.pwd = "PWD=" +node->value + ";";
		}
		else if (node->key == "DATABASE")
		{
			m_conn_param.database = "DATABASE="+node->value+";";
		}
		else if (node->key == "CharSet")
		{
			m_conn_param._charset = "CharSet="+node->value+";";
		}
		else if (node->key == "FILEDSN")
		{
			m_conn_param.filedsn = "FILEDSN={"+node->value+"};";
		}
		else if (node->key == "SAVEFILE")
		{
			m_conn_param.savefile = "SAVEFILE="+node->value+";";
		}else if (node->key == "MAXSIZE")
		{
			sscanf(node->value.c_str(),"%d",&m_conn_param.maxsize);
		}else if (node->key == "IDLESIZE")
		{
			sscanf(node->value.c_str(),"%d",&m_conn_param.idlesize);
		}else if (node->key == "AUTOCMMIT")
		{
			if (node->key == "TRUE" || node->key == "true")
			{
				m_conn_param.autocommit = true;
			}else if(node->key == "FALSE" || node->key == "false"){
				m_conn_param.autocommit = false; 
			} 
		}else if (node->key == "LOGINTIMEOUT")
		{
			sscanf(node->value.c_str(),"%lf",&m_conn_param.logintimeout);
		}else if (node->key == "CONNECTIONTIMEOUT")
		{
			sscanf(node->value.c_str(),"%lf",&m_conn_param.connectiontimeout);
		}else if (node->key == "QUERYTIMEOUT")
		{
			sscanf(node->value.c_str(),"%lf",&m_conn_param.querytimeout);
		}
	}

	return 0;

}

std::wstring odbcConf::getConnStr_W(){
	return m_conn_str;
}

std::string odbcConf::getConnStr(){
	std::wstring& connstr = m_conn_str;
	return ws2s(connstr);
}

