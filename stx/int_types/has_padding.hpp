#ifndef STX_INT_TYPES_HAS_PADDING_HPP
#define STX_INT_TYPES_HAS_PADDING_HPP

#include <limits.h>
#include <stx/int_types/long_long.hpp>
#include <stx/int_types/int_limits.hpp>

namespace stx {

template <uintmax_t X>
struct has_padding_impl
{
    enum { value = (X == 0 ? 0 : 1) + has_padding_impl<(X >> 1)>::value };
};

template <>
struct has_padding_impl<0>
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
    enum { value = (sizeof(value_type)*CHAR_BIT != has_padding_impl<int_limits<value_type>::max >::value) };
};

template <>
struct has_padding<short>
{
    typedef short value_type;
    enum { value =
        (
            (has_padding<unsigned value_type>::value == 0) &&
            ((int_limits<unsigned value_type>::max >> 1) == int_limits<value_type>::max)
        ) ? 0 : 1
    };
};

template <>
struct has_padding<unsigned int>
{
    typedef unsigned int value_type;
    enum { value = (sizeof(value_type)*CHAR_BIT != has_padding_impl<int_limits<value_type>::max >::value) };
};

template <>
struct has_padding<int>
{
    typedef int value_type;
    enum { value =
        (
            (has_padding<unsigned value_type>::value == 0) &&
            ((int_limits<unsigned value_type>::max >> 1) == int_limits<value_type>::max)
        ) ? 0 : 1
    };
};

template <>
struct has_padding<unsigned long>
{
    typedef unsigned long value_type;
    enum { value = (sizeof(value_type)*CHAR_BIT != has_padding_impl<int_limits<value_type>::max >::value) };
};

template <>
struct has_padding<long>
{
    typedef long value_type;
    enum { value =
        (
            (has_padding<unsigned value_type>::value == 0) &&
            ((int_limits<unsigned value_type>::max >> 1) == int_limits<value_type>::max)
        ) ? 0 : 1
    };
};

#if STX_HAS_LONG_LONG

template <>
struct has_padding<unsigned long long>
{
    typedef unsigned long long value_type;
    enum { value = (sizeof(value_type)*CHAR_BIT != has_padding_impl<int_limits<value_type>::max >::value) };
};

template <>
struct has_padding<long long>
{
    typedef long long value_type;
    enum { value =
        (
            (has_padding<unsigned value_type>::value == 0) &&
            ((int_limits<unsigned value_type>::max >> 1) == int_limits<value_type>::max)
        ) ? 0 : 1
    };
};

#endif

} // namespace stx

#endif // STX_INT_TYPES_HAS_PADDING_HPP
