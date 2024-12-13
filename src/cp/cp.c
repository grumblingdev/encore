#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

void main(int argc, char **argv) {
    if (argc < 3) {
        fputs("cp: missing file operand/s.\n", stderr);
        exit(EXIT_FAILURE);
    }

    FILE *src_fp;                                       /* File to copy contents of */
    src_fp = fopen(argv[1], "rb");
    if (!src_fp) {
        perror("fopen");
        exit(errno);
    }

    FILE *dest_fp;                                      /* File to write contents to */
    dest_fp = fopen(argv[2], "wb");
    if (!dest_fp) {
        perror("fopen");
        exit(errno);
    }

    char c;                                             /* Indiviual byte */
    for (; c = fgetc(src_fp); fputc(c, dest_fp))
        if (c == EOF)
            break;

    exit(EXIT_SUCCESS);
}