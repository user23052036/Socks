#include <stdio.h>

int main() 
{
    unsigned int n; // size 32bits 4 bytes and signed is 16bits i.e 2 bytes
    printf("Enter number: ");
    scanf("%u", &n);

    printf("Bytes:\n%u\n%u\n%u\n%u\n",
        n&0xFF,
        (n >> 8) & 0xFF,
        (n >> 16) & 0xFF,
        (n >> 24) & 0xFF
    ); // 0xFF == 11111111 and >> right shift so here we are extracting 8 bits
    // and shifting 8 bits and then again extracting the 8 bytes, 4 times
}