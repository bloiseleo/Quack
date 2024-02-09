#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <linux/limits.h>
#include "freedesktop.h"

#define OPTIONS "n:"

extern char *optarg;

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
        fprintf(stderr, "%s is not a valid Desktop Entry Name. It must fullfill the regex ^[a-zA-z0-9_-]$\n", optarg);
        exit(-1);
    }
}

void parse(int c, char *v[])
{
    int opt;
    while ((opt = getopt(c, v, OPTIONS)) != -1)
    {
        switch (opt) {
            case 'n':
                checkDesktopEntryName();
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