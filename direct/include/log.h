#pragma once

//Log.h
// store log message


#include <fstream>
#include <string>



namespace direct
{

class _declspec(dllexport) Logger
{
public:
	static Logger* get();
	void init(bool debug, bool runprint, bool runlog);
	void release();
	void log(const std::string);
	void print(const std::string);

private:
	Logger();
	~Logger();

	std::fstream* logfile;

	bool debug;
	bool runprint;
	bool runlog;
};

#ifndef _LOGGER_H_
#define _LOGGER_H_
#define console(s) Logger::get()->log(s)
#endif // !_LOGGER_H_

}
