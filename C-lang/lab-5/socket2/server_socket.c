#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() 
{
    int sock;
    struct sockaddr_in server, client;
    char buf[100];
    socklen_t len = sizeof(client);

    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) { perror("socket"); exit(1); }

    server.sin_family = AF_INET;
    server.sin_port = htons(9173);
    server.sin_addr.s_addr = INADDR_ANY;

    if (bind(sock, (struct sockaddr*)&server, sizeof(server)) < 0) 
    {
        perror("bind");
        close(sock);
        exit(1);
    }

    printf("UDP Server running on port 9173...\n");

    while (1) 
    {
        int n = recvfrom(sock, buf, sizeof(buf), 0,
                         (struct sockaddr*)&client, &len);
        buf[n] = '\0';

        int a, b;
        sscanf(buf, "%d %d", &a, &b);

        if (a == -1 && b == -1) 
        {
            printf("Server shutting down...\n");
            break;
        }

        int sum = a + b;
        sprintf(buf, "%d", sum);

        sendto(sock, buf, strlen(buf), 0, (struct sockaddr*)&client, len);

        printf("Received: %d %d | Sent Sum: %d\n", a, b, sum);
    }

    close(sock);
    return 0;
}
