/* Example code for Think OS.

Copyright 2014 Allen Downey
License: GNU GPLv3

*/

#include <stdio.h>
#include <stdlib.h>

int var1;

void printLocalVar() {
    int a = 1;
    printf ("a (local function var) points to %p\n", &a);
}

int main ()
{
    int var2 = 5;
    void *p = malloc(128);
    char *s = "Hello, World";

    printf ("Address of main is %p\n", main);
    printf ("Address of var1 (global var) is %p\n", &var1);
    printf ("Address of var2 (local main var) is %p\n", &var2);
    printf ("p (first allocation) points to %p\n", p);
    printf ("s (read-only string) points to %p\n", s);

    void *r = malloc(128);
    char t[] = "Scoopdittywoop";
    printf ("r (second allocation) points to %p\n", r);
    printf ("t (writable char array) points to %p\n", t);

    printLocalVar();

    void* r1 = malloc(13);
    void* r2 = malloc(13);

    printf ("r1 (allocation of 13 bytes) points to %p\n", r1);
    printf ("r2 (allocation of 13 bytes) points to %p\n", r2);

    return 0;
}
