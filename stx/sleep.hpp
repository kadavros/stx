#ifndef STX_SLEEP_HPP
#define STX_SLEEP_HPP

#include <stx/config.hpp>

#if defined(STX_PLATFORM_POSIX)
#include <limits.h>
#include <time.h>
#elif defined(STX_PLATFORM_WINDOWS)

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN_DEFINED_LOCALLY
#endif
#ifndef NOMINMAX
#define NOMINMAX
#define NOMINMAX_DEFINED_LOCALLY
#endif
#include <windows.h>
#ifdef NOMINMAX_DEFINED_LOCALLY
#undef NOMINMAX
#endif
#ifdef WIN32_LEAN_AND_MEAN_DEFINED_LOCALLY
#undef WIN32_LEAN_AND_MEAN
#endif

#endif

namespace stx {

#ifdef STX_PLATFORM_POSIX

//  TODO
//  seconds > UINT_MAX
//  m.b. wee need to check against std::numeric_limits<time_t>::max()

inline void sleep(double seconds)
{
    if (seconds < 0) {
        //STX_THROW(std::invalid_argument, "seconds < 0: " << seconds);
        seconds = 0;
    } else if (seconds > UINT_MAX) {
        //STX_THROW(std::invalid_argument, "seconds > UINT_MAX: " << seconds);
        seconds = UINT_MAX;
    }
    struct timespec t;
    t.tv_sec = static_cast<time_t> (seconds);
    t.tv_nsec = static_cast<long> (1000000000*(seconds - t.tv_sec));
    // From POSIX standard:
    // nanosleep() will fail and return EINVAL if nanosecond value less than
    // zero or greater than or equal to 1000 million.
    if (t.tv_nsec >= 1000000000) {
        t.tv_nsec = 999999999;
    }
    int ret = nanosleep(&t, NULL);
    if (ret != 0) {
        //STX_THROW_SYSTEM_ERROR("nanosleep() failed; t.tv_sec: " << t.tv_sec << "t.tv_nsec: " << t.tv_nsec);
    }
}

inline void sleep(time_t seconds, long nanoseconds)
{
    if (nanoseconds < 0) {
        //STX_THROW(std::invalid_argument, "nanoseconds < 0: " << nanoseconds);
    } else if (nanoseconds > 1000000000) {
        //STX_THROW(std::invalid_argument, "nanoseconds >= 1000000000: " << nanoseconds);
    }
    struct timespec t;
    t.tv_sec = seconds;
    t.tv_nsec = nanoseconds;
    int ret = nanosleep(&t, NULL);
    if (ret != 0) {
        //STX_THROW_SYSTEM_ERROR("nanosleep() failed; t.tv_sec: " << t.tv_sec << "t.tv_nsec: " << t.tv_nsec);
    }
}

#endif // STX_PLATFORM_POSIX

#ifdef STX_PLATFORM_WINDOWS

inline void sleep(double seconds)
{
    DWORD dwMilliseconds = seconds * 1000.0;
    Sleep(dwMilliseconds);
}

inline void sleep(time_t seconds, long nanoseconds)
{
    DWORD dwMilliseconds = seconds * 1000 + nanoseconds / 1000000;
    Sleep(dwMilliseconds);
}

#endif // STX_PLATFORM_WINDOWS

} // namespace stx

#endif // STX_SLEEP_HPP
