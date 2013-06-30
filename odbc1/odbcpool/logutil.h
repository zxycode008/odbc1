#ifndef _LOGUTIL_
#define  _LOGUTIL_

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#ifndef _LOGUTIL_TRACE
#define _LOGUTIL_TRACE
#define DEBUG_TRACE_FILE_LINE_INFO __FILE__,__LINE__
#define RELEASE_NO_TRACE NULL,0
#endif

#ifndef _MYUTIL
#define _MYUTIL

#pragma comment(lib,"myutil.lib")
std::string ws2s(const std::wstring& ws);
std::wstring s2ws(const std::string& s);
std::vector<std::string> splitString(const char* origin, const char* token);
std::string replaceAll(const char* src, const char* t, const char* _repstr);

#endif



class _declspec(dllexport) LogUtil{


private:


	bool toConsole;
	const char* m_fname;
	static LogUtil* m_loginstance;
	LogUtil();
	~LogUtil();

	typedef struct  
	{

		std::string appenderToConsole;
		int auto_linefeed;
		int fileMaxSize;
		std::string dataformat;
		std::string outputfile;


	}logconfig;
	logconfig config;


	int loadConfig();
	void init();

public:

	static const int L_ERROR = 1;
	static const int L_DEBUG = 2;
	static const int L_FATEL = 3;
	static const int L_INFO = 0;

	static LogUtil* getlog();

	void log(int log_lv, const char* msg,const char* fn, int line);
	void setOutToConsole(bool allowed);



};


#endif


