#ifndef STX_ALIGNMENT_ALIGNED_STORAGE_HPP
#define STX_ALIGNMENT_ALIGNED_STORAGE_HPP

#include <stddef.h>
#include <stx/alignment/alignment_of.hpp>
#include <stx/alignment/max_alignment.hpp>

namespace stx {

template <size_t Size, size_t Alignment = STX_MAX_ALIGNMENT>
struct aligned_storage
{
    typedef struct
    {
        union
        {
            unsigned char buf_[Size];
            unsigned char alignment_[Alignment];
        };
    } type;
};

} // namespace stx

#endif // STX_ALIGNMENT_ALIGNED_STORAGE_HPP
