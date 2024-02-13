#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

int isDirectory(char* path) {
    struct stat stats;
    int status = stat(path, &stats);
    if (status != 0) {
        return 0;
    }
    return S_ISDIR(stats.st_mode);
}

char* join(int npaths, ...) {
    va_list pathList;
    va_start(pathList, npaths);
    int bfsize = 1024;
    char* buff = malloc(sizeof(char) * bfsize);
    int transferedToBuffer = 0;
    for (int i = 0; i < npaths; i++) {
        char* p = va_arg(pathList, char*);
        int written = 0;
        int total = strlen(p);
        if ((transferedToBuffer + total + 1) >= bfsize) {
            bfsize = (total + bfsize) * 2; // Make sure that realloc will suport the new string and double it;
            buff = realloc(buff, sizeof(char) * bfsize);
        }
        while (written < total) {
            buff[transferedToBuffer++] = p[written];
            written++;
        }
        if (i != (npaths - 1)) {
            buff[transferedToBuffer++] = '/';    
        }
    }
    buff = realloc(buff, sizeof(char) * strlen(buff));
    return buff;
}

int createDirIfNotExists(char* path) {
    if (isDirectory(path)) {
        return 1;
    }
    int res = mkdir(path, 0755);
    return res == 0 ? 1: 0;
}

int validExecutable(char* executable) {
    char* paths = getenv("PATH");
    char* p = strtok(paths, ":");
    int exec = 0;
    while (p != NULL) {
        char* joined = join(2, p, executable);
        p = strtok(NULL, ":");
        struct stat stats;
        if(stat(joined, &stats) == 0 && stats.st_mode & S_IXUSR) {
            exec = 1;
        }
    }
    return exec;
}