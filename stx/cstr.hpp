#ifndef STX_CSTR_HPP
#define STX_CSTR_HPP

//  cstr - lightweight null-terminated C-string wrapper.

#include <string>
#include <vector>
#include <stdexcept>
#include <iterator>
#include <string.h>
#include <stddef.h>
#include <assert.h>

#ifndef STX_SIZE_T_MAX
#   define STX_SIZE_T_MAX (~((size_t) 0))
#endif

namespace stx {

class cstr
{
public:
    
    typedef char             char_type;
    typedef const char       value_type;
    typedef size_t           size_type;
    typedef ptrdiff_t        difference_type;
    typedef const char&      reference;
    typedef const char&      const_reference;
    typedef const char_type* pointer; // Both pointer and const_pointer are of type const char_type*
    typedef const char_type* const_pointer;
    typedef pointer          iterator;
    typedef const_pointer    const_iterator;
    typedef std::reverse_iterator<iterator>       reverse_iterator;
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
    
    const char_type* c_str() const
    {
        return buf_;
    }
    
    size_type size() const
    {
        if (!size_initialized()) {
            size_ = strlen(buf_);
        }
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
    
    size_type max_size() const
    {
        return size();
    }
    
    void clear()
    {
        buf_ = empty_c_str();
        size_ = 0;
    }
    
    bool empty() const
    {
        return (size_ == 0);
    }
    
    const char& operator[](size_type pos) const
    {
        assert(pos <= size_);
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
        assert(!empty());
        return buf_[0];
    }
    
    const char_type& back() const
    {
        assert(!empty());
        return buf_[size_ - 1];
    }
    
    //  Does nothing, just for compatibility.
    void shrink_to_fit()
    {
    }
    
    //  Constructors.
    
    cstr():
        buf_(empty_c_str()), size_(0)
    {
    }
    
    //  For "const char*" and "const char* const" parameters.
    template <class T>
    cstr(const T& t):
        buf_(t), size_(STX_SIZE_T_MAX)
    {
        if (t == NULL) {
            buf_ = empty_c_str();
        }
    }
    
    //  For "const char []" parametes.
    //  Precondition: t[Size - 1] == '\0'
    template <class T, size_type Size>
    cstr(const T (&t)[Size])
    {
        if (!Size) {
            clear();
        } else {
            assert(t[Size - 1] == '\0');
            buf_ = t;
            size_ = Size - 1;
        }
    }
    
    template <class CharTraits, class Allocator>
    cstr(const std::basic_string<char_type, CharTraits, Allocator>& s)
    {
        if (s.empty()) {
            clear();
        } else {
            buf_ = s.c_str();
            size_ = s.size();
        }
    }
    
    //  Precondition: v[size() - 1] == '\0'
    template <class Allocator>
    cstr(const std::vector<char_type, Allocator>& v)
    {
        if (v.empty()) {
            clear();
        } else {
            assert(v[v.size() - 1] == '\0');
            buf_ = &v[0];
            size_ = v.size() - 1;
        }
    }
    
    //  Constructors with multiple parameters.
    
    //  Precondition: s[size] == '\0'
    cstr(const char_type* s, size_type size):
        buf_(s), size_(size)
    {
        if (!s || !size) {
            clear();
        } else {
            assert(s[size] == '\0');
            buf_ = s;
            size_ = size;
        }
    }
    
    //  Precondition: *(last - 1) == '\0'
    cstr(const char_type* first, const char_type* last)
    {
        if (!first) {
            clear();
        } else if (!last) {
            buf_ = first;
            size_ = STX_SIZE_T_MAX;
        } else {
            assert(first < last);
            assert(*(last - 1) == '\0');
            buf_ = first;
            size_ = last - first - 1;
        }
    }
    
    //  Precondition: v[size] == '\0'
    template <class Allocator>
    cstr(const std::vector<char_type, Allocator>& v, size_type size)
    {
        if (!size || v.empty()) {
            clear();
        } else {
            assert(v.size() >= size);
            assert(v[size] == '\0');
            buf_ = &v[0];
            size_ = size;
        }
    }
    
    //  Raw size/length/capacity/max_size.
    //  When cstr object is constructed from const char* C-string,
    //  evaluation of actual string size is performed (once) only when size()
    //  member function is called. This lazy size evaluation implies
    //  some overhead for getting cstr's size, therefore we provide
    //  raw_size() function. It's safe to call raw_size() after first
    //  call to size(). Call to raw_size() will generally be faster than
    //  call to size(), though it won't ensure proper size evaluation.
    //  You can check whether internal size value is initialized by
    //  call to size_initialized() function.
    size_type raw_size() const
    {
        return size_;
    }
    
    size_type raw_length() const
    {
        return raw_size();
    }
    
    size_type raw_capacity() const
    {
        return raw_size() + 1;
    }
    
    size_type raw_max_size() const
    {
        return raw_size();
    }
    
    bool size_initialized() const
    {
        return raw_size() != STX_SIZE_T_MAX;
    }
    
    iterator begin()
    {
        return iterator(buf_);
    }
    
    const_iterator begin() const
    {
        return const_iterator(buf_);
    }
    
    iterator end()
    {
        return iterator(buf_ + size());
    }
    
    const_iterator end() const
    {
        return const_iterator(buf_ + size());
    }
    
    reverse_iterator rbegin()
    {
        return reverse_iterator(end());
    }
    
    const_reverse_iterator rbegin() const
    {
        return const_reverse_iterator(end());
    }
    
    reverse_iterator rend()
    {
        return reverse_iterator(begin());
    }
    
    const_reverse_iterator rend() const
    {
        return const_reverse_iterator(begin());
    }
    
    const_iterator cbegin() const
    {
        return begin();
    }
    
    const_iterator cend() const
    {
        return end();
    }
        
    const_reverse_iterator crbegin() const
    {
        return rbegin();
    }
    
    const_reverse_iterator crend() const
    {
        return rend();
    }
    
    //  TODO
    //  -= C++03 =-
    //  assign()
    //  copy()
    //  find()
    //  rfind()
    //  find_first_of()
    //  find_last_of()
    //  find_first_not_of()
    //  find_last_not_of()
    //  substr()
    //  compare()
    
private:
    
    static const char_type* empty_c_str()
    {
        return "";
    }
    
    const char_type* buf_;
    
    //  size_ is made mutable because of lazy initialization
    //  performed in size() function.
    mutable size_type size_;
};

} // namespace stx

#endif // STX_CSTR_HPP
