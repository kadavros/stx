#ifndef STX_TYPE_TRAITS_BOOL_TYPES_HPP
#define STX_TYPE_TRAITS_BOOL_TYPES_HPP

#include <stx/type_traits/integral_constant.hpp>

namespace stx {

typedef integral_constant<int, 1> true_type;
typedef integral_constant<int, 0> false_type;

} // namespace stx

#endif // STX_TYPE_TRAITS_BOOL_TYPES_HPP
