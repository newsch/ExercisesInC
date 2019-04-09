/* Reads a text file and counts the frequency of each word.
 *
 * Usage: "./word_count FILE"
 *
 * Prints the totals unsorted in the format <COUNT>\t<WORD>. Sorting can be done
 * with "sort": "./word_count foo.txt | sort -g -r". Punctuation is discarded.
 *
 * Output from "New Hacker's Dictionary, The" (https://archive.org/details/jarg422):
 * ```
 * $ ./word_count jarg422.txt | sort -r -g | head -n 15
 * 15217   htm
 * 15215   jarg422h
 * 9697    the
 * 4762    3d
 * 4498    and
 * 2638    that
 * 2378    Node
 * 2377    Next
 * 2375    Previous
 * 2035    for
 * 1714    The
 * 1256    with
 * 1171    from
 * 1026    are
 * 1014    this
 * ```
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>

// #define DEBUG

// characters to skip
char* SKIPCHARS = " \t\r\n,./()[]{}*\"'!@#$%%^&*-_=+\\|~:;<>?";

/* Update or add a word's count to the hashmap.
 *
 * Returns: the new count of the word, or -1 on error
*/
int handle_word(GHashTable* wordhash, char* word) {
    int* cval = g_hash_table_lookup(wordhash, word);
    if (cval == NULL) {
        // allocate storage for count of new word
        int* new_count = malloc(sizeof(int));
        if (new_count == NULL) {
            return -1;
        }
        *new_count = 1;
        g_hash_table_insert(wordhash, strdup(word), new_count);
        return *new_count;
    }
    (*cval)++;
    return *cval;
}

/* Check if a character is in a string.
 * TODO: check char num value instead of comparing to string.
 *
 * Returns: TRUE if c is in str, FALSE if not
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
 *
 * If a char in toks is read first, reads until it finds a valid character and
 * then an invalid one.
 *
 * Returns: the number of valid characters read (and stored in buffer), or EOF if at EOF
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
            break;
        }

        // add char to buffer and iterate
        buffer[buf_idx] = c;
        buf_idx++;
    }
    buffer[buf_idx] = '\0';
    return (int) buf_idx;
}

int main(int argc, char** argv) {
    FILE* fp = fopen(argv[1], "r");

    if (fp == NULL) {
        perror("File error");
        exit(1);
    }

    // hash table to store {word: count}
    GHashTable* wordhash = g_hash_table_new(g_str_hash,g_int_equal);

    char wordbuffer[80];
    int numread;
    int count;
    while ((numread = read_until(fp, wordbuffer, sizeof(wordbuffer), SKIPCHARS)) != EOF) {
        if (numread == sizeof(wordbuffer)) {
            fprintf(stderr, "Reached buffer limit.");
        }
        // TODO: convert to lowercase before checking
        count = handle_word(wordhash, wordbuffer);
        if (count == -1) {
            perror("handle_word");
            exit(2);
        }
        #ifdef DEBUG
        printf("read %d: %s\n", numread, wordbuffer);
        printf("count: %d\n", count);
        #endif
    }

    // print totals
    GList* keys = g_hash_table_get_keys(wordhash);
    GList* vals = g_hash_table_get_values(wordhash);

    GList *k = keys;
    GList *v = vals;
    while (TRUE) {
        if (k == NULL || v == NULL) {
            break;
        }
        printf("%d\t%s\n", *(int*) (v->data), (char*) (k->data));
        k = k->next;
        v = v->next;
    }

    return 0;
}
