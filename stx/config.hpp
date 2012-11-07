#ifndef STX_CONFIG_HPP
#define STX_CONFIG_HPP

#include <climits>

#ifdef LLONG_MAX
#   define STX_HAS_LONG_LONG 1
#else
#   define STX_HAS_LONG_LONG 0
#endif

#include <cfloat>

#ifdef LDBL_MANT_DIG
#   define STX_HAS_LONG_DOUBLE 1
#else
#   define STX_HAS_LONG_DOUBLE 0
#endif

#endif /* STX_CONFIG_HPP */
