#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() 
{
    int client_socket, n, arr[100];
    struct sockaddr_in servaddr;
    socklen_t len = sizeof(servaddr);

    // Create UDP socket
    client_socket = socket(AF_INET, SOCK_DGRAM, 0);
    if (client_socket < 0) 
    {
        perror("Socket creation failed");
        exit(1);
    }

    // Server details
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(9173);
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Input
    printf("Enter number of elements: ");
    scanf("%d", &n);

    printf("Enter %d elements: ", n);
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    // Send data individually
    //first sending the length of array
    sendto(client_socket, &n, sizeof(n), 0, (struct sockaddr*)&servaddr, len);
    //then sending the array
    sendto(client_socket, arr, sizeof(int) * n, 0, (struct sockaddr*)&servaddr, len);

    // Receive sorted array
    recvfrom(client_socket, arr, sizeof(int) * n, 0, (struct sockaddr*)&servaddr, &len);

    printf("Sorted array from server: ");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");

    close(client_socket);
    return 0;
}
