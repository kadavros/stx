#ifndef STX_LOG_OSTREAM_LOGGER_HPP
#define STX_LOG_OSTREAM_LOGGER_HPP

#include <stx/log/basic_logger.hpp>

namespace stx {

template<std::ostream& explicit_ostream>
class ostream_logger: public basic_logger
{
public:
    
    ostream_logger(
        const std::string& delimiter = "",
        int log_level = log_level_all):
            basic_logger(delimiter, log_level)
    {
    }
    
    std::ostream& stream()
    {
        return explicit_ostream;
    }
};

// std::cout based logger
typedef ostream_logger<std::cout> cout_logger;

// std::clog based logger
typedef ostream_logger<std::clog> clog_logger;

} // namespace stx

#endif // STX_LOG_OSTREAM_LOGGER_HPP
