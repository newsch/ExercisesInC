/* Example code for Software Systems at Olin College.

Copyright 2017 Allen Downey
License: Creative Commons Attribution-ShareAlike 3.0

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>

#include "trout/util.h"
#include "minunit.h"

int tests_run = 0;

static char* testTv_sub() {
    struct timeval tests[][3] = {
        // out, in, expected
        {{3, 0}, {1, 0}, {2, 0}},             // 1: tv_sec subtraction
        {{0, 1000}, {0, 500}, {0, 500}},      // 2: tv_usec subtraction
        {{3, 1000}, {1, 500}, {2, 500}},      // 3: combined subtraction
        {{1, 1000}, {0, 2000}, {0, 999000}},  // 4: combined subtraction w/ carry
        // {{3, 0}, {1, 0}, {0, 0}},             // 5: false (for debugging)
    };
    char* message = malloc(sizeof(char)*80);
    for (int i=0; i<sizeof(tests)/sizeof(tests[0]); i++) {
        struct timeval* t = tests[i];
        sprintf(message, "testTv_sub case %i failed", i+1);
        tv_sub(t, t+1);
        int res = ((t[0].tv_sec == t[2].tv_sec) && (t[0].tv_usec == t[2].tv_usec));
        mu_assert(message, res == 1);
    }
    return NULL;
}

static char * all_tests() {
    mu_run_test(testTv_sub);
    return NULL;
}

int main(int argc, char **argv) {
    char *result = all_tests();
    if (result != NULL) {
        printf("%s\n", result);
    } else {
        printf("ALL TESTS PASSED\n");
    }
    printf("Tests run: %d\n", tests_run);

    return result != 0;
}
