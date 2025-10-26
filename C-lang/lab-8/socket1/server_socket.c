#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUF_SIZE 1024

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    socklen_t addrlen = sizeof(address);
    char buffer[BUF_SIZE];
    char message[BUF_SIZE];

    // Create socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }

    // Prepare address
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Bind
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Listen
    if (listen(server_fd, 3) < 0) {
        perror("Listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d...\n", PORT);

    // Accept client connection
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, &addrlen)) < 0) {
        perror("Accept failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Client connected! Start chatting...\n");

    while (1) {
        memset(buffer, 0, BUF_SIZE);
        int valread = recv(new_socket, buffer, BUF_SIZE, 0);
        if (valread <= 0) {
            printf("Client disconnected.\n");
            break;
        }

        buffer[valread] = '\0';
        printf("Client: %s\n", buffer);

        if (strncmp(buffer, "exit", 4) == 0) {
            printf("Client ended the chat.\n");
            break;
        }

        printf("Server: ");
        fgets(message, BUF_SIZE, stdin);
        message[strcspn(message, "\n")] = '\0'; // remove newline

        send(new_socket, message, strlen(message), 0);

        if (strncmp(message, "exit", 4) == 0) {
            printf("Server ended the chat.\n");
            break;
        }
    }

    close(new_socket);
    close(server_fd);
    return 0;
}
