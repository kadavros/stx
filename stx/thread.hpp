#ifndef STX_THREAD_HPP
#define STX_THREAD_HPP

#include <stx/config.hpp>
#include <stx/bind.hpp>

#if defined(STX_PLATFORM_POSIX)
#include <stx/thread/posix/thread.hpp>
#include <stx/thread/posix/mutex.hpp>
namespace stx {
    typedef stx::posix::thread thread_impl;
}

#elif defined(STX_PLATFORM_WINDOWS)
#include <stx/thread/windows/thread.hpp>
#include <stx/thread/windows/mutex.hpp>
namespace stx {
    typedef stx::windows::thread thread_impl;
}
#endif

namespace stx {

template <class Mutex>
class lock_guard
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
    
    lock_guard(const lock_guard<Mutex>&);
    const lock_guard<Mutex>& operator=(const lock_guard<Mutex>&);
    
    Mutex* pm;
};

template <class Mutex>
class unique_lock
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
    
    unique_lock(const unique_lock<Mutex>&);
    const unique_lock<Mutex>& operator=(const unique_lock<Mutex>&);
    
    Mutex* pm;
    bool locked_;
};

template <class Func>
inline void* thread_routine(void* arg)
{
    (*((Func*) arg))();
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
    
    template <class Func>
    thread(Func func)
    {
        t.create(bind(func));
    }
    
    template <class Func, class A1>
    thread(Func func, A1 a1)
    {
        t.create(bind(func, a1));
    }
    
    template <class Func, class A1, class A2>
    thread(Func func, A1 a1, A2 a2)
    {
        t.create(bind(func, a1, a2));
    }
    
    template <class Func, class A1, class A2, class A3>
    thread(Func func, A1 a1, A2 a2, A3 a3)
    {
        t.create(bind(func, a1, a2, a3));
    }
    
    template <class Func, class A1, class A2, class A3, class A4>
    thread(Func func, A1 a1, A2 a2, A3 a3, A4 a4)
    {
        t.create(bind(func, a1, a2, a3, a4));
    }
    
    template <class Func, class A1, class A2, class A3, class A4, class A5>
    thread(Func func, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5)
    {
        t.create(bind(func, a1, a2, a3, a4, a5));
    }
    
    template <class Func, class A1, class A2, class A3, class A4, class A5, class A6>
    thread(Func func, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6)
    {
        t.create(bind(func, a1, a2, a3, a4, a5, a6));
    }
    
    template <class Func, class A1, class A2, class A3, class A4, class A5, class A6, class A7>
    thread(Func func, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7)
    {
        t.create(bind(func, a1, a2, a3, a4, a5, a6, a7));
    }
    
    template <class Func, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8>
    thread(Func func, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8)
    {
        t.create(bind(func, a1, a2, a3, a4, a5, a6, a7, a8));
    }
    
    template <class Func, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9>
    thread(Func func, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9)
    {
        t.create(bind(func, a1, a2, a3, a4, a5, a6, a7, a8, a9));
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
