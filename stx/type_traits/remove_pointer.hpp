#ifndef STX_TYPE_TRAITS_REMOVE_POINTER_HPP
#define STX_TYPE_TRAITS_REMOVE_POINTER_HPP

namespace stx {

template <class T> struct remove_pointer;
template <class T> struct remove_pointer<T*> { typedef T type; };
template <class T> struct remove_pointer<const T*> { typedef T type; };
template <class T> struct remove_pointer<volatile T*> { typedef T type; };
template <class T> struct remove_pointer<const volatile T*> { typedef T type; };

} // namespace stx

#endif // STX_TYPE_TRAITS_REMOVE_POINTER_HPP
