#ifndef STX_INTPTR_HPP
#define STX_INTPTR_HPP

//  Typedefs for intptr_t & uintptr_t.

#include <stddef.h>
#include <limits.h>

namespace stx {

template <size_t N>
struct intptr_t_impl;

template <>
struct intptr_t_impl<sizeof(char)>
{
    typedef signed char signed_type;
    typedef unsigned char unsigned_type;
};

#if USHRT_MAX != UCHAR_MAX
template <>
struct intptr_t_impl<sizeof(short)>
{
    typedef short signed_type;
    typedef unsigned short unsigned_type;
};
#endif

#if UINT_MAX != USHRT_MAX
template <>
struct intptr_t_impl<sizeof(int)>
{
    typedef int signed_type;
    typedef unsigned int unsigned_type;
};
#endif

#if ULONG_MAX != UINT_MAX
template <>
struct intptr_t_impl<sizeof(long)>
{
    typedef long signed_type;
    typedef unsigned long unsigned_type;
};
#endif

#ifdef ULLONG_MAX
#if ULLONG_MAX != ULONG_MAX
template <>
struct intptr_t_impl<sizeof(long long)>
{
    typedef long long signed_type;
    typedef unsigned long long unsigned_type;
};
#endif
#endif

typedef intptr_t_impl<sizeof(void*)>::signed_type intptr_t;
typedef intptr_t_impl<sizeof(void*)>::unsigned_type uintptr_t;

} // namespace stx

#endif // STX_INTPTR_HPP
