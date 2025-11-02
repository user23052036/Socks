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
    int server_socket, arr[100], n, i, j;
    struct sockaddr_in server_addr, client_addr;
    socklen_t len = sizeof(client_addr);

    // Create UDP socket
    server_socket = socket(AF_INET, SOCK_DGRAM, 0);

    // Configure server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(9173);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // Bind the socket
    bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr));

    // Receive number of elements
    recvfrom(server_socket, &n, sizeof(n), 0, (struct sockaddr*)&client_addr, &len);
    // Receive array
    recvfrom(server_socket, arr, sizeof(int)*n, 0, (struct sockaddr*)&client_addr, &len);

    // Bubble sort
    for (i = 0; i < n-1; i++) 
    {
        for (j = 0; j < n-i-1; j++) 
        {
            if (arr[j] > arr[j+1]) 
                swap(&arr[j], &arr[j+1]); // Corrected!
        }
    }

    // Send sorted array back
    sendto(server_socket, arr, sizeof(int) * n, 0, (struct sockaddr*)&client_addr, len);

    close(server_socket);
    return 0;
}
