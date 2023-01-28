#include <stdlib.h>

#include "../libs/Unity/src/unity.h"
#include "../../main/algorithms/cirilo/cirilo.h"
#include "../../main/algorithms/classic/classic.h"

static int *first_arr;
static int *second_arr;

void setUp(void)
{
}

void tearDown(void)
{
	free(first_arr);
	free(second_arr);
}

static void assert_closest_pair_for_algorithm(int expected_first, int expected_second, int first_arr_size, int second_arr_size, int *(*algorithm) (int *, int *, int, int))
{
	int *closest_pair = algorithm(first_arr, second_arr, first_arr_size, second_arr_size);

	TEST_ASSERT_EQUAL_INT(expected_first, closest_pair[0]);
	TEST_ASSERT_EQUAL_INT(expected_second, closest_pair[1]);

	free(closest_pair);
}

static void assert_closest_pair(int expected_first, int expected_second, int first_arr_size, int second_arr_size)
{
	assert_closest_pair_for_algorithm(expected_first, expected_second, first_arr_size, second_arr_size, cirilo_find);
	assert_closest_pair_for_algorithm(expected_first, expected_second, first_arr_size, second_arr_size, classic_find);
}

static void test_singleton_arrays_return_singleton_pair(void)
{
	first_arr = malloc(1 * sizeof(*first_arr));
	first_arr[0] = 5;

	second_arr = malloc(1 * sizeof(*second_arr));
	second_arr[0] = 7;


	assert_closest_pair(5, 7, 1, 1);
}

static void test_arrays_with_the_same_elements(void)
{
	first_arr = malloc(4 * sizeof(*first_arr));
	for (int i = 0; i < 4; i++)
		first_arr[i] = 3;

	second_arr = malloc(6 * sizeof(*second_arr));
	for (int i = 0; i < 6; i++)
		second_arr[i] = 3;

	assert_closest_pair(3, 3, 4, 6);
}

static void test_sorted_arrays(void)
{
	first_arr = malloc(3 * sizeof(*first_arr));
	first_arr[0] = 1;
	first_arr[1] = 2;
	first_arr[2] = 3;

	second_arr = malloc(3 * sizeof(*second_arr));
	second_arr[0] = 5;
	second_arr[1] = 6;
	second_arr[2] = 7;

	assert_closest_pair(3, 5, 3, 3);
}

static void test_random_arrays(void)
{
	first_arr = malloc(3 * sizeof(*first_arr));
	first_arr[0] = 1;
	first_arr[1] = 12;
	first_arr[2] = 150;

	second_arr = malloc(4 * sizeof(*second_arr));
	second_arr[0] = 32;
	second_arr[1] = -20;
	second_arr[2] = 11;
	second_arr[3] = 8;

	assert_closest_pair(12, 11, 3, 4);
}


int main(void)
{
	UNITY_BEGIN();

	RUN_TEST(test_singleton_arrays_return_singleton_pair);
	RUN_TEST(test_arrays_with_the_same_elements);
	RUN_TEST(test_sorted_arrays);
	RUN_TEST(test_random_arrays);

	return UNITY_END();
}

