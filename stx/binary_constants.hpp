#ifndef STX_BINARY_CONSTANTS_HPP
#define STX_BINARY_CONSTANTS_HPP

#ifdef STX_NO_MACRO_PREFIX
#   define BIN8(x)  STX_BIN8(x)
#   define BIN16(x1, x2) STX_BIN16(x1, x2)
#   define BIN24(x1, x2, x3) STX_BIN24(x1, x2, x3)
#   define BIN32(x1, x2, x3, x4) STX_BIN32(x1, x2, x3, x4)
#   define BIN64(x1, x2, x3, x4, x5, x6, x7, x8) STX_BIN64(x1, x2, x3, x4, x5, x6, x7, x8)
#endif

#define STX_BIN8_IMPL(x) (               \
    ((x / 000000001ul) % 010)*(2 >> 1) + \
    ((x / 000000010ul) % 010)*(2 << 0) + \
    ((x / 000000100ul) % 010)*(2 << 1) + \
    ((x / 000001000ul) % 010)*(2 << 2) + \
    ((x / 000010000ul) % 010)*(2 << 3) + \
    ((x / 000100000ul) % 010)*(2 << 4) + \
    ((x / 001000000ul) % 010)*(2 << 5) + \
    ((x / 010000000ul) % 010)*(2 << 6))

#define STX_BIN8(x) STX_BIN8_IMPL(0##x)

//  Alternative implementation
/*
#define STX_BIN_N(x) (x) | x >> 3 | x >> 6 | x >> 9
#define STX_BIN_B(x) (x) & 0xf | (x) >> 12 & 0xf0
#define STX_BIN8(v) (STX_BIN_B(STX_BIN_N(0x##v)))
*/

#define STX_BIN16(x1, x2) \
    ((BIN8(x1) << 8) + BIN8(x2))

#define STX_BIN24(x1, x2, x3) \
    ((BIN8(x1) << 16) + (BIN8(x2) << 8) + BIN8(x3))

#define STX_BIN32(x1, x2, x3, x4) \
    ((BIN8(x1) << 24) + (BIN8(x2) << 16) + (BIN8(x3) << 8) + BIN8(x4))

/*
#define BIN64(x1, x2, x3, x4, x5, x6, x7, x8) \
    ((__int64(BIN32(x1, x2, x3, x4)) << 32) + __int64(BIN32(x5, x6, x7, x8)))
*/

#endif // STX_BINARY_CONSTANTS_HPP
