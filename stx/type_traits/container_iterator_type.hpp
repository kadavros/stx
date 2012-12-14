#ifndef STX_TYPE_TRAITS_CONTAINER_ITERATOR_TYPE_HPP
#define STX_TYPE_TRAITS_CONTAINER_ITERATOR_TYPE_HPP

#include <stddef.h>

namespace stx {

template <class T>
struct container_iterator_type { typedef typename T::iterator type; };

template <class T, size_t Size>
struct container_iterator_type<T [Size]> { typedef T* type; };

template <class T>
struct container_const_iterator_type { typedef typename T::const_iterator type; };

template <class T, size_t Size>
struct container_const_iterator_type<T [Size]> { typedef const T* type; };

} // namespace stx

#endif // STX_TYPE_TRAITS_CONTAINER_ITERATOR_TYPE_HPP
