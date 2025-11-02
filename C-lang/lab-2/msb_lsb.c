#include <stdio.h>

int main() 
{
    unsigned int num;
    printf("Enter a 4-byte unsigned integer: ");
    scanf("%u", &num);

    unsigned char lsb = num & 0xFF;  // first 8 bits 0xFF == 11111111
    unsigned char msb = (num >> 24) & 0xFF;  // last 8 bits we can also write (num & 0xFF000000)

    /*
        Byte0 → bits 0–7
        Byte3 → bits 24–31

        used unsigned char cause it holds exactly one byte
        Why unsigned char works perfectly

        Guaranteed 0–255 range
        Matches all valid byte values
        No negative surprises
        Ideal for bitwise operations and memory-level data
        It treats the byte as data, not a character symbol.

        char [-128 - 127]
    */

    printf("First Byte (MSB): %u\n", msb);
    printf("Last Byte (LSB): %u\n", lsb);

    return 0;
}