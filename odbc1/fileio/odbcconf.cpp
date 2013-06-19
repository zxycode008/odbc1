#include "odbcconf.h"
#include <iostream>
#include <string>



odbcConf::odbcConf(const char* fileName)
{
}

odbcConf::~odbcConf()
{

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
   fclose(file);
   std::ifstream fs(this->m_onfig_file);
   if (NULL != m_config_head)
   {

	   while (NULL != m_config_head->next)
	   {
		   configNode* _tmpNode = m_config_head;
		   m_config_head = m_config_head->next;
		   free(_tmpNode);

	   }
   }
   //是否到达文件尾部
   std::string str_tmp;
   while (fs.eof())
   { 
	   std::getline(fs,str_tmp);
	 

   }
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

