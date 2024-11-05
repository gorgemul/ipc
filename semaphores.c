#include <stdio.h>
#include <sys/ipc.h>
#include <stdlib.h>
#include <sys/sem.h>
#include <errno.h>
#include <unistd.h>

#define FILEPATH     "semaphores.c"
#define PROJECTID    'z'
#define NSEMS         1
#define PALCEHOLDER   0
#define MAXRETRY      10

int retry(key_t key, int nsems)
{
        int ready = 0;
        union semun arg;
        int sem_id = semget(key, nsems, 0);
        struct semid_ds buf;

        arg.buf = &buf;

        for (int i = 0; (i < MAXRETRY && !ready); i++) {
                semctl(sem_id, PALCEHOLDER, IPC_STAT, arg);
                if (arg.buf->sem_otime != 0) {
                        ready = 1;
                }
                else {
                        printf("Retry...\n");
                        sleep(1);
                }
        }

        if (!ready) {
                errno = ETIME;
                return -1;
        }

        return sem_id;
}

int init_semaphores(int sem_id, int nsems)
{
        struct sembuf sb = {
                .sem_num = 0,
                .sem_op = 1,
                .sem_flg = 0,
        };

        printf("Enter return to init semaphores...\n");
        getchar();

        for (sb.sem_num = 0; sb.sem_num < nsems; sb.sem_num++) {
                if (semop(sem_id, &sb, 1) == -1) {
                        int err = errno;
                        semctl(sem_id, PALCEHOLDER, IPC_RMID);
                        errno = err;
                        return -1;
                }
        }

        return sem_id;
}

int create_semaphores(key_t key, int nsems)
{
        int sem_id = semget(key, nsems, 0666 | IPC_CREAT | IPC_EXCL);

        if (errno == EEXIST) {
                sem_id = retry(key, nsems);
                return sem_id == -1 ? -1 : sem_id;
        }

        if (sem_id > 0) {
                sem_id = init_semaphores(sem_id, nsems);
                return sem_id == -1 ? -1 : sem_id;
        }

        return -1;
}

int main()
{
        int sem_id = -1;
        key_t key = -1;
        struct sembuf sb = {
                .sem_num = 0,
                .sem_op = -1,
                .sem_flg = SEM_UNDO,
        };

        if ((key = ftok(FILEPATH, PROJECTID)) == -1) {
                perror("ftok");
                exit(1);
        }

        if ((sem_id = create_semaphores(key, NSEMS)) == -1) {
                perror("create semaphores");
                exit(1);
        }

        printf("Enter return to lock...\n");
        getchar();
        printf("Try locking...\n");

        if (semop(sem_id, &sb, 1) == -1) {
                perror("semop");
                exit(1);
        }

        sb.sem_op = 1;
        printf("Enter return to unlock...\n");
        getchar();
        printf("Try unlocking...\n");

        if (semop(sem_id, &sb, 1) == -1) {
                perror("semop");
                exit(1);
        }

        return 0;
}
