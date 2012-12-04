#ifndef STX_INT_TYPES_HAS_PADDING_HPP
#define STX_INT_TYPES_HAS_PADDING_HPP

#include <limits.h>
#include <stx/int_types/long_long.hpp>
#include <stx/int_types/int_limits.hpp>
#include <stx/int_types/intmax.hpp>

namespace stx {

template <uintmax_t X>
struct effective_bits_num
{
    enum { value = (X == 0 ? 0 : 1) + effective_bits_num<(X >> 1)>::value };
};

template <>
struct effective_bits_num<0>
{
    enum { value = 0 };
};

template <class T>
struct has_padding;

template <>
struct has_padding<char>
{
    typedef char value_type;
    enum { value = 0 };
};

template <>
struct has_padding<signed char>
{
    typedef signed char value_type;
    enum { value = 0 };
};

template <>
struct has_padding<unsigned char>
{
    typedef unsigned char value_type;
    enum { value = 0 };
};

template <>
struct has_padding<unsigned short>
{
    typedef unsigned short value_type;
    enum { value = (sizeof(value_type)*CHAR_BIT != effective_bits_num<USHRT_MAX>::value) };
};

template <>
struct has_padding<short>
{
    typedef short value_type;
    typedef unsigned short unsigned_value_type;
    enum { value =
        (
            (has_padding<unsigned_value_type>::value == 0) &&
            ((int_limits<unsigned_value_type>::max >> 1) == SHRT_MAX)
        ) ? 0 : 1
    };
};

template <>
struct has_padding<unsigned int>
{
    typedef unsigned int value_type;
    enum { value = (sizeof(value_type)*CHAR_BIT != effective_bits_num<UINT_MAX>::value) };
};

template <>
struct has_padding<int>
{
    typedef int value_type;
    typedef unsigned int unsigned_value_type;
    enum { value =
        (
            (has_padding<unsigned_value_type>::value == 0) &&
            ((int_limits<unsigned_value_type>::max >> 1) == INT_MAX)
        ) ? 0 : 1
    };
};

template <>
struct has_padding<unsigned long>
{
    typedef unsigned long value_type;
    enum { value = (sizeof(value_type)*CHAR_BIT != effective_bits_num<ULONG_MAX>::value) };
};

template <>
struct has_padding<long>
{
    typedef long value_type;
    typedef unsigned long unsigned_value_type;
    enum { value =
        (
            (has_padding<unsigned_value_type>::value == 0) &&
            ((int_limits<unsigned_value_type>::max >> 1) == LONG_MAX)
        ) ? 0 : 1
    };
};

#if STX_HAS_LONG_LONG

template <>
struct has_padding<ullong>
{
    typedef ullong value_type;
    enum { value = (sizeof(value_type)*CHAR_BIT != effective_bits_num<STX_ULLONG_MAX>::value) };
};

template <>
struct has_padding<llong>
{
    typedef llong value_type;
    typedef ullong unsigned_value_type;
    enum { value =
        (
            (has_padding<unsigned_value_type>::value == 0) &&
            ((int_limits<unsigned_value_type>::max >> 1) == STX_LLONG_MAX)
        ) ? 0 : 1
    };
};

#endif

} // namespace stx

#endif // STX_INT_TYPES_HAS_PADDING_HPP
