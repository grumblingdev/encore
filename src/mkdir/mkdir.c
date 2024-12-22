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
    -m=MODE sets file mode (like chmod)\n\
    -v prints a message for every created directory\n\
    -p create parent directories if necessary"

typedef int errno_t;
errno_t mkprnt(const char *path, mode_t mode);

int main(int argc, char **argv) {
    int path_index, verbose = 0, prnt_flag = 0, ret = 0;
    mode_t mode = (S_IRWXU|S_IRWXG|S_IRWXO);

    if (argc < 2) {
        fputs("mkdir: missing operand\n\
        Use \"mkdir --help\" for more information.\n", stderr);
        
        return 1;
    }

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--help") == 0) {
            puts(MKDIR_HELP_MSG);                                           /* Print help message and exit */
            return 0;
        } else if (strncmp(argv[i], "-m=", 2) == 0) {
            sscanf(argv[i], "-m=%o", &mode);                                /* Mode checking */
            if (mode == 0) {
                fputs("mkdir: mode is not a valid value.\n", stderr);
                return 1;
            }

            continue;
        } else if (strncmp(argv[i], "-v", 2) == 0) {
            verbose = 1;                                                    /* Verbosity check */
            continue;
        } else if (strncmp(argv[i], "-p", 2) == 0) {
            prnt_flag = 1;                                                    /* Verbosity check */
            continue;
        } else {
            path_index = i;                                                 /* Save directory path index */
        }
    }
    if (prnt_flag) {
        ret = mkprnt(argv[path_index], mode);
        if (ret == -1) {
            perror("mkdir");
            return errno;
        }
    } else {
        ret = mkdir(argv[path_index], mode);
        if (ret == -1) {
            perror("mkdir");
            return errno;
        }
    }
    if (verbose) {
        printf("mkdir: created directory: %s\n", argv[path_index]);
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
    while (token = strtok(NULL, "/")) {
        if (mkdir(token, mode) == -1 && errno != EEXIST) return -1;
        chdir(token);
    }
    chdir(copy);
    free(copy);
    return 0;
}