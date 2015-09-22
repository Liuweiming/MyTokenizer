#include "stdafx.h"
#include "LogLayout.h"
const std::string LogLayout::SimpleLayout = "[%-5p] - %m";
const std::string LogLayout::TTCCLayout = "%d [%-5p] %-30c - %m";
const std::string LogLayout::FULLLayout = "%d [%-5p] %-100I - %n    %m";



LogLayoutSub::LogLayoutSub()
{
}

LogLayoutSub::LogLayoutSub(const std::string & patt)
{
	setPatten(patt);
}

LogLayoutSub::~LogLayoutSub()
{
}

void LogLayoutSub::setPatten(const std::string & patt)
{
	patten = patt;
	update = true;
}

std::string LogLayoutSub::getResult(const struct LogInfomations &logInfo)
{
	return std::string();
}

std::stringstream LogLayoutSub::getBraceExpstd(const std::string & patten)
{
	std::stringstream sst;
	auto pos = patten.begin();
	while (pos != patten.end() && *pos != '{')
	{
		++pos;
	}
	++pos;
	while (pos != patten.end() && *pos != '}')
	{
		sst << *pos;
		++pos;
	}
	return std::move(sst);
}

std::string LogLayoutSub::getLogInfoTokens(const std::string & logInfo, Spliter<std::string> &spliter, std::size_t tokenLength)
{
	std::string ret;
	auto tokens = spliter.spliteRes(logInfo);
	if (tokenLength <= 0 || tokens.size() < tokenLength)
	{
		return logInfo;
	}
	ret += tokens[tokens.size() - tokenLength];
	for (auto i = tokens.size() - tokenLength + 1; i != tokens.size(); ++i)
	{
		ret += spliter.getDelim();
		ret += tokens[i];
	}
	return std::move(ret);
}

void LogLayoutSub::resetFormatter()
{
	formatter.clear();
	formatter.str("");
	formatter.width(fullLength);
}

void LogLayoutSub::updateFormat()
{
	if (update)
	{
		if (patten.empty())
		{
			formatter.unsetf(std::ios::adjustfield);
			formatter.unsetf(std::ios::floatfield);
			return;
		}
		std::string pattenSub = patten.substr(1, patten.find_first_not_of("%.-+#0123456789") - 1);
		if (pattenSub.size() == 0)
		{
			return;
		}
		auto ind = pattenSub.find_first_of('.', 0);
		std::stringstream sst;
		mark = pattenSub.front();
		if (mark == '-')
		{
			formatter << std::left;
		}
		else
		{
			formatter << std::right;
		}
		if (ind != std::string::npos)
		{
			sst << pattenSub.substr(ind, pattenSub.length());
			sst >> subLength;
			formatter << std::ios::fixed << std::setprecision(subLength);
			sst.clear();
			sst.str("");
			if (mark == '-' || mark == '+' || mark == '#')
			{
				sst << pattenSub.substr(1, ind - 1); // like 5.6
			}
			else
			{
				sst << pattenSub.substr(0, ind);
			}
		}
		else
		{
			sst << pattenSub; // like -5
		}
		if (!sst.str().empty())
		{
			sst >> fullLength;
		}
		update = false;
	}
}

std::string LogLayoutLacation::getResult(const struct LogInfomations &logInfo)
{
	resetFormatter();
	formatter << logInfo.lineNum;
	return logInfo.fileName + "\\"  + ":" + logInfo.methodName + ":\t[" + formatter.str() + "]";
}

std::string LogLayoutDate::getResult(const struct LogInfomations &logInfo)
{
	updateFormat();
	resetFormatter();
	formatter << dateFormatter.formatDate(logInfo.dateAndTime);
	return formatter.str();
}

void LogLayoutDate::updateFormat()
{
	if (update) {
		LogLayoutSub::updateFormat();
		if (patten.back() == '}')
		{
			dateFormatter.setFormat(getBraceExpstd(patten).str());
		}
		else
		{
			dateFormatter.setFormat(DateTime::DateFormat::defaultDateFormat);
		}
		update = false;
	}
}

std::string LogLayoutFile::getResult(const struct LogInfomations &logInfo)
{
	updateFormat();	
	resetFormatter();
	formatter << getLogInfoTokens(logInfo.fileName, spliter, tokenLen);
	return formatter.str();
}

std::string LogLayoutLine::getResult(const struct LogInfomations &logInfo)
{
	updateFormat();
	resetFormatter();
	formatter << logInfo.lineNum;
	return formatter.str();
}

std::string LogLayoutMess::getResult(const struct LogInfomations &logInfo)
{
	updateFormat();
	resetFormatter();
	formatter << logInfo.message;
	return formatter.str();
}


std::string LogLayoutMeth::getResult(const struct LogInfomations &logInfo)
{
	updateFormat();
	resetFormatter();
	formatter << getLogInfoTokens(logInfo.methodName, spliter, tokenLen);
	return formatter.str();
}

std::string LogLayoutProi::getResult(const struct LogInfomations &logInfo)
{
	updateFormat();
	resetFormatter();
	formatter << proitities[logInfo.proitity];
	return formatter.str();
}

std::string LogLayoutMilli::getResult(const struct LogInfomations &logInfo)
{
	updateFormat();
	resetFormatter();
	formatter << logInfo.milliSecond;
	return formatter.str();
}

std::string LogLayoutThread::getResult(const struct LogInfomations &logInfo)
{
	updateFormat();
	resetFormatter();
	formatter << logInfo.threadName;
	return formatter.str();
}

std::string LogLayoutNone::getResult(const struct LogInfomations &logInfo)
{
	return patten;
}

std::string LogLayoutDelim::getResult(const LogInfomations & logInfo)
{
	return std::string();
}

void LogLayoutDelim::updateFormat()
{
	if (update)
	{
		LogLayoutSub::updateFormat();
		if (patten.back() == '}')
		{
			getBraceExpstd(patten) >> tokenLen;
		}
		else
		{
			tokenLen = 0;
		}
		update = false;
	}
}


LogLayout::LogLayout()
{
}

LogLayout::LogLayout(LogLayoutPre logLayPre)
{
	setPatten(logLayPre);
}

LogLayout::LogLayout(const std::string & patt)
{
	setPatten(patt);
}


LogLayout::~LogLayout()
{
	destructVec();
}

void LogLayout::setPatten(const std::string &patt)
{
	patten = patt;
	update = true;
}

void LogLayout::setPatten(LogLayoutPre logLayPre)
{
	switch (logLayPre)
	{
	case LogLayoutPre::HtmlLayout:
	case LogLayoutPre::SimpleLayout:
	case LogLayoutPre::PattenLayout:
		patten = SimpleLayout;
		break;
	case LogLayoutPre::TTCCLayout:
		patten = TTCCLayout;
		break;
	case LogLayoutPre::FULLLayout:
		patten = FULLLayout;
		break;
	default:
		patten = SimpleLayout;
		break;
	}
	update = true;
}

void LogLayout::logLayoutParser()
{
	if (update)
	{
		destructVec();
		auto pos = patten.begin();
		std::string subPatten;
		while (pos != patten.end())
		{
			switch (*pos)
			{
			case '%':
				if (subPatten.size() != 0)
				{
					logLayoutSubs.push_back(new LogLayoutNone(subPatten));
					subPatten.clear();
				}
				try
				{
					logLayoutSubs.push_back(updateFormat(pos, patten.cend()));
				}
				catch (std::invalid_argument &)
				{
				}
				catch (std::exception &)
				{
					std::cerr << "unknown error!" << std::endl;
					exit(1);
				}
				break;
			default:
				subPatten.push_back(*pos);
				++pos;
				break;
			}
		}
		if (subPatten.size() != 0)
		{
			logLayoutSubs.push_back(new LogLayoutNone(subPatten));
		}
		update = false;
	}
}

std::string LogLayout::getResult(const struct LogInfomations &logInfo)
{
	logLayoutParser();
	std::string ret;
	for (auto p = logLayoutSubs.begin(); p != logLayoutSubs.end(); ++p)
	{
		try
		{
			ret += (*p)->getResult(logInfo);
		}
		catch (std::invalid_argument &)
		{

		}
	}
	return ret;
}

LogLayoutSub * LogLayout::updateFormat(std::string::iterator & pos, std::string::const_iterator &end)
{
	std::string patten;
	std::string needReadBrae = "dFIm";
	LogLayoutSub *logLaySub = nullptr;
	bool finished = false;
	patten.push_back(*pos);
	++pos;
	while (pos != end) {
		patten.push_back(*pos);
		if (needReadBrae.find(*pos))
		{
			try
			{
				patten += readBrae(pos, end);
			}
			catch (std::invalid_argument &e)
			{
				throw e;
			}
			catch (std::exception &)
			{
				std::cerr << "unknown error! exiting!" << std::endl;
				exit(1);
			}
		}
		switch (*pos)
		{
		case 'd':
			logLaySub = new LogLayoutDate;
			finished = true;
			break;
		case 'F':
			logLaySub = new LogLayoutFile;
			finished = true;
			break;
		case 'I':
			logLaySub = new LogLayoutLacation;
			finished = true;
			break;
		case 'L':
			logLaySub = new LogLayoutLine;
			finished = true;
			break;
		case 'm':
			logLaySub = new LogLayoutMess;
			finished = true;
			break;
		case 'M':
			logLaySub = new LogLayoutMeth;
			finished = true;
			break;
		case 'n':
			logLaySub = new LogLayoutNone;
			patten = "\r\n";
			finished = true;
			break;
		case 'p':
			logLaySub = new LogLayoutProi;
			finished = true;
			break;
		case 'r':
			logLaySub = new LogLayoutMilli;
			finished = true;
			break;
		case 't':
			logLaySub = new LogLayoutThread;
			break;
		case 'x':
			logLaySub = new LogLayoutNone;
			finished = true;
			break;
		case 'X':
			logLaySub = new LogLayoutNone;
			finished = true;
			break;
		case '%':
			logLaySub = new LogLayoutNone;
			finished = true;
			break;
		default:
			break;
		}
		++pos;
		if (finished == true)
		{
			if (logLaySub == nullptr)
			{
				throw std::invalid_argument("format patten is error, need argument after '%'");
			}
			logLaySub->setPatten(patten);
			break;
		}
	}
	return logLaySub;
}

std::string LogLayout::readBrae(std::string::iterator & pos, std::string::const_iterator & end)
{
	std::string ret;
	if ((pos + 1) != end && *(pos + 1) == '{')
	{
		++pos;
		while (pos != end && *pos != '}')
		{
			ret.push_back(*pos);
			++pos;
		}
		if (pos != end)
		{
			ret.push_back(*pos);
			return std::move(ret);
		}
		else
		{
			throw std::invalid_argument("need '}' after '{'");
		}
	}
	return std::string();
}

void LogLayout::destructVec()
{
	for (auto p = logLayoutSubs.begin(); p != logLayoutSubs.end(); ++p) {
		delete *p;
	}
	logLayoutSubs.clear();
}
