#include <sys/msg.h>
#include <sys/ipc.h>
#include <stdio.h>
#include <stdlib.h>

#define PATH "/kira/dev/foo"
#define LINELEN 100

struct WBuf {
	long mtype;
	char mtext[LINELEN];
};

int main(void)
{
	key_t key = ftok(PATH, 'z');
	int bytes = -1;
	struct WBuf wb;

	int mqid = msgget(key, 0666);

        printf("Waiting for message...\n");

	while (1) {
		if ((bytes = msgrcv(mqid, &wb, LINELEN, 0, 0)) == -1) {
			perror("msgrcv");
			exit(1);
		}

		printf("Receiving message: %s", wb.mtext);
	}

	return 0;
}
