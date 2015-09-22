#pragma once
#include <string>
#include <vector>
#include <ios>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <cassert>
#include <exception>
#include "..\DateAndTime\DateTime.h"
#include "..\Spliter\Spliter.h"
#include "logProperties.h"

enum LogInfoSub
{
	dateAndTime,
	fileName,
	locationInfo,
	lineNum,
	message,
	methodName,
	proitity,
	milliSecond,
	threadName,
	none
};
struct LogInfomations
{
	DateTime dateAndTime;
	std::string fileName;
	unsigned long long lineNum;
	std::string message;
	std::string methodName;
	LogProperties::LogProirity proitity;
	unsigned long long milliSecond;
	std::string threadName;
};


class LogLayoutSub
{
public:
	LogLayoutSub();
	LogLayoutSub(const std::string &patt);
	virtual ~LogLayoutSub();
	void setPatten(const std::string &patt);
	virtual std::string getResult(const struct LogInfomations &logInfo);
protected:
	virtual void updateFormat(); //update function
	std::stringstream getBraceExpstd(const std::string & patten);
	
	void resetFormatter();
	bool update = false; // flag for this subLayout to update it's formatter;
	std::string patten;
	std::stringstream formatter;
	char mark;
	std::size_t fullLength = 1;
	std::size_t subLength = 3;
};

class LogLayoutDate : public LogLayoutSub
{
public:
	LogLayoutDate() : LogLayoutSub()
	{
	}
	LogLayoutDate(const std::string &patt) : LogLayoutSub(patt) 
	{
	}
	~LogLayoutDate() {}
	virtual std::string getResult(const struct LogInfomations &logInfo);
private:
	virtual void updateFormat();
	DateTime::DateFormat dateFormatter;
};

class LogLayoutDelim : public LogLayoutSub
{
public:
	LogLayoutDelim(){}
	LogLayoutDelim(const std::string &patt) : LogLayoutSub(patt)
	{
	}
	virtual std::string getResult(const LogInfomations & logInfo);
protected:
	virtual void updateFormat();
	std::string getLogInfoTokens(const std::string & logInfo);
	std::string delim;
	std::size_t tokenLen = 0;
	Spliter<std::string> spliter;
	void setSpliter(const std::string &del)
	{
		delim = del;
		spliter.setDelim(delim);
		spliter.setType(Spliter<std::string>::split_with_sub);
	}
};

class LogLayoutFile : public LogLayoutDelim
{
public:
	LogLayoutFile()
	{
		setSpliter("\\");
	}
	LogLayoutFile(const std::string &patt) : LogLayoutDelim(patt)
	{
		setSpliter("\\");
	}
	virtual std::string getResult(const struct LogInfomations &logInfo);
};

class LogLayoutLacation : public LogLayoutSub
{
public:
	LogLayoutLacation() : LogLayoutSub()
	{
	}
	LogLayoutLacation(const std::string &patt) : LogLayoutSub(patt)
	{
	}
	~LogLayoutLacation() {}
	virtual std::string getResult(const struct LogInfomations &logInfo);
};

class LogLayoutLine : public LogLayoutSub
{
public:
	LogLayoutLine() : LogLayoutSub()
	{
	}
	LogLayoutLine(const std::string &patt) : LogLayoutSub(patt)
	{
	}
	~LogLayoutLine() {}
		virtual std::string getResult(const struct LogInfomations &logInfo);
};

class LogLayoutMess : public LogLayoutSub
{
public:
	LogLayoutMess() : LogLayoutSub()
	{
	}
	LogLayoutMess(const std::string &patt) : LogLayoutSub(patt)
	{
	}
	~LogLayoutMess() {}
		virtual std::string getResult(const struct LogInfomations &logInfo);
};

class LogLayoutMeth : public LogLayoutDelim
{
public:
	LogLayoutMeth()
	{
		setSpliter("::");
	}
	LogLayoutMeth(const std::string &patt) : LogLayoutDelim(patt)
	{
		setSpliter("::");
	}
	~LogLayoutMeth() {}
	virtual std::string getResult(const struct LogInfomations &logInfo);
private:
	
};

class LogLayoutProi : public LogLayoutSub
{
public:
	LogLayoutProi() : LogLayoutSub()
	{
	}
	LogLayoutProi(const std::string &patt) : LogLayoutSub(patt)
	{
	}
	~LogLayoutProi() {}
		virtual std::string getResult(const struct LogInfomations &logInfo);
public:
	LogProperties::LogProirity proitity;
private:
	const std::string proitities[LogProperties::logDEBUG + 1] = { "ERROR", "WARM", "INFO", "DEBUG" };
};

class LogLayoutMilli : public LogLayoutSub
{
public:
	LogLayoutMilli() : LogLayoutSub()
	{
	}
	LogLayoutMilli(const std::string &patt) : LogLayoutSub(patt)
	{
	}
	~LogLayoutMilli() {}
		virtual std::string getResult(const struct LogInfomations &logInfo);
};

class LogLayoutThread : public LogLayoutSub
{
public:
	LogLayoutThread() : LogLayoutSub()
	{
	}
	LogLayoutThread(const std::string &patt) : LogLayoutSub(patt)
	{
	}
	~LogLayoutThread() {}
		virtual std::string getResult(const struct LogInfomations &logInfo);
};

class LogLayoutNone : public LogLayoutSub
{
public:
	LogLayoutNone() : LogLayoutSub()
	{
	}
	LogLayoutNone(const std::string &patt) : LogLayoutSub(patt)
	{
	}
	~LogLayoutNone() {}
		virtual std::string getResult(const struct LogInfomations &logInfo);
};



class LogLayout
{
public:
	using LogLayoutPre = LogProperties::LogLayoutPre;
	using LogProirity = LogProperties::LogProirity;
	static const std::string SimpleLayout;
	static const std::string TTCCLayout;
	static const std::string FULLLayout;
public:
	LogLayout();
	LogLayout(LogLayoutPre logLayPre);
	LogLayout(const std::string &patt);
	~LogLayout();
	void setPatten(const std::string &patt);
	void setPatten(LogLayoutPre logLayPre);
	std::string getResult(const struct LogInfomations &logInfo);
private:
	std::string patten = SimpleLayout;
	std::vector<LogLayoutSub *> logLayoutSubs;
	void logLayoutParser();
	LogLayoutSub * updateFormat(std::string::iterator &pos, std::string::const_iterator &end);
	std::string readBrae(std::string::iterator & pos, std::string::const_iterator & end);
	void destructVec();
	bool update = true; // flag for update formatter;
};



