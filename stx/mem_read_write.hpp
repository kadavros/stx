#ifndef STX_MEM_READ_WRITE_HPP
#define STX_MEM_READ_WRITE_HPP

/*
    Unaligned memory read/write.
    Example:
        void* p = malloc(2*sizeof(int));
        int x = 123, y = 0;
        char* p2 = (char*) p + 1;
        // *(int*) p2 = x; // Undefined behavior - program may crash on some
        // y = *(int*) p2; // platforms due to unaligned memory access.
        mem_write(p2, x); // Ok
        mem_read(p2, y);  // Ok
        free(p);
*/

#include <string.h>

namespace stx {

template <class T>
inline void mem_read(const void* p, T& t)
{
    memcpy(&t, p, sizeof(T));
}

template <class T>
inline void mem_write(void* p, const T& t)
{
    memcpy(p, &t, sizeof(T));
}

} // namespace stx

#endif // STX_MEM_READ_WRITE_HPP
