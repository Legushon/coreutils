#include <syslog.h>
#include <iostream>
#include "log/cSyslogStorage.h"

using namespace std;
#ifndef LOGNAME
#define LOGNAME "heavens"
#endif
namespace logger
{
	std::string cSyslogStorage::logName_ = LOGNAME;

	cSyslogStorage::cSyslogStorage()
	{
		openlog( logName_.c_str(), LOG_NDELAY | LOG_PID, LOG_LOCAL0 );
	}

	cSyslogStorage::~cSyslogStorage()
	{
		closelog();
	}

	bool cSyslogStorage::Register( eLogType msgType, const char * const msg )
	{
		syslog( msgType, "%s",msg );
		return true;
	}
}
