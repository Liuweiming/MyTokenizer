#include "stdafx.h"
#include "DateTime.h"

#include <cassert>
DateTime::DateTime()
{
	mark();
	updateTime();
}

DateTime::DateTime(const _timeb & timebuffer) : timebuffer(timebuffer)
{
	updateTime();
}



DateTime::~DateTime()
{
}

std::string DateTime::FormatDate(const std::string & dateFormat)
{
	updateTime();
	myDateFormat.setFormat(dateFormat);
	return myDateFormat.getResult(dateAndTime, milliSecond);
}

std::string DateTime::FormatDate()
{
	updateTime();
	return myDateFormat.getResult(dateAndTime, milliSecond);
}


std::string DateTime::DateFormat::defaultDateFormat = "dd-MM-yyyy HH:mm:ss";

int DateTime::DateFormat::countLetter(std::string::iterator beg, std::string::const_iterator & end, char letter)
{
	int letterCount = 0;
	while (beg != end && *beg == letter) {
		++letterCount;
		++beg;
	}
	return letterCount;
}

void DateTime::DateFormat::setFormat(const std::string & dateF)
{
	dateFormat = dateF;
	dateFormateSubs.clear();
	try
	{
		parserDateFormat();
	}
	catch (std::invalid_argument)
	{
		dateFormat = defaultDateFormat;
		try
		{
			parserDateFormat();
		}
		catch (std::exception &e)
		{
			std::printf("unknow error!");
			throw e;
		}
	}
	catch (std::exception &e)
	{
		std::printf("unknow error!");
		throw e;
	}
}

std::string DateTime::DateFormat::getResult(const std::tm &dateAndTime, const unsigned &milliSecond)
{
	std::string ret;
	for (auto &p : dateFormateSubs)
	{
		
		ret += p->getResult(dateAndTime, milliSecond);
	}
	return std::move(ret);
}

std::string DateTime::DateFormat::formatDate(const DateTime & datetime)
{
	return getResult(datetime.dateAndTime, datetime.milliSecond);
}

void DateTime::DateFormat::parserDateFormat()
{
	auto pos = dateFormat.begin();
	std::string comment;
	int count = 0;
	std::string patt = "dDMyHKmsSEua";
	while (pos != dateFormat.end())
	{
		
		if (patt.find(*pos) != patt.npos)
		{
			count = countLetter(pos, dateFormat.cend(), *pos);
			assert(count > 0);
			if (!comment.empty())
			{
				dateFormateSubs.push_back(std::unique_ptr<DateFormatSub>(new CommentSub(comment)));
				comment.clear();
			}
		}
		else
		{
			count = 1;
		}
		switch (*pos)
		{
		case 'd': 
			dateFormateSubs.push_back(std::unique_ptr<DateFormatSub>(new MdaySub(std::string(pos, pos + count))));
			break;
		case 'D':
			dateFormateSubs.push_back(std::unique_ptr<DateFormatSub>(new YdaySub(std::string(pos, pos + count))));
			break;
		case 'M':
			dateFormateSubs.push_back(std::unique_ptr<DateFormatSub>(new MonthSub(std::string(pos, pos + count))));
			break;
		case 'y':
			dateFormateSubs.push_back(std::unique_ptr<DateFormatSub>(new YearSub(std::string(pos, pos + count))));
			break;
		case 'H':
			dateFormateSubs.push_back(std::unique_ptr<DateFormatSub>(new HourSub(std::string(pos, pos + count))));
			break;
		case 'K':
			dateFormateSubs.push_back(std::unique_ptr<DateFormatSub>(new KhourSub(std::string(pos, pos + count))));
			break;
		case 'm':
			dateFormateSubs.push_back(std::unique_ptr<DateFormatSub>(new MinuteSub(std::string(pos, pos + count))));
			break;
		case 's':
			dateFormateSubs.push_back(std::unique_ptr<DateFormatSub>(new SecondSub(std::string(pos, pos + count))));
			break;
		case 'S':
			dateFormateSubs.push_back(std::unique_ptr<DateFormatSub>(new milliSecondSub(std::string(pos, pos + count))));
			break;
		case 'E':
			dateFormateSubs.push_back(std::unique_ptr<DateFormatSub>(new WeekSub(std::string(pos, pos + count))));
			break;
		case 'u':
			dateFormateSubs.push_back(std::unique_ptr<DateFormatSub>(new WdaySub(std::string(pos, pos + count))));
			break;
		case 'F':
			break;
		case 'w':
			break;
		case 'a':
			dateFormateSubs.push_back(std::unique_ptr<DateFormatSub>(new AMSub(std::string(pos, pos + count))));
			break;
		case '\'':
			++pos;
			while (pos != dateFormat.end() && *pos != '\'')
			{
				comment.push_back(*pos);
				++pos;
			}
			if (pos == dateFormat.end())
			{
				throw std::invalid_argument("need '\''");
			}
			dateFormateSubs.push_back(std::unique_ptr<DateFormatSub>(new CommentSub(comment)));
			comment.clear();
			break;
		default:
			comment.push_back(*pos);
			break;
		}
		pos += count;
	}
	if (!comment.empty())
	{
		dateFormateSubs.push_back(std::unique_ptr<DateFormatSub>(new CommentSub(comment)));
		comment.clear();
	}
}