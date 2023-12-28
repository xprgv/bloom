#include "bitarray.h"

extern BitArray* bit_array_new(size_t size) {
    BitArray* array = malloc(sizeof(BitArray));
    if (array == NULL) {
        free(array);
        return NULL;
    }

    size_t alloc_size = size / CHUNK_SIZE;
    if (!(size % CHUNK_SIZE)) {
        alloc_size++;
    }

    array->buf = malloc(alloc_size);
    if (array->buf == NULL) {
        free(array->buf);
        free(array);
        return NULL;
    }
    array->size = size;

    return array;
}

extern void bit_array_free(BitArray* array) {
    free(array->buf);
    free(array);
}

extern int bit_array_set(BitArray* array, size_t idx, int value) {
    if (idx >= array->size) {
        return -1;
    }

    size_t chunk_offset = idx / CHUNK_SIZE;
    size_t bit_offset   = idx % CHUNK_SIZE;

    Chunk* chunk = &(array->buf[chunk_offset]);

    if (value) {
        *chunk = *chunk | (1 << bit_offset);
    } else {
        *chunk = *chunk & (~1 << bit_offset);
    }

    return 0;
}

extern int bit_array_get(const BitArray* array, size_t idx) {
    if (idx >= array->size) {
        return -1;
    }

    size_t chunk_offset = idx / CHUNK_SIZE;
    size_t bit_offset   = idx % CHUNK_SIZE;

    Chunk chunk = array->buf[chunk_offset];

    return (chunk >> bit_offset) & 1;
}
