#include <stdio.h>
#include <stdlib.h>

/*
argc (argument count): number of command-line arguments (including program name).
argv (argument vector): an array of strings representing the arguments.
*/
void swap(int *a, int *b) 
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int main(int argc, char *argv[]) 
{
    if (argc != 3) 
    {
        printf("enter at least 2 strings(numbers)");
        return 1;
    }

    int x = atoi(argv[1]);  // string to integer
    int y = atoi(argv[2]);

    printf("Before Swap: x = %d, y = %d\n", x, y);
    swap(&x,&y);
    printf("After Swap:  x = %d, y = %d\n", x, y);

    return 0;
}