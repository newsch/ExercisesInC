/* cards

Returns the sum of entered integers.
For Exercise 2 of Allen Downey's "Exercises in C".

Author: Evan Lloyd New-Schmidt
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARRAY_LEN 3
#define BUFFER_LEN 8


/* Calculate the sum of an integer array.
a: integer array
size: size of array a

returns: the sum of the array
*/
long int sum(int* a, int size) {
    long int s = 0;
    for (int i = 0; i < size; i++) {
        s += a[i];
        printf("%i ", a[i]);
    }
    return s;
}

int main() {
    char input[BUFFER_LEN];  // space for +/-32,767, \n, and \0
    int array[ARRAY_LEN] = {};  // initialized w/ zeros: https://stackoverflow.com/questions/2589749/how-to-initialize-array-to-0-in-c
    long int s;  // long int for sum, max +/- 2,147,483,647 < +/- 32/767 * 64

    printf("Enter up to %i integers (of up to an arbitrary %i digits) and ^D to sum.\n", ARRAY_LEN, BUFFER_LEN - 2);
    int i;
    for (i = 0; i < ARRAY_LEN + 1; i++) {
        // check for EOF to stop
        if (fgets(input, BUFFER_LEN, stdin) == NULL) {
            break;
        }
        // check against array length
        if (i >= ARRAY_LEN) {
            fprintf(stderr, "Reached maximum number of numbers\n");
            return 1;
        }
        // check against buffer length
        if (strlen(input) == BUFFER_LEN - 1 && input[BUFFER_LEN - 2] != '\n') {
            fprintf(stderr, "Input exceeded buffer\n");
            return 1;
        }

        int val = atoi(input);
        // check int-ness of input
        if (val == 0 && strncmp(input, "0\n", 3)) {
            fprintf(stderr, "Could not parse input as int\n");
            return 1;
        }
        array[i] = val;
        printf("Value: %i\n", val);
    }
    s = sum(array, i);  // only sum entered numbers (up to i, including ^D)
    printf("Sum: %li\n", s);
    return 0;
}