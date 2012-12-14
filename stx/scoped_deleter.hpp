#ifndef STX_SCOPED_DELETER_HPP
#define STX_SCOPED_DELETER_HPP

#include <stx/algorithm/begin.hpp>
#include <stx/algorithm/end.hpp>
#include <stx/default_delete.hpp>
#include <stx/type_traits/remove_pointer.hpp>

namespace stx {

template <class T>
struct container_value_type { typedef typename T::value_type type; };

template <class T, size_t Size>
struct container_value_type<T [Size]> { typedef T type; };

template <class T>
struct container_iterator_type { typedef typename T::iterator type; };

template <class T, size_t Size>
struct container_iterator_type<T [Size]> { typedef T* type; };

template <
    class Container,
    typename Deleter = default_delete<typename remove_pointer<typename container_value_type<Container>::type>::type > >
class scoped_deleter: protected Deleter
{
public:
    
    typedef scoped_deleter<Container> this_type;
    typedef Container container_type;
    typedef Deleter deleter_type;
    
    scoped_deleter(container_type& c): c_(c) {}
    
    ~scoped_deleter()
    {
        typename container_iterator_type<container_type>::type i = begin(c_), last = end(c_);
        for (; i != last; ++i) {
            deleter_type::operator()(*i);
        }
    }
    
private:
    
    container_type& c_;
};

} // namespace stx

#endif // STX_SCOPED_DELETER_HPP
