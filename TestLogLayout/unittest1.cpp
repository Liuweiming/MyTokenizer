#include "stdafx.h"
#include "CppUnitTest.h"
#include <sys/timeb.h>
#include <time.h>
#include <vector>
#include <string>
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;
#define private public
#define protected public
#include "..\log4cpp\LogLayout.h"
namespace TestLogLayout
{
	TEST_CLASS(TestLogLayout)
	{

	public:

		static LogInfomations info;
		static DateTime dt;
		static _timeb timeBuffer;

		TEST_CLASS_INITIALIZE(iniInfo)
		{
			TestLogLayout::timeBuffer.time = 1441446549;
			TestLogLayout::timeBuffer.millitm = 389;
			TestLogLayout::dt.timebuffer = TestLogLayout::timeBuffer;
			TestLogLayout::dt.updateFlag = true;
			TestLogLayout::dt.updateTime();
			TestLogLayout::info.dateAndTime = TestLogLayout::dt;
			TestLogLayout::info.fileName = __FILE__;
			TestLogLayout::info.lineNum = 1234;
			TestLogLayout::info.message = "test";
			TestLogLayout::info.methodName = __FUNCTION__;
			TestLogLayout::info.milliSecond = 931;
			TestLogLayout::info.proitity = LogProperties::logDEBUG;
			TestLogLayout::info.threadName = "Main";
		}

		TEST_METHOD(TestSimple)
		{
			LogLayout myLayout;
			myLayout.setPatten(LogLayout::SimpleLayout);
			myLayout.getResult(TestLogLayout::info);
			Assert::AreEqual(string("[DEBUG] - test"), myLayout.getResult(TestLogLayout::info));
		}

	};

	LogInfomations TestLogLayout::info;
	DateTime TestLogLayout::dt;
	_timeb TestLogLayout::timeBuffer;
}