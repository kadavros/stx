#ifndef STX_SCOPED_PTR_VECTOR_HPP
#define STX_SCOPED_PTR_VECTOR_HPP

#include <vector>

namespace stx {

template <class T, class A = std::allocator<T*> >
class scoped_ptr_vector: public std::vector<T*, A>
{
public:
    
    typedef scoped_ptr_vector<T, A>                     this_type;
    typedef typename std::vector<T*, A>                 base_type;
    
    typedef typename base_type::value_type              value_type;
    typedef typename base_type::pointer                 pointer;
    typedef typename base_type::const_pointer           const_pointer;
    typedef typename base_type::reference               reference;
    typedef typename base_type::const_reference         const_reference;
    typedef typename base_type::iterator                iterator;
    typedef typename base_type::const_iterator          const_iterator;
    typedef typename base_type::const_reverse_iterator  const_reverse_iterator;
    typedef typename base_type::reverse_iterator        reverse_iterator;
    typedef typename base_type::size_type               size_type;
    typedef typename base_type::difference_type         difference_type;
    typedef A                                           allocator_type;
    
    explicit scoped_ptr_vector(): base_type() {}
    
    explicit scoped_ptr_vector(const allocator_type& a): base_type(a) {}
    
    explicit scoped_ptr_vector(
        size_type n,
        const value_type& value = value_type(),
        const allocator_type& a = allocator_type()): base_type(n, value, a) {}
    
    template <class InputIterator>
    scoped_ptr_vector(InputIterator first, InputIterator last): base_type(first, last) {}
    
    ~scoped_ptr_vector()
    {
        for (size_type i = 0, size = this->size(); i < size; ++i) {
            delete this->operator [](i);
        }
    }
    
private:
    
    scoped_ptr_vector(const scoped_ptr_vector& v);
    scoped_ptr_vector& operator=(const scoped_ptr_vector& x);
};

} // namespace stx

#endif // STX_SCOPED_PTR_VECTOR_HPP
