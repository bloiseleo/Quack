/**
 * All kinds of DesktopEntry
*/
enum DesktopEntryTypes {
    APPLICATION,
    LINK,
    DIRECTORY
};
/**
 * Checks if a given string fullfills the regex ^[A-z0-9-_]$
*/
int validConventionValueFormat(char* value);
/**
 * Check if a given string follows the pattern defined by Semantic Versioning.
 * Examples: 1.2.3, 0.0.1, etc...
*/
int checkVersionSyntax(char* s);
/**
 * Values of type string may contain all ASCII characters except for control characters. 
*/
int checkStringType(char* s, int size);