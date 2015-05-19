#include "Logger.h"
#include <stdio.h>
#include <wtypes.h>

#pragma warning(disable:4996)

Logger::Logger()
{
	SYSTEMTIME systime;
	GetLocalTime(&systime);

	char name[256];
	sprintf(name, "F:\\log_%02i_%02i_%02i_%02i_%02i_%02i.txt", systime.wYear, systime.wMonth, systime.wDay, systime.wHour, systime.wMinute, systime.wSecond);
	m_logfile.open(name);
}
Logger::~Logger()
{
	m_logfile.flush();
	m_logfile.close();
}
void Logger::info(const char* module, const char* message)
{
	logTime();
	m_logfile << " == INF == ";
	m_logfile << "(" << module << ") " << message;
	m_logfile << "\n";
}
void Logger::warning(const char* module, const char* message)
{
	logTime();
	m_logfile << " == WRN == ";
	m_logfile << "(" << module << ") " << message;
	m_logfile << "\n";
}
void Logger::error(const char* module, const char* message)
{
	logTime();
	m_logfile << " == ERR == ";
	m_logfile << "(" << module << ") " << message;
	m_logfile << "\n";
}

void Logger::logTime()
{
	SYSTEMTIME t;
	GetLocalTime(&t);
	char name[256];
	sprintf(name, "%02i-%02i-%02i %02i:%02i:%02i", t.wYear, t.wMonth, t.wDay, t.wHour, t.wMinute, t.wSecond);
	m_logfile << name;
}

static Logger log_instance;

Logger& logger()
{
	return log_instance;
}