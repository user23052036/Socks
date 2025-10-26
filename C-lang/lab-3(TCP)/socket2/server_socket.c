#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main() 
{
    int server_sock, client_sock;
    struct sockaddr_in server_addr;
    char buffer[1024];

    // 1. Create socket
    server_sock = socket(AF_INET, SOCK_STREAM, 0); // TCP
    if (server_sock < 0) 
    {
        perror("Server socket creation failed");
        exit(1);
    }
    printf("Server socket created successfully.\n");

    // 2. Set up server address
    memset(&server_addr, 0, sizeof(server_addr)); // clears the garbage value
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    server_addr.sin_addr.s_addr = INADDR_ANY; // 0.0.0.0, listens on all interfaces

    // 3. Bind socket to IP & port
    if (bind(server_sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) 
    {
        perror("Server bind failed");
        close(server_sock);
        exit(1);
    }
    printf("Server bind successful on port 8080\n");

    // 4. Listen for connections
    if (listen(server_sock, 5) < 0) 
    {
        perror("Listen failed");
        close(server_sock);
        exit(1);
    }
    printf("Server listening...\n");

    // 5. Accept a client
    client_sock = accept(server_sock, NULL, NULL);
    if (client_sock < 0) 
    {
        perror("Accept failed");
        close(server_sock);
        exit(1);
    }
    printf("Client connected!\n");

    // 6. Receive message from client
    int n = read(client_sock, buffer, sizeof(buffer)-1);
    buffer[n] = '\0';
    printf("Client says: %s\n", buffer);

    // 7. Send response
    char *msg = "Hello from server!";
    write(client_sock, msg, strlen(msg));

    // 8. Close sockets
    close(client_sock);
    close(server_sock);

    return 0;
}
