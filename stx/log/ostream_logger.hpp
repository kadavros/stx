#ifndef STX_LOG_OSTREAM_LOGGER_HPP
#define STX_LOG_OSTREAM_LOGGER_HPP

#include <stx/log/basic_logger.hpp>

namespace stx {

template <
    class CharType,
    class Mutex = fake_mutex,
    class CharTraits = std::char_traits<CharType>,
    class Allocator = std::allocator<CharType>,
    class Formatter = log_formatter<CharType, CharTraits, Allocator>
>
class basic_ostream_logger:
    public basic_logger<CharType, Mutex, CharTraits, Allocator, Formatter>
{
public:
    
    typedef abstract_logger<Formatter, CharType, CharTraits, Allocator> abstract_logger_type;
    typedef CharType char_type;
    typedef std::basic_string<CharType, CharTraits, Allocator> string_type;
    typedef std::basic_ostream<CharType, CharTraits> ostream_type;
    typedef basic_logger<CharType, Mutex, CharTraits, Allocator, Formatter> basic_logger_type;
    
    basic_ostream_logger(ostream_type& s, int log_level = log_level_all):
        basic_logger_type(log_level),
        ostream_(s)
    {
    }
    
    ostream_type& stream()
    {
        return ostream_;
    }
    
private:
    
    ostream_type& ostream_; 
};

typedef basic_ostream_logger<char> ostream_logger;
typedef basic_ostream_logger<wchar_t> wostream_logger;

} // namespace stx

#endif // STX_LOG_OSTREAM_LOGGER_HPP
