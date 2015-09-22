#include "stdafx.h"
#include "myTokenReader.h"



myTokenReader::myTokenReader(std::istream &is) : sourceStream(is)
{
}


myTokenReader::~myTokenReader()
{
}

std::deque<std::string>& myTokenReader::getresult()
{
	// TODO: 在此处插入 return 语句
	return myTokenQueue;
}

std::string myTokenReader::getNext()
{
	if (!myTokenQueue.empty())
	{
		std::string retString = myTokenQueue.front();
		myTokenQueue.pop_front();
		return retString;
	}
	else
	{
		return std::string();
	}
}

std::string myTokenReader::lookAhead()
{
	if (!myTokenQueue.empty())
	{
		std::string retString = myTokenQueue.front();
		return retString;
	}
	else
	{
		return std::string();
	}
}

std::string myTokenReader::lookAhead(std::size_t aheadCount)
{
	if (myTokenQueue.size() >= aheadCount)
	{
		std::string retString = myTokenQueue[aheadCount - 1];
		return retString;
	}
	else
	{
		return std::string();
	}
}

void myTokenReader::readToken()
{
	std::stringstream tmp_token;
	std::string tmp_str;
	sourceStream >> tmp_str;
	tmp_token.str(tmp_str);
	if (tmp_str == "-")
	{
		sourceStream >> tmp_str;
		tmp_token << tmp_str;
	}
}
