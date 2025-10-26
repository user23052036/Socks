#include <stdio.h>

int main() 
{
    int num;
    printf("Enter a signed integer: ");
    scanf("%d", &num);

    printf("Byte 1: %d\n", (num & 0xFF));
    printf("Byte 2: %d\n", (num >> 8) & 0xFF);
    printf("Byte 3: %d\n", (num >> 16) & 0xFF);
    printf("Byte 4: %d\n", (num >> 24) & 0xFF);

    return 0;
}