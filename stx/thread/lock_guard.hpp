#ifndef STX_THREAD_LOCK_GUARD_HPP
#define STX_THREAD_LOCK_GUARD_HPP

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

} // namespace stx

#endif // STX_THREAD_LOCK_GUARD_HPP
