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

template <class CharType>
inline const CharType* g_level_to_string(int level);

template <>
inline const char* g_level_to_string<char>(int level)
{
    const char* p = "UNKNOWN";
    switch (level) {
    case log_level_trace: p = "TRACE"; break;
    case log_level_debug: p = "DEBUG"; break;
    case log_level_info:  p = "INFO "; break;
    case log_level_warn:  p = "WARN "; break;
    case log_level_error: p = "ERROR"; break;
    case log_level_fatal: p = "FATAL"; break;
    }
    return p;
}

template <>
inline const wchar_t* g_level_to_string<wchar_t>(int level)
{
    const wchar_t* p = L"UNKNOWN";
    switch (level) {
    case log_level_trace: p = L"TRACE"; break;
    case log_level_debug: p = L"DEBUG"; break;
    case log_level_info:  p = L"INFO "; break;
    case log_level_warn:  p = L"WARN "; break;
    case log_level_error: p = L"ERROR"; break;
    case log_level_fatal: p = L"FATAL"; break;
    }
    return p;
}

//  Basic logger - includes all interface functions except stream() -
//  it must be implemented in derived classes.
template <
    class CharType,
    class CharTraits = std::char_traits<CharType>,
    class Allocator = std::allocator<CharType>,
    class Formatter = log_formatter<CharType, CharTraits, Allocator>
>
class basic_logger:
    public abstract_logger<Formatter, CharType, CharTraits, Allocator>
{
public:
    
    typedef abstract_logger<Formatter, CharType, CharTraits, Allocator> abstract_logger_type;
    typedef CharType char_type;
    typedef std::basic_string<CharType, CharTraits, Allocator> string_type;
    typedef std::basic_ostream<CharType, CharTraits> ostream_type;
    typedef basic_logger<CharType, CharTraits, Allocator, Formatter> basic_logger_type;
    
    basic_logger(int log_level = log_level_all): level_(log_level)
    {
    }
    
    basic_logger(const basic_logger& log)
    {
        level_ = log.level_;
        delimiter_ = log.delimiter_;
    }
    
    Formatter log(int message_level)
    {
        if (enabled(message_level)) {
            start_formatting(message_level);
        }
        return Formatter(*this, enabled(message_level));
    }
    
    Formatter trace()
    {
        return log(log_level_trace);
    }
    
    Formatter debug()
    {
        return log(log_level_debug);
    }
    
    Formatter info()
    {
        return log(log_level_info);
    }
    
    Formatter warn()
    {
        return log(log_level_warn);
    }
    
    Formatter error()
    {
        return log(log_level_error);
    }
    
    Formatter fatal()
    {
        return log(log_level_fatal);
    }
    
    int level() const
    {
        return level_;
    }
    
    void set_level(int new_level)
    {
        level_ = new_level;
    }
    
    string_type delimiter() const
    {
        return delimiter_;
    }
    
    void set_delimiter(const string_type& s)
    {
        delimiter_ = s;
    }
    
    string_type level_to_string(int message_level) const
    {
        return string_type(g_level_to_string<char_type>(message_level));
    }
    
    bool enabled(int message_level) const
    {
        return (message_level >= level());
    }
    
    void print_delimiter()
    {
        stream() << delimiter();
    }
    
    virtual ostream_type& stream() = 0;
    
    void start_formatting(int message_level)
    {
        log::local_time<CharType, CharTraits, Allocator> lt;
        lt.print(stream()) << " ";
        stream() << level_to_string(message_level) << " ";
    }
    
    void finish_formatting(Formatter& fmt)
    {
        if (fmt.enabled()) {
            stream() << std::endl;
        }
    }
    
protected:
    
    int level_;
    string_type delimiter_;
};

typedef basic_logger<char> logger;
typedef basic_logger<wchar_t> wlogger;

} // namespace stx

#endif // STX_LOG_BASIC_LOGGER_HPP
