#ifndef HASHMAP_H
#define HASHMAP_H

struct hashmap;

struct hashmap *hashmap_create(int min, int max);

void hashmap_destroy(struct hashmap *map);

void hashmap_put(struct hashmap *map, int key, int value);

int hashmap_get(struct hashmap *map, int key);

#endif
