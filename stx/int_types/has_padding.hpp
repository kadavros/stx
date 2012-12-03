#ifndef STX_INT_TYPES_HAS_PADDING_HPP
#define STX_INT_TYPES_HAS_PADDING_HPP

#include <limits.h>
#include <stx/int_types/long_long.hpp>
#include <stx/int_types/int_limits.hpp>

namespace stx {

template <uintmax_t X>
struct has_padding_impl_t
{
    enum { value = (X == 0 ? 0 : 1) + has_padding_impl_t<(X >> 1)>::value };
};

template <>
struct has_padding_impl_t<0>
{
    enum { value = 0 };
};

template <class T>
struct has_padding_t;

template <>
struct has_padding_t<char>
{
    typedef char value_type;
    enum { value = 0 };
};

template <>
struct has_padding_t<signed char>
{
    typedef signed char value_type;
    enum { value = 0 };
};

template <>
struct has_padding_t<unsigned char>
{
    typedef unsigned char value_type;
    enum { value = 0 };
};

template <>
struct has_padding_t<unsigned short>
{
    typedef unsigned short value_type;
    enum { value = (sizeof(value_type)*CHAR_BIT != has_padding_impl_t<int_limits<value_type>::max >::value) };
};

template <>
struct has_padding_t<unsigned int>
{
    typedef unsigned int value_type;
    enum { value = (sizeof(value_type)*CHAR_BIT != has_padding_impl_t<int_limits<value_type>::max >::value) };
};

template <>
struct has_padding_t<unsigned long>
{
    typedef unsigned long value_type;
    enum { value = (sizeof(value_type)*CHAR_BIT != has_padding_impl_t<int_limits<value_type>::max >::value) };
};

#if STX_HAS_LONG_LONG

template <>
struct has_padding_t<unsigned long long>
{
    typedef unsigned long long value_type;
    enum { value = (sizeof(value_type)*CHAR_BIT != has_padding_impl_t<int_limits<value_type>::max >::value) };
};

#endif

} // namespace stx

#endif // STX_INT_TYPES_HAS_PADDING_HPP
