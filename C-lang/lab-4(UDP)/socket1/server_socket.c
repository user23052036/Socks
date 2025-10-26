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

    // 1. Create a UDP socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) 
    {
        perror("Socket creation failed");
        return 1;
    }

    // 2. Configure server address
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // 3. Bind server socket to port 8080 so it can receive data
    if (bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) 
    {
        perror("Bind failed");
        close(sockfd);
        return 1;
    }

    printf("UDP Server listening on port 8080...\n");

    // 4. Receive data from client
    int n = recvfrom(sockfd, buffer, sizeof(buffer) - 1, 0,
                     (struct sockaddr *)&client_addr, &addr_len);
    if (n < 0) 
    {
        perror("Receive failed");
        close(sockfd);
        return 1;
    }

    buffer[n] = '\0';
    printf("Client says: %s\n", buffer);

    close(sockfd);
    return 0;
}
