#ifndef STX_STANDARD_NEW_DELETE_HPP
#define STX_STANDARD_NEW_DELETE_HPP

#include <stddef.h>
#include <new>

namespace stx {

class standard_new_delete
{
public:
    
    // normal new/delete
    
    static void* operator new(size_t size) //throw(std::bad_alloc)
    {
        return ::operator new(size);
    }
    
    static void operator delete(void* p) throw()
    {
        ::operator delete(p);
    }
    
    // placement new/delete
    
    static void* operator new(size_t size, void* ptr) throw()
    {
        return ::operator new(size, ptr);
    }
    
    static void operator delete(void* p, void* p2) throw()
    {
        return ::operator delete(p, p2);
    }
    
    // nothrow new/delete
    
    static void* operator new(size_t size, const std::nothrow_t& nt) throw()
    {
        return ::operator new(size, nt);
    }
    
    static void operator delete(void* p, const std::nothrow_t&) throw()
    {
        ::operator delete(p);
    }
};

} // namespace stx

#endif // STX_STANDARD_NEW_DELETE_HPP
