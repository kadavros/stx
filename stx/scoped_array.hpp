#ifndef STX_SCOPED_ARRAY_HPP
#define STX_SCOPED_ARRAY_HPP

#include <stddef.h>

namespace stx {

template<class T, typename Deleter = default_delete<T[]> >
class scoped_array: protected Deleter // noncopyable
{
private:
    
    T* p_;
    
    typedef T value_type;
    typedef scoped_ptr<T, Deleter> this_type;
    typedef Deleter deleter_type;
    scoped_array(scoped_array const&);
    scoped_array& operator=(scoped_array const&);
    void operator==(scoped_array const&) const;
    void operator!=(scoped_array const&) const;
    
public:

    typedef T element_type;

    explicit scoped_array(T* p = 0): p_(p) // never throws
    {
    }
    
    explicit scoped_array(T* p, deleter_type d):
        deleter_type(d), p_(p)
    {
    }
    
    ~scoped_array() // never throws
    {
        if (p_) {
            deleter_type::operator()(p_);
        }
    }

    void reset(T* p = 0) // never throws
    {
        //  TODO
        //  p == 0
        //  p != p_
        this_type(p).swap(*this);
    }

    T& operator[](ptrdiff_t i) const // never throws
    {
        //  TODO
        //  p_ != 0
        //  i >= 0
        return p_[i];
    }

    T* get() const // never throws
    {
        return p_;
    }

    operator bool() const
    {
        return p_ != 0;
    }
    
    bool operator!() const // never throws
    {
        return p_ == 0;
    }

    void swap(scoped_array& b) // never throws
    {
        T* tmp = b.p_;
        b.p_ = p_;
        p_ = tmp;
    }
};

template<class T> inline void swap(scoped_array<T>& a, scoped_array<T>& b) // never throws
{
    a.swap(b);
}

template <class T>
inline T* get_pointer(scoped_array<T> const& p)
{
    return p.get();
}

} // namespace stx

#endif // STX_SCOPED_ARRAY_HPP
