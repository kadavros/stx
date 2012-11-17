#ifndef STX_CFILESTREAM_HPP
#define STX_CFILESTREAM_HPP

#include <stdio.h>
#include <wchar.h>
#include <string.h>
#include <stddef.h>
#include <streambuf>
#include <iostream>

namespace stx {

inline int cfile_putc(int c, FILE* fp)
{
    return fputc(c, fp);
}

inline std::char_traits<wchar_t>::int_type
cfile_putc(wchar_t c, FILE* fp)
{
    return fputwc(c, fp);
}

template <class CharType, class IntType>
inline IntType cfile_getc(FILE* fp);

template <>
inline int cfile_getc<char, int>(FILE* fp)
{
    return fgetc(fp);
}

template <>
inline wint_t cfile_getc<wchar_t, wint_t>(FILE* fp)
{
    return fgetwc(fp);
}

template<typename CharType, typename CharTraits = std::char_traits<CharType> >
class basic_cfilebuf: public std::basic_streambuf<CharType, CharTraits>
{
public:
    
    typedef basic_cfilebuf<CharType, CharTraits> this_type;
    typedef std::basic_streambuf<CharType, CharTraits> base_type;
    typedef typename base_type::int_type int_type;
    typedef CharType char_type;
    typedef CharTraits traits_type;
    
    basic_cfilebuf()
    {
        fp_ = NULL;
        fp_ownership_ = false;
    }
    
    basic_cfilebuf(FILE* fp, bool fp_ownership = false)
    {
        fp_ = NULL;
        open(fp, fp_ownership);
    }
    
    basic_cfilebuf(const char* filename, const char* opentype)
    {
        fp_ = NULL;
        open(filename, opentype);
    }
    
    ~basic_cfilebuf()
    {
        close();
    }
    
    bool is_open()
    {
        return fp_;
    }
    
    this_type* open(FILE* fp, bool fp_ownership = false)
    {
        init();
        fp_ = fp;
        fp_ownership_ = fp_ownership;
        return this;
    }
    
    this_type* open(const char* filename, const char* opentype)
    {
        init();
        fp_ = fopen(filename, opentype);
        fp_ownership_ = true;
        return this;
    }
    
    this_type* close()
    {
        if (fp_ && fp_ownership_) {
            fclose(fp_);
            fp_ = NULL;
        }
        return this;
    }
    
    FILE* file_handle()
    {
        return fp_;
    }
    
protected:
    
    void init()
    {
        close();
        base_type::setg(buf_, buf_, buf_);
    }
    
    virtual int_type overflow(int_type c)
    {
        if (!fp_) {
            return traits_type::eof();
        }
        if (c != EOF) {
            if (cfile_putc(c, fp_) == EOF) {
                return traits_type::eof();
            }
        }
        return traits_type::not_eof(c);
    }
    
    virtual int_type underflow()
    {
        if (!fp_) {
            return traits_type::eof();
        }
        if (base_type::gptr() < base_type::egptr()) {
            return traits_type::to_int_type(*base_type::gptr());
        }
        if (feof(fp_)) {
            return traits_type::eof();
        }
        char_type c = cfile_getc<char_type, int_type>(fp_);
        if (ferror(fp_)) {
            return traits_type::eof();
        }
        buf_[0] = c;
        base_type::setg(buf_, buf_, buf_ + 1);
        return traits_type::to_int_type(*base_type::gptr());
    }
    
private:
    
    FILE* fp_;
    bool fp_ownership_;
    char_type buf_[1];
};

typedef basic_cfilebuf<char> cfilebuf;
typedef basic_cfilebuf<wchar_t> wcfilebuf;

template<typename CharType, typename CharTraits = std::char_traits<CharType> >
class basic_ocfilestream: public std::basic_ostream<CharType, CharTraits>
{
public:
    
    typedef basic_cfilebuf<CharType, CharTraits> buf_type;
    typedef std::basic_ostream<CharType, CharTraits> base_type;
    
    basic_ocfilestream()
    {
    }
    
    basic_ocfilestream(FILE* fp, bool fp_ownership = false):
        buf_(fp, fp_ownership)
    {
        init();
    }
    
    basic_ocfilestream(const char* filename, const char* opentype = "w"):
        buf_(filename, opentype)
    {
        init();
    }
    
    bool is_open()
    {
        return buf_.is_open();
    }
    
    void open(FILE* fp, bool fp_ownership = false)
    {
        buf_.open(fp, fp_ownership);
    }
    
    void open(const char* filename, const char* opentype)
    {
        buf_.open(filename, opentype);
    }
    
    void close()
    {
        buf_.close();
    }
    
    buf_type* rdbuf() const
    {
        return &buf_;
    }
    
    FILE* file_handle()
    {
        return buf_.file_handle();
    }
    
protected:
    
    void init()
    {
        base_type::rdbuf(&buf_);
    }
    
    basic_cfilebuf<CharType, CharTraits> buf_;
};

typedef basic_ocfilestream<char> ocfilestream;
typedef basic_ocfilestream<wchar_t> wocfilestream;

template<typename CharType, typename CharTraits = std::char_traits<CharType> >
class basic_icfilestream: public std::basic_istream<CharType, CharTraits>
{
public:
    
    typedef basic_cfilebuf<CharType, CharTraits> buf_type;
    typedef std::basic_istream<CharType, CharTraits> base_type;
    
    basic_icfilestream()
    {
    }
    
    basic_icfilestream(FILE* fp, bool fp_ownership = false):
        buf_(fp, fp_ownership)
    {
        init();
    }
    
    basic_icfilestream(const char* filename, const char* opentype = "r"):
        buf_(filename, opentype)
    {
        init();
    }
    
    bool is_open()
    {
        return buf_.is_open();
    }
    
    void open(FILE* fp, bool fp_ownership = false)
    {
        buf_.open(fp, fp_ownership);
    }
    
    void open(const char* filename, const char* opentype)
    {
        buf_.open(filename, opentype);
    }
    
    void close()
    {
        buf_.close();
    }
    
    buf_type* rdbuf() const
    {
        return &buf_;
    }
    
    FILE* file_handle()
    {
        return buf_.file_handle();
    }
    
protected:
    
    void init()
    {
        base_type::rdbuf(&buf_);
    }
    
    basic_cfilebuf<CharType, CharTraits> buf_;
};

typedef basic_icfilestream<char> icfilestream;
typedef basic_icfilestream<wchar_t> wicfilestream;

template<typename CharType, typename CharTraits = std::char_traits<CharType> >
class basic_cfilestream: public std::basic_iostream<CharType, CharTraits>
{
public:
    
    typedef basic_cfilebuf<CharType, CharTraits> buf_type;
    typedef std::basic_iostream<CharType, CharTraits> base_type;
    
    basic_cfilestream()
    {
    }
    
    basic_cfilestream(FILE* fp, bool fp_ownership = false):
        buf_(fp, fp_ownership)
    {
        init();
    }
    
    basic_cfilestream(const char* filename, const char* opentype):
        buf_(filename, opentype)
    {
        init();
    }
    
    bool is_open()
    {
        return buf_.is_open();
    }
    
    void open(FILE* fp, bool fp_ownership = false)
    {
        buf_.open(fp, fp_ownership);
    }
    
    void open(const char* filename, const char* opentype)
    {
        buf_.open(filename, opentype);
    }
    
    void close()
    {
        buf_.close();
    }
    
    buf_type* rdbuf() const
    {
        return &buf_;
    }
    
    FILE* file_handle()
    {
        return buf_.file_handle();
    }
    
protected:
    
    void init()
    {
        base_type::rdbuf(&buf_);
    }
    
    basic_cfilebuf<CharType, CharTraits> buf_;
};

typedef basic_cfilestream<char> cfilestream;
typedef basic_cfilestream<wchar_t> wcfilestream;

} // namespace stx

#endif // STX_CFILESTREAM_HPP
