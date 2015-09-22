/*
you can set log properties there. it look like log4j
what this logger can do?
1. a logger
2. you can set some appenders to log messages to different destinations
3. you can customize different appenders with different formats

properties £º 
1. proiritis : ERROR, WARN, INFO, DEBUG, ALL
2. destinations : console, file { itemize, xml(not yet) }, iostream
3. layouts : 
   SampleLayout : {[proirity] [message]}
   TTCCLayout £º {[time] [proirity] [function] [message]}
   PatternLayout : customize pattern
4. cutomize pattern : 
   %d : date Format, %d{HH:mm:ss,SSS}, %d{ISO8601}, %d{ABSOLUTE}
   %F : file name
   %I : location imformation, include file name, class name, function name, line number
		equal to "%f.%c.%m.%L"
   %L : line number
   %m : application supplied message
   %M : method name
   %n : line separator like "\n", "\r\n"
   %p : proitity
   %r : milliseconds elapsed from begin until the creation of the logging event
   %t : thread name
   %x : not yet
   %X : not yet
   %% : out put an %
*/


#pragma once
#include <string>
#include <iostream>
class Appender;
class LogProperties
{
public:
	friend class Appender;
public:
	enum LogProirity { logERROR, logWARN, logINFO, logDEBUG};
	enum LogLayoutPre { HtmlLayout, PattenLayout, SimpleLayout, TTCCLayout, FULLLayout };
	enum LogAppenderDest { ConsoleDest, FileDest, StreamDest };
	LogProperties();
	~LogProperties();
	LogProperties(LogProirity logPro, LogAppenderDest logDest, LogLayoutPre logLay);
	LogProperties(LogProirity logPro, LogAppenderDest logDest, LogLayoutPre logLay, std::ostream &ostr);
private:
	std::string customizedFileDest = "log4cpp.log";
	std::ostream *customizedStreamDest = &(std::cout);
	std::string customizedPatten = "[-5p] %m";
public:
	LogProirity logProirity = logDEBUG;
	LogLayoutPre logLayout = SimpleLayout;
	LogAppenderDest logDestination = ConsoleDest;
	void customizeFileDest(const std::string &cust);
	void customizePatten(const std::string &cust);
	void customizeStream(std::iostream &ostr);
};

