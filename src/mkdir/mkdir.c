#include <stdio.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>
#include <libgen.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <bits/posix1_lim.h>

#define MKDIR_HELP_MSG "\
Usage: mkdir [OPTION]... DIRECTORY...\n\
Create directories if they don't already exist.\n\
\n\
    -m MODE sets file mode (like chmod)\n\
    -v prints a message for every created directory\n\
    -p create parent directories if necessary"

#define MKDIR_MISSING "\
mkdir: missing operand\n\
Use \"mkdir -h\" for more information.\n"

#define MKDIR_INV_OPT "\
mkdir: invalid option -- \"%c\"\n"
typedef int errno_t;
errno_t mkprnt(const char *path, mode_t mode);

int main(int argc, char **argv) {
    int i, v_flag, p_flag;
    mode_t mode = (S_IRWXU|S_IRWXG|S_IRWXO);

    if (argc < 2) {
        fputs("mkdir: missing operand\n\
        Use \"mkdir -h\" for more information.\n", stderr);
        
        return 1;
    }
    
    while ((i = getopt(argc, argv, "m:vph") != -1)) {
        switch (i) {
            case 'h':
                puts(MKDIR_HELP_MSG);
                return 0;
            case 'm':
                sscanf(optarg, "%o", &mode);
                break;
            case 'v':
                v_flag = 1;
                break;
            case 'p':
                p_flag = 1;
                break;
            case '?':
                fprintf(stderr, MKDIR_INV_OPT, optopt);
        }
    }


    return 0;
}

errno_t mkprnt(const char *path, mode_t mode) { /* TO IMPROVE */
    char *token;
    char *copy = strdup(path);
    strcpy(copy, path);

    if (!strcmp(copy, "/")) {
        errno = EEXIST;
        return -1;
    } else if (copy[0] == '/' && strcmp(copy, "/"))
        chdir("/");
    
    token = strtok(copy, "/");
    if (mkdir(token, mode) == -1 && errno != EEXIST) return -1;

    chdir(token);
    while ((token = strtok(NULL, "/"))) {
        if (mkdir(token, mode) == -1 && errno != EEXIST) return -1;
        chdir(token);
    }
    chdir(copy);
    free(copy);
    return 0;
}