#pragma once
#include "LogLayout.h"
#include "logProperties.h"
#include "LogDestination.h"
#include <string>
class myLog;
class Appender
{
public:
	using LogProirity = LogProperties::LogProirity;
	using LogLayoutPre = LogProperties::LogLayoutPre;
	using LogAppenderDest = LogProperties::LogAppenderDest;
	friend class myLog;
public:
	Appender();
	explicit Appender(LogProperties & logProp);
	void setLogProp(LogProperties & logProp);
	LogProperties &getLogProperties();
	bool log(const LogInfomations &logInfo);
	~Appender();
private:
	void setLogProp();
	LogProperties logProperties;
	LogDestination *logDest = nullptr;
	LogLayout *logLayout = nullptr;
	LogProirity logProirity = LogProirity::logDEBUG;
	bool iniFinished = false;
	void destructPtr()
	{
		if (logDest != nullptr)
		{
			delete logDest;
		}
		if (logLayout != nullptr)
		{
			delete logLayout;
		}
	}
};


