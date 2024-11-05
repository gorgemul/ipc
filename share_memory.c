#include <stdio.h>
#include <sys/ipc.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <string.h>

#define SIZE       1024
#define FILEPATH   "share_memory.c"
#define PROJECTID  'z'

int main(int argc, char **argv)
{
        int shm_id = -1;
        key_t key = -1;
        char *buf;
        (void)argv;

        if (argc > 2) {
                fprintf(stderr, "Usage: shm arg\n");
                return 1;
        }

        if ((key = ftok(FILEPATH, PROJECTID)) == -1) {
                perror("ftok");
                exit(1);
        }

        if ((shm_id = shmget(key, SIZE, 0666 | IPC_CREAT)) == -1) {
                perror("shmget");
                exit(1);
        }

        if ((buf = shmat(shm_id, (void *)0, 0)) == (void *)-1) {
                perror("shmat");
                exit(1);
        }

        if (argc == 1) {
                printf("Share memory content: %s\n", buf);
        } else {
                memcpy(buf, argv[1], SIZE);
                printf("Sucessfully writing %s into share memory\n", buf);
        }

        if (shmdt(buf) == -1) {
                perror("shmdt");
                exit(1);
        }

        printf("Detaching from share memory...\n");

        return 0;

}
