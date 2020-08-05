#pragma once

//Log.h
// store log message


#include <fstream>
#include <string>
#include <Windows.h>




class Logger
{
public:
	static Logger* get();
	void init(bool debug, bool runprint, bool runlog);
	void release();
	void log(const std::string);
	void print(const std::string);

protected:
	Logger();
	~Logger();

	static Logger* _instance;
	std::fstream logfile;
	HANDLE handle;

	bool debug;
	bool runprint;
	bool runlog;
};