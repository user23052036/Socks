#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() 
{
    int server_socket;
    struct sockaddr_in server_addr, client_addr;
    char buf[100];
    socklen_t len = sizeof(client_addr);

    server_socket = socket(AF_INET, SOCK_DGRAM, 0);
    if (server_socket < 0) { perror("socket"); exit(1); }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(9173);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) 
    {
        perror("bind");
        close(server_socket);
        exit(1);
    }

    printf("UDP Server running on port 9173...\n");

    while (1) 
    {
        int n = recvfrom(server_socket, buf, sizeof(buf), 0,
                         (struct sockaddr*)&client_addr, &len);
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

        sendto(server_socket, buf, strlen(buf), 0, (struct sockaddr*)&client_addr, len);
        printf("Received: %d %d | Sent Sum: %d\n", a, b, sum);
    }

    close(server_socket);
    return 0;
}

// sscanf() reads formatted data from a string (opposite of sprintf).
// Example: sscanf(buf, "%d %d", &a, &b); → extracts two integers from buf into a and b.
// Useful for converting received string data back into numeric values.


// recvfrom() returns the number of bytes received in 'n'.
// Example: if client sent "10 20" (5 characters), n = 5.
// Always add buf[n] = '\0'; to terminate the string safely.

