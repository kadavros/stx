#ifndef STX_ALGORITHM_ASSIGN_HPP
#define STX_ALGORITHM_ASSIGN_HPP

#include <stddef.h>

#include <bitset>
#include <valarray>

#include <vector>
#include <deque>
#include <list>
#include <string>

#include <set>
#include <map>

#include <queue>
#include <stack>

#if __cplusplus >= 201103L
#include <array>
#include <forward_list>
#include <unordered_map>
#include <unordered_set>
#endif

namespace stx {

template <class T1, class T2>
inline T1&
assign(T1& x1, const T2& x2)
{
    x1 = x2;
    return x1;
}

template <size_t N>
inline std::bitset<N>&
assign(std::bitset<N>& x1, const std::bitset<N>& x2)
{
    x1 = x2;
    return x1;
}

template <class T, class A, class Container>
inline std::vector<T, A>&
assign(std::vector<T, A>& x1, const Container& x2)
{
    x1.assign(x2.begin(), x2.end());
    return x1;
}

template <class T, class A, class Container>
inline std::deque<T, A>&
assign(std::deque<T, A>& x1, const Container& x2)
{
    x1.assign(x2.begin(), x2.end());
    return x1;
}

template <class T, class A, class Container>
inline std::list<T, A>&
assign(std::list<T, A>& x1, const Container& x2)
{
    x1.assign(x2.begin(), x2.end());
    return x1;
}

template <class Char, class Traits, class Allocator, class Container>
inline std::basic_string<Char, Traits, Allocator>&
assign(std::basic_string<Char, Traits, Allocator>& x1, const Container& x2)
{
    x1.assign(x2.begin(), x2.end());
    return x1;
}

} // namespace stx

#endif // STX_ALGORITHM_ASSIGN_HPP
