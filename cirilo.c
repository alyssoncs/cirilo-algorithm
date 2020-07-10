#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <stdbool.h>

#define MIN_NUMBER -1000000
#define MAX_NUMBER  1000000
int *closest;
int map_min;
int map_max;

int *create_map(int min, int max) {
	map_min = min;
	map_max = max;
	
	long size = (long)max - (long)min + 1;
	return malloc(sizeof(int) * size);
}

void destroy_map(int *map) {
	free(map);
}

void put(int key, int value) 
{
	long index = key - map_min;

	closest[index] = value;
}

int get(int key)
{
	long index = key - map_min;

	return closest[index];
}

int cmp (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}

int *findClosestMap(int arr[], int n) {
	for (int i = 0; i < n-1; i++) {
		put(arr[i], arr[i]);

		int middle = (arr[i] + arr[i+1]) / 2;

		for (int num = arr[i] + 1; num < arr[i+1]; num++) {
			if (num <= middle) {
				put(num, arr[i]);
			} else {
				put(num, arr[i+1]);
			}
		}
	}

	put(arr[n-1], arr[n-1]);

	return closest;
}

long diff(long a, long b) {
	return labs(a - b);
}

int smallestArray[2];
void find(int arrA[], int arrB[], int m, int n) {
	if (m > n) {
		int *tmp = arrA;
		arrA = arrB;
		arrB = tmp;

		int tmp_size = m;
		m = n;
		n = tmp_size;
	}

	qsort(arrA, m, sizeof(int), cmp);

	findClosestMap(arrA, m);

	smallestArray[0] = arrA[0];
	smallestArray[1] = arrB[0];

	int smallestFromA = arrA[0];
	int greatestFromA = arrA[m - 1];
	for (int i = 0; i < n; i++) {
		int currentFromA;

		if (arrB[i] > greatestFromA) {
			currentFromA = greatestFromA;
		} else if (arrB[i] < smallestFromA) {
			currentFromA = smallestFromA;
		} else {
			currentFromA = get(arrB[i]);
		}

		if (diff(currentFromA, arrB[i]) < diff(smallestArray[0], smallestArray[1])) {
			smallestArray[0] = currentFromA;
			smallestArray[1] = arrB[i];
		}
	}
}

int *randomArray(int size, int lower, int upper) {
	int *arr = malloc(sizeof(int) * size);
	if (arr != NULL) {


		for (int i = 0; i < size; i++) {
			arr[i] = (rand() % ((long)upper - (long)lower + 1)) + lower; 
		}
	}

	return arr;
}

void print_arr(int arr[], int n) {
	printf("[");
	for (int i = 0; i < n-1; i++) {
		printf("%d, ", arr[i]);
	}
	printf("%d]\n", arr[n-1]);
}

void test() {
	
	closest = create_map(-1, 28);

	int arrA[] = {-1, 5, 10, 20, 28, 3};
	int arrB[] = {26, 134, 135, 15, 17, 500};

	find(arrA, arrB, 6, 6);
	print_arr(smallestArray, 2);
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

	closest = create_map(MIN_NUMBER, MAX_NUMBER);

	if (closest == NULL) {
		fprintf(stderr, "unable to allocate so much space\n");
		return 2;
	}
	
	for (int i = start; i <= end; i += step) {

		int *arrA = randomArray(i, MIN_NUMBER, MAX_NUMBER);
		int *arrB = randomArray(i, MIN_NUMBER, MAX_NUMBER);

		//print_arr(arrA, i);
		//print_arr(arrB, i);
		
		find(arrA, arrB, i, i);

		print_arr(smallestArray, 2);
		printf("\n");
		
		free(arrA);
		free(arrB);
	}

	destroy_map(closest);



	return 0;
}
