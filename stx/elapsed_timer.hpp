#ifndef STX_ELAPSED_TIMER_HPP
#define STX_ELAPSED_TIMER_HPP

#include <stx/config.hpp>

#ifdef STX_PLATFORM_POSIX

#include <time.h>

//  TODO
//  Check other possible timers:
//      CLOCK_PROCESS_CPUTIME_ID
//      CLOCK_THREAD_CPUTIME_ID
//      CLOCK_MONOTONIC_RAW
//      CLOCK_REALTIME_COARSE
//      CLOCK_MONOTONIC_COARSE
#if defined(CLOCK_MONOTONIC)
#   define STX_DEFAULT_POSIX_CLOCK CLOCK_MONOTONIC
#elif defined(CLOCK_REALTIME)
#   define STX_DEFAULT_POSIX_CLOCK CLOCK_REALTIME
#endif

namespace stx {

class elapsed_timer
{
public:
    
    elapsed_timer()
    {
        reset();
    }
    
    // Restart timer.
    void reset()
    {
        int ret = clock_gettime(STX_DEFAULT_POSIX_CLOCK, &t1);
        if (ret) {
            // handle error
        }
    }
    
    // Elapsed time in seconds.
    double elapsed() const
    {
        struct timespec t2;
        int ret = clock_gettime(STX_DEFAULT_POSIX_CLOCK, &t2);
        if (ret) {
            // handle error
        }
        return (double) (t2.tv_sec - t1.tv_sec) + 1e-9*(t2.tv_nsec - t1.tv_nsec);
    }
    
private:
    
    struct timespec t1;
};

} // namespace stx

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

namespace stx {

class elapsed_timer
{
public:
    
    elapsed_timer()
    {
        reset();
    }
    
    // Restart timer.
    void reset()
    {
        BOOL ret = QueryPerformanceCounter(&t1);
        if (!ret) {
            // handle error
        }
    }
    
    // Elapsed time in seconds.
    double elapsed() const
    {
        LARGE_INTEGER t2;
        BOOL ret = QueryPerformanceCounter(&t2);
        if (!ret) {
            // handle error
        }
        LARGE_INTEGER frequency;
        QueryPerformanceFrequency(&frequency);
        if (!ret) {
            // handle error
        }
        //return (double) (current_time.tv_sec - t.tv_sec) + 1e-9*(current_time.tv_nsec - t.tv_nsec);
        return (double) (t2.QuadPart - t1.QuadPart) / frequency.QuadPart;
    }
    
private:
    
    LARGE_INTEGER t1;
};

} // namespace stx

#else

#include <time.h>

namespace stx {

class elapsed_timer
{
public:
    elapsed_timer() { reset(); }
    void reset() { t1 = clock(); }
    double elapsed() const { return (double) (clock() - t1)/CLOCKS_PER_SEC; }
    
private:
    clock_t t1;
};

} // namespace stx

#endif

#endif // STX_ELAPSED_TIMER_HPP
