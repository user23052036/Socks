#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() 
{
    int sock;
    struct sockaddr_in server;
    char buf[100];
    socklen_t len = sizeof(server);

    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) { perror("socket"); exit(1); }

    server.sin_family = AF_INET;
    server.sin_port = htons(9173);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    while (1) 
    {
        int a, b;
        printf("\nEnter two numbers (-1 -1 to quit): ");
        scanf("%d %d", &a, &b);

        sprintf(buf, "%d %d", a, b);
        sendto(sock, buf, strlen(buf), 0, (struct sockaddr*)&server, len);

        if (a == -1 && b == -1) {
            printf("Exiting client...\n");
            break;
        }

        int n = recvfrom(sock, buf, sizeof(buf), 0, NULL, NULL);
        buf[n] = '\0';

        printf("Sum from server: %s\n", buf);
    }

    close(sock);
    return 0;
}
