#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
#include "filesystem.h"

void generateEntry(Options* o) {
    char* userpath = getenv("HOME");
    char* pathToLocal = join(2, userpath, ".local");
    createDirIfNotExists(pathToLocal);
    char* pathToShare = join(2, pathToLocal, "share");
    createDirIfNotExists(pathToShare);
    char* pathToApp = join(2, pathToShare, "applications");
    createDirIfNotExists(pathToApp);
}

int main(int argc, char *argv[]) {
    Options* options = parse(argc, argv);
    generateEntry(options);
    return 0;
}