#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

#define FIFO_PATH "foobar"
#define LEN 100

int main(void)
{
        int fd = -1;
        int bytes = -1;
        char buf[LEN];

        mknod(FIFO_PATH, S_IFIFO | 0666, 0);

        printf("Waiting for a reader...\n");
        fd = open(FIFO_PATH, O_RDONLY);
        printf("Getting a reader...\n");

        do {
                bytes = read(fd, buf, LEN);
                buf[bytes] = '\0';
                printf("Receiving %d bytes msg: %s", bytes, buf);
        } while (bytes > 0);

        printf("all writer has gone!\n");

        return 0;
}
