#ifndef STX_INT_TYPES_EXACT_INT_HPP
#define STX_INT_TYPES_EXACT_INT_HPP

//  Integer types with exact number of bits.
//  Note: not all platforms support every version of int type.
//  
//  int8_t
//  uint8_t
//  int16_t
//  uint16_t
//  int32_t
//  uint32_t
//  int64_t
//  uint64_t
//  STX_HAS_INT8
//  STX_HAS_INT16
//  STX_HAS_INT32
//  STX_HAS_INT64

#include <limits.h>
#include <stx/int_types/long_long.hpp>

#define STX_UINT8_MAX   0xff
#define STX_UINT16_MAX  0xffff
#define STX_UINT32_MAX  0xffffffff
#define STX_UINT64_MAX  0xffffffffffffffff

namespace stx {

#define STX_HAS_INT8  1
#if   UCHAR_MAX  == STX_UINT8_MAX
typedef signed char         int8_t;
typedef unsigned char       uint8_t;
#else
#undef  STX_HAS_INT8
#define STX_HAS_INT8  0
#endif

#define STX_HAS_INT16 1
#if   UCHAR_MAX  == STX_UINT16_MAX
typedef signed char         int16_t;
typedef unsigned char       uint16_t;
#elif USHRT_MAX  == STX_UINT16_MAX
typedef short               int16_t;
typedef unsigned short      uint16_t;
#elif UINT_MAX   == STX_UINT16_MAX
typedef int                 int16_t;
typedef unsigned int        uint16_t;
#elif ULONG_MAX  == STX_UINT16_MAX
typedef long                int16_t;
typedef unsigned long       uint16_t;
#elif STX_HAS_LONG_LONG && STX_ULLONG_MAX == STX_UINT16_MAX
typedef long long           int16_t;
typedef unsigned long long  uint16_t;
#else
#undef  STX_HAS_INT16
#define STX_HAS_INT16 0
#endif

#define STX_HAS_INT32 1
#if   UCHAR_MAX  == STX_UINT32_MAX
typedef signed char         int32_t;
typedef unsigned char       uint32_t;
#elif USHRT_MAX  == STX_UINT32_MAX
typedef short               int32_t;
typedef unsigned short      uint32_t;
#elif UINT_MAX   == STX_UINT32_MAX
typedef int                 int32_t;
typedef unsigned int        uint32_t;
#elif ULONG_MAX  == STX_UINT32_MAX
typedef long                int32_t;
typedef unsigned long       uint32_t;
#elif STX_HAS_LONG_LONG && STX_ULLONG_MAX == STX_UINT32_MAX
typedef long long           int32_t;
typedef unsigned long long  uint32_t;
#else
#undef  STX_HAS_INT32
#define STX_HAS_INT32 0
#endif

#define STX_HAS_INT64 1
#if   UCHAR_MAX  == STX_UINT64_MAX
typedef signed char         int64_t;
typedef unsigned char       uint64_t;
#elif USHRT_MAX  == STX_UINT64_MAX
typedef short               int64_t;
typedef unsigned short      uint64_t;
#elif UINT_MAX   == STX_UINT64_MAX
typedef int                 int64_t;
typedef unsigned int        uint64_t;
#elif ULONG_MAX  == STX_UINT64_MAX
typedef long                int64_t;
typedef unsigned long       uint64_t;
#elif STX_ULLONG_MAX && STX_ULLONG_MAX == STX_UINT64_MAX
typedef long long           int64_t;
typedef unsigned long long  uint64_t;
#else
#undef  STX_HAS_INT64
#define STX_HAS_INT64 0
#endif

} // namespace stx

#endif // STX_INT_TYPES_EXACT_INT_HPP
