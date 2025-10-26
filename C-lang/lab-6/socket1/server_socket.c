#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080

int main() {
    int server_sock, client_sock;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_size;
    int num1, num2, sum;

    // Create socket
    server_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sock < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }
    printf("Server socket created successfully.\n");

    // Set up server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // Bind socket
    if (bind(server_sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Binding failed");
        close(server_sock);
        exit(EXIT_FAILURE);
    }
    printf("Binding successful.\n");

    // Listen for connections
    if (listen(server_sock, 5) < 0) {
        perror("Listen failed");
        close(server_sock);
        exit(EXIT_FAILURE);
    }
    printf("Server listening on port %d...\n", PORT);

    addr_size = sizeof(client_addr);
    client_sock = accept(server_sock, (struct sockaddr*)&client_addr, &addr_size);
    if (client_sock < 0) {
        perror("Accept failed");
        close(server_sock);
        exit(EXIT_FAILURE);
    }
    printf("Client connected.\n");

    // Receive two numbers from client
    if (recv(client_sock, &num1, sizeof(num1), 0) <= 0 ||
        recv(client_sock, &num2, sizeof(num2), 0) <= 0) {
        perror("Receive failed");
        close(client_sock);
        close(server_sock);
        exit(EXIT_FAILURE);
    }
    printf("Received numbers from client: %d and %d\n", num1, num2);

    // Calculate sum
    sum = num1 + num2;
    printf("Sending sum: %d\n", sum);

    // Send sum to client
    if (send(client_sock, &sum, sizeof(sum), 0) < 0) {
        perror("Send failed");
    }

    // Close sockets
    close(client_sock);
    close(server_sock);
    return 0;
}
