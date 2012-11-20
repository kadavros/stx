#ifndef STX_LOG_LOG_FORMATTER_HPP
#define STX_LOG_LOG_FORMATTER_HPP

#include <stx/log/abstract_logger.hpp>
#include <ios>
#include <iomanip>

namespace stx {

//  Log formatting facilities.
//  Note: manipulators with implemenation specific type cause logger to print
//  delimiter where it is not appropriate. In order to fix this, those
//  manipulators are reimplemented as member functions:
//      setiosflags()
//      resetiosflags()
//      setbase()
//      setfill()
//      setprecision()
//      setw()
//  Using manipulators:
//      stx::cout_logger log;
//      log.set_delimiter(" ");
//      log.debug().setw(10).setfill('0') << 256; // Ok - desired formatting.
//      log.debug() << setw(10) << setfill('0') << 256; // Ops, extra delimiters!

template <
    class CharType,
    class CharTraits = std::char_traits<CharType>,
    class Allocator = std::allocator<CharType>
>
class log_formatter
{
public:
    
    typedef log_formatter<CharType, CharTraits, Allocator> this_type;
    typedef abstract_logger<this_type, CharType, CharTraits, Allocator> logger_type;
    typedef CharType char_type;
    typedef std::basic_string<CharType, CharTraits, Allocator> string_type;
    typedef std::basic_ostream<CharType, CharTraits> stream_type;
    typedef std::basic_ios<CharType, CharTraits> ios_type;
    
    log_formatter(): enabled_(0)
    {
    }
    
    log_formatter(logger_type& logger, bool enabled):
        logger_(logger),
        enabled_(enabled),
        first_record_(true)
    {
    }
    
    logger_type& logger()
    {
        return logger_;
    }
    
    inline bool enabled() const
    {
        return enabled_;
    }
    
    template<class T>
    log_formatter& operator <<(const T& x)
    {
        write_to_stream(x);
        return *this;
    }
    
    log_formatter& operator <<(const string_type& x)
    {
        if (!x.empty()) {
            write_to_stream(x);
        }
        return *this;
    }
    
    log_formatter& operator <<(const char_type* x)
    {
        if (*x) {
            write_to_stream(x);
        }
        return *this;
    }
    
    log_formatter& operator<< (stream_type& (*x)(stream_type&))
    {
        write_to_stream_without_delimiter(x);
        return *this;
    }
    
    log_formatter& operator <<(ios_type& (*x)(ios_type&))
    {
        write_to_stream_without_delimiter(x);
        return *this;
    }
    
    log_formatter& operator <<(std::ios_base& (*x)(std::ios_base&))
    {
        write_to_stream_without_delimiter(x);
        return *this;
    }
    
    log_formatter& setiosflags(std::ios_base::fmtflags mask)
    {
        logger().actual_stream() << std::setiosflags(mask);
        return *this;
    }
    
    log_formatter& resetiosflags(std::ios_base::fmtflags mask)
    {
        logger().actual_stream() << std::resetiosflags(mask);
        return *this;
    }
    
    log_formatter& setbase(int base)
    {
        logger().actual_stream() << std::setbase(base);
        return *this;
    }
    
    log_formatter& setfill(char c)
    {
        logger().actual_stream() << std::setfill(c);
        return *this;
    }
    
    log_formatter& setprecision(int n)
    {
        logger().actual_stream() << std::setprecision(n);
        return *this;
    }
    
    log_formatter& setw(int n)
    {
        logger().actual_stream() << std::setw(n);
        return *this;
    }
    
    template<class T>
    void write_to_stream(const T& x)
    {
        if (enabled_) {
            if (!first_record_) {
                logger().print_delimiter();
            } else {
                first_record_ = 0;
            }
            logger().actual_stream() << x;
        }
    }
    
    template<class T>
    void write_to_stream_without_delimiter(const T& x)
    {
        if (enabled_) {
            logger().actual_stream() << x;
        }
    }
    
    ~log_formatter()
    {
        if (enabled_) {
            logger().finish_formatting(*this);
        }
    }
    
private:
    
    logger_type& logger_;
    unsigned enabled_ : 1;
    unsigned first_record_ : 1;
};

} // namespace stx

#endif // STX_LOG_LOG_FORMATTER_HPP
