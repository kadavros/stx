#ifndef STX_DEFAULT_DELETE_HPP
#define STX_DEFAULT_DELETE_HPP

#ifndef STX_NOEXCEPT
#   if __cplusplus >= 201103L
#       define STX_NOEXCEPT noexcept
#   else
#       define STX_NOEXCEPT throw()
#   endif
#endif

namespace stx {

template <class T>
struct default_delete
{
    default_delete() STX_NOEXCEPT
    {
    }
    
    void operator() (T* p) const STX_NOEXCEPT
    {
        delete p;
    }
};

template <class T>
struct default_delete<T[]>
{
    void operator() (T* p) const STX_NOEXCEPT
    {
        delete[] p;
    }
};

} // namespace stx

#endif // STX_DEFAULT_DELETE_HPP
