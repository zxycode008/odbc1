#include "odbcconf.h"
#include <iostream>
#include <string>
#include <Windows.h>
#include <iostream>
#include <string>

#pragma comment(lib,"myutil.lib")

using namespace std;

extern _declspec (dllimport) string ws2s(const wstring& ws);
extern _declspec (dllimport) wstring s2ws(const string& s);
extern _declspec (dllimport) void splitString(char* origin, const char* token,string** tg, int* size);




int main(){
	
	string ss("helko world");
	const string &s2 = ss;
	wstring ws = s2ws(s2);
	wcout<<ws<<ws.size()<<endl;
	char* t1 = "test=bland!";
    char* token = "=";
	string** string_arr = (string**)malloc(sizeof(string**));
	int* size = new int();
    splitString(t1,token,string_arr,size);
	for (int i=0; i< *size; i++)
	{
		cout<<*string_arr[i]<<endl;
	}
	system("pause");

	return 0;
}