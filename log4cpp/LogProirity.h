#pragma once
#include "logProperties.h"
#include <string>
class LogProirity
{
public:
	using LogProirityEnum = LogProperties::LogProirity;
public:
	LogProirity();
	~LogProirity();
	virtual std::string toString();
	bool ifLogMessage(LogProirityEnum toLogProi);
private:
	LogProirityEnum logProi = LogProirityEnum::logDEBUG;
};

class LogERROR : LogProirity
{
public:
	LogERROR();
	~LogERROR();
	virtual std::string toString();
};

class LogWARN : LogProirity
{
public:
	LogWARN();
	~LogWARN();
	virtual std::string toString();
};

class LogINFO : LogProirity
{
public:
	LogINFO();
	~LogINFO();
	virtual std::string toString();
};

class LogDEBUG : LogProirity
{
public:
	LogDEBUG();
	~LogDEBUG();
	virtual std::string toString();
};




