#ifndef STX_INT_TYPES_SSIZE_T_HPP
#define STX_INT_TYPES_SSIZE_T_HPP

#include <stddef.h>
#include <stx/int_types/sign_type_conversions.hpp>

namespace stx {

typedef make_signed_t<size_t>::type ssize_t;

} // namespace stx

#endif // STX_INT_TYPES_SSIZE_T_HPP
