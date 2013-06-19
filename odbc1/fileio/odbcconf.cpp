#include "odbcconf.h"
#include <Windows.h>
#include <iostream>
#include <string>
#include <vector>



odbcConf::odbcConf(const char* fileName)
{
	m_onfig_file = fileName;
	m_config_head = NULL;

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
   return rec;
}

void odbcConf::showError(){

}

std::wstring odbcConf::generateConnStr()
{
	std::wstring connStr(L"");
	connStr += m_conn_param.driver;
	connStr += m_conn_param.server;
	connStr += m_conn_param.uid;
	connStr += m_conn_param.pwd;
	connStr += m_conn_param.database;
	connStr += m_conn_param._charset;

	return connStr;
}

