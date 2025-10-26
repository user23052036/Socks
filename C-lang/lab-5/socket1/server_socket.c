#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>

void swap(int *a, int *b) 
{
    int t = *a;
    *a = *b;
    *b = t;
}

int main() 
{
    int sock, arr[100], n, i, j;
    struct sockaddr_in server, client;
    socklen_t len = sizeof(client);

    // Create UDP socket
    sock = socket(AF_INET, SOCK_DGRAM, 0);

    // Configure server address
    server.sin_family = AF_INET;
    server.sin_port = htons(9173);
    server.sin_addr.s_addr = INADDR_ANY;

    // Bind the socket
    bind(sock, (struct sockaddr*)&server, sizeof(server));

    // Receive number of elements
    recvfrom(sock, &n, sizeof(n), 0, (struct sockaddr*)&client, &len);

    // Receive array
    recvfrom(sock, arr, sizeof(int) * n, 0, (struct sockaddr*)&client, &len);

    // Bubble sort
    for (i = 0; i < n - 1; i++) 
    {
        for (j = 0; j < n - i - 1; j++) 
        {
            if (arr[j] > arr[j + 1]) 
            {
                swap(&arr[j], &arr[j + 1]); // Corrected!
            }
        }
    }

    // Send sorted array back
    sendto(sock, arr, sizeof(int) * n, 0, (struct sockaddr*)&client, len);

    close(sock);
    return 0;
}
