#include <stdlib.h>

#include "../../libs/hashmap/hashmap.h"

static struct hashmap *find_closest_map(int sorted_arr[], int n) 
{
	struct hashmap *const closest = hashmap_create(sorted_arr[0], sorted_arr[n - 1]);
	if (closest) {
		for (int i = 0; i < n-1; i++) {
			const int curr_elm = sorted_arr[i];
			const int next_elm = sorted_arr[i+1];

			hashmap_put(closest, curr_elm, curr_elm);

			int middle = (curr_elm + next_elm) / 2;
			for (int num = curr_elm + 1; num < next_elm; num++) {
				if (num <= middle)
					hashmap_put(closest, num, curr_elm);
				else
					hashmap_put(closest, num, next_elm);
			}
		}

		hashmap_put(closest, sorted_arr[n-1], sorted_arr[n-1]);
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
	int *const tmp = *first_array;
	*first_array = *second_array;
	*second_array = tmp;

	const int tmp_size = *m;
	*m = *n;
	*n = tmp_size;
}

static int find_closest(struct hashmap *closest_map, int sorted_arr[], int arr_size, int target)
{
	const int smallest = sorted_arr[0];
	const int greatest = sorted_arr[arr_size - 1];
	int closest;
	if (target > greatest) {
		closest = greatest;
	} else if (target < smallest) {
		closest = smallest;
	} else {
		closest = hashmap_get(closest_map, target);
	}

	return closest;

}

int *cirilo_find(int first_array[], int second_array[], int m, int n)
{
	if (m > n)
		swap_arrays(&first_array, &second_array, &m, &n);

	qsort(first_array, m, sizeof(int), cmp);

	struct hashmap *const closest = find_closest_map(first_array, m);
	int *const closest_pair = malloc(sizeof(int) * 2);

	if (!closest || !closest_pair)
		return NULL;
	
	closest_pair[0] = first_array[0];
	closest_pair[1] = second_array[0];

	for (int i = 0; i < n; i++) {
		const int closest_from_first = find_closest(closest, first_array, m, second_array[i]);

		if (diff(closest_from_first, second_array[i]) < diff(closest_pair[0], closest_pair[1])) {
			closest_pair[0] = closest_from_first;
			closest_pair[1] = second_array[i];
		}
	}

	hashmap_destroy(closest);

	return closest_pair;
}

