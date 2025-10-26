/*
client side TCP (CONNECTION ORIENTED) socket does the following:
socket_creation -> connect -> read/send -> close
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main() 
{
    int client_socket;
    client_socket = socket(AF_INET, SOCK_STREAM, 0);

    if (client_socket < 0) 
    {
        perror("Client socket creation failed");
        exit(1);
    }

    printf("Client socket created successfully. FD = %d\n", client_socket);
    return 0;
}