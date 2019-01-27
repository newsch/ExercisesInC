#include <stdio.h>

int main() {
    int x = 5;
    printf("%d\n", x);
    return 0;
}

/* Exercise 1 Optimization Questions

1.  With the added int declaration, the difference between the assembly is 4
    lines:

    15a16,17
    >       subq    $16, %rsp
    >       movl    $5, -4(%rbp)
    19c21
    <       popq    %rbp
    ---
    >       leave

    From what I can tell based on my brief research
    (https://nickdesaulniers.github.io/blog/2014/04/18/lets-write-some-x86-64/),
    the `subq` and `popq` lines are interacting with the stack pointer, `%rsp`.
    The `movl` line is the equivalent of the `int x = 5;` line in C.

2.  Using the optimization flag creates an assembly file that's 3 lines longer
    but doesn't seem to include an equivalent `int x = 5;` line.

3.  When printing `x` with `printf`, the assembly code calls `printf` instead
    of `puts`, and passes the x value and the string into registers:

    subq    $16, %rsp
    movl    $5, -4(%rbp)
    movl    -4(%rbp), %eax
    movl    %eax, %esi
    movl    $.LC0, %edi
    movl    $0, %eax
    call    printf

    When optimized, it looks like it only sets 5 once, like it's using a
    constant value instead of assigning and referencing. It also calls
    `__printf_chk` instead of `printf`, which seems like an internal function
    called by `printf`:

    subq    $8, %rsp
    .cfi_def_cfa_offset 16
    movl    $5, %edx
    movl    $.LC0, %esi
    movl    $1, %edi
    xorl    %eax, %eax
    call    __printf_chk

*/
