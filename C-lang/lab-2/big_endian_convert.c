#include <stdio.h>

unsigned int toBigEndian(unsigned int n) 
{
    return ((n >> 24)) | ((n >> 8) & 0xFF00) | ((n << 8) & 0xFF0000) | ((n << 24));
}

/*
    in my system intel stores in little endian so 0x12345678 is stored as

     3     2     1     0
    0x12  0x34  0x56  0x78     (little endian)
    0x78  ox56  0x34  0x12      (big endian)
*/

int main() 
{
    unsigned int n;
    printf("Enter number: ");
    scanf("%u", &n);

    printf("Big Endian: 0x%X\n", toBigEndian(n));
    return 0;
}