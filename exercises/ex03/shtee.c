#include <argp.h>
#include <stdio.h>
#include <stdlib.h>

// #define DEBUG  // print more debugging info

const char* argp_program_version = "shtee alpha-0.2";
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
    int append, ignoreInterrups;  // flags
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
            arguments->ignoreInterrups = 1;
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

void openFile(char* fileName, int append, FILE* );  // TODO: fill this out

int main(int argc, char* argv[]) {
    // prep argument storage struct
    char* p[argc];
    struct arguments arguments;
    arguments.append = 0;
    arguments.ignoreInterrups = 0;
    arguments.numFiles = 0;
    // allocate array of string pointers for filenames, will never be larger
    // than number of arguments
    arguments.fileNames = malloc(sizeof(char*) * argc);

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
          arguments.ignoreInterrups ? "yes" : "no");
    #endif

    // TODO: implement tee
    // TODO: catch interrupt

    int numOuts = arguments.numFiles + 1;

    // prep outputs
    // outs[0] is stdout, rest are files from args
    FILE* outs[numOuts];
    outs[0] = stdout;
    const char* mode = arguments.append ? "a" : "w";  // set mode for fopen
    // open files and add to outs
    for (int j=0; j<arguments.numFiles; j++) {
        outs[j+1] = fopen(arguments.fileNames[j], mode);
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

    // close files (NOT stdout)
    for (int i=1; i<numOuts; i++) {
        fclose(outs[i]);
    }
}