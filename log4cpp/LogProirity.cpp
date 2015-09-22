#include "stdafx.h"
#include "LogProirity.h"


LogProirity::LogProirity()
{
}


LogProirity::~LogProirity()
{
}

std::string LogProirity::toString()
{
	return std::string();
}

bool LogProirity::ifLogMessage(LogProirityEnum toLogProi)
{
	if (toLogProi <= logProi)
	{
		return true;
	}
	else
	{
		return false;
	}
}

LogERROR::LogERROR()
{
}

LogERROR::~LogERROR()
{
}

std::string LogERROR::toString()
{
	return "ERROR";
}

LogWARN::LogWARN()
{
}

LogWARN::~LogWARN()
{
}

std::string LogWARN::toString()
{
	return "WARN";
}

LogINFO::LogINFO()
{
}

LogINFO::~LogINFO()
{
}

std::string LogINFO::toString()
{
	return "INFO";
}

LogDEBUG::LogDEBUG()
{
}

LogDEBUG::~LogDEBUG()
{
}

std::string LogDEBUG::toString()
{
	return "DEBUG";
}
