#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() 
{
    int sockfd;
    struct sockaddr_in server_addr;

    // 1. Create a UDP socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) 
    {
        perror("Socket creation failed");
        return 1;
    }

    // 2. Configure the server to send message to
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // 3. Send data
    char *msg = "Hello from client!";
    if (sendto(sockfd, msg, strlen(msg), 0,(struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) 
    {
        perror("Send failed");
        close(sockfd);
        return 1;
    }

    printf("Message sent to server.\n");

    close(sockfd);
    return 0;
}
