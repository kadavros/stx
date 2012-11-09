#ifndef STX_LOG_ABSTRACT_LOGGER_HPP
#define STX_LOG_ABSTRACT_LOGGER_HPP

#include <iostream>
#include <string>

namespace stx {

template <
    class Formatter,
    class CharType,
    class CharTraits = std::char_traits<CharType>,
    class Allocator = std::allocator<CharType>
>
class abstract_logger
{
public:
    
    typedef abstract_logger<Formatter, CharType, CharTraits, Allocator> abstract_logger_type;
    typedef Formatter formatter_type;
    typedef CharType char_type;
    typedef std::basic_string<CharType, CharTraits, Allocator> string_type;
    typedef std::basic_ostream<CharType, CharTraits> ostream_type;
    
    virtual Formatter log(int message_level) = 0;
    
    virtual Formatter trace() = 0;
    
    virtual Formatter debug() = 0;
    
    virtual Formatter info() = 0;
    
    virtual Formatter warn() = 0;
    
    virtual Formatter error() = 0;
    
    virtual Formatter fatal() = 0;
    
    virtual int level() const = 0;
    
    virtual void set_level(int new_level) = 0;
    
    virtual string_type delimiter() const = 0;
    
    virtual void set_delimiter(const string_type& s) = 0;
    
    virtual const char* level_to_string(int message_level) const = 0;
    
    virtual bool enabled(int message_level) const = 0;
    
    virtual void print_delimiter() = 0;
    
    virtual ostream_type& stream() = 0;
    
    virtual void start_formatting(int message_level) = 0;
    
    virtual void finish_formatting(Formatter& fmt) = 0;
    
    virtual ~abstract_logger()
    {
    }
};

} // namespace stx

#endif // STX_LOG_ABSTRACT_LOGGER_HPP
