/* cards

Commandline program for basic card counting.
Based on the example in chapter 1 of "Head First C".

Author: Evan Lloyd New-Schmidt
*/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

/* Parse a string of a card into an integer value.

    card: string of card representation, must be (upper or lowercase) 'A', 'K',
        'Q', 'J', or a number between 1 and 10 inclusive

    returns: int of the card value between 1 and 11 or -1 if unparsable
*/
int parseCard(char * cardName) {
    int val;
    switch (toupper(cardName[0])) {
        case 'K':
        case 'Q':
        case 'J':
            val = 10;
            break;
        case 'A':
            val = 11;
            break;
        default:
            val = atoi(cardName);
            if ((val < 1) || (val > 10)) {  /* invalid number/character */
                return -1;
            }
    }
    return val;
}

/* Add a new card to a running count.

    Values between 2 and 7 (exclusive) increment the count, and values of 10
    decrement the count.

    val: value of the card to consider

    returns: value of the running total
*/
int countCard(int val) {
    static int count;
    if ((val > 2) && (val < 7)) {
        count++;
    } else if (val == 10) {
        count--;
    }
    return count;
}

int main() {
    char cardName[3];
    int val = 0;
    do {
        puts("Enter a card (A, K, Q, J, 1-10), or X to exit: ");
        scanf("%2s", cardName);
        if (toupper(cardName[0]) == 'X') {  /* continue and exit loop/program */
            continue;
        }
        val = parseCard(cardName);
        if (val < 0) {  /* try again */
            puts("I don't understand that value!");
            continue;
        }
        printf("Card value: %i\n", val);
        printf("Current count: %i\n", countCard(val));
    } while (toupper(cardName[0]) != 'X');
    return 0;
}