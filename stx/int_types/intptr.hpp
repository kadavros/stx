#ifndef STX_INT_TYPES_INTPTR_HPP
#define STX_INT_TYPES_INTPTR_HPP

//  Typedefs for intptr_t & uintptr_t.
//
//  We are using template metaprogramming to make sure that we select
//  integer of minimal size for (u)intptr_t. More simple version would be
//  like this (it selects integer of maximum size, but avoids problems
//  with padding bits in integers, which is really rare problem nowadays):
//  
//  #include <limits.h>
//  #if defined(LLONG_MAX) || defined(LONG_LONG_MAX)
//  typedef long long intptr_t;
//  typedef unsigned long long uintptr_t;
//  #else
//  typedef long intptr_t;
//  typedef unsigned long uintptr_t;
//  #endif

#include <stddef.h>
#include <limits.h>
#include <stx/int_types/long_long.hpp>

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

#if STX_HAS_LONG_LONG
#if STX_ULLONG_MAX != ULONG_MAX
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

#endif // STX_INT_TYPES_INTPTR_HPP
