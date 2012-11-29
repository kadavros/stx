#ifndef STX_IS_ALIGNED_HPP
#define STX_IS_ALIGNED_HPP

#include <assert.h>
#include <stddef.h>
#include <stx/intptr.hpp>

//  Check if alignment is a power of 2.
#define STX_ASSERT_ALIGNMENT(alignment) \
    assert(alignment && !(alignment & (alignment - 1)));

#define STX_IS_ALIGNED(ptr, alignment) \
    (((reinterpret_cast<uintptr_t>(ptr)) & (alignment - 1)) == 0)

namespace stx {

template <class T>
inline bool is_aligned(const T* p, size_t alignment)
{
    STX_ASSERT_ALIGNMENT(alignment);
    return STX_IS_ALIGNED(p, alignment);
}

//template <class T>
inline bool is_aligned(void (*p)(), size_t alignment)
{
    STX_ASSERT_ALIGNMENT(alignment);
    return STX_IS_ALIGNED(p, alignment);
}

template <class T, class U>
inline bool is_aligned(const U T::*p, size_t alignment)
{
    STX_ASSERT_ALIGNMENT(alignment);
    return STX_IS_ALIGNED(p, alignment);
}

} // namespace stx

#endif // STX_IS_ALIGNED_HPP
