#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() 
{
    int client_socket;
    struct sockaddr_in server_addr;
    char buf[100];
    socklen_t len = sizeof(server_addr);

    client_socket = socket(AF_INET, SOCK_DGRAM, 0);
    if (client_socket < 0) { perror("socket"); exit(1); }

    memset(&server_addr,0,sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(9173);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    while (1) 
    {
        int a, b;
        printf("\nEnter two numbers (-1 -1 to quit): ");
        scanf("%d %d", &a, &b);

        sprintf(buf, "%d %d", a, b);
        sendto(client_socket, buf, strlen(buf), 0, (struct sockaddr*)&server_addr, len);

        if (a == -1 && b == -1) {
            printf("Exiting client...\n");
            break;
        }

        int n = recvfrom(client_socket, buf, sizeof(buf), 0,(struct sockaddr*)&server_addr,&len);
        buf[n] = '\0';

        printf("Sum from server: %s\n", buf);
    }

    close(client_socket);
    return 0;
}

// sprintf() formats data and stores it into a string buffer (like printf but writes to a variable).
// Syntax: sprintf(buffer, "format", values);
// Example: sprintf(buf, "%d %d", a, b);  → converts integers a and b into a single string "a b".
// Useful for preparing data to send or display later.

