// test randomll
#include <stdio.h>
#include <stdlib.h>

#include "rand.h"

int main (int argc, char *argv[])
{
    int i;
    long long int x;

    srandom (time (NULL));

    for (i=0; i<10000; i++) {
        x = randomll();
        printf ("%lld\n", x);
    }

    return 0;
}
