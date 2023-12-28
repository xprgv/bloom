CC := gcc
OBJ_FLAGS := -Wall -Werror -fPIC -c
SHARED_FLAGS := -shared -fPIC
EXEC_FLAGS := -Wall -Werror


.PHONY: build build_so build_exec clean bitarray hash bloom

.DEFAULT_GOAL = build


bitarray: $(bitarray_sources)
	$(CC) $(OBJ_FLAGS) bitarray/bitarray.c -o bitarray/bitarray.o
	$(CC) $(SHARED_FLAGS) bitarray/bitarray.c -o bitarray/libbitarray.so


hash:
	$(CC) $(OBJ_FLAGS) hash/hash.c -o hash/hash.o
	$(CC) $(SHARED_FLAGS) hash/hash.c -o hash/libhash.so 


bloom:
	$(CC) $(OBJ_FLAGS) bloom.c -o bloom.o
	$(CC) $(SHARED_FLAGS) bloom.c -o libbloom.so


build2: bloom.h bloom.c
	$(CC) $(CFLAGS) $^ -o bloom.o


build_so:
	$(CC) $(SHARED_FLAGS) bloom.h bloom.c \
		hash/hash.h hash/hash.c \
		bitarray/bitarray.h bitarray/bitarray.c \
		-o libbloom.so

build_exec:
	$(CC) $(EXEC_FLAGS) test.c bloom.h bloom.c \
		hash/hash.h hash/hash.c \
		bitarray/bitarray.h bitarray/bitarray.c \
		-o bloom_test


build: hash bitarray bloom


clean:
	rm bloom.o libbloom.so \
		hash/hash.o hash/libhash.so \
		bitarray/bitarray.o bitarray/libbitarray.so

run: 
	cc -o ht-example example/main.c bloom.h bloom.c hash/hash.h hash/hash.c bitarray/bitarray.h bitarray/bitarray.c
	./ht-example
	rm ht-example
