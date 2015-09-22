/*
this is a class for get date and time, and then you can format it.
the format expression are the same as java.
*/



#pragma once
#include <ctime>
#include <sys/timeb.h>
#include <time.h>
#include <string>
#include <sstream>
#include <vector>
#include <exception>
#include <ios>
#include <iomanip>
#include <memory>

class DateTime
{
public:
	DateTime();
	DateTime(const _timeb &timebuffer);
	DateTime(const DateTime &lhs) : dateAndTime(lhs.dateAndTime), timebuffer(lhs.timebuffer), milliSecond(lhs.milliSecond), updateFlag(lhs.updateFlag), myDateFormat(DateFormat())
	{
	}
	~DateTime();
	void mark()
	{
		// mark to record a time;
		_ftime_s(&timebuffer);
		updateFlag = true;
	}
	void setFormate(const std::string &dateFormat)
	{
		myDateFormat.setFormat(dateFormat);
	}
	std::string FormatDate(const std::string &dateFormat);
	std::string FormatDate();
	unsigned long long diffInMilliSec(const DateTime &other)
	{
		updateTime();
		return timebuffer.time * 1000 + timebuffer.millitm - other.timebuffer.time * 1000 - other.timebuffer.millitm;
	}
	unsigned long long diffInSecond(const DateTime &other)
	{
		updateTime();
		return timebuffer.time - other.timebuffer.time;
	}
private:
	struct _timeb timebuffer;
	struct std::tm dateAndTime;
	unsigned milliSecond;
	bool updateFlag = false; //flag for update time

	void updateTime()
	{
		// update time mean to translate time to localtime and get millisecond
		if (updateFlag)
		{
			localtime_s(&dateAndTime, &timebuffer.time);
			milliSecond = timebuffer.millitm;
			updateFlag = false;
		}
	}

private:
	class numberSub {
	public:
		numberSub() {};
		~numberSub() {};
		std::string getResult(const unsigned &val)
		{
			resetFormatter();
			formatter << val;
			return formatter.str();
		}
		void setPatten(char fill, std::size_t len)
		{
			this->fill = fill;
			fullLength = len;
			formatter << std::setfill(fill);
		}
	private:
		std::stringstream formatter;
		std::size_t fullLength;
		char fill;
		void resetFormatter()
		{
			formatter.str("");
			formatter.clear();
			formatter << std::setw(fullLength);
		}

	};

	class DateFormatSub
	{
	public:
		DateFormatSub() {};
		DateFormatSub(const std::string &patt) : patten(patt)
		{
			numSub.setPatten('0', patten.length());
		}
		virtual ~DateFormatSub() {};
		virtual std::string getResult(const struct std::tm &dateAndTime, const unsigned &milliSec)
		{
			return std::string();
		}
	protected:
		numberSub numSub;
		std::string patten;
	};

	class YdaySub : public DateFormatSub
	{
	public:
		YdaySub() {};
		YdaySub(const std::string &patt) : DateFormatSub(patt) {}
		virtual std::string getResult(const struct std::tm &dateAndTime, const unsigned &milliSec)
		{
			return std::move(numSub.getResult(dateAndTime.tm_yday));
		}
	};

	class MdaySub : public DateFormatSub
	{
	public:
		MdaySub() {};
		MdaySub(const std::string &patt) : DateFormatSub(patt) {}
		virtual std::string getResult(const struct std::tm &dateAndTime, const unsigned &milliSec)
		{
			return std::move(numSub.getResult(dateAndTime.tm_mday));
		}
	};

	class HourSub : public DateFormatSub
	{
	public:
		HourSub() {};
		HourSub(const std::string &patt) : DateFormatSub(patt) {}
		virtual std::string getResult(const struct std::tm &dateAndTime, const unsigned &milliSec)
		{
			return std::move(numSub.getResult(dateAndTime.tm_hour));
		}
	};

	class KhourSub : public DateFormatSub
	{
	public:
		KhourSub() {};
		KhourSub(const std::string &patt) : DateFormatSub(patt) {}
		virtual std::string getResult(const struct std::tm &dateAndTime, const unsigned &milliSec)
		{
			return std::move(numSub.getResult(dateAndTime.tm_hour % 12));
		}
	};

	class MinuteSub : public DateFormatSub
	{
	public:
		MinuteSub() {};
		MinuteSub(const std::string &patt) : DateFormatSub(patt) {}
		virtual std::string getResult(const struct std::tm &dateAndTime, const unsigned &milliSec)
		{
			return std::move(numSub.getResult(dateAndTime.tm_min));
		}
	};

	class SecondSub : public DateFormatSub
	{
	public:
		SecondSub() {};
		SecondSub(const std::string &patt) : DateFormatSub(patt) {}
		virtual std::string getResult(const struct std::tm &dateAndTime, const unsigned &milliSec)
		{
			return std::move(numSub.getResult(dateAndTime.tm_sec));
		}
	};

	class milliSecondSub : public DateFormatSub
	{
	public:
		milliSecondSub() {};
		milliSecondSub(const std::string &patt) : DateFormatSub(patt) {}
		virtual std::string getResult(const struct std::tm &dateAndTime, const unsigned &milliSec)
		{
			return std::move(numSub.getResult(milliSec));
		}
	};

	class WdaySub : public DateFormatSub
	{
	public:
		WdaySub() {};
		WdaySub(const std::string &patt) : DateFormatSub(patt) {}
		virtual std::string getResult(const struct std::tm &dateAndTime, const unsigned &milliSec)
		{
			return std::move(numSub.getResult((dateAndTime.tm_wday + 13) % 7 + 1));
		}
	};

	class MonthSub : public DateFormatSub
	{
	public:
		MonthSub() {};
		MonthSub(const std::string &patt) : DateFormatSub(patt) {}
		virtual std::string getResult(const struct std::tm &dateAndTime, const unsigned &milliSec)
		{
			if (patten.length() <= 2)
			{
				return std::move(numSub.getResult(dateAndTime.tm_mon + 1));
			}
			else if (patten.length() == 3)
			{
				return MONTH_NAME[dateAndTime.tm_mon].substr(0, 3);
			}
			else
			{
				return MONTH_NAME[dateAndTime.tm_mon];
			}
		}
	private:
		const std::string MONTH_NAME[12] = {
			"January",
			"February",
			"March",
			"April",
			"May",
			"June",
			"July",
			"August",
			"September",
			"October",
			"November",
			"December"
		};
	};

	class YearSub : public DateFormatSub
	{
	public:
		YearSub() {};
		YearSub(const std::string &patt) : DateFormatSub(patt) {}
		virtual std::string getResult(const struct std::tm &dateAndTime, const unsigned &milliSec)
		{
			auto year = numSub.getResult(dateAndTime.tm_year + 1900);
			if (patten.length() == 2)
			{
				return year.substr(year.length() - 2, 2);
			}
			else
			{
				return std::move(year);
			}
		}
	};

	class WeekSub : public DateFormatSub
	{
	public:
		WeekSub() {};
		WeekSub(const std::string &patt) : DateFormatSub(patt) {}
		virtual std::string getResult(const struct std::tm &dateAndTime, const unsigned &milliSec)
		{
			if (patten.length() <= 2)
			{
				return std::move(numSub.getResult(dateAndTime.tm_wday));
			}
			else if (patten.length() == 3)
			{
				return WEEK_NAME[dateAndTime.tm_wday].substr(0, 3);
			}
			else
			{
				return WEEK_NAME[dateAndTime.tm_wday];
			}
		}
	private:
		const std::string WEEK_NAME[7] = {
			"Sunday",
			"Monday",
			"Tuesday",
			"Wednesday",
			"Thursday",
			"Friday",
			"Saturday"
		};
	};

	class AMSub : public DateFormatSub
	{
	public:
		AMSub() {};
		AMSub(const std::string &patt) : DateFormatSub(patt) {}
		virtual std::string getResult(const struct std::tm &dateAndTime, const unsigned &milliSec)
		{
			if (dateAndTime.tm_hour < 12)
			{
				return "AM";
			}
			else
			{
				return "PM";
			}
		}
	};

	class CommentSub : public DateFormatSub
	{
	public:
		CommentSub() {};
		CommentSub(const std::string &patt) : DateFormatSub(patt) {}
		virtual std::string getResult(const struct std::tm &dateAndTime, const unsigned &milliSec)
		{
			return patten;
		}
	};
	//std::string dateFormat = "dd-MMM-yyyy EEE HH:mm:ss";
public:
	class DateFormat {
		public:
			DateFormat() {};
			DateFormat(const std::string &dateF)
			{
				setFormat(dateF);
			}
			void setFormat(const std::string &dateF);
			~DateFormat() {};
			std::string getResult(const std::tm &dateAndTime, const unsigned &milliSecond);
			std::string formatDate(const DateTime &datetime);
			static std::string defaultDateFormat;
		private:
			std::string dateFormat = defaultDateFormat;
			std::vector<std::unique_ptr<DateFormatSub>> dateFormateSubs;

			int DateTime::DateFormat::countLetter(std::string::iterator beg, std::string::const_iterator & end, char letter);
			void parserDateFormat();
			//std::string dayFormat = "dd";
			/*
			Number
			d : day in month
			D : day in year
			*/
			//std::string monthFormat = "MM";
			/*
			Month
			M : month in year
			*/
			//std::string yearFormat = "yyyy";
			/*
			Year
			y : year
			*/
			//std::string hourFormat = "HH";
			/*
			Number
			H : hour in day(0-23)
			K : hour in am/pm(0-11)
			*/
			//std::string minuteFormat = "mm";
			/*
			Number
			m : minute in hour
			*/
			//std::string secondFormat = "SS";
			/*
			Number
			s : second in minute
			*/
			//std::string millisecondFormat = "SSS";
			/*
			Number
			S£º millisecond
			*/
			//std::string weekFormat = "EEE";
			/*
			Number and Text
			E : day name in week
			u : day index of week (1-7)
			F : day of week in month
			w : week in year
			*/
			//std::string amPmMarker = "a";
			/*
			Text
			a : am/pm marker
			*/

		};
private:
	DateFormat myDateFormat;
};

