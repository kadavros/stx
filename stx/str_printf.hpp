#ifndef STX_STR_PRINTF_HPP_
#define STX_STR_PRINTF_HPP_

#include <string>
#include <vector>
#include <stdio.h>
#include <stdarg.h>
#include <stddef.h>
#include <string.h>

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

template <size_t BufSize, class StringType>
inline int str_vprintf_impl(StringType& s, bool is_sequential, const char* format, va_list args)
PRINTF_FORMAT(3, 0);

template <size_t BufSize, class StringType>
inline int str_vprintf_impl(StringType& s, bool is_sequential, const char* format, va_list args)
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
            struct scoped_buf
            {
                char* ptr;
                scoped_buf(size_t n) { ptr = (char*) malloc(n); }
                ~scoped_buf() { free(ptr); }
            };
            scoped_buf buf(size);
            p = buf.ptr;
            n = vsnprintf_impl(p, size, format, args);
            if (n < 0) return n;
            s.assign(p, p + n);
        }
    }
    return n;
}

template <class StringType>
inline bool is_continuous_string(StringType&) { return false; }

template <class Allocator>
inline bool is_continuous_string(std::vector<char, Allocator>&) { return true; }

#if __cplusplus >= 201103L
template <class Traits, class Allocator>
inline bool is_continuous_string(std::basic_string<char, Traits, Allocator>&) { return true; }
#endif

template <class StringType>
inline int str_vprintf(StringType& s, const char* format, va_list args)
PRINTF_FORMAT(2, 0);

template <class StringType>
inline int str_printf(StringType& s, const char* format, ...)
PRINTF_FORMAT(2, 3);

template <class StringType>
inline int str_vprintf(StringType& s, const char* format, va_list args)
{
    return str_vprintf_impl<1024, StringType>(s, is_continuous_string(s), format, args);
}

template <class StringType>
inline int str_printf(StringType& s, const char* format, ...)
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
