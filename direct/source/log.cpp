// Log.cpp


#include "../include/log.h"

#ifndef _LOG_FILE_NAME_
std::string LOG_FILE_NAME = "run.log";
#define _LOG_FILE_NAME_ 0
#endif // !_LOG_FILE_NAME_

Logger* Logger::_instance = nullptr;

Logger::Logger():debug(false), runprint(false), runlog(false)
{

}

Logger::~Logger()
{
}

void Logger::init(bool _debug, bool _print, bool _runlog)
{
	debug = _debug;
	runprint = _print;
	runlog = _runlog;
	if (debug) {
		if (runlog) {
			logfile.open(LOG_FILE_NAME, std::ios::out);
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
		if (runlog) {
			logfile << "logfile release!" << std::endl;
			logfile << "log file " << LOG_FILE_NAME << " closed." << std::endl;
			logfile.close();
		}
		if (Logger::_instance != nullptr)
		{
			delete Logger::_instance;
			Logger::_instance = nullptr;
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

	if (logfile.is_open())
		logfile << "[LOG]" << s << std::endl;
	
}

void Logger::print(const std::string s)
{
	if (!debug)
		return;

	const std::string _s = s + "\n";
	unsigned long len;
	WriteConsole(handle, _s.c_str(), strlen(_s.c_str()), &len, NULL);
}

Logger* Logger::get()
{
	if (Logger::_instance == nullptr) {
		Logger::_instance = new Logger;
	}
	return Logger::_instance;
}

