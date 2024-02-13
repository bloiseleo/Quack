#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <linux/limits.h>
#include "freedesktop.h"
#include "filesystem.h"
#include <stdlib.h>

#define OPTIONS "n:aldv:g:c:e:hi:f:"

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
    char* filename;
} Options;

void concatInBuffer(char* buffer, size_t bufferSize, char* s) {
    buffer = realloc(buffer, sizeof(char) * (strlen(s) + bufferSize));
    strcat(buffer, s);
    return;
}

char* help() {
    char* buffer = malloc(sizeof(char) * 20);
    concatInBuffer(buffer, strlen(buffer), "quack - Create Desktop Entry Easily\n");
    concatInBuffer(buffer, strlen(buffer), "Usage: quack [options]\n\n");
    concatInBuffer(buffer, strlen(buffer), "The Desktop Entry is specified by FreeDesktop at https://specifications.freedesktop.org/desktop-entry-spec/latest/. Read to know more about it \n");
    concatInBuffer(buffer, strlen(buffer), "This is a tool created to apply these specifications above and make this process more easy to learn and apply to everything you want to.\n\n");
    concatInBuffer(buffer, strlen(buffer), "Options:\n");
    concatInBuffer(buffer, strlen(buffer), "    -n: Name of the entry. This name will appear at the search bar.(*)\n");
    concatInBuffer(buffer, strlen(buffer), "    -v: Version of the entry following the Semantic Versioning Sintax.\n");
    concatInBuffer(buffer, strlen(buffer), "    -a: Determines the Type of entry to Application (DEFAULT)\n");
    concatInBuffer(buffer, strlen(buffer), "    -l: Determines the Type of entry to Link\n");
    concatInBuffer(buffer, strlen(buffer), "    -d: Determines the Type of entry to Directory\n");
    concatInBuffer(buffer, strlen(buffer), "    -g: Determines the GenericName of entry.\n");
    concatInBuffer(buffer, strlen(buffer), "    -c: Tooltip for the entry. It will be shown if your entry is used to open other files, like \"Open HTML in Firefox\".\n");
    concatInBuffer(buffer, strlen(buffer), "    -i: Determines the absolute path to Icon to be shown in Search Bar. If relative path is provided, full absolute path is processed from it.\n");
    concatInBuffer(buffer, strlen(buffer), "    -e: Determines the absolute path to Executable File to be executed. If relative path is provided, full absolute path is processed from it. It must be informed when Application type\n");
    concatInBuffer(buffer, strlen(buffer), "    -f: Determines the name of the Desktop Entry File to be used. If none is provided, the name of application will be used\n");
    return strdup(buffer);
}

char* error(char* er) {
    char* def = "Type quack -h to get more information\n";
    char* buffer = malloc(sizeof(char) * strlen("Error: ") + 1);
    strcat(buffer, "Error: ");
    concatInBuffer(buffer, strlen(buffer), er);
    concatInBuffer(buffer, strlen(buffer), "\n");
    concatInBuffer(buffer, strlen(buffer), def);
    printf("%s", buffer);
    exit(-1);
}

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
    o->filename = NULL;
    return o;
}

void checkDestkopNameEntry() {
    if(!checkStringType(optarg, strlen(optarg))) {
        printf("%s - Desktop Entry Names must not have control characteres", optarg);
        exit(-1);
    }
}

void checkFilename() {
    if(!checkStringType(optarg, strlen(optarg))) {
        printf("%s - Desktop Entry Filename must not have control characteres", optarg);
        exit(-1);
    }
}

char* getExecutablePath()
{
    char path[PATH_MAX + 1];
    char *p = realpath(optarg, path);
    if (p == NULL) { // Not valid path, will be treated as executable in $PATH.
        if (validExecutable(optarg)) {
            return strdup(optarg);
        }
        error("Executable not valid as an absolute path neither executable from $PATH");
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
            case 'f':
                checkFilename();
                o->filename = optarg;
                break;
            default:
                printf("%s", help());
                exit(0);
                break;
        }
    }
    if (o->name == NULL) {
        error("Name must be provided to generate a Desktop Entry");
    }
    if (o->filename == NULL) {
        o->filename = o->name;
    }    
    return o;
}
