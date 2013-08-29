#include <iostream>
#include "log/cLogsStream.h"
#include "log/cSyslogStorage.h"

namespace logger
{
	cLogsStream::cLogsStream( cLogsStorage::eLogType type ) :  type_( type )
	{
	}

	cLogsStream::~cLogsStream()
	{
		cSyslog * tmp = cSyslog::Instance();
		tmp->Register( type_, buf_.str().c_str() );
		tmp->FreeInst();
	}
}
