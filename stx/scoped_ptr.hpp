#ifndef STX_SCOPED_PTR_HPP
#define STX_SCOPED_PTR_HPP

#include <stx/default_delete.hpp>

namespace stx {

template <typename T, typename Deleter = default_delete<T> >
class scoped_ptr
{
private:
    
    T* p_;
    Deleter deleter_;
    
    typedef scoped_ptr<T, Deleter> this_type;
    scoped_ptr(scoped_ptr const&);
    scoped_ptr& operator=(scoped_ptr const&);
    void operator==(scoped_ptr const&) const;
    void operator!=(scoped_ptr const&) const;
    
public:
    
    typedef T element_type;
    
    explicit scoped_ptr(T* p = 0): p_(p), deleter_(Deleter())
    {
    }
    
    explicit scoped_ptr(T* p, Deleter d): p_(p), deleter_(d)
    {
    }
    
    ~scoped_ptr()
    {
        if (p_) {
            deleter_(p_);
        }
    }
    
    void reset(T* p = 0)
    {
        // p != 0; p != px;
        this_type(p).swap(*this);
    }

    T& operator*() const
    {
        // px != 0
        return *p_;
    }

    T* operator->() const
    {
        // px != 0
        return p_;
    }

    T* get()
    {
        return p_;
    }
    
    const T* get() const
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

    void swap(scoped_ptr&  b)
    {
        T* tmp = b.p_;
        b.p_ = p_;
        p_ = tmp;
    }
    
    T* release()
    {
        T* ret = p_;
        p_ = 0;
        return ret;
    }
};

template <class T>
inline void swap(scoped_ptr<T>& a, scoped_ptr<T>& b)
{
    a.swap(b);
}

template <class T>
inline T* get_pointer(scoped_ptr<T> const& p)
{
    return p.get();
}

} // namespace stx

#endif // STX_SCOPED_PTR_HPP
