/* Example code for Think OS.

Copyright 2014 Allen Downey
License: GNU GPLv3

*/

#include <stdio.h>
#include <stdlib.h>

#define SIZE 5

int *foo() {
    int i;
    int array[SIZE];

    // printf("%p\n", array);

    for (i=0; i<SIZE; i++) {
        array[i] = 42;
    }
    return array;
}

void bar() {
    int i;
    int array[SIZE];

    // printf("%p\n", array);

    for (i=0; i<SIZE; i++) {
        array[i] = i;
    }
}

int main()
{
    int i;
    int *array = foo();
    bar();

    for (i=0; i<SIZE; i++) {
        printf("%d\n", array[i]);
    }

    return 0;
}

/* ex02 answers

1. Program prints the locations of two arrays defined locally in functions, and then prints the contents of the arrays locations in memory (presumably the same space, with the contents of the second array overwriting the contents of the first array after deallocation). I would expect to see the contents of the array in bar() printed, 0-4.

2. On compilation, I get the following warning:
  ```
  stack.c: In function ‘foo’:
  stack.c:22:12: warning: function returns address of local variable [-Wreturn-local-addr]
       return array;
              ^
  ```
  It doesn't like returning local variable locations to code with different scope.

3. On execution, I see the two addresses of the arrays and no other output - not even empty line breaks.

4. With both print statements commented out I don't get any output at all.
*/
