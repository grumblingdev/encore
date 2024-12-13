#include <stdio.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>

#define MKDIR_HELP_MSG "\
Usage: mkdir [OPTION]... DIRECTORY...\n\
Create directories if they don't already exist.\n\
\n\
    -m=MODE sets file mode (like chmod)\n\
    -v prints a message for every created directory"

int main(int argc, char **argv) {
    int path_index;
    unsigned int mode = S_IRWXU, verbose = 0;

    if (argc < 2) {
        fputs("mkdir: missing operand\nUse \"mkdir --help\" for more information.\n", stderr);
        return 1;
    }

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--help") == 0) {
            puts(MKDIR_HELP_MSG);                                           /* Print help message and exit */
            return 0;
        } else if (strncmp(argv[i], "-m=", 2) == 0) {
            sscanf(argv[i], "-m=%d", &mode);                                /* Mode checking */
            if (mode == 0) {
                fputs("mkdir: mode is not a valid value.\n", stderr);
                return 1;
            }

            continue;
        } else if (strcmp(argv[i], "-v") == 0) {
            verbose = 1;                                                    /* Verbosity check */
            continue;
        } else {
            path_index = i;                                                 /* Save directory path index */
        }
    }
    mkdir(argv[path_index], mode);
    if (errno != 0) {
        perror("mkdir");
        return errno;
    }
    if (verbose) {
        printf("mkdir: created directory: %s\n", argv[path_index]);
    }
    return 0;
}