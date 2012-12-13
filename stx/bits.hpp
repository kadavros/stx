#ifndef STX_BITS_HPP
#define STX_BITS_HPP

#include <limits.h>
#include <stx/int_types/long_long.hpp>

namespace stx {

template <class T> struct unsigned_type_guard;

#if CHAR_MAX == UCHAR_MAX
template <> struct unsigned_type_guard<char> { typedef char type; };
#endif
template <> struct unsigned_type_guard<unsigned char> { typedef unsigned char type; };
template <> struct unsigned_type_guard<unsigned short> { typedef unsigned short type; };
template <> struct unsigned_type_guard<unsigned int> { typedef unsigned int type; };
template <> struct unsigned_type_guard<unsigned long> { typedef unsigned long type; };
#if STX_HAS_LONG_LONG
template <> struct unsigned_type_guard<ullong> { typedef ullong type; };
#endif

template <class T>
inline T rotate_right(T x)
{
    typedef typename unsigned_type_guard<T>::type type;
    return (x << 1) | (x >> (sizeof(T) * CHAR_BIT - 1));
}

template <class T>
inline T rotate_left(T x)
{
    typedef typename unsigned_type_guard<T>::type type;
    return (x >> 1) | (x << (sizeof(T) * CHAR_BIT - 1));
}

} // namespace stx

#endif // STX_BITS_HPP
