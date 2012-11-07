#ifndef STX_LOG_HPP
#define STX_LOG_HPP

#define STX_LOG_TRACE(x) get_logger().trace() << x
#define STX_LOG_DEBUG(x) get_logger().debug() << x
#define STX_LOG_INFO(x)  get_logger().info()  << x
#define STX_LOG_WARN(x)  get_logger().warn()  << x
#define STX_LOG_ERROR(x) get_logger().error() << x
#define STX_LOG_FATAL(x) get_logger().fatal() << x

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
#include <stx/log/syslog_logger.hpp>
#include <stx/log/global_logger.hpp>

//  Log level constants are defined in <stx/log/basic_logger.hpp> file.
//  Available ready-to-use logger classes:
//      class cout_logger;
//      class clog_logger;
//      class file_logger;
//      class rolling_file_logger;
//      class syslog_logger;

//  Functions get_logger() and set_logger() should not be defined only in
//  namespace stx in order to let users provide their own implementations
//  inside their classes to override default log facilities.

namespace stx {

inline basic_logger& get_logger()
{
    return *global_logger<basic_logger>();
}

inline void set_logger(basic_logger& log)
{
    global_logger<basic_logger>(&log);
}

} // namespace stx

using stx::get_logger;
using stx::set_logger;

#endif // STX_LOG_HPP
