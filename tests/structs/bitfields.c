#include <stdlib.h>

typedef unsigned char uchar;
typedef unsigned short ushort;

// *** Dumping AST Record Layout
//          0 | struct three_byte_date
//      0:0-4 |   unsigned char d
//      0:5-8 |   unsigned char m
//     1:1-15 |   unsigned short y
//            | [sizeof=3, align=1]
typedef struct {
    unsigned char day: 5;
    unsigned char month: 4;
    unsigned short year: 15;
} __attribute((packed)) three_byte_date;

size_t size_of_three_byte_date() {
    return sizeof(three_byte_date);
}

unsigned char compare_three_byte_date(three_byte_date const* tbd, uchar d, uchar m, ushort y) {
    if (tbd->day != d) {
        return 1;
    }

    if (tbd->month != m) {
        return 2;
    }

    if (tbd->year != y) {
        return 3;
    }

    return 0;
}

void write_three_byte_date(three_byte_date* tbd, uchar d, uchar m, ushort y) {
    tbd->day = d;
    tbd->month = m;
    tbd->year = y;

}

// *** Dumping AST Record Layout
//          0 | struct test3
//      0:0-6 |   long x
//        2:- |   short
//      2:0-9 |   unsigned long z
//            | [sizeof=8, align=8]
typedef struct {
    signed long x: 7;
    signed short: 0;
    unsigned long z: 10;
} padded_bitfield;

size_t size_of_padded_bitfield() {
    return sizeof(padded_bitfield);
}

void ops_padded_bitfield(padded_bitfield* bf) {
    // These should not add casts to rhs
    // (shifts seem to add them for some reason)
    bf->x %= 2L;
    bf->x += 1L;
    bf->x *= 2L;
    bf->x -= 1L;
    bf->x /= 2L;
    bf->x ^= 1L;
    bf->x >>= 2L;
    bf->x <<= 1L;
    bf->x &= 1L;
    bf->x |= 2L;

    // These should add casts to rhs
    bf->x %= 2;
    bf->x += 1;
    bf->x *= 2;
    bf->x -= 1;
    bf->x /= 2;
    bf->x ^= 1;
    bf->x >>= 2;
    bf->x <<= 1;
    bf->x &= 1;
    bf->x |= 2;
}

padded_bitfield ops_padded_bitfield_init(void) {
    padded_bitfield bf = {13, 0};
    // These should not add casts to rhs
    // (shifts seem to add them for some reason)
    bf.x %= 2L;
    bf.x += 1L;
    bf.x *= 2L;
    bf.x -= 1L;
    bf.x /= 2L;
    bf.x ^= 1L;
    bf.x >>= 2L;
    bf.x <<= 1L;
    bf.x &= 1L;
    bf.x |= 2L;

    // These should add casts to rhs
    bf.x %= 2;
    bf.x += 1;
    bf.x *= 2;
    bf.x -= 1;
    bf.x /= 2;
    bf.x ^= 1;
    bf.x >>= 2;
    bf.x <<= 1;
    bf.x &= 1;
    bf.x |= 2;

    return bf;
}

three_byte_date static_date = {13, 12, 2018};
