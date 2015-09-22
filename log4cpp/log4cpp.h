#pragma once
#include "myLog.h"

#define logDEBUG(message) logIDEBUG(__FILE__, __FUNCTION__, __LINE__, getTime(), LogProperties::LogProirity::logDEBUG, message)

#define logERROR(message) logIDEBUG(__FILE__, __FUNCTION__, __LINE__, getTime(), LogProperties::LogProirity::logERROR, message)

#define logWARN(message) logIDEBUG(__FILE__, __FUNCTION__, __LINE__, getTime(), LogProperties::LogProirity::logWARN, message)

#define logINFO(message) logIDEBUG(__FILE__, __FUNCTION__, __LINE__, getTime(), LogProperties::LogProirity::logINFO, message)