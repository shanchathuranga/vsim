#ifndef _Logger_
#define _Logger_
#include <iostream>
#include <fstream>
#include <sstream>

class Logger
{
public:
	Logger();
	~Logger();
	void info(const char* module, const char* message);
	void warning(const char* module, const char* message);
	void error(const char* module, const char* message);

private:
	void logTime();
	std::ofstream m_logfile;
};

Logger& logger();

#endif