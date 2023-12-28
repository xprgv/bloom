#include "bloom.h"

extern BloomFilterCtx* bloom_filter_new(size_t size, size_t num_functions,
                                        ...) {
    BloomFilterCtx* filter = (BloomFilterCtx*)malloc(sizeof(BloomFilterCtx));
    if (filter == NULL) {
        return NULL;
    }
    filter->num_items      = 0;
    filter->array          = bit_array_new(size);
    filter->num_functions  = num_functions;
    filter->hash_functions = malloc(sizeof(HashFunc) * num_functions);
    if (filter->hash_functions == NULL) {
        return NULL;
    }

    va_list argp;
    va_start(argp, num_functions);
    for (int i = 0; i < num_functions; ++i) {
        filter->hash_functions[i] = va_arg(argp, HashFunc);
    }

    va_end(argp);
    return filter;
}

extern BloomFilterCtx* bloom_filter_new_default(size_t size) {
    return bloom_filter_new(size, 2, hashf_djb2, hashf_sdbm);
}

extern void bloom_filter_free(BloomFilterCtx* filter) {
    bit_array_free(filter->array);
    free(filter->hash_functions);
    free(filter);
}

extern void bloom_filter_put(BloomFilterCtx* filter, const void* data,
                             size_t len) {
    for (int i = 0; i < filter->num_functions; ++i) {
        Hash curr_hash = filter->hash_functions[i]((const char*)data);
        bit_array_set(filter->array, curr_hash % filter->array->size, true);
    }
    filter->num_items++;
}

extern void bloom_filter_put_str(BloomFilterCtx* filter, const char* str) {
    return bloom_filter_put(filter, str, strlen(str));
}

extern bool bloom_filter_test(BloomFilterCtx* filter, const void* data,
                              size_t len) {
    for (int i = 0; i < filter->num_functions; ++i) {
        Hash curr_hash = filter->hash_functions[i]((const char*)data);
        if (!bit_array_get(filter->array, curr_hash % filter->array->size)) {
            return false;
        }
    }
    return true;
}

extern bool bloom_filter_test_str(BloomFilterCtx* filter, const char* str) {
    return bloom_filter_test(filter, str, strlen(str));
}
