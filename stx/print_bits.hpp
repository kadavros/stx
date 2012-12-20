#ifndef STX_PRINT_BITS_HPP
#define STX_PRINT_BITS_HPP

#include <stddef.h>
#include <limits.h>

namespace stx {

template <class Ostream>
inline Ostream& print_bits(Ostream& s, const void* buf, size_t size)
{
    size_t i, j;
    unsigned char *p = (unsigned char*) buf;
    for (i = 0; i < size; ++i, ++p) {
        for (j = 0; j < CHAR_BIT; ++j) {
            s << (unsigned) (((*p) >> j) & 1);
        }
    }
    return s;
}

template <class Ostream>
inline Ostream& println_bits(Ostream& s, const void* buf, size_t size)
{
    print_bits(s, buf, size);
    s << '\n';
    return s;
}

template <class Ostream, class T>
inline Ostream& print_bits(Ostream& s, const T& x)
{
    return print_bits(s, &x, sizeof(x));
}

template <class Ostream, class T>
inline Ostream& println_bits(Ostream& s, const T& x)
{
    return println_bits(s, &x, sizeof(x));
}

template <class Ostream, class ForwardIterator>
inline Ostream& print_bits(Ostream& s, ForwardIterator begin, ForwardIterator end)
{
    for (; begin != end; ++begin) {
        print_bits(s, *begin);
    }
    return s;
}

template <class Ostream, class ForwardIterator>
inline Ostream& println_bits(Ostream& s, ForwardIterator begin, ForwardIterator end)
{
    print_bits(s, begin, end);
    s << '\n';
    return s;
}

template <class Ostream, class ForwardIterator>
inline Ostream& print_bits(Ostream& s, ForwardIterator begin, size_t size)
{
    size_t i;
    for (i = 0; i < size; ++i, ++begin) {
        print_bits(s, *begin);
    }
    return s;
}

template <class Ostream, class ForwardIterator>
inline Ostream& println_bits(Ostream& s, ForwardIterator begin, size_t size)
{
    print_bits(s, begin, size);
    s << '\n';
    return s;
}

} // namespace stx

#endif // STX_PRINT_BITS_HPP
