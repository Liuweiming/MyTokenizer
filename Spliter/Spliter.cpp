// Spliter.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <vector>
#include <string>
#include "Spliter.h"
using namespace std;
int main()
{
	Spliter<string> spl("::", Spliter<string>::split_with_sub);
	auto p = spl.spliteRes("Unit1::Class1::class2::class3::method1::method2::x", spl.split_with_sub);
    return 0;
}

