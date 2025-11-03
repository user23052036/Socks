/*
write a socket program to implement a simple calculator service using TCP socket in C. the client 
send a request with 2 numbers and an arithmatic operator(+,-,*,/) to the server. The server performs 
the specified operation and send back the result to the client. Binary arithmatic operator. 
use read and write methods.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

int main()
{
    int client_socket;
    struct sockaddr_in server_addr;
    int num1, num2;
    char op;
    int result;

    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket < 0)
    {
        perror("Socket creation failed");
        exit(1);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8081);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (connect(client_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        perror("Connection failed");
        close(client_socket);
        exit(1);
    }

    printf("Enter expression (e.g., 5 + 3): ");
    scanf("%d %c %d", &num1, &op, &num2);

    // Send variables directly
    write(client_socket, &num1, sizeof(num1));
    write(client_socket, &op, sizeof(op));
    write(client_socket, &num2, sizeof(num2));

    close(client_socket);
    return 0;
}
