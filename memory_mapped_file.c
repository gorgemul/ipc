#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <stdlib.h>

#define FILEPATH "foo.txt"

int main(int argc, char **argv)
{
    int fd = -1;
    int offset = -1;
    char *data;
    struct stat statbuf;

    if (argc != 2) {
        fprintf(stderr, "Usage: mmf arg\n");
        return 1;
    }

    offset = atoi(argv[1]);

    if ((fd = open(FILEPATH, O_RDONLY)) == -1) {
        perror("open");
        exit(1);
    }

    if (stat(FILEPATH, &statbuf) == -1) {
        perror("stat");
        exit(1);
    }

    if ((offset < 0) || (offset > statbuf.st_size)) {
        fprintf(stderr, "Invalid offest!\n");
        return 1;
    }

    if ((data = mmap((void *)0, statbuf.st_size, PROT_READ, MAP_SHARED, fd, 0)) == (void *)-1) {
        perror("mmap");
        exit(1);
    }

    printf("Offset %d character is %c", offset, data[offset]);

    return 0;
}
