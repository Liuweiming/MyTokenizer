#pragma once
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
using namespace std;
class Solution_3 {
public:
	int myAtoi(string str) {
		long long ret = 0;
		bool positive = true;
		bool scientific = false;
		bool needDot = false;
		int dot = 0;
		if (str.empty())
		{
			return static_cast<int>(ret);
		}
		unsigned int pos = 0;
		string patten = "+-0123456789";
		while (pos != str.length() && (str[pos] == ' ' || str[pos] == '\t'))
		{
			++pos;
		}
		if (patten.find(str[pos]) == string::npos)
		{
			return static_cast<int>(ret);
		}
		if (str[pos] == '+')
		{
			positive = true;
			pos = pos + 1;
		}
		else if (str[pos] == '-')
		{
			positive = false;
			pos = pos + 1;
		}
		while (pos < str.length())
		{
			if (str[pos] == '.')
			{
				scientific = true;
				needDot = true;
			}
			else if (str[pos] == 'e' || str[pos] == 'E')
			{
				scientific = true;
				if (pos != str.length() - 1)
				{
					if (ret == 0)
					{
						if (positive)
						{
							ret = 1;
						}
						else
						{
							ret = -1;
						}
					}
					ret = getScientific(str.substr(pos + 1, str.length()), ret, dot);
				}
				break;
			}
			else if (str[pos] >= '0' && str[pos] <= '9')
			{
				ret = ret * 10 + (positive ? 1 : -1) * (str[pos] - '0');
				if (positive && ret > 0x7fffffff)
				{
					ret = 0x7fffffff;
				}
				else if (!positive && ret < -(long long)0x80000000)
				{
					ret = -(long long)0x80000000;
				}
				if (needDot)
				{
					++dot;
				}
			}
			else {
				break;
			}
			++pos;
		}
		return static_cast<int>(ret);
	}
	int getScientific(string str, long long val, int dot)
	{
		long sci = 0;
		bool positive = true;
		string patten = "+-0123456789";
		if (!str.empty())
		{
			unsigned int pos = 0;
			if (patten.find(str[pos]) != string::npos)
			{
				if (str[pos] == '+')
				{
					positive = true;
					pos = pos + 1;
				}
				else if (str[pos] == '-')
				{
					positive = false;
					pos = pos + 1;
				}
				while (pos < str.length())
				{
					if (str[pos] >= '0' && str[pos] <= '9')
					{
						sci = sci * 10 + (positive ? 1 : -1) * (str[pos] - '0');
						if (positive && sci > 0x7fffffff)
						{
							sci = 0x7fffffff;
						}
						else if (!positive && sci < -(long long)0x80000000)
						{
							sci = -(long long)0x80000000;
						}
					}
					else {
						break;
					}
					++pos;
				}
			}
		}
		int exp = sci - dot;
		if (exp < 0 || exp > 9)
		{
			return static_cast<int>(val);
		}
		long long valBack = val;
		bool posi = val > 0 ? true : false;
		for (; exp != 0; --exp)
		{
			val = val * 10;
			if (val > 0x7fffffff)
			{
				return static_cast<int>(valBack);
			}
			else if (!posi && val < -(long long)0x80000000)
			{
				return static_cast<int>(valBack);
			}
		}
		return static_cast<int>(val);
	}
};

class Solution {
public:
	vector<vector<string>> groupAnagrams(vector<string>& strs) {
		vector<string> back = strs;
		vector<vector<string>> ret;
		vector<string> group;
		unordered_map<string, vector<string>> mytable;
		for (auto p = back.begin(); p != back.end(); ++p)
		{
			sort(p->begin(), p->end());
		}
		for (auto i = 0; i != back.size(); ++i)
		{
			mytable[back[i]].push_back(std::move(strs[i]));
		}
		for (auto p = mytable.begin(); p != mytable.end(); ++p)
		{
			ret.push_back(std::move(p->second));
		}
		for (auto p = ret.begin(); p != ret.end(); ++p)
		{
			sort(p->begin(), p->end());
		}
		return std::move(ret);
	}
	void sortString(vector<string> &vec1, vector<string> &vec2)
	{
		if (vec1.size() == 0)
		{
			return;
		}
		for (int i = 1; i != vec1.size(); ++i)
		{
			for (int j = i - 1; j >= 0; --j)
			{
				if (vec1[j + 1] >= vec1[j])
				{
					break;
				}
				using std::swap;
				swap(vec1[j], vec1[j + 1]);
				swap(vec2[j], vec2[j + 1]);
			}
		}
	}
};