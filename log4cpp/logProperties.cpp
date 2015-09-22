#include "stdafx.h"
#include "logProperties.h"


LogProperties::LogProperties()
{
}

LogProperties::LogProperties(LogProirity logPro, LogAppenderDest logDest, LogLayoutPre logLay) : logProirity(logPro), logDestination(logDest), logLayout(logLay)
{
}

void LogProperties::customizeFileDest(const std::string & cust)
{
	customizedFileDest = cust;
	logDestination = FileDest;
}

void LogProperties::customizePatten(const std::string & cust)
{
	customizedPatten = cust;
	logLayout = PattenLayout;
}

void LogProperties::customizeStream(std::iostream & ostr)
{
	customizedStreamDest = &ostr;
}



LogProperties::LogProperties(LogProirity logPro, LogAppenderDest logDest, LogLayoutPre logLay, std::ostream & ostr) : logProirity(logPro), logDestination(logDest), logLayout(logLay), customizedStreamDest(&ostr)
{
}


LogProperties::~LogProperties()
{
}
