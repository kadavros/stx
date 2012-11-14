#ifndef STX_THREAD_HPP
#define STX_THREAD_HPP

#include <stx/config.hpp>
#include <stx/noncopyable.hpp>

#if defined(STX_PLATFORM_POSIX)
#include <stx/thread/thread_posix.hpp>
#include <errno.h>

namespace stx {

typedef stx::posix::thread thread_impl;

template <int mutex_type>
class basic_mutex: noncopyable
{
public:
    
    basic_mutex()
    {
        int ret;
        pthread_mutexattr_t attr;
        
        ret = pthread_mutexattr_init(&attr);
        if (ret) {
            //STX_THROW_SYSTEM_ERROR_VAL(ret, "pthread_mutexattr_init");
            throw std::runtime_error("pthread_mutexattr_init");
        }
        
        ret = pthread_mutexattr_settype(&attr, mutex_type);
        if (ret) {
            //STX_THROW_SYSTEM_ERROR_VAL(ret, "pthread_mutexattr_settype");
            throw std::runtime_error("pthread_mutexattr_settype");
        }
        
        ret = pthread_mutex_init(&handle_, NULL);
        if (ret) {
            //STX_THROW_SYSTEM_ERROR_VAL(ret, "pthread_mutex_init");
            throw std::runtime_error("pthread_mutex_init");
        }
        
        ret = pthread_mutexattr_destroy(&attr);
        if (ret) {
            //STX_DESTRUCTOR_SYSTEM_ERROR_VAL(ret, "pthread_mutexattr_destroy");
            throw std::runtime_error("pthread_mutexattr_destroy");
        }
    }
    
    ~basic_mutex()
    {
        int ret = pthread_mutex_destroy(&handle_);
        if (ret) {
            //STX_DESTRUCTOR_SYSTEM_ERROR_VAL(ret, "pthread_mutex_destroy");
            // todo: how to handle this error in destructor?
            // We can't throw exception in destructor.
            //throw std::runtime_error("pthread_mutex_destroy");
        }
    }
    
    void lock()
    {
        int ret = pthread_mutex_lock(&handle_);
        if (ret) {
            //STX_THROW_SYSTEM_ERROR_VAL(ret, "pthread_mutex_lock");
            throw std::runtime_error("pthread_mutex_lock");
        }
    }
    
    bool try_lock()
    {
        int ret = pthread_mutex_trylock(&handle_);
        if (ret == EBUSY) {
            return false;
        } else  {
            //STX_THROW_SYSTEM_ERROR_VAL(ret, "pthread_mutex_trylock");
            throw std::runtime_error("pthread_mutex_trylock");
        }
        return true;
    }
    
    void unlock()
    {
        int ret = pthread_mutex_unlock(&handle_);
        if (ret) {
            //STX_THROW_SYSTEM_ERROR_VAL(ret, "pthread_mutex_unlock");
            throw std::runtime_error("pthread_mutex_unlock");
        }
    }
    
private:
    
    pthread_mutex_t handle_;
};

typedef basic_mutex<PTHREAD_MUTEX_NORMAL> mutex;
typedef basic_mutex<PTHREAD_MUTEX_RECURSIVE> recursive_mutex;

} // namespace stx

#elif defined(STX_PLATFORM_WINDOWS)
#include <stx/thread/thread_windows.hpp>

namespace stx {

typedef stx::windows::thread thread_impl;

class mutex: noncopyable
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
};

} // namespace stx

#endif

namespace stx {

template <class Mutex>
class lock_guard: noncopyable
{
public:
    
    explicit lock_guard(Mutex& m)
    {
        pm = &m;
        pm->lock();
    }
    
    ~lock_guard()
    {
        pm->unlock();
    }
    
private:
    
    Mutex* pm;
};

template <class Mutex>
class unique_lock: noncopyable
{
public:
    
    unique_lock()
    {
        pm = NULL;
        locked_ = false;
    }
    
    explicit unique_lock(Mutex& m)
    {
        pm = &m;
        lock();
    }
    
    ~unique_lock()
    {
        if (owns_lock()) {
            pm->unlock();
        }
    }
    
    bool try_lock()
    {
        locked_ = pm->try_lock();
        return locked_;
    }
    
    void lock()
    {
        pm->lock();
        locked_ = true;
    }
    
    void unlock()
    {
        pm->unlock();
        locked_ = false;
    }
    
    bool owns_lock() const
    {
        return locked_;
    }
    
private:
    
    Mutex* pm;
    bool locked_;
};

template <class CallableType>
inline void* thread_routine(void* arg)
{
    (*((CallableType*) arg))();
    return NULL;
}

class thread
{
public:
    
    typedef thread_impl::handle_type native_handle_type;
    
    thread()
    {
    }
    
    thread(const thread& t2)
    {
        t = t2.t;
    }
    
    template <class CallableType>
    thread(CallableType callable)
    {
        t.create(callable);
    }
    
    bool joinable() const
    {
        return t.joinable();
    }
    
    native_handle_type native_handle()
    {
        return t.handle();
    }
    
    static unsigned hardware_concurrency()
    {
        return thread_impl::hardware_concurrency();
    }
    
    void join()
    {
        t.join();
    }
    
    void detach()
    {
        t.detach();
    }
    
    void swap(thread& t2)
    {
        t.swap(t2.t);
    }
    
private:
    
    thread_impl t;
};

} // namespace stx

#endif // STX_THREAD_HPP
