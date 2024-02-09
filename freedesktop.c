#include <ctype.h>
#include <string.h>

int validConventionValueFormat(char* value) {
    for (int i = 0; i < strlen(value); i++) {
        char c = value[i];
        if (!isalnum(c) && c != '.' && c != '_' && c != '-') {
            return 0;
        }
    } 
    return 1;
}
