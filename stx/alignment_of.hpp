#ifndef STX_ALIGNMENT_OF_HPP
#define STX_ALIGNMENT_OF_HPP

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
   enum { value = A < S ? A : S };
};

template <typename T>
struct alignment_of
{
    enum {
        value = alignment_logic <
            sizeof(alignment_of_hack<T>) - sizeof(T),
            sizeof(T)
        >::value
    };
};

} // namespace stx

#endif // STX_ALIGNMENT_OF_HPP
