#ifndef STX_THREAD_WINDOWS_THREAD_HPP
#define STX_THREAD_WINDOWS_THREAD_HPP

#include <stx/thread/windows/common.hpp>
#include <stdexcept>

namespace stx {

namespace windows {

template<class Func>
inline DWORD WINAPI thread_routine(LPVOID arg)
{
    (*((Func*) arg))();
    delete (Func*) arg;
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
    
    template<class Func>
    void create(LPTHREAD_START_ROUTINE lpStartAddress, LPVOID lpParameter)
    {
        LPSECURITY_ATTRIBUTES lpThreadAttributes = NULL;
        SIZE_T dwStackSize = 0; // Leads to default value.
        DWORD dwCreationFlags = 0; // Zero value means that thread runs immediately after creation.
        DWORD dwThreadId;
        handle_ = CreateThread(
            lpThreadAttributes,
            dwStackSize,
            lpStartAddress,
            lpParameter,
            dwCreationFlags,
            &dwThreadId);
        if (!handle_) {
            //STX_THROW_SYSTEM_ERROR_VAL(GetLastError(), "CreateThread");
            // todo
            delete (Func*) lpParameter;
            throw std::runtime_error("CreateThread");
        }
    }
    
    template<class Func>
    void create(Func func)
    {
        Func* pf = new Func(func);
        create<Func>((LPTHREAD_START_ROUTINE) thread_routine<Func>, (LPVOID) pf);
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

#endif // STX_THREAD_WINDOWS_THREAD_HPP
