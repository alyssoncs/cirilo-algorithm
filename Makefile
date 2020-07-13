CC = gcc
cflags = -Wall -std=c11

test: obj/cirilo.o obj/hashmap.o obj/classic.o src/algorithms/cirilo/cirilo.h src/test.c
	$(CC) src/$@.c obj/cirilo.o obj/hashmap.o obj/classic.o -o bin/$@ $(cflags)

obj/cirilo.o: src/algorithms/cirilo/cirilo.c src/libs/hashmap/hashmap.h
	$(CC) -c $< -o $@ $(cflags) 

obj/hashmap.o: src/libs/hashmap/hashmap.c
	$(CC) -c $< -o $@ $(cflags) 
	
obj/classic.o: src/algorithms/classic/classic.c
	$(CC) -c $< -o $@ $(cflags) 

clean:
	rm obj/*.o

