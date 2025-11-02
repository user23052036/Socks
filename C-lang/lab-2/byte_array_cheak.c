#include <stdio.h>

int main() 
{
    int num = 0x12345678;  // base 16 hexadecimal
    unsigned char *ptr = (unsigned char*)&num;

    printf("Bytes and their addresses:\n");
    for (int i = 0; i < sizeof(num); i++)
        printf("Byte %d: %05X at address %p\n",i+1, ptr[i], &ptr[i]);

    /*
        %X for printing hexadecimal val
        %02X prints the byte in hex, 2 represents no of digits and 0 represents padding used on left
        %p prints the memory address.

        if we would have written %@5 the nmbers would be of length 5 with @ padding in left
    */

    if (ptr[0] == 0x78) printf("\nSystem is Little Endian.\n");
    else printf("\nSystem is Big Endian.\n");
    return 0;
}