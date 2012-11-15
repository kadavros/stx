#ifndef STX_CONFIG_HPP
#define STX_CONFIG_HPP

#if !defined(STX_PLATFORM_WINDOWS) || !defined(STX_PLATFORM_POSIX)
#   if defined (_WIN32) || defined (_WIN64) || defined (__WIN32__) || defined (__TOS_WIN__) || defined (__WINDOWS__)
#       define STX_PLATFORM_WINDOWS
#   endif
#   if defined(unix) || defined(__unix__) || defined(__unix)
#       define STX_PLATFORM_UNIX
#   endif
#   if defined(STX_PLATFORM_UNIX)
#       include <unistd.h>
#       if defined(_POSIX_VERSION)
#           define STX_PLATFORM_POSIX
#       endif
#   endif
#endif

#include <limits.h>

#ifdef LLONG_MAX
#   define STX_HAS_LONG_LONG 1
#else
#   define STX_HAS_LONG_LONG 0
#endif

#if CHAR_MAX < UCHAR_MAX
#define STX_CHAR_IS_SIGNED   1
#define STX_CHAR_IS_UNSIGNED 0
#else
#define STX_CHAR_IS_SIGNED   0
#define STX_CHAR_IS_UNSIGNED 1
#endif

//  Minimum and maximum values for built-in integer types.
//  We use ((unsigned long) 0) version for unsigned minimum values
//  instead of version with suffix 0UL, because suffixes are known
//  to be not absolutely portable across different implementations
//  at least for some types.
#define STX_BITS_IN_BYTE CHAR_BIT
#define STX_CHAR_MIN     CHAR_MIN
#define STX_CHAR_MAX     CHAR_MAX
#define STX_SCHAR_MIN    SCHAR_MIN
#define STX_SCHAR_MAX    SCHAR_MAX
#define STX_UCHAR_MIN    ((unsigned char) 0)
#define STX_UCHAR_MAX    UCHAR_MAX
#define STX_SHORT_MIN    SHRT_MIN
#define STX_SHORT_MAX    SHRT_MAX
#define STX_USHORT_MIN   ((unsigned short) 0)
#define STX_USHORT_MAX   USHRT_MAX
#define STX_INT_MIN      INT_MIN
#define STX_INT_MAX      INT_MAX
#define STX_UINT_MIN     ((unsigned int) 0)
#define STX_UINT_MAX     UINT_MAX
#define STX_LONG_MIN     LONG_MIN
#define STX_LONG_MAX     LONG_MAX
#define STX_ULONG_MIN    ((unsigned long) 0)
#define STX_ULONG_MAX    ULONG_MAX
#if STX_HAS_LONG_LONG
#define STX_LLONG_MIN    LLONG_MIN
#define STX_LLONG_MAX    LLONG_MAX
#define STX_ULLONG_MIN   ((unsigned long long) 0)
#define STX_ULLONG_MAX   ULLONG_MAX
#endif

#include <float.h>

#ifdef LDBL_MANT_DIG
#   define STX_HAS_LONG_DOUBLE 1
#else
#   define STX_HAS_LONG_DOUBLE 0
#endif

#define STX_MAX(x, y) (((x) > (y)) ? (x) : (y))
#define STX_MIN(x, y) (((x) < (y)) ? (x) : (y))
#define STX_EQUAL(x, y) ((x) == (y))

#endif /* STX_CONFIG_HPP */
