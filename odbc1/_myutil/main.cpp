#include "myutil.h"

using namespace std;

int main(){

	string ss("helko world");
	const string &s2 = ss;
	wstring ws = s2ws(s2);
	wcout<<ws<<ws.size()<<endl;
	system("pause");

}