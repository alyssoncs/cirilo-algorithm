#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "algorithms/cirilo/cirilo.h"
#include "algorithms/classic/classic.h"

#define MIN_NUMBER -10000
#define MAX_NUMBER  10000

static int *create_random_array(int size, int lower, int upper) 
{
	int *const arr = malloc(sizeof(int) * size);
	if (arr) {
		for (int i = 0; i < size; i++) {
			arr[i] = (rand() % ((long)upper - (long)lower + 1)) + lower; 
		}
	}

	return arr;
}

static int *copy_array(const int arr[const], int n)
{
	int *arr_c = NULL;
	if (arr) {
		int size = sizeof(int) * n;
		arr_c = malloc(size);

		if (arr_c)
			memcpy(arr_c, arr, size);
	}

	return arr_c;
}

struct args {
	const int start;
	const int end;
	const int step;
};

union args_union {
	const struct args args;
	const int error;
};

struct args_result {
	const union args_union value;
	const bool is_success;
};

static struct args_result read_args(int argc, char *argv[static argc])
{
	if (argc < 3) {
		return (struct args_result) { 
			.is_success = false, 
			.value = { .error = 1 },
		};
	}
	
	int start, end, step;

	sscanf(argv[1], "%d", &start);
	sscanf(argv[2], "%d", &end);

	if (argc > 3) {
		sscanf(argv[3], "%d", &step);
	} else {
		step = 1;
	}

	return (struct args_result) {
		.is_success = true,
		.value = {
			.args = {
				.start = start,
				.end = end,
				.step = step,
			}
		},
	};
}

union measure_union {
	const double measurement;
	const int error;
};

struct measure_result {
	const bool is_success;
	const union measure_union value;
};

static struct measure_result measure_success(double measurement) {
	return (struct measure_result) {
		.is_success = true,
		.value = { .measurement = measurement },
	};
}

static struct measure_result measure_error() {
	return (struct measure_result) {
		.is_success = false,
		.value = { .error = 2 },
	};
}

static struct measure_result measure(
	int first_arr[], 
	int second_arr[], 
	int size, 
	int *(*algorithm)(int[], int[], int, int)
) { 
	const clock_t t0 = clock();
	int *const closest_pair = algorithm(first_arr, second_arr, size, size);
	const clock_t t1 = clock();
	
	free(closest_pair);
	if (!closest_pair)
		return measure_error();

	const clock_t dt = t1 - t0;
	const double measurement = 1000.0*(dt)/CLOCKS_PER_SEC;

	return measure_success(measurement);
}

static void print_memory_error() {
	fprintf(stderr, "not able to allocate so much space\n");
}

static void print_measurement(int arr_size, struct measure_result classic, struct measure_result cirilo) {
	printf("%d,%lf,%lf\n", arr_size, classic.value.measurement, cirilo.value.measurement);
}


int main(int argc, char *argv[static argc])
{
	const struct args_result result = read_args(argc, argv);
	if (!result.is_success) {
		fprintf(stderr, "Please, provide [start], [end] and [step (optional)] arguments\n");
		return result.value.error;
	}

	const struct args args = result.value.args;
	
	srand(time(NULL)); 

	printf("n,classic(ms),cirilo(ms)\n");
	for (int arr_size = args.start; arr_size <= args.end; arr_size += args.step) {

		int *first_array = create_random_array(arr_size, MIN_NUMBER, MAX_NUMBER);
		int *second_array = create_random_array(arr_size, MIN_NUMBER, MAX_NUMBER);
		
		int *first_array_c = copy_array(first_array, arr_size);
		int *second_array_c = copy_array(second_array, arr_size);

		if (first_array && second_array && first_array_c && second_array_c) {
			const struct measure_result classic_result = measure(first_array_c, second_array_c, arr_size, classic_find);
			free(first_array_c);
			free(second_array_c);
			if (!classic_result.is_success) {
				print_memory_error();
				return classic_result.value.error;
			}
			
			const struct measure_result cirilo_result = measure(first_array, second_array, arr_size, cirilo_find);
			free(first_array);
			free(second_array);

			if (!cirilo_result.is_success) {
				print_memory_error();
				return cirilo_result.value.error;
			}

			print_measurement(arr_size, classic_result, cirilo_result);
		} else {
			free(first_array_c);
			free(second_array_c);
			free(first_array);
			free(second_array);

			fprintf(stderr, "not able to allocate so much space\n");
			return 3;
		}

	}
	
	return 0;
}
