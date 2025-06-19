all: funcptr prng goc

funcptr: 0x0_funcptr_example.c
	cc 0x0_funcptr_example.c -o build/funcptr_example.o

prng: 0x1_rand_example.c
	cc 0x1_rand_example.c -o build/rand_example.o

goc: 0x2_game_of_chance.c
	cc 0x2_game_of_chance.c -o build/game_of_chance.o

clean:
	rm -r build/*.o