CC = gcc
CFLAGS = -Wall -Wpedantic -std=c11

SRC_DIR = src/main
TEST_DIR = src/test
BUILD_DIR = build

MAIN_BUILD_DIR = ${BUILD_DIR}/obj/main

MAIN_OUT_DIR = ${BUILD_DIR}/output/main
TEST_OUT_DIR = ${BUILD_DIR}/output/test

MAIN_BIN_DIR = ${MAIN_OUT_DIR}/bin
TEST_BIN_DIR = ${TEST_OUT_DIR}/bin

${MAIN_BIN_DIR}/compare: ${SRC_DIR}/compare.c ${MAIN_BUILD_DIR}/algorithms/cirilo/cirilo.o ${MAIN_BUILD_DIR}/libs/hashmap/hashmap.o ${MAIN_BUILD_DIR}/algorithms/classic/classic.o ${SRC_DIR}/algorithms/cirilo/cirilo.h | ${MAIN_BIN_DIR}
	${CC} $< ${MAIN_BUILD_DIR}/algorithms/cirilo/cirilo.o ${MAIN_BUILD_DIR}/libs/hashmap/hashmap.o ${MAIN_BUILD_DIR}/algorithms/classic/classic.o -o $@ ${CFLAGS}

${MAIN_BUILD_DIR}/algorithms/cirilo/cirilo.o: ${SRC_DIR}/algorithms/cirilo/cirilo.c ${SRC_DIR}/libs/hashmap/hashmap.h | ${MAIN_BUILD_DIR}/algorithms/cirilo
	${CC} -c $< -o $@ ${CFLAGS} 

${MAIN_BUILD_DIR}/libs/hashmap/hashmap.o: ${SRC_DIR}/libs/hashmap/hashmap.c | ${MAIN_BUILD_DIR}/libs/hashmap
	${CC} -c $< -o $@ ${CFLAGS} 
	
${MAIN_BUILD_DIR}/algorithms/classic/classic.o: ${SRC_DIR}/algorithms/classic/classic.c | ${MAIN_BUILD_DIR}/algorithms/classic
	${CC} -c $< -o $@ ${CFLAGS} 

${MAIN_BIN_DIR}:
	mkdir -p $@

${MAIN_BUILD_DIR}/algorithms/cirilo:
	mkdir -p $@

${MAIN_BUILD_DIR}/libs/hashmap:
	mkdir -p $@

${MAIN_BUILD_DIR}/algorithms/classic:
	mkdir -p $@

# testing
${TEST_BIN_DIR}/algorithms/smallest_pair_test: ${TEST_DIR}/algorithms/smallest_pair_test.c ${MAIN_BUILD_DIR}/algorithms/cirilo/cirilo.o ${MAIN_BUILD_DIR}/libs/hashmap/hashmap.o ${MAIN_BUILD_DIR}/algorithms/classic/classic.o ${TEST_DIR}/libs/Unity/src/unity.c | ${TEST_BIN_DIR}/algorithms
	${CC} $< ${MAIN_BUILD_DIR}/algorithms/cirilo/cirilo.o ${MAIN_BUILD_DIR}/libs/hashmap/hashmap.o ${MAIN_BUILD_DIR}/algorithms/classic/classic.o ${TEST_DIR}/libs/Unity/src/unity.c -o $@ ${CFLAGS}

${TEST_BIN_DIR}/algorithms:
	mkdir -p $@

test: ${TEST_BIN_DIR}/algorithms/smallest_pair_test
	${TEST_BIN_DIR}/algorithms/smallest_pair_test

clean:
	rm -rf ${BUILD_DIR}

