#ifndef STX_LOG_HPP
#define STX_LOG_HPP

#define STX_LOG(level) if (get_logger().disabled(level)); else get_logger().log_message(level)
#define STX_LOG_TRACE  STX_LOG(stx::log_level_trace)
#define STX_LOG_DEBUG  STX_LOG(stx::log_level_debug)
#define STX_LOG_INFO   STX_LOG(stx::log_level_info)
#define STX_LOG_WARN   STX_LOG(stx::log_level_warn)
#define STX_LOG_ERROR  STX_LOG(stx::log_level_error)
#define STX_LOG_FATAL  STX_LOG(stx::log_level_fatal)

//  Warning: some of those short macros conflict with syslog macros.
#ifdef STX_NO_MACRO_PREFIX
#   define log_msg     STX_LOG
#   define log_trace   STX_LOG_TRACE
#   define log_debug   STX_LOG_DEBUG
#   define log_info    STX_LOG_INFO
#   define log_warn    STX_LOG_WARN
#   define log_error   STX_LOG_ERROR
#   define log_fatal   STX_LOG_FATAL
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
    return detail::global_logger<logger>((logger*) NULL);
}

inline void set_logger(logger& log)
{
    detail::global_logger<logger>(&log);
}

} // namespace stx

using stx::get_logger;
using stx::set_logger;

#endif // STX_LOG_HPP
