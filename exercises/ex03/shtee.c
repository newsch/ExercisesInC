#include <argp.h>
#include <stdio.h>
#include <stdlib.h>

const char* argp_program_version = "shtee alpha-0.1";
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
        case ARGP_KEY_ARG:
            printf("File: \"%s\"\n", arg);
            break;
        default:
            return ARGP_ERR_UNKNOWN;
    }
    return 0;
}

static struct argp argp = { options, parse_opt, args_doc, doc };

void appendToFile(char* fileName);  // TODO: fill this out

int main(int argc, char* argv[]) {
    struct arguments arguments;
    arguments.append = 0;
    arguments.ignoreInterrups = 0;

    // print argc and argv
    printf("argc: %i, argv: [", argc);
    for (int i = 0; i<argc; i++) {
        printf("\"%s\"", argv[i]);
        if (i != argc-1) {
            printf(",");
        }
    }
    printf("]\n");

    argp_parse(&argp, argc, argv, 0, 0, &arguments);
    // print state
    printf ("append = %s\nignoreInterrupts = %s\n",
          arguments.append ? "yes" : "no",
          arguments.ignoreInterrups ? "yes" : "no");

    // TODO: implement tee
    // TODO: capture filenames in array
    // TODO: allow unknown number of filenames
    // TODO: map stdin to stdout and functions
}