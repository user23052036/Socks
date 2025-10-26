#include <stdio.h>

int main() 
{
    unsigned int num = 1;
    char *ptr = (char*)&num;

    if (*ptr == 1) printf("Machine is Little Endian\n");
    else printf("Machine is Big Endian\n");
    return 0;
}

/*
Little Endian
The *least significant byte* goes first in memory. Imagine writing a number starting from the 
tiny digits on the right side first. Intel CPUs love this style.

Big Endian
The *most significant byte* goes first in memory. It feels like reading numbers normally, 
from the big important digits on the left. Many network protocols prefer this.

Take the decimal number: 500

500 in bytes looks like this:
* **MSB** (Most Significant Byte): 1
* **LSB** (Least Significant Byte): 244
  (because 500 = 1×256 + 244)

Now see how they are stored:

| Endianness        | Memory Order | Explanation                               |
| ----------------- | ------------ | ----------------------------------------- |
| **Little Endian** | 244, 1       | Least significant part (244) stored first |
| **Big Endian**    | 1, 244       | Most significant part (1) stored first    |

You still have the same number 500.
Only the **order in memory changes**.

A tiny story:

500 says,
"244 is smaller than me, you walk first!"
That’s Little Endian.

Big Endian replies,
"I am the boss byte 1, I walk first."

Boom. Same number. Different byte walking order.

*/