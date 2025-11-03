#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<sys/socket.h>

int main()
{
    // writting tcp client side socket
    
    int client_socket;
    struct sockaddr_in server_addr;

    client_socket = socket(AF_INET,SOCK_STREAM,0);

    memset(&server_addr,0,sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); //using LOOPBACK

    connect(client_socket,(struct sockaddr*)&server_addr,sizeof(server_addr));

    char *message = "how many vowels are their in this sentence";
    int mess_len = strlen(message);

    write(client_socket,message,mess_len);

    int vowels=0,words=0;
    read(client_socket,&vowels,sizeof(vowels));
    read(client_socket,&words,sizeof(words));

    printf("no of vowels and words are %d and %d respectively",vowels,words);
    close(client_socket);
    return 0;
}