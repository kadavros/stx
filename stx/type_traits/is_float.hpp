#ifndef STX_TYPE_TRAITS_IS_FLOAT_HPP
#define STX_TYPE_TRAITS_IS_FLOAT_HPP

#include <stx/type_traits/bool_types.hpp>

namespace stx {

template <class T> struct is_float: false_type {};

template <> struct is_float<float>: true_type {};
template <> struct is_float<const float>: true_type {};
template <> struct is_float<volatile float>: true_type {};
template <> struct is_float<const volatile float>: true_type {};

template <> struct is_float<double>: true_type {};
template <> struct is_float<const double>: true_type {};
template <> struct is_float<volatile double>: true_type {};
template <> struct is_float<const volatile double>: true_type {};

template <> struct is_float<long double>: true_type {};
template <> struct is_float<const long double>: true_type {};
template <> struct is_float<volatile long double>: true_type {};
template <> struct is_float<const volatile long double>: true_type {};

} // namespace stx

#endif // STX_TYPE_TRAITS_IS_FLOAT_HPP
