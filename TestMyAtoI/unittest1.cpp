#include "stdafx.h"
#include "CppUnitTest.h"
#include "test.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace TestMyAtoI
{		
	TEST_CLASS(UnitTest1)
	{
	private:
		Solution_3 sol;
		Assert asser;
	public:
		TEST_METHOD(EasyTest1)
		{
			asser.AreEqual(sol.myAtoi("0"), 0);
			asser.AreEqual(sol.myAtoi(" 1"), 1);
			asser.AreEqual(sol.myAtoi("		12 "), 12);
			asser.AreEqual(sol.myAtoi(" d0 "), 0);
			asser.AreEqual(sol.myAtoi("012"), 12);
			asser.AreEqual(sol.myAtoi("+4664"), 4664);
			asser.AreEqual(sol.myAtoi("-1122"), -1122);
			asser.AreEqual(sol.myAtoi("123456789"), 123456789);
		}
		TEST_METHOD(OverFlowTest)
		{
			asser.AreEqual(sol.myAtoi("2147483647"), 0x7fffffff);
			asser.AreEqual(sol.myAtoi("-2148483648"), (int)0x80000000);
			asser.AreEqual(sol.myAtoi("2147483648"), 0x7fffffff);
			asser.AreEqual(sol.myAtoi("-2148483649"), (int)0x80000000);
		}
		TEST_METHOD(EXPTest)
		{
			asser.AreEqual(sol.myAtoi(" 1.23E3"), 1230);
			asser.AreEqual(sol.myAtoi("1E"), 1);
			asser.AreEqual(sol.myAtoi("235E0"), 235);
			asser.AreEqual(sol.myAtoi(" -124E+2"), -12400);
			asser.AreEqual(sol.myAtoi("123E10354354363"), 123);
			asser.AreEqual(sol.myAtoi("124E-3532"), 124);
			asser.AreEqual(sol.myAtoi("\t-134e1"), -1340);

		}
		TEST_METHOD(difficialTest)
		{
			asser.AreEqual(sol.myAtoi("    10522545459"), 0x7fffffff);
			asser.AreEqual(sol.myAtoi("-1122"), -1122);
			asser.AreEqual(sol.myAtoi("   -1118250626E1"), -1118250626);
			asser.AreEqual(sol.myAtoi("-9223372036854775809"), (int)0x80000000);
		}
		TEST_METHOD(testString)
		{
			Solution sol;
			vector<string> vec1 = { "we", "a", "tish", "k" };
			vector<vector<string>> ans = {
				{"ate", "eat", "tea"},
					{"nat", "tan"},
					{"bat"}
			};
			sol.groupAnagrams(vec1);
			//asser.AreEqual(, ans);
		}

	};
}