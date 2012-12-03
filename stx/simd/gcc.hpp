#ifndef STX_SIMD_GCC_HPP
#define STX_SIMD_GCC_HPP

#ifdef __GNUC__

#ifdef __3dNOW__
#endif

#ifdef __MMX__
#endif

#ifdef __SSE__
#endif

#ifdef __SSE2__
#endif

#ifdef __SSE3__
#endif

#ifdef __SSSE3__
#endif

#ifdef __SSE4a__
#endif

#if defined (__SSE4_2__) || defined (__SSE4_1__)
#endif

#ifdef __SSE5__
#endif

#if defined (__AES__) || defined (__PCLMUL__)
#endif

#ifdef __AVX__
#endif

//#include <immintrin.h>
//#include <mm3dnow.h>
//#include <mmintrin.h>
//#include <xmmintrin.h>
//#include <emmintrin.h>
//#include <pmmintrin.h>
//#include <tmmintrin.h>
//#include <smmintrin.h>
//#include <wmmintrin.h>
//#include <avxintrin.h>

#endif // __GNUC__

namespace stx {



} // namespace stx

#endif // STX_SIMD_GCC_HPP
