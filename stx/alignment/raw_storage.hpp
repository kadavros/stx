#ifndef STX_ALIGNMENT_RAW_STORAGE_HPP
#define STX_ALIGNMENT_RAW_STORAGE_HPP

#include <stx/alignment/aligned_storage.hpp>

namespace stx {

template <typename T>
class raw_storage
{
public:
    
    typedef typename aligned_storage<sizeof(T), alignment_of<T>::value>::type aligned_storage_type;
    typedef raw_storage<T> this_type;
    typedef T value_type;
    typedef T* pointer;
    typedef const T* const_pointer;
    typedef T& reference;
    typedef const T& const_reference;
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;
    
    raw_storage()
    {
    }
    
    raw_storage(const T& x)
    {
        get() = x;
    }
    
    raw_storage(const raw_storage<T>& x)
    {
        get() = x.get();
    }
    
    pointer address()
    {
        return reinterpret_cast<pointer>(&raw_data_);
    }
    
    const_pointer address() const
    {
        return reinterpret_cast<pointer>(&const_cast<this_type*>(this)->raw_data_);
    }
    
    void construct(const T& x = T())
    {
        ::new(address()) T(x);
    }
    
    void destroy()
    {
        get().~T();
    }
    
    reference get()
    {
        return *(reinterpret_cast<pointer>(address()));
    }
    
    const_reference get() const
    {
        return *(reinterpret_cast<const_pointer>(address()));
    }
    
private:
    
    aligned_storage_type raw_data_;
};

} // namespace stx

#endif // STX_ALIGNMENT_RAW_STORAGE_HPP
