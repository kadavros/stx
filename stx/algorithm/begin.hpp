#ifndef STX_ALGORITHM_BEGIN_HPP
#define STX_ALGORITHM_BEGIN_HPP

#include <stddef.h>

namespace stx {

template <class Container>
inline typename Container::iterator
begin(Container& c)
{
    return c.begin();
}

template <class Container>
inline typename Container::const_iterator
begin(const Container& c)
{
    return c.begin();
}

template <class T, size_t Size>
inline T*
begin(T (&x)[Size])
{
    return &x[0];
}

template <class T, size_t Size>
inline const T*
begin(const T (&x)[Size])
{
    return &x[0];
}

} // namespace stx

#endif // STX_ALGORITHM_BEGIN_HPP
