#ifndef STX_ALGORITHM_DESTROY_HPP
#define STX_ALGORITHM_DESTROY_HPP

namespace stx {

template <class T>
inline void destroy(T* p)
{
	p->~T();
}

template <class ForwardIterator>
inline void destroy(ForwardIterator first, ForwardIterator last)
{
	for (; first != last; ++first) {
		destroy(&*first);
	}
}

} // namespace stx

#endif // STX_ALGORITHM_DESTROY_HPP
