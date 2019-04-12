/* Example code for Exercises in C.

Copyright 2016 Allen B. Downey
License: MIT License https://opensource.org/licenses/MIT

QUESTION ANSWERS:

1. Thread Diagram:

```
PARENT
  |
"Creating child 0"-------------------------------- CHILD 0
  |                                                   |
 fork                                              sleep 0
  |                                                   |
"Creating child 1" ----------------- CHILD 1  "Hello from child 0"
  |                                    |              |
 fork                               sleep 1    /---< exit
  |                                    |      /
"Creating child 2" --- CHILD 2  /------|-----/
  |             /--------|-----/       |
wait 0 <-------/      sleep 2   "Hello from child 1"
  |                      |             |
wait 1 <-----------------|----------- exit
  |                      |
wait 2 <--\              |
  |        \             |
exit        \    "Hello from child 2"
             \           |
              \-------- exit
```

2. What's shared?

I created global, static, main, and allocated values and had each child
decrement them. None of the children's changes were seen by other children or
the parent process, so my conclusion is that they are not shared.

```
Creating child 0.
Parent: global: 10      static: 10      main: 10        heap: 10
Creating child 1.
Parent: global: 10      static: 10      main: 10        heap: 10
Creating child 2.
Hello from child 0.
Child: global: 9        static: 9       main: 9 heap: 9
Parent: global: 10      static: 10      main: 10        heap: 10
Hello from the parent.
Child 17037 exited with error code 0.
Hello from child 1.
Child: global: 9        static: 9       main: 9 heap: 9
Child 17038 exited with error code 1.
Hello from child 2.
Child: global: 9        static: 9       main: 9 heap: 9
Child 17039 exited with error code 2.
Parent: global: 10      static: 10      main: 10        heap: 10
Elapsed time = 2.001693 seconds.
```

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/time.h>
#include <sys/types.h>
#include <wait.h>


// errno is an external global variable that contains
// error information
extern int errno;

int globalVal = 10;
static int staticVal = 10;

// get_seconds returns the number of seconds since the
// beginning of the day, with microsecond precision
double get_seconds() {
    struct timeval tv[1];

    gettimeofday(tv, NULL);
    return tv->tv_sec + tv->tv_usec / 1e6;
}


void child_code(int i, int *mainVal, int *heapVal)
{
    sleep(i);
    printf("Hello from child %d.\n", i);
    globalVal--;
    staticVal--;
    (*mainVal)--;
    (*heapVal)--;
    printf("Child: global: %d\tstatic: %d\tmain: %d\theap: %d\n", globalVal, staticVal, *mainVal, *heapVal);
}

// main takes two parameters: argc is the number of command-line
// arguments; argv is an array of strings containing the command
// line arguments
int main(int argc, char *argv[])
{
    int mainVal = 10;
    int* heapVal = malloc(sizeof(int));
    *heapVal = 10;

    int status;
    pid_t pid;
    double start, stop;
    int i, num_children;

    // the first command-line argument is the name of the executable.
    // if there is a second, it is the number of children to create.
    if (argc == 2) {
        num_children = atoi(argv[1]);
    } else {
        num_children = 1;
    }

    // get the start time
    start = get_seconds();

    for (i=0; i<num_children; i++) {

        // create a child process
        printf("Creating child %d.\n", i);
        pid = fork();

        /* check for an error */
        if (pid == -1) {
            fprintf(stderr, "fork failed: %s\n", strerror(errno));
            perror(argv[0]);
            exit(1);
        }

        /* see if we're the parent or the child */
        if (pid == 0) {
            child_code(i, &mainVal, heapVal);
            exit(i);
        } else {
            printf("Parent: global: %d\tstatic: %d\tmain: %d\theap: %d\n", globalVal, staticVal, mainVal, *heapVal);
        }
    }

    /* parent continues */
    printf("Hello from the parent.\n");

    for (i=0; i<num_children; i++) {
        pid = wait(&status);

        if (pid == -1) {
            fprintf(stderr, "wait failed: %s\n", strerror(errno));
            perror(argv[0]);
            exit(1);
        }

        // check the exit status of the child
        status = WEXITSTATUS(status);
        printf("Child %d exited with error code %d.\n", pid, status);
    }
    printf("Parent: global: %d\tstatic: %d\tmain: %d\theap: %d\n", globalVal, staticVal, mainVal, *heapVal);
    // compute the elapsed time
    stop = get_seconds();
    printf("Elapsed time = %f seconds.\n", stop - start);

    exit(0);
}
