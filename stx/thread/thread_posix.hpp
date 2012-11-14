#ifndef STX_THREAD_POSIX_HPP
#define STX_THREAD_POSIX_HPP

#include <pthread.h>
#include <stdexcept>

namespace stx {

namespace posix {

template<class CallableType>
inline void* thread_routine(void* arg)
{
    (*((CallableType*) arg))();
    return NULL;
}

//  Create thread object for main thread:
//      thread t(this_thread::handle());

class thread
{
public:
    
    typedef thread this_type;
    
    typedef pthread_t handle_type;
    
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
    }
    
    thread(const pthread_t handle): handle_(handle)
    {
    }
    
    thread(const thread& t)
    {
        handle_ = t.handle();
    }
    
    ~thread()
    {
    }
    
    void create(void *(*start_routine)(void*), void* arg)
    {
        int ret = pthread_create(&handle_, NULL, start_routine, arg);
        if (ret) {
            //STX_THROW_SYSTEM_ERROR_VAL(ret, "pthread_create");
            // todo
            throw std::runtime_error("pthread_create");
        }
    }
    
    template<class CallableType>
    void create(CallableType callable)
    {
        create(thread_routine<CallableType>, (void*) &callable);
    }
    
    void join()
    {
        void* val;
        join(val);
    }
    
    void join(void*& val)
    {
        int ret = pthread_join(handle_, &val);
        if (ret) {
            //STX_THROW_SYSTEM_ERROR_VAL(ret, "pthread_join");
            // todo
            throw std::runtime_error("pthread_join");
        }
    }
    
    bool joinable() const
    {
        return !equal(pthread_self());
    }
    
    bool equal(const thread& t) const
    {
        return pthread_equal(handle_, t.handle());
    }
    
    bool equal(const handle_type& h) const
    {
        return pthread_equal(handle_, h);
    }
    
    static unsigned hardware_concurrency()
    {
        return 0;
    }
    
    void detach()
    {
        int ret = pthread_detach(handle_);
        if (ret) {
            //STX_THROW_SYSTEM_ERROR_VAL(ret, "pthread_detach");
            // todo
            throw std::runtime_error("pthread_detach");
        }
    }
    
    void swap(thread& t)
    {
        handle_type h = handle_;
        handle_ = t.handle_;
        t.handle_ = h;
    }
    
private:
    
    handle_type handle_;
};

} // namespace posix

} // namespace stx

#endif // STX_THREAD_POSIX_HPP
