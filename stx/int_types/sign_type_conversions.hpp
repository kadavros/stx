#ifndef STX_INT_TYPES_SIGN_TYPE_CONVERSIONS_HPP
#define STX_INT_TYPES_SIGN_TYPE_CONVERSIONS_HPP

#include <stx/int_types/long_long.hpp>

namespace stx {

template <class T>
struct make_signed_t;

template <>
struct make_signed_t<char>
{
    typedef signed char type;
};

template <>
struct make_signed_t<signed char>
{
    typedef signed char type;
};

template <>
struct make_signed_t<unsigned char>
{
    typedef signed char type;
};

template <>
struct make_signed_t<short>
{
    typedef short type;
};

template <>
struct make_signed_t<unsigned short>
{
    typedef short type;
};

template <>
struct make_signed_t<int>
{
    typedef int type;
};

template <>
struct make_signed_t<unsigned int>
{
    typedef int type;
};

template <>
struct make_signed_t<long>
{
    typedef long type;
};

template <>
struct make_signed_t<unsigned long>
{
    typedef long type;
};

#if STX_HAS_LONG_LONG

template <>
struct make_signed_t<long long>
{
    typedef long long type;
};

template <>
struct make_signed_t<unsigned long long>
{
    typedef long long type;
};

#endif

template <class T>
struct make_unsigned_t;

template <>
struct make_unsigned_t<char>
{
    typedef unsigned char type;
};

template <>
struct make_unsigned_t<signed char>
{
    typedef unsigned char type;
};

template <>
struct make_unsigned_t<unsigned char>
{
    typedef unsigned char type;
};

template <>
struct make_unsigned_t<short>
{
    typedef unsigned short type;
};

template <>
struct make_unsigned_t<unsigned short>
{
    typedef unsigned short type;
};

template <>
struct make_unsigned_t<int>
{
    typedef unsigned int type;
};

template <>
struct make_unsigned_t<unsigned int>
{
    typedef unsigned int type;
};

template <>
struct make_unsigned_t<long>
{
    typedef unsigned long type;
};

template <>
struct make_unsigned_t<unsigned long>
{
    typedef unsigned long type;
};

#if STX_HAS_LONG_LONG

template <>
struct make_unsigned_t<long long>
{
    typedef unsigned long long type;
};

template <>
struct make_unsigned_t<unsigned long long>
{
    typedef unsigned long long type;
};

#endif

template <class T>
struct invert_sign_t;

template <>
struct invert_sign_t<char>
{
#if CHAR_MIN < 0
    typedef unsigned char type;
#else
    typedef signed char type;
#endif
};

template <>
struct invert_sign_t<signed char>
{
    typedef unsigned char type;
};

template <>
struct invert_sign_t<unsigned char>
{
    typedef signed char type;
};

template <>
struct invert_sign_t<short>
{
    typedef unsigned short type;
};

template <>
struct invert_sign_t<unsigned short>
{
    typedef short type;
};

template <>
struct invert_sign_t<int>
{
    typedef unsigned int type;
};

template <>
struct invert_sign_t<unsigned int>
{
    typedef int type;
};

template <>
struct invert_sign_t<long>
{
    typedef unsigned long type;
};

template <>
struct invert_sign_t<unsigned long>
{
    typedef long type;
};

#if STX_HAS_LONG_LONG

template <>
struct invert_sign_t<long long>
{
    typedef unsigned long long type;
};

template <>
struct invert_sign_t<unsigned long long>
{
    typedef long long type;
};

#endif

} // namespace stx

#endif // STX_INT_TYPES_SIGN_TYPE_CONVERSIONS_HPP
