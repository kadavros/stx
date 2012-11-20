#ifndef STX_THREAD_UNIQUE_LOCK_HPP
#define STX_THREAD_UNIQUE_LOCK_HPP

namespace stx {

template <class Mutex>
class unique_lock
{
public:
    
    unique_lock()
    {
        pm = 0;
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

} // namespace stx

#endif // STX_THREAD_UNIQUE_LOCK_HPP
