#include <stdlib.h>

struct hashmap {
	int *map;
	int min_value;
	int max_value;
};

struct hashmap *hashmap_create(int min, int max)
{
	struct hashmap *hashmap= malloc(sizeof(hashmap));
	
	long size = (long)max - (long)min + 1;
	int *map = malloc(sizeof(int) * size);
	
	if (hashmap && map) {
		hashmap->map = map;
		hashmap->min_value = min;
		hashmap->max_value = max;
	} else {
		free(hashmap);
		free(map);
	}
	
	return hashmap;
}

void hashmap_destroy(struct hashmap *map)
{
	if (map != NULL) {
		free(map->map);
		free(map);
	}
}

void hashmap_put(struct hashmap map[static 1], int key, int value) 
{
	long index = key - map->min_value;

	map->map[index] = value;
}

int hashmap_get(struct hashmap map[static 1], int key)
{
	long index = key - map->min_value;

	return map->map[index];
}


