#ifndef STX_EXACT_INT_HPP
#define STX_EXACT_INT_HPP

//  Integer types with exact bitness.
//  Note: not all platforms support every version of exact_int type.
//  
//  exact_int8_t
//  exact_uint8_t
//  exact_int16_t
//  exact_uint16_t
//  exact_int32_t
//  exact_uint32_t
//  exact_int64_t
//  exact_uint64_t
//  STX_HAS_EXACT_INT8
//  STX_HAS_EXACT_INT16
//  STX_HAS_EXACT_INT32
//  STX_HAS_EXACT_INT64

#include <limits.h>

namespace stx {

#define STX_HAS_EXACT_INT8  1
#if   UCHAR_MAX  == 0xff
typedef signed char         exact_int8_t;
typedef unsigned char       exact_uint8_t;
#else
#undef  STX_HAS_EXACT_INT8
#define STX_HAS_EXACT_INT8  0
#endif

#define STX_HAS_EXACT_INT16 1
#if   UCHAR_MAX  == 0xffff
typedef signed char         exact_int16_t;
typedef unsigned char       exact_uint16_t;
#elif USHRT_MAX  == 0xffff
typedef short               exact_int16_t;
typedef unsigned short      exact_uint16_t;
#elif UINT_MAX   == 0xffff
typedef int                 exact_int16_t;
typedef unsigned int        exact_uint16_t;
#elif ULONG_MAX  == 0xffff
typedef long                exact_int16_t;
typedef unsigned long       exact_uint16_t;
#elif defined(ULLONG_MAX) && ULLONG_MAX == 0xffff
typedef long long           exact_int16_t;
typedef unsigned long long  exact_uint16_t;
#else
#undef  STX_HAS_EXACT_INT16
#define STX_HAS_EXACT_INT16 0
#endif

#define STX_HAS_EXACT_INT32 1
#if   UCHAR_MAX  == 0xffffffff
typedef signed char         exact_int32_t;
typedef unsigned char       exact_uint32_t;
#elif USHRT_MAX  == 0xffffffff
typedef short               exact_int32_t;
typedef unsigned short      exact_uint32_t;
#elif UINT_MAX   == 0xffffffff
typedef int                 exact_int32_t;
typedef unsigned int        exact_uint32_t;
#elif ULONG_MAX  == 0xffffffff
typedef long                exact_int32_t;
typedef unsigned long       exact_uint32_t;
#elif defined(ULLONG_MAX) && ULLONG_MAX == 0xffffffff
typedef long long           exact_int32_t;
typedef unsigned long long  exact_uint32_t;
#else
#undef  STX_HAS_EXACT_INT32
#define STX_HAS_EXACT_INT32 0
#endif

#define STX_HAS_EXACT_INT64 1
#if   UCHAR_MAX  == 0xffffffffffffffffULL
typedef signed char         exact_int64_t;
typedef unsigned char       exact_uint64_t;
#elif USHRT_MAX  == 0xffffffffffffffffULL
typedef short               exact_int64_t;
typedef unsigned short      exact_uint64_t;
#elif UINT_MAX   == 0xffffffffffffffffULL
typedef int                 exact_int64_t;
typedef unsigned int        exact_uint64_t;
#elif ULONG_MAX  == 0xffffffffffffffffULL
typedef long                exact_int64_t;
typedef unsigned long       exact_uint64_t;
#elif ULLONG_MAX && ULLONG_MAX == 0xffffffffffffffffULL
typedef long long           exact_int64_t;
typedef unsigned long long  exact_uint64_t;
#else
#undef  STX_HAS_EXACT_INT64
#define STX_HAS_EXACT_INT64 0
#endif

} // namespace stx

#endif // STX_EXACT_INT_HPP
