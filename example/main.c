#include <stdio.h>

#include "../bloom.h"

int main(int argc, char* argv[]) {
    BloomFilterCtx* filter = bloom_filter_new_default(100);

    bloom_filter_put_str(filter, "hello");
    bool exists = bloom_filter_test_str(filter, "hello");
    printf("%d\n", exists);

    bloom_filter_free(filter);
    return 0;
}
