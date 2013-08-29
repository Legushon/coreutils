#ifndef C_SYSLOG_STORAGE_H
#define C_SYSLOG_STORAGE_H

#include "cLogsStorage.h"
#include "singleton.h"
#include <syslog.h>
namespace logger
{
	class cSyslogStorage : public cLogsStorage, public cSingleton< cSyslogStorage >
	{
		protected:
			static std::string logName_;

		public:
			cSyslogStorage();
			virtual ~cSyslogStorage();

			virtual bool Register( eLogType msgType, const char * const msg );
			static void SetName( const std::string &name )
			{
				closelog();
				openlog( name.c_str(), LOG_NDELAY | LOG_PID, LOG_LOCAL0 );
				logName_ = name;
			};
	};
	typedef cSyslogStorage cSyslog;
}


#endif
