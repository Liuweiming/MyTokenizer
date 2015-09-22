#pragma once
#include <string>
#include <vector>
#include <functional>
#include "Appender.h"
#include "LogLayout.h"
#include "LogProirity.h"
#include "../DateAndTime/DateTime.h"
#include "../Spliter/Spliter.h"

class myLog
{
public:
	myLog();
	myLog(const std::initializer_list<Appender> &il);
	void addAppender();
	bool logIDEBUG(const std::string &FILE, const std::string &FUNCTION, const unsigned long long LINE, const DateTime &dt, const LogProperties::LogProirity logProi, const std::string &message);
	~myLog();
public:
	std::vector<Appender> logAppenders{ Appender() };
private:
	DateTime iniTime;
};

DateTime &getTime();