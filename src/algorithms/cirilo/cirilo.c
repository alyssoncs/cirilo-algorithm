#include <stdlib.h>

#include "../../libs/hashmap/hashmap.h"

static struct hashmap *find_closest_map(int arr[], int n) 
{
	struct hashmap *closest = hashmap_create(arr[0], arr[n - 1]);
	if (closest) {
		for (int i = 0; i < n-1; i++) {
			hashmap_put(closest, arr[i], arr[i]);

			int middle = (arr[i] + arr[i+1]) / 2;

			for (int num = arr[i] + 1; num < arr[i+1]; num++) {
				if (num <= middle) {
					hashmap_put(closest, num, arr[i]);
				} else {
					hashmap_put(closest, num, arr[i+1]);
				}
			}
		}

		hashmap_put(closest, arr[n-1], arr[n-1]);
	}

	return closest;
}

static long diff(long a, long b) 
{
	return labs(a - b);
}

static int cmp (const void * a, const void * b) 
{
	return (*(int *)a - *(int *)b);
}

static void swap_arrays(int **first_array, int **second_array, int *m, int *n)
{
	int *tmp = *first_array;
	*first_array = *second_array;
	*second_array = tmp;

	int tmp_size = *m;
	*m = *n;
	*n = tmp_size;
}

int *cirilo_find(int first_array[], int second_array[], int m, int n)
{
	if (m > n) {
		swap_arrays(&first_array, &second_array, &m, &n);
	}

	qsort(first_array, m, sizeof(int), cmp);

	struct hashmap *closest = find_closest_map(first_array, m);
	int *closest_pair = malloc(sizeof(int) * 2);

	if (!closest || !closest_pair) {
		return NULL;
	}
	
	closest_pair[0] = first_array[0];
	closest_pair[1] = second_array[0];

	int smallest_from_first = first_array[0];
	int greatest_from_first = first_array[m - 1];
	for (int i = 0; i < n; i++) {
		int current_from_first;

		if (second_array[i] > greatest_from_first) {
			current_from_first = greatest_from_first;
		} else if (second_array[i] < smallest_from_first) {
			current_from_first = smallest_from_first;
		} else {
			current_from_first = hashmap_get(closest, second_array[i]);
		}

		if (diff(current_from_first, second_array[i]) < diff(closest_pair[0], closest_pair[1])) {
			closest_pair[0] = current_from_first;
			closest_pair[1] = second_array[i];
		}
	}

	hashmap_destroy(closest);

	return closest_pair;
}

