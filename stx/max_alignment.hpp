#ifndef STX_MAX_ALIGNMENT_HPP
#define STX_MAX_ALIGNMENT_HPP

//  Duplication of STX_HAS_LONG_LONG: #ifdef LLONG_MAX
#include <limits.h>
//  Duplication of STX_HAS_LONG_DOUBLE: #ifdef LDBL_MANT_DIG
#include <float.h>

namespace stx {

class max_alignment_helper_class {};

//  This is not standard, but should work with all compilers.
union max_alignment
{
    char        char_;
    short       short_;
    int         int_;
    long        long_;
#   ifdef LLONG_MAX
    long long   long_long_;
#   endif
    float       float_;
    double      double_;
#   ifdef LDBL_MANT_DIG
    long double long_double_;
#   endif
    void        *void_ptr_;
    void        (*void_func_ptr_)();
#   ifdef __cplusplus
    void        *max_alignment_helper_class::*void_member_ptr_;
    void        (max_alignment_helper_class::*void_member_func_ptr_)();
#   endif
};

} // namespace stx

#endif // STX_MAX_ALIGNMENT_HPP
