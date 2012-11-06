#ifndef STX_IMPLICIT_CAST_HPP
#define STX_IMPLICIT_CAST_HPP

/*
    What is implicit_cast? when should I prefer implicit_cast rather than
    static_cast?
    
    You can down-cast with static_cast. Not so with implicit_cast.
    static_cast basically allows you to do any implicit conversion,
    and in addition the reverse of any implicit conversion (up to some limits:
    you can't downcast if there is a virtual base-class involved).
    But implicit_cast will only accept implicit conversions.
    No down-cast, no void*->T*, no U->T if T has only explicit
    constructors for U.
*/

namespace stx {

template<typename T>
struct identity
{
    typedef T type;
};

template<typename Dst> Dst implicit_cast(typename identity<Dst>::type x)
{
    return x;
}

/*
    Why we are not using more simple implementation without identity like this:
    
    template<typename Src, typename Dst>
    inline Dst implicit_cast(Src const &x)
    {
        return x;
    }
    
    With the identity you can cast to a reference: implicit_cast<T&>(t),
    while simple version will deduce U and will copy everything.
    If a conversion failure occurs, the compiler will point to the caller
    in the identity version. But in simplier version, the conversion happens
    within the function and the error message would probably not be as simple.
    identity makes it require an explicit parameter.
    Otherwise, it would accept things like "implicit_cast(x)".
*/

} // namespace stx

#endif // STX_IMPLICIT_CAST_HPP
