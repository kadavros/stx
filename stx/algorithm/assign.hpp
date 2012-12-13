#ifndef STX_ALGORITHM_ASSIGN_HPP
#define STX_ALGORITHM_ASSIGN_HPP

#include <stx/algorithm/begin.hpp>
#include <stx/algorithm/end.hpp>

#include <stddef.h>

#include <vector>
#include <deque>
#include <list>
#include <string>

//#include <bitset>
//#include <valarray>

//#include <set>
//#include <map>

//#include <queue>
//#include <stack>

//#if __cplusplus >= 201103L
//#include <array>
//#include <forward_list>
//#include <unordered_map>
//#include <unordered_set>
//#endif

namespace stx {

template <class T1, class T2>
inline T1&
assign(T1& x1, const T2& x2)
{
    x1 = x2;
    return x1;
}

template <class T1, class T2, size_t Size>
inline T1 (&assign(T1 (&x1)[Size], const T2 (&x2)[Size]))[Size]
{
    for (size_t i = 0; i < Size; ++i) {
        x1[i] = x2[i];
    }
    return x1;
}

template <class T, class A, class Container>
inline std::vector<T, A>&
assign(std::vector<T, A>& x1, const Container& x2)
{
    x1.assign(begin(x2), end(x2));
    return x1;
}

template <class T, class A, class Container>
inline std::deque<T, A>&
assign(std::deque<T, A>& x1, const Container& x2)
{
    x1.assign(begin(x2), end(x2));
    return x1;
}

template <class T, class A, class Container>
inline std::list<T, A>&
assign(std::list<T, A>& x1, const Container& x2)
{
    x1.assign(begin(x2), end(x2));
    return x1;
}

template <class Char, class Traits, class Allocator, class Container>
inline std::basic_string<Char, Traits, Allocator>&
assign(std::basic_string<Char, Traits, Allocator>& x1, const Container& x2)
{
    x1.assign(begin(x2), end(x2));
    return x1;
}

} // namespace stx

#endif // STX_ALGORITHM_ASSIGN_HPP
