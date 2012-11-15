#ifndef STX_BIT_CAST_HPP
#define STX_BIT_CAST_HPP

namespace stx {

//
// [thanks to chromium code base]
//
// bit_cast<Dst,Src> is a template function that implements the
// equivalent of "*reinterpret_cast<Dst*>(&source)".
//
//   float f = 3.14159265358979;
//   int i = bit_cast<int32>(f);
//   // i = 0x40490fdb
//
// The classical address-casting method is:
//
//   // WRONG
//   float f = 3.14159265358979;            // WRONG
//   int i = * reinterpret_cast<int*>(&f);  // WRONG
//
// The address-casting method actually produces undefined behavior
// according to ISO C++ specification section 3.10 -15 -. Roughly, this
// section says: if an object in memory has one type, and a program
// accesses it with a different type, then the result is undefined
// behavior for most values of "different type".
//
// This is true for any cast syntax, either *(int*)&f or
// *reinterpret_cast<int*>(&f).  And it is particularly true for
// conversions betweeen integral lvalues and floating-point lvalues.
//
// The purpose of 3.10 -15- is to allow optimizing compilers to assume
// that expressions with different types refer to different memory. gcc
// 4.0.1 has an optimizer that takes advantage of this. So a
// non-conforming program quietly produces wildly incorrect output.
//
// The problem is not the use of reinterpret_cast. The problem is type
// punning: holding an object in memory of one type and reading its bits
// back using a different type.
//
// The C++ standard is more subtle and complex than this, but that
// is the basic idea.
//
// Anyways ...
//
// bit_cast<> calls memcpy() which is blessed by the standard,
// especially by the example in section 3.9. Also, of course,
// bit_cast<> wraps up the nasty logic in one place.
//
// Fortunately memcpy() is very fast. In optimized mode, with a
// constant size, gcc 2.95.3, gcc 4.0.1, and msvc 7.1 produce inline
// code with the minimal amount of data movement. On a 32-bit system,
// memcpy(d,s,4) compiles to one load and one store, and memcpy(d,s,8)
// compiles to two loads and two stores.
//
// This code was tested with gcc 2.95.3, gcc 4.0.1, icc 8.1, and msvc 7.1.
//
// WARNING: if Dst or Src is a non-POD type, the result of the memcpy
// is likely to surprise you.

template <class Dst, class Src>
inline Dst bit_cast(const Src& source) {
    // Compile time assertion: sizeof(Dst) == sizeof(Src)
    // A compile error here means your Dst and Src have different sizes.
    typedef char verify_sizes_are_equal [sizeof(Dst) == sizeof(Src) ? 1 : -1];

    Dst dest;
    memcpy(&dest, &source, sizeof(dest));
    return dest;
}

} // namespace stx

#endif // STX_BIT_CAST_HPP
