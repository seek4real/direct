#pragma once

//Log.h
// store log message


#include <fstream>
#include <string>





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

	bool debug;
	bool runprint;
	bool runlog;
};