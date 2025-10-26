#include <stdio.h>

int main() 
{
    unsigned int num;
    printf("Enter a number: ");
    scanf("%u", &num);

    char b1 = num & 0xFF;
    char b2 = (num >> 8) & 0xFF;
    char b3 = (num >> 16) & 0xFF;
    char b4 = (num >> 24) & 0xFF;

    printf("Byte 1 lsb: %u\n", (unsigned char)b1);
    printf("Byte 2      : %u\n", (unsigned char)b2);
    printf("Byte 3      : %u\n", (unsigned char)b3);
    printf("Byte 4 msb: %u\n", (unsigned char)b4);

    return 0;
}