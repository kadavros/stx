#ifndef STX_LOG_GLOBAL_LOGGER_HPP
#define STX_LOG_GLOBAL_LOGGER_HPP

#include <stx/log/basic_logger.hpp>
#include <stx/log/ostream_logger.hpp>

namespace stx {

template <class Logger>
Logger* global_logger(Logger* new_log = NULL)
{
    static cout_logger log;
    static Logger* plog = &log;
    //static mutex m;
    if (new_log) {
        //lock_guard<mutex> lock(m);
        plog = new_log;
    }
    return plog;
}

//template basic_logger* global_logger(basic_logger* new_log = NULL);

} // namespace stx

#endif // STX_LOG_GLOBAL_LOGGER_HPP
