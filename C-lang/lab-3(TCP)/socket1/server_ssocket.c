/*
server side TCP (CONNECTION ORIENTED) socket does the following:
socket_creation -> bind -> listen -> accept -> read/send -> close
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main() 
{
    int server_socket;
    server_socket = socket(AF_INET, SOCK_STREAM, 0);

    if (server_socket < 0) 
    {
        perror("Server socket creation failed");
        exit(1);
    }

    printf("Server socket created successfully. FD = %d\n", server_socket);
    return 0;
}