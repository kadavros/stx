#ifndef STX_SAFE_REALLOC_HPP
#define STX_SAFE_REALLOC_HPP

#include <stddef.h>
#include <stdlib.h>

namespace stx {

inline void* safe_malloc(size_t size)
{
    void* ret = NULL;
    if (size) {
        ret = malloc(size);
    }
    return ret;
}

inline void* safe_calloc(size_t num, size_t size)
{
    void* ret = NULL;
    if ((num <= (~((size_t) 0))/size) && num && size) {
        ret = calloc(num, size);
    }
    return ret;
}

//  If size == 0 is passed, safe_realloc() corresponds to C++03' behavior:
//  memory is freed.
inline void* safe_realloc(void* ptr, size_t size)
{
    void* ret = NULL;
    if (ptr) {
        if (size) {
            ret = realloc(ptr, size);
        } else {
            free(ptr);
        }
    } else if (size) {
        ret = malloc(size);
    }
    return ret;
}

inline void safe_free(void*& ptr)
{
    if (ptr) {
        free(ptr);
        ptr = NULL;
    }
}

} // namespace stx

#endif // STX_SAFE_REALLOC_HPP
