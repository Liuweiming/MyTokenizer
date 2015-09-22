// DateAndTime.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "DateTime.h"
#include <string>
#include <iostream>
#include <Windows.h>
using namespace std;
int main()
{
	std::string dateFormat = "[dd-MMMM-MM-yyyy-yy EEEE EE uu FF ww a HH:KK:mm:ss,SSS]";
	DateTime datetime;
	DateTime bac = datetime;
	datetime.setFormate(dateFormat);
	for (int i = 0; i != 10; ++i)
	{
		datetime.mark();
		cout << datetime.FormatDate() << endl;
		Sleep(10);
	}
	cout << datetime.diffInMilliSec(bac) << endl;
    return 0;
}

