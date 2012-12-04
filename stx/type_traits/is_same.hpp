#ifndef STX_TYPE_TRAITS_IS_SAME_HPP
#define STX_TYPE_TRAITS_IS_SAME_HPP

#include <stx/type_traits/bool_types.hpp>

namespace stx {

template <class T, class U> struct is_same:       false_type {};
template <class T>          struct is_same<T, T>: true_type {};

} // namespace stx

#endif // STX_TYPE_TRAITS_IS_SAME_HPP
