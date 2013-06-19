#include "odbcconf.h"
#include <iostream>
#include <string>
#include <Windows.h>
#include <string>
#include <vector>

#pragma comment(lib,"myutil.lib")

using namespace std;

extern _declspec (dllimport) string ws2s(const wstring& ws);
extern _declspec (dllimport) wstring s2ws(const string& s);
extern _declspec (dllimport) vector<string> splitString(const char* origin, const char* token);



int main(){
	
	string ss("helko world");
	const string &s2 = ss;
	wstring ws = s2ws(s2);
	wcout<<ws<<ws.size()<<endl;
	const char* t1 = "test=bland!";
    char* token = "=";   
	vector<string> v;
	v=splitString(t1,token);
	for (int i=0; i< v.size(); i++)
	{
		cout<<v[i]<<endl;
	}
    odbcConf* oc = new odbcConf("config.txt");
    oc->configRead();
    string str1 = "fucke you";
	string* str2 = new string("fucke you");
	if (str1 == *str2)
	{
		cout<<"µÈÓÚ"<<endl;
	}
	delete str2;
	system("pause");
    delete(oc);
	return 0;
}