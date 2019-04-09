/* Simple example using Glib.

From http://www.ibm.com/developerworks/linux/tutorials/l-glib/

Questions from EX08:

Q: Where is GLib from and why does it exist? Who uses it, and for what? Would it have been better if they had given it a name less likely to be confused with glibc?

A: GLib was created by the GNOME desktop project (but can be used independently of it) and provides implementations of data structures, IO facilities, warnings, and other niceties (Wikipedia refers to it as a "widget toolkit"). It seems like it would be useful for anyone writing cross-platform projects that wants a consistent API, or if you don't want to implement and debug (reinvent the wheel) some common patterns and practices that aren't included in standard C. In some ways it seems like an expansion of the standard lib, so maybe something like `Gstdlib` or `Gextlib` would be names that better communicate what it is?

Q: What are the most important pros and cons of using GLib, as opposed to another library, or just using core C features?

A: I think they're probably the same as most libraries - you can save time by not implementing everything yourself, but you need to spend time familiarizing yourself with the library's API, how to use it effectively, how to distribute it, if it doesn't end up fitting your usecase then you'll need to do that all over again.

Q: What do you have to do to compile and run a "Hello GLib" example?

A: You need to give the compiler glib's include paths and library locations, something like "gcc -Wall -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include    ex_compile.c  -lglib-2.0 -o ex_compile". The GLib documentation recommends you do this using pkg-config, their example is "cc hello.c `pkg-config --cflags --libs glib-2.0` -o hello".

*/

#include <stdio.h>
#include <stdlib.h>
#include <glib.h>

int main(int argc, char** argv) {
    GList* list = NULL;
    list = g_list_append(list, "Hello world!");
    printf("The first item is '%s'\n", (char *) g_list_first(list)->data);
    return 0;
}
