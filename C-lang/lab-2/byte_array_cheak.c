#include <stdio.h>

int main() 
{
    int num = 0x12345678;  // base 16 hexadecimal
    unsigned char *ptr = (unsigned char*)&num;

    printf("Bytes and their addresses:\n");
    for (int i = 0; i < sizeof(num); i++)
        printf("Byte %d: %02X at address %p\n", i + 1, ptr[i], &ptr[i]);

    /*
        %02X prints the byte in hex, two digits.
        %p prints the memory address.
    */

    if (ptr[0] == 0x78) printf("\nSystem is Little Endian.\n");
    else printf("\nSystem is Big Endian.\n");
    return 0;
}