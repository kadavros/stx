#ifndef STX_INT_TYPES_HPP
#define STX_INT_TYPES_HPP

#include <stx/int_types/long_long.hpp>
#include <stx/int_types/exact_int.hpp>
#include <stx/int_types/intptr.hpp>
#include <stx/int_types/has_padding.hpp>

//  todo: padding of integer types
//  todo: least_int

namespace stx {

typedef signed char        schar;
typedef unsigned char      uchar;

typedef short              sshort;
typedef unsigned short     ushort;

typedef int                sint;
typedef unsigned int       uint;

typedef long               slong;
typedef unsigned long      ulong;

#if STX_HAS_LONG_LONG 
typedef long long          llong;
typedef long long          sllong;
typedef unsigned long long ullong;
#endif

} // namespace stx

#endif // STX_INT_TYPES_HPP
