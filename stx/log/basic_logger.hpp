#ifndef STX_LOG_BASIC_LOGGER_HPP
#define STX_LOG_BASIC_LOGGER_HPP

#include <stx/log/abstract_logger.hpp>
#include <stx/log/log_formatter.hpp>
#include <stx/log/date_time.hpp>

namespace stx {

enum {
    log_level_all = 0,
    log_level_trace,
    log_level_debug,
    log_level_info,
    log_level_warn,
    log_level_error,
    log_level_fatal,
    log_level_none = 255
};

//  Basic logger - includes all interface functions except stream() -
//  it must be implemented in derived classes.
class basic_logger: public abstract_logger<log_formatter>
{
public:
    
    basic_logger(
        const std::string& delimiter = "",
        int log_level = log_level_all):
            level_(log_level),
            delimiter_(delimiter)
    {
    }
    
    basic_logger(const basic_logger& log)
    {
        level_ = log.level_;
        delimiter_ = log.delimiter_;
    }
    
    log_formatter log(int message_level)
    {
        if (enabled(message_level)) {
            start_formatting(message_level);
        }
        return log_formatter(*this, enabled(message_level));
    }
    
    log_formatter trace()
    {
        return log(log_level_trace);
    }
    
    log_formatter debug()
    {
        return log(log_level_debug);
    }
    
    log_formatter info()
    {
        return log(log_level_info);
    }
    
    log_formatter warn()
    {
        return log(log_level_warn);
    }
    
    log_formatter error()
    {
        return log(log_level_error);
    }
    
    log_formatter fatal()
    {
        return log(log_level_fatal);
    }
    
    int level() const
    {
        return level_;
    }
    
    basic_logger& set_level(int new_level)
    {
        level_ = new_level;
        return *this;
    }
    
    std::string delimiter() const
    {
        return delimiter_;
    }
    
    basic_logger& set_delimiter(const std::string& s)
    {
        delimiter_ = s;
        return *this;
    }
    
    const char* level_to_string(int message_level) const
    {
        const char* p = "UNKNOWN";
        switch (message_level) {
        case log_level_trace: p = "TRACE"; break;
        case log_level_debug: p = "DEBUG"; break;
        case log_level_info:  p = "INFO "; break;
        case log_level_warn:  p = "WARN "; break;
        case log_level_error: p = "ERROR"; break;
        case log_level_fatal: p = "FATAL"; break;
        }
        return p;
    }
    
    bool enabled(int message_level) const
    {
        return (message_level >= level());
    }
    
    void print_delimiter()
    {
        stream() << delimiter();
    }
    
    //virtual std::ostream& stream() = 0;
    
    void start_formatting(int message_level)
    {
        log::local_time lt;
        lt.print(stream()) << " ";
        stream() << level_to_string(message_level) << " ";
    }
    
    void finish_formatting(log_formatter& fmt)
    {
        if (fmt.enabled()) {
            stream() << std::endl;
        }
    }
    
protected:
    
    int level_;
    std::string delimiter_;
};

} // namespace stx

#endif // STX_LOG_BASIC_LOGGER_HPP
