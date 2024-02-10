#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <linux/limits.h>
#include "freedesktop.h"

#define OPTIONS "n:aldv:"

extern char *optarg;

typedef struct {
    enum DesktopEntryTypes kind;
    char* name;
    char* version;
} Options;

Options* init() {
    Options* o = malloc(sizeof(Options));
    o->kind = APPLICATION;
    o->name = NULL;
    o->version = NULL;
    return o;
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

void checkDesktopEntryName() {
    if(!validConventionValueFormat(optarg)) {
        fprintf(stderr, "%s is not a valid name. It must fullfill the regex ^[a-zA-z0-9_-]$\n", optarg);
        exit(-1);
    }
}

void checkVersion() {
    if(!checkVersionSyntax(optarg)) {
        printf("%s - Version string must follows the pattern d.d.d where d are digits from 0 to 9", optarg);
        exit(-1);
    }
}

char* getValue() {
    return strdup(optarg);
}

void parse(int c, char *v[])
{
    Options* o = init();
    int opt;
    while ((opt = getopt(c, v, OPTIONS)) != -1)
    {
        switch (opt) {
            case 'n':
                checkDesktopEntryName();
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
            default:
                break;
        }
    }
}

int main(int argc, char *argv[])
{
    parse(argc, argv);
    return 0;
}