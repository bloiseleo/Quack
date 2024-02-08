#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define MAXIMUM 101

struct MapNode {
    char* key;
    char* value;
    struct MapNode* next;
};

typedef struct {
    struct MapNode* values[MAXIMUM];
    int length;
} Map;

Map* map() {
    Map* mp = malloc(sizeof(Map));
    mp->length = 0;
    for (int i = 0; i < MAXIMUM; i++) {
        mp->values[i] = NULL;
    }
    return mp;
}

int map_length(Map* map) {
    return map->length;
}

int hash(char* s) {
    int sum = 0;
    for(int i = 0; i < strlen(s); i++) {
        sum += (s[i] - 'a');
    }
    int h = sum % MAXIMUM;
    return h > MAXIMUM ? h - 100: h;
}

struct MapNode* createNode(char* key, char* value) {
    struct MapNode* mnp = malloc(sizeof(struct MapNode));
    mnp->key = strdup(key);
    mnp->value = strdup(value);
    mnp->next = NULL;
    return mnp;
}

void map_insert(Map* m, char* key, char* value) {
    int k = hash(key);
    struct MapNode* v = m->values[k];
    struct MapNode* mnp = createNode(key, value);
    if (v == NULL) {
        m->values[k] = mnp;
        m->length++;
        return;
    }
    struct MapNode* node = mnp;
    struct MapNode* nnext = mnp->next;
    while(nnext != NULL) {
     node = nnext;
     nnext = node->next;
    }
    node->next = v;
    m->length++;
}

char* map_get(Map* m, char* key) {
    int k = hash(key);
    struct MapNode* n = m->values[k];
    if (n == NULL) {
        return NULL;
    }
    if (n->next == NULL) {
    	return n->value;
    }
    struct MapNode* next = n->next;
    while(next != NULL) {
    	if (key == next->key) {
    		return next->value;
    	}
    }
    return NULL;
}
