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
