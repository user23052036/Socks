#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <errno.h>

#define PORT 8080
#define MAX_CLIENTS 5
#define BUFFER_SIZE 1024

int main() {
    int server_sock, new_sock, client_socks[MAX_CLIENTS];
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_size;
    char buffer[BUFFER_SIZE];
    fd_set readfds;
    int max_sd, activity, i, valread;

    // Initialize all client sockets to 0
    for (i = 0; i < MAX_CLIENTS; i++)
        client_socks[i] = 0;

    // Create server socket
    server_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sock < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }
    printf("Server socket created.\n");

    // Configure server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // Bind
    if (bind(server_sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }
    printf("Binding successful.\n");

    // Listen
    if (listen(server_sock, 5) < 0) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }
    printf("Listening on port %d...\n", PORT);

    addr_size = sizeof(client_addr);

    while (1) {
        // Clear the socket set
        FD_ZERO(&readfds);

        // Add server socket to set
        FD_SET(server_sock, &readfds);
        max_sd = server_sock;

        // Add client sockets to set
        for (i = 0; i < MAX_CLIENTS; i++) {
            int sd = client_socks[i];
            if (sd > 0)
                FD_SET(sd, &readfds);
            if (sd > max_sd)
                max_sd = sd;
        }

        // Wait for activity on any socket
        activity = select(max_sd + 1, &readfds, NULL, NULL, NULL);
        if ((activity < 0) && (errno != EINTR)) {
            perror("Select error");
            continue;
        }

        // Incoming connection
        if (FD_ISSET(server_sock, &readfds)) {
            new_sock = accept(server_sock, (struct sockaddr*)&client_addr, &addr_size);
            if (new_sock < 0) {
                perror("Accept failed");
                exit(EXIT_FAILURE);
            }

            printf("New connection: socket fd %d, IP: %s, PORT: %d\n",
                   new_sock, inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

            // Add new socket to client list
            for (i = 0; i < MAX_CLIENTS; i++) {
                if (client_socks[i] == 0) {
                    client_socks[i] = new_sock;
                    printf("Added to client list at index %d\n", i);
                    break;
                }
            }
        }

        // Handle I/O from clients
        for (i = 0; i < MAX_CLIENTS; i++) {
            int sd = client_socks[i];
            if (FD_ISSET(sd, &readfds)) {
                valread = read(sd, buffer, BUFFER_SIZE);
                if (valread <= 0) {
                    // Client disconnected
                    getpeername(sd, (struct sockaddr*)&client_addr, &addr_size);
                    printf("Client disconnected: IP %s, PORT %d\n",
                           inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
                    close(sd);
                    client_socks[i] = 0;
                } else {
                    buffer[valread] = '\0';
                    printf("Message from client %d: %s", i, buffer);
                    send(sd, buffer, strlen(buffer), 0); // Echo back
                }
            }
        }
    }

    close(server_sock);
    return 0;
}
