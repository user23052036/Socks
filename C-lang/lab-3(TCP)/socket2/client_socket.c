#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main() 
{
    int client_sock;
    struct sockaddr_in server_addr;
    char buffer[1024];

    // 1. Create socket
    client_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (client_sock < 0) 
    {
        perror("Client socket creation failed");
        exit(1);
    }
    printf("Client socket created successfully.\n");

    // 2. Set up server address to connect
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // 3. Connect to server
    if (connect(client_sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) 
    {
        perror("Connection to server failed");
        close(client_sock);
        exit(1);
    }
    printf("Connected to server!\n");

    // 4. Send message
    char *msg = "Hello from client!";
    write(client_sock, msg, strlen(msg));

    // 5. Receive response
    int n = read(client_sock, buffer, sizeof(buffer)-1);
    buffer[n] = '\0';
    printf("Server says: %s\n", buffer);

    // 6. Close socket
    close(client_sock);

    return 0;
}
