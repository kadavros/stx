#ifndef STX_ALIGNMENT_MAX_ALIGNMENT_HPP
#define STX_ALIGNMENT_MAX_ALIGNMENT_HPP

#include <stx/int_types/long_long.hpp>

namespace stx {

class max_alignment_helper_class {};

template <typename T>
struct max_alignment_struct_with_type
{
    T data;
};

//  This is not standard, but should work with all compilers.
union max_alignment_t
{
    char        char_;
    short       short_;
    int         int_;
    long        long_;
#   if STX_HAS_LONG_LONG
    long long   long_long_;
#   endif
    float       float_;
    double      double_;
    long double long_double_;
    void        *void_ptr_;
    void        (*func_ptr_)();
    int         max_alignment_helper_class::*member_ptr_;
    int         (max_alignment_helper_class::*member_func_ptr_)();
    
    max_alignment_struct_with_type<char>        struct_with_char_;
    max_alignment_struct_with_type<short>       struct_with_short_;
    max_alignment_struct_with_type<int>         struct_with_int_;
    max_alignment_struct_with_type<long>        struct_with_long_;
#   if STX_HAS_LONG_LONG
    max_alignment_struct_with_type<long long>   struct_with_long_long_;
#   endif
    max_alignment_struct_with_type<float>       struct_with_float_;
    max_alignment_struct_with_type<double>      struct_with_double_;
    max_alignment_struct_with_type<long double> struct_with_long_double_;
    max_alignment_struct_with_type<void*>       struct_with_void_ptr_;
    max_alignment_struct_with_type<void (*)()>  struct_with_func_ptr_;
    max_alignment_struct_with_type<int max_alignment_helper_class::*> struct_with_member_ptr_;
    max_alignment_struct_with_type<int (max_alignment_helper_class::*)()> struct_with_member_func_ptr_;
};

#define STX_MAX_ALIGNMENT sizeof(max_alignment_t)

} // namespace stx

#endif // STX_ALIGNMENT_MAX_ALIGNMENT_HPP
