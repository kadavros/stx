#ifndef STX_CSTR_HPP
#define STX_CSTR_HPP

//  cstr - lighweight string wrapper.

#include <string>
#include <vector>
#include <string.h>
#include <stddef.h>

namespace stx {

class cstr
{
public:
    
    typedef char char_type;
    
    const char_type* c_str() const
    {
        return buf_;
    }
    
    size_t size() const
    {
        return size_;
    }
    
    //  For "const char*" and "const char* const" parameters.
    template <class T>
    cstr(const T& t):
        buf_(t), size_(strlen(buf_))
    {
    }
    
    //  For "const char []" parametes.
    template <class T, size_t Size>
    cstr(const T (&t)[Size]):
        buf_(t), size_(Size - 1)
    {
    }
    
    template <class CharTraits, class Allocator>
    cstr(const std::basic_string<char_type, CharTraits, Allocator>& s):
        buf_(s.c_str()), size_(s.size())
    {
    }
    
    template <class Allocator>
    cstr(const std::vector<char_type, Allocator>& v):
        buf_(&v[0]), size_(v.size())
    {
    }
    
    //  Constructors with multiple parameters.
    
    cstr(const char_type* s, size_t size):
        buf_(s), size_(size)
    {
    }
    
    cstr(const char_type* begin, const char_type* end):
        buf_(begin), size_(end - begin)
    {
    }
    
    template <class Allocator>
    cstr(const std::vector<char_type, Allocator>& v, size_t size):
        buf_(&v[0]), size_(size)
    {
    }
    
private:
    
    const char_type* buf_;
    size_t size_;
};

} // namespace stx

#endif // STX_CSTR_HPP
