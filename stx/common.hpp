#ifndef STX_COMMON_HPP
#define STX_COMMON_HPP

#include <stx/config.hpp>

#ifndef NDEBUG
#   define STX_DEBUG 0
#else
#   define STX_DEBUG 1
#endif

#define STX_CSTR_(x) #x
#define STX_CSTR(x) STX_CSTR_(x)

namespace stx {

typedef signed char        schar;
typedef unsigned char      uchar;
typedef unsigned short     ushort;
typedef unsigned int       uint;
typedef unsigned long      ulong;
typedef long double        ldouble;
#if STX_HAS_LONG_LONG
typedef long long          llong;
typedef unsigned long long ullong;
#endif

} // namespace stx

#endif // STX_COMMON_HPP
