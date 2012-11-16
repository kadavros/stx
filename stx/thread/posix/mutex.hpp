#ifndef STX_THREAD_POSIX_MUTEX_HPP
#define STX_THREAD_POSIX_MUTEX_HPP

#include <stx/thread/posix/common.hpp>
#include <stddef.h>
#include <errno.h>

namespace stx {

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
        //  According to POSIX standard, the only error that
        //  pthread_mutex_unlock() may return is EPERM, indicating that
        //  the current thread does not own the mutex. We can safely
        //  ignore this error, because we always unlock mutex handle,
        //  that is in private section of this class (and  therefore
        //  nobody else has access to lock it, except us ourselves).
        (void) pthread_mutex_unlock(&handle_);
    }
    
private:
    
    pthread_mutex_t handle_;
};

typedef basic_mutex<PTHREAD_MUTEX_NORMAL> mutex;
typedef basic_mutex<PTHREAD_MUTEX_RECURSIVE> recursive_mutex;

} // namespace stx

#endif // STX_THREAD_POSIX_MUTEX_HPP
