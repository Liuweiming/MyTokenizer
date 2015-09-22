#pragma once
#include <string>
#include <deque>
#include <iostream>
#include <sstream>
#include <fstream>

class myTokenReader
{
public:
	myTokenReader(std::istream &is);
	~myTokenReader();
	std::deque<std::string>  &getresult();
	std::string getNext();
	std::string lookAhead();
	std::string lookAhead(std::size_t aheadCount);
private:
	void readToken();
private:
	std::istream &sourceStream;
	std::deque<std::string> myTokenQueue; //toknes container


};

