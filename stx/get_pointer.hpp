#ifndef STX_GET_POINTER_HPP
#define STX_GET_POINTER_HPP

#include <memory>

namespace stx {

template<class T>
inline T* get_pointer(T* p)
{
    return p;
}

template<class T>
inline T* get_pointer(T& t)
{
    return &t;
}

template<class T>
inline T* get_pointer(const std::auto_ptr<T>& p)
{
    return p.get();
}

template<class T>
struct get_pointer_t
{
    typedef T* type;
};

template<class T>
struct get_pointer_t<T*>
{
    typedef T* type;
};

} // namespace stx

#endif // STX_GET_POINTER_HPP
