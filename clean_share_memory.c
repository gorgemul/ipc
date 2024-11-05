#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SIZE       1024
#define FILEPATH   "share_memory.c"
#define PROJECTID  'z'

int main()
{
        key_t key = -1;
        int shm_id = -1;

        if ((key = ftok(FILEPATH, PROJECTID)) == -1) {
                perror("ftok");
                exit(1);
        }

        if ((shm_id = shmget(key, SIZE, 0)) == -1) {
                perror("shmget");
                exit(1);
        }

        if (shmctl(shm_id, IPC_RMID, NULL) == -1) {
                perror("shmctl");
                exit(1);
        }

        printf("Sucessfully remove share memory(id: %d)!\n", shm_id);

        return 0;
}
