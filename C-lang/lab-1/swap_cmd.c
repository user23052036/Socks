#include <stdio.h>
#include <stdlib.h>

/*
📘 Concept:
--------------
In C, when you run a program from the command line, you can pass *arguments* to it.

Example run:
    ./a.out 10 20

Here:
    argc = 3  
        → counts total arguments: ["./a.out", "10", "20"]

    argv = array of strings:
        argv[0] → "./a.out"  (program name)
        argv[1] → "10"        (first argument as string)
        argv[2] → "20"        (second argument as string)

*/


void swap(int *a, int *b) 
{
    int temp = *a; 
    *a = *b;       
    *b = temp;      
}

// 📌 main() with command-line arguments
int main(int argc, char *argv[]) 
{
    // ✅ Step 1: Validate number of arguments
    if (argc != 3) // expecting program name + 2 numbers = 3 arguments
    {
        printf("Usage: %s <num1> <num2>\n", argv[0]);
        return 1; 
    }

    
    int x = atoi(argv[1]);  // atoi() = argument to integer
    int y = atoi(argv[2]);

    printf("Before Swap: x = %d, y = %d\n", x, y);
    swap(&x, &y);
    printf("After Swap:  x = %d, y = %d\n", x, y);

    return 0;
}