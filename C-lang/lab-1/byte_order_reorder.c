#include <stdio.h>

typedef struct packet
{ char ch1, ch2[2], ch3;}packet;

int main() 
{
    unsigned int n;
    packet p;
    printf("Enter number: ");
    scanf("%u", &n);

    p.ch1 = n & 0xFF;
    p.ch2[0] = (n >> 8) & 0xFF;
    p.ch2[1] = (n >> 16) & 0xFF;
    p.ch3 = (n >> 24) & 0xFF;

    printf("Bytes: %u %u %u %u\n", p.ch1, p.ch2[0], p.ch2[1], p.ch3);

    n = p.ch1 | (p.ch2[0] << 8) | (p.ch2[1] << 16) | (p.ch3 << 24);
    printf("Reconstructed: %u\n", n);
}

/*
Note:
------
This program extracts bytes and reconstructs the same number.
It does NOT convert endianness — both steps use the same byte order (LSB first).

To actually convert between little and big endian,
you must reverse the byte order while rebuilding.
*/

/*
Execution order:

Each shift is evaluated:

p.ch2[0] << 8
p.ch2[1] << 16
p.ch3 << 24

Then OR operations are performed left-to-right:

(p.ch1) | (p.ch2[0] << 8)
result | (p.ch2[1] << 16)`
result | (p.ch3 << 24)`

------------------------------------
Tiny Summary

Shifting happens first.
OR happens next.
left-to-right.
*/