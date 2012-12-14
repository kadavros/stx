#ifndef STX_TYPE_TRAITS_CONTAINER_VALUE_TYPE_HPP
#define STX_TYPE_TRAITS_CONTAINER_VALUE_TYPE_HPP

#include <stddef.h>

namespace stx {

template <class T>
struct container_value_type { typedef typename T::value_type type; };

template <class T, size_t Size>
struct container_value_type<T [Size]> { typedef T type; };

} // namespace stx

#endif // STX_TYPE_TRAITS_CONTAINER_VALUE_TYPE_HPP
