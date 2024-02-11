#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <linux/limits.h>
#include "freedesktop.h"
#include <stdlib.h>

#define OPTIONS "n:aldv:g:c:e:"

extern char *optarg;

typedef struct {
    enum DesktopEntryTypes kind;
    char* name;
    char* version;
    char* genericName;
    int noDisplay;
    char* comment;
    char* iconPath;
    char* executable;
} Options;

Options* init() {
    Options* o = malloc(sizeof(Options));
    o->kind = APPLICATION;
    o->genericName = NULL;
    o->name = NULL;
    o->version = NULL;
    o->noDisplay = 0;
    o->comment = NULL;
    o->iconPath = NULL;
    o->executable = NULL;
    return o;
}

void checkDestkopNameEntry() {
    if(!checkStringType(optarg, strlen(optarg))) {
        printf("%s - Desktop Entry Names must not have control characteres", optarg);
        exit(-1);
    }
}

char* getExecutablePath()
{
    char path[PATH_MAX + 1];
    char *p = realpath(optarg, path);
    if (p == NULL) {
        fprintf(stderr, "%s is not a valid path. %s", optarg, path);
        exit(-1);
    }
    return p;
}

char* getIconPath() {
    char path[PATH_MAX + 1];
    char *p = realpath(optarg, path);
    if (p == NULL) {
        fprintf(stderr, "%s is not a valid path. %s", optarg, path);
        exit(-1);
    }
    return p;
}

void checkVersion() {
    if(!checkStringType(optarg, strlen(optarg))) {
        printf("%s - Version string must not have control characteres", optarg);
        exit(-1);
    }
    if(!checkVersionSyntax(optarg)) {
        printf("%s - Version string must follows the pattern d.d.d where d are digits from 0 to 9", optarg);
        exit(-1);
    }
}

char* getValue() {
    return strdup(optarg);
}

Options* parse(int c, char *v[])
{
    Options* o = init();
    int opt;
    while ((opt = getopt(c, v, OPTIONS)) != -1)
    {
        switch (opt) {
            case 'n':
                checkDestkopNameEntry();
                o->name = getValue();
                break;
            case 'a':
                o->kind = APPLICATION;
                break;
            case 'l':
                o->kind = LINK;
                break;
            case 'd':
                o->kind = DIRECTORY;
                break;
            case 'v':
                checkVersion();
                o->version = getValue();
                break;
            case 'g':
                o->genericName = getValue();
                break;
            case 'c':
                o->comment = getValue();
                break;
            case 'i':
                o->iconPath = getIconPath();
                break;
            case 'e':
                o->executable = getExecutablePath();
                break;
            default:
                break;
        }
    }
    return o;
}
