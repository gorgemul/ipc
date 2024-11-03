#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define PATH "/kira/dev/foo"
#define LINELEN 100

struct WBuf {
	long mtype;
	char mtext[LINELEN];
};

int main(void)
{
        struct WBuf wb;
	key_t key = ftok(PATH, 'z');

	int mqid = msgget(key, IPC_CREAT | 0666);

	printf("Successfully create message queue: %d\n", mqid);

	printf("Input message push to message queue: \n");

        wb.mtype = 1;

	while (fgets(wb.mtext, LINELEN, stdin) != NULL) {
                wb.mtext[LINELEN-1] = '\0';

		if (msgsnd(mqid, &wb, sizeof(wb.mtext), 0) == -1) {
			perror("msgsnd");
			exit(1);
		}

		printf("Sending msg: %s", wb.mtext);
	}

	if (msgctl(mqid, IPC_RMID, NULL) == -1) {
		perror("msgctl");
		exit(1);
	}

	printf("Successfully destruct message queue!\n");

	return 0;
}
