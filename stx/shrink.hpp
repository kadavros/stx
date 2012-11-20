#ifndef STX_SHRINK_HPP
#define STX_SHRINK_HPP

#include <string>
#include <vector>
#include <deque>

namespace stx {

template <typename Char, typename Traits, typename Allocator>
inline void shrink(std::basic_string<Char, Traits, Allocator>& v)
{
    std::basic_string<Char, Traits, Allocator>(v.begin(), v.end()).swap(v);
}

template <typename T, typename Allocator>
inline void shrink(std::vector<T, Allocator>& v)
{
    std::vector<T, Allocator>(v.begin(), v.end()).swap(v);
}

template <typename T, typename Allocator>
inline void shrink(std::deque<T, Allocator>& v)
{
    std::deque<T, Allocator>(v.begin(), v.end()).swap(v);
}

} // namespace stx

#endif // STX_SHRINK_HPP
