#include "myutil.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main(){

	string ss("helko world");
	const string &s2 = ss;
	wstring ws = s2ws(s2);
	wcout<<ws<<ws.size()<<endl;
	const char* t1 = "test=bland!";
	char* token = "=";
	vector<string> string_arr=splitString(t1,token);
    for(int i=0;i<string_arr.size();i++)
	{
       cout<<string_arr[i]<<endl;
	}
	system("pause");

}