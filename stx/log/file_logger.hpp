#ifndef STX_LOG_FILE_LOGGER_HPP
#define STX_LOG_FILE_LOGGER_HPP

#include <stx/log/basic_logger.hpp>
#include <fstream>

namespace stx {

template <
    class CharType,
    class CharTraits = std::char_traits<CharType>,
    class Allocator = std::allocator<CharType>,
    class Formatter = log_formatter<CharType, CharTraits, Allocator>
>
class basic_file_logger:
    public basic_logger<CharType, CharTraits, Allocator, Formatter>
{
public:
    
    typedef abstract_logger<Formatter, CharType, CharTraits, Allocator> abstract_logger_type;
    typedef CharType char_type;
    typedef std::basic_string<CharType, CharTraits, Allocator> string_type;
    typedef std::basic_ostream<CharType, CharTraits> ostream_type;
    typedef basic_logger<CharType, CharTraits, Allocator, Formatter> basic_logger_type;
    typedef std::basic_ofstream<CharType, CharTraits> ofstream_type;
    
    basic_file_logger(int log_level = log_level_all): basic_logger_type(log_level)
    {
    }
    
    basic_file_logger(const std::string& file_name, int log_level = log_level_all)
    {
        create(file_name, log_level);
    }
    
    void create(const std::string& file_name, int log_level = log_level_all)
    {
        file_.exceptions(ofstream_type::eofbit | ofstream_type::failbit | ofstream_type::badbit);
        file_.open(file_name.c_str(), std::ios_base::out | std::ios_base::binary);
        this->set_level(log_level);
    }
    
    virtual ostream_type& stream()
    {
        return file_;
    }
    
protected:
    
    ofstream_type file_;
};

typedef basic_file_logger<char> file_logger;
typedef basic_file_logger<wchar_t> wfile_logger;

} // namespace stx

#endif // STX_LOG_FILE_LOGGER_HPP
