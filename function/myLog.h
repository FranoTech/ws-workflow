#ifndef __MYLOG_H__
#define __MYLOG_H__

#include <string>
#include <iostream>
#include <fstream>
#include <sys/time.h>

#endif

enum LogLevel {logERROR, logWARNING, logINFO, logDEBUG};

inline std::string NowTime();

class Log {
	public:
		Log();
		virtual ~Log();
		std::ofstream& Get(LogLevel level = logINFO);
		static std::string ToString(LogLevel level);
	
	private:
		bool enabled;
		std::ofstream out;
};

inline Log::Log()
{
	out.open("test", std::ios::out | std::ios::app);
}

inline std::ofstream& Log::Get(LogLevel level)
{	
	
    out << "- " << NowTime();
    out << " " << ToString(level) << ": ";
    out << "\t";
    return out;
}

inline Log::~Log()
{
    out.close();
}

inline std::string Log::ToString(LogLevel level)
{
	static const char* const buffer[] = {"ERROR", "WARNING", "INFO", "DEBUG"};
    return buffer[level];
}

#define Log(level) Log().Get(level)

inline std::string NowTime()
{
    char buffer[11];
    time_t t;
    time(&t);
    tm r = {0};
    strftime(buffer, sizeof(buffer), "%X", localtime_r(&t, &r));
    struct timeval tv;
    gettimeofday(&tv, 0);
    char result[100] = {0};
    std::sprintf(result, "%s.%03ld", buffer, (long)tv.tv_usec / 1000); 
    return result;
}
