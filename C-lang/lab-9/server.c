#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

int main()
{
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_size;
    int num1, num2;
    char op;
    int result;

    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0)
    {
        perror("Socket creation failed");
        exit(1);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8081);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        perror("Bind failed");
        close(server_socket);
        exit(1);
    }

    if (listen(server_socket, 1) < 0)
    {
        perror("Listen failed");
        close(server_socket);
        exit(1);
    }

    printf("Server listening on port 8080...\n");

    addr_size = sizeof(client_addr);
    client_socket = accept(server_socket, NULL,NULL);
    if (client_socket < 0)
    {
        perror("Accept failed");
        close(server_socket);
        exit(1);
    }

    // Read the operator and operands directly
    read(client_socket, &num1, sizeof(num1));
    read(client_socket, &op, sizeof(op));
    read(client_socket, &num2, sizeof(num2));

    printf("Received: %d %c %d\n", num1, op, num2);

    // Perform the operation
    switch (op)
    {
    case '+': result = num1 + num2; break;
    case '-': result = num1 - num2; break;
    case '*': result = num1 * num2; break;
    case '/':
        if (num2 == 0)
        {
            printf("Division by zero!\n");
            close(client_socket);
            close(server_socket);
            return 0;
        }
        result = (float)num1 / num2;
        break;
    default:
        printf("Invalid operator received.\n");
        close(client_socket);
        close(server_socket);
        return 0;
    }
    printf("Result : %d\n", result);

    close(client_socket);
    close(server_socket);
    return 0;
}
