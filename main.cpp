#include "hash_map.h"
#include <iostream>

int main() {

	map_hash_map* map1 = map_new();

	insert(map1, "1", "kotok");
	insert(map1, "2", "mal");
	insert(map1, "3", "boss");

	cout << "1. " << find(map1, "1") << "\n";
	cout << "2. " << find(map1, "2") << "\n";
	cout << "3. " << find(map1, "3") << "\n";
}