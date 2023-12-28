#ifndef BLOOM_FILTER_H
#define BLOOM_FILTER_H

#include <stdarg.h>
#include <stdbool.h>
#include <string.h>
#include <unitypes.h>

#include "bitarray/bitarray.h"
#include "hash/hash.h"

typedef struct BloomFilterCtx {
    BitArray* array;
    HashFunc* hash_functions;
    size_t    num_functions;
    size_t    num_items;
} BloomFilterCtx;

extern BloomFilterCtx* bloom_filter_new(size_t size, size_t num_functions, ...);
extern BloomFilterCtx* bloom_filter_new_default(size_t size);
extern void            bloom_filter_free(BloomFilterCtx* filter);
extern void bloom_filter_put(BloomFilterCtx* filter, const void* data,
                             size_t length);
extern void bloom_filter_put_str(BloomFilterCtx* filter, const char* str);
extern bool bloom_filter_test(BloomFilterCtx* filter, const void* data,
                              size_t length);
extern bool bloom_filter_test_str(BloomFilterCtx* filter, const char* str);

#endif
