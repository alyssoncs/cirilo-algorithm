#include <stdlib.h> 
  
static long diff(long a, long b) 
{
	return labs(a - b);
}

static int cmp (const void * a, const void * b) 
{
	return (*(int *)a - *(int *)b);
}

int *classic_find(int first_array[], int second_array[], int m, int n) 
{ 
	qsort(first_array, m, sizeof(int), cmp); 
	qsort(second_array, n, sizeof(int), cmp); 
  
	int a = 0, b = 0; 
  
	int *closest_pair = malloc(sizeof(int) * 2);

	if (!closest_pair) {
		return NULL;
	}
	
	closest_pair[0] = first_array[0];
	closest_pair[1] = second_array[0];
  
	while (a < m && b < n) { 
		if (diff(first_array[a], second_array[b]) < diff(closest_pair[0], closest_pair[1])) {
				closest_pair[0] = first_array[a];
				closest_pair[1] = second_array[b];
		}
  
		if (first_array[a] < second_array[b]) 
			a++; 
		else
			b++; 
	} 
  
	return closest_pair;  
} 
