typedef struct {
	char** values;
} Map;
/**
 * Creates and initiliazes a struct Map in Heap.
 */
Map* map();
/**
 * Get the length of values inserted inside Map.
 */
int map_length(Map* map);
/**
 * Insert a given value inside of the map upon the given key.
 */ 
void map_insert(Map* m, char* key, char* value);
/**
 * Retrieves a given value from map.
 */ 
char* map_get(Map* m, char* key);