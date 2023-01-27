CC = gcc
cflags = -Wall -Wpedantic -std=c11
build_dir = build

test: ${build_dir}/cirilo.o ${build_dir}/hashmap.o ${build_dir}/classic.o src/algorithms/cirilo/cirilo.h src/test.c
	mkdir -p bin
	$(CC) src/$@.c ${build_dir}/cirilo.o ${build_dir}/hashmap.o ${build_dir}/classic.o -o bin/$@ $(cflags)

${build_dir}/cirilo.o: src/algorithms/cirilo/cirilo.c src/libs/hashmap/hashmap.h
	mkdir -p ${build_dir}
	$(CC) -c $< -o $@ $(cflags) 

${build_dir}/hashmap.o: src/libs/hashmap/hashmap.c
	mkdir -p ${build_dir}
	$(CC) -c $< -o $@ $(cflags) 
	
${build_dir}/classic.o: src/algorithms/classic/classic.c
	mkdir -p ${build_dir}
	$(CC) -c $< -o $@ $(cflags) 

clean:
	rm ${build_dir}/*.o

