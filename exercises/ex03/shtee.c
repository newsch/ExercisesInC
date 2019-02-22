/* shtee, a tee clone
Made by Evan New-Schmidt.

RE: questions

3. What worked, what slowed you down? What would you do differently next time?
  Argp was pretty useful, but understanding the documentation took a long time.
  Getopt would have been shorter and faster for this usecase, but I'm glad I
  learned how argp works. I ran into the issue of cached file changes not being
  written to on interrupts/errors, and I had to refactor a bit to save the
  files array in the global space and allocate it after startup in order to be
  able to close all of the files on a signal. Assigning array/pointer values to
  structs was also confusing.

4. Apple uses a linked list for managing the list of filenames. Both Apple and
  GNU use getopt, not argp. Both also read more than a single character (Apple
  reads 8KiB) in the input/output loop. Both also do more error checking than I
  do.
*/
#include <argp.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>


// #define DEBUG  // print more debugging info

// program globals
FILE** outs;  // array of FILE* outputs
int numOuts = 0;  // number of FILE* outputs


// argp configuration

// globals for argp
const char* argp_program_version = "shtee beta-0.3";
const char* argp_program_bug_address = "evan@new-schmidt.com";
// doc strings
static char doc[] = "shtee -- a tee clone";
static char args_doc[] = "[FILE1]...";
// commandline options
static struct argp_option options[] = {
    {"append", 'a', 0, OPTION_ARG_OPTIONAL, "append to the given FILEs, do not overwrite"},
    {"ignore-interrupts", 'i', 0, OPTION_ARG_OPTIONAL, "ignore interrupt signals"},
    {"foobar", 0, 0, OPTION_DOC, "neat"},
    { 0 }  // terminating entry
};
// internal representation of arg state
struct arguments {
    int append, ignoreInterrupts;  // flags
    int numFiles;  // number of files passed in
    char** fileNames;  // array of string pointers
};
// function for parse loop
static error_t parse_opt(int key, char* arg, struct argp_state* state) {
    // extract arguments from state
    struct arguments *arguments = state->input;

    switch (key) {
        case 'a':
            arguments->append = 1;
            break;
        case 'i':
            arguments->ignoreInterrupts = 1;
            break;
        case ARGP_KEY_ARG:  // args, not opts (files)
            #ifdef DEBUG
            printf("File: \"%s\"\n", arg);
            #endif
            arguments->fileNames[arguments->numFiles] = arg;
            arguments->numFiles++;
            break;
        default:
            return ARGP_ERR_UNKNOWN;
    }
    return 0;
}
static struct argp argp = { options, parse_opt, args_doc, doc };


// interrupt handler to close files before exiting
void interruptHandler(int signal) {
    #ifdef DEBUG
    printf("Handled signal %i\n", signal);
    #endif
    cleanup();
    exit(0);
}

// close all opened files (NOT stdout) and free outs array
void cleanup() {
    for (int i=1; i<numOuts; i++) {
        fclose(outs[i]);
    }
    free(outs);
    #ifdef DEBUG
    printf("Closed %i files\n", numOuts-1);
    #endif
}


int main(int argc, char* argv[]) {
    // prep argument storage struct
    char* p[argc];
    struct arguments arguments;
    arguments.append = 0;
    arguments.ignoreInterrupts = 0;
    arguments.numFiles = 0;
    // allocate array of string pointers for filenames, should never be larger
    // than number of arguments
    arguments.fileNames = (char**) malloc(sizeof(char*) * argc);

    #ifdef DEBUG  // print argc and argv
    printf("argc: %i, argv: [", argc);
    for (int i = 0; i<argc; i++) {
        printf("\"%s\"", argv[i]);
        if (i != argc-1) {
            printf(",");
        }
    }
    printf("]\n");
    #endif

    argp_parse(&argp, argc, argv, 0, 0, &arguments);  // parse arguments

    #ifdef DEBUG  // print state
    printf ("append = %s\nignoreInterrupts = %s\n",
          arguments.append ? "yes" : "no",
          arguments.ignoreInterrupts ? "yes" : "no");
    #endif

    // register signal handlers
    if (arguments.ignoreInterrupts) {
        signal(SIGINT, SIG_IGN);
    } else {
        signal(SIGINT, interruptHandler);
    }
    signal(SIGQUIT, interruptHandler);
    signal(SIGABRT, interruptHandler);
    signal(SIGKILL, interruptHandler);
    signal(SIGTERM, interruptHandler);

    // prep outputs
    // outs[0] is stdout, rest are files from args
    int maxOuts = arguments.numFiles + 1;
    outs = (FILE**) malloc(sizeof(FILE*) * maxOuts);
    if (outs == NULL) {
        exit(1);
    }

    outs[0] = stdout;
    numOuts++;
    const char* mode = arguments.append ? "a" : "w";  // set mode for fopen
    // open files and add to outs
    for (int j=0; j<arguments.numFiles; j++) {
        outs[1+j] = fopen(arguments.fileNames[j], mode);
        numOuts++;
    }
    free(arguments.fileNames);  // free fileNames since we're done with them

    // read from stdin character by character and write until EOF received
    char c;
    while (1) {
        c = getchar();
        if (c == EOF) {
            break;
        }
        for (int i=0; i<numOuts; i++) {
            fputc(c, outs[i]);
        }
    }

    cleanup();  // close files and free outs
    return 0;
}
