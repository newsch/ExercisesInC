/* Reads a text file and counts the frequency of each word.
*/

#include <stdio.h>
#include <stdlib.h>
#include <glib.h>

char* SKIPCHARS = " \t\r\n,./()[]{}*\"'";

/* Update or add a word's count to the hashmap.
*/
int handle_word(GHashTable* wordhash, char* word) {
    int* cval = g_hash_table_lookup(wordhash, word);
    if (cval == NULL) {
        return g_hash_table_insert(wordhash, word, 0);
    }
    (*cval)++;
    return *cval;
}

/* Check if a character is in a string.
 * TODO: check char num value instead of comparing to string.
*/
int char_in_str(char c, char* str) {
    for (char* sc = str; *sc; sc++) {
        if (c == *sc) {
            return TRUE;
        }
    }
    return FALSE;
}

/* Read from file into buffer up to any character in toks.
*/
int read_until(FILE* fp, char* buffer, int bufsize, char* toks) {
    size_t buf_idx = 0;

    int c;

    while (buf_idx < bufsize - 1) {
        c = fgetc(fp);
        int at_eof = (c == EOF);
        int in_str = char_in_str(c, toks);

        if (buf_idx == 0) {
            if (at_eof) {
                // stop and return EOF
                return EOF;
            }
            if (in_str) {
                // skip char and read next
                continue;
            }
        }

        if (at_eof || in_str) {
            // return to finish buffer
            // buffer[buf_idx] == '\0';
            break;
        }

        // add char to buffer and iterate
        buffer[buf_idx] = c;
        buf_idx++;
    }
    buffer[buf_idx] = '\0';
    return (int) buf_idx;
}

/* Read a file and store word counts in wordhash
*/
int read_file() {
    return 0;
}

int main(int argc, char** argv) {
    FILE* fp = fopen(argv[1], "r");

    if (fp == NULL) {
        perror("fopen");
        exit(1);
    }

    // GHashTable* wordhash = g_hash_table_new(g_str_hash,g_int_equal);

    char wordbuffer[80];
    int numread;
    while ((numread = read_until(fp, wordbuffer, sizeof(wordbuffer), SKIPCHARS)) != EOF) {
        if (numread == sizeof(wordbuffer)) {
            printf("Reached buffer limit.");
        }
        printf("read %d: %s\n", numread, wordbuffer);
    }
    // g_hash_table_insert(wordhash, "foo", 5);
    // list = g_list_append(list, "Hello world!");
    // printf("The first item is '%s'\n", (char *) g_list_first(list)->data);
    return 0;
}
