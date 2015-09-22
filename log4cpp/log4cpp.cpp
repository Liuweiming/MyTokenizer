// log4cpp.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <string>
#include <iostream>
#include "log4cpp.h"
#include <Windows.h>
using namespace std;
void test1()
{
	LogDestConsole con;
	LogDestStream logStr(std::cout);
	LogDestFile logFile;
	con.pushLog("yyyy\n");
	logStr.pushLog("this is a stream log\n");
	logFile.pushLog("this is a file log\n");
}

class testClass
{
public:
	class testClass2
	{
	public:
		void testMethod(myLog &mylog)
		{
			mylog.logDEBUG("in testMethod");
			mylog.logINFO("this is an info");
		}
	};
};

void test3()
{
	myLog log;
	log.addAppender();
	log.logAppenders[0].getLogProperties().logDestination = LogProperties::LogAppenderDest::FileDest;
	log.logAppenders[0].getLogProperties().customizeFileDest("test.log");
	log.logAppenders[0].getLogProperties().customizePatten("%d{yyyy/MMM/ddd HH:mm:ss,SSS} [%-5p] %c{2} %F %C %M %L ---- %m");
	log.logAppenders[1].getLogProperties().logDestination = LogProperties::LogAppenderDest::ConsoleDest;
	testClass::testClass2 myClass;
	for (auto i = 0; i != 30; ++i)
	{
		//Sleep(50);
		//log.DEBUG("this is a test");
		myClass.testMethod(log);
	}
	return;
}

int main()
{
	test3();
	return 0;
}

