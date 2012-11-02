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



#endif // STX_COMMON_HPP
