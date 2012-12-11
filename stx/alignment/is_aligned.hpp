#ifndef STX_ALIGNMENT_IS_ALIGNED_HPP
#define STX_ALIGNMENT_IS_ALIGNED_HPP

#include <assert.h>
#include <stddef.h>
#include <stx/int_types/intptr.hpp>

//  Check if alignment is a power of 2.
#define STX_ASSERT_ALIGNMENT(alignment) \
    assert(alignment && !(alignment & (alignment - 1)));

#define STX_IS_ALIGNED(ptr, alignment) \
    (((reinterpret_cast<uintptr_t>(ptr)) & (alignment - 1)) == 0)

namespace stx {

inline bool is_aligned(const void* p, size_t alignment)
{
    STX_ASSERT_ALIGNMENT(alignment);
    return STX_IS_ALIGNED(p, alignment);
}

inline bool is_aligned(void (*p)(), size_t alignment)
{
    STX_ASSERT_ALIGNMENT(alignment);
    return STX_IS_ALIGNED(p, alignment);
}

template <class T, class U>
inline bool is_aligned(U T::*p, size_t alignment)
{
    STX_ASSERT_ALIGNMENT(alignment);
    return STX_IS_ALIGNED(p, alignment);
}

} // namespace stx

#endif // STX_ALIGNMENT_IS_ALIGNED_HPP
