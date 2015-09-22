#include "stdafx.h"
#include "LogDestination.h"


LogDestination::LogDestination()
{
}


LogDestination::~LogDestination()
{
}

bool LogDestination::pushLog(const std::string & message, std::ostream & ostr)
{
	ostr << message;
	return true;
}

bool LogDestination::pushLog(const std::string & message)
{
	return false;
}

LogDestConsole::LogDestConsole()
{
}

LogDestConsole::~LogDestConsole()
{
}

bool LogDestConsole::pushLog(const std::string & message)
{
	ostr << message << std::endl;
	return true;
}

LogDestFile::LogDestFile() : ostr(std::ofstream("log4cpp.log", std::ios::out|std::ios::app))
{
	if (!ostr)
	{
		std::cerr << "open file : " << "log4cpp.log" << " error" << std::endl;
	}
}

LogDestFile::LogDestFile(const std::string & fileName) : 
	ostr(std::ofstream(fileName, std::ios::out | std::ios::app))
{
	if (!ostr)
	{
		std::cerr << "open file : " << fileName << " error" << std::endl;
	}
}

LogDestFile::~LogDestFile()
{
	ostr.close();
}

bool LogDestFile::pushLog(const std::string & message)
{
	if (ostr)
	{
		ostr << message << std::endl;
		if (ostr)
		{
			return true;
		}
		else
		{
			std::cerr << "write to file error" << std::endl;
			return false;
		}
	}
	else
	{
		std::cerr << "write to file error" << std::endl;
		return false;
	}
}

LogDestStream::LogDestStream()
{
}

LogDestStream::LogDestStream(std::ostream & ostr) : ostr(ostr)
{
}

LogDestStream::~LogDestStream()
{
}

bool LogDestStream::pushLog(const std::string & message)
{
	if (ostr)
	{
		ostr << message << std::endl;
		if (ostr)
		{
			return true;
		}
		else
		{
			std::cerr << "write to file error" << std::endl;
			return false;
		}
	}
	else
	{
		std::cerr << "write to file error" << std::endl;
		return false;
	}
}
