#ifndef STX_LOG_HPP
#define STX_LOG_HPP

#define STX_LOG_TRACE(x) if (log_level_trace >= get_logger().level()) { get_logger().trace() << x; }
#define STX_LOG_DEBUG(x) if (log_level_debug >= get_logger().level()) { get_logger().debug() << x; }
#define STX_LOG_INFO(x)  if (log_level_info  >= get_logger().level()) { get_logger().info()  << x; }
#define STX_LOG_WARN(x)  if (log_level_warn  >= get_logger().level()) { get_logger().warn()  << x; }
#define STX_LOG_ERROR(x) if (log_level_error >= get_logger().level()) { get_logger().error() << x; }
#define STX_LOG_FATAL(x) if (log_level_fatal >= get_logger().level()) { get_logger().fatal() << x; }

#ifdef STX_NO_MACRO_PREFIX
#   define LOG_TRACE STX_LOG_TRACE
#   define LOG_DEBUG STX_LOG_DEBUG
#   define LOG_INFO  STX_LOG_INFO
#   define LOG_WARN  STX_LOG_WARN
#   define LOG_ERROR STX_LOG_ERROR
#   define LOG_FATAL STX_LOG_FATAL
#endif

#include <stx/log/abstract_logger.hpp>
#include <stx/log/basic_logger.hpp>
#include <stx/log/ostream_logger.hpp>
#include <stx/log/file_logger.hpp>
#include <stx/log/rolling_file_logger.hpp>
#include <stx/log/global_logger.hpp>

#ifdef STX_PLATFORM_UNIX
// TODO
// Is there any trustworthy way to determine presense of syslog api at macro level?
//#ifdef STX_HAS_SYSLOG
#include <stx/log/syslog_logger.hpp>
//#endif // STX_HAS_SYSLOG
#endif

//  Log level constants are defined in <stx/log/basic_logger.hpp> file.
//  Available ready-to-use logger classes:
//      class file_logger;
//      class rolling_file_logger;
//      class ostream_logger;
//      class syslog_logger;
//  And wide char analogs:
//      class wfile_logger;
//      class wrolling_file_logger;
//      class wostream_logger;

//  Functions get_logger() and set_logger() should not be defined only in
//  namespace stx in order to let users provide their own implementations
//  inside their classes to override default log facilities.

namespace stx {

inline logger& get_logger()
{
    return detail::global_logger<logger>();
}

inline void set_logger(logger& log)
{
    detail::global_logger<logger>(&log);
}

} // namespace stx

using stx::get_logger;
using stx::set_logger;

#endif // STX_LOG_HPP