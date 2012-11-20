#ifndef STX_SAFE_ABS_HPP
#define STX_SAFE_ABS_HPP

/*
    ISO/IEC 9899:1999 7.20.6.1 The abs, labs and llabs functions
    The abs, labs, and llabs functions compute the absolute value of an integer j.
    If the result cannot be represented, the behavior is undeﬁned. The absolute
    value of the most negative number cannot be represented in two’s complement.
    E.g.: abs(INT_MIN), labs(LONG_MIN), llabs(LLONG_MIN) - undefined behavior.
*/

#include <limits.h>

namespace stx {

inline unsigned int safe_abs(int n)
{
    unsigned int ret;
    if (n > 0) {
        ret = n;
    } else {
        ret = -n;
    }
    return ret;
}

inline unsigned long safe_abs(long n)
{
    unsigned long ret;
    if (n > 0) {
        ret = n;
    } else {
        ret = -n;
    }
    return ret;
}

#ifdef LLONG_MAX
inline unsigned long long safe_abs(long long n)
{
    unsigned long long ret;
    if (n > 0) {
        ret = n;
    } else {
        ret = -n;
    }
    return ret;
}
#endif

} // namespace stx

#endif // STX_SAFE_ABS_HPP
