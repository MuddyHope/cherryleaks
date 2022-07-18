#include "c-mem.h"
/* Evgenii Meshcheriakov. Excercise 20 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define LSTWORD 9
#define FRSTWORD 0
#define MAXCHAR 126
#define MINCHAR 32
#define PASSWORDS 3
#define PASSIZE 30
#define RNDCHARS 10

char *rand_str(size_t length);
int rand_num(int min, int max);
int main(void)
{
    START;
    char* buffer = NULL;
    char pass[PASSWORDS][PASSIZE];
    const char* words[LSTWORD+1] = {
            "one", "two", "three", "four", "five",
            "six", "seven", "eight", "nine", "ten" };
    time_t t;
    srand((unsigned) time(&t));

    for(int i=0; i<PASSWORDS; i++) {
        buffer = rand_str(RNDCHARS);
        strcat(buffer, words[rand_num(FRSTWORD, LSTWORD)]);
        strcat(buffer, "\0");
        strcpy(pass[i], buffer);
        printf("Password %d: %s\n", i+1, pass[i]);
    }
    END_PRINT_LEFT;
    return 0;
}

int rand_num(int min, int max)
{
    int random = (rand() % (max - min + 1)) + min;
    return random;
}

char *rand_str(size_t length) {
    int key = 0;
    char *str = NULL;
    if (length) {
        str = malloc(sizeof(char) * PASSIZE);

        if (str) {
            for (int i = 0; i < length; i++) {
                key = rand() % (MAXCHAR - MINCHAR + 1) + MINCHAR;
                str[i] = key;
            }
            str[length] = '\0';
        }
    } else {
        printf("Error during malloc\n");
    }
    return str;
}