#ifndef STX_ALGORITHM_END_HPP
#define STX_ALGORITHM_END_HPP

#include <stddef.h>

namespace stx {

template <class Container>
inline typename Container::iterator
end(Container& c)
{
    return c.end();
}

template <class Container>
inline typename Container::const_iterator
end(const Container& c)
{
    return c.end();
}

template <class T, size_t Size>
inline const T*
end(const T (&x)[Size])
{
    return &x[Size];
}

} // namespace stx

#endif // STX_ALGORITHM_END_HPP
