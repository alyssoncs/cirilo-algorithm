#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <limits.h>
#include <stdbool.h>

#include "algorithms/cirilo/cirilo.h"
#include "algorithms/classic/classic.h"

#define MIN_NUMBER -10000
#define MAX_NUMBER  10000

long diff(long a, long b) 
{
	return labs(a - b);
}

int *create_random_array(int size, int lower, int upper) 
{
	int *arr = malloc(sizeof(int) * size);
	if (arr) {
		for (int i = 0; i < size; i++) {
			arr[i] = (rand() % ((long)upper - (long)lower + 1)) + lower; 
		}
	}

	return arr;
}

int *copy_array(int arr[], int n)
{
	int *arr_c = NULL;
	if (arr) {
		int size = sizeof(int) * n;
		arr_c = malloc(size);

		if (arr_c) {
			memcpy(arr_c, arr, size);
		}
	}

	return arr_c;
}

void print_arr(int arr[], int n) 
{
	printf("[");
	for (int i = 0; i < n-1; i++) {
		printf("%d, ", arr[i]);
	}
	printf("%d]\n", arr[n-1]);
}

void test()
{
	int first_array[] = {-1, 5, 10, 20, 28, 3};
	int second_array[] = {26, 134, 135, 15, 17, 500};

	int m = sizeof(first_array) / sizeof(first_array[0]);
	int n = sizeof(second_array) / sizeof(second_array[0]);
	
	int *closest_pair = cirilo_find(first_array, second_array, m, n);
	print_arr(closest_pair, 2);

	free(closest_pair);
}

int main(int argc, char *argv[static argc])
{
	if (argc < 3) {
		return 1;
	}
	
	srand(time(NULL)); 

	int start, end, step;

	sscanf(argv[1], "%d", &start);
	sscanf(argv[2], "%d", &end);
	step = 1;

	printf("n,classic(ms),cirilo(ms)\n");
	for (int i = start; i <= end; i += step) {

		int *first_array = create_random_array(i, MIN_NUMBER, MAX_NUMBER);
		int *second_array = create_random_array(i, MIN_NUMBER, MAX_NUMBER);
		
		int *first_array_c = copy_array(first_array, i);
		int *second_array_c = copy_array(second_array, i);


		int *cirilo_closest_pair;
		int *classic_closest_pair;
		
		clock_t classic_dt;
		clock_t cirilo_dt;
		if (first_array && second_array && first_array_c && second_array_c) {
			clock_t classic_t0, classic_t1;
			classic_t0 = clock();
			classic_closest_pair = classic_find(first_array_c, second_array_c, i, i);
			classic_t1 = clock();
			
			classic_dt = classic_t1 - classic_t0;
			
			free(first_array_c);
			free(second_array_c);
			
			clock_t cirilo_t0, cirilo_t1;
			cirilo_t0 = clock();
			cirilo_closest_pair = cirilo_find(first_array, second_array, i, i);
			cirilo_t1 = clock();
			
			cirilo_dt = cirilo_t1 - cirilo_t0;
			
			free(first_array);
			free(second_array);
		} else {
			fprintf(stderr, "not able to allocate so much space");
			return 2;
		}

		if (!cirilo_closest_pair || !classic_closest_pair) {
			free(cirilo_closest_pair);
			free(classic_closest_pair);
			fprintf(stderr, "not able to allocate so much space");
			return 2;
		}

		free(cirilo_closest_pair);
		free(classic_closest_pair);
		
		double classic_duration = 1000.0*(classic_dt)/CLOCKS_PER_SEC;
		double cirilo_duration = 1000.0*(cirilo_dt)/CLOCKS_PER_SEC;
		printf("%d,%lf,%lf\n", i, classic_duration, cirilo_duration);
	}
	
	return 0;
}
