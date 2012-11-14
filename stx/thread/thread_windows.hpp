#ifndef STX_THREAD_WINDOWS_HPP
#define STX_THREAD_WINDOWS_HPP

#include <windows.h>
#include <stdexcept>

namespace stx {

namespace windows {

template<class CallableType>
inline DWORD WINAPI thread_routine(LPVOID arg)
{
    (*((CallableType*) arg))();
    return 0;
}

class thread
{
public:
    
    typedef thread this_type;
    
    typedef HANDLE handle_type;
    
    handle_type handle()
    {
        return handle_;
    }
    
    const handle_type handle() const
    {
        return handle_;
    }
    
    thread()
    {
        handle_ = NULL;
    }
    
    void create(LPTHREAD_START_ROUTINE lpStartAddress, LPVOID lpParameter)
    {
        LPSECURITY_ATTRIBUTES lpThreadAttributes = NULL;
        SIZE_T dwStackSize = 0; // Leads to default value.
        DWORD dwCreationFlags = CREATE_SUSPENDED;
        DWORD dwThreadId;
        HANDLE handle_ = CreateThread(lpThreadAttributes, dwStackSize, lpStartAddress,
            lpParameter, dwCreationFlags, &dwThreadId);
        if (!handle_) {
            //STX_THROW_SYSTEM_ERROR_VAL(GetLastError(), "CreateThread");
            // todo
            throw std::runtime_error("CreateThread");
        }
    }
    
    template<class CallableType>
    void create(CallableType callable)
    {
        create(thread_routine<CallableType>, (void*) &callable);
    }
    
    // todo: implement correctly
    bool joinable() const
    {
        return (handle_ != NULL);
    }
    
    static unsigned hardware_concurrency()
    {
        return 0;
    }
    
    void join()
    {
        WaitForSingleObject(handle_, INFINITE);
    }
    
    void detach()
    {
    }
    
    void swap(thread& t)
    {
        handle_type h = handle_;
        handle_ = t.handle_;
        t.handle_ = h;
    }
    
private:
    
    HANDLE handle_;
};

} // namespace windows

} // namespace stx

#endif // STX_THREAD_WINDOWS_HPP
