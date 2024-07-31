#include <stdlib.h> 
  
static long diff(long a, long b) 
{
	return labs(a - b);
}

static int cmp(const void * a, const void * b) 
{
	return (*(int *)a - *(int *)b);
}

int *classic_find(int first_array[], int second_array[], int m, int n) 
{ 
	qsort(first_array, m, sizeof(int), cmp); 
	qsort(second_array, n, sizeof(int), cmp); 
  
	int *closest_pair = malloc(sizeof(int) * 2);
	if (!closest_pair)
		return NULL;
	
	closest_pair[0] = first_array[0];
	closest_pair[1] = second_array[0];
  
	int i = 0, j = 0; 
	while (i < m && j < n) { 
		if (diff(first_array[i], second_array[j]) < diff(closest_pair[0], closest_pair[1])) {
			closest_pair[0] = first_array[i];
			closest_pair[1] = second_array[j];
		}
  
		if (first_array[i] < second_array[j]) 
			i++; 
		else
			j++; 
	} 
  
	return closest_pair;  
} 
