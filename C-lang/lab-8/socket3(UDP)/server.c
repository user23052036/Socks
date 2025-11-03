#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main()
{
    int server_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len = sizeof(client_addr);

    server_socket = socket(AF_INET, SOCK_DGRAM, 0);
    if (server_socket < 0)
    {
        perror("server socket creation failed");
        exit(1);
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        perror("bind failed");
        close(server_socket);
        exit(1);
    }

    printf("Server listening on port 8080...\n");

    int mess_len;
    char message[100];

    // Receive message length first
    recvfrom(server_socket, &mess_len, sizeof(mess_len), 0,(struct sockaddr *)&client_addr, &addr_len);
    // Receive message
    recvfrom(server_socket, message, mess_len, 0,(struct sockaddr *)&client_addr, &addr_len);

    message[mess_len] = '\0'; // null-terminate the string
    printf("Received message: %s\n", message);

    // Count vowels and words
    int vowels = 0, words = 0;
    for (int i = 0; message[i] != '\0'; i++)
    {
        char c = message[i];
        if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' ||
            c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U') vowels++;

        if (c == ' ' || c == '\t' || c == '\n') words++;
    }

    // Last word (if message not empty)
    if (mess_len > 0) words++;

    // Send results back to client
    sendto(server_socket, &vowels, sizeof(vowels), 0,(struct sockaddr *)&client_addr, addr_len);
    sendto(server_socket, &words, sizeof(words), 0,(struct sockaddr *)&client_addr, addr_len);

    printf("Sent back -> vowels: %d, words: %d\n", vowels, words);

    close(server_socket);
    return 0;
}
