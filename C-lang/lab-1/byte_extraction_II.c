#include <stdio.h>

int main() 
{
    unsigned int n; // 4 bytes (32 bits) on most systems
    printf("Enter number: ");
    scanf("%u", &n);

    /*
     * WHY WE USE (unsigned char *) HERE:
     * ----------------------------------
     * - A normal 'unsigned int*' points to the WHOLE integer (4 bytes at once).
     *   Example: p = &n  →  p[0] = n,  p[1] = next integer (4 bytes away).
     *
     * - But we want to see EACH BYTE stored in memory.
     *   So we use a 'char*' because:
     *      → 1 char = 1 byte (smallest addressable unit in memory)
     *
     * - We use **unsigned char** instead of plain 'char' because:
     *      → Plain 'char' can be signed (-128 to 127)
     *      → Unsigned char always gives clean values (0–255)
     *
     * Hence:
     *      (unsigned char*)&n  → lets us safely access all 4 bytes of 'n'
     */
    unsigned char *p = (unsigned char*)&n;

    printf("\nBytes stored in memory (little-endian order likely):\n");
    for (int i = 0; i < 4; i++)
        printf("Byte %d: %u\n", i, p[i]);  // print each byte as an unsigned value

    /*
     * NOTE:
     * -----
     * On little-endian systems (like Intel/AMD CPUs),
     * memory stores the least significant byte first.
     * So for 0x12345678, the bytes will appear as:
     *      78 56 34 12
     *
     * On big-endian systems, they would appear as:
     *      12 34 56 78
     *
     * This shows how your system's memory actually stores integers.
     */

    return 0;
}
