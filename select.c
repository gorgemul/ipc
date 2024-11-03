#include <stdio.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

#define STDIN 0

int main(void)
{
        struct timeval tv;
        fd_set readfds;

        tv.tv_sec = 2;
        tv.tv_usec = 0;

        FD_SET(STDIN, &readfds);

        printf("Enter return plz..\n");

        select(STDIN+1, &readfds, NULL, NULL, &tv);

        if (FD_ISSET(STDIN, &readfds))
                printf("You have enter return!\n");
        else
                printf("Timeout!\n");
}
