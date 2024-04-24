#include "hash_map.h"

// allocate memory with size of map_item 
static map_item* map_new_item(const char* k, const char* v) {

	map_item* i = static_cast<map_item*>(malloc(sizeof(map_item)));
	i->key = _strdup(k);
	i->value = _strdup(v);
	return i;
}

// initialize new hashmap
map_hash_map* map_new() {

	map_hash_map* map = static_cast<map_hash_map*>(malloc(sizeof(map_hash_map)));

	map->size = 55;
	map->count = 0;
	map->items = static_cast<map_item**>(calloc((size_t)map->size, sizeof(map_item*)));
	
	return map;
}

static void map_delete_item(map_item* i) {

	free(i->key);
	free(i->value);
	free(i);
}

void map_delete(map_hash_map* map) {

	for (int i = 0; i < map->size; i++) {

		map_item* item = map->items[i];
		if (item != NULL)
			map_delete_item(item);
	}
	free(map->items);
	free(map);
}

				// str value, prime number, size of map
 static int hash(const char* s, const int PRIME, const int m) {
	
	 long hash = 0;
	 const int len_s = strlen(s);
	 for (int i = 0; i < len_s; i++) {
		 hash += (long)pow(PRIME, len_s - (i + 1)) * s[i];
		 hash = hash % m;
	 }
	 return (int)hash;
}


 // prime number should be larger, than ASCII alphabet, which size of 128
 int PRIME_1 = 135;
 int PRIME_2 = 212;
 static int double_hash(const char* s, const int map_size, const int i) {
	
	 const int hash_1 = hash(s, PRIME_1, map_size);
	 const int hash_2 = hash(s, PRIME_2, map_size);

	 return (hash_1 + (i * (hash_2 + 1))) % map_size;
 }
 

 static map_item DELETED_ITEM = { NULL, NULL };

 void insert(map_hash_map* map, const char* key, const char* val) {

	 map_item* item = map_new_item(key, val);
	 int index = double_hash(item->key, map->size, 0);
	 map_item* curr_item = map->items[index];

	 int i = 1;
	 while (curr_item != NULL) {

		 if (curr_item != &DELETED_ITEM) {

			 if (strcmp(curr_item->key, key) == 0) {
				 
				 map_delete_item(curr_item);
				 map->items[index] = item;
				 return;
			 }
		 }

		 index = double_hash(item->key, map->size, i);
		 curr_item = map->items[index];
		 i++;
	 }
	 map->items[index] = item;
	 map->count++;
 }

 void remove(map_hash_map* map, const char* key) {

	 int index = double_hash(key, map->size, 0);
	 map_item* item = map->items[index];
	 int i = 1;

	 while (item != NULL) {

		// if item isn't marked as deleted
		 if (item != &DELETED_ITEM) {

			 if (strcmp(item->key, key) == 0) {

				 map_delete_item(item);
				 map->items[index] = &DELETED_ITEM;
			 }
		 }

		 index = double_hash(key, map->size, i);
		 item = map->items[index];
		 i++;
	 }

	 map->count--;
 }
 char* find(map_hash_map* map, const char* key) {

	 int index = double_hash(key, map->size, 0);
	 map_item* item = map->items[index];
	 int i = 1;

	 while (item != NULL) {

		 if (strcmp(item->key, key) == 0)
			 return item->value;

		 index = double_hash(key, map->size, i);
		 item = map->items[index];
		 i++;
	 }

	 return NULL;
 }