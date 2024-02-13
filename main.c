#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
#include <string.h>
#include "filesystem.h"

char* generateFolderInLocal() {
    char* userpath = getenv("HOME");
    char* pathToLocal = join(2, userpath, ".local");
    createDirIfNotExists(pathToLocal);
    char* pathToShare = join(2, pathToLocal, "share");
    createDirIfNotExists(pathToShare);
    char* pathToApp = join(2, pathToShare, "applications");
    createDirIfNotExists(pathToApp);
    return pathToApp;
}

void generateEntry(Options* o) {
    char* path = generateFolderInLocal();
    char* pathToDesktopEntry = join(2, path, o->filename);
    char buff[strlen(pathToDesktopEntry) + 7];
    sprintf(buff, "%s.desktop", pathToDesktopEntry);
    FILE* fp = fopen(buff, "w");
    fprintf(fp, "[Desktop Entry]\n");
    fprintf(fp, "Type=%s\n", entryTypeToStr(o->kind));
    fprintf(fp, "Name=%s\n", o->name);
    if (o->executable != NULL) {
        fprintf(fp, "Exec=%s", o->executable);
    }
    
    fclose(fp);
}

int main(int argc, char *argv[]) {
    Options* options = parse(argc, argv);
    generateEntry(options);
    return 0;
}