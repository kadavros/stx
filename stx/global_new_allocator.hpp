#ifndef STX_GLOBAL_NEW_ALLOCATOR_HPP
#define STX_GLOBAL_NEW_ALLOCATOR_HPP

#include <new>
#include <assert.h>
#include <stddef.h>
#include <stdlib.h>

namespace stx {

template <typename T>
class global_new_allocator
{
public:
    
    typedef T value_type;
    typedef T* pointer;
    typedef const T* const_pointer;
    typedef T& reference;
    typedef const T& const_reference;
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;
    
    template <typename T1>
    struct rebind
    {
        typedef global_new_allocator<T1> other;
    };
    
    global_new_allocator() throw()
    {
    }
    
    global_new_allocator(const global_new_allocator&) throw()
    {
    }
    
    template <typename T1>
    global_new_allocator(const global_new_allocator<T1>&) throw()
    {
    }
    
    ~global_new_allocator() throw()
    {
    }
    
    pointer address(reference x) const
    {
        return &x;
    }
    
    const_pointer address(const_reference x) const
    {
        return &x;
    }
    
    pointer allocate(size_type n, const void* = 0)
    {
        if (n > this->max_size()) {
            throw std::bad_alloc();
        }
        pointer ret = static_cast<T*>(::operator new(n * sizeof(T)));
        if (!ret) {
            throw std::bad_alloc();
        }
        return ret;
    }
    
    void deallocate(pointer p, size_type)
    {
        assert(p);
        ::operator delete(p);
    }
    
    size_type max_size() const throw() 
    {
        return size_t(-1) / sizeof(T);
    }
    
    void construct(pointer p, const T& val) 
    {
        ::new ((void*) p) value_type(val);
    }
    
    void destroy(pointer p)
    {
        p->~T();
    }
};

template <typename T>
inline bool operator==(const global_new_allocator<T>&, const global_new_allocator<T>&)
{
    return true;
}

template <typename T>
inline bool operator!=(const global_new_allocator<T>&, const global_new_allocator<T>&)
{
    return false;
}

} // namespace stx

#endif // STX_GLOBAL_NEW_ALLOCATOR_HPP
