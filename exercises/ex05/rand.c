/*  Implementations of several methods for generating random floating-point.

Copyright 2016 Allen B. Downey
License: MIT License https://opensource.org/licenses/MIT
*/

#include <stdlib.h>

// #define DEBUG

#ifdef DEBUG
#include <stdio.h>
#include <string.h>
#endif

// generate a random float using the algorithm described
// at http://allendowney.com/research/rand
float my_random_float()
{
    int x, exp, mant;
    float f;

    // this union is for assembling the float.
    union {
        float f;
        int i;
    } b;

    // generate 31 random bits (assuming that RAND_MAX is 2^31 - 1
    x = random();

    // use bit-scan-forward to find the first set bit and
    // compute the exponent
    asm ("bsfl %1, %0"
    :"=r"(exp)
    :"r"(x)
    );
    exp = 126 - exp;

    // use the other 23 bits for the mantissa (for small numbers
    // this means we are re-using some bits)
    mant = x >> 8;
    b.i = (exp << 23) | mant;

    return b.f;
}

// alternative implementation of my algorithm that doesn't use
// embedded assembly
float my_random_float2()
{
    int x;
    int mant;
    int exp = 126;
    int mask = 1;

    union {
        float f;
        int i;
    } b;

    // generate random bits until we see the first set bit
    while (1) {
        x = random();
        if (x == 0) {
            exp -= 31;
        } else {
            break;
        }
    }

    // find the location of the first set bit and compute the exponent
    while (x & mask) {
        mask <<= 1;
        exp--;
    }

    // use the remaining bit as the mantissa
    mant = x >> 8;
    b.i = (exp << 23) | mant;

    return b.f;
}

// get a random long long int (64 bits) by concatenating random ints
long long int randomll() {
    long long int a = 0;
    // int llintS = sizeof(long long int);
    // int intS = sizeof(int);
    // for (int i=0; i < llintS; i += intS) {
    for (int i=0; i<3; i++) {
        #ifdef DEBUG
        printf("iter: %lld\n", a);
        #endif
        a <<= sizeof(int)*8 - 1;
        int b = random();
        #ifdef DEBUG
        printf("b: %d\n", b);
        #endif
        a |= b;
    }
    a = a & ~(((long long int) 1)<<63);  // set sign bit to 0
    #ifdef DEBUG
    printf("sign bit: %lld\n", ((unsigned long long int) a) >> 63);
    // char buffer[65];
    // itoa(a, buffer, 2);
    // printf("binary: %s", buffer);
    #endif
    return a;
}

// compute a random double using my algorithm
double my_random_double()
{
    // 1 sign bit, 11 exponent bits, 52 fraction bits
    long long x, mantissa, exp;
    exp = 1022;  // start at -1 (only decimal), 1022-1023 https://en.wikipedia.org/wiki/Exponent_bias

    union {
        double d;
        long long i;
    } b;

    // pick random number
    // loop to allow exponent to decrease more than 63
    for (int i=0; 1; i++) {
        #ifdef DEBUG
        printf("iter %i\n", i);
        #endif
        x = randomll();
        if (x == 0 && x >= 63) {
            exp -= 63;
        } else {
            break;
        }
    }

    // step through bits to set exponents
    int mask = 1;
    while(x & mask && exp > 1) {
        mask <<= 1;
        exp--;
    }

    mantissa = x >> 11;
    b.i = (exp << 52) | mantissa;

    return b.d;
}

// return a constant (this is a dummy function for time trials)
float dummy()
{
    float f = 0.5;
    return f;
}

// generate a random integer and convert to float (dummy function)
float dummy2()
{
    int x;
    float f;

    x = random();
    f = (float) x;

    return f;
}

// generate a random float using the standard algorithm
float random_float()
{
    int x;
    float f;

    x = random();
    f = (float) x / (float) RAND_MAX;

    return f;
}


// generate a random double using the standard algorithm
float random_double()
{
    int x;
    double f;

    x = random();
    f = (double) x / (double) RAND_MAX;

    return f;
}
