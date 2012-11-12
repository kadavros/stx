#ifndef STX_ALIGNMENT_OF_HPP
#define STX_ALIGNMENT_OF_HPP

#include <stddef.h>

namespace stx {

template <typename T> struct alignment_of;

template <typename T>
struct alignment_of_hack
{
    char c;
    T t;
    alignment_of_hack();
};

template <unsigned A, unsigned S>
struct alignment_logic
{
   static const size_t value = A < S ? A : S;
};

template <typename T>
struct alignment_of
{
    static const size_t value = alignment_logic <
       sizeof(alignment_of_hack<T>) - sizeof(T),
       sizeof(T)
    >::value;
};

} // namespace stx

#endif // STX_ALIGNMENT_OF_HPP
