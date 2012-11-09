#ifndef STX_LOG_ROLLING_FILE_LOGGER_HPP
#define STX_LOG_ROLLING_FILE_LOGGER_HPP

#include <stx/log/basic_logger.hpp>
#include <fstream>
#include <sstream>
#include <cstddef>
#include <limits>

namespace stx {

template <
    class CharType,
    class CharTraits = std::char_traits<CharType>,
    class Allocator = std::allocator<CharType>,
    class Formatter = log_formatter<CharType, CharTraits, Allocator>
>
class basic_rolling_file_logger:
    public basic_logger<CharType, CharTraits, Allocator, Formatter>
{
public:
    
    typedef abstract_logger<Formatter, CharType, CharTraits, Allocator> abstract_logger_type;
    typedef CharType char_type;
    typedef std::basic_string<CharType, CharTraits, Allocator> string_type;
    typedef std::basic_ostream<CharType, CharTraits> ostream_type;
    typedef basic_logger<CharType, CharTraits, Allocator, Formatter> basic_logger_type;
    typedef std::basic_ofstream<CharType, CharTraits> ofstream_type;
    typedef std::basic_ostringstream<CharType, CharTraits, Allocator> ostringstream_type;
    
    basic_rolling_file_logger(int log_level = log_level_all): basic_logger_type(log_level)
    {
    }
    
    basic_rolling_file_logger(
        const string_type& file_name,
        std::size_t max_file_size = std::numeric_limits<int>::max(),
        int log_level = log_level_all)
    {
        create(file_name, max_file_size, log_level);
    }
    
    void create(
        const std::string& file_name,
        std::size_t max_file_size = std::numeric_limits<int>::max(),
        int log_level = log_level_all)
    {
        file_.exceptions(ofstream_type::eofbit | ofstream_type::failbit | ofstream_type::badbit);
        file_.open(file_name.c_str(), std::ios_base::out | std::ios_base::binary);
        basic_logger_type::set_level(log_level);
        max_file_size_ = max_file_size;
    }
    
    virtual ostream_type& stream()
    {
        return ss_;
    }
    
    void start_formatting(int message_level)
    {
        ss_.str(""); //todo make portable for wchar_t
        basic_logger_type::start_formatting(message_level);
    }
    
    void finish_formatting(Formatter& fmt)
    {
        if (fmt.enabled()) {
            stream() << std::endl;
            std::size_t max_size = max_file_size(),
                current_size = current_file_size(),
                remaining_size = max_size - current_size,
                message_size = stream_str_size(ss_);
            if (message_size <= remaining_size) {
                file_ << ss_.str();
            } else if (message_size > max_size) {
                file_.seekp(0, std::ios_base::beg);
                file_.write(ss_.str().c_str(), max_size);
            } else {
                string_type buf_str = ss_.str();
                file_.write(buf_str.c_str(), remaining_size);
                file_.seekp(0, std::ios_base::beg);
                file_.write(buf_str.c_str() + remaining_size, message_size - remaining_size);
            }
            //file_.flush();
        }
    }
    
    std::size_t max_file_size() const
    {
        return max_file_size_;
    }
    
    basic_rolling_file_logger& set_max_file_size(std::size_t size)
    {
        max_file_size_ = size;
        return *this;
    }
    
    std::size_t current_file_size()
    {
        std::streampos p = file_.tellp();
        if (p == std::streampos(-1)) {
            file_.seekp(0, std::ios_base::beg);
            p = std::streampos(0);
        }
        return std::size_t(p);
    }
    
protected:
    
    std::size_t stream_str_size(ostringstream_type& ss)
    {
        return ss.str().size();
    }
    
    ofstream_type file_;
    std::size_t max_file_size_;
    ostringstream_type ss_;
};

typedef basic_rolling_file_logger<char> rolling_file_logger;
typedef basic_rolling_file_logger<wchar_t> wrolling_file_logger;

} // namespace stx

#endif // STX_LOG_ROLLING_FILE_LOGGER_HPP
