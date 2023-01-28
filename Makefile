# compiler
CC = gcc
CFLAGS = -Wall -Wpedantic -std=c11 -MP -MD

# directories
MAIN_SRC_DIR = src/main
TEST_SRC_DIR = src/test
BUILD_DIR = build

# objects
MAIN_OBJ_DIR = ${BUILD_DIR}/obj/main
TEST_OBJ_DIR = ${BUILD_DIR}/obj/test

# binaries
MAIN_BIN_DIR = ${BUILD_DIR}/output/main/bin
TEST_BIN_DIR = ${BUILD_DIR}/output/test/bin

# files
MAIN_FILE = ${MAIN_SRC_DIR}/compare.c
MAIN_SRC_FILES := $(shell find ${MAIN_SRC_DIR} -name '*.c')
MAIN_OBJ_FILES := $(shell echo $(patsubst %.c,%.o, ${MAIN_SRC_FILES}) | sed s#src/#build/obj/#g)
MAIN_DEP_FILES := $(patsubst %.o,%.d, ${MAIN_OBJ_FILES})

TEST_SRC_FILES := $(shell find ${TEST_SRC_DIR} -name '*.c')
TEST_OBJ_FILES := $(shell echo $(patsubst %.c,%.o, ${TEST_SRC_FILES}) | sed s#src/#build/obj/#g)
TEST_DEP_FILES := $(patsubst %.o,%.d, ${TEST_OBJ_FILES})

# main
${MAIN_BIN_DIR}/compare: ${MAIN_FILE} ${MAIN_OBJ_FILES}
	@mkdir -p $(dir $@)
	${CC} ${CFLAGS} ${MAIN_OBJ_FILES} -o $@

${MAIN_OBJ_DIR}/%.o: ${MAIN_SRC_DIR}/%.c
	@mkdir -p $(dir $@)
	${CC} ${CFLAGS} -c $< -o $@

# testing
${TEST_BIN_DIR}/algorithms/smallest_pair_test: ${TEST_OBJ_DIR}/algorithms/smallest_pair_test.o ${MAIN_OBJ_DIR}/algorithms/cirilo/cirilo.o ${MAIN_OBJ_DIR}/libs/hashmap/hashmap.o ${MAIN_OBJ_DIR}/algorithms/classic/classic.o ${TEST_SRC_DIR}/libs/Unity/src/unity.c
	@mkdir -p $(dir $@)
	${CC} ${CFLAGS} $^ -o $@ 

${TEST_OBJ_DIR}/%.o: ${TEST_SRC_DIR}/%.c
	@mkdir -p $(dir $@)
	${CC} ${CFLAGS} -c $< -o $@

test: ${TEST_BIN_DIR}/algorithms/smallest_pair_test
	${TEST_BIN_DIR}/algorithms/smallest_pair_test

# cleaning
clean:
	rm -rf ${BUILD_DIR}

-include ${MAIN_DEP_FILES}
-include ${TEST_DEP_FILES}

