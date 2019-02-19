#include <argp.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

// #define DEBUG  // print more debugging info

const char* argp_program_version = "shtee beta-0.3";
const char* argp_program_bug_address = "evan@new-schmidt.com";

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

// parse an option
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

FILE** outs;  // array of FILE* outputs
int numOuts = 0;  // number of FILE* outputs

// close files (NOT stdout)
void closeFiles() {
    for (int i=1; i<numOuts; i++) {
        fclose(outs[i]);
    }
    #ifdef DEBUG
    printf("Closed %i files\n", numOuts-1);
    #endif
}

void interruptHandler(int signal) {
    #ifdef DEBUG
    printf("Handled signal %i\n", signal);
    #endif
    closeFiles();
    exit(0);
}

static struct argp argp = { options, parse_opt, args_doc, doc };

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

    // TODO: pass errors on from malloc, fopen, fclose
    // TODO: comment functions and break into more functions?

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

    closeFiles();
    return 0;
}
