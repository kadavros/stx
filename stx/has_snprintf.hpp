#ifndef STX_HAS_SNPRINTF_HPP
#define STX_HAS_SNPRINTF_HPP

#include <stdio.h>

#ifdef snprintf
inline bool has_snprintf() { return true; }
#else
inline void snprintf() {}
inline bool has_snprintf()
{
    void (*fp1)() = snprintf;
    void (*fp2)() = (void (*)()) ((int (*)(char*, size_t, const char*, ...)) snprintf);
    return (fp1 != fp2);
}
#endif

#endif // STX_HAS_SNPRINTF_HPP
