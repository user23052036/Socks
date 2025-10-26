#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define SERVER_IP "127.0.0.1"

int main() {
    int client_sock;
    struct sockaddr_in server_addr;
    int num1, num2, sum;

    // Create socket
    client_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (client_sock < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }
    printf("Client socket created successfully.\n");

    // Set up server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);

    // Connect to server
    if (connect(client_sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connection failed");
        close(client_sock);
        exit(EXIT_FAILURE);
    }
    printf("Connected to server.\n");

    // Input two numbers
    printf("Enter first number: ");
    scanf("%d", &num1);
    printf("Enter second number: ");
    scanf("%d", &num2);

    // Send numbers to server
    if (send(client_sock, &num1, sizeof(num1), 0) < 0 ||
        send(client_sock, &num2, sizeof(num2), 0) < 0) {
        perror("Send failed");
        close(client_sock);
        exit(EXIT_FAILURE);
    }

    // Receive sum from server
    if (recv(client_sock, &sum, sizeof(sum), 0) <= 0) {
        perror("Receive failed");
    } else {
        printf("Sum received from server: %d\n", sum);
    }

    // Close socket
    close(client_sock);
    return 0;
}
