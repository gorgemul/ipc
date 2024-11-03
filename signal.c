#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#if 0
        1. Keep printing "sleeping!" until get the signal of USR1
#endif

volatile sig_atomic_t got_usr1;

void handle_sig(int sig)
{
        (void)sig;

        got_usr1 = 1;
}

int main(void)
{
        struct sigaction sa = {
                .sa_handler = handle_sig,
                .sa_mask = 0,
                .sa_flags = 0,
        };

        if ((sigaction(SIGUSR1, &sa, NULL)) == -1) {
                perror("sigaction");
                exit(1);
        }

        while (got_usr1 != 1) {
                printf("pid(%d) sleeping: zzzzzzzzz\n", getpid());
                sleep(1);
        }

        printf("Wake up!\n");

        return 0;
}
