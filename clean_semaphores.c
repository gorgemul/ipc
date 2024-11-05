#include <stdio.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdlib.h>

#define FILEPATH     "semaphores.c"
#define PROJECTID    'z'
#define NSEMS         1
#define PALCEHOLDER   0
#define MAXRETRY      10


int main(void)
{
        key_t key = ftok(FILEPATH, PROJECTID);

        int sem_id;

        if ((sem_id = semget(key, NSEMS, 0)) == -1) {
                perror("semget");
                exit(1);
        }

        if (semctl(sem_id, PALCEHOLDER, IPC_RMID) == -1) {
                perror("semctl");
                exit(1);
        }

        printf("Succesfully remove semaphoe set %d\n", sem_id);

        return 0;
}
