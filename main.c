#include <stdio.h>
#include <stdlib.h>
#include "definitions.h"
#include "map.h"

int main(int argc, char* argv[]) {
    Map* m = map();
    map_insert(m, "first", "teste");
    map_insert(m, "second", "teste2");

    printf("%s\n", map_get(m, "first"));
    printf("%s\n", map_get(m, "second"));
}