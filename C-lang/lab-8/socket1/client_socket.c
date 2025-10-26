#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUF_SIZE 1024

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[BUF_SIZE];
    char message[BUF_SIZE];

    // Create socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert IP
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        perror("Invalid address / Address not supported");
        close(sock);
        exit(EXIT_FAILURE);
    }

    // Connect to server
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Connection failed");
        close(sock);
        exit(EXIT_FAILURE);
    }

    printf("Connected to server! Start chatting...\n");

    while (1) {
        printf("Client: ");
        fgets(message, BUF_SIZE, stdin);
        message[strcspn(message, "\n")] = '\0'; // remove newline

        send(sock, message, strlen(message), 0);

        if (strncmp(message, "exit", 4) == 0) {
            printf("You ended the chat.\n");
            break;
        }

        memset(buffer, 0, BUF_SIZE);
        int valread = recv(sock, buffer, BUF_SIZE, 0);
        if (valread <= 0) {
            printf("Server disconnected.\n");
            break;
        }

        buffer[valread] = '\0';
        printf("Server: %s\n", buffer);

        if (strncmp(buffer, "exit", 4) == 0) {
            printf("Server ended the chat.\n");
            break;
        }
    }

    close(sock);
    return 0;
}
