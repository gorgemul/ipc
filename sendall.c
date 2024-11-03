#include <sys/socket.h>

int send_all(int sockfd, char *text, int *len)
{
        int sent = 0;
        int left = *len;
        int status = 0;

        while (sent < *len) {
                int bytes = send(sockfd, text+sent, left, 0);
                if (bytes == -1) {
                        status = -1;
                        break;
                }

                sent += bytes;
                left -= bytes;
        }

        *len = sent;

        return status == 0 ? 1 : 0;
}
