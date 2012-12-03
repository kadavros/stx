#ifndef STX_INT_TYPES_LONG_LONG_HPP
#define STX_INT_TYPES_LONG_LONG_HPP

#include <limits.h>

#if defined(LLONG_MAX) || defined(LONG_LONG_MAX)
#   define STX_HAS_LONG_LONG 1
#else
#   define STX_HAS_LONG_LONG 0
#endif

#if defined(LONG_LONG_MAX)
#   define STX_LLONG_MIN  LONG_LONG_MIN
#   define STX_LLONG_MAX  LONG_LONG_MAX
#   define STX_ULLONG_MIN 0ULL
#   define STX_ULLONG_MAX ULONG_LONG_MAX
#elif defined(LLONG_MAX)
#   define STX_LLONG_MIN  LLONG_MIN
#   define STX_LLONG_MAX  LLONG_MAX
#   define STX_ULLONG_MIN 0ULL
#   define STX_ULLONG_MAX ULLONG_MAX
#endif

#endif // STX_INT_TYPES_LONG_LONG_HPP
