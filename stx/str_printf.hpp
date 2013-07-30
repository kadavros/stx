#ifndef STX_STR_PRINTF_HPP_
#define STX_STR_PRINTF_HPP_

#include <string>
#include <vector>
#include <stdio.h>
#include <stdarg.h>
#include <stddef.h>

#ifdef __GNUC__
#define PRINTF_FORMAT(format_param, dots_param) \
    __attribute__((format(printf, format_param, dots_param)))
#else
#define PRINTF_FORMAT(format_param, dots_param)
#endif

namespace stx {

inline int vsnprintf_impl(char* buffer, size_t size, const char* format, va_list arguments)
PRINTF_FORMAT(3, 0);

#ifdef _WIN32
inline int vsnprintf_impl(char* buffer, size_t size, const char* format, va_list arguments)
{
    int length = _vsprintf_p(buffer, size, format, arguments);
    if (length < 0) {
        if (size > 0 && buffer) {
            buffer[0] = 0;
        }
        length = _vscprintf_p(format, arguments);
    }
    return length;
}
#else
inline int vsnprintf_impl(char* buffer, size_t size, const char* format, va_list arguments)
{
    return vsnprintf(buffer, size, format, arguments);
}
#endif

template <size_t BufSize, class String>
inline int str_vprintf_impl(String& s, bool is_sequential, const char* format, va_list args)
PRINTF_FORMAT(3, 0);

template <size_t BufSize, class String>
inline int str_vprintf_impl(String& s, bool is_sequential, const char* format, va_list args)
{
    char buf[BufSize];
    char* p = buf;
    int size = BufSize;
    
    if (s.capacity() >= BufSize) {
        s.resize(s.capacity());
        p = &s[0];
        size = s.size();
    }
    
    int n = vsnprintf_impl(p, size, format, args);
    if (n < 0) {
        // Format error occured.
    } else if (n < size) {
        if (p == buf) {
            s.assign(p, p + n);
        } else if (s.size() > (size_t) n) {
            s.resize(n);
        }
    } else {
        size = n + 1;
        if (is_sequential) {
            s.resize(size);
            n = vsnprintf_impl(&s[0], size, format, args);
            if (n < 0) return n;
        } else {
            std::vector<char> v;
            v.resize(size);
            n = vsnprintf_impl(&v[0], size, format, args);
            if (n < 0) return n;
            p = &v[0];
            s.assign(p, p + n);
        }
    }
    return n;
}

template <class String> inline bool is_continuous_string(String&) { return false; }
//template <> inline bool is_continuous_string(std::string&) { return true; } // Only for C++11
template <> inline bool is_continuous_string(std::vector<char>&) { return true; }

template <class String>
inline int str_vprintf(String& s, const char* format, va_list args)
PRINTF_FORMAT(2, 0);

template <class String>
inline int str_printf(String& s, const char* format, ...)
PRINTF_FORMAT(2, 3);

template <class String>
inline int str_vprintf(String& s, const char* format, va_list args)
{
    return str_vprintf_impl<1024, String>(s, is_continuous_string(s), format, args);
}

template <class String>
inline int str_printf(String& s, const char* format, ...)
{
    va_list args;
    va_start(args, format);
    int n;
    try {
        n = str_vprintf(s, format, args);
        va_end(args);
    } catch (...) {
        va_end(args);
        throw;
    }
    return n;
}

} // namespace stx

#endif // STX_STR_PRINTF_HPP_
