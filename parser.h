#include "freedesktop.h"

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

Options* parse(int c, char *v[]);

char* error(char* er);