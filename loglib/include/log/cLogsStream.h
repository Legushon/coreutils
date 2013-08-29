#ifndef C_LOGS_STREAM_H_INCLUDED
#define C_LOGS_STREAM_H_INCLUDED

#include <sstream>
#include <string>
#include <list>
#include "log/cLogsStorage.h"
//#include "json/json.h"

namespace logger
{
	class cLogsStream
	{
	protected:
		std::string typeStamp_;
		cLogsStorage::eLogType type_;
		std::stringstream buf_;

	public:

	   cLogsStream( cLogsStorage::eLogType logType );
	   ~cLogsStream();

		template< class T> cLogsStream& operator << ( const T &msg )
		{
			buf_ << msg;
			return *this;
		}
	};
	class cNullStream
	{
	public:
	   cNullStream( ) {};
	   ~cNullStream() {};

		template< class T> cNullStream& operator << ( const T &msg )
		{
			return *this;
		}
	};
}

#endif
