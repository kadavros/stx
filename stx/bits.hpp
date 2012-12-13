#ifndef STX_BITS_HPP
#define STX_BITS_HPP

#include <limits.h>

namespace stx {

template <class UnsignedInteger>
inline UnsignedInteger rotate_right(UnsignedInteger x)
{
    return (x << 1) | (x >> (sizeof(UnsignedInteger) * CHAR_BIT - 1));
}

template <class UnsignedInteger>
inline UnsignedInteger rotate_left(UnsignedInteger x)
{
    return (x >> 1) | (x << (sizeof(UnsignedInteger) * CHAR_BIT - 1));
}

} // namespace stx

#endif // STX_BITS_HPP
