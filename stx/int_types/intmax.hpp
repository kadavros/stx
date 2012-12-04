#ifndef STX_INT_TYPES_INTMAX_HPP
#define STX_INT_TYPES_INTMAX_HPP

#include <stx/int_types/long_long.hpp>

namespace stx {

#if STX_HAS_LONG_LONG
typedef llong         intmax_t;
typedef ullong        uintmax_t;
#else
typedef long          intmax_t;
typedef unsigned long uintmax_t;
#endif

} // namespace stx

#endif // STX_INT_TYPES_INTMAX_HPP
