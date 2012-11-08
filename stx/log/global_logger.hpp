#ifndef STX_LOG_GLOBAL_LOGGER_HPP
#define STX_LOG_GLOBAL_LOGGER_HPP

#include <stx/log/basic_logger.hpp>
#include <stx/log/ostream_logger.hpp>

namespace stx {
namespace detail {

template <class T>
int global_logger_nifty_counter(int x = 0);

template<> int
global_logger_nifty_counter<int>(int x)
{
    static int counter = 0;
    counter += x;
    return counter;
}

template <class T>
T* default_global_logger(T* new_log = NULL, bool destroy = false);

template<> cout_logger*
default_global_logger<cout_logger>(cout_logger* new_log, bool destroy)
{
    static cout_logger* log = NULL;
    if (destroy) {
        if (log) {
            delete log;
            log = NULL;
        }
    }
    if (new_log) {
        log = new_log;
    }
    return log;
}

template <class Logger>
Logger* global_logger(Logger* new_log = NULL);

template<> basic_logger*
global_logger<basic_logger>(basic_logger* new_log)
{
    static basic_logger* log = NULL;
    if (new_log) {
        //  TODO: maybe we need make this reassignment thread-safe
        log = new_log;
    }
    return log;
}

struct global_logger_initializer
{
    global_logger_initializer()
    {
        if (!global_logger_nifty_counter<int>()) {
            //  Create default logger.
            default_global_logger<cout_logger>(new cout_logger);
            //  Initialize global logger with default global logger.
            global_logger<basic_logger>(default_global_logger<cout_logger>());
        }
        global_logger_nifty_counter<int>(1);
    }
    
    ~global_logger_initializer()
    {
        global_logger_nifty_counter<int>(-1);
        if (!global_logger_nifty_counter<int>()) {
            //  Delete default logger.
            default_global_logger<cout_logger>(NULL, true);
        }
    }
};

static global_logger_initializer g_global_logger_initializer;

} // namespace detail
} // namespace stx

#endif // STX_LOG_GLOBAL_LOGGER_HPP
