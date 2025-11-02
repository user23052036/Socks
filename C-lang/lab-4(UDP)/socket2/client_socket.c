#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() 
{
    int client_socket;
    struct sockaddr_in server_addr;
    socklen_t addr_len = sizeof(server_addr);
    char buffer[1024];

    // Create UDP socket
    client_socket = socket(AF_INET, SOCK_DGRAM, 0);

    // Server address configuration
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);               // Send to port 8080
    server_addr.sin_addr.s_addr = inet_addr("127.0.1.3"); // Localhost  can be INADDR_ANY

    // Send message to server
    char *msg = "Hello from client";
    sendto(client_socket, msg, strlen(msg), 0,
           (struct sockaddr *)&server_addr, sizeof(server_addr));
    printf("Message sent to server.\n");

    // Receive reply from server
    int n = recvfrom(client_socket, buffer, sizeof(buffer) - 1, 0,
                     (struct sockaddr *)&server_addr, &addr_len);
    buffer[n] = '\0';
    printf("Server says: %s\n", buffer);

    close(client_socket);
    return 0;
}
