all: funcptr prng

funcptr: 0x0_funcptr_example.c
	cc 0x0_funcptr_example.c -o build/funcptr_example.o

prng: 0x1_rand_example.c
	cc 0x1_rand_example.c -o build/rand_example.o

clean:
	rm -r build/*.o