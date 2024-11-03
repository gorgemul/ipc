#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

#define FIFO_PATH "foobar"
#define LEN 100

int main(void)
{
        int fd = -1;
        int num;
        char s[LEN];
        mknod(FIFO_PATH, S_IFIFO | 0666, 0);

        printf("Waiting for a writer...\n");
        fd = open(FIFO_PATH, O_WRONLY);
        printf("Having a writer...\n");

        while(fgets(s, LEN, stdin) != NULL) {
                if ((num = write(fd, s, sizeof(s))) == -1) {
                        perror("write");
                } else {
                        printf("Writing %s(%d bytes) into FIFO\n", s, num);
                }
        }
}
