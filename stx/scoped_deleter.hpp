#ifndef STX_SCOPED_DELETER_HPP
#define STX_SCOPED_DELETER_HPP

#include <stx/algorithm/begin.hpp>
#include <stx/algorithm/end.hpp>
#include <stx/default_delete.hpp>
#include <stx/type_traits/remove_pointer.hpp>
#include <stx/type_traits/container_value_type.hpp>
#include <stx/type_traits/container_iterator_type.hpp>

namespace stx {

template <
    class Container,
    typename Deleter = default_delete<typename remove_pointer<typename container_value_type<Container>::type>::type > >
class scoped_deleter: protected Deleter
{
public:
    
    typedef scoped_deleter<Container> this_type;
    typedef Container container_type;
    typedef Deleter deleter_type;
    
    scoped_deleter(const container_type& c): c_(c) {}
    
    ~scoped_deleter()
    {
        typename container_const_iterator_type<container_type>::type i = begin(c_), last = end(c_);
        for (; i != last; ++i) {
            deleter_type::operator()(*i);
        }
    }
    
private:
    
    const container_type& c_;
};

} // namespace stx

#endif // STX_SCOPED_DELETER_HPP
