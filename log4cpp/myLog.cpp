#include "stdafx.h"
#include "myLog.h"


myLog::myLog()
{
}

myLog::myLog(const std::initializer_list<Appender>& il) : logAppenders(il)
{
}

void myLog::addAppender()
{
	logAppenders.push_back(Appender());
}

bool myLog::logIDEBUG(const std::string & FILE, const std::string & FUNCTION, const unsigned long long LINE, const DateTime & dt, const LogProperties::LogProirity logProi, const std::string & message)
{
	auto milli = iniTime.diffInMilliSec(dt);
	LogInfomations logInfo =
	{
		dt,
		FILE,
		LINE,
		message,
		FUNCTION,
		logProi,
		milli,
		"this"
	};
	for (auto p = logAppenders.begin(); p != logAppenders.end(); ++p)
	{
		if (logProi <= p->logProperties.logProirity)
		{
			if (!p->log(logInfo))
			{
				return false;
			}
		}
	}
	return true;
}


myLog::~myLog()
{
}

DateTime & getTime()
{
	static DateTime dt;
	dt.mark();
	return dt;
	// TODO: 在此处插入 return 语句
}
