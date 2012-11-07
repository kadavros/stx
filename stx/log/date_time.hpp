#ifndef STX_LOG_DATE_TIME_HPP
#define STX_LOG_DATE_TIME_HPP

#if !defined(STX_PLATFORM_WINDOWS) || !defined(STX_PLATFORM_POSIX)
#if defined (_WIN32) || defined (_WIN64) || defined (__WIN32__) || defined (__TOS_WIN__) || defined (__WINDOWS__)
#   define STX_PLATFORM_WINDOWS
#endif
#if defined(unix) || defined(__unix__) || defined(__unix)
#   define STX_PLATFORM_UNIX
#endif
#if defined(STX_PLATFORM_UNIX)
#   include <unistd.h>
#   if defined(_POSIX_VERSION)
#       define STX_PLATFORM_POSIX
#   endif
#endif
#endif

#include <ctime>

#if defined(STX_PLATFORM_WINDOWS)
#include <windows.h>
/*
    According to MSDN:
        Both the 32-bit and 64-bit versions of gmtime, mktime, mkgmtime, and localtime all use a single tm structure
        per thread for the conversion. Each call to one of these routines destroys the result of the previous call.
*/
#define STX_THREAD_SAFE_LOCALTIME
#elif defined(STX_PLATFORM_POSIX)
#include <time.h>
//#define STX_HAS_LOCALTIME_R
#endif

/*
    clockid_t:
        CLOCK_REALTIME - POSIX
        CLOCK_MONOTONIC - POSIX 1003.1j D10
        CLOCK_PROCESS_CPUTIME_ID - POSIX 1003.1d D14
        CLOCK_THREAD_CPUTIME_ID - POSIX 1003.1d D14
*/

namespace stx {
namespace log {

class local_time
{
public:
    
    typedef local_time this_type;
    
    local_time()
    {
        update();
    }
    
    this_type& update()
    {
#if     defined(STX_PLATFORM_WINDOWS)
        SYSTEMTIME st;
        GetLocalTime(&st);
        BOOL ret = SystemTimeToFileTime(&st, &t);
        if (!ret) {
            return *this;
            //STX_THROW_SYSTEM_ERROR("SystemTimeToFileTime");
        }
#elif   defined(STX_PLATFORM_POSIX)
        int ret = clock_gettime(CLOCK_REALTIME, &t);
        if (ret == -1) {
            return *this;
            //STX_THROW_SYSTEM_ERROR("clock_gettime");
        }
#else
        time(&rawtime);
#endif
        return *this;
    }
    
    //  subsecond_precision range: from 0 to 9.
    template <class ostream_type>
    ostream_type& print(ostream_type& os, int subsecond_precision = 3) const
    {
        std::string date_separator("-"),
            datetime_separator(" "),
            time_separator(":"),
            nanoseconds_separator(".");
        std::ios_base::fmtflags prev_flags(os.flags());
        os.flags(std::ios::dec | std::ios::fixed);
        char prev_fill_char = os.fill();
        os.fill('0');
        if (subsecond_precision > 9) {
            subsecond_precision = 9;
        }
#if     defined(STX_PLATFORM_WINDOWS)
        SYSTEMTIME st;
        BOOL ret = FileTimeToSystemTime(&t, &st);
        if (!ret) {
            //STX_THROW_SYSTEM_ERROR("FileTimeToSystemTime");
        }
        os  << std::setw(4) << st.wYear << date_separator
            << std::setw(2) << st.wMonth + 1 << date_separator
            << std::setw(2) << st.wDay << datetime_separator
            << std::setw(2) << st.wHour << time_separator
            << std::setw(2) << st.wMinute << time_separator
            << std::setw(2) << st.wSecond;
        if (subsecond_precision > 0) {
            os << nanoseconds_separator;
            long n = 1;
            for (int i = 0; i < 9 - subsecond_precision; ++i) {
                n *= 10;
            }
            os << std::setw(subsecond_precision) << (st.wMilliseconds * (1000000/n));
        }
#elif   defined(STX_PLATFORM_POSIX)
        struct std::tm time_info;
#ifdef  STX_HAS_LOCALTIME_R
        localtime_r(&t.tv_sec, &time_info);
#else
        const struct std::tm* tp = localtime(&t.tv_sec);
        time_info = *tp;
#endif
        os  << std::setw(4) << time_info.tm_year + 1900 << date_separator
            << std::setw(2) << time_info.tm_mon + 1 << date_separator
            << std::setw(2) << time_info.tm_mday << datetime_separator
            << std::setw(2) << time_info.tm_hour << time_separator
            << std::setw(2) << time_info.tm_min << time_separator
            << std::setw(2) << time_info.tm_sec;
        if (subsecond_precision > 0) {
            os << nanoseconds_separator;
            long n = 1;
            for (int i = 0; i < 9 - subsecond_precision; ++i) {
                n *= 10;
            }
            os << std::setw(subsecond_precision) << (t.tv_nsec/n);
        }
#else
        struct std::tm* tp;
        int nsec = 0;
        tp = localtime(&rawtime);
        os  << std::setw(4) << tp->tm_year + 1900 << date_separator
            << std::setw(2) << tp->tm_mon + 1 << date_separator
            << std::setw(2) << tp->tm_mday << datetime_separator
            << std::setw(2) << tp->tm_hour << time_separator
            << std::setw(2) << tp->tm_min << time_separator
            << std::setw(2) << tp->tm_sec;
        if (subsecond_precision > 0) {
            os << nanoseconds_separator;
            long n = 1;
            for (int i = 0; i < 9 - subsecond_precision; ++i) {
                n *= 10;
            }
            os << std::setw(subsecond_precision) << (nsec/n);
        }
#endif
        os.fill(prev_fill_char);
        os.flags(prev_flags);
        return os;
    }
    
private:
    
#if defined(STX_PLATFORM_WINDOWS)
    FILETIME t;
#elif defined(STX_PLATFORM_POSIX)
    struct timespec t;
#else
    std::time_t rawtime;
#endif
};

} // namespace log
} // namespace stx

#endif // STX_LOG_DATE_TIME_HPP
