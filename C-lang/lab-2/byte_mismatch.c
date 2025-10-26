#include <stdio.h>

int main() 
{
    unsigned int num;
    int attempts = 0;

    while (1) 
    {
        printf("Enter an unsigned integer: ");
        scanf("%u", &num);
        attempts++;

        unsigned char firstByte = num & 0xFF;
        unsigned char lastByte = (num >> 24) & 0xFF;

        if (firstByte != lastByte) break;
    }

    printf("Succeeded with %d attempts\n",attempts);
    return 0;
}