#ifndef STX_ALGORITHM_CONSTRUCT_HPP
#define STX_ALGORITHM_CONSTRUCT_HPP

namespace stx {

template <class T1, class T2>
inline void construct(T1* p, const T2& value)
{
	new (p) T1(value);
}

} // namespace stx

#endif // STX_ALGORITHM_CONSTRUCT_HPP
