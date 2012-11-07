#ifndef STX_LOG_CONFIG_HPP
#define STX_LOG_CONFIG_HPP

//  Platform selection:
//      STX_PLATFORM_WINDOWS
//      STX_PLATFORM_POSIX

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

#endif // STX_LOG_CONFIG_HPP
