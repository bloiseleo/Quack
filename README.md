<h1 align="center">Quack 🦆</h1>

Creating desktops entrys in Ubuntu Linux always was something very boring for me. So, I've automated this process with this binary CLI application.

## Goals
The main goal is provide a CLI-way to create a Desktop Entry in Linux Distros and learn more about C in the way. 

The references used for this project are located at the end of the file.

## Options

| Option | Required | Format | Information |
|--------| -------- | ------ | ----------- |
| *n* | YES | String | Determines the name of the application to be displayed and looked for. If it has more than one word, it must be escaped with double-quotes |
| *a* | NO | Flag | Determines the Type of the application to be APPLICATION |
| *l* | NO | Flag | Determines the Type of the application to be LINK |
| *d* | NO | Flag | Determines the Type of the application to be DIRECTORY |
| *g* | NO | String | Determines the GenericName of the entry. |
| *c* | NO | String | Determines the Comment of the entry. |
| *e* | NO | String | Determines the path to the executable of the entry. If it's not absolute, the binary will try to solve it from the current directory. If it does not found any valid path, it will be treated as an executable directly from $PATH |
| *h* | NO | Flag | Shows the help menu |
| *i* | NO | String | Determines the path to the icon of the entry. If it's not absolute, the binary will try to solve it from the current directory. If it does not found any valid path, it will throw an Error |
| *f* | NO | String | Determines the filename to the desktop entry. Its default value is the same value of *n* |
| *v* | NO | String | Determines the version to the desktop entry. It must follow the convention defined in the reference below. |


### Examples

In order to create a Desktop Entry to an executable binary, you can create it in two ways:
- The executable is located in $PATH and you can call it from your terminal emulator.
- The executable is a binary or .AppImage and you can execute it.

So, the command would be something like that:

```
quack -n "Application Name" -i path_to_icon -e executable -a 
```

The `-n` option determines the name of the application. The `-i` option determines the path to the icon. It can be relative to the folder running or absolute. If it's not found, an error will be shown. The `-e`define the path to the executable. The `-a` option determines that this entry is an entry of type Application.

This command will create an entry in $USER/.local/share/applications and, if this path does not exists, it will be automatically created.

### References

This sections contains all the documents that I've used as reference to learn more about CLI applications and Desktop Entrys itself.

- [Command Line Interface Guidelines](https://clig.dev/#foreword)
- [Semantic Versioning](https://semver.org/)
- [Desktop Entry Specification](https://specifications.freedesktop.org/desktop-entry-spec/latest/index.html)
