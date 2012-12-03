#ifndef STX_INT_TYPES_INT_LIMITS_HPP
#define STX_INT_TYPES_INT_LIMITS_HPP

#include <stx/int_types/long_long.hpp>
#include <cwchar>

namespace stx {

template <class T>
struct int_limits;

template <>
struct int_limits<wchar_t>
{
    enum {
        is_signed = WCHAR_MIN < 0 ? 1 : 0,
        is_unsigned = WCHAR_MIN < 0 ? 0 : 1,
        radix = 2,
        min = WCHAR_MIN,
        max = WCHAR_MAX
    };
};

template <>
struct int_limits<char>
{
    enum {
        is_signed = CHAR_MIN < 0 ? 1 : 0,
        is_unsigned = CHAR_MIN < 0 ? 0 : 1,
        radix = 2,
        min = CHAR_MIN,
        max = CHAR_MAX
    };
};

template <>
struct int_limits<signed char>
{
    enum {
        is_signed = 1,
        is_unsigned = 0,
        radix = 2,
        min = SCHAR_MIN,
        max = SCHAR_MAX
    };
};

template <>
struct int_limits<unsigned char>
{
    enum {
        is_signed = 0,
        is_unsigned = 1,
        radix = 2,
        min = 0,
        max = UCHAR_MAX
    };
};

template <>
struct int_limits<short>
{
    enum {
        is_signed = 1,
        is_unsigned = 0,
        radix = 2,
        min = SHRT_MIN,
        max = SHRT_MAX
    };
};

template <>
struct int_limits<unsigned short>
{
    enum {
        is_signed = 0,
        is_unsigned = 1,
        radix = 2,
        min = 0,
        max = USHRT_MAX
    };
};

template <>
struct int_limits<int>
{
    enum {
        is_signed = 1,
        is_unsigned = 0,
        radix = 2,
        min = INT_MIN,
        max = INT_MAX
    };
};

template <>
struct int_limits<unsigned int>
{
    enum {
        is_signed = 0,
        is_unsigned = 1,
        radix = 2,
        min = 0,
        max = UINT_MAX
    };
};

template <>
struct int_limits<long>
{
    enum {
        is_signed = 1,
        is_unsigned = 0,
        radix = 2,
        min = LONG_MIN,
        max = LONG_MAX
    };
};

template <>
struct int_limits<unsigned long>
{
    enum {
        is_signed = 0,
        is_unsigned = 1,
        radix = 2,
        min = 0,
        max = ULONG_MAX
    };
};

#if STX_HAS_LONG_LONG

template <>
struct int_limits<long long>
{
    enum {
        is_signed = 1,
        is_unsigned = 0,
        radix = 2,
        min = STX_LLONG_MIN,
        max = STX_LLONG_MAX
    };
};

template <>
struct int_limits<unsigned long long>
{
    enum {
        is_signed = 0,
        is_unsigned = 1,
        radix = 2,
        min = 0,
        max = STX_ULLONG_MAX
    };
};

#endif

} // namespace stx

#endif // STX_INT_TYPES_INT_LIMITS_HPP
