#ifndef STX_RAW_PTR_HPP
#define STX_RAW_PTR_HPP

#include <stddef.h>
#include <memory> // auto_ptr
#include <stx/scoped_ptr.hpp>

namespace stx {

template <class T>
class raw_ptr
{
public:
    
    typedef T element_type;
    typedef raw_ptr<T> this_type;
    
    raw_ptr(): p_(NULL) {}
    
    template <class U>
    raw_ptr(U* x): p_(x) {}
    
    template <class U>
    raw_ptr(U& x): p_(&x) {}
    
    template <class U>
    raw_ptr(std::auto_ptr<U>& x): p_(x.get()) {}
    
    template <class U>
    raw_ptr(const std::auto_ptr<U>& x): p_(x.get()) {}
    
    template <class U, class Deleter>
    raw_ptr(scoped_ptr<U, Deleter>& x): p_(x.get()) {}
    
    template <class U, class Deleter>
    raw_ptr(const scoped_ptr<U, Deleter>& x): p_(x.get()) {}
    
    void reset(T* p = 0)
    {
        p_ = p;
    }
    
    void reset(this_type p)
    {
        p_ = p.p_;
    }
    
    T& operator*() const
    {
        // p_ != 0
        return *p_;
    }
    
    T* operator->() const
    {
        // p_ != 0
        return p_;
    }
    
    T* get() const
    {
        return p_;
    }
    
    operator bool() const
    {
        return p_ != 0;
    }
    
    bool operator!() const
    {
        return p_ == 0;
    }
    
    void swap(raw_ptr& b)
    {
        T* tmp = b.p_;
        b.p_ = p_;
        p_ = tmp;
    }
    
private:
    
    T* p_;
};

template <class T>
inline void swap(raw_ptr<T>& a, raw_ptr<T>& b)
{
    a.swap(b);
}

template <class T>
inline T* get_pointer(raw_ptr<T> const& p)
{
    return p.get();
}

} // namespace stx

#endif // STX_RAW_PTR_HPP
