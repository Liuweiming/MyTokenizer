// stringAppendTest.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <ctime>
#include <sstream>
using namespace std;
#define OUT_IN_REPEATE_NUM 1000
#define IN_REPEATE_NUM 600

string s1 = "abcedfg";
string s2 = "hijklmn";
string s3 = "opqrst";
stringstream ss;
void  plusTest(string& ret)
{
	for (int i = 0; i<IN_REPEATE_NUM; i++)
	{
		ret += s1;
		ret += s2;
		ret += s3;
	}
}
void  appendTest(string& ret)
{
	for (int i = 0; i<IN_REPEATE_NUM; i++)
	{
		ret.append(s1);
		ret.append(s2);
		ret.append(s3);
	}
}
void sprintfTest(string& ret)
{
	const size_t length = 26 * IN_REPEATE_NUM;
	char tmp[length];
	char* cp = tmp;
	size_t strLength = s1.length() + s2.length() + s3.length();
	for (int i = 0; i<IN_REPEATE_NUM; i++)
	{
		sprintf_s(cp, (strLength + 1) * sizeof(char), "%s%s%s", s1.c_str(), s2.c_str(), s3.c_str());
		cp += strLength;
	}
	ret = tmp;
}

void  ssTest(string& ret)
{
	ss.str("");
	for (int i = 0; i<IN_REPEATE_NUM; i++)
	{
		ss << s1;
		ss << s2;
		ss << s3;
	}
	ret = ss.str();
}
int main() {
	string ss, plus, append, sprintf;
	clock_t sTime, eTime;

	sTime = clock();
	for (int i = 0; i<OUT_IN_REPEATE_NUM; i++)
	{
		sprintf = "";
		sprintfTest(sprintf);
	}
	eTime = clock();
	double SprintfTime = (double)(eTime-sTime)/CLOCKS_PER_SEC; //exeTime 单位是微秒

	sTime = clock();
	for (int i = 0; i<OUT_IN_REPEATE_NUM; i++)
	{
		append = "";
		appendTest(append);
	}
	eTime = clock();
	double AppendTime = (double)(eTime-sTime)/CLOCKS_PER_SEC; //exeTime 单位是微秒

	sTime = clock();
	for (int i = 0; i<OUT_IN_REPEATE_NUM; i++)
	{
		ss = "";
		ssTest(ss);
	}
	eTime = clock();
	double SsTime = (double)(eTime-sTime)/CLOCKS_PER_SEC; //exeTime 单位是微秒

	sTime = clock();
	for (int i = 0; i<OUT_IN_REPEATE_NUM; i++)
	{
		plus = "";
		plusTest(plus);
	}
	eTime = clock();
	double PlusTime = (double)(eTime-sTime)/CLOCKS_PER_SEC; //exeTime 单位是微秒

	cout << "PlusTime is :   " << PlusTime << endl;
	cout << "AppendTime is : " << AppendTime << endl;
	cout << "SsTime is :     " << SsTime << endl;
	cout << "SprintfTime is :" << SprintfTime << endl;
	if (ss == sprintf && append == plus && ss == plus)
	{
		cout << "They are same" << endl;
	}
	else
	{
		cout << "Different!" << endl;
		cout << "Sprintf:  " << sprintf << endl;
		cout << "ss:       " << ss << endl;
		cout << "Plus:     " << plus << endl;
		cout << "Append:   " << append << endl;
	}
	return 0;
}

