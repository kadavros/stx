#ifndef STX_REF_HPP
#define STX_REF_HPP

namespace stx {

template <class T>
class reference_wrapper
{ 
public:
    
    typedef T type;
    explicit reference_wrapper(T& t): t_(&t) {}
    operator T& () const { return *t_; }
    T& get() const { return *t_; }
    T* get_pointer() const { return t_; }
    
private:
    
    T* t_;
};

#if defined(__BORLANDC__)
#   define STX_REF_CONST
#else
#   define STX_REF_CONST const
#endif

template <class T>
inline reference_wrapper<T> STX_REF_CONST ref(T& t)
{ 
    return reference_wrapper<T>(t);
}

template <class T>
inline reference_wrapper<T const> STX_REF_CONST cref(T const& t)
{
    return reference_wrapper<T const>(t);
}

#undef STX_REF_CONST

} // namespace stx

#endif // STX_REF_HPP
