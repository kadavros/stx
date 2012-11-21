#ifndef STX_LOG_BASIC_LOGGER_HPP
#define STX_LOG_BASIC_LOGGER_HPP

#include <stx/log/abstract_logger.hpp>
#include <stx/log/log_formatter.hpp>
#include <stx/log/date_time.hpp>
#include <stx/log/fake_mutex.hpp>
#include <vector>
#include <algorithm>

namespace stx {

//  TODO
//  wostream supports operator<<() for following types:
//      - const char*
//      - const wchar_t*
//      - std::wstring
//  but not for std::string.
//  May be we could provide operator<<() for std::string via std::string.c_str()
//  function.

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
template <
    class CharType,
    class Mutex = fake_mutex,
    class CharTraits = std::char_traits<CharType>,
    class Allocator = std::allocator<CharType>,
    class Formatter = log_formatter<CharType, CharTraits, Allocator>
>
class basic_logger:
    public abstract_logger<Formatter, CharType, CharTraits, Allocator>
{
public:
    
    typedef abstract_logger<Formatter, CharType, CharTraits, Allocator> abstract_logger_type;
    typedef basic_logger<CharType, CharTraits, Allocator, Formatter> basic_logger_type;
    typedef Formatter formatter_type;
    typedef CharType char_type;
    typedef CharTraits traits_type;
    typedef std::basic_string<CharType, CharTraits, Allocator> string_type;
    typedef std::basic_ostream<CharType, CharTraits> ostream_type;
    typedef std::basic_ostringstream<CharType, CharTraits, Allocator> ostringstream_type;
    typedef Mutex mutex_type;
    
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
    
    bool disabled(int message_level) const
    {
        return !enabled(message_level);
    }
    
    void print_delimiter()
    {
        actual_stream() << delimiter();
    }
    
    virtual ostream_type& stream() = 0;
    
    ostream_type& actual_stream()
    {
        if (has_appended_loggers()) {
            return intermediate_stream();
        } else {
            return stream();
        }
    }
    
    void write_message(abstract_logger_type* message_provider, const string_type& message)
    {
        //  Check for recursive message write.
        if ((abstract_logger_type*) this != message_provider) {
            stream() << message;
            typename std::vector<abstract_logger_type*>::iterator i;
            for (i = appended_loggers_.begin(); i != appended_loggers_.end(); ++i) {
                if ((abstract_logger_type*) *i != message_provider) {
                    (*i)->write_message(message_provider, message);
                }
            }
        }
    }
    
    void start_formatting(int message_level)
    {
        log::local_time<CharType, CharTraits, Allocator> t;
        if (has_appended_loggers()) {
            intermediate_stream_.str(string_type());
        }
        t.print(actual_stream()) << " ";
        actual_stream() << level_to_string(message_level) << " ";
    }
    
    void finish_formatting(Formatter& fmt)
    {
        if (fmt.enabled()) {
            actual_stream() << std::endl;
            if (has_appended_loggers()) {
                //stream() << intermediate_stream().rdbuf();
                stream() << intermediate_stream().str();
                typename std::vector<abstract_logger_type*>::iterator i;
                for (i = appended_loggers_.begin(); i != appended_loggers_.end(); ++i) {
                    //ntermediate_stream().rdbuf();
                    (*i)->write_message((abstract_logger_type*) this, intermediate_stream().str());
                }
            }
        }
    }
    
    //  Additional methods, not included in abstract_logger.
    
    void append(abstract_logger_type& _log)
    {
        appended_loggers_.push_back(&_log);
    }
    
    void remove_all()
    {
        appended_loggers_.clear();
    }
    
    void remove(abstract_logger_type& _log)
    {
        appended_loggers_.erase(std::remove(appended_loggers_.begin(),
            appended_loggers_.end(), &_log), appended_loggers_.end());
    }
    
    bool has_appended_loggers()
    {
        return !appended_loggers_.empty();
    }
    
    ostringstream_type& intermediate_stream()
    {
        return intermediate_stream_;
    }
    
protected:
    
    int level_;
    string_type delimiter_;
    std::vector<abstract_logger_type*> appended_loggers_;
    ostringstream_type intermediate_stream_;
    mutex_type mutex_;
};

typedef basic_logger<char> logger;
typedef basic_logger<wchar_t> wlogger;

} // namespace stx

#endif // STX_LOG_BASIC_LOGGER_HPP
