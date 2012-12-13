#ifndef STX_ALGORITHM_END_HPP
#define STX_ALGORITHM_END_HPP

namespace stx {

template <class Container>
inline typename Container::iterator
end(Container& c)
{
    return c.end();
}

template <class Container>
inline typename Container::const_iterator
end(const Container& c)
{
    return c.end();
}

} // namespace stx

#endif // STX_ALGORITHM_END_HPP
