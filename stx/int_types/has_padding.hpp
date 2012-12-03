#ifndef STX_INT_TYPES_HAS_PADDING_HPP
#define STX_INT_TYPES_HAS_PADDING_HPP

#include <limits>
#include <limits.h>
#include <stx/int_types/long_long.hpp>

namespace stx {

template <class IntegerType>
inline bool has_padding();

template <class UnsignedIntegerType>
inline bool has_padding_impl()
{
    UnsignedIntegerType x = std::numeric_limits<UnsignedIntegerType>::max();
    size_t num_bits = 0;
    for (; x != 0; x >>= 1) {
        ++num_bits;
    }
    return num_bits != CHAR_BIT * sizeof(UnsignedIntegerType);
}

template <>
inline bool has_padding<char>()
{
    return false;
}

template <>
inline bool has_padding<signed char>()
{
    return false;
}

template <>
inline bool has_padding<unsigned char>()
{
    return false;
}

template <>
inline bool has_padding<unsigned short>()
{
    return has_padding_impl<unsigned short>();
}

template <>
inline bool has_padding<unsigned int>()
{
    return has_padding_impl<unsigned int>();
}

#if STX_HAS_LONG_LONG
template <>
inline bool has_padding<unsigned long long>()
{
    return has_padding_impl<unsigned long long>();
}
#endif

} // namespace stx

#endif // STX_INT_TYPES_HAS_PADDING_HPP
