#include <stdio.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>
#include <libgen.h>
#include <sys/types.h>
<<<<<<< HEAD
#include <time.h>
=======
>>>>>>> 64e1b77265cb2ffaa81c500a30a0a25492c46fb3
#include <unistd.h>
#include <stdlib.h>
#include <bits/posix1_lim.h>

#define MKDIR_HELP_MSG "\
Usage: mkdir [OPTION]... DIRECTORY...\n\
Create directories if they don't already exist.\n\
\n\
<<<<<<< HEAD
    -m MODE sets file mode (like chmod)\n\
    -v prints a message for every created directory\n\
    -p create parent directories if necessary"

#define MKDIR_MISSING "\
mkdir: missing operand\n\
Use \"mkdir -h\" for more information.\n"

#define DEFAULT_MODE (S_IRWXU|S_IRWXG|S_IRWXO)
typedef int errno_t;
static errno_t gd_mkdir(const char *path, const mode_t mode, const int p_flag);
=======
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
>>>>>>> 64e1b77265cb2ffaa81c500a30a0a25492c46fb3

int main(int argc, char **argv){
    int i, p_flag = 0;
    mode_t mode = DEFAULT_MODE;

    if (argc<2){ fputs("mkdir: missing operand\n\
    Use \"mkdir -h\" for more information.", stderr); return 1; }
    
    while((i=getopt(argc, argv, "m:ph"))!=-1){
        switch (i){
            case 'h':
                puts(MKDIR_HELP_MSG);
                return 0;
            case 'm':
                sscanf(optarg, "%o", &mode);
                break;
            case 'p':
                p_flag = 1;
                break;
            case '?':
                return 1;
<<<<<<< HEAD
        }
    }
    char **p = argv+optind;
    if(*p==NULL){ fputs(MKDIR_MISSING, stderr); return 1; }

    for(;*p;p++)
        if(gd_mkdir(*p, mode, p_flag) == 1){ fprintf(stderr, "mkdir: unable to create directory \"%s\"\n", *p); return errno; }
    return 0;
}

static errno_t gd_mkdir(const char *path, const mode_t mode, const int p_flag){
    if(strcmp(path, "/")==0) { errno=EEXIST; return -1; }
    char *original = getcwd(NULL, 0);
    if(path[0]=='/') chdir("/");
    if(p_flag){
        char *path_copy = strdup(path);
        char *t;
        for(t=strtok(path_copy, "/"); t; t=strtok(NULL, "/")){
            if(mkdir(t, DEFAULT_MODE)!=0 && errno!=EEXIST) { free(path_copy); return 1; }
            chdir(t);
        }
        free(path_copy);
    }else if(mkdir(path, mode)==-1) return 1;
    chdir(original);
    if (chmod(path, mode)!=0) { free(original); return 1; }
    free(original);
    return 0;
}
=======
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
>>>>>>> 64e1b77265cb2ffaa81c500a30a0a25492c46fb3
