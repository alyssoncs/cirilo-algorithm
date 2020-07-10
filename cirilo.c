#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <stdbool.h>

int *closest;

int *create_map(long len) {
	return malloc(sizeof(int) * len);
}

void destroy_map(int *map) {
	free(map);
}

void put(int key, int value) 
{
	long index = (long)INT_MAX;
	index -= 0;
	index += key;

	closest[index] = value;
}

bool get(int key)
{
	long index = (long)INT_MAX;
	index -= 0;
	index += key;

	return closest[index];
}

int cmp (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}

int *findClosestMap(int arr[], int n) {
	for (int i = 0; i < n-1; i++) {
		put(arr[i], arr[i]);

		int middle = (arr[i] + arr[i+1]) / 2;

		for (int n = arr[i] + 1; n < arr[i+1]; n++) {
			if (n <= middle) {
				put(n, arr[i]);
			} else {
				put(n, arr[i+1]);
			}
		}
	}

	put(arr[n], arr[n]);

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

		srand(time(NULL)); 

		for (int i = 0; i < size; i++) {
			arr[i] = (rand() % ((long)upper - (long)lower + 1)) + lower; 
		}
	}

	return arr;
}

int main(int argc, char *argv[static argc])
{
	if (argc < 3) {
		return 1;
	}

	int start, end, step;

	sscanf(argv[1], "%d", &start);
	sscanf(argv[1], "%d", &end);
	step = 1;

	closest = create_map((long)INT_MAX - (long)INT_MIN + 1);
	
	for (int i = start; i <= end; i += step) {

		int *arrA = randomArray(i, INT_MIN, INT_MAX);
		int *arrB = randomArray(i, INT_MIN, INT_MAX);

		find(arrA, arrB, i, i);

		free(arrA);
		free(arrB);
	}

	destroy_map(closest);


	return 0;
}
