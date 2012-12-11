#ifndef STX_UNINITIALIZED_HPP
#define STX_UNINITIALIZED_HPP

/*
    uninitialized_t tag for delayed object initialization.
    
    Example:
    
    class MyClass
    {
    public:
        MyClass(int); // calls init(int);
        MyClass(const MyClass&);
        MyClass(uninitialized_t);
        init(int);
    };
    
    std::vector<MyClass> v(1000, MyClass(uninitialized_t));
    for (size_t i = 0; i < v.size(); ++i) {
        v.init(i);
    }
*/

namespace stx {

struct uninitialized_t {};

} // namespace stx

#endif // STX_UNINITIALIZED_HPP
