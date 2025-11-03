#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main() {
    int client_socket;
    struct sockaddr_in server_addr;
    socklen_t addr_len = sizeof(server_addr);

    // 1. Create TCP socket
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket < 0) {
        perror("Client socket creation failed");
        exit(1);
    }

    // 2. Fill server address structure
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");  // loopback address

    // 3. Connect to the server
    if (connect(client_socket, (struct sockaddr*)&server_addr, addr_len) < 0) {
        perror("Connection failed");
        exit(1);
    }

    // 4. Prepare the message
    char *message = "Hi How many vowels do i have";
    int mess_len = strlen(message);

    // 5. Send the length and message to server
    write(client_socket, &mess_len, sizeof(mess_len));
    write(client_socket, message, mess_len);

    // 6. Receive the results
    int vowels = 0, words = 0;
    read(client_socket, &vowels, sizeof(vowels));
    read(client_socket, &words, sizeof(words));

    // 7. Display output
    printf("Message: \"%s\"\n", message);
    printf("Vowels = %d, Words = %d\n", vowels, words);

    // 8. Close the socket
    close(client_socket);
    return 0;
}
