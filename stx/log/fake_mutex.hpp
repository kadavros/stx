#ifndef STX_LOG_FAKE_MUTEX_HPP
#define STX_LOG_FAKE_MUTEX_HPP

namespace stx {

struct fake_mutex
{
    void lock() {}
    void unlock() {}
};

} // namespace stx

#endif // STX_LOG_FAKE_MUTEX_HPP
