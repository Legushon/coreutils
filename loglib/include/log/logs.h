#ifndef LOGS_H_HEADER
#define LOGS_H_HEADER

#include <boost/format.hpp>
#include "log/cLogsStream.h"

namespace logger
{
	class Formatter
	{
	public:
		template < class ParamType1, class ... ParamTypeN >
		static const boost::format Format( ParamType1 format, ParamTypeN ... paramn )
		{
			Formatter formatter(format);
			return formatter.AddParam(paramn ...);
		}
	private:
		boost::format format_;
		Formatter( const std::string & format )
		:	format_(format)
		{
			// LOG(...) will not throw exceptions 
			format_.exceptions( boost::io::no_error_bits );
		}
		const boost::format & AddParam()
		{
			return format_;
		}

		template < class ParamType1, class ... ParamTypeN >
		const boost::format AddParam( ParamType1 param1, ParamTypeN ... paramn )
		{
			format_ = format_ % param1;
			return AddParam( paramn ... );
		}
	};
}

#ifndef __DEBUG__
	#define CUSTOM_LOG_DEBUG( ... ) 
#else
	#define CUSTOM_LOG_DEBUG( ... )\
		logger::cLogsStream(logger::cLogsStorage::DEBUG)  << __func__ << "( " << __FILE__ << ": " << __LINE__ << " ) # " << logger::Formatter::Format(__VA_ARGS__)
#endif

#define CUSTOM_LOG_ERROR(...)\
	logger::cLogsStream(logger::cLogsStorage::ERROR) << __func__ << "( " << __FILE__ << ": " << __LINE__ << " ) # " << logger::Formatter::Format(__VA_ARGS__)

#define CUSTOM_LOG_INFO(...)\
	logger::cLogsStream(logger::cLogsStorage::INFO) << logger::Formatter::Format(__VA_ARGS__)

#define LOG(loglevel, ...) CUSTOM_##loglevel( __VA_ARGS__ )
#define LOG_IF(condition, loglevel, ...)\
	if (condition) CUSTOM_##loglevel( __VA_ARGS__ )
#endif
