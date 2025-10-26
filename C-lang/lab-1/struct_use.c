#include <stdio.h>

// typedef int number; now number is just another name for int
// number x=6; same as int

/*
Defining a structure with the tag name student.
Creating a typedef alias also called student.

struct student s1;  // uses the tag name
student s2;         // uses the typedef alias (preferred)

typedef is just giving a name to simplify complex structures

*/

typedef struct dob // this is tag name
{ 
    int d, m, y; 
}dob; // this is typedef alias

typedef struct student_info 
{ 
    int roll; 
    char name[50]; 
    float cgpa; 
    dob age; 
}student_info;



void byVal(student_info s) // here s is a variable of structure studemt_info
{
    printf("[Val]:->  %d %s %.2f %02d-%02d-%d\n", s.roll, s.name, s.cgpa, s.age.d, s.age.m, s.age.y);
}

void byAddr(student_info *s) // here s is just a memory address pointing to s a variable of student_info
{
    printf("[Addr] %d %s %.2f %02d-%02d-%d\n", s->roll, s->name, s->cgpa, s->age.d, s->age.m, s->age.y);
}

int main() 
{
    student_info s = {101, "Alice", 9.12, {5,10,2003}};
    byVal(s); 
    byAddr(&s);
}