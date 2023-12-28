#ifndef BITARRAY_H
#define BITARRAY_H

#include <stdlib.h>
#include <unitypes.h>

typedef uint8_t Chunk;

// assume that byte in target platform contains 8 bits
#define BITS_IN_BYTE 8
#define CHUNK_SIZE   (BITS_IN_BYTE * (sizeof(Chunk)))

typedef struct BitArray {
    Chunk* buf;
    size_t size;
} BitArray;

extern BitArray* bit_array_new(size_t size);
extern void      bit_array_free(BitArray* array);
extern int       bit_array_set(BitArray* array, size_t idx, int value);
extern int       bit_array_get(const BitArray* array, size_t idx);

#endif
