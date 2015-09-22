#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <ios>
class LogDestination
{
public:
	LogDestination();
	~LogDestination();
	virtual bool pushLog(const std::string &message);
private:
	virtual bool pushLog(const std::string &message, std::ostream &ostr);
};

class LogDestConsole : public LogDestination
{
public:
	LogDestConsole();
	~LogDestConsole();
	virtual bool pushLog(const std::string &message);
private:
	std::ostream &ostr = std::cout;
};

class LogDestFile : public LogDestination
{
public:
	LogDestFile();
	LogDestFile(const std::string &fileName);
	~LogDestFile();
	virtual bool pushLog(const std::string &message);
private:
	std::ofstream ostr;
};

class LogDestStream : public LogDestination
{
public:
	LogDestStream();
	LogDestStream(std::ostream &ostr);
	~LogDestStream();
	virtual bool pushLog(const std::string &message);
private:
	std::ostream &ostr = std::cout;
};