#ifndef STX_LOG_GLOBAL_LOGGER_HPP
#define STX_LOG_GLOBAL_LOGGER_HPP

#include <stx/log/basic_logger.hpp>
#include <stx/log/ostream_logger.hpp>
#include <iostream>

namespace stx {

namespace detail {

template <class T> T& cout_logger();
template <> ostream_logger& cout_logger<ostream_logger>()
{
    static ostream_logger logger(std::cout);
    return logger;
}

template <class T> T& wcout_logger();
template <> wostream_logger& wcout_logger<wostream_logger>()
{
    static wostream_logger logger(std::wcout);
    return logger;
}

template <class T> T& clog_logger();
template <> ostream_logger& clog_logger<ostream_logger>()
{
    static ostream_logger logger(std::clog);
    return logger;
}

template <class T> T& wclog_logger();
template <> wostream_logger& wclog_logger<wostream_logger>()
{
    static wostream_logger logger(std::wclog);
    return logger;
}

template <class T> int global_logger_nifty_counter(int x = 0);
template<> int global_logger_nifty_counter<int>(int x)
{
    static int counter = 0;
    counter += x;
    return counter;
}

template <class Logger>
Logger& global_logger(Logger* new_log = NULL);

template<> logger&
global_logger<logger>(logger* new_log)
{
    //  We can't just make assignment log = &_log, because in this case
    //  probably some compilers may optimize away call to
    //  global_logger<basic_logger>() in global_logger_initializer
    //  constructor, which is for sure incorrect - because
    //  first call to this function should call default_global_logger
    //  constructor.
    static logger* log = NULL;
    if (!log) {
        log = &cout_logger<ostream_logger>();
    }
    if (new_log) {
        //  TODO: maybe we should make this reassignment thread-safe
        log = new_log;
    }
    return *log;
}

struct global_logger_initializer
{
    global_logger_initializer()
    {
        if (!global_logger_nifty_counter<int>()) {
            // Initialize global loggers.
            cout_logger<ostream_logger>();
            wcout_logger<wostream_logger>();
            clog_logger<ostream_logger>();
            wclog_logger<wostream_logger>();
            global_logger<logger>((logger*) NULL);
        }
        global_logger_nifty_counter<int>(1);
    }
};

static global_logger_initializer g_global_logger_initializer;

} // namespace detail

inline ostream_logger& cout_logger()
{
    return detail::cout_logger<ostream_logger>();
}

inline wostream_logger& wcout_logger()
{
    return detail::wcout_logger<wostream_logger>();
}

inline ostream_logger& clog_logger()
{
    return detail::clog_logger<ostream_logger>();
}

inline wostream_logger& wclog_logger()
{
    return detail::wclog_logger<wostream_logger>();
}

} // namespace stx

#endif // STX_LOG_GLOBAL_LOGGER_HPP
