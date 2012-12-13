#ifndef STX_ALGORITHM_ALL_OF_HPP
#define STX_ALGORITHM_ALL_OF_HPP

#include <stx/algorithm/begin.hpp>
#include <stx/algorithm/end.hpp>

namespace stx {

template <class InputIterator, class Predicate>
inline bool
all_of(InputIterator first, InputIterator last, Predicate pred)
{
    for (; first != last; ++first) {
        if (!pred(*first)) {
            return false;
        }
    }
    return true;
}

template <class Container, class Predicate>
inline bool
all_of(const Container& c, Predicate pred)
{
    return all_of(begin(c), end(c), pred);
}

} // namespace stx

#endif // STX_ALGORITHM_ALL_OF_HPP
