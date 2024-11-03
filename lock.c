#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv)
{
        int fd = -1;

        (void)argv;

        struct flock fl = {
                .l_type = F_WRLCK,
                .l_whence = SEEK_SET,
                .l_start = 0,
                .l_len = 0,
        };

        if (argc > 1) {
                fl.l_type = F_RDLCK;
        }


        fd = open("lock.c", O_RDWR);

        printf("Hiting return to lock file...\n");
        getchar();
        printf("Try Locking file with %s lock\n", fl.l_type == F_WRLCK ? "WRITE" : "READ");

        fcntl(fd, F_SETLKW, &fl);

        printf("Successfully lock the file\n");

        fl.l_type = F_UNLCK;

        printf("Hitting return to unlock file...\n");
        getchar();
        printf("Try Unlocking the file...\n");

        fcntl(fd, F_SETLK, &fl);

        printf("Successfully unlock...\n");

        close(fd);

        return 0;
}
