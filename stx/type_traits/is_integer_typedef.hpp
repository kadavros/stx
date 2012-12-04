#ifndef STX_TYPE_TRAITS_IS_INTEGER_TYPEDEF_HPP
#define STX_TYPE_TRAITS_IS_INTEGER_TYPEDEF_HPP

#include <stx/int_types/long_long.hpp>
#include <stx/type_traits/bool_types.hpp>

namespace stx {

template <class T> struct is_integer_typedef:                 false_type {};
template <>        struct is_integer_typedef<char>:           true_type {};
template <>        struct is_integer_typedef<signed char>:    true_type {};
template <>        struct is_integer_typedef<unsigned char>:  true_type {};
template <>        struct is_integer_typedef<short>:          true_type {};
template <>        struct is_integer_typedef<unsigned short>: true_type {};
template <>        struct is_integer_typedef<int>:            true_type {};
template <>        struct is_integer_typedef<unsigned int>:   true_type {};
template <>        struct is_integer_typedef<long>:           true_type {};
template <>        struct is_integer_typedef<unsigned long>:  true_type {};
#if STX_HAS_LONG_LONG
template <>        struct is_integer_typedef<llong>:          true_type {};
template <>        struct is_integer_typedef<ullong>:         true_type {};
#endif

} // namespace stx

#endif // STX_TYPE_TRAITS_IS_INTEGER_TYPEDEF_HPP
