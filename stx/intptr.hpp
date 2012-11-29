#ifndef STX_INTPTR_HPP
#define STX_INTPTR_HPP

//  Typedefs for intptr_t & uintptr_t.

#include <limits.h>

namespace stx {

#ifdef LLONG_MAX
typedef long long intptr_t;
typedef unsigned long long uintptr_t;
#else
typedef long intptr_t;
typedef unsigned long uintptr_t;
#endif

} // namespace stx

#endif // STX_INTPTR_HPP
