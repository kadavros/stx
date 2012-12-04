#ifndef STX_TYPE_TRAITS_INTEGRAL_CONSTANT_HPP
#define STX_TYPE_TRAITS_INTEGRAL_CONSTANT_HPP

namespace stx {

template <class T, T v>
struct integral_constant
{
    enum { value = v };
    typedef T value_type;
    typedef integral_constant type;
    
    operator value_type() const
    {
        return value;
    }
    
    static value_type get_value()
    {
        return value;
    }
};

} // namespace stx

#endif // STX_TYPE_TRAITS_INTEGRAL_CONSTANT_HPP
