#ifndef STX_NONCOPYABLE_HPP
#define STX_NONCOPYABLE_HPP

/*
    noncopyable
    
    Private copy constructor and copy assignment ensure classes derived from
    class noncopyable cannot be copied.
    
    Usage:
        class MyClass: public noncopyable
        {
            // ...
        };
*/

namespace stx {

/*
    Additional noncopyable_ namespace is a protection from unintended ADL.
    If noncopyable were defined in namespace stx, then function calls
    involving classes deriving from noncopyable would get namespace stx
    added to the ADL scopes in which the function is looked up.
    Usually this isn't wanted, as noncopyable is an implementation
    detail, not an interface. See docs/adl_problem.txt for more details.
*/

namespace noncopyable_ { 

class noncopyable
{
protected:
    noncopyable() {}
    ~noncopyable() { }
private:
    noncopyable(const noncopyable&);
    const noncopyable& operator=(const noncopyable&);
};

} // namespace noncopyable_

typedef noncopyable_::noncopyable noncopyable;

} // namespace stx

#endif // STX_NONCOPYABLE_HPP
