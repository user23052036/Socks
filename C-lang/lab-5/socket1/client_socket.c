#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() 
{
    int sockfd, n, arr[100];
    struct sockaddr_in servaddr;
    socklen_t len = sizeof(servaddr);

    // Create UDP socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) 
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

    // Send data
    sendto(sockfd, &n, sizeof(n), 0, (struct sockaddr*)&servaddr, len);
    sendto(sockfd, arr, sizeof(int) * n, 0, (struct sockaddr*)&servaddr, len);

    // Receive sorted array
    recvfrom(sockfd, arr, sizeof(int) * n, 0, (struct sockaddr*)&servaddr, &len);

    printf("Sorted array from server: ");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");

    close(sockfd);
    return 0;
}
