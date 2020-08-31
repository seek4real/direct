// Log.cpp

#include <windows.h>
#include "../include/log.h"

#ifndef _LOG_FILE_NAME_
#define _LOG_FILE_NAME_ 0
const std::string LOG_FILE_NAME = "debuglog.txt";
#endif // !_LOG_FILE_NAME_

using std::fstream;
using direct::Logger;


HANDLE handle;

Logger::Logger():debug(true), runprint(true), runlog(true)
{
	if (runlog) {
		logfile = new fstream;
		this->init(debug, runprint, runlog);
	}
}

Logger::~Logger()
{
	if (runlog && logfile) {
		logfile->close();
		delete logfile;
		logfile = nullptr;
	}
}

void Logger::init(bool _debug, bool _print, bool _runlog)
{
	debug = _debug;
	runprint = _print;
	runlog = _runlog;
	if (debug) {
		if (runlog) {
			logfile->open(LOG_FILE_NAME, std::ios::out | std::ios::trunc);
		}

		if (runprint) {
			BOOL r = AllocConsole();
			if (r)
				handle = GetStdHandle(STD_OUTPUT_HANDLE);
		}
	}
}

void Logger::release()
{
	if (debug) {
		if (runlog && logfile->is_open()) {
			(*logfile) << "logfile release!" << std::endl;
			(*logfile) << "log file " << LOG_FILE_NAME << " closed." << std::endl;
			logfile->close();
		}

		if (runprint) {
			FreeConsole();
		}
	}
}


void Logger::log(const std::string s)
{
	//using namespace std;
	if (!debug)
		return;

	if (logfile->is_open())
		(*logfile) << "[LOG]" << s << std::endl;
	
}

void Logger::print(const std::string s)
{
	if (!debug)
		return;

	const std::string _s = s + "\n";
	unsigned long len;
	WriteConsole(handle, _s.c_str(), strlen(_s.c_str()), &len, NULL);
}


//以下是错误的c++单例实现，new生成的对象无法delete
//Logger* Logger::get()
//{
//	if (_instance == nullptr) {
//		_instance = new Logger();
//	}
//	return _instance;
//}

//正确的单例模式，直接使用静态变量
Logger* Logger::get()
{
	static Logger instance;
	return &instance;
}

