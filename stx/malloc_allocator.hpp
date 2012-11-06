#ifndef STX_MALLOC_ALLOCATOR_HPP
#define STX_MALLOC_ALLOCATOR_HPP

#include <cassert>
#include <cstdlib>
#include <new>

namespace stx {

template<typename T>
class malloc_allocator
{
public:
    
    typedef T value_type;
    typedef T* pointer;
    typedef const T* const_pointer;
    typedef T& reference;
    typedef const T& const_reference;
    typedef std::size_t size_type;
    typedef std::ptrdiff_t difference_type;
    
    template<typename T1>
    struct rebind
    {
        typedef malloc_allocator<T1> other;
    };
    
    malloc_allocator() throw()
    {
    }
    
    malloc_allocator(const malloc_allocator&) throw()
    {
    }
    
    template<typename T1>
    malloc_allocator(const malloc_allocator<T1>&) throw()
    {
    }
    
    ~malloc_allocator() throw()
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
        pointer ret = static_cast<T*> (std::malloc(n * sizeof(T)));
        if (!ret) {
            throw std::bad_alloc();
        }
        return ret;
    }
    
    void deallocate(pointer p, size_type)
    {
        assert(p);
        std::free(static_cast<void*> (p));
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

template<typename T>
inline bool operator==(const malloc_allocator<T>&, const malloc_allocator<T>&)
{
    return true;
}

template<typename T>
inline bool operator!=(const malloc_allocator<T>&, const malloc_allocator<T>&)
{
    return false;
}

} // namespace stx

#endif // STX_MALLOC_ALLOCATOR_HPP
