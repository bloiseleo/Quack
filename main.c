#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <linux/limits.h>

#define OPTIONS "e:"
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

void parse(int c, char *v[])
{
    int opt;
    while ((opt = getopt(c, v, OPTIONS)) != -1)
    {
        switch (opt) {
            case 'e':
                char* p = getExecutablePath();
                printf("%s", p);
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