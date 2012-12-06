#ifndef STX_HAS_FUNCTION_HPP
#define STX_HAS_FUNCTION_HPP

/*
    STX_DECLARE_HAS_FUNCTION macro declares a function presence checking function
    named has_F(), where F - name of a function, which presence we want to check.
    has_F() is a portable runtime check. If there is no function with given
    name and signature, has_F() returns false, otherwise it returns true.
    We can't call function of interest directly, because it just won't compile
    on platform where it's absent, but we can access it via pointer.
    STX_DECLARE_HAS_FUNCTION declares such pointer returning function with
    suffix _ptr, added to original function's name.
    
    Usage example. Suppose we wand to check wether snprintf is supported.
    
    #include <stdio.h> // We must include header where snprintf may be declared.
    STX_DECLARE_HAS_FUNCTION(snprintf, int, (char*, size_t, const char*, ...))
    #include <iostream>
    
    int main(int argc, char** argv)
    {
        char buf[256] = { 0 };
        int x = 12345;
        if (has_snprintf()) {
            std::cout << "snprintf is present" << std::endl;
            snprintf_ptr()(buf, 6, "%d", x);
            std::cout << buf << std::endl;
        } else {
            std::cout << "snprintf is absent" << std::endl;
        }
        return 0;
    }
    
    Note: some function may be declared as macros, therefore complete function
    checking facility might be more complicated. Considering snprintf example,
    complete function presence checking looks like this:
    
    #include <stdio.h> // We must include header where snprintf may be declared.
    #ifdef snprintf    // Check, whether snprintf is declared as macro.
    inline bool has_snprintf() { return true; };
    inline int (*snprintf_ptr())(char*, size_t, const char*, ...) { return snprintf; }
    #else
    STX_DECLARE_HAS_FUNCTION(snprintf, int, (char*, size_t, const char*, ...))
    #endif
*/

#define STX_DECLARE_HAS_FUNCTION(function_name, return_type, param_types) \
    \
    struct has_##function_name##_t {}; \
    \
    inline void function_name(has_##function_name##_t) {} \
    \
    inline bool has_##function_name() \
    { \
        void (*fp1)() = (void (*)()) \
            ((void (*)(has_##function_name##_t)) function_name); \
        void (*fp2)() = (void (*)()) \
            ((return_type (*)param_types) function_name); \
        return (fp1 != fp2); \
    } \
    inline return_type (*function_name##_ptr())param_types \
    { \
        return (return_type (*)param_types) function_name; \
    }

#endif // STX_HAS_FUNCTION_HPP
