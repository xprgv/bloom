#include "hash.h"

extern Hash hash_bitmix32(Hash hash) {
    hash ^= hash >> 16;
    hash *= 0x3243f6a9U;
    hash ^= hash >> 16;
    return hash;
}

// just sum all uint8 values of an ascii string
extern Hash hashf_krlose(const char* str) {
    Hash hash = 0;
    while (*str) {
        hash += *str;
        str++;
    }
    return hash;
}

#define HASH_DJB2_SEED 5381

// Bernstein hash djb2
extern unsigned int hashf_djb2(const char* str) {
    unsigned int hash = HASH_DJB2_SEED;
    while (*str) {                          // while char is not '\n'
        hash = ((hash << 5) + hash) + *str; // hash * 33 + c
        str++;
    }
    return hash;
}

extern Hash hashf_djb2_mix(const char* str, BitMixer mixer) {
    Hash hash = hashf_djb2(str);
    if (mixer != NULL) {
        hash = mixer(hash);
    }
    return hash;
}

extern Hash hashf_sdbm(const char* str) {
    Hash hash = 0;
    while (*str) {
        hash = *str + (hash << 6) + (hash << 16) - hash;
        str++;
    }
    return hash;
}

extern Hash hashf_jenkins(const char* str) {
    Hash hash = 0;
    while (*str) {
        hash += *str;
        hash += (hash << 10);
        hash ^= (hash >> 6);
        str++;
    }
    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);
    return hash;
}
