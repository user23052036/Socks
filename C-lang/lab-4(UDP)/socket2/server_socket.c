#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() 
{
    int sockfd;
    char buffer[1024];
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len = sizeof(client_addr);

    // Create UDP socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    // Server address configuration
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);  // Listen on port 8080
    server_addr.sin_addr.s_addr = INADDR_ANY; // Accept from any IP on this machine

    // Bind socket to the address & port
    bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    printf("UDP Server listening on port 8080...\n");

    // Receive message from client
    int n = recvfrom(sockfd, buffer, sizeof(buffer) - 1, 0,
                     (struct sockaddr *)&client_addr, &addr_len);
    buffer[n] = '\0';
    printf("Client says: %s\n", buffer);

    // Reply to client
    char *reply = "Hello from server";
    sendto(sockfd, reply, strlen(reply), 0,
           (struct sockaddr *)&client_addr, addr_len);
    printf("Reply sent to client.\n");

    close(sockfd);
    return 0;
}
