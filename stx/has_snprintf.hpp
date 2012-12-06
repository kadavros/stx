#ifndef STX_HAS_SNPRINTF_HPP
#define STX_HAS_SNPRINTF_HPP

#include <stx/has_function.hpp>

#include <stdio.h>

#ifdef snprintf
inline bool has_snprintf() { return true; };
inline int (*snprintf_ptr())(char*, size_t, const char*, ...) { return snprintf; }
#else
STX_DECLARE_HAS_FUNCTION(snprintf, int, (char*, size_t, const char*, ...))
#endif

#endif // STX_HAS_SNPRINTF_HPP
