#ifndef STX_SAFE_REALLOC_HPP
#define STX_SAFE_REALLOC_HPP

#include <cstddef>
#include <cstdlib>

namespace stx {

inline void* safe_malloc(std::size_t size)
{
    void* ret = NULL;
    if (size) {
        ret = std::malloc(size);
    }
    return ret;
}

inline void* safe_calloc(std::size_t num, std::size_t size)
{
    void* ret = NULL;
    if ((num <= (~((std::size_t) 0))/size) && num && size) {
        ret = std::calloc(num, size);
    }
    return ret;
}

//  If size == 0 is passed, safe_realloc() corresponds to C++03' behavior:
//  memory is freed.
inline void* safe_realloc(void* ptr, std::size_t size)
{
    void* ret = NULL;
    if (ptr) {
        if (size) {
            ret = std::realloc(ptr, size);
        } else {
            std::free(ptr);
        }
    } else if (size) {
        ret = std::malloc(size);
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
