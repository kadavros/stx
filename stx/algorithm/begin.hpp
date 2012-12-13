#ifndef STX_ALGORITHM_BEGIN_HPP
#define STX_ALGORITHM_BEGIN_HPP

namespace stx {

template <class Container>
inline typename Container::iterator
begin(Container& c)
{
    return c.begin();
}

template <class Container>
inline typename Container::const_iterator
begin(const Container& c)
{
    return c.begin();
}

} // namespace stx

#endif // STX_ALGORITHM_BEGIN_HPP
