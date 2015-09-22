#include "stdafx.h"
#include "Appender.h"


Appender::Appender()
{
}

Appender::Appender(LogProperties & logProp) : logProperties(logProp)
{
}

void Appender::setLogProp(LogProperties & logProp)
{
	logProperties = logProp;
	iniFinished = false;
}

void Appender::setLogProp()
{
	destructPtr();
	switch (logProperties.logDestination)
	{
	case LogProperties::ConsoleDest:
		logDest = new LogDestConsole;
		break;
	case LogProperties::FileDest:
		logDest = new LogDestFile(logProperties.customizedFileDest);
		break;
	case LogProperties::StreamDest:
		logDest = new LogDestStream(*(logProperties.customizedStreamDest));
	default:
		logDest = new LogDestConsole;
		break;
	}
	if (logProperties.logLayout == LogProperties::PattenLayout)
	{
		logLayout = new LogLayout(logProperties.customizedPatten);
	}
	else
	{
		logLayout = new LogLayout(logProperties.logLayout);
	}
	logProirity = logProperties.logProirity;
	iniFinished = true;
}

LogProperties & Appender::getLogProperties()
{
	iniFinished = false;
	return logProperties;
}

bool Appender::log(const LogInfomations &logInfo)
{
	if (iniFinished == false)
	{
		setLogProp();
	}
	return logDest->pushLog(logLayout->getResult(logInfo));
}


Appender::~Appender()
{
	destructPtr();
}
