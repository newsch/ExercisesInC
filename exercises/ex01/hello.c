#include <stdio.h>

int main() {
    int x = 5;
    printf("Hello, World!\n");
    return 0;
}

/* Exercise 1 Optimization Questions

with the added int declaration, the difference between the assembly is 4 lines:

15a16,17
>       subq    $16, %rsp
>       movl    $5, -4(%rbp)
19c21
<       popq    %rbp
---
>       leave

From what I can tell based on my brief research
(https://nickdesaulniers.github.io/blog/2014/04/18/lets-write-some-x86-64/),
the `subq` and `popq` lines are interacting with the stack pointer, `%rsp`. The
`movl` line is the equivalent of the `int x = 5;` line in C.

Using the optimization flag creates an assembly file that's 3 lines longer but
doesn't seem to include an equivalent `int x = 5;` line.

*/
