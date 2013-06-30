#include <Windows.h>
//��������ODBC API�Ķ���
#include <sql.h>
//������չODBC �Ķ���
#include <sqlext.h>
#include <sqltypes.h>
#include <stdio.h>
#include <iostream>
#include <Locale.h>



#pragma comment(lib,"odbc32.lib")

#define LOGIN_TIMEOUT 30;
#define MAXBUFFLEN 255;

//�������
SQLHENV env = NULL;
//���ݿ����Ӿ��
SQLHDBC dbc = NULL;
//�����
SQLHSTMT stmt = NULL;
//����ֵ
SQLRETURN result = NULL;

typedef struct dBInfo{
  
	 SQLWCHAR* dns;
	 SQLWCHAR* inet;
	int port;
	 SQLWCHAR* user;
	 SQLWCHAR* password;
	 SQLWCHAR* db_name;
}MyDBInfo;

typedef struct dBError{

	SQLSMALLINT recNum;
	SQLWCHAR sqlstate[10] ;
	SQLINTEGER  nativeErrorPtr;
	SQLWCHAR MessageText[200];
	SQLSMALLINT BufferLength;
	SQLSMALLINT TextLengthPtr;

}MyDBError;

MyDBError error;

//��������Ϣ
void getDiag(SQLSMALLINT handType,SQLHANDLE handle,MyDBError* rev){
   

	SQLSMALLINT recNum=1;
	SQLWCHAR sqlstate[10] ;
	SQLINTEGER  nativeErrorPtr;
	SQLWCHAR MessageText[200];
	SQLSMALLINT BufferLength =100;
	SQLSMALLINT TextLengthPtr;
  
   SQLGetDiagRec(handType,handle,recNum,sqlstate,&nativeErrorPtr,MessageText,BufferLength,&TextLengthPtr);
   wprintf(L"line:(%d) %s \n",nativeErrorPtr,MessageText);	
   
}

void showDBConError(){
   getDiag(SQL_HANDLE_DBC,dbc,&error);
}

void showDBError(){
	getDiag(SQL_HANDLE_STMT,stmt,&error);
}





void init(MyDBInfo* dbinfo){

	dbinfo->db_name = L"test";
	dbinfo->dns = L"mysql1";
	dbinfo->inet = L"localhost";
	dbinfo->port = 3306;
	dbinfo->user = L"root";
	dbinfo->password = L"root";

	//���价�����
	result = SQLAllocHandle(SQL_HANDLE_ENV,NULL,&env);
	//���û����������
	result = SQLSetEnvAttr(env,SQL_ATTR_ODBC_VERSION,(SQLPOINTER)SQL_OV_ODBC3,SQL_IS_INTEGER);

	//�������Ӿ��
	result = SQLAllocHandle(SQL_HANDLE_DBC,env,&dbc);

    //StringLength���������������������������ΪSQL_IS_INTEGER,���ַ������Ȼ���SQL_NTS
	result = SQLSetConnectAttr(dbc,SQL_LOGIN_TIMEOUT,(void*)30, 0);
	result = SQLSetConnectAttr(dbc,SQL_ATTR_AUTOCOMMIT,SQL_AUTOCOMMIT_OFF, 0);

	
    //
	result = SQLConnect(dbc,dbinfo->dns,SQL_NTS,dbinfo->user,SQL_NTS,dbinfo->password,SQL_NTS);

	if (SQL_ERROR == result)
	{
		showDBConError();
	}
	
}

//�������ݿ��ѯ
int close(){

	SQLFreeHandle(SQL_HANDLE_STMT,stmt);
	SQLDisconnect(dbc);
	SQLFreeHandle(SQL_HANDLE_DBC,dbc);
	SQLFreeHandle(SQL_HANDLE_ENV,env);
	return 0;	
}

int main(){

  MyDBInfo dbinfo;
  //���ñ������Ի���,�����ֹ����ת��ʱ����
  setlocale(LC_ALL, "chs");

  init(&dbinfo);

  //���������
  result = SQLAllocHandle(SQL_HANDLE_STMT,dbc,&stmt);
  result = SQLPrepare(stmt,(SQLWCHAR*)L"select * from t1",SQL_NTS);
  //����Ƿ��д�
  showDBError();
  result = SQLExecute(stmt);
  SQLWCHAR cn[255];
  short len1;
  short datatype;
  SQLUINTEGER size;
  int closed;
  result = SQLGetConnectAttr(dbc,SQL_ATTR_CONNECTION_DEAD,(SQLPOINTER)&closed, SQL_IS_INTEGER,0);
  SQLDescribeCol(stmt,4,cn, 255,&len1, &datatype,&size,NULL,NULL);
  //ʰȡ����
  while (SQLFetch(stmt) != SQL_NO_DATA_FOUND)
  {
	  SQLWCHAR name[32];
	  SQLINTEGER len;
	  SQLGetData(stmt,2,SQL_C_WCHAR,name,32,&len);
	  wprintf(L"name = %s ", name);
	  memset(name,'\0',sizeof(name));
	  SQLGetData(stmt,4,SQL_C_WCHAR,name,32,&len);
	  wprintf(L"name = %s \n", name);
  }
  //COMMIT ���� ROLLBACK
  SQLEndTran(SQL_HANDLE_DBC,dbc,SQL_COMMIT);
  SQLFreeHandle(SQL_HANDLE_STMT,stmt);
  close();

  system("pause");
  return 0;
}