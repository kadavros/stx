#ifndef STX_DATETIME_FORMATTER_HPP
#define STX_DATETIME_FORMATTER_HPP

#include <time.h>
#include <stddef.h>
#include <string>
#include <vector>
#include <stx/shrink.hpp>

namespace stx {

class datetime_formatter
{
public:
    
    enum { min_repr_size = 32 };
    
    datetime_formatter():
        format_str_("%Y-%m-%d %H:%M:%S"),
        repr_(repr_size(format_str_.size()), '\0'),
        str_size_(0)
    {
    }
    
    datetime_formatter(const std::string& format_str):
        format_str_(format_str),
        repr_(repr_size(format_str_.size()), '\0'),
        str_size_(0)
    {
    }
    
    std::string format_str() const
    {
        return format_str_;
    }
    
    void set_format_str(const std::string& format_str)
    {
        format_str_ = format_str;
    }
    
    void format(const struct tm* t)
    {
        size_t ret = 0;
        while (!ret) {
            ret = strftime(&repr_[0], repr_.size(), format_str_.c_str(), t);
            if (ret == 0) {
                //  Resize policy.
                repr_.resize(repr_.size() * 1.5);
            }
        }
        str_size_ = ret;
    }
    
    void format(const struct tm& t)
    {
        format(&t);
    }
    
    const char* c_str() const
    {
        return &repr_[0];
    }
    
    const char* c_str(const struct tm* t)
    {
        format(t);
        return c_str();
    }
    
    const char* c_str(const struct tm& t)
    {
        format(t);
        return c_str();
    }
    
    std::string str() const
    {
        return std::string(c_str(), str_size_);
    }
    
    std::string str(const struct tm* t)
    {
        format(t);
        return str();
    }
    
    std::string str(const struct tm& t)
    {
        format(t);
        return str();
    }
    
    //  Technical interface.
    
    size_t repr_size()
    {
        return repr_.size();
    }
    
    size_t set_repr_size(size_t size)
    {
        repr_.resize(min_repr_size > size ? min_repr_size : size);
        return repr_.size();
    }
    
    void shrink()
    {
        shrink_format_str();
        shrink_repr();
    }
    
    void shrink_format_str()
    {
        stx::shrink(format_str_);
    }
    
    void shrink_repr()
    {
        stx::shrink(repr_);
    }
    
private:
    
    static size_t repr_size(size_t format_str_size)
    {
        size_t size = format_str_size * 1.5;
        return min_repr_size > size ? min_repr_size : size;
    }
    
    std::string format_str_;
    std::vector<char> repr_;
    size_t str_size_;
};

} // namespace stx

#endif // STX_DATETIME_FORMATTER_HPP
