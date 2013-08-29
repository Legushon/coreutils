#ifndef C_LOG_STORAGE_H_INCLUDED
#define C_LOG_STORAGE_H_INCLUDED

#include <string>
#include <syslog.h>

namespace logger
{
	class cLogsStorage
	{
		public:
			enum eLogType { INFO = 6, DEBUG = 7, ERROR = 3, USER = LOG_NOTICE };

		protected:
			std::string sourceName_;

		public:
			cLogsStorage() {};
			virtual ~cLogsStorage() {};

			virtual void SetSourceName( const std::string &name )
			{
				sourceName_ = name;
			};

			const std::string& GetSourceName() const
			{
				return sourceName_;
			};

			virtual bool Register( eLogType msgType, const std::string &msg )
			{
				return Register( msgType, msg.c_str() );
			};

			virtual bool Register( eLogType msgType, const char *msg ) = 0;
	};
}

#endif
