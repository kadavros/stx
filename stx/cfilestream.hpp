#ifndef STX_CFILESTREAM_HPP
#define STX_CFILESTREAM_HPP

#include <stdio.h>
#include <streambuf>
#include <iostream>

namespace stx {

template<typename CharType, typename CharTraits = std::char_traits<CharType> >
class basic_cfilebuf: public std::basic_streambuf<CharType, CharTraits>
{
public:
    
    typedef std::basic_streambuf<CharType, CharTraits> base_type;
    typedef typename base_type::int_type int_type;
    typedef CharType char_type;
    typedef typename base_type::traits_type traits_type;
    
    basic_cfilebuf(FILE* fp, bool auto_close_fd = false):
        fp_(fp), auto_close_fd_(auto_close_fd)
    {
    }
    
    basic_cfilebuf(const char* filename, const char* opentype):
        auto_close_fd_(true)
    {
        fp_ = fopen(filename, opentype);
    }
    
    ~basic_cfilebuf()
    {
        if (auto_close_fd_ && fp_) {
            fclose(fp_);
        }
    }
    
protected:
    
    virtual int_type overflow(int_type c)
    {
        if (!fp_) {
            return traits_type::eof();
        }
        if (c != EOF) {
            if (fputc(c, fp_) == EOF) {
                return traits_type::eof();
            }
        }
        return traits_type::not_eof(c);
    }
    
    virtual std::streamsize xsputn(const char_type* s, std::streamsize n)
    {
        size_t ret = fwrite(s, 1, n, fp_);
        if (ret != (size_t) n) {
            return -1;
        }
        return std::streamsize(n);
    }
    
private:
    
    FILE* fp_;
    bool auto_close_fd_;
};

typedef basic_cfilebuf<char> cfilebuf;
typedef basic_cfilebuf<wchar_t> wcfilebuf;

template<typename CharType, typename CharTraits = std::char_traits<CharType> >
class basic_cfilestream: public std::basic_ostream<CharType, CharTraits>
{
public:
    
    typedef basic_cfilebuf<CharType, CharTraits> buf_type;
    
    basic_cfilestream(FILE* fp, bool auto_close_fd = false):
        buf(fp, auto_close_fd)
    {
        rdbuf(&buf);
    }
    
    basic_cfilestream(const char* filename, const char* opentype):
        buf(filename, opentype)
    {
        rdbuf(&buf);
    }
    
protected:
    
    basic_cfilebuf<CharType, CharTraits> buf;
};

typedef basic_cfilestream<char> cfilestream;
typedef basic_cfilestream<wchar_t> wcfilestream;

} // namespace stx

#endif // STX_CFILESTREAM_HPP
