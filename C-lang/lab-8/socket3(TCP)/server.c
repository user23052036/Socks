#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<sys/socket.h>

int main()
{
    // writting tcp server side socket
    
    int server_socket,client_socket;
    struct sockaddr_in server_addr;

    server_socket = socket(AF_INET,SOCK_STREAM,0);

    memset(&server_addr,0,sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); //using LOOPBACK
    bind(server_socket,(struct sockaddr*)&server_addr,sizeof(server_addr));

    //listen for incoming connections
    listen(server_socket,1);
    client_socket = accept(server_socket,NULL,NULL);

    //length of message recive in mess_len variable
    int mess_len=0;
    read(client_socket,&mess_len,sizeof(mess_len));
    //now read the actual message
    char message[mess_len+1];
    read(client_socket,message,sizeof(message)-1);
    message[mess_len]='\0'; //null terminating the string

    int vowels=0,words=0;
    // main server side logic

    for(int i=0; i<mess_len; i++)
    {
        char ch = message[i];
        if(ch=='a'||ch=='e'||ch=='i'||ch=='o'||ch=='u') vowels++;
        if(ch=='\n'||ch=='\t'||ch==' ') words++;
    }
    words++;

    
    write(client_socket,&vowels,sizeof(vowels));
    write(client_socket,&words,sizeof(words));
    
    close(client_socket);
    close(server_socket);
    return 0;
}