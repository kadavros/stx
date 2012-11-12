#ifndef STX_NULLSTREAM_HPP
#define STX_NULLSTREAM_HPP

#include <string>
#include <ostream>

namespace stx {

template<typename CharType, typename CharTraits = std::char_traits<CharType> >
struct basic_nullbuf: std::basic_streambuf<CharType, CharTraits>
{
     typedef std::basic_streambuf<CharType, CharTraits> base_type;
     typedef typename base_type::int_type int_type;
     typedef typename base_type::traits_type traits_type;

     virtual int_type overflow(int_type c)
     {
         return traits_type::not_eof(c);
     }
};

typedef basic_nullbuf<char> nullbuf;
typedef basic_nullbuf<wchar_t> wnullbuf;

template<typename CharType, typename CharTraits = std::char_traits<CharType> >
class basic_null_ostream: public std::basic_ostream<CharType, CharTraits>
{
public:
    
    typedef std::basic_ostream<CharType, CharTraits> ostream_type;
    
    basic_null_ostream(): ostream_type(&buf_) {}
    
private:
    
    basic_nullbuf<CharType, CharTraits> buf_;
};

typedef basic_null_ostream<char> onullstream;
typedef basic_null_ostream<wchar_t> wonullstream;

} // namespace stx

#endif // STX_NULLSTREAM_HPP
