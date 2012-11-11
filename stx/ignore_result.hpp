#ifndef STX_IGNORE_RESULT_HPP
#define STX_IGNORE_RESULT_HPP

namespace stx {

//
//  [thanks to chromium code base]
//
// Used to explicitly mark the return value of a function as unused. If you are
// really sure you don't want to do anything with the return value of a function
// that has been marked WARN_UNUSED_RESULT, wrap it with this. Example:
//
//   scoped_ptr<MyType> my_var = ...;
//   if (TakeOwnership(my_var.get()) == SUCCESS)
//     ignore_result(my_var.release());
//
template<typename T>
inline void ignore_result(const T&)
{
}

} // namespace stx

#endif // STX_IGNORE_RESULT_HPP
