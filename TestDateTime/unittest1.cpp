#include "stdafx.h"
#include "CppUnitTest.h"

#include <sys/timeb.h>
#include <time.h>
#include <vector>
#include <string>
#define private public
#define protected public
#include "../DateAndTime/DateTime.h"
#include "../Spliter/Spliter.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;
namespace TestDateTime
{		
	BEGIN_TEST_MODULE_ATTRIBUTE()
		TEST_MODULE_ATTRIBUTE(L"Date", L"2015/9/5")
	END_TEST_MODULE_ATTRIBUTE()

	TEST_MODULE_INITIALIZE(ModuleInitialize)
	{
		Logger::WriteMessage("In Module Initialize");
	}

	TEST_MODULE_CLEANUP(ModuleCleanup)
	{
		Logger::WriteMessage("In Module Cleanup");
	}

	TEST_CLASS(TestDateAndTime)
	{

		_timeb timeBuffer;
		DateTime dt;
		DateTime::DateFormat formatter;
	public:

		TestDateAndTime()
		{
			Logger::WriteMessage("In Class1");
			timeBuffer.time = 1441446549;
			timeBuffer.millitm = 389;
			dt.timebuffer = timeBuffer;
			dt.updateFlag = true;
			dt.updateTime();
		}

		~TestDateAndTime()
		{
			Logger::WriteMessage("In ~Class1");
		}

		TEST_CLASS_INITIALIZE(ClassInitialize)
		{
			Logger::WriteMessage("In Class Initialize");
		}

		TEST_CLASS_CLEANUP(ClassCleanup)
		{
			Logger::WriteMessage("In Class Cleanup");
		}

		BEGIN_TEST_METHOD_ATTRIBUTE(SimpleTest)
			TEST_OWNER(L"Luwemng")
			TEST_PRIORITY(1)
		END_TEST_METHOD_ATTRIBUTE()

			BEGIN_TEST_METHOD_ATTRIBUTE(MoreDifficult)
			TEST_OWNER(L"Luwemng")
			TEST_PRIORITY(2)
			END_TEST_METHOD_ATTRIBUTE()

			TEST_METHOD(SimpleTest)
		{
			Logger::WriteMessage("In SimpleTest");
			Assert::AreEqual(string("05"), dt.FormatDate("dd"));
			Assert::AreEqual(string("5"), dt.FormatDate("d"));
			Assert::AreEqual(string("0005"), dt.FormatDate("dddd"));
			Assert::AreEqual(string("9"), dt.FormatDate("M"));
			Assert::AreEqual(string("09"), dt.FormatDate("MM"));
			Assert::AreEqual(string("Sep"), dt.FormatDate("MMM"));
			Assert::AreEqual(string("September"), dt.FormatDate("MMMM"));
			Assert::AreEqual(string("September"), dt.FormatDate("MMMMM"));
			Assert::AreEqual(string("2015"), dt.FormatDate("y"));
			Assert::AreEqual(string("15"), dt.FormatDate("yy"));
			Assert::AreEqual(string("2015"), dt.FormatDate("yyy"));
			Assert::AreEqual(string("2015"), dt.FormatDate("yyyy"));
			Assert::AreEqual(string("02015"), dt.FormatDate("yyyyy"));
			Assert::AreEqual(string("17"), dt.FormatDate("H"));
			Assert::AreEqual(string("17"), dt.FormatDate("HH"));
			Assert::AreEqual(string("017"), dt.FormatDate("HHH"));
			Assert::AreEqual(string("0017"), dt.FormatDate("HHHH"));
			Assert::AreEqual(string("5"), dt.FormatDate("K"));
			Assert::AreEqual(string("05"), dt.FormatDate("KK"));
			Assert::AreEqual(string("005"), dt.FormatDate("KKK"));
			Assert::AreEqual(string("0005"), dt.FormatDate("KKKK"));
			Assert::AreEqual(string("49"), dt.FormatDate("m"));
			Assert::AreEqual(string("49"), dt.FormatDate("mm"));
			Assert::AreEqual(string("049"), dt.FormatDate("mmm"));
			Assert::AreEqual(string("0049"), dt.FormatDate("mmmm"));
			Assert::AreEqual(string("9"), dt.FormatDate("s"));
			Assert::AreEqual(string("09"), dt.FormatDate("ss"));
			Assert::AreEqual(string("009"), dt.FormatDate("sss"));
			Assert::AreEqual(string("0009"), dt.FormatDate("ssss"));
			Assert::AreEqual(string("389"), dt.FormatDate("S"));
			Assert::AreEqual(string("389"), dt.FormatDate("SS"));
			Assert::AreEqual(string("389"), dt.FormatDate("SSS"));
			Assert::AreEqual(string("0389"), dt.FormatDate("SSSS"));
			Assert::AreEqual(string("6"), dt.FormatDate("E"));
			Assert::AreEqual(string("06"), dt.FormatDate("EE"));
			Assert::AreEqual(string("Sat"), dt.FormatDate("EEE"));
			Assert::AreEqual(string("Saturday"), dt.FormatDate("EEEE"));
			Assert::AreEqual(string("Saturday"), dt.FormatDate("EEEEE"));
			Assert::AreEqual(string("6"), dt.FormatDate("u"));
			Assert::AreEqual(string("06"), dt.FormatDate("uu"));
			Assert::AreEqual(string("006"), dt.FormatDate("uuu"));
			Assert::AreEqual(string("0006"), dt.FormatDate("uuuu"));
			Assert::AreEqual(string("PM"), dt.FormatDate("a"));
			Assert::AreEqual(string("PM"), dt.FormatDate("aa"));
		}

		TEST_METHOD(MoreDifficult)
		{
			Assert::AreEqual(string(" [ 05 - 09 - 2015 ] "), dt.FormatDate(" [ dd - MM - yyyy ] "));
			Assert::AreEqual(string("this is 17:49:09 "), dt.FormatDate("'this is 'HH:mm:ss "));
			Assert::AreEqual(string("test commentSeptime15HH17ss09SSS389end"), dt.FormatDate("'test comment'MMM'time'yy'HH'HH'ss'ss'SSS'SSS'end'"));
			Assert::AreEqual(string("05-09-2015 Sat 17:49:09,389"), dt.FormatDate("dd-MM-yyyy EEE HH:mm:ss,SSS"));
			Assert::AreEqual(string("05-Sep-2015 Saturday 05:49:09,389 PM"), dt.FormatDate("dd-MMM-yyyy EEEE KK:mm:ss,SSS a"));
			Assert::AreEqual(string("05/September/2015 Saturday 17:49:09"), dt.FormatDate("dd/MMMM/yyyy EEEE HH:mm:ss"));
			Assert::AreEqual(string("[5 05 005 9 09 Sep September 2015 15 2015 2015 6 06 Sat Saturday 6 06 006 0006 17 17 017 0017 5 05 005 0005 PM PM PM 49 49 049 9 09 009 0009 389 389 389 0389]"), dt.FormatDate("[d dd ddd M MM MMM MMMM y yy yyy yyyy E EE EEE EEEE u uu uuu uuuu H HH HHH HHHH K KK KKK KKKK a aa aaa m mm mmm s ss sss ssss S SS SSS SSSS]"));
		}
		TEST_METHOD(testDateFormat)
		{
			formatter.setFormat(" [ dd - MM - yyyy ] ");
			Assert::AreEqual(string(" [ 05 - 09 - 2015 ] "), formatter.formatDate(dt));
			formatter.setFormat("dd");
			Assert::AreEqual(string("05"), formatter.formatDate(dt));;
			formatter.setFormat("d");
			Assert::AreEqual(string("5"), formatter.formatDate(dt));;
			formatter.setFormat("dddd");
			Assert::AreEqual(string("0005"), formatter.formatDate(dt));;
			formatter.setFormat("M");
			Assert::AreEqual(string("9"), formatter.formatDate(dt));;
			formatter.setFormat("MM");
			Assert::AreEqual(string("09"), formatter.formatDate(dt));;
			formatter.setFormat("MMM");
			Assert::AreEqual(string("Sep"), formatter.formatDate(dt));;
			formatter.setFormat("MMMM");
			Assert::AreEqual(string("September"), formatter.formatDate(dt));;
			formatter.setFormat("MMMMM");
			Assert::AreEqual(string("September"), formatter.formatDate(dt));;
			formatter.setFormat("y");
			Assert::AreEqual(string("2015"), formatter.formatDate(dt));;
			formatter.setFormat("yy");
			Assert::AreEqual(string("15"), formatter.formatDate(dt));;
			formatter.setFormat("yyy");
			Assert::AreEqual(string("2015"), formatter.formatDate(dt));;
			formatter.setFormat("yyyy");
			Assert::AreEqual(string("2015"), formatter.formatDate(dt));;
			formatter.setFormat("yyyyy");
			Assert::AreEqual(string("02015"), formatter.formatDate(dt));;
			formatter.setFormat("H");
			Assert::AreEqual(string("17"), formatter.formatDate(dt));;
			formatter.setFormat("HH");
			Assert::AreEqual(string("17"), formatter.formatDate(dt));;
			formatter.setFormat("HHH");
			Assert::AreEqual(string("017"), formatter.formatDate(dt));;
			formatter.setFormat("HHHH");
			Assert::AreEqual(string("0017"), formatter.formatDate(dt));;
			formatter.setFormat("K");
			Assert::AreEqual(string("5"), formatter.formatDate(dt));;
			formatter.setFormat("KK");
			Assert::AreEqual(string("05"), formatter.formatDate(dt));;
			formatter.setFormat("KKK");
			Assert::AreEqual(string("005"), formatter.formatDate(dt));;
			formatter.setFormat("KKKK");
			Assert::AreEqual(string("0005"), formatter.formatDate(dt));;
			formatter.setFormat("m");
			Assert::AreEqual(string("49"), formatter.formatDate(dt));;
			formatter.setFormat("mm");
			Assert::AreEqual(string("49"), formatter.formatDate(dt));;
			formatter.setFormat("mmm");
			Assert::AreEqual(string("049"), formatter.formatDate(dt));;
			formatter.setFormat("mmmm");
			Assert::AreEqual(string("0049"), formatter.formatDate(dt));;
			formatter.setFormat("s");
			Assert::AreEqual(string("9"), formatter.formatDate(dt));;
			formatter.setFormat("ss");
			Assert::AreEqual(string("09"), formatter.formatDate(dt));;
			formatter.setFormat("sss");
			Assert::AreEqual(string("009"), formatter.formatDate(dt));;
			formatter.setFormat("ssss");
			Assert::AreEqual(string("0009"), formatter.formatDate(dt));;
			formatter.setFormat("S");
			Assert::AreEqual(string("389"), formatter.formatDate(dt));;
			formatter.setFormat("SS");
			Assert::AreEqual(string("389"), formatter.formatDate(dt));;
			formatter.setFormat("SSS");
			Assert::AreEqual(string("389"), formatter.formatDate(dt));;
			formatter.setFormat("SSSS");
			Assert::AreEqual(string("0389"), formatter.formatDate(dt));;
			formatter.setFormat("E");
			Assert::AreEqual(string("6"), formatter.formatDate(dt));;
			formatter.setFormat("EE");
			Assert::AreEqual(string("06"), formatter.formatDate(dt));;
			formatter.setFormat("EEE");
			Assert::AreEqual(string("Sat"), formatter.formatDate(dt));;
			formatter.setFormat("EEEE");
			Assert::AreEqual(string("Saturday"), formatter.formatDate(dt));;
			formatter.setFormat("EEEEE");
			Assert::AreEqual(string("Saturday"), formatter.formatDate(dt));;
			formatter.setFormat("u");
			Assert::AreEqual(string("6"), formatter.formatDate(dt));;
			formatter.setFormat("uu");
			Assert::AreEqual(string("06"), formatter.formatDate(dt));;
			formatter.setFormat("uuu");
			Assert::AreEqual(string("006"), formatter.formatDate(dt));;
			formatter.setFormat("uuuu");
			Assert::AreEqual(string("0006"), formatter.formatDate(dt));;
			formatter.setFormat("a");
			Assert::AreEqual(string("PM"), formatter.formatDate(dt));;
			formatter.setFormat("aa");
			Assert::AreEqual(string("PM"), formatter.formatDate(dt));;
			formatter.setFormat("'this is 'HH:mm:ss ");
			Assert::AreEqual(string("this is 17:49:09 "), formatter.formatDate(dt));;
			formatter.setFormat("'test comment'MMM'time'yy'HH'HH'ss'ss'SSS'SSS'end'");
			Assert::AreEqual(string("test commentSeptime15HH17ss09SSS389end"), formatter.formatDate(dt));;
			formatter.setFormat("dd-MM-yyyy EEE HH:mm:ss,SSS");
			Assert::AreEqual(string("05-09-2015 Sat 17:49:09,389"), formatter.formatDate(dt));;
			formatter.setFormat("dd-MMM-yyyy EEEE KK:mm:ss,SSS a");
			Assert::AreEqual(string("05-Sep-2015 Saturday 05:49:09,389 PM"), formatter.formatDate(dt));;
			formatter.setFormat("dd/MMMM/yyyy EEEE HH:mm:ss");
			Assert::AreEqual(string("05/September/2015 Saturday 17:49:09"), formatter.formatDate(dt));;
			formatter.setFormat("[d dd ddd M MM MMM MMMM y yy yyy yyyy E EE EEE EEEE u uu uuu uuuu H HH HHH HHHH K KK KKK KKKK a aa aaa m mm mmm s ss sss ssss S SS SSS SSSS]");
			Assert::AreEqual(string("[5 05 005 9 09 Sep September 2015 15 2015 2015 6 06 Sat Saturday 6 06 006 0006 17 17 017 0017 5 05 005 0005 PM PM PM 49 49 049 9 09 009 0009 389 389 389 0389]"), formatter.formatDate(dt));;
		}
	};
}

namespace Microsoft {
	namespace VisualStudio {
		namespace CppUnitTestFramework
		{
			template<typename T> inline std::wstring ToString(const vector<T> &t)
			{
				//函数中不需要显式声明类型vector<T>，它可以根据参数类型推断，
				//而如果要半特化模板类的话，就需要在class 后显式声明 vecotr<T>
				std::wstring ret;
				ret += L"[";
				for (const T &s : t)
				{
					ret += ToString(s) + L" ";
				}
				ret += L"]";
				return std::move(ret);
			}
		}
	}
}

namespace TestSplit
{
	BEGIN_TEST_MODULE_ATTRIBUTE()
		TEST_MODULE_ATTRIBUTE(L"Date", L"2015/9/7")
		END_TEST_MODULE_ATTRIBUTE()

		TEST_MODULE_INITIALIZE(ModuleInitialize)
	{
		Logger::WriteMessage("In Module Initialize");
	}

	TEST_MODULE_CLEANUP(ModuleCleanup)
	{
		Logger::WriteMessage("In Module Cleanup");
	}

	TEST_CLASS(TestSplit)
	{
		Spliter<string> spl;
		Spliter<vector<int>> IntSpl;
		Spliter<wstring> wspl;
		Assert as;
	public:
		TestSplit() : spl(":, .", Spliter<string>::split_with_char), IntSpl(vector<int>{2, 3}, Spliter<vector<int>>::split_with_char), wspl(L":, .", Spliter<wstring>::split_with_char)
		{}
		TEST_METHOD(SimpleTest)
		{
			as.AreEqual(vector<string>{""}, spl.spliteRes(""));
			as.AreEqual(vector<string>{"1"}, spl.spliteRes("1"));
			as.AreEqual(vector<string>{"agfdse1"}, spl.spliteRes("agfdse1"));
			as.AreEqual(vector<string>{"", "", "a"}, spl.spliteRes("::a"));
			as.AreEqual(vector<string>{"", "", "a","", "", ""}, spl.spliteRes("::a..,"));
			as.AreEqual(vector<string>{"", "a", ""}, spl.spliteRes(".a,"));
			as.AreEqual(vector<string>{"class1", "class2"}, spl.spliteRes("class1.class2"));
			as.AreEqual(vector<string>{"a", "b", "c"}, spl.spliteRes("a:b:c"));
			as.AreEqual(vector<string>{"1", "2", "3", "4"}, spl.spliteRes("1,2,3,4"));
			as.AreEqual(vector<string>{"test", "", "Class1", "", "Class2", "void", "", "getInt(int", "i", "", "int", "j)"}, spl.spliteRes("test::Class1::Class2.void  getInt(int i, int j)"));
		}
		TEST_METHOD(SimpleTest2)
		{
			spl.type = Spliter<string>::split_with_sub;
			as.AreEqual(vector<string>{""}, spl.spliteRes(""));
			as.AreEqual(vector<string>{"1"}, spl.spliteRes("1"));
			as.AreEqual(vector<string>{"agfdse1"}, spl.spliteRes("agfdse1"));
			as.AreEqual(vector<string>{"::a"}, spl.spliteRes("::a"));
			as.AreEqual(vector<string>{"", "a..."}, spl.spliteRes(":, .a..."));
			as.AreEqual(vector<string>{".a,"}, spl.spliteRes(".a,"));
			as.AreEqual(vector<string>{"", "a", " ,:"}, spl.spliteRes(":, .a:, . ,:"));
			as.AreEqual(vector<string>{"class1", "class2"}, spl.spliteRes("class1:, .class2"));
			as.AreEqual(vector<string>{"a", "b", "c"}, spl.spliteRes("a:, .b:, .c"));
			as.AreEqual(vector<string>{"1", "2", "3", "4"}, spl.spliteRes("1:, .2:, .3:, .4"));
			as.AreEqual(vector<string>{"test", "Class1", "Class2", "void getInt(int i, int j)"}, spl.spliteRes("test:, .Class1:, .Class2:, .void getInt(int i, int j)"));
		}
		TEST_METHOD(wSimpleTest22)
		{
			wspl.type = Spliter<wstring>::split_with_sub;
			as.AreEqual(vector<wstring>{L""}, wspl.spliteRes(L""));
			as.AreEqual(vector<wstring>{L"1"}, wspl.spliteRes(L"1"));
			as.AreEqual(vector<wstring>{L"agfdse1"}, wspl.spliteRes(L"agfdse1"));
			as.AreEqual(vector<wstring>{L"::a"}, wspl.spliteRes(L"::a"));
			as.AreEqual(vector<wstring>{L"", L"a..."}, wspl.spliteRes(L":, .a..."));
			as.AreEqual(vector<wstring>{L".a,"}, wspl.spliteRes(L".a,"));
			as.AreEqual(vector<wstring>{L"", L"a", L" ,:"}, wspl.spliteRes(L":, .a:, . ,:"));
			as.AreEqual(vector<wstring>{L"class1", L"class2"}, wspl.spliteRes(L"class1:, .class2"));
			as.AreEqual(vector<wstring>{L"a", L"b", L"c"}, wspl.spliteRes(L"a:, .b:, .c"));
			as.AreEqual(vector<wstring>{L"1", L"2", L"3", L"4"}, wspl.spliteRes(L"1:, .2:, .3:, .4"));
			as.AreEqual(vector<wstring>{L"test", L"Class1", L"Class2", L"void getInt(int i, int j)"}, wspl.spliteRes(L"test:, .Class1:, .Class2:, .void getInt(int i, int j)"));
		}
		TEST_METHOD(VectorInt)
		{
			as.AreEqual(vector<vector<int>>{ {}}, IntSpl.spliteRes({}));
			as.AreEqual(vector<vector<int>>{ {1}}, IntSpl.spliteRes({1}));
			as.AreEqual(vector<vector<int>>{ {}, {1}}, IntSpl.spliteRes({ 2, 1 }));
			as.AreEqual(vector<vector<int>>{ {}, { 1 }, {}}, IntSpl.spliteRes({ 2, 1, 3 }));
			as.AreEqual(vector<vector<int>>{ {1}, { 1 }}, IntSpl.spliteRes({ 1, 2, 1 }));
			as.AreEqual(vector<vector<int>>{ {}, { 4 }, { 1 }, {}}, IntSpl.spliteRes({ 3, 4, 3, 1, 2 }));
		}
	};
}