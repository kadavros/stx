#ifndef STX_THREAD_WINDOWS_MUTEX_HPP
#define STX_THREAD_WINDOWS_MUTEX_HPP

#include <stx/thread/windows/common.hpp>

namespace stx {

class mutex
{
public:
    
    mutex()
    {
        InitializeCriticalSection(&critical_section_);
    }
    
    ~mutex()
    {
        DeleteCriticalSection(&critical_section_);
    }
    
    void lock()
    {
        EnterCriticalSection(&critical_section_);
    }
    
    bool try_lock()
    {
        return TryEnterCriticalSection(&critical_section_);
    }
    
    void unlock()
    {
        EnterCriticalSection(&critical_section_);
    }
    
private:
    
    mutex(const mutex&);
    const mutex& operator=(const mutex&);
    
    CRITICAL_SECTION critical_section_;
};

/*
    Remark from MSDN:
        When a thread owns a critical section, it can make additional calls to EnterCriticalSection
        or TryEnterCriticalSection without blocking its execution. This prevents a thread from
        deadlocking itself while waiting for a critical section that it already owns. To release
        its ownership, the thread must call LeaveCriticalSection one time for each time that it
        entered the critical section. There is no guarantee about the order in which waiting threads
        will acquire ownership of the critical section.
    
    So we can safely implement recursive_mutex as mutex on win32 platform.
*/

class recursive_mutex: public mutex
{
private:
    
    recursive_mutex(const recursive_mutex&);
    const recursive_mutex& operator=(const recursive_mutex&);
};

} // namespace stx

#endif // STX_THREAD_WINDOWS_MUTEX_HPP
