// server_select.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/select.h>
#define PORT 8080
#define BUF_SIZE 1024

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[BUF_SIZE];
    fd_set readfds;
    struct timeval timeout;
    int max_sd, activity;

    // Create socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Bind
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Listen
    if (listen(server_fd, 3) < 0) {
        perror("listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d...\n", PORT);

    while (1) {
        // Clear and set file descriptors
        FD_ZERO(&readfds);
        FD_SET(server_fd, &readfds);    // For new client connections
        FD_SET(STDIN_FILENO, &readfds); // For keyboard input
        max_sd = server_fd;

        // Timeout of 10 seconds
        timeout.tv_sec = 10;
        timeout.tv_usec = 0;

        printf("Waiting for client or keyboard input (10s timeout)...\n");
        activity = select(max_sd + 1, &readfds, NULL, NULL, &timeout);

        if (activity < 0) {
            perror("select error");
            continue;
        } else if (activity == 0) {
            printf("Timeout! No activity.\n");
            continue;
        }

        // Check for new client connection
        if (FD_ISSET(server_fd, &readfds)) {
            new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen);
            if (new_socket < 0) {
                perror("accept failed");
                continue;
            }
            printf("New client connected!\n");

            int valread = read(new_socket, buffer, BUF_SIZE - 1);
            if (valread > 0) {
                buffer[valread] = '\0';
                printf("Client: %s\n", buffer);
                send(new_socket, "Hello from server", strlen("Hello from server"), 0);
            }
            close(new_socket);
        }

        // Check for keyboard input
        if (FD_ISSET(STDIN_FILENO, &readfds)) {
            if (fgets(buffer, BUF_SIZE, stdin) != NULL) {
                buffer[strcspn(buffer, "\n")] = '\0'; // Remove newline
                printf("You typed: %s\n", buffer);
            }
        }
    }

    close(server_fd);
    return 0;
}
