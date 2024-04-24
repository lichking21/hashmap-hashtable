#ifndef HASH_MAP_H
#define HASH_MAP_H

#include <cstdlib>
#include <cstring>
#include <cmath>

using namespace std;

typedef struct {

	char* key;
	char* value;
}map_item;

typedef struct {

	int size;			// total size of the map
	int count;					// current count of items
	map_item** items;			// array of pointers to items	
}map_hash_map;

map_item* map_new_item(const char* k, const char* v);
map_hash_map* map_new();

void map_delete_item(map_item* i);
void map_delete(map_hash_map* map);

int hash(const char* s, const int a, const int m);
int double_hash(const char* s, const int map_size, const int i);

void insert(map_hash_map* map, const char* key, const char* val);
void remove(map_hash_map* map, const char* key);
char* find(map_hash_map* map, const char* key);

#endif


