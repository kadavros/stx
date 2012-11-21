#ifndef STX_CSTR_HPP
#define STX_CSTR_HPP

//  cstr - lighweight string wrapper.

#include <string>
#include <vector>
#include <string.h>
#include <stddef.h>
#include <stdexcept>

namespace stx {

class cstr
{
public:
    
    typedef char char_type;
    typedef size_t size_type;
    
    const char_type* c_str() const
    {
        return buf_;
    }
    
    size_type size() const
    {
        return size_;
    }
    
    size_type length() const
    {
        return size();
    }
    
    size_type capacity() const
    {
        return size() + 1;
    }
    
    void clear()
    {
        buf_ = "";
        size_ = 0;
    }
    
    bool empty() const
    {
        return (size_ == 0);
    }
    
    const char& operator[](size_type pos) const
    {
        return buf_[pos];
    }
    
    const char& at(size_type pos) const
    {
        if (pos > size_) {
            throw std::out_of_range("");
        }
        return buf_[pos];
    }
    
    void swap(cstr& s)
    {
        cstr tmp = s;
        s = *this;
        *this = tmp;
    }
    
    const char_type* data() const
    {
        return buf_;
    }
    
    //  C++11 functions.
    
    const char_type& front() const
    {
        return buf_[0];
    }
    
    const char_type& back() const
    {
        return buf_[size_ - 1];
    }
    
    //  Does nothing, just for compatibility.
    void shrink_to_fit()
    {
    }
    
    //  Constructors.
    
    cstr():
        buf_(""), size_(0)
    {
    }
    
    //  For "const char*" and "const char* const" parameters.
    template <class T>
    cstr(const T& t):
        buf_(t), size_(strlen(buf_))
    {
    }
    
    //  For "const char []" parametes.
    template <class T, size_type Size>
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
    
    cstr(const char_type* s, size_type size):
        buf_(s), size_(size)
    {
    }
    
    cstr(const char_type* begin, const char_type* end):
        buf_(begin), size_(end - begin)
    {
    }
    
    template <class Allocator>
    cstr(const std::vector<char_type, Allocator>& v, size_type size):
        buf_(&v[0]), size_(size)
    {
    }
    
    //  TODO
    //  -= C++03 =-
    //  begin()
    //  end()
    //  rbegin()
    //  rend()
    //  max_size() (is it useful for const string?)
    //  assign() (duplicate constructors)
    //  copy()
    //  find()
    //  rfind()
    //  find_first_of()
    //  find_last_of()
    //  find_first_not_of()
    //  find_last_not_of()
    //  substr()
    //  compare()
    //
    //  -= C++11 =-
    //  cbegin()
    //  cend()
    //  crbegin()
    //  crend()
    
private:
    
    const char_type* buf_;
    size_type size_;
};

} // namespace stx

#endif // STX_CSTR_HPP
