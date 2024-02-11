#include <ctype.h>
#include <string.h>
#include <regex.h>

enum DesktopEntryTypes {
    APPLICATION,
    LINK,
    DIRECTORY
};

int validConventionValueFormat(char* value) {
    for (int i = 0; i < strlen(value); i++) {
        char c = value[i];
        if (!isalnum(c) && c != '.' && c != '_' && c != '-') {
            return 0;
        }
    } 
    return 1;
}

int checkVersionSyntax(char* s) {
    regex_t r;
    int vc = regcomp(&r, "^[0-9][0-9]*[.][0-9][0-9]*[.][0-9][0-9]*$", 0);
    if (vc != 0) {
        return 0;
    };
    int rv = regexec(&r, s, 0, NULL, 0);
    if (rv == 0) {
        return 1;
    } 
    return 0;
}

int checkStringType(char* s, int size) {
    for (int i = 0; i < size; i++) {
        int c = (int) s[i];
        if (c >= 0 && c <= 31 || c == 127) {
            return 0;
        }
    }
    return 1;
}