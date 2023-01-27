CC = gcc
cflags = -Wall -Wpedantic -std=c11
build_dir = build
src_dir = src/main

compare: ${build_dir}/cirilo.o ${build_dir}/hashmap.o ${build_dir}/classic.o ${src_dir}/algorithms/cirilo/cirilo.h ${src_dir}/compare.c
	mkdir -p bin
	$(CC) ${src_dir}/$@.c ${build_dir}/cirilo.o ${build_dir}/hashmap.o ${build_dir}/classic.o -o bin/$@ $(cflags)

${build_dir}/cirilo.o: ${src_dir}/algorithms/cirilo/cirilo.c ${src_dir}/libs/hashmap/hashmap.h
	mkdir -p ${build_dir}
	$(CC) -c $< -o $@ $(cflags) 

${build_dir}/hashmap.o: ${src_dir}/libs/hashmap/hashmap.c
	mkdir -p ${build_dir}
	$(CC) -c $< -o $@ $(cflags) 
	
${build_dir}/classic.o: ${src_dir}/algorithms/classic/classic.c
	mkdir -p ${build_dir}
	$(CC) -c $< -o $@ $(cflags) 

clean:
	rm ${build_dir}/*.o

